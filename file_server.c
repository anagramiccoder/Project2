#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include <unistd.h>
typedef struct worker_thread{
	pthread_t id;
	struct worker_thread *next;
}work;
time_t t;
char command[150];
FILE *cmdfile;
void rfile(char *add);
void wfile(char *cmd);
void efile(char *add);
void worker(char *cmd);
int main(){
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
		worker(wcmd);
	}
	return 0;
}

void worker(char  *cmd){
	int del=rand()%10;
	if(del==0 || del==1){
	sleep(0.6);
	}
	else{
	sleep(0.6);
	}
	if (cmd[0]=='r' && cmd[1]=='e' && cmd[2]=='a' && cmd[3]=='d'){
		rfile(&cmd[5]);
	}
	else if(cmd[0]=='e' && cmd[1]=='m' && cmd[2]=='p' && cmd[3]=='t' && cmd[4]=='y'){
		efile(&cmd[6]);
	}
	else if(cmd[0]=='w' && cmd[1]=='r' && cmd[2]=='i' && cmd[3]=='t' && cmd[4]=='e'){
		wfile(&cmd[6]);
	}
	else{
		printf("ERROR: no such command\n");
	}
}
void rfile(char *add){
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
	free(add);
}
void efile(char *add){
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
	free(add);
}
void wfile(char *cmd){
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
	printf("%s\n",&cmd[count+1]);
}
