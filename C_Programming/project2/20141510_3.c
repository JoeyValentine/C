#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum cardType {credit=0,charge=1}; //Card type can be diveded into credit card and transportation card(charge)

typedef struct{ 
	int userId;
	char name[50];
	int charge;
	enum cardType type;
	char age[10];
}CUSTOMER; //customer's information

typedef struct{
	int tsID;
	int station;
	char stationName[100];
	double distance;
}TRANSPORTATION; //transformation information

typedef struct{
	int userId;
	int recharge;
}USERINPUT; //what program user types will be saved by this structure

typedef struct{
	int chargeOrNot;
	int userId;
	int beforeBalance;
	int afterBalance;
}CHARGEOUTPUT; //result from charge

typedef struct{
	char transportation[10];
	int userId;
	char getOnOffTime[20];
	int stationId;
	enum cardType type;
	char age[10];
	int charge;
}READER_OUTPUT; //data from reader_output.txt

typedef struct{
	int userId;
	int charge;
}B604DB; //DB of b604

typedef struct{
	int userId;
	int charge;
}G5714DB; //DB of g5714

typedef struct{
	int userId;
	int charge;
}T10DB; //DB of t10

typedef struct{
	int userId;
	char name[50];
	int charge;
}CREDITOUTPUT; //result from credit initialization

