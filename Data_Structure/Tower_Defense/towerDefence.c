#include "towerDefence.h"

int middleX = 0;	//It stores a middle x-coordinate
int middleY = 0;	//It stores a middle y-coordinate

int cursorX = 1;	//Cursor's left_top x-coordinate
int cursorY = 1;	//Cursor's left_top y-coordinate

char *choices[] = {
	"PLAY",
	"RANKING",
	"HELP",
	"EXIT",
};

const int n_choices = sizeof(choices) / sizeof(char*);	//The number of choices user can choose

int score;
int gameOver=0;
int money;
int life;
int cur_wave;
int curMapType;			//A player's current map type.
int bulletSpeed=3000;	//which control's game speed
int enemySpeed = 6000;
int enemyGenSpeed=200000;
int bulletTimer=0;
int enemyTimer=0;
int enemyGenTimer=0;
int buildFlag=0;	//If an user type 't',then buildFlag will be set to 1
int curEnemy;
int waveEnemy;

TOWER tower[MAX_TOWER_NUM];
int numOfTower;
int nodeNum;

Node* rankHead;

int startX=0;
int startY=0;
int finishX=0;
int finishY=0;
int curEnemy=0;
int waveEnemy=0;
ENEMY enemy[MAX_ENEMY_NUM];

int main (int argc,char *argv[]){
	int input;
	int choice=0;
	MEVENT event;

	initscr();	//Start curses mode
	clear();
	noecho();
	cbreak();	//Line buffering disalbed

	middleX = (60 - MENU_WIDTH) / 2;	//Calculating for a center placement
	middleY = (24 - MENU_HEIGTH) / 2;

	start_color();
	init_pair(1,COLOR_BLACK,COLOR_CYAN);
	init_pair(2,COLOR_RED,COLOR_RED);
	init_pair(3,COLOR_CYAN,COLOR_CYAN);
	init_pair(4,COLOR_GREEN,COLOR_GREEN);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_RED,COLOR_WHITE);

	attron(COLOR_PAIR(1));
	mvprintw(23,1,"------------------Click on Exit to quit------------------");
	refresh();
	attroff(COLOR_PAIR(1));

	print_menu(1,middleY,middleX);
	mousemask(ALL_MOUSE_EVENTS,NULL);				
	keypad(stdscr,TRUE);
	mouseinterval(0);								//Remove mouse delay
	curs_set(0);									//Remove a cursor

	createRankList();

	while(1){
		attron(COLOR_PAIR(1));
		mvprintw(23,1,"------------------Click on Exit to quit------------------");
		refresh();
		attroff(COLOR_PAIR(1));
		input = wgetch(stdscr);
		switch(input){
			case KEY_MOUSE:
				if(getmouse(&event) == OK){
					if(event.bstate & BUTTON1_PRESSED){
						report_choice(event.x+1,event.y,&choice);
						if(choice==-1)
							goto end;
						switch(choice){
							case MENU_PLAY: play(); break;
							case MENU_RANK: rank(); break;
							case MENU_HELP: help(); break;
							default: break;
						}
						clear();
						refresh();
					}
				}
				print_menu(choice,middleY,middleX);
				break;
		}
	}
end:

	endwin();
	system("clear");
	return 0;
}

int checkToMove(int y,int x){
	if(0<x && x<MAX_X-3 && 0<y && y<MAX_Y-3) return 1;
	else return 0;
}

int checkToBuild(int y,int x){
	int i,j;
	if(numOfTower+1>MAX_TOWER_NUM){
		printStatusBar("You can't build more tower!                            ");	
		return 0;
	}
	if(money<100){
		printStatusBar("You don't have enough money! You need 100 money!          ");
		return 0;
	}
	for(i=0;i<3;++i)
		for(j=0;j<3;++j)
			if(map[curMapType][y+i][x+j]){
				printStatusBar("You can't build that place!                          ");
				return 0;
			}

	return 1;
}

void initTowerDefence(){
	int i,j;
	score=0;
	gameOver=0;
	curEnemy=0;
	waveEnemy=0;
	buildFlag=0;
	money=500;
	life = 20;
	bulletTimer=0;
	enemyTimer=0;
	enemySpeed = 6000;
	enemyGenTimer=0;
	cur_wave=1;
	cursorX = 1;
	cursorY = 1;
	numOfTower=0;
	for(i=0;i<MAX_Y;++i)	//map initialization
		for(j=0;j<MAX_X;++j)
			if(map[curMapType][i][j]==2)
				map[curMapType][i][j]=0;
	drawOutLine();
	drawField();
	drawCursor(cursorY,cursorX);
	printStat(score, curEnemy, money, cur_wave, life);
	printStatusBar("Build first tower to start game!");
}

