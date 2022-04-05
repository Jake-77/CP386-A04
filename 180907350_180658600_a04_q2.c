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
#define EMPTY -1

typedef struct allocation //Data structures to keep track of usr input
{
    char command[100];
    char pid[100];
    int memNeeded;
    char format[20];
    int iPID;

    int firstIndex; 
    int lastIndex;
    int length;

} Allocation; //Created by maroyan

typedef struct inMem //Data structures to keep track of usr input
{
    int length;
    int startI;
    int endI;
    char pid[10];

} INMEM; //Created by maroyan

typedef struct memtrack //Data structures to keep track of usr input
{
    int holes;
    int allocated;

} MEMTRACK;

void uppercase(char *str);
void bestfit(Allocation *userArgs, int *table, const int MAX);
void freemem(Allocation *userArgs, int *table, const int MAX);
int statusOFNOTEMPTY(Allocation *userArrgs, INMEM **allocated, int *table, const int MAX);
void statusOfEmpty(int *table, const int MAX);
void printTable(int *table, const int MAX);


int globalAllocated;
INMEM *allocated = NULL;
INMEM *notAllocated = NULL;

int nAlloc_count = 0;
int alloc_count = 0;


void main(int argc, char* argv[]){
    (allocated) = (INMEM*) malloc(sizeof(INMEM) * 15);
    (notAllocated) = (INMEM*) malloc(sizeof(INMEM) * 15);

    Allocation userArrgs;
    char *ptr;
    int MAX = strtol(argv[1], &ptr, 10);
    //free(ptr);
    int memTable[MAX];

    //designate memory for the memory table  

    //init the array with -1 meaning not in use
    for (int i = 0; i < MAX; i++){
        memTable[i] = EMPTY;
    }

    printf("Allocated %d bytes of memory\n", MAX);
    char usrInput[30] = { '\0' };
    //get user input
    do {
        
        printf("command>");

        //read until usr presses enter
        fgets(usrInput, 30, stdin);
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
                userArrgs.iPID = (int) userArrgs.pid[1];
            }else if (j == 2){
                userArrgs.memNeeded = (int) atoi(token);
            }else if(j == 3){
                strcpy(userArrgs.format, token); 
                uppercase(userArrgs.format);  
            }
            j++;
            token = strtok(NULL, " ");  
        }

        if (strncmp(userArrgs.command, RQ, strlen(RQ)) == 0){
            bestfit(&userArrgs, memTable, MAX);

        }else if (strncmp(userArrgs.command, RL, strlen(RL)) == 0){
            freemem(&userArrgs, memTable, MAX);
        }else if (strncmp(userArrgs.command, STATUS, strlen(STATUS)) == 0){
            // int stat_count_allocated = statusOFNOTEMPTY(&userArrgs,&allocated, memTable, MAX);
            

            // printf("Partitions [Allocated memory = %d]:\n", allocated[0].length);
            // for (int i = 0 ; i < stat_count_allocated; i++){
            //     printf("Address [%d:%d] Process %s\n", allocated[i].startI, allocated[i].endI, allocated[i].pid);         
            // }

            // printf("Holes [Free memory = %d]\n", userArrgs.length);
            // for (int i = 0 ; i < stat_count_NA; i++){
            //     printf("Address [%d:%d] len = %d\n", notAllocated[i].startI, notAllocated[i].endI, notAllocated[i].length);         
            // }

            printf("Partitions [Allocated memory = %d]:\n", globalAllocated);
            for (int i = 0 ; i < alloc_count; i++){
                if (strcmp(allocated[i].pid, "Free") != 0){
                    printf("Address [%d:%d] Process %s\n", allocated[i].startI, allocated[i].endI, allocated[i].pid);  
                }
                       
            }

            statusOfEmpty(memTable, MAX);
            printf("Holes [Free memory = %d]\n", (MAX - globalAllocated) );
            for (int i = 0 ; i < nAlloc_count; i++){
                printf("Address [%d:%d] len = %d\n", notAllocated[i].startI, notAllocated[i].endI, notAllocated[i].length);         
            }

        }
        
        // printTable(memTable, MAX);

    } while (strncmp(userArrgs.command, EXIT, strlen(EXIT)) != 0);
    
    
    //printf("Instruction <%s> \nPID <%s> \nMEM <%d> \nFORMAT <%s> \n ", userArrgs.command, userArrgs.pid, userArrgs.memNeeded, userArrgs.format);   
}


