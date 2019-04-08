#include <stdio.h>
#include <stdlib.h> //rand(), srand()함수를 사용하기 위해서 포함시키는 파일
#include <time.h> //time(NULL)을 사용하기 위해서 포함시키는 파일

int play_game(char id[10][9], char pw[10][9], int score[10]); //로그인을 완료한 후에 행맨게임을 실행하는 함수
void ranking(char id[10][9], int score[10]); //user의 정보를 읽어서 점수순으로 내림차순 정령해서 랭킬을 출력하는 함수
int str_len(char*); //parameter로 넘어온 string의 길이를 return해주는 함수
int str_cmp(char *, char*); //두 개의 string을 비교해서 같으면 0, 다르면 1을 return해주는 함수
void str_cpy(char *, char *); //첫 번째 parameter의 string을 두번째 parameter의 string으로 복사하는 함수

int main ()
{
  FILE* fop1 = fopen("user.txt","r"); //사용자의 정보(ID,PW,점수)가 저장되어 있는 파일을 열기 위한 FILE 포인터 변수
  FILE* fop3; //게임 후 사용자의 정보를 저장하기 위한 FILE 포인터 변수
  char id[10][9];  //10명의 사용자의 ID가 저장되어있는 2차원 배열
  char pw[10][9];  //10명의 사용자의 PW가 저장되어있는 2차원 배열
  char input_id[9]; //사용자가 입력하는 ID를 입력받는 변수
  char input_pw[9]; //사용자가 입력하는 PW를 입력받는 변수
  int select_menu; //사용자가 선택하는 메뉴를 입력받는 변수
  int numuser = 0; //사용자의 수
  int score[10]; //10명의 사용자의 점수가 저장되있는 1차원 배열
  int fcl1; //파일을 닫을 때 성공적으로 닫혔는지 확인하기 위해 사용하는 변수
  int fcl3; //파일을 닫을 때 성공적으로 닫혔는지 확인하기 위해 사용하는 변수
  int num; //for문 사용시 반복되는 횟수를 제한하기 위해 사용되는 변수
  int res; //fscanf로 파일의 내용을 읽어 올 때 파일의 끝인지 확인하기 위해 사용한 변수
  int GameResult; //play_game 함수가 정상적으로 종료되었는지 확인하기 위해 사용한 변수

  if(fop1 == NULL)  //파일이 성공적으로 열렸는지 확인하는 과정
  {
    printf("file open error!\n"); //만일 오류가 발생하면, error 메세지를 출력한다.
    return -1;
  }

  for(num=0;num<10;num++) //user.txt파일에 저장된 사용자의 id,pw,score를 변수에 저장하는 과정
  {
    res = fscanf(fop1,"%s %s %d",id[num],pw[num],&score[num]);
    numuser += 1;
    if(res == EOF)
    {
      numuser -= 1;
      break;
    }
  }

  while(1) //메뉴
  {
    printf("\n<Menu>\n");
    printf("1. Play game\n"); //1을 입력하면 play_game함수를 호출하여 행맨 게임이 실행된다.
    printf("2. Ranking\n");   //2를 입력하면 ranking함수가 호출되어 사용자들의 랭킹이 출력된다.
    printf("3. Exit\n");      //3을 입력하면 프로그램이 종료된다.
    printf("Select menu : "); //1~3까지 원하는 메뉴를 입력받는다.
    scanf("%d", &select_menu);

    if(select_menu == 1) //1을 입력하면 행맨 게임이 실행된다.
    {
      while(1)
      {     
        GameResult=play_game(id,pw,score); 
        if(GameResult == 0) //문제를 맞추어서 점수를 획득할 경우에는 user.txt에 사용자가 얻은 점수를 저장한다.
        { 
          fop3 = fopen("user.txt","w");
          for(num=0;num<numuser;num++)
            fprintf(fop3,"%s %s %d\n",id[num],pw[num],score[num]);
          fcl3 = fclose(fop3);
          if(fcl3 != 0)
          {
            printf("file close error!\n");
            return -1;
          }
          break;
        }
        if(GameResult == -1) //제대로 프로그램이 작동되지 않을 경우
          break;
      }
    }
    else if(select_menu == 2) //2를 입력할 경우에는 저장되어있는 사용자들의 랭킹이 출력된다.
      ranking(id,score);
    else if(select_menu == 3) //3을 입력할 경우에는 프로그램이 종료된다.
    {
      fcl1 = fclose(fop1); //파일을 닫을 때 성공적으로 닫혔는지 확인하는 과정
      if(fcl1 != 0)
      {
        printf("file close error!\n"); //만일 파일이 제대로 닫히지 않았으면, error 메세지를 출력한다.
        return -1;
      }
      return 0;
    }
    else  //1~3이외의 값을 입력할 경우에는 error 메시지를 출력한다.
      printf("Input error!\n");
  }

}
int play_game(char id[10][9], char pw[10][9], int score[10])
{
  FILE* fop1 = fopen("user.txt","r"); //사용자의 정보(ID,PW,점수)가 저장되어 있는 파일을 열기 위한 FILE 포인터 변수
  FILE* fop2 = fopen("word.txt","r"); //단어가 저장되어 있는 text파일을 열기 위한 FILE 포인터 변수
  char questword[3][16]; //사용자가 맞추어야 하는 영어 단어.
  char word[50][16]; //word.txt에 저장되어 있는 50개의 영어 단어가 저장되어있는 2차원 배열
  char info[50][16]; //word.txt에 저장되어 있는 50개의 영어 단어에 대한 정보가 저장되어있는 2차원 배열
  char input_id[9]; //사용자가 입력하는 ID를 입력받는 변수
  char input_pw[9]; //사용자가 입력하는 PW를 입력받는 변수
  char input; //행맨 게임에서 사용자가 입력하는 단어를 저장하는 변수
  char enter; //입력버퍼에 남아있는 엔터값을 제거하기 위해 사용하는 변수
  char alphabet[2][26]; //사용자가 같은 단어를 반복입력하는 것을 막기 위해 존재하는 변수
  int usernumber; //사용자가 단어장에서 몇 번 째에 저장되었는지 
  int charhintnum; //Character hint를 사용했을 때 몇 번째 index를 확인할 지 입력받는 변수
  int questnumber[50];  //출제되는 문제의 번호  
  int templife; //처음 life의 수와 문제를 맞출 때 까지의 life를 비교하기 위해 사용하는 변수
  int charhint = 1; //character hint를 사용가능한 횟수
  int numuser = 0; //사용자의 수
  int numword = 0; //단어의 수
  int countword; //맞춰야 하는 단어의 개수
  int wordpass = 1; //wordpass를 사용가능한 횟수
  int idcheck = 0; //id를 올바르게 입력했는지 확인하는 변수
  int reveal = 0; //사용자가 단어를 입력했을 때 드러나는 단어의 개수
  int repeatcheck[50] = {0}; //난수를 생성하는 과정에서 숫자가 반복되는지 확인하는 변수
  int life = 10; //사용자에게 주어진 기회
  int temp; //난수를 발생시키기 위해서 사용하는 임시 변수
  int getscore = 0; //사용자가 게임을 통해서 얻은 점수
  int result = 1; //사용자가 문제를 맞추었는지 확인하는 변수
  int fcl1; //파일을 닫을 때 성공적으로 닫혔는지 확인하기 위해 사용하는 변수
  int fcl2; //파일을 닫을 때 성공적으로 닫혔는지 확인하기 위해 사용하는 변수
  int num; //for문 사용시 반복되는 횟수를 제한하기 위해 사용되는 변수
  int num2 = 0; //questnumber배열을 사용하기 위해서 사용하는 변수
  int res;  //fscanf로 파일의 내용을 읽어 올 때 파일의 끝인지 확인하기 위해 사용한 변수

  if(fop1 == NULL || fop2 == NULL) //파일이 성공적으로 열렸는지 확인하는 과정
  {
    printf("file open error!\n"); //만일 오류가 발생하면, error메세지를 출력한다.
    return -1;
  }

  for(num=0;num<10;num++) //user.txt파일에 저장된 사용자의 id,pw,score를 변수에 저장하는 과정
  {
    res = fscanf(fop1,"%s %s %d",id[num],pw[num],&score[num]);
    numuser += 1;
    if(res == EOF)
    {
      numuser -= 1;
      break;
    }
  }

  for(num=0;num<50;num++) //word.txt파일에 저장된 단어와 단어의 정보를 변수에 저장하는 과정
  {
    res = fscanf(fop2,"%s %s",word[num],info[num]);
    numword += 1; //단어의 개수를 세는 과정
    if(res == EOF)
    {
      numword -= 1;
      break;
    }
  }

  srand(time(NULL)); //time(NULL)을 사용하여 seed의 값을 변화시켜 항상 다른 난수를 발생시킨다.

  for(num=0;num<numword;) //난수를 생성하는 과정
  {
    temp = rand() % numword;
    if(repeatcheck[temp] == 0)
    {
      repeatcheck[temp] = 1;
      questnumber[num] = temp + 1;
      num++;
    }
  }

  countword = numword; //맞추어야 하는 단어의 개수를 정하는 과정

  while(1) //로그인
  {
    printf("\n<Login>\n");
    printf("ID : ");
    scanf("%s", input_id);
    printf("PW : ");
    scanf("%s%c", input_pw,&enter);//버퍼에 있는 엔터값을 제거하기 위해서 %c를 사용하였다.

    for(num=0;num<numuser;num++)
    {
      if(str_cmp(input_id,id[num]) == 0) //입력한 ID가 존재하는지 확인하는 과정
        idcheck = 1;
      if(str_cmp(input_id,id[num]) == 0 && str_cmp(input_pw,pw[num]) == 0 ) //입력한 ID에 대응하는 PW와 입력한 PW가 일치할 시에는 로그인이 완료된다.
      {
        usernumber = num;
        printf("Login complete\n\n");
        break;
      }
    }
    if(str_cmp(input_id,id[num]) == 0 && str_cmp(input_pw,pw[num]) == 0 )
      break;
    if(idcheck == 0)
    {
      printf("there is no ID<%s>\n",input_id); //사용자가 입력하는 ID가 존재하지 않을 경우 출력하는 error 메시지 출력 후 종료
      fcl1 = fclose(fop1);  //파일이 올바르게 닫혔는지 확인하는 과정
      fcl2 = fclose(fop2);
      if(fcl1 != 0 || fcl2 != 0)
      {
        printf("file close error!\n"); //만일 파일이 올바르게 닫히지 않으면, error 메시지를 출력한다.
        return -1;
      }
      return 0;
    }
    else
    {
      printf("PW is not correct!\n"); //사용자가 입력하는 PW가 ID에 대응하는 PW와 일치하지 않을 경우 출력하는 error 메시지 출력 후 종료
      fcl1 = fclose(fop1);  //파일이 올바르게 닫혔는지 확인하는 과정
      fcl2 = fclose(fop2);
      if(fcl1 != 0 || fcl2 != 0)
      {
        printf("file close error!\n"); //만일 파일이 올바르게 닫히지 않으면, error 메시지를 출력한다.
        return -1;
      }
      return 0;
    }
  }

  for(num=0;num<26;num++) //사용자가 같은 단어를 반복입력하는 것을 막기 위한 과정
  {
    alphabet[0][num] = 'a' + num;
    alphabet[1][num] = 0;
  }

  templife = life; //처음 life의 수와 문제를 맞출 때 까지의 life를 비교하기 위해 templife에 처음 life를 저장하는 과정
  str_cpy(word[questnumber[num2]-1],questword[0]); //questword[0]에는 출제될 문제의 단어를 저장한다.

  for(num=0;num<str_len(questword[0]);num++)
  {
    questword[1][num] = '_'; //questword[1]에는 '_'를 저장한다.
    questword[2][num] = 0; //questword[2]에는 사용자가 이 단어를 맞추었을 경우에는 1을, 맞추지 못했을 경우에는 0을 대입한다.
  }

  while(1) //행맨 게임
  {
    printf("Life : %d\n",life); //사용자에게 주어진 기회
    printf("Word : "); //사용자에게 주어진 단어
    for(num=0;num<str_len(questword[0]);num++)
    {
      if(questword[2][num] == 0) //사용자가 맞춘 단어는 표시하고 맞추지 못한 단어는 _로 표시한다.
        printf("%c ", questword[1][num]);
      else
        printf("%c ", questword[0][num]);
    }
    printf("\n");
    printf("Category : %s\n", info[questnumber[num2]-1]); //사용자에게 주어지는 단어에 대한 정보
    printf("1. Character hint(count : %d) 2. Word pass(count : %d)\n", charhint,wordpass); //사용가능한 Item의 횟수
    printf("Input alphabet or item number : "); //26개의 글자 중에서 하나를 입력하는 과정
    scanf("%c%c", &input,&enter); //버퍼에 남아있는 엔터를 제거하기 위해서 %c%c를 사용하였다.

    if(input>=97 && input<=122) //사용자가 정상적으로 입력했을 경우에 진행하는 과정
    {
      for(num=0;num<26;num++) //사용자가 같은 단어를 반복입력하는 것을 막기 위한 과정
      {
        if(alphabet[0][num] == input)
          break;
      }
      if(alphabet[1][num] == 1)
      {
        printf("You already type it!\n");
        continue;
      }
      for(num=0;num<str_len(questword[0]);num++)
      {
        if(input == questword[0][num]) //만일 사용자가 입력한 단어가 word에 존재하는 경우에는 그 단어를 드러낸다.
        {
          questword[2][num] = 1;
          reveal += 1;
        }
      }

      if(reveal == 0) //사용자가 word에 존재하지 않는 영어 단어를 입력했을 때는 life가 하나씩 줄어들고, 0이 되면 gameover가 된다.
      {
        life -= 1;
        if(life == 0)
        {
          printf("Your current score is %d\n", score[usernumber]);
          fcl1 = fclose(fop1);  //파일이 올바르게 닫혔는지 확인하는 과정
          fcl2 = fclose(fop2);
          if(fcl1 != 0 || fcl2 != 0)
          {
            printf("file close error!\n"); //만일 파일이 올바르게 닫히지 않으면, error 메시지를 출력한다.
            return -1;
          }
          return 0; //사용자가 문제를 맞추지 못했을 경우에는 0을 return한다.
        }
      }
      reveal = 0;

      for(num=0;num<26;num++)
      {
        if(alphabet[0][num] == input)
          break;
      }
      alphabet[1][num] = 1;

      for(num=0;num<str_len(questword[0]);num++) //사용자가 문제를 맞추었는지 확인하는 과정
        result *= questword[2][num];
      if(result == 1) //만일 사용자가 문제를 맞추었을 경우에 진행하는 과정
      {
        if(life == templife) //만일 사용자가 한 단어를 맞추는 동안 한 글자도 틀리지 않을 경우 사용자가 얻게되는 점수
          getscore = str_len(questword[0]) * 2 + life;
        else //사용자가 한 단어를 맞추는 동안에 몇 번 틀렸을 경우
          getscore = str_len(questword[0]) + life;
        printf("Correct! The word is %s\n", questword[0]);
        printf("The score that you get is %d\n", getscore);
        printf("Your current score is %d\n", score[usernumber] + getscore);
        score[usernumber] += getscore;
        num2 += 1;
        countword -= 1;
        if(countword == 0)
        {
          fcl1 = fclose(fop1);  //파일이 올바르게 닫혔는지 확인하는 과정
          fcl2 = fclose(fop2);
          if(fcl1 != 0 || fcl2 != 0)
          {
            printf("file close error!\n"); //만일 파일이 올바르게 닫히지 않으면, error 메시지를 출력한다.
            return -1;
          }
          return 0;  
        }
        templife = life; //처음 life의 수와 문제를 맞출 때 까지의 life를 비교하기 위해 templife에 처음 life를 저장하는 과정
        str_cpy(word[questnumber[num2]-1],questword[0]); //questword[0]에는 출제될 문제의 단어를 저장한다.
        charhint = 1;

        for(num=0;num<str_len(questword[0]);num++)
        {
          questword[1][num] = '_'; //questword[1]에는 '_'를 저장한다.
          questword[2][num] = 0; //questword[2]에는 사용자가 이 단어를 맞추었을 경우에는 1을, 맞추지 못했을 경우에는 0을 대입한다.
        }
        for(num=0;num<26;num++)
          alphabet[1][num] = 0;
      }
      result = 1;
    }
    else if(input == '1') //사용자가 1을 입력하여 Character hint를 사용한 경우
    {
      if(charhint == 0) //Character hint는 각 단어 당 1회 사용 가능하며, 이미 사용한 경우에는 error 메세지 출력
      {
        printf("You can use one character hint per word!\n");
        continue;
      }
      while(1)
      {
        printf("Select word column to see (1 ~ %d) : ",str_len(questword[0])); //사용자가 알고 싶어하는 빈칸을 입력하는 과정
        scanf("%d%c", &charhintnum,&enter);//버퍼에 남아있는 엔터를 제거하기 위해 %c를 사용하였다.
        if(questword[2][charhintnum-1] == 1) //이미 알고있는 단어에 대해서는 사용이 불가능하다.
        {
          printf("You already know it!\n");
          continue;
        }
        if(charhintnum < 1 || charhintnum > str_len(questword[0])) //만일 주어진 범위 외의 값을 입력했을 경우
          printf("You input wrong range of number!\n");
        else //정상적으로 입력했을 경우
          break;
      }
      printf("Alphabet which you select is %c\n", questword[0][charhintnum-1]);
      questword[2][charhintnum-1] = 1;
      for(num=0;num<str_len(questword[0]);num++) //아이템 사용 이후 단어를 모두 맞추었는지 확인하는 과정
        result *= questword[2][num];
      if(result == 1) //Character hint를 사용하여 한 단어를 맞추었을 경우
      {
        if(life == 10)
          getscore = str_len(questword[0]) * 2 + life;
        else
          getscore = str_len(questword[0]) + life;
        printf("Correct! The word is %s\n", questword[0]);
        printf("The score that you get is %d\n", getscore);
        printf("Your current score is %d\n", score[usernumber] + getscore);
        score[usernumber] += getscore;
        num2++;
        countword--;
        if(countword == 0) //Character hint를 사용하여 게임을 끝냈을 경우
        {
          fcl1 = fclose(fop1);  //파일이 올바르게 닫혔는지 확인하는 과정
          fcl2 = fclose(fop2);
          if(fcl1 != 0 || fcl2 != 0)
          {
            printf("file close error!\n"); //만일 파일이 올바르게 닫히지 않으면, error 메시지를 출력한다.
            return -1;
          }
          return 0;
        }
        templife = life; //처음 life의 수와 문제를 맞출 때 까지의 life를 비교하기 위해 templife에 처음 life를 저장하는 과정
        str_cpy(word[questnumber[num2]-1],questword[0]); //questword[0]에는 출제될 문제의 단어를 저장한다.

        for(num=0;num<str_len(questword[0]);num++)
        {
          questword[1][num] = '_'; //questword[1]에는 '_'를 저장한다.
          questword[2][num] = 0; //questword[2]에는 사용자가 이 단어를 맞추었을 경우에는 1을, 맞추지 못했을 경우에는 0을 대입한다.
        }
        result = 1;
        charhint = 1;
        for(num=0;num<26;num++)
          alphabet[1][num] == 0;
        continue;
      }
      result = 1;
      charhint = 0;
    }
    else if(input == '2') //사용자가 2를 입력하여 wordpass를 사용한 경우
    {
      if(wordpass == 0) //사용자가 이미 wordpass를 사용한 경우 error 메세지를 출력한다.
      {
        printf("You can only use word pass once!\n");
        continue;
      }
      printf("You use word pass!!\n");

      num2++;
      if(num2 == numword)//만약 wordpass를 사용하여 게임을 끝냈을 경우
      {
        printf("Correct! The word is %s\n", questword[0]);
        printf("The score that you get is 0\n");
        printf("Your current score is %d\n", score[usernumber]);
        fcl1 = fclose(fop1);  //파일이 올바르게 닫혔는지 확인하는 과정
        fcl2 = fclose(fop2);
        if(fcl1 != 0 || fcl2 != 0)
        {
          printf("file close error!\n"); //만일 파일이 올바르게 닫히지 않으면, error 메시지를 출력한다.
          return -1;
        }
        return 0;
      }
      templife = life; //처음 life의 수와 문제를 맞출 때 까지의 life를 비교하기 위해 templife에 처음 life를 저장하는 과정
      str_cpy(word[questnumber[num2]-1],questword[0]); //questword[0]에는 출제될 문제의 단어를 저장한다.

      for(num=0;num<str_len(questword[0]);num++)
      {
        questword[1][num] = '_'; //questword[1]에는 '_'를 저장한다.
        questword[2][num] = 0; //questword[2]에는 사용자가 이 단어를 맞추었을 경우에는 1을, 맞추지 못했을 경우에는 0을 대입한다.
      }
      for(num=0;num<26;num++)
        alphabet[1][num] = 0;
      charhint = 1; //wordpass를 사용한 다음에는 Character hint를 다시 사용할 수 있다.
      wordpass = 0;
      countword -= 1;
    }
    else
      printf("You type wrong alphabet or item number!\n");
  }

}

