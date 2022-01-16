#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include <unistd.h>
#include<pthread.h>
typedef struct workerthread{
	pthread_t id;//thread part
	struct workerthread *next;
}worker;
time_t t;
char command[150];
FILE *cmdfile;
void toread(char *add);
void towrite(char *cmd);
void toempty(char *add);
void towork(char *cmd);
int main(){
	worker *head=NULL;//initial worker->none
	while(1){
		printf(">>");
		scanf("%[^\n]%*c", command);//scanf command which gets the input, denoted by \n on the end
		if(strcmp(command,"exit")==0){break;}
		time(&t);//update time after getting command
		cmdfile=fopen("command.txt","a+"); //a+ to append if file present, create if not.
		fprintf(cmdfile,"%s %s",command,ctime(&t));//ctime(&t) was part of the previous lab, it returns a string format of the current time recorded at time(&t)
		fclose(cmdfile);
		char *wcmd=(char *) malloc(150 *sizeof(char));//new malloc for threading purposes.
		strcpy(wcmd,command);//creating a new copy of the command
		worker *temp=malloc(sizeof(worker));
		temp->next=head;//earlier threads goes to the tail, meaning the nearer it is in the head, the more recent the thread is
		head=temp;
		pthread_create(&head->id,NULL,(void *) towork,wcmd);
	}
	printf("waiting for all threads to finish\n");
	while(head!=NULL){//while there are other threads left
	pthread_join(head->id,NULL);
	head=head->next;
	}
	printf("all Threads finished...\n");
	return 0;
}

void towork(char  *cmd){
	int del=rand()%10;//random seconds
	if(del==5 || del==6){
	sleep(6);//sleep is in integer, seconds
	}
	else{
	sleep(1);
	}
	//did not use strcmp, since this is one of the unique ways of how I implement it
	if (cmd[0]=='r' && cmd[1]=='e' && cmd[2]=='a' && cmd[3]=='d'){
		toread(&cmd[5]);
	}
	else if(cmd[0]=='e' && cmd[1]=='m' && cmd[2]=='p' && cmd[3]=='t' && cmd[4]=='y'){
		toempty(&cmd[6]);
	}
	else if(cmd[0]=='w' && cmd[1]=='r' && cmd[2]=='i' && cmd[3]=='t' && cmd[4]=='e'){
		towrite(&cmd[6]);
	}
	else{//just incase it is not from the 4 commands, read, write, empty, exit-- note that for exit, it willnot create a new thread
		printf("ERROR: no such command\n");
	}
}
void toread(char *add){
	FILE *rf;
	rf=fopen(add,"r");
	char *input="read";
	char data[50]="FILE DNE";//set default value to FILE DNE,
	if(rf!=NULL){
		char tempdata[50];
		fgets(tempdata,50,rf);
		fclose(rf);
		strcpy(data,tempdata);
		if(strlen(tempdata)>0){//check if existing file but empty content
		int len=strlen(data);
		data[len-1]='\0';
		}
	}
	rf=fopen("read.txt","a+");
	fprintf(rf,"%s %s: %s\n",input,add,data);
	fclose(rf);
}
void toempty(char *add){
	FILE *ef;
	ef=fopen(add,"r");
	char *input="empty";
	int emp=0;
	char data[50]="FILE ALREADY EMPTY";
	if(ef!=NULL){
		char tempdata[50];//temporary
		fgets(tempdata,50,ef);
		fclose(ef);
		if(strlen(tempdata)>0){//non empty file
		emp=1;
		strcpy(data,tempdata);
		int len=strlen(data);
		data[len-1]='\0';
		}
	}
	ef=fopen("empty.txt","a+");
	fprintf(ef,"%s %s: %s\n",input,add,data);
	fclose(ef);
	if(emp==1){//file not empty, does emptying and delaying
	fclose(fopen(add,"w"));
	int delay=rand()%3001;//0-3000 increase delay
	int sec=(7000+delay)*1000;//7s to 10 s with decimals
	usleep(sec);
	}
}
void towrite(char *cmd){
	FILE *wf;
	int count=0;//count until the <space>
	char *p=cmd;
	while(*p!=' '){//find the first iteration of <space> after the space after the 'write'
		count+=1;
		p++;
	}
	int c=0;
	char add[60];//create a new char
	strncpy(add,cmd,count-1);//strncpy, max char to be read
	add[count]='\0';//change the space to null terminator
	p++;
	char *string=(char *)malloc(55*sizeof(char));
	strncpy(string,p,50);
	int l=strlen(string);
	c=0;
	string[l]='\0';
	wf=fopen(add,"a+");
	while(c<l){
		if (string[c]=='\0')
			break;
		fputc(string[c],wf);
		c++;
		usleep(25000);//sleep every  25 ms
	}
	fclose(wf);
	free(string);
}
