/*
 *  snake.cpp
 *  TikiSnake - a Tiki version of the classic snake game
 *
 *  Copyright (C)2006 Sam Steele
 *
 */

#include <Tiki/tiki.h>
#include <Tiki/plxcompat.h>
#include <Tiki/gl.h>
#include <Tiki/hid.h>
#include <Tiki/tikitime.h>
#include <Tiki/drawables/console.h>

using namespace Tiki;
using namespace Tiki::GL;
using namespace Tiki::Hid;

#define BOARD_X 77
#define BOARD_Y 20

int board[BOARD_X][BOARD_Y];

int sx=3,sy=3,sdx=1,sdy=0,ssize=3;
int sscore=0,slives=3;

volatile bool quitting = false;
void tkCallback(const Hid::Event & evt, void * data) {
	if (evt.type == Hid::Event::EvtQuit) {
		quitting = true;
	} else if (evt.type == Hid::Event::EvtKeypress) {
		switch(evt.key) {
			case 27:
				quitting = true;
				break;
			case Event::KeyUp:
				sdx = 0;
				sdy = -1;
				break;
			case Event::KeyDown:
				sdx = 0;
				sdy = 1;
				break;
			case Event::KeyLeft:
				sdx = -1;
				sdy = 0;
				break;
			case Event::KeyRight:
				sdx = 1;
				sdy = 0;
				break;
		}
	}
}

extern "C" int tiki_main(int argc, char **argv) {
	int x,y;
	bool go=1;
	bool dead=0;
	
	//srand(time(NULL));
		
	// Init Tiki
	if(!Tiki::init(argc, argv))
	{
		exit(-1);
	}
	Tiki::setName("SnakeyGame", NULL);
	Hid::callbackReg(tkCallback, NULL);

	//initialize the screen		
	ConsoleText *ct = new ConsoleText(80,25,new Texture("pc-ascii.png", true));
	
	ct->setSize(640,480);
	ct->translate(Vector(320,240,0));
	ct->setAutoScroll(0);
	ct->setAutoWrap(0);

	//initialize the board
	for(x=0;x<BOARD_X;x++) {
		for(y=0;y<BOARD_Y;y++) {
			board[x][y]=0;
		}
	}
	
	//place an item
	do {
		x=rand()%BOARD_X; y=rand()%BOARD_Y;
	} while(board[x][y]!=0);
	board[x][y]=999;
	
	while(!quitting) {
		//move head
		if(!dead) {
			sx+=sdx;
			sy+=sdy;
		}
		//check bounds
		if(sx>=BOARD_X || sx<0 || sy>=BOARD_Y || sy<0) { 
			slives--; 
			ssize=3; 
			for(x=0;x<BOARD_X;x++) {
				for(y=0;y<BOARD_Y;y++) {
					board[x][y]=0;
				}
			}
			sx=rand()%BOARD_X;
			sy=rand()%BOARD_Y;
			do { //place a new item in an empty spot
				x=rand()%BOARD_X; y=rand()%BOARD_Y;
			} while(board[x][y]!=0);
			board[x][y]=999;
		}
		
		//check collisions
		if(board[sx][sy]>0) {
			if(board[sx][sy]==999) { //item
				ssize+=2; //increment snake size
				sscore++; //and score
				do { //place a new item in an empty spot
					x=rand()%BOARD_X; y=rand()%BOARD_Y;
				} while(board[x][y]!=0);
				board[x][y]=999;
				//make the stretch work correctly
				for(x=0;x<BOARD_X;x++) {
					for(y=0;y<BOARD_Y;y++) {
						if(board[x][y]>0&&board[x][y]!=999) board[x][y]+=2;
					}
				}
			} else { //snake
				slives--; 
				ssize=3; 
				for(x=0;x<BOARD_X;x++) {
					for(y=0;y<BOARD_Y;y++) {
						board[x][y]=0;
					}
				}
				sx=rand()%BOARD_X;
				sy=rand()%BOARD_Y;
			}
		}
		if(slives<=0) dead=1;
		board[sx][sy]=ssize+1;
		
		//decrement the array (simulates motion)
		for(x=0;x<BOARD_X;x++) {
			for(y=0;y<BOARD_Y;y++) {
				if(board[x][y]>0&&board[x][y]!=999) board[x][y]--;
			}
		}
		
		//render the screen
		ct->locate(0,0);
		ct->color(GREY | HIGH_INTENSITY, BLACK);
		*ct << "Score: " << sscore << endl;
		ct->locate(70,0);
		if(dead==0) *ct << "Lives: " << slives << endl; 
		ct->color(YELLOW | HIGH_INTENSITY, BLACK);
		*ct << (char)218;
		for(x=0;x<BOARD_X;x++)
			*ct << (char)196;
			*ct << (char)191 << endl;
			for(y=0;y<BOARD_Y;y++) {
				ct->color(YELLOW | HIGH_INTENSITY, BLACK);
				*ct << (char)179;
				for(x=0;x<BOARD_X;x++) {
					ct->color(GREY | HIGH_INTENSITY, BLACK);
					if(board[x][y]==999 && dead==0) { //draw an item
						ct->color(5,0);
						*ct << (char)4;
					} else if(board[x][y]>0&&dead==0) *ct << "*"; //draw a snake piece
					else *ct << " "; //draw a space
				}
				ct->color(YELLOW | HIGH_INTENSITY, BLACK);
				*ct << (char)179 << endl;
			}
			*ct << (char)192;
			for(x=0;x<BOARD_X;x++)
				*ct << (char)196;
			*ct << (char)217<<endl;
			ct->color(GREY | HIGH_INTENSITY, BLACK);
			*ct << "TikiSnake                                                  (C) 2006 Sam Steele";
			if(dead) {
				ct->color(RED, BLACK);
				ct->locate(36,11); *ct << "You Died!";
				ct->locate(36,12); *ct << "Press ESC";
			}
			
			Frame::begin();
			ct->draw(Drawable::Opaque);
			Frame::transEnable();
			ct->draw(Drawable::Trans);
			Frame::finish();
			
			Time::sleep(80000);
	}	
	
	Tiki::shutdown();

	return 0;
}

