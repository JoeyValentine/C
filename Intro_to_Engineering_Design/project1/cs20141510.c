#include <stdio.h>
#include <math.h>

void taylor_sin(double, int, double *); //Taylor series를 이용해 sine값을 구하는 함수
void taylor_cos(double, int, double *); //Taylor series를 이용해 cosine값을 구하는 함수
void taylor_tan(double, int, double *); //Taylor series를 이용해 tangent값을 구하는 함수
int factorial(int); //1부터 어떤 양의 정수 n까지의 정수를 모두 곱한 것을 구하는 함수
double angle_to_radian(double); //입력한 60분법 형태의 각도를 라디안으로 변환하는 함수
void compute_error_rate(double, double, double, double); //Math library를 이용한 삼각함수의 결과값과 Taylor series를 이용해 구현한 삼각함수의 결과값의 오차율을 구하여, 각각의 오차율을 출력하는 함수

int main ()
{
  double angle;   //각의 크기 (60분법)
  double ModifiedAngle; //입력받은 각의 정수부분을 360으로 나누었을 때 생긴 나머지와 입력받은 각의 소수부분을 더한값 (60분법)
  double radian;  //각의 크기 (호도법)
  double sine;    //Taylor series를 이용해 구한 sine의 값
  double cosine;  //Taylor series를 이용해 구한 cosine의 값
  double tangent; //Taylor series를 이용해 구한 tangent의 값
  int term;       //항의 개수

  printf("Input angle : "); 
  scanf("%lf", &angle);
  printf("Input the number of terms (3~5) : "); //이때, 3이상 5이하의 정수만을 입력해야 한다.
  scanf("%d", &term);

  if( term>=6 || term<=2) //3, 4, 5 이외의 정수를 입력하는 경우, 에러 메시지를 출력하고 main함수가 종료된다.
  {
    printf("Error!\n");
    return 0;
  }

  if( (int)angle >= 360 || (int)angle <= -360 ) /*angle의 크기가 360이상이거나 -360이하일 경우,
                                                  angle의 정수부분을 360으로 나눈 나머지와 angle의 소수부분을 더하여 생성된 값을 ModifiedAngle에 대입한다. 
                                                  그다음 60분법형태의 ModifiedAngle을 라디안으로 변환한다. */
  {
      ModifiedAngle = (int)angle%360 + (angle - (int)angle);
      radian = angle_to_radian(ModifiedAngle);
  }
  else //angle의 크기가 -360초과 360미만일 경우, 입력한 60분법형태의 각도를 라디안으로 변환한다.
  {
    radian = angle_to_radian(angle);
  }

  printf("\n<Sin, Cos, Tan function using math library>\n"); //Math library를 이용하여 구한 sine, cosine, tangent의 값을 아래에 출력한다.
  //이때 tan(angle)의 값이 infinite인지 아닌지에 따라서 출력하는 방식을 달리한다.

  if( angle == (int)angle && (int)fabs((int)angle%180) == 90) //tan(angle)의 값이 infinite인 경우 출력하는 방식
  {
    printf("Sin(%.2lf) : %25.15lf\n", angle, sin(radian) ); 
    printf("Cos(%.2lf) : %25.15lf\n", angle, cos(radian) );
    printf("Tan(%.2lf) :         Infinite\n", angle);
  }
  else //tan(angle)의 값이 infinite가 아닌  경우 출력하는 방식
  {
    printf("Sin(%.2lf) : %25.15lf\n", angle, sin(radian) );
    printf("Cos(%.2lf) : %25.15lf\n", angle, cos(radian) );
    printf("Tan(%.2lf) : %25.15lf\n", angle, tan(radian) );
  }

  taylor_sin(radian, term, &sine);
  taylor_cos(radian, term, &cosine);
  taylor_tan(radian, term, &tangent);

  printf("\n<Sin, Cos, Tan function using taylor series>\n"); //Taylor series를 이용하여 구한 sine, cosine, tangent의 값을 아래에 출력한다.
  printf("Sin(%.2lf) : %25.15lf\n", angle, sine);
  printf("Cos(%.2lf) : %25.15lf\n", angle, cosine);
  printf("Tan(%.2lf) : %25.15lf\n", angle, tangent);

  compute_error_rate(angle, sine, cosine, tangent); //함수를 이용하여 sine, cosine, tangent의 오차율을 구한 후, 각각의 오차율을 출력한다.

  return 0;
}

void taylor_sin(double radian, int term, double *sine) //Taylor series를 이용하여 sine의 값을 구하는 함수 
  //이때 항의 값에 따라서 경우를 나누어 sine의 값을 구한다.
{ 
  if(term==3)
  {
    *sine = pow(radian, 1) / factorial(1) - pow(radian, 3) / factorial(3) + pow(radian, 5) / factorial(5); 
  }
  else if(term==4)
  {
    *sine = pow(radian, 1) / factorial(1) - pow(radian, 3) / factorial(3) + pow(radian, 5) / factorial(5) - pow(radian, 7) / factorial(7);
  }
  else
  {
    *sine = pow(radian, 1) / factorial(1) - pow(radian, 3) / factorial(3) + pow(radian, 5) / factorial(5) - pow(radian, 7) / factorial(7) + pow(radian, 9) / factorial(9);
  }
  return;
}