void printTable(int *table, const int MAX){
    printf("TABLE after \n");
    for (int i = 0; i < MAX; i++){
        printf("[%c], ", table[i]);
    }
    printf("\n");
}

void uppercase(char *str){
    for (int i = 0; i < strlen(str); i++){
        if (str[i] >= 'a' && str[i] <= 'z'){
            str[i] = str[i] -32;
        }
    }
}


void bestfit(Allocation *userArgs,int *table, int MAX){ 
    //FIXMEE
    int runninCount = 0; int index = 0; int tempSize = userArgs->memNeeded; int found = 0;
    
    while (index < MAX){
        while (runninCount < tempSize){
            if ((table[index] ==  EMPTY)){
                runninCount++;
            }else {
                runninCount = 0;
                userArgs->firstIndex = index + 1;
            }
            if(runninCount == userArgs->memNeeded){
                userArgs->lastIndex = index ;
                
                found = 1;
                break;
            }
            index++;
        }
        
        index++;
        // tempSize += index;
    }

    userArgs->lastIndex++;

    if (found == 1){
        printf("Successfully allocated %d to process %s\n", userArgs->memNeeded, userArgs->pid);
        for (int j = userArgs->firstIndex; j < userArgs->lastIndex; j++){
            table[j] = userArgs->iPID;
        }

        // (allocated) = (INMEM*) malloc(sizeof(INMEM));
        allocated[alloc_count].startI = userArgs->firstIndex;
        allocated[alloc_count].endI = userArgs->lastIndex -1;
        strcpy(allocated[alloc_count].pid, userArgs->pid);
        alloc_count++;

        // printf("%d, %d \n\n", userArgs->firstIndex, userArgs->lastIndex);

        globalAllocated += (userArgs->lastIndex - userArgs->firstIndex);

    }else {
        printf("No hole of sufficient size\n");

    }
    
}

void freemem(Allocation *userArgs, int *table, const int MAX){

    int done = 0;
    int i = 0;
    int j = 0;
    while (done == 0 && i < MAX){
        if (table[i] == userArgs->iPID){
            printf("releasing memory for process %s", userArgs->pid);
            j = i;
            while (table[j] == userArgs->iPID){
                table[j] = EMPTY;
                j++;
            }
            printf("Successfully released memory for process %s", userArgs->pid);
            done = 1;
        }
        i++;
    }
    // printf("PID1 ::; %s, ::: USER PID %s", allocated[0].pid, userArgs->pid);
    for (int i = 0; i < alloc_count; i++){
        if (strncmp(allocated[i].pid, userArgs->pid, 2) == 0){
            strcpy(allocated[i].pid, "Free");
            // printf("HEREREREREER\n");
            // printf("PID1 ::; %s, ::: USER PID %s", allocated[i].pid, userArgs->pid);
        }
    }
    globalAllocated -= j;

}

void statusOfEmpty(int *table, const int MAX){
    int i = 0;
    int freeMEM = 1;
    int count = 0;

    //scan left to right
    while (i < MAX){
        if (table[i] == EMPTY){

            // (notAllocated) = (INMEM*) malloc(sizeof(INMEM));
            
            notAllocated[nAlloc_count].startI = i;

            while (table[i] == EMPTY) {
                count++;
                i++;
            }
            // userArrgs->length = freeMEM;
            notAllocated[nAlloc_count].endI = i - 1;

            notAllocated[nAlloc_count].length = ((notAllocated)[nAlloc_count].endI - (notAllocated)[nAlloc_count].startI) + 1; 
            nAlloc_count++;
            // statusCounter++;
        }
        i++;
    }
    // return statusCounter;
}
