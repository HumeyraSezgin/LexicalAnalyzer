#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	FILE *file;
	FILE *wFile;
	char character;
	int counter = 0;
	int i=0;
	int stringFlag=0; //if character== " , Flag=1 
	int commentFlag=0; //if character=={ , Flag=1
	int keywordFlag=0; //if character==keyword[] , Flag=1
	char* keywords[]={"move","add","sub","out","loop","to","from","times","int","newline"}; //BigAdd Language's keyword
	char fileName[20];
	char wFileName[20];
	int k=0;
	int j=0;
	printf("Enter file name:");
    scanf("%s",fileName);
    while(fileName[k]!='\0'){
		k++;
	} // read file name -> xxx.ba
    fileName[k]='.';
    fileName[k+1]='b';
    fileName[k+2]='a';
    fileName[k+3]='\0';
    file=fopen(fileName,"r");
	if(file==NULL){
		printf("This file can not open!");
	}
	else{
		printf("Enter file name:");
	    scanf("%s",wFileName);
	    while(wFileName[j]!='\0'){ 
			j++;
		} // output file name -> xxx.lx
	    wFileName[j]='.';
	    wFileName[j+1]='l';
	    wFileName[j+2]='x';
	    wFileName[j+3]='\0';
		wFile=fopen(wFileName,"w");
		character=getc(file);
		while(character!=EOF){
			if(isdigit(character) || character=='-'){ //Is characters INT CONSTANT?
				char characters[100]= {'\0'};
				counter =0;
				characters[counter++]=character;
				character = getc(file);
				while(isdigit(character)){
					characters[counter++]=character;
					character = getc(file);
				}
				if(strcmp("-",characters)==0){
					printf("Invalid character!\n");
				}
				else{
					characters[counter]='\0';
					printf("IntConstant %s\n",characters);
					fprintf(wFile,"IntConstant %s\n",characters);
				}
					
			}
			if(isalpha(character)){ //Is characters IDENTIFIER or KEYWORD?
				char characters[20]= {'\0'};
				counter=0;
				characters[counter++]=character;
				character=getc(file);
				if(isalpha(character)){
					characters[counter++]=character;
					character=getc(file);
					while(isalpha(character)){
						characters[counter++]=character;
						character=getc(file);
					}
				}
				if(isalnum(character) || character=='_'){
					characters[counter++]=character;
					character=getc(file);
					while(isalnum(character) || character=='_'){
						characters[counter++]=character;
						character=getc(file);
					}
				}
				characters[counter]='\0';
				for(i=0;i<10;i++){
					if(strcmp(keywords[i],characters)==0){ //if characters == keyword[i]
						printf("Keyword %s\n",characters);
						fprintf(wFile,"Keyword %s\n",characters);
						keywordFlag=1;
					}
				}
				if(keywordFlag==0){ //if characters are not a keyword
					printf("Identifier %s\n",characters);
					fprintf(wFile,"Identifier %s\n",characters);
				}
				keywordFlag=0;
			}
			if(character == 34){ //Is characters STRÝNG CONSTANT?  ASCII Code=34=> character= "
				char characters[20]= {'\0'};
				counter =0;
				stringFlag=1;
				characters[counter++]=character;
				character=getc(file);
				while(character!=34){
					characters[counter++]=character;
					character=getc(file);
				}
				if(character==34&&stringFlag==1){
					characters[counter++]=character;
					characters[counter]='\0';
					stringFlag=0;
					printf("StringConstant %s\n",characters);
					fprintf(wFile,"StringConstant %s\n",characters);
				}
				if(character=='\n'&&stringFlag==1){
					printf("StringConstant did not close!\n");
				}
			}
			if(character == 46){//ASCII Code=46=> character= .
				printf("EndOfLine \n");
				fprintf(wFile,"EndOfLine \n");
			}
			if(character=='['){
				printf("OpenBlock \n");
				fprintf(wFile,"OpenBlock \n");
			}
			if(character==']'){
				printf("CloseBlock \n");
				fprintf(wFile,"CloseBlock \n");
			}
			if(character==','){
				printf("Seperator \n");
				fprintf(wFile,"Seperator \n");
			}
			if(character==123){//Is character comment? ASCII Code=123=> character= {
				commentFlag=1;
				int count=0;
				while(character!=125){ //ASCII Code=125=> character= }
					character=getc(file);
					if(character=='\n'){
						count++;
					}
					if(count==2){
						printf("This line is not a comment line!\n");
						break;
					}
				}
				if(character==125&&commentFlag==1){
					commentFlag=0;
				}					
			}
			//if character do not define the BigAdd Language
			if(character!='{'&&character!='}'&&character!=123&&character!=','&&character!=']'&&character!='['&&character!=46&&character!=34&&character!='_'&&character!='\n'&&character!=' '&&!isalnum(character)){
				printf("Invalid character! \n");
			}
			character = getc(file);
		}
	}
	return 0;
}
