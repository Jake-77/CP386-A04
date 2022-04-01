//Github login ID's: Jake-77, maroyanp --- Github Repository URL: https://github.com/Jake-77/CP386-A04

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct banker //Data structures for banker to keep track of.
{
    int available[4];
    int maximum[5][4];
    int allocation[5][4];
    int need[5][4];

} Banker; //Created by Jake-77

typedef struct userArgs
{
    char command[10];
    int CID;
    int resources[4];

} UserArgs;

void main(int argc, char *argv[]){

    Banker bank;
    bank.maximum[0][0] = 6; //Hardcoded the file input straight into maximum array
    bank.maximum[0][1] = 4;
    bank.maximum[0][2] = 7;
    bank.maximum[0][3] = 3;
    bank.maximum[1][0] = 4;
    bank.maximum[1][1] = 2;
    bank.maximum[1][2] = 3;
    bank.maximum[1][3] = 2;
    bank.maximum[2][0] = 2;
    bank.maximum[2][1] = 5;
    bank.maximum[2][2] = 3;
    bank.maximum[2][3] = 3;
    bank.maximum[3][0] = 6;
    bank.maximum[3][1] = 3;
    bank.maximum[3][2] = 3;
    bank.maximum[3][3] = 2;
    bank.maximum[4][0] = 5;
    bank.maximum[4][1] = 5;
    bank.maximum[4][2] = 7;
    bank.maximum[4][3] = 5;

    int n = 5; //# of customers
    int m = argc - 1; //# of resource types
    int k = 1;

    for(int i = 0; i < m; i++){  // Initialize available array to # of resources of each type from command line
        bank.available[i] = atoi(argv[k]);
        k++;
    }
    for(int i = 0; i < n; i++){ //Initialize allocation array with all zeros as nothings been allocated
        for(int j = 0; j < m; j++){
            bank.allocation[i][j] = 0;
        }
    }
    updateNeed(m, n, bank); // initialize need array

    printf("Number of Customers: %d\n", n);
    printf("Currently Available resources: %d ", bank.available[0]);
    for(int i = 1; i < m; i++){
        printf("%d ", bank.available[i]);
    }
    printf("\n");
    printf("Maximum resources from file:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", bank.maximum[i][j]);
        }
        printf("\n");
    }
    char commandInput[15] = { '\0' };
    int exit;

    do {
        printf("Enter Command: ");
        //scanf("%[^\n]s" , commandInput);
        //scanf("%[^\n]%*c", commandInput);
        fgets(commandInput, 15, stdin);
        printf("%s", commandInput);
        exit = 0;

        if(strncmp(commandInput, "Status", 6) == 0){

            printf("Available Resources: \n");
            for(int i = 0; i < m; i++){
                printf("%d ", bank.available[i]);
            }
            printf("\n");
            printf("Maximum Resources: ");
            printf("\n");
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    printf("%d ", bank.maximum[i][j]);
                }
                printf("\n");    
            }
            printf("Allocated Resources: ");
            printf("\n");
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    printf("%d ", bank.allocation[i][j]);
                }
                printf("\n");
            }
            printf("Need Resources: ");
            printf("\n");
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    printf("%d ", bank.need[i][j]);
                }
                printf("\n");
            }
        }
        else if (strncmp(commandInput, "Run", 3) == 0){
            printf("not finished");
        }
        else if(strncmp(commandInput, "Exit", 4) == 0){
            exit = 1;
        }
        else{// if an error in here need to say wrong command
            char *token;
            token = strtok(commandInput, " ");
            int j = 0;
            int k = 0;
            UserArgs arguments;

            while(token != NULL){

                if(j == 0){
                    strcpy(arguments.command, token);
                }
                else if(j == 1){
                    arguments.CID = atoi(token);
                }
                else{
                    arguments.resources[k] = atoi(token);
                    k += 1;
                }
                j += 1;
                token = strtok(NULL, " ");
            }

            if(strncmp(arguments.command, "RQ", 2) == 0){
                printf("not finished");
            }
            else if(strncmp(arguments.command, "RL", 2) == 0){
                printf("not finished");
            }
        }
    }while(exit != 1);
}

void updateNeed(int m, int n, Banker b){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            b.need[i][j] = b.maximum[i][j] - b.allocation[i][j];
        }
    }
}

int safety(int m, int n, Banker b){

    int Work[m];
    int Finish[n];

    for(int i = 0; i < m; i++){
        Work[i] = b.available[i];
    }
    for (int j = 0; j < n; j++) {
        Finish[j] = 0;
    }

    int c = 0;
    int safe;
    int enough;
    while(c < n){
        safe = 0;
        for (int i = 0; i < n; i++){
            if(Finish[i] == 0){
                enough = 0;
                for(int j = 0; j < m; j++){
                    if(b.need[i][j] <= Work[j]){
                        enough += 1;
                    }
                }
                if(enough == m){
                    for(int k = 0; k < m; k++){
                        Work[k] += b.allocation[i][k];
                    }
                    Finish[i] = 1;
                    c += 1;
                    safe = 1;
                }
            } 
        }
        if (safe == 0){
            return safe;
        }
    }
    return safe;
}

