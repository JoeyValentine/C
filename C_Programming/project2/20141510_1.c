#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}TRANSPORTATION; //transportation's informationm

typedef struct _NODE{
	int userId;
	char transportaion[10];
	int stationId;
	char getOnOffTime[20];
	double distance;
	int charge;
	struct _NODE *next;
	struct _NODE *prev;
}NODE; //which was used to make linked list

NODE *head = NULL;
NODE *tail = NULL;

typedef struct{
	int userId;
	int restCharge;
	int noMoney;
}OUTPUT; //after calculation, function save data into structure

void InsertNodeAtBack(int userId,char* transportation,int stationId,char* getOnOffTime,double distance,int charge){

	//insert node at back

	//initialization

	NODE *newNode = (NODE*)malloc(sizeof(NODE)),*cur;
	newNode->userId = userId;
	strcpy(newNode->transportaion,transportation);
	newNode->stationId = stationId;
	strcpy(newNode->getOnOffTime,getOnOffTime);
	newNode->distance = distance;
	newNode->charge = charge;
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

OUTPUT* calcCharge(CUSTOMER *customer){

	// after calculation, we get charge information

	NODE *cur,*temp;
	int i,j,count =0,flag = 0;
	OUTPUT *output;

	for(cur=head;cur!=NULL;cur=cur->next) count++;
	output = (OUTPUT*)malloc(sizeof(OUTPUT)*count);

	for(i=0;i<count;i++)
		output[i].noMoney = 0;

	//if noMoney is 0, they have enough money
	//if noMoney is 1, they don't have enough money

	for(cur=head,i=0;cur!=NULL;cur=cur->next,i++){
		output[i].userId = cur->userId;
		if(customer[cur->userId].type == charge){
			if( customer[cur->userId].charge < cur->charge) output[i].noMoney = 1;
			else{
				if(cur->distance!=0){
					for(temp=cur->prev,j=i-1;temp!=NULL;temp=temp->prev,j--){
						if(temp->distance == 0 && temp->userId == cur->userId && strcmp(temp->transportaion,cur->transportaion)==0 && output[j].noMoney == 1 ){
							output[i].noMoney = 1;
							flag = 1;
						}
					}
				}
				if(flag != 1){
					output[i].restCharge = customer[cur->userId].charge - cur->charge;
					customer[cur->userId].charge -= cur->charge;
				}
			}
		}
		else if(customer[cur->userId].type == credit){
			output[i].restCharge = customer[cur->userId].charge + cur->charge;
			if(strcmp(cur->transportaion,"line3")==0)
				customer[cur->userId].charge += cur->charge;
		}
		flag = 0;
	}

	return output;
}

int main (){

	FILE *cusFile; //FILE pointers were used to open files
	int state; //It was used to check whether a file closed properly
	int i; //They were used to compute for loops
	int len; //string's length
	int count; //It the number of how many times user types input
	int NumOfCustomer; //the number of customer
	char cardTypeTemp[7]; //It was used to distinguish between credit card and transportation card
	//temp~ were used to save data temporarly
	int tempUserId;  
	char tempTransportation[10];
	int tempStationId;
	char tempGetOnOffTime[20];
	double tempDistance;
	int tempCharge;
	NODE *cur,*temp; //they were needed for for loops
	CUSTOMER *cusInfo; //CUSTOMER pointer was used to store customer's information
	OUTPUT *output; // outcome of this program

	//File open procedure
	cusFile = fopen("customer.txt","r");

	//Check if there exists an error opening files
	if(cusFile==NULL){
		puts("customer.txt open Error!");
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
	}

	//closing customer.txt file
	state = fclose(cusFile);
	if(state != 0){
		puts("customer.txt close Error!");
		return 1;
	}

	printf("-Input-\n");
	printf("Input size : ");
	scanf("%d",&count);
	for(i=0;i<count;i++){
		scanf("%d / %s / %d / %[^/]/ %lf / %d",
			&tempUserId,tempTransportation,&tempStationId,tempGetOnOffTime,&tempDistance,&tempCharge);
		len = strlen(tempGetOnOffTime);
		tempGetOnOffTime[len-1] = 0;
		InsertNodeAtBack(tempUserId,tempTransportation,tempStationId,tempGetOnOffTime,tempDistance,tempCharge);
	}

	output = calcCharge(cusInfo);

	//if customer has no money, he or she fails to board or get off from transportation
	for(i=0;i<count;i++){
		if(output[i].noMoney==1) puts("fail");
		else printf("%d : %d\n",output[i].userId,output[i].restCharge);
	}

	//after calculation, customer.txt file needs to be updated
	cusFile = fopen("customer.txt","w");

	if(cusFile==NULL){
		puts("customer.txt open Error!");
		return 1;
	}

	fprintf(cusFile,"%d\n",NumOfCustomer);
	for(i=0;i<NumOfCustomer;i++){
		if(cusInfo[i].type == credit) strcpy(cardTypeTemp,"credit");
		else if(cusInfo[i].type == charge) strcpy(cardTypeTemp,"charge");
		fprintf(cusFile,"%d / %s / %d / %s / %s\n"
			,cusInfo[i].userId,cusInfo[i].name,cusInfo[i].charge,cardTypeTemp,cusInfo[i].age);
	}

	state = fclose(cusFile);
	if(state!=0){
		puts("customer.txt close Error!");
		return 1;
	}

	//free procedure
	free(cusInfo);
	free(output);
	for(cur=head;cur!=NULL;){
		temp = cur;
		cur = cur->next;
		free(temp);
	}

	return 0;
}
