#include "towerDefence.h"

void push(char* name,int score){
	int flag=0;
	Node* newNode=(Node*)malloc(sizeof(Node)),*temp;
	newNode->score=score;
	strcpy(newNode->name,name);
	newNode->link = NULL;
	if(rankHead==NULL)
		rankHead=newNode;
	else{
		if(nodeNum==1 && score <= rankHead->score)
			rankHead->link=newNode;
		else if(score >= rankHead->score){
			newNode->link = rankHead;
			rankHead = newNode;
		}
		else{
			for(temp=rankHead;temp->link;temp=temp->link){
				if(temp->score >= score && ((temp->link)->score) <= score){
					newNode->link = temp->link;
					temp->link = newNode;
					flag = 1;
					break;
				}
			}
			if(flag==0)
				temp->link = newNode;
		}
	}
	++nodeNum;
}

void createRankList(){
	char name[NAMELEN];
	int numOfPeople,score,i;
	FILE* fp = fopen("rank.txt","r");
	if(fp==NULL){
		//if there is no rank.txt,then program makes ranking list automatically
		fp = fopen("rank.txt","w");
		fprintf(fp,"3\n");
		fprintf(fp,"999999999 CALCULUS PRINCESS\n");
		fprintf(fp,"888888888 MI NU KIM\n");
		fprintf(fp,"777777777 MAN JU LEE\n");
		fclose(fp);
		fp = fopen("rank.txt","r");
	}
	rankHead=NULL;
	fscanf(fp,"%d",&numOfPeople);
	for(i=0;i<numOfPeople;++i){
		fscanf(fp,"%d%*c",&score);
		fgets(name,NAMELEN,fp);
		name[strlen(name)-1] = 0;	//remove enter
		push(name,score);
	}
	fclose(fp);
}

void newRank(int score){
	char name[NAMELEN];
	while(1){
		clear();
		drawBox(4, 6, 9, 35);
		mvprintw(9, 8, "Your name : ");
		echo();
		getnstr(name,NAMELEN);
		noecho();
		if(name[0]!=0 && name[0]!=' ' && name[0]!='\t')
			break;
	}
	push(name,score);
	writeRankFile();
}

void writeRankFile(){
	int i;
	FILE* fp=fopen("rank.txt","w");
	Node* temp;
	fprintf(fp,"%d\n",nodeNum);
	for(i=0,temp=rankHead;i<nodeNum;++i,temp=temp->link)
		fprintf(fp,"%d %s\n",temp->score,temp->name);
	fclose(fp);
}

void nodeSearch(char* name){
	int flag = 0;
	Node* cur;
	for(cur=rankHead;cur;cur=cur->link){
		if(strcmp(cur->name,name)==0){
			printw("           %-20s    |  %-10d\n",cur->name,cur->score);
			flag = 1;
		}
	}
	if(flag==0)
		printw("               Search failure: no name in the list\n");
}

void rank(){
	char name[NAMELEN];
	Node *temp,*cur;
	int X=1,Y=2147483647,count=1,option=-1,input1,input2,ret1=0,ret2=0,rank;
	clear();
	attron(COLOR_PAIR(1));
	mvprintw(0, 0, "                            RANKIGN SYSTEM                               ");
	attroff(COLOR_PAIR(1));
	mvprintw(2, 22, "1. List ranks from X to Y\n");
	mvprintw(3, 22, "2. List ranks by a specific name\n");
	mvprintw(4, 22, "3. Delete a specific rank\n");
	wgetch(stdscr);
	option=wgetch(stdscr)-'0';
	if(option==1){
		echo();
		attron(COLOR_PAIR(1));
		mvprintw(6, 0, "                             Input Range                                 ");
		attroff(COLOR_PAIR(1));
		mvprintw(8, 22, "X: ");
		ret1=scanw("%d",&X);
		mvprintw(9, 22, "Y: ");
		ret2=scanw("%d",&Y);
		noecho();
		
		attron(COLOR_PAIR(1));
		mvprintw(11, 0, "                                Ranking                                  ");
		attroff(COLOR_PAIR(1));
		printw("\n-------------------------------------------------------------------------");
		printw("\n               NAME                |              SCORE   \n");
		printw("-------------------------------------------------------------------------\n");


		if(X>nodeNum || X<=0 || Y<=0 || X>Y)
			printw("               Search failure: no name in the list\n");
		else if(ret1==-1 && ret2==-1){
			for(cur=rankHead,count=1;cur;cur=cur->link,++count)
				printw("           %-20s    |  %-10d\n",cur->name,cur->score);
		}
		else if(ret1==-1){
			for(cur=rankHead,count=1;cur;cur=cur->link,++count){
				if(count<=Y)
					printw("           %-20s    |  %-10d\n",cur->name,cur->score);
			}

		}
		else if(ret2==-1){
			for(cur=rankHead,count=1;cur;cur=cur->link,++count){
				if(count>=X)
					printw("           %-20s    |  %-10d\n",cur->name,cur->score);
			}
		}
		else{
			for(cur=rankHead,count=1;cur;cur=cur->link,++count){
				if(count>=X && count<=Y)
					printw("           %-20s    |  %-10d\n",cur->name,cur->score);
				else
					if(count>Y || cur->link==NULL)
						break;
			}
		}
		printw("-------------------------------------------------------------------------\n");
		attron(COLOR_PAIR(1));
		printw("                      PRESS ANY KEY TO CONTINUE                          ");
		attroff(COLOR_PAIR(1));
		writeRankFile();
		wgetch(stdscr);
	}
	else if(option==2){
		attron(COLOR_PAIR(1));
		mvprintw(6, 0, "                             Input Name                                 ");
		attroff(COLOR_PAIR(1));
		mvprintw(8, 22, "Type the name: ");
		echo();
		getnstr(name,NAMELEN);


		attron(COLOR_PAIR(1));
		mvprintw(10, 0, "                                Ranking                                  ");
		attroff(COLOR_PAIR(1));
		
		printw("\n-------------------------------------------------------------------------");
		printw("\n               NAME                |              SCORE   \n");
		printw("-------------------------------------------------------------------------\n");
		noecho();
		nodeSearch(name);
		printw("-------------------------------------------------------------------------\n");
		attron(COLOR_PAIR(1));
		printw("                      PRESS ANY KEY TO CONTINUE                          ");
		attroff(COLOR_PAIR(1));
		wgetch(stdscr);
	}
	else if(option==3){
		echo();
		attron(COLOR_PAIR(1));
		mvprintw(6, 0, "                              Input Rank                                 ");
		attroff(COLOR_PAIR(1));
		mvprintw(8, 22, "Input the rank: ");
		scanw("%d",&rank);
		
		attron(COLOR_PAIR(1));
		mvprintw(10, 0, "                                                                         \n");
		attroff(COLOR_PAIR(1));
		noecho();
		if(rank<=0 || rank>nodeNum)
			printw("\n               Search failure: the rank not in the list\n\n");
		//	printw("\nSearch failure: the rank not in the list\n");
		else{
			for(cur=rankHead,count=1;cur;cur=cur->link,++count){
				if(rank==1){
					temp = rankHead;
					rankHead = rankHead->link;
					free(temp);
					break;
				}
				if(count+1==rank){
					temp = cur->link;
					cur->link = (cur->link)->link;
					free(temp);
					break;
				}
			}
			printw("\n                      Result: the rank deleted\n\n");
			--nodeNum;
			writeRankFile();
		}
		attron(COLOR_PAIR(1));
		printw("                      PRESS ANY KEY TO CONTINUE                          ");
		attroff(COLOR_PAIR(1));
		wgetch(stdscr);
	}
}
