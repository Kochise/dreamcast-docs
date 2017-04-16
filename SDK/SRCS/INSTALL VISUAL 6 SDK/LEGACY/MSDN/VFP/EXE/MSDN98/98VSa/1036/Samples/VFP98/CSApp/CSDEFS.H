*
*Obvious note to localizers: anything that doesn't end with "_LOC" should be left alone
*

*Any given #def may be used in several places; the notes on the
*"location" where it's used is mostly for the developer's benefit

#DEFINE HELP_OPENDBC	489321236
#DEFINE HELP_CONFLICTS	489321237
#DEFINE HELP_SAMPLE		489321238


* Operating System codes
#DEFINE	OS_W32S				1
#DEFINE	OS_NT				2
#DEFINE	OS_WIN95			3
#DEFINE	OS_MAC				4
#DEFINE	OS_DOS				5
#DEFINE	OS_UNIX				6
#define ERRORTITLE_LOC		"Microsoft Visual FoxPro"
#DEFINE CS_TIMEOUT			5

#define ERRORMESSAGE_LOC "Erreur N°" + alltrim(str(m.nError)) + " dans " + m.cMethod +	" (" + alltrim(str(m.nLine)) + "): " + m.cMessage


#define MB_ICONEXCLAMATION		48
#define MB_ABORTRETRYIGNORE		2
#define MB_OK					0
#define ALERTTITLE_LOC		"Microsoft Visual FoxPro"
#define THERMCOMPLETE_LOC	"Terminé."
#DEFINE	C_DEBUG				.F.

* Client server application defs
#DEFINE CS_DATABASE						"cs.dbc"
#DEFINE CS_CONNECTION					"emp_connection"
#DEFINE CS_TABLE						"employee"
#DEFINE CS_INITIALTABLE					"emp_init"
#DEFINE CS_LOCAL_VIEW					"emp_view_local"
#DEFINE CS_REMOTE_VIEW					"emp_view_remote"
#DEFINE CS_CONFLICTS					"conflicts"
#DEFINE CS_BIZRULES						"bizrules"

#DEFINE CS_ROWCONFLICT_LOC				"Conflits sur la ligne:  "

#DEFINE CS_STATUS_LOC 					"Statut: "
#DEFINE CS_STATTBL_LOC 					"Table: "
#DEFINE CS_STATLV_LOC 					"Vue locale: "
#DEFINE CS_STATRV_LOC 					"Vue distante: "
#DEFINE CS_STATOPENEX_LOC 				"OPEN  EXCLUSIVE"
#DEFINE CS_STATOPENSH_LOC 				"OPEN  SHARED"
#DEFINE CS_STATNOOPEN_LOC 				"NOT  OPEN"
#DEFINE CS_STATONLINE_LOC 				"ONLINE"
#DEFINE CS_STATOFFLINE_LOC 				"OFFLINE"

#DEFINE NO_CURSOR						0
#DEFINE TABLE_CURSOR					1
#DEFINE LOCAL_VIEW_CURSOR				2
#DEFINE REMOTE_VIEW_CURSOR				3

#DEFINE DBC_TYPE						"DBC"
#DEFINE GETFILE_LOC						"Nom de fichier: "
#DEFINE GETFILEBTN_LOC					"OK"

* Client server Info messages
#DEFINE CS_DATABASE_INFO_LOC		"La base de données CS.DBC est requise par cet exemple. Vérifiez que " +"le chemin d'accès complet à CS.DBC est affiché dans la zone de texte." +								" Si ce n'est pas le cas, cliquez sur « ... » à côté de la zone de texte " +								"et localisez CS.DBC."



#DEFINE CS_DATABASE_INFO1_LOC		"Cliquez sur Ouvrir pour ouvrir la base de données CS.DBC. Vérifiez que Exclusive " +"est sélectionné si voulez être en mesure de modifier cette base de données dans l'exemple."

#DEFINE CS_DATABASE_INFO2_LOC		"Pour appliquer l'extension client/serveur et afficher les données distantes, vous devez définir une connexion " +"à une base de données terminale. Vouns ne devez définir la connexion qu'à la première exécution de " +								" cet exemple."


#DEFINE CS_CURSOR_INFO_LOC			"Sélectionnez un type de curseur basé sur une table, une vue locale ou une vue distante. Pour les curseurs de table vous pouvez recharger les données initiales et appliquer l'extension client/serveur à la table. Pour les curseurs de vues vous pouvez " +"basculer entre les modes en ligne et déconnecté. Sélectionnez alors l'option de concurrence et ouvrez le curseur."



#DEFINE CS_FUNCTIONS_INFO_LOC	"Informations sur les fonctionnalités de mise à jour."
#DEFINE CS_CONFLICTS_INFO_LOC	"Informations sur la résolution des conflits."

#DEFINE CONNECT_FAILURE_LOC		"L'application de l'extension client/serveur est interrompue du fait d'une erreur de connexion"
#DEFINE	CANT_OPEN_EXCLU_LOC		"Ouverture de '|1' en mode exclusif impossible."
#DEFINE NO_SUCH_FILE_LOC		"Le fichier n'existe pas."
#DEFINE BIZRULEERROR_LOC		"Erreur de violation des règles de gestion"
 
#DEFINE	WAIT_UPDATEOK_LOC		"Mise à jour réussie"
#DEFINE	WAIT_UPDATEFAIL1_LOC	"Échec de la mise à jour, la clé primaire a été modifiée"
#DEFINE	WAIT_UPDATEFAIL2_LOC	"Échec de la mise à jour"
#DEFINE WAIT_REVERTFAIL_LOC		"Échec de l'annulation"
#DEFINE WAIT_REVERT1_LOC		"1 ligne annulée"
#DEFINE WAIT_REVERT2_LOC		" lignes annulées"
#DEFINE WAIT_REQUERYOK_LOC		"Réussite de requery"
#DEFINE WAIT_REQUERYFAIL_LOC	"Échec de requery"

#DEFINE ERR_NOOPENEMP_LOC		"Ouverture de la table Employee impossible."
#DEFINE WAIT_UPSIZEOK_LOC		"Extension de la table réussie."