/*
----------------------------------------------------
GITHUB NAMES:
    maroyanp
    Jake-77
-----------------------------------------------------
GITHUB URL:
    https://github.com/Jake-77/CP386-A04.git
-----------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RQ "RQ"
#define RL "RL"
#define STATUS "STATUS"
#define EXIT "EXIT"


typedef struct allocation //Data structures to keep track of usr input
{
    char command[100];
    char pid[100];
    int memNeeded;
    char format[20];
} Allocation; //Created by maroyan

void uppercase(char *str);
void bestfit(char *pid, int size, int *table, const int MAX);


void main(int argc, char* argv[]){

    Allocation userArrgs;
    char *ptr;
    const int MAX = strtol(argv[1], &ptr, 10);

    //designate memory for the memory table 
    int *memTable = (int *) malloc (MAX * sizeof(int));

    //init the array with -1 meaning not in use
    for (int i = 0; i < MAX; i++){
        memTable[i] = -1;
    }
    printf("Allocated %d bytes of memory\n", MAX);

    //get user input
    
    char usrInput[100];
    printf("command>");

    //read until usr presses enter
    // scanf("%99[^\n]"    
    scanf("%1000[^\n]" , usrInput);
    char *token;
    token = strtok(usrInput, " ");
    int j = 0;

    while (token != NULL){
        if (j == 0){
            strcpy(userArrgs.command, token);
            uppercase(userArrgs.command);
        }else if (j == 1){
            strcpy(userArrgs.pid, token);
            uppercase(userArrgs.pid);
        }else if (j == 2){
            userArrgs.memNeeded = (int) atoi(token);
        }else if(j == 3){
            strcpy(userArrgs.format, token);   
        }            
        j++;
        token = strtok(NULL, " ");  
    }



    if (strcmp(userArrgs.command, RQ) == 0){
        bestfit(userArrgs.pid, userArrgs.memNeeded, memTable, MAX);
    }else if (strcmp(userArrgs.command, RL) == 0){
        
    }




    //printf("Instruction <%s> \nPID <%s> \nMEM <%d> \nFORMAT <%s> \n ", userArrgs.command, userArrgs.pid, userArrgs.memNeeded, userArrgs.format);
        
    
}

void uppercase(char *str){
    for (int i = 0; i < strlen(str); i++){
        if (str[i] >= 'a' && str[i] <= 'z'){
            str[i] = str[i] -32;
        }
    }
}

void bestfit(char *pid, int size, int *table, const int MAX){

    int found = 0; int index = 0; int tempSize = size; int b_fit = 0; 

    while (found != 1 && tempSize < MAX){
        if (tempSize < MAX){
            for (int i = index; i < tempSize; i++){
                if (table[i] == -1){
                    b_fit = 1;
                }
            }
            if (b_fit == 1){
                for (int i = index; i < tempSize; i++){
                    table[i] = (int) pid[1]; 
                }
                found = 1;
                printf("Successfully allocated %d to process %s\n", size, pid);
            }
        }else{
            printf("NO hole of sufficient size\n");
        }
        index += tempSize;
        tempSize += tempSize;
    }
}