void ranking(char id[10][9], int score[10])
{
  FILE* fop1 = fopen("user.txt","r"); //사용자의 정보(ID,PW,점수)가 저장되어 있는 파일을 열기 위한 FILE 포인터 변수
  char temppw[10][9]; //사용자의 수를 세기 위해 임시로 pw를 읽는 임시 변수
  char tempid[10][9]; //랭킹 보기에서 사용자의 ID가 저장되어 있는 배열의 내용을 바꾸지 않기 위해서 따로 ID를 저장하는 배열
  char tempid2[9]; //랭킹 보기에서 사용자의 PW가 저장되어 있는 배열의 내용을 바꾸지 않기 위해서 따로 PW를 저장하는 배열
  int rank; //사용자의 순위
  int tempscore[2][10]; //랭킹 보기에서 사용자의 점수가 저장되어 있는 배열의 내용을 바꾸지 않기 위해서 따로 점수를 저장하는 배열
  int temp; //사용자의 점수를 swap 할 때 필요로 하는 임시 변수
  int numuser = 0; //사용자의 수
  int i; //for문 사용시 반복되는 횟수를 제한하기 위해 사용되는 변수
  int j; //for문 사용시 반복되는 횟수를 제한하기 위해 사용되는 변수
  int num = 1; //for문 사용시 반복되는 횟수를 제한하기 위해 사용되는 변수
  int res; //fscanf로 파일의 내용을 읽어 올 때 파일의 끝인지 확인하기 위해 사용한 변수
  int fcl1; //파일을 닫을 때 성공적으로 닫혔는지 확인하기 위해 사용하는 변수

  for(num=0;num<10;num++) //사용자의 ID, PW, 점수에 관한 배열의 내용을 바꾸지 않기 위해서 따로 저장하는 과정
  {
    res = fscanf(fop1,"%s %s %d",tempid[num],temppw[num],&tempscore[0][num]);
    numuser += 1;
    tempscore[1][num] = num;
    if(res == EOF) 
    {
      numuser -= 1;
      break;
    }
  }

  num = 1;

  for(i=0;i<numuser-1;i++) //점수를 비교하여 점수순으로 내림차순 정렬하는 과정
  {
    for(j=num;j<numuser;j++)
    {
      if(tempscore[0][i] < tempscore[0][j])
      {
        temp = tempscore[0][j];
        tempscore[0][j] = tempscore[0][i];
        tempscore[0][i] = temp;
        temp = tempscore[1][j];
        tempscore[1][j] = tempscore[1][i];
        tempscore[1][i] = temp;
        str_cpy(tempid[j],tempid2);
        str_cpy(tempid[i],tempid[j]);
        str_cpy(tempid2,tempid[i]);
      }
    }
    num += 1;
  }

  num = 1;

  for(i=0;i<numuser-1;i++) //동점자들은 메모장에 나온 순서대로 정렬한다.
  {
    for(j=num;j<numuser;j++)
    {
      if(tempscore[0][i] == tempscore[0][j] && tempscore[1][i] > tempscore[1][j])
      {
        temp = tempscore[1][j];
        tempscore[1][j] = tempscore[1][i];
        tempscore[1][i] = temp;
        str_cpy(tempid[j],tempid2);
        str_cpy(tempid[i],tempid[j]);
        str_cpy(tempid2,tempid[i]);
      }
    }
    num += 1;
  }

  printf(" Rank    User ID      Score\n");
  for(rank=0;rank<numuser;rank++) //랭킹을 출력하는 과정
    printf("%5d%11s%11d\n",rank+1,tempid[rank],tempscore[0][rank]);

  fcl1 = fclose(fop1);
  if(fcl1 != 0)
  {
    printf("file close error!\n"); //만일 파일이 제대로 닫히지 않았으면, error 메세지를 출력한다.
    return;
  }
}

int str_len(char string[])
{
  int sl = 0; //parameter로 넘어온 string의 길이
  int num = 0; //while문 사용시 모든 단어를 확인하기 위해 사용하는 변수
  while(1)
  {
    if(string[num] == '\0') //string의 길이를 측정하는 과정
      break;
    sl++;
    num++;
  }
  return sl;
}

int str_cmp(char input[], char data[])
{
  int num = 0; //while문 사용시 모든 단어를 확인하기 위해 사용하는 변수
  while(1)
  {
    if(input[num] != data[num]) //두 개의 string이 다르면 1을 return 한다.
      return 1;
    else
    {
      if(input[num] == '\0' && input[num] == '\0') //두 개의 string이 같으면 0을 return 한다.
        return 0;
    }
    num++;
  }
}

void str_cpy(char x[], char y[])
{
  int num = 0; //while문 사용시 모든 단어를 확인하기 위해 사용하는 변수
  while(1) //첫 번째 parameter의 string을 두 번째 parameter의 string으로 복사하는 과정
  {
    y[num] = x[num];
    if(x[num] == '\0')
      break;
    num++;
  }
}