void taylor_cos(double radian, int term, double *cosine) //Taylor series를 이용하여 cosine의 값을 구하는 함수
  //이때 항의 값에 따라서 경우를 나누어 cosine의 값을 구한다.
{
  if(term==3)
  {
    *cosine = pow(radian, 0) / factorial(0) - pow(radian, 2) / factorial(2) + pow(radian, 4) / factorial(4);
  }
  else if(term==4)
  {
    *cosine = pow(radian, 0) / factorial(0) - pow(radian, 2) / factorial(2) + pow(radian, 4) / factorial(4) - pow(radian, 6) / factorial(6);
  }
  else
  {
    *cosine = pow(radian, 0) / factorial(0) - pow(radian, 2) / factorial(2) + pow(radian, 4) / factorial(4) - pow(radian, 6) / factorial(6) + pow(radian, 8) / factorial(8);
  }
  return;
}

void taylor_tan(double radian, int term, double *tangent) //Taylor series를 이용하여 tangent의 값을 구하는 함수
  //위에서 구한 sine의 값과 cosine의 값을 나누어 tangent의 값을 구한다.
{
  double sine;
  double cosine;

  taylor_sin(radian, term, &sine);
  taylor_cos(radian, term, &cosine);
  *tangent = sine / cosine;

  return;
}

int factorial(int n) //1부터 어떤 양의 정수n까지의 정수를 모두 곱한 것을 구하는 함수
  //항의 값이 3이상 5이하로 정해져 있으므로, 1에서 9까지의 계승만을 생각하면 된다.(이때 else는 n==9인 경우를 의미한다.)
{
  if(n==0)
    return 1;
  else if(n==1)
    return 1;
  else if(n==2)
    return 1*2;
  else if(n==3)
    return 1*2*3;
  else if(n==4)
    return 1*2*3*4;
  else if(n==5)
    return 1*2*3*4*5;
  else if(n==6)
    return 1*2*3*4*5*6;
  else if(n==7)
    return 1*2*3*4*5*6*7;
  else if(n==8)
    return 1*2*3*4*5*6*7*8;
  else
    return 1*2*3*4*5*6*7*8*9;
}

double angle_to_radian(double angle) //입력한 60분법 형태의 각을 라디안으로 변환하는 함수
{
  double radian;

  radian = (M_PI/180) * angle; //변환된 60분법 형태의 angle을 라디안으로 변환시킨다.

  return radian;
}

void compute_error_rate(double angle, double sine, double cosine, double tangent) //Math library를 이용한 삼각함수의 결과값과 Taylor series를 이용해 구현한 삼각함수의 결과값의 오차율을 구하여 각각의 오차율을 출력하는 함수
{
  double radian;
  double ErrorRateSine;
  double ErrorRateCosine;
  double ErrorRateTangent;

  radian = angle_to_radian(angle);

  //Math library에서 구한 삼각함수 결과값이 0이거나 infinite인 경우에 따라서 출력하는 방식을 달리한다.
  if( angle == (int)angle && (int)fabs((int)angle%180) == 90 ) //cosine의 값이 0이고 tangent의 값이 infinite인 경우의 출력방식
  {
    ErrorRateSine = fabs( sin(radian) - sine ) / fabs( sin(radian) ) * 100;
    printf("\nThe error rate of Sin : %25.13lf\n", ErrorRateSine);
    printf("The error rate of Cos :           Infinite\n");
    printf("The error rate of Tan :           Infinite\n");
  }
  else if( angle == (int)angle && (int)fabs((int)angle%180) == 0 ) //sine의 값이 0이고 tangent의 값이 0인 경우의 출력방식
  {
    ErrorRateCosine = fabs( cos(radian) - cosine ) / fabs( cos(radian) ) * 100;
    printf("\nThe error rate of Sin :           Infinite\n");
    printf("The error rate of Cos : %25.13lf\n", ErrorRateCosine);
    printf("The error rate of Tan :           Infinite\n");
  }
  else //모든 삼각함수의 값이 0도 아니고 infinite도 아닌 경우의 출력방식
  {
    ErrorRateSine = fabs( sin(radian) - sine ) / fabs( sin(radian) )  * 100;
    ErrorRateCosine = fabs( cos(radian) - cosine ) / fabs( cos(radian) )  * 100;
    ErrorRateTangent = fabs( tan(radian) - tangent ) / fabs( tan(radian) ) * 100;
    printf("\nThe error rate of Sin : %25.13lf\n", ErrorRateSine);
    printf("The error rate of Cos : %25.13lf\n", ErrorRateCosine);
    printf("The error rate of Tan : %25.13lf\n", ErrorRateTangent);
  }

  return;
}
