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


typedef struct allocation //Data structures for banker to keep track of.
{
    char command[100];
    char pid[100];
    int memNeeded;
    char format[20];
} Allocation; //Created by Jake-77


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

    // do{
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
            }else if (j == 1){
                strcpy(userArrgs.pid, token);
            }else if (j == 2){
                userArrgs.memNeeded = (int) atoi(token);
            }else if(j == 3){
                strcpy(userArrgs.format, token);   
            }            
            j++;
            token = strtok(NULL, " ");  
        }

        printf("Instruction <%s> \nPID <%s> \nMEM <%d> \nFORMAT <%s> \n ", userArrgs.command, userArrgs.pid, userArrgs.memNeeded, userArrgs.format);
        
    // }while (1);

}