void drawOutLine(){

	//outline for map
	drawBox(0,0,36,60);

	//outline for status bar
	drawBox(37,0,7,60);

	//outline for score
	drawBox(0,61,44,20);
}

int getCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
		case KEY_UP:
			break;
		case KEY_DOWN:
			break;
		case KEY_LEFT:
			break;
		case KEY_RIGHT:
			break;
		case 't':
			command = BUILDTOWER;
			break;
		case 'u':
			command = UPGRADE;
			break;
		case 'q':
		case 'Q':
			command = QUIT;
			break;
			//		case ' ':
			//			command = SPACE;
			//			break;
		default:
			command = NOTHING;
			break;
	}
	return command;
}

int processCommand(int command){
	int ret=1;
	int moveFlag=0,drawFlag=0;
	switch(command){
		case QUIT:
			ret=QUIT;
			break;
		case KEY_UP:
			if(buildFlag==0){
				if(moveFlag = checkToMove(cursorY-1,cursorX))
					cursorY-=1;
			}
			else{
				buildTower(cursorY,cursorX,UP);
				drawTower(cursorY,cursorX);
				drawFlag=1;
				buildFlag=0;
			}
			break;
		case KEY_DOWN:
			if(buildFlag==0){
				if(moveFlag = checkToMove(cursorY+1,cursorX))
					cursorY+=1;
			}
			else{
				buildTower(cursorY,cursorX,DOWN);
				drawTower(cursorY,cursorX);
				drawFlag=1;
				buildFlag=0;
			}
			break;
		case KEY_RIGHT:
			if(buildFlag==0){
				if(moveFlag = checkToMove(cursorY,cursorX+1))
					cursorX+=1;
			}
			else{
				buildTower(cursorY,cursorX,RIGHT);
				drawTower(cursorY,cursorX);
				drawFlag=1;
				buildFlag=0;
			}
			break;
		case KEY_LEFT:
			if(buildFlag==0){
				if(moveFlag = checkToMove(cursorY,cursorX-1))
					cursorX-=1;
			}
			else{
				buildTower(cursorY,cursorX,LEFT);
				drawTower(cursorY,cursorX);
				drawFlag=1;
				buildFlag=0;
			}
			break;
		case BUILDTOWER:
			buildFlag = checkToBuild(cursorY,cursorX);
			break;
		case UPGRADE:
			upgrade(cursorY,cursorX);
			break;
		default:
			break;
	}
	if(moveFlag) drawChangedCursor(cursorY,cursorX);
	if(drawFlag){
		drawChangedField(cursorY,cursorX);
		refresh();
	}
	return ret;
}