int main (){

	FILE *cusFile,*line3File,*b604FIle,*g5714File,*t10File,*reader_outputFp; //FILE pointers were used to open files
	int state; //It was used to check whether a file closed properly
	int i,j=0,l=0,a=0,b=0,c=0; //They were used to compute for loops
	int len; //string's length
	int count; //It the number of how many times user types input
	int flag = 0; //which was used to control a program's direction
	int NumOfCustomer; //the number of customer
	int NumOfLine3; //the number of line3
	int NumOfB604; //the number of b604
	int NumOfG5714; //the numbe of g5714
	int NumOfT10; //the number of t10
	int NumOfReader_output; //the number of reader_output.txt
	int NumOfB604User=0; //the number of b604 user
	int NumOfG5714User=0; //the number of g5714 user
	int NumOfT10User=0; //the number of t10 user
	char enter; //it was used to remove enter
	char firstInput[100]; //what user types was stored there
	char cardTypeTemp[7]; //It was used to distinguish between credit card and transportation card
	char tempTransportation[10]; //it was used to store transportion's name
	int NumOfCreditCard=0; //the number of credit card user

	//structure variable
	CUSTOMER *cusInfo; 
	TRANSPORTATION *line3,*b604,*g5714,*t10; 
	READER_OUTPUT *reader_output;
	USERINPUT userInput;
	CHARGEOUTPUT chargeOutput;
	B604DB *b604DB;
	G5714DB *g5714DB;
	T10DB *t10DB;
	CREDITOUTPUT* creditOutput;

	//File open procedure
	cusFile = fopen("customer.txt","r");
	line3File = fopen("subway_line3.txt","r");
	b604FIle = fopen("bus_b604.txt","r");
	g5714File = fopen("bus_g5714.txt","r");
	t10File = fopen("bus_t10.txt","r");

	//Check if there exists an error opening files
	if(cusFile==NULL){
		puts("customer.txt open Error!");
		return 1;
	}
	if(line3File==NULL){
		puts("subway_line3.txt open Error!");
		return 1;
	}
	if(b604FIle==NULL){
		puts("bus_b604.txt open Error!");
		return 1;
	}
	if(g5714File==NULL){
		puts("bus_g5714.txt open Error!");
		return 1;
	}
	if(t10File==NULL){
		puts("bus_t10.txt open Error!");
		return 1;
	}

	//get data from customer.txt

	fscanf(cusFile,"%d",&NumOfCustomer);

	cusInfo = (CUSTOMER*)malloc(sizeof(CUSTOMER)*NumOfCustomer);

	for(i=0;i<NumOfCustomer;i++){
		fscanf(cusFile,"%d / %[^/]/ %d / %s / %s",
			&cusInfo[i].userId,cusInfo[i].name,&cusInfo[i].charge,cardTypeTemp,cusInfo[i].age);
		len = strlen(cusInfo[i].name);
		cusInfo[i].name[len-1] = 0;
		if(strcmp(cardTypeTemp,"charge")==0) cusInfo[i].type = charge;
		else if(strcmp(cardTypeTemp,"credit")==0){
			cusInfo[i].type = credit;
			NumOfCreditCard++;
		}
	}

	//closing customer.txt file

	state = fclose(cusFile);
	if(state != 0){
		puts("customer.txt close Error!");
		return 1;
	}

	//get data from subway_line3.txt

	fscanf(line3File,"%d",&NumOfLine3);

	line3 = (TRANSPORTATION*)malloc(sizeof(TRANSPORTATION)*NumOfLine3);

	for(i=0;i<NumOfLine3;i++){
		fscanf(line3File,"%d / %d / %[^/] / %lf",
			&line3[i].tsID,&line3[i].station,line3[i].stationName,&line3[i].distance);
		len = strlen(line3[i].stationName);
		line3[i].stationName[len-1] = 0;
	}

	//closing subway_line.txt

	state = fclose(line3File);
	if(state!=0){
		puts("subway_line3,txt close Error!");
		return 1;
	}

	//get data from bus_b604.txt

	fscanf(b604FIle,"%d",&NumOfB604);

	b604 = (TRANSPORTATION*)malloc(sizeof(TRANSPORTATION)*NumOfB604);

	for(i=0;i<NumOfB604;i++){
		fscanf(b604FIle,"%d / %d / %[^/] / %lf",
			&b604[i].tsID,&b604[i].station,b604[i].stationName,&b604[i].distance);
		len = strlen(b604[i].stationName);
		b604[i].stationName[len-1] = 0;
	}

	//closing bus_b604.txt

	state = fclose(b604FIle);
	if(state!=0){
		puts("bus_b604.txt close Error!");
		return 1;
	}

	//get data from bus_g5714.txt

	fscanf(g5714File,"%d",&NumOfG5714);

	g5714 = (TRANSPORTATION*)malloc(sizeof(TRANSPORTATION)*NumOfG5714);

	for(i=0;i<NumOfG5714;i++){
		fscanf(g5714File,"%d / %d / %[^/] / %lf",
			&g5714[i].tsID,&g5714[i].station,g5714[i].stationName,&g5714[i].distance);
		len = strlen(g5714[i].stationName);
		g5714[i].stationName[len-1] = 0;
	}

	//closing bus_g5714.txt

	state = fclose(g5714File);
	if(state!=0){
		puts("bus_g5714.txt close Erro!");
		return 1;
	}

	//get data from bus_t10.txt

	fscanf(t10File,"%d",&NumOfT10);

	t10 = (TRANSPORTATION*)malloc(sizeof(TRANSPORTATION)*NumOfT10);

	for(i=0;i<NumOfT10;i++){
		fscanf(t10File,"%d / %d / %[^/] / %lf",
			&t10[i].tsID,&t10[i].station,t10[i].stationName,&t10[i].distance);
		len = strlen(t10[i].stationName);
		t10[i].stationName[len-1] = 0;
	}

	//closing bus_t10.txt

	state = fclose(t10File);
	if(state!=0){
		puts("bus_t10.txt close Error!");
		return 1;
	}

	flag = 0;

	//initializing creditOutput

	creditOutput = (CREDITOUTPUT*)malloc(sizeof(CREDITOUTPUT)*NumOfCreditCard);

	for(i=0,j=0;i<NumOfCustomer;i++){
		if(cusInfo[i].type == credit){	
			strcpy(creditOutput[j].name,cusInfo[i].name);
			creditOutput[j].charge = cusInfo[i].charge;
			creditOutput[j].userId = cusInfo[i].userId;
			j++;
		}
	}

	printf("-Input-\n");
	printf("Input size : ");
	scanf("%d%c",&count,&enter);

	printf("Input : \n");
	for(i=0;i<count;i++){
		gets(firstInput);
		if(*firstInput=='1'){

			//if you type 1, customer's charge card will be charged

			sscanf(firstInput,"%*d / %d / %d",&userInput.userId, &userInput.recharge);
			for(j=0;j<NumOfCustomer;j++){
				if(cusInfo[j].userId == userInput.userId && cusInfo[j].type == charge){
					chargeOutput.beforeBalance = cusInfo[j].charge;
					cusInfo[j].charge += userInput.recharge;
					chargeOutput.userId = cusInfo[j].userId;
					chargeOutput.afterBalance = cusInfo[j].charge;
					break;
				}
				else if(cusInfo[j].userId == userInput.userId && cusInfo[j].type == credit){ chargeOutput.chargeOrNot = 1; break; }
			}

			//if customer uses credit card, it is not possible to charge it

			if(chargeOutput.chargeOrNot == 1) puts("fail");
			else printf("%d / %d, %d\n",chargeOutput.userId,chargeOutput.beforeBalance,chargeOutput.afterBalance);

			cusFile = fopen("customer.txt","w");
			if(cusFile==NULL){
				puts("customer.txt open Error!");
				return 1;
			}
			fprintf(cusFile,"%d\n",NumOfCustomer);
			for(l=0;l<NumOfCustomer;l++){
				if(cusInfo[l].type==credit) strcpy(cardTypeTemp,"credit");
				else if(cusInfo[l].type==charge) strcpy(cardTypeTemp,"charge");
				fprintf(cusFile,"%d / %s / %d / %s / %s\n",cusInfo[l].userId,cusInfo[l].name,cusInfo[l].charge,cardTypeTemp,cusInfo[l].age);
			}

			state = fclose(cusFile);
			if(state!=0){
				puts("customer.txt close Error!");
				return 1;
			}
		}
		else if(*firstInput=='2'){

			//if you type 2, customer's credit card will be initialized

			cusFile = fopen("customer.txt","w");
			if(cusFile==NULL){
				puts("customer.txt open Error!");
				return 1;
			}

			for(j=0;j<NumOfCreditCard;j++){

				for(l=0;l<NumOfG5714User;l++)
					if(g5714DB[l].userId == creditOutput[j].userId)
						creditOutput[j].charge += g5714DB[l].charge;

				for(l=0;l<NumOfB604User;l++)
					if(b604DB[l].userId == creditOutput[j].userId)
						creditOutput[j].charge += b604DB[l].charge;

				for(l=0;l<NumOfT10User;l++)
					if(t10DB[l].userId == creditOutput[j].userId)
						creditOutput[j].charge += t10DB[l].charge;

			}

			for(l=0;l<NumOfCreditCard;l++)
				printf("%d : %s / %d\n",creditOutput[l].userId,creditOutput[l].name,creditOutput[l].charge);

			//after printing how much creditcard user have to pay, they have to pay for it

			fprintf(cusFile,"%d\n",NumOfCustomer);
			for(l=0;l<NumOfCustomer;l++){
				if(cusInfo[l].type==credit){
					strcpy(cardTypeTemp,"credit");
					cusInfo[l].charge = 0;
				}
				else if(cusInfo[l].type==charge) strcpy(cardTypeTemp,"charge");
				fprintf(cusFile,"%d / %s / %d / %s / %s\n",cusInfo[l].userId,cusInfo[l].name,cusInfo[l].charge,cardTypeTemp,cusInfo[l].age);
			}

			state = fclose(cusFile);
			if(state!=0){
				puts("customer.txt close Error!");
				return 1;
			}
		}
		else if(*firstInput=='3'){

			//if you type 3, last stop system will be started

			if(flag==0){

				//if you start it first time, program has to read data from reader_output.txt

				reader_outputFp = fopen("reader_output.txt","r");
				if(reader_outputFp == NULL){
					puts("reader_output.txt open Error!");
					return 1;
				}

				fscanf(reader_outputFp,"%d",&NumOfReader_output);
				reader_output = (READER_OUTPUT*)malloc(sizeof(READER_OUTPUT)*NumOfReader_output);

				for(l=0;l<NumOfReader_output;l++){
					fscanf(reader_outputFp,"%s / %d / %[^/]/ %d / %s / %s / %d",
						reader_output[l].transportation, &reader_output[l].userId, reader_output[l].getOnOffTime,
						&reader_output[l].stationId, cardTypeTemp, reader_output[l].age , &reader_output[l].charge);
					if(strcmp(cardTypeTemp,"charge")==0) reader_output[l].type = charge;
					else if(strcmp(cardTypeTemp,"credit")==0){
						reader_output[l].type = credit;
						if( strcmp(reader_output[l].transportation,"g5714") == 0 ) NumOfG5714User++;
						else if( strcmp(reader_output[l].transportation,"b604") == 0 ) NumOfB604User++;
						else if( strcmp(reader_output[l].transportation,"t10") == 0 ) NumOfT10User++;
					}
				}

				if(NumOfB604User>0) b604DB = (B604DB*)malloc(sizeof(B604DB)*NumOfB604User);
				if(NumOfG5714User>0) g5714DB = (G5714DB*)malloc(sizeof(G5714DB)*NumOfG5714User);
				if(NumOfT10User>0) t10DB = (T10DB*)malloc(sizeof(T10DB)*NumOfT10User);

				for(l=0;l<NumOfReader_output;l++){
					if( cusInfo[reader_output[l].userId].type == credit ){
						if( strcmp(reader_output[l].transportation,"g5714") == 0 ){
							g5714DB[a].userId = reader_output[l].userId;
							g5714DB[a].charge = reader_output[l].charge;
							a++;
						}
						else if( strcmp(reader_output[l].transportation,"b604") == 0 ){
							b604DB[b].userId = reader_output[l].userId;
							b604DB[b].charge = reader_output[l].charge;
							b++;
						}
						else if( strcmp(reader_output[l].transportation,"t10") == 0 ){
							t10DB[c].userId = reader_output[l].userId;
							t10DB[c].charge = reader_output[l].charge;
							c++;
						}
					}
				}

				flag = 1; 

				state = fclose(reader_outputFp);
				if(state!=0){
					puts("reader_output.txt close Error!");
					return 1;
				}
			}

			//print people who use a transportation

			sscanf(firstInput,"%*d / %s",tempTransportation);
			if(strcmp(tempTransportation,"t10")==0){
				if(NumOfT10User==0) puts("Anybody who has credit card doesn't take t10");
				else
					for(l=0;l<NumOfT10User;l++)
						if(t10DB[l].charge!=0)
							printf("%d : %d\n",t10DB[l].userId,t10DB[l].charge);
			}
			else if(strcmp(tempTransportation,"b604")==0){
				if(NumOfB604User==0) puts("Anybody who has credit card doesn't take b604");
				else
					for(l=0;l<NumOfB604User;l++)
						if(b604DB[l].charge!=0)
							printf("%d : %d\n",b604DB[l].userId,b604DB[l].charge);
			}
			else if(strcmp(tempTransportation,"g5714")==0){
				if(NumOfG5714User==0) puts("Anybody who has credit card doesn't take g5714");
				else
					for(l=0;l<NumOfG5714User;l++)
						if(g5714DB[l].charge!=0)
							printf("%d : %d\n",g5714DB[l].userId,g5714DB[l].charge);
			}

		}
	}

	//free procedure
	free(b604);
	free(g5714);
	free(t10);
	free(cusInfo);
	free(line3);
	free(creditOutput);
	free(reader_output);
	if(NumOfB604User>0) free(b604DB); 			
	if(NumOfG5714User>0) free(g5714DB); 			
	if(NumOfT10User>0) free(t10DB);

	return 0;
}
