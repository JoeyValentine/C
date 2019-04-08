#include "towerDefence.h"

void setPos(int curMap){
	switch(curMap){
		case 0 : startY = 18; startX = -1;
	//			 finishY = 18; finishX = MAX_X-1;
				 break;
		case 1 : startY = 0; startX = 52;
	//			 finishY = MAX_Y-1; finishX = 8;
				 break;
		case 2 : startY = -1; startX = 6;
	//			 finishY = 0; finishX = MAX_X-5;
				 break;
		case 3 : startY = 15; startX = 26;
	//			 finishY = 17; finishX = MAX_X-5;
				 break;
	}
}

void summonEnemy(){
	int i, j;
	setPos(curMapType);

	if(waveEnemy<MAX_ENEMY_NUM){
		enemy[curEnemy].shape[0] = '!';
		enemy[curEnemy].shape[1] = 0;
		enemy[curEnemy].hp = 5*cur_wave;
		enemy[curEnemy].posX = startX;
		enemy[curEnemy].posY = startY;
		enemy[curEnemy].preX = -256;
		enemy[curEnemy].preY = -256;
		curEnemy++;
		waveEnemy++;
	}
	if(curEnemy>0){
		for(i=0; i<curEnemy; ++i){
			if(map[curMapType][enemy[i].posY][enemy[i].posX+1] == 1 &&
			   enemy[i].preX != enemy[i].posX+1){
			   		enemy[i].preX = enemy[i].posX;
			   		enemy[i].preY = enemy[i].posY;
					enemy[i].posX++;
			   }
			else if(map[curMapType][enemy[i].posY][enemy[i].posX-1] == 1 &&
			   enemy[i].preX != enemy[i].posX-1){
			   		enemy[i].preX = enemy[i].posX;
			   		enemy[i].preY = enemy[i].posY;
					enemy[i].posX--;
			   }
			else if(map[curMapType][enemy[i].posY+1][enemy[i].posX] == 1 &&
			   enemy[i].preY != enemy[i].posY+1){
			   		enemy[i].preX = enemy[i].posX;
			   		enemy[i].preY = enemy[i].posY;
					enemy[i].posY++;
			   }
			else if(map[curMapType][enemy[i].posY-1][enemy[i].posX] == 1 &&
			   enemy[i].preY != enemy[i].posY-1){
			   		enemy[i].preX = enemy[i].posX;
			   		enemy[i].preY = enemy[i].posY;
					enemy[i].posY--;
			   }
		//	if(enemy[i].posX == finishX && enemy[i].posY == finishY){
			else{
				drawEnemy(enemy[i]);
				for(j=i;j<curEnemy-1;++j)
					enemy[j] = enemy[j+1];
				--curEnemy;
				--life;
				if(life==0){
					printStat(score,curEnemy,money,cur_wave,life);
					gameOver=1;
				}
			}
		}
		for(i=0; i<curEnemy; ++i)
			drawEnemy(enemy[i]);
	}

	refresh();
}

void drawEnemy(ENEMY e){
	attron(COLOR_PAIR(6));
	mvprintw(e.posY+1, e.posX+1, e.shape);
	attroff(COLOR_PAIR(6));
}

void reDrawEnemy(){
	int i;
	for(i=0;i<curEnemy;++i)
		drawEnemy(enemy[i]);
	refresh();
}
