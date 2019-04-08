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
	int noMoney;
}CUSTOMER; //customer's information

typedef struct{
	int tsID;
	int station;
	char stationName[100];
	double distance;
}TRANSPORTATION; //transportation's information

typedef struct _NODE{
	int userId;
	char transportation[10];
	int stationId;
	char getOnOffTime[20];
	int transferNum;
	int getOnOffInfo;
	struct _NODE *next;
	struct _NODE *prev;
}NODE; //linked list's node

NODE *head = NULL;
NODE *tail = NULL;

typedef struct{
	int userId;
	int charge;
	int restCharge;
	double distance;
	int noMoney;
}OUTPUT; //this saves data after calculating

typedef struct{
	char transportation[10];
	int userId;
	char getOnOffTime[20];
	int stationId;
	enum cardType type;
	char age[10];
	int charge;
}READER_OUTPUT; //data will be saved by this structure to make reader_output.txt

void InsertNodeAtBack(int userId,char* transportation,int stationId,char* getOnOffTime,int transferNum,int getOnOffInfo){

	//insert node at back

	//initialization

	NODE *newNode = (NODE*)malloc(sizeof(NODE)),*cur;
	newNode->userId = userId;
	strcpy(newNode->transportation,transportation);
	newNode->stationId = stationId;
	strcpy(newNode->getOnOffTime,getOnOffTime);
	newNode->transferNum = transferNum;
	newNode->getOnOffInfo = getOnOffInfo;
	newNode->next = NULL;

	if(head == NULL){
		head = newNode;
		tail = newNode;
		newNode->prev = NULL;
		newNode->next = NULL;
		head->prev = NULL;
		tail->next = NULL;
	}
	else{
		for(cur=head;;cur=cur->next){
			if(cur->next==NULL){
				cur->next = newNode;
				tail = newNode;
				newNode->prev = cur;
				break;
			}
		}
	} 
}

