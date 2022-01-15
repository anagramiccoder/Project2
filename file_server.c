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
		scanf("%[^\n]%*c", command);
		time(&t);
		printf("%s %s",command,ctime(&t));
		cmdfile=fopen("command.txt","a+");
		fprintf(cmdfile,"%s %s",command,ctime(&t));
		fclose(cmdfile);
		char *wcmd=(char *) malloc(150 *sizeof(char));
		strcpy(wcmd,command);
		worker *temp=malloc(sizeof(worker));
		temp->next=head;
		head=temp;
		pthread_create(&head->id,NULL,(void *) towork,wcmd);
	}
	while(head!=NULL){
	pthread_join(head->id,NULL);
	head=head->next;
	}
	return 0;
}

void towork(char  *cmd){
	int del=rand()%10;
	if(del==0 || del==1){
	sleep(6);
	}
	else{
	sleep(1);
	}
	if (cmd[0]=='r' && cmd[1]=='e' && cmd[2]=='a' && cmd[3]=='d'){
		toread(&cmd[5]);
	}
	else if(cmd[0]=='e' && cmd[1]=='m' && cmd[2]=='p' && cmd[3]=='t' && cmd[4]=='y'){
		toempty(&cmd[6]);
	}
	else if(cmd[0]=='w' && cmd[1]=='r' && cmd[2]=='i' && cmd[3]=='t' && cmd[4]=='e'){
		towrite(&cmd[6]);
	}
	else{
		printf("ERROR: no such command\n");
	}
}
void toread(char *add){
	FILE *rf;
	rf=fopen(add,"r");
	char *input="read";
	char data[50]="FILE DNE";
	if(rf!=NULL){
		fgets(data,50,rf);
		fclose(rf);
		int len=strlen(data);
		data[len-1]='\0';
	}
	rf=fopen("read.txt","a+");
	fprintf(rf,"%s %s: %s\n",input,add,data);
	fclose(rf);
}
void toempty(char *add){
	FILE *ef;
	ef=fopen(add,"r");
	char *input="empty";
	char data[50]="FILE ALREADY EMPTY";
	if(ef!=NULL){
		fgets(data,50,ef);
		fclose(ef);
		fclose(fopen(add,"w"));
		int len=strlen(data);
		data[len-1]='\0';
	}
	ef=fopen("empty.txt","a+");
	fprintf(ef,"%s %s: %s\n",input,add,data);
	fclose(ef);
	int delay=rand()%3001;
	double sec=(7000+delay)/1000;
	sleep(sec);
}
void towrite(char *cmd){
	FILE *wf;
	int count=0;
	char *p=cmd;
	while(*p!=' '){
		count+=1;
		p++;
	}
	char add[count-1];
	strcpy(add,cmd);
	add[count]='\0';
	p=&cmd[count+1];
	wf=fopen(add,"a+");
	while(*p!='\0'){
		fputc(*p,wf);
		sleep(0.025);
		p++;
	}
	fclose(wf);
}
