#include "towerDefence.h"

void shotEnemy(){
	int i,j,k,l,temp,flag;
	for(i=0;i<curEnemy;++i){
		flag = 0;
		for(j=0;j<numOfTower;++j){
			temp = tower[j].numOfBullet;
			for(k=0;k<temp;++k){
				if(tower[j].b[k].posX-1 == enemy[i].posX && tower[j].b[k].posY-1 == enemy[i].posY){
					if(tower[j].dir==UP){
						tower[j].b[k]=tower[j].b[temp-1];
						--tower[j].numOfBullet;
						--temp;
					}
					else if(tower[j].dir==DOWN){
						tower[j].b[k]=tower[j].b[temp-1];
						--tower[j].numOfBullet;
						--temp;
					}
					else if(tower[j].dir==RIGHT){
						tower[j].b[k]=tower[j].b[temp-1];
						--tower[j].numOfBullet;
						--temp;
					}
					else if(tower[j].dir==LEFT){
						tower[j].b[k]=tower[j].b[temp-1];
						--tower[j].numOfBullet;
						--temp;
					}
					enemy[i].hp-=tower[j].dmg;
					if(enemy[i].hp<=0){
						flag = 1;
						score += 1;
						money += 20;
						for(l=i;l<curEnemy-1;++l)
							enemy[l] = enemy[l+1];
						--curEnemy;
						break;
					}
				}
				if(flag==1)
					break;
			}
			if(flag==1)
				break;
		}
	}
}

void upgrade(int y,int x){
	int i;
	for(i=0;i<numOfTower;++i){
		if(tower[i].posY==y && tower[i].posX==x){
			if(tower[i].fireRate<9){
				if(tower[i].fireRate==5){
					if(money<1000){
						printStatusBar("You don't have enough money! You need 1000 money!       ");
						break;
					}
					money-=1000;
					tower[i].dmg = 1000;
				}
				else if(tower[i].fireRate==6){
					if(money<5000){
						printStatusBar("You don't have enough money! You need 5000 money!      ");
						break;
					}
					money-=5000;
					tower[i].dmg = 10000;
				}
				else if(tower[i].fireRate==7){
					if(money<10000){
						printStatusBar("You don't have enough money! You need 10000 money!     ");
						break;
					}
					money-=10000;
					tower[i].dmg = 100000;
				}
				else if(tower[i].fireRate==8){
					if(money<50000){
						printStatusBar("You don't have enough money! You need 50000 money!     ");
						break;
					}
					money-=50000;
					tower[i].dmg = 100000000;
				}
				printStatusBar("Upgrade Complete                                 ");
				tower[i].bulletConst=0;
				++tower[i].fireRate;
				break;
			}
			else if(tower[i].fireRate==9)
				printStatusBar("It was fully upgraded!                           ");
		}
	}
}