void drawField(){
	int i,j;
	for(i=0;i<MAX_Y;++i){
		move(i+1,1);
		for(j=0;j<MAX_X;++j){
			if(map[curMapType][i][j]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else if(map[curMapType][i][j]==2){
				attron(COLOR_PAIR(4));
				printw(" ");
				attroff(COLOR_PAIR(4));
			}
			else 
				printw(" ");
		}
	}
}

void drawChangedField(int y,int x){
	drawField();
	drawCursor(y,x);
	reDrawBullet();
	reDrawEnemy();
}

void drawCursor(int y,int x){
	int i,j;
	move(y,x);
	attron(COLOR_PAIR(2));
	addch(ACS_ULCORNER);
	for(i=0;i<3;++i)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(i=0;i<3;++i){
		move(y+1+i,x);
		addch(ACS_VLINE);
		move(y+1+i,x+4);
		addch(ACS_VLINE);
	}
	move(y+i+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<3;++i)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
	attroff(COLOR_PAIR(2));
}

void drawChangedCursor(int y,int x){
	drawField();
	drawCursor(y,x);
	reDrawBullet();
	reDrawEnemy();
}

void printStat(int score, int curEnemy, int money, int cur_wave, int life){
	mvprintw(20,64,"score : %8d",score);
	mvprintw(21,64,"enemy : %8d",curEnemy);
	mvprintw(22,64,"money : %8d",money);
	mvprintw(23,64,"wave  : %8d",cur_wave);
	mvprintw(24,64,"life  : %8d",life);
}

void printStatusBar(char* string){
	mvprintw(41,2,"%s",string);
}

void drawBox(int y,int x,int height,int width){
	int i,j;
	move(y,x);
	attron(COLOR_PAIR(3));
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
	attroff(COLOR_PAIR(3));
}

void play(){
	int command;
	clear();
	refresh();
	chooseMapType();
	initTowerDefence();
	nodelay(stdscr,TRUE);	// if i use nodelay(stascr,TRUE) and don't type anything, wgetch may return -1
	do{
		printStat(score, curEnemy, money, cur_wave, life);
//		if(numOfTower!=0 && bulletTimer % bulletSpeed==0){
//			moveBullet();
//			shotEnemy();
//			bulletTimer %= bulletSpeed;
//			drawChangedField(cursorY,cursorX);
//		}
		if(numOfTower!=0 && enemyTimer % enemySpeed == 0){
			enemyTimer %= enemySpeed;
			summonEnemy();
			shotEnemy();
			drawChangedField(cursorY,cursorX);
		}
		if(numOfTower!=0 && bulletTimer % bulletSpeed==0){
			moveBullet();
			shotEnemy();
			bulletTimer %= bulletSpeed;
			drawChangedField(cursorY,cursorX);
		}
		if(numOfTower!=0 && enemyGenTimer % enemyGenSpeed == 0){
			if(curEnemy==0){
				waveEnemy = 0;
				++cur_wave;
			}
			if(enemySpeed>1000)
				enemySpeed-=10;
			enemyGenTimer %= enemyGenSpeed;
		}

		if(numOfTower!=0){
			++enemyGenTimer;
			++bulletTimer;
			++enemyTimer;
		}
		command = getCommand();
		if(processCommand(command)==QUIT){
			nodelay(stdscr,FALSE);
			drawBox(44/2-5,80/2-10,3,15);
			mvprintw(18,31," Are You sure?");
			mvprintw(19,31,"   (QUIT : q)  ");
			mvprintw(20,31," (CONTINUE : c)");
			refresh();
			while(1){
				command=getch();
				if(command=='q'){
					newRank(score);
					return;
				}
				else if(command=='c'){
					nodelay(stdscr,TRUE);
					clear();
					drawOutLine();
					drawField();
					drawCursor(cursorY,cursorX);
					printStat(score, curEnemy, money, cur_wave, life);
					break;
				}
			}
		}
	}while(!gameOver);
	nodelay(stdscr,FALSE);
	drawBox(44/2-5,80/2-10,3,15);
	mvprintw(18,31,"               ");
	mvprintw(19,31,"   Game Over   ");
	mvprintw(20,31,"               ");
	refresh();
	getch();
	newRank(score);
}

void print_menu(int highlight,int midY,int midX){
	int x,y,i;
	x=midX+2;
	y=midY+3;
	drawBox(midY,midX,MENU_HEIGTH,MENU_WIDTH);
	for(i=0;i<n_choices;++i){
		if(highlight==i+1){
			attron(COLOR_PAIR(1));
			mvprintw(y,x,"%s",choices[i]);
			attroff(COLOR_PAIR(1));
		}
		else
			mvprintw(y,x,"%s",choices[i]);
		++y;
	}
	refresh();
}

void report_choice(int mouse_x,int mouse_y,int *p_choice){
	int i,j,choice;
	i = middleX + 2;
	j = middleY + 3;
	for(choice = 0; choice < n_choices; ++choice)
		if(mouse_y == j+choice && mouse_x >= i && mouse_x <= i+strlen(choices[choice])){
			if(choice == n_choices - 1)
				*p_choice = -1;
			else
				*p_choice = choice +1;
			break;
		}
}

void chooseMapType(){
	int x=3,y=4;
	int midX = (80-MENU_WIDTH)/2;
	int midY = (44-MENU_HEIGTH)/2;
	drawBox(midY,midX,7,30);
	mvprintw(midY+4,midX+3,"Choose map type : ");
	echo();
	while(1){
		refresh();
		scanw("%d",&curMapType);
		if( curMapType > 0 && curMapType < MAP_TYPE)
			break;
		else{
			clear();
			drawBox(midY,midX,7,30);
			attron(COLOR_PAIR(5));
			mvprintw(midY+6,midX+3,"You can choose from 1 to %d",MAP_TYPE-1);
			attroff(COLOR_PAIR(5));
			mvprintw(midY+4,midX+3,"Choose map type : ");
		}
	}
	--curMapType;
	noecho();
}

void drawTower(int y,int x){
	int i,j;
	for(i=0;i<3;++i)
		for(j=0;j<3;++j)
			map[curMapType][y+i][x+j]=2;
}

void buildTower(int y,int x,DIRECTION dir){
	int i;
	money-=100; //towerCost
	tower[numOfTower].dmg = 10;
	tower[numOfTower].posX = x;
	tower[numOfTower].posY = y;
	//	tower[numOfTower].type = 0;
	//	tower[numOfTower].twLevel = 0;
	tower[numOfTower].fireRate = 5;
	tower[numOfTower].bulletConst = 0;
	tower[numOfTower].dir = dir;
	tower[numOfTower].numOfBullet = 0;
	if(dir==UP){
		for(i=0;i<MAX_BULLET_NUM;++i){
			tower[numOfTower].b[i].posX=x+2;
			tower[numOfTower].b[i].posY=y;
			//	tower[numOfTower].b[i].dir=dir;
		}
	}
	else if(dir==DOWN){
		for(i=0;i<MAX_BULLET_NUM;++i){
			tower[numOfTower].b[i].posX=x+2;
			tower[numOfTower].b[i].posY=y+4;
			//	tower[numOfTower].b[i].dir=dir;
		}
	}
	else if(dir==RIGHT){
		for(i=0;i<MAX_BULLET_NUM;++i){
			tower[numOfTower].b[i].posX=x+4;
			tower[numOfTower].b[i].posY=y+2;
			//	tower[numOfTower].b[i].dir=dir;
		}
	}
	else if(dir==LEFT){
		for(i=0;i<MAX_BULLET_NUM;++i){
			tower[numOfTower].b[i].posX=x;
			tower[numOfTower].b[i].posY=y+2;
			//	tower[numOfTower].b[i].dir=dir;
		}
	}
	++numOfTower;
	if(numOfTower==1)
		printStatusBar("                                                     ");
}

void drawBullet(BULLET b){
	mvprintw(b.posY,b.posX,"@");
}

void moveBullet(){
	int i,j,temp;
//	drawChangedField(cursorY,cursorX);
	for(i=0;i<numOfTower;++i){
		temp = tower[i].numOfBullet;
		if(tower[i].dir==UP){
			for(j=0;j<temp;++j){
				if(tower[i].b[j].posY!=1){
					drawBullet(tower[i].b[j]);
					--(tower[i].b[j].posY);
				}
				else{
					tower[i].b[j]=tower[i].b[temp-1];
					if(temp!=1)
						drawBullet(tower[i].b[j]);
					--tower[i].numOfBullet;
					--temp;
				}
			}
		}
		else if(tower[i].dir==DOWN){
			for(j=0;j<temp;++j){
				if(tower[i].b[j].posY!=MAX_Y-1){
					drawBullet(tower[i].b[j]);
					++(tower[i].b[j].posY);
				}
				else{
					tower[i].b[j]=tower[i].b[temp-1];
					if(temp!=1)
						drawBullet(tower[i].b[j]);
					--tower[i].numOfBullet;
					--temp;
				}
			}
		}
		else if(tower[i].dir==RIGHT){
			for(j=0;j<temp;++j){
				if(tower[i].b[j].posX!=MAX_X-1){
					drawBullet(tower[i].b[j]);
					++(tower[i].b[j].posX);
				}
				else{
					tower[i].b[j]=tower[i].b[temp-1];
					if(temp!=1)
						drawBullet(tower[i].b[j]);
					--tower[i].numOfBullet;
					--temp;
				}
			}
		}
		else if(tower[i].dir==LEFT){
			for(j=0;j<temp;++j){
				if(tower[i].b[j].posX!=1){
					drawBullet(tower[i].b[j]);
					--(tower[i].b[j].posX);
				}
				else{
					tower[i].b[j]=tower[i].b[temp-1];
					if(temp!=1)
						drawBullet(tower[i].b[j]);
					--tower[i].numOfBullet;
					--temp;
				}
			}
		}
	}
	for(i=0;i<numOfTower;++i){
		if(tower[i].bulletConst % (10-tower[i].fireRate) == 0 ){	//interval % constant == 0 ??
			if(tower[i].dir==UP){
				tower[i].b[tower[i].numOfBullet].posX = tower[i].posX+2;
				tower[i].b[tower[i].numOfBullet].posY = tower[i].posY;
			}
			else if(tower[i].dir==DOWN){
				tower[i].b[tower[i].numOfBullet].posX = tower[i].posX+2;
				tower[i].b[tower[i].numOfBullet].posY = tower[i].posY+4;
			}
			else if(tower[i].dir==RIGHT){
				tower[i].b[tower[i].numOfBullet].posX = tower[i].posX+4;
				tower[i].b[tower[i].numOfBullet].posY = tower[i].posY+2;
			}
			else if(tower[i].dir==LEFT){
				tower[i].b[tower[i].numOfBullet].posX = tower[i].posX;
				tower[i].b[tower[i].numOfBullet].posY = tower[i].posY+2;
			}
			++tower[i].numOfBullet;
			tower[i].bulletConst %= (10-tower[i].fireRate);
		}
		++tower[i].bulletConst;
	}
	refresh();
}

void reDrawBullet(){
	int i,j,temp;
	for(i=0;i<numOfTower;++i){
		temp = tower[i].numOfBullet;
		for(j=0;j<temp;++j)
			drawBullet(tower[i].b[j]);
	}
	refresh();
}
