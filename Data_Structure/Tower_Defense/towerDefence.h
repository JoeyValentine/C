#ifndef TOWER_DEFENCE
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TOWER_DEFENCE

//Direction type
typedef enum {UP,DOWN,RIGHT,LEFT} DIRECTION;

//Map's WIDTH and HEIGTH
#define MAX_X 60
#define MAX_Y 36
#define MAP_TYPE 5 //The number of maps which player can choose
#define MAX_TOWER_NUM 100
#define MAX_BULLET_NUM 60
#define MAX_ENEMY_NUM 50

//Menu's WIDTH and HEIGTH
#define MENU_WIDTH 30
#define MENU_HEIGTH 8

//Menu number
#define MENU_PLAY 1
#define MENU_RANK 2
#define MENU_HELP 3

#define NAMELEN 20

#define QUIT 'q'
#define BUILDTOWER 'b'
//#define SPACE ' '
#define UPGRADE 'u'
//#define SKILL1 'z'
//#define SKILL2 'x'
//#define SKILL3 'c'
//#define SKILL4 'v'
#define NOTHING 0

extern int middleX;	//It stores a middle x-coordinate
extern int middleY;	//It stores a middle y-coordinate

extern int cursorX;	//Cursor's left_top x-coordinate
extern int cursorY;	//Cursor's left_top y-coordinate

extern char *choices[];

typedef struct{
	char shape[2];
	int hp;
	int posX;	//current position
	int posY;
	int preX;	//post position
	int preY;
//	bool exist;		//It indicates whether an enemy is dead or not
//	bool poison;
}ENEMY;

typedef struct{
	DIRECTION dir;
	int posX;
	int posY;
//	bool exist;		//It indicates whether an enemy is hit by bullet
}BULLET;

typedef struct{
	int dmg;
	int posX;	//Tower's middle x-coordinate
	int posY;	//Tower's middle y-coordinate
//	int type;
//	int twLevel;
	int fireRate;
	int bulletConst;	// it is needed to control tower's firerate
	DIRECTION dir; //It indicates a direction in which it shoots bullet
	int numOfBullet;
	BULLET b[MAX_BULLET_NUM];
}TOWER;

typedef struct _Node{
	char name[NAMELEN];
	int score;
	struct _Node* link;
}Node;

extern const int n_choices;	//The number of choices user can choose
extern char map[MAP_TYPE][MAX_Y][MAX_X];

extern int score;
extern int gameOver;
extern int money;
extern int life;
extern int cur_wave;
extern int curMapType;	//A player's current map type.
extern int bulletSpeed;	//which control's bullet's speed
extern int enemySpeed;
extern int gameSpeed;
extern int buildFlag;	//If an user type 't',then buildFlag will be set to 1

extern TOWER tower[MAX_TOWER_NUM];
extern int numOfTower;
extern int nodeNum;

extern Node* rankHead;

int checkToMove(int y,int x);
int checkToBuild(int y,int x);

extern int startX;
extern int startY;
extern int finishX;
extern int finishY;
extern int curEnemy;
extern int waveEnemy;
extern ENEMY enemy[MAX_ENEMY_NUM];

void drawField();
void drawCursor(int y,int x);
void drawChangedCursor();	//Draw a changed cursor
void drawChangedField(int y,int x); //Draw a changed building
void initTowerDefence();

void drawOutLine();
void drawTower(int y,int x);
int getCommand();
int processCommand(int command);

void printStat(int score, int curEnemy, int money, int cur_wave, int life);
void printScore(int score);
void printLeftEnemy(int left_enemy);
void printMoney(int money);
void printCurWave(int cur_wave);
void printLife(int life);
void printStatusBar(char* string);

void drawBox(int y,int x,int height,int width);
void buildTower(int y,int x,DIRECTION dir);

void play();
void rank();

void print_menu(int highlight,int midY,int midX);			//Print menu on window
void report_choice(int mouse_x,int mouse_y,int* p_choice);	//Print what you click

void chooseMapType();

void drawBullet(BULLET b);
void moveBullet();
void reDrawBullet();	//redraw bullet

void push();
void createRankList();
void rank();
void writeRankFile();
void newRank(int score);

void setPos(int curMap);
void summonEnemy();
void drawEnemy(ENEMY e);
void reDrawEnemy();

void shotEnemy();
void upgrade(int y,int x);
#endif