OUTPUT* chargeCalc(int count,CUSTOMER *customer,TRANSPORTATION* line3,TRANSPORTATION *b604,TRANSPORTATION* g5714,TRANSPORTATION* t10,int NumOfLine3,int NumOfB604,int NumOfG5714,int NumOfT10){

	// after calculation, we get userId,distance,charge information

	OUTPUT* output = (OUTPUT*)malloc(sizeof(OUTPUT)*count); //result of this function
	NODE *cur,*temp,*tempNoMoney; //which was used to help for loops
	int i,j,k,tempCost,UserNumber,tempStationId,flag=0,indexPrev,indexCur,flagNoMoney=0; // which was used to help for loops
	double distance = 0,totalDistance = 0; //how long 

	//if noMoney is 0, they have enough money
	//if noMoney is 1, they don't have enough money

	for(i=0;i<count;i++)
		output[i].noMoney = 0;

	for(cur=head,i=0;cur!=NULL;cur=cur->next,i++){

		// 1st step : save user Id

		output[i].userId = cur->userId;
		UserNumber = output[i].userId;

		// 2nd step : measure distance

		if(cur->getOnOffInfo == 0)
			output[i].distance = 0;
		else if(cur->getOnOffInfo == 1){
			for(temp=cur->prev;temp!=NULL;temp=temp->prev){
				if(flag==1){
					flag = 0;
					break;
				}
				if(temp->getOnOffInfo == 0 && temp->userId == cur->userId && strcmp(temp->transportation,cur->transportation)==0 ){
					tempStationId = cur->stationId;
					if(strcmp(cur->transportation,"3") == 0){
						for(k=0;k<NumOfLine3;k++)
							if(line3[k].station==tempStationId) indexCur = k;
						for(k=0;k<NumOfLine3;k++)
							if(line3[k].station==temp->stationId) indexPrev = k;

						if(indexCur>indexPrev){
							for(j=1;j<NumOfLine3;j++){
								if(flag == 0 && temp->stationId == line3[j-1].station){
									flag = 1;
									distance += line3[j].distance;
								}
								else if(flag==1) distance += line3[j].distance;
								if(tempStationId==line3[j].station) break;
							}
						}
						else if(indexCur<indexPrev){
							for(j=NumOfLine3-1;j>0;j--){
								if(tempStationId==line3[j].station) break;
								if(flag == 0 && temp->stationId == line3[j].station){ 
									distance += line3[j].distance;
									flag = 1;
								}
								else if(flag==1) distance += line3[j].distance;

							}
						}

					}
					else if(strcmp(cur->transportation,"b604")==0){
						for(k=0;k<NumOfB604;k++)
							if(b604[k].station==tempStationId) indexCur = k;
						for(k=0;k<NumOfB604;k++)
							if(b604[k].station==temp->stationId) indexPrev = k;

						if(indexCur>indexPrev){
							for(j=1;j<NumOfB604;j++){
								if(flag == 0 && temp->stationId == b604[j-1].station){
									flag = 1;
									distance += b604[j].distance;
								}
								else if(flag==1) distance += b604[j].distance;
								if(tempStationId==b604[j].station) break;
							}
						}
						else if(indexCur<indexPrev){
							for(j=NumOfB604-1;j>0;j--){
								if(tempStationId==b604[j].station) break;
								if(flag == 0 && temp->stationId == b604[j].station){ 
									distance += b604[j].distance;
									flag = 1;
								}
								else if(flag==1) distance += b604[j].distance;

							}
						}
					}
					else if(strcmp(cur->transportation,"g5714")==0){
						for(k=0;k<NumOfG5714;k++)
							if(g5714[k].station==tempStationId) indexCur = k;
						for(k=0;k<NumOfG5714;k++)
							if(g5714[k].station==temp->stationId) indexPrev = k;

						if(indexCur>indexPrev){
							for(j=1;j<NumOfG5714;j++){
								if(flag == 0 && temp->stationId == g5714[j-1].station){
									flag = 1;
									distance += g5714[j].distance;
								}
								else if(flag==1) distance += g5714[j].distance;
								if(tempStationId==g5714[j].station) break;
							}
						}
						else if(indexCur<indexPrev){
							for(j=NumOfG5714-1;j>0;j--){
								if(tempStationId==g5714[j].station) break;
								if(flag == 0 && temp->stationId == g5714[j].station){ 
									distance += g5714[j].distance;
									flag = 1;
								}
								else if(flag==1) distance += g5714[j].distance;

							}
						}
					}
					else if(strcmp(cur->transportation,"t10")==0){
						for(k=0;k<NumOfT10;k++)
							if(t10[k].station==tempStationId) indexCur = k;
						for(k=0;k<NumOfT10;k++)
							if(t10[k].station==temp->stationId) indexPrev = k;

						if(indexCur>indexPrev){
							for(j=1;j<NumOfT10;j++){
								if(flag == 0 && temp->stationId == t10[j-1].station){
									flag = 1;
									distance += t10[j].distance;
								}
								else if(flag==1) distance += t10[j].distance;
								if(tempStationId == t10[j].station) break;
							}
						}
						else if(indexCur<indexPrev){
							for(j=NumOfT10-1;j>0;j--){
								if(tempStationId==t10[j].station) break;
								if(flag == 0 && temp->stationId == t10[j].station){ 
									distance += t10[j].distance;
									flag = 1;
								}
								else if(flag==1) distance += t10[j].distance;

							}
						}
					}
					flag = 1;
					output[i].distance = distance;
				}
				distance = 0;
			}
		}

		// 3rd step : depend on the situation, function calculate charge

		if( cur->getOnOffInfo == 0 && cur->transferNum == 0 ){
			if(strcmp(customer[UserNumber].age,"adult")==0){
				if(strcmp(cur->transportation,"t10")==0) tempCost = 850;
				else tempCost = 1050;
			}
			else if(strcmp(customer[UserNumber].age,"teens")==0){
				if(strcmp(cur->transportation,"t10")==0) tempCost = 560;
				else tempCost = 720; 
			}
			else if(strcmp(customer[UserNumber].age,"child")==0){
				if(strcmp(cur->transportation,"t10")==0)
					tempCost = 350;
				else tempCost = 450;
			}
		}
		else if( cur->getOnOffInfo == 0 && cur->transferNum != 0 ){
			if(cur->transferNum==1){
				for(temp=cur;temp!=NULL;temp=temp->prev){
					if( temp->userId == cur->userId && strcmp(temp->transportation,"t10")==0 ){
						if(strcmp(customer[UserNumber].age,"adult")==0)
							tempCost = 200;
						else if(strcmp(customer[UserNumber].age,"teens")==0)
							tempCost = 160;
						else if(strcmp(customer[UserNumber].age,"child")==0)
							tempCost = 100;
						flag = 0;
					}
				}
			}
			if(flag==1) tempCost = 0;
			flag = 1;
		}
		else if( cur->getOnOffInfo == 1 && cur->transferNum == 0 ){
			if(strcmp(cur->transportation,"3")==0){
				for(temp=head,j=0;j<=i;j++,temp=temp->next){
					if(output[j].userId == cur->userId) totalDistance += output[j].distance;
					if(temp->transferNum == 0 && temp->getOnOffInfo == 0) totalDistance = 0;
				}
				if( totalDistance <= 10 ) tempCost = 0;
				else if( totalDistance > 10 && totalDistance <=40 )
					tempCost = ((int)(totalDistance-10)/5+1)*100;
				else if( totalDistance>40 )
					tempCost = ((int)(totalDistance-40)/10+1)*100 + 600;

				if(strcmp(customer[UserNumber].age,"teens")==0) tempCost *= 0.8;
				else if(strcmp(customer[UserNumber].age,"child")==0) tempCost *= 0.5;
			}
			else tempCost = 0;
		}
		else if( cur->getOnOffInfo == 1 && cur->transferNum != 0 ){
			for(temp=head,j=0;j<=i;j++,temp=temp->next){
				if(output[j].userId == cur->userId) totalDistance += output[j].distance;
				if(output[j].userId == cur->userId && temp->transferNum == 0 && temp->getOnOffInfo == 0) totalDistance = 0;
			}
			if( totalDistance <= 10 ) tempCost = 0;
			else if( totalDistance > 10 )
				tempCost = ((int)(totalDistance-10)/5+1)*100;

			if(strcmp(customer[UserNumber].age,"teens")==0) tempCost *= 0.8;
			else if(strcmp(customer[UserNumber].age,"child")==0) tempCost *= 0.5;
		}
		output[i].charge = tempCost;

		// 4th step : depend on card type, function calculate money differently

		if(customer[cur->userId].type == charge){
			if( customer[cur->userId].charge < output[i].charge ) output[i].noMoney = 1;
			else{
				if(output[i].distance!=0){
					for(tempNoMoney=cur->prev,j=i-1;tempNoMoney!=NULL;tempNoMoney=tempNoMoney->prev,j--){
						if(tempNoMoney->getOnOffInfo == 0 && tempNoMoney->userId == cur->userId && strcmp(tempNoMoney->transportation,cur->transportation)==0 && output[j].noMoney == 1 ){
							output[i].noMoney = 1;
							flagNoMoney = 1;
						}
					}
				}
				if(flagNoMoney != 1){
					output[i].restCharge = customer[output[i].userId].charge - output[i].charge;
					customer[output[i].userId].charge -= output[i].charge;
				}
			}
		}
		else if(customer[cur->userId].type == credit){
			output[i].restCharge = customer[output[i].userId].charge + output[i].charge;
			if(strcmp(cur->transportation,"line3")==0)
				customer[output[i].userId].charge += output[i].charge;
		}

		tempCost = 0;
		totalDistance = 0;
		flag = 0;
		flagNoMoney = 0;
	}

	return output;
}
int main (){

	FILE *cusFile,*line3File,*b604FIle,*g5714File,*t10File,*outputTxt; //FILE pointers were used to open files
	int state; //It was used to check whether a file closed properly
	int i; //They were used to compute for loops
	int len; //string's length
	int count; //It the number of how many times user types input
	int NumOfCustomer; //the number of customer
	int NumOfLine3;
	int NumOfB604;
	int NumOfG5714;
	int NumOfT10; 
	char cardTypeTemp[7]; //It was used to distinguish between credit card and transportation card
	int tempUserId; 
	char tempTransportation[10];
	int tempStationId;
	char tempGetOnOffTime[20];
	int transferNum;
	int getOnOffInfo;
	int NumOfReader_Output=0;
	NODE *cur; //
	NODE *temp; //
	CUSTOMER *cusInfo; //CUSTOMER pointer was used to store customer's information
	TRANSPORTATION *line3,*b604,*g5714,*t10; //TRANSPORTATION pointers were used to store transportation's information
	OUTPUT *output; 
	READER_OUTPUT *reader_output;

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
		else if(strcmp(cardTypeTemp,"credit")==0) cusInfo[i].type = credit;
		cusInfo[i].noMoney = 0;
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

	//closing subway_line3.txt file
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

	//closing bus_b604.txt file
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

	//closing bus_g5714.txt file
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

	//closing bus_t10.txt file
	state = fclose(t10File);
	if(state!=0){
		puts("bus_t10.txt close Error!");
		return 1;
	}

	//first, user type how many times he or she wants to type. Then, user inputs a transportation information

	printf("-Input-\n");
	printf("Input size : ");
	scanf("%d",&count);
	for(i=0;i<count;i++){
		scanf("%d / %s / %d / %[^/]/ %d / %d",
			&tempUserId,tempTransportation,&tempStationId,tempGetOnOffTime,&transferNum,&getOnOffInfo);
		len = strlen(tempGetOnOffTime);
		tempGetOnOffTime[len-1] = 0;
		InsertNodeAtBack(tempUserId,tempTransportation,tempStationId,tempGetOnOffTime,transferNum,getOnOffInfo);
	}

	output = chargeCalc(count,cusInfo,line3,b604,g5714,t10,NumOfLine3,NumOfB604,NumOfG5714,NumOfT10);

	for(i=0;i<count;i++){
		if(output[i].noMoney == 1) puts("fail");
		else printf("%d : %d, %d, %.1lf\n",output[i].userId,output[i].charge,output[i].restCharge,output[i].distance);
	}

	//in order to write data, fopen is needed
	outputTxt = fopen("reader_output.txt","w");

	if(outputTxt==NULL){
		puts("reader_output.txt open Error!");
		return 1;
	}

	reader_output = (READER_OUTPUT*)malloc(sizeof(READER_OUTPUT)*count);

	for(i=0;i<count;i++)
		if(output[i].noMoney!=1) NumOfReader_Output++;

	fprintf(outputTxt,"%d\n",NumOfReader_Output);

	for(cur=head,i=0;i<count;cur=cur->next,i++){
		if(output[i].noMoney!=1){
			strcpy(reader_output[i].transportation,cur->transportation);
			reader_output[i].userId = output[i].userId;
			strcpy(reader_output[i].getOnOffTime,cur->getOnOffTime);
			reader_output[i].stationId = cur->stationId;
			if(cusInfo[output[i].userId].type == credit){ 
				strcpy(cardTypeTemp,"credit");
				reader_output[i].type = credit;
			}
			else if(cusInfo[output[i].userId].type == charge){ 
				strcpy(cardTypeTemp,"charge");
				reader_output[i].type = charge;
			}
			strcpy(reader_output[i].age,cusInfo[output[i].userId].age);
			reader_output[i].charge = output[i].charge;
			fprintf(outputTxt,"%s / %d / %s / %d / %s / %s / %d\n",
				reader_output[i].transportation,reader_output[i].userId,reader_output[i].getOnOffTime,
				reader_output[i].stationId,cardTypeTemp,reader_output[i].age,reader_output[i].charge);
		}
	}

	state = fclose(outputTxt);
	if(state!=0){
		puts("reader_output.txt close Error!");
		return 1;
	}

	//in order to update customer's data, fopen is needed
	cusFile = fopen("customer.txt","w");

	if(cusFile==NULL){
		puts("customer.txt open Error!");
		return 1;
	}

	fprintf(cusFile,"%d\n",NumOfCustomer);
	for(i=0;i<NumOfCustomer;i++){
		if( cusInfo[i].type == charge ) strcpy(cardTypeTemp,"charge");
		else if( cusInfo[i].type == credit ) strcpy(cardTypeTemp,"credit");
		fprintf(cusFile,"%d / %s / %d / %s / %s\n"
			,cusInfo[i].userId,cusInfo[i].name,cusInfo[i].charge,cardTypeTemp,cusInfo[i].age);
	}

	state = fclose(cusFile);
	if(state!=0){
		puts("customer.txt close Error!");
		return 1;
	}

	//free procedure
	free(output);	
	free(b604);
	free(g5714);
	free(t10);
	free(cusInfo);
	free(line3);
	free(reader_output);

	for(cur=head;cur!=NULL;){
		temp = cur;
		cur = cur->next;
		free(temp);
	}

	return 0;
}
