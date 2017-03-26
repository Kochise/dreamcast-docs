#include <kos.h>
#include <lwip/lwip.h>
#include <lwip/sockets.h>
#include <sys/queue.h>
#include <sys/process.h>
#include <kos/process.h>
#include <kos/fs_pty.h>
#include <errno.h>
#include <signal.h>

struct tel_state;
typedef TAILQ_HEAD(tel_state_list, tel_state) tel_state_list_t;

typedef struct tel_state {
	TAILQ_ENTRY(tel_state)		list;

	int			socket;
	struct sockaddr_in	client;
	socklen_t		client_size;

	kprocess_t		* proc;
	kthread_t		* thd;

	int			ptyfd;
} tel_state_t;

tel_state_list_t states;
#define st_foreach(var) TAILQ_FOREACH(var, &states, list)
mutex_t * list_mutex;

int st_init() {
	TAILQ_INIT(&states);	
	list_mutex = mutex_create();
	return 0;
}

tel_state_t * st_create() {
	tel_state_t * ns;

	ns = calloc(1, sizeof(tel_state_t));
	mutex_lock(list_mutex);
	TAILQ_INSERT_TAIL(&states, ns, list);
	mutex_unlock(list_mutex);

	return ns;
}

void st_destroy(tel_state_t *st) {
	mutex_lock(list_mutex);
	TAILQ_REMOVE(&states, st, list);
	mutex_unlock(list_mutex);
	free(st);
}

int st_add_fds(fd_set * fds, int maxfd) {
	tel_state_t * st;

	mutex_lock(list_mutex);
	st_foreach(st) {
		FD_SET(st->socket, fds);
		if (maxfd < (st->socket+1))
			maxfd = st->socket + 1;
	}
	mutex_unlock(list_mutex);
	return maxfd;
}

/**********************************************************************/

// This thread will grab input from the PTY and stuff it into the socket
void client_thread(void *param) {
	int rc, o;
	char buf[256];
	tel_state_t * ts = (tel_state_t *)param;

	printf("telnetd: client thread started, sock %d\n", ts->socket);

	// Block until we have something to write out
	for ( ; ; ) {
		rc = fs_read(ts->ptyfd, buf, 256);
		if (rc <= 0)
			break;

		for (o=0; rc; ) {
			int i = write(ts->socket, buf, rc);
			if (i <= 0) {
				rc = -1;
				break;
			}
			rc -= i;
			o += i;
		}
		if (rc < 0)
			break;
	}

	printf("telnetd: client thread exited, sock %d\n", ts->socket);
	close(ts->socket);
	fs_close(ts->ptyfd);
	st_destroy(ts);
}

// Grab any input from the socket and stuff it into the PTY
int handle_read(tel_state_t * ts) {
	char buffer[256];
	int rc, o, d;

	for (d = 0; !d; ) {
		rc = read(ts->socket, buffer, 256);
		if (rc == 0)
			return -1;
		if (rc < 256)
			d = 1;

		for (o=0; rc; ) {
			int i = fs_write(ts->ptyfd, buffer + o, rc);
			if (i <= 0)
				return -1;
			rc -= i;
			o += i;
		}
	}

	return 0;
}

/**********************************************************************/

int sighnd(int sig, void * data) {
	kprocess_t * proc = (kprocess_t *)data;
	printf("telnetd: croaked child for pid %d\n", process_get_pid(proc));
	process_wait(proc);
	return 0;
}

/**********************************************************************/

void spawn_shell(tel_state_t * ts) {
	file_t master, slave;
	kprocess_t * p;
	static const char * args[] = {
		"/rd/kosh.elf",
		"-"
	};

	// Create a new PTY pair for us to use
	if (fs_pty_create(NULL, 0, &master, &slave) < 0) {
		printf("telnetd: can't create pty for shell\n");
		return;
	}
	ts->ptyfd = master;
	assert( ts->ptyfd >= 0 );

	// Fork to start the new process
	ts->proc = process_vfork();
	if (!ts->proc) {
		printf("telnetd: can't vfork() -- %s\n", strerror(errno));
		fs_close(master);
		fs_close(slave);
		close(ts->socket);
		st_destroy(ts);
		return;
	}

	// Dup the pty descriptors into it
	fs_dup2(slave, 0);
	fs_dup2(slave, 1);
	fs_dup2(slave, 2);

	// Exec the new process image
	if (process_execv(args[0], 2, args) < 0) {
		printf("telnetd: can't exec() -- %s\n", strerror(errno));
		fs_close(master);
		fs_close(slave);
		close(ts->socket);
		st_destroy(ts);
		return;
	}

	// Close the slave on our end (we only keep master)
	fs_close(slave);

	// Make a thread to listen on the master
	ts->thd = thd_create(client_thread, ts);
}

void telnetd() {
	int listenfd;
	struct sockaddr_in saddr;
	fd_set readset;
	fd_set writeset;
	int i, maxfdp1;
	tel_state_t *ts;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) {     
		printf("telnetd: socket create failed\n");
		return;                 
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	saddr.sin_port = htons(23);

	if (bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("telnetd: bind failed\n");
		close(listenfd);
		return;
	}

	if (listen(listenfd, 10) < 0) {
		printf("telnetd: listen failed\n");
		close(listenfd);
		return;
	}

	st_init();
	printf("telnetd: listening for connections on socket %d\n", listenfd);

	for ( ; ; ) {
		maxfdp1 = listenfd + 1;

		FD_ZERO(&readset);
		FD_ZERO(&writeset);
		FD_SET(listenfd, &readset);
		maxfdp1 = st_add_fds(&readset, maxfdp1);

		i = select(maxfdp1, &readset, &writeset, 0, 0);

		if (i == 0)
			continue;

		// Check for new incoming connections
		if (FD_ISSET(listenfd, &readset)) {
			ts = st_create();
			ts->client_size = sizeof(ts->client);
			ts->socket = accept(listenfd,
				(struct sockaddr *)&ts->client,
				&ts->client_size);
			printf("telnetd: connect from %08lx, port %d, socket %d\n",
				ts->client.sin_addr.s_addr, ts->client.sin_port, ts->socket);
			if (ts->socket < 0) {
				st_destroy(ts);
			} else {
				spawn_shell(ts);
			}
		}

		// Process data from connected clients
		st_foreach(ts) {
			if (FD_ISSET(ts->socket, &readset)) {
				if (handle_read(ts) < 0) {
					printf("telnetd: disconnected socket %d\n", ts->socket);
					process_signal(ts->proc, SIGQUIT, NULL);
					break;
				}
			}
		}
	}
}

/**********************************************************************/

int main(int argc, char **argv) {
	printf("telnetd started\n");

	signal(SIGCHLD, sighnd);
	telnetd();

	printf("telnetd finished\n");
	return 0;
}
