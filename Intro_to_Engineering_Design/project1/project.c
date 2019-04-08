#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int play_game(char id[10][9], char pw[10][9], int score[10]);
void ranking(char id[10][9], int score[10]);
int str_len(char*);
int str_cmp(char *, char*);
void str_cpy(char *, char *);

int main ()
{
  FILE* fop1 = fopen("userinfo.text","r+");
  FILE* fop2;
  char id[10][9];
  char pw[10][9];
  char input_id[9];
  char input_pw[9];
  char word[50][16];
  char info[50][16];
  int select_menu;
  int score[10];
  int fcl1;
  int fcl2;
  int num;
  int res;
  int GameResult;
  int n; 
  int life = 10;

  for(num=0;num<10;num++)
  {
    res = fscanf(fop1,"%s %s %d",id[num],pw[num],score[num]);
    if(res == EOF) break;
  }

  if(fop1 == NULL)
  {
    printf("file open error!\n");
    return 1;
  }

  while(1)
  {
    printef("<Menu>\n");
    printf("1. Play game\n");
    printf("2. Ranking\n");
    printf("3. Exit\n");
    printf("Select menu : \n");
    scanf("%d", &select_menu);

    if(select_menu == 1)
    {
      printf("<Login>\n");
      printf("ID : ");
      scanf("%s", input_id);
      printf("PW : ");
      scanf("%s", input_pw);
      if(str_cmp(input_id,id) == 0 && str_cmp(input_pw,pw) == 0)
      {
        printf("Login complete\n");
        fop2 = fopen("wordinfo.text","r");
        if(fop2 == NULL)
        {
          printf("file open error!\n");
          return 1;
        }

        for(num=0;num<50;num++)
        {
          res = fscanf(fop2,"%s %s",word[num],info[num]);
          if(res == EOF) break;
        }



        while(1)
        {
          printf("Life : %d\n",life);
          for(num=0;num<str_len(word[]);
          printf("_");


        GameResult=play_game(id,pw,score);
        if(GameResult == 0)
          continue;
        if(GameResult == -1)
          GameResult=play_game(id,pw,score);
      }
      else
      {
        if(str_cmp(input_id,id) == 1)
          printf("there is no ID<%s>\n",input_id);
        if(str_cmp(input_pw,pw) == 1)
          printf("PW is not correct!\n");
        return 0;
      }
    else if(select_menu == 2)
      ranking(id,score);
    else if(select_menu == 3)
      return 0;
    else
      printf("Input error!\n");
  }

  fcl1 = fclose(fop1);
  fcl2 = fclose(fop2);
  if(fcl1 != 0 || fcl2 != 0)
  {
    printf("file close error!\n");
    return 1;
  }

  return 0;
}
int play_game(char id[10][9], char pw[10][9], int score[10])
{
  FILE* fop1 = fopen("userinfo.txt","w");
  FILE* fop2 = fopen("wordinfo.txt","r");
  int fcl1;
  int fcl2;
  if(fop1 == NULL || fop2 == NULL)
  {
    printf("file open error!\n");
    return -1;
  }





  fcl1 = fclose(fop1);
  fcl2 = flcose(fop2);
  if(fcl1 != 0 || fcl2 != 0)
  {
    printf("file close error!\n");
    return -1;
  }
}

void ranking(char id[10][9], int score[10])
{
  char tempid[10][9];
  char tempid2[9];
  int rank;
  int tempscore[10];
  int temp;
  int i;
  int j;
  int num = 10;

  str_cpy(id,tempid);
  str_cpy(score,tempscore);

  for(i=0;i<9;i++)
  {
    for(j=1;j<num;j++)
    {
      if(tempscore[i] < tempscore[j])
      {
        temp = tempscore[j];
        tempscore[j] = tempscore[i];
        tempscore[i] = temp;
        str_cpy(tempid[j],tempid2);
        str_cpy(tempid[i],tempid[j]);
        str_cpy(tempid2,tempid[i]);
      }
    }
  }
  printf(" Rank    User ID    Score\n");
  for(rank=0;rank<10;rank++)
    printf("%d%10c%10d\n",rank+1,tempid[rank],tempscore[rank]);
}

int str_len(char string[])
{
  int sl = 0;
  int num = 0;
  while(1)
  {
    if(string[num] == '\0')
      break;
    sl++;
    num++;
  }
  return sl;
}

int str_cmp(char input[], char data[])
{
  int num = 0;
  while(1)
  {
    if(input[num] != data[num])
      return 1;
    else
    {
      if(input[num] == '\0' && input[num] == '\0')
        return 0;
    }
    num++;
  }
}

void str_cpy(char x[], char y[])
{
  while(1)
  {
    y[num] = x[num];
    if(x[num] == '\0')
      break;
    num++;
  }
}
