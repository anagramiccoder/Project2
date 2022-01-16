#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include <unistd.h>
#include<pthread.h>
typedef struct workerthread{
	pthread_t id;
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
	worker *head=NULL;
	while(1){
		printf(">>");
		scanf("%[^\n]%*c", command);//scanf command which gets the input, denoted by \n on the end
		if(strcmp(command,"exit")==0){break;}
		time(&t);//update time after getting command
		cmdfile=fopen("command.txt","a+"); //a+ to append if file present, create if not.
		fprintf(cmdfile,"%s %s",command,ctime(&t));
		fclose(cmdfile);
		char *wcmd=(char *) malloc(150 *sizeof(char));
		strcpy(wcmd,command);
		worker *temp=malloc(sizeof(worker));
		temp->next=head;//earlier threads goes to the tail, meaning the nearer it is in the head, the more recent the thread is
		head=temp;
		pthread_create(&head->id,NULL,(void *) towork,wcmd);
	}
	printf("waiting for all threads to finish\n");
	while(head!=NULL){
	pthread_join(head->id,NULL);
	head=head->next;
	}
	printf("all Threads finished...\n");
	return 0;
}

void towork(char  *cmd){
	int del=rand()%10;
	if(del==3 || del==6){
	sleep(6);
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
		char tempdata[50];
		fgets(tempdata,50,ef);
		fclose(ef);
		if(strlen(tempdata)>0){
		emp=1;
		strcpy(data,tempdata);
		int len=strlen(data);
		data[len-1]='\0';
		}
	}
	ef=fopen("empty.txt","a+");
	fprintf(ef,"%s %s: %s\n",input,add,data);
	fclose(ef);
	if(emp==1){
	fclose(fopen(add,"w"));
	int delay=rand()%3001;
	double sec=(7000+delay)/1000;
	sleep(sec);
	}
}
void towrite(char *cmd){
	FILE *wf;
	int count=0;
	char *p=cmd;
	while(*p!=' '){//find the first iteration of <space> after the space after the 'write'
		count+=1;
		p++;
	}
	char add[count-1];//create a new char
	strcpy(add,cmd);
	add[count]='\0';//change the space to null terminator
	p=&cmd[count+1];//start after the detected space meaning the string
	wf=fopen(add,"a+");
	while(*p!='\0'){
		fputc(*p,wf);
		sleep(0.025);//sleep every 25 ms
		p++;
	}
	fclose(wf);
}
