//Elizabeth Koshelev
//12/10/16
//This code implements a circular queue and a hash table to solve a sliding tile puzzle.
//Known bugs: it runs an infinite loop for the original puzzle (assuming because the hash function is incorrect), but works for the AB puzzle. After it completes the puzzle the program has an error, and the code for computing hash buckets stats is wrong so it is commented out.

#include<stdio.h>
#include <stdlib.h>
#include "Puzzle.h"
#include "Output.h"


/*Make the position structure, using the suggested code from P1*/
typedef struct pnode {
     struct pnode *next; /*next pointer for the hash bucket*/
     struct pnode *back; /*position from which this one came*/
     int cost; /*number of moves to get to this position*/
     char piece; /*piece that moved to this position*/
     int dir; /*direction moved to enter this position*/
     char board[BoardSize-1]; /*this position's board*/
} *Board;

//Constants:
int costtemp=0;
Board hashArray[HashArraySize];
int front = -1;
int rear = -1;
int size = QueueArraySize;
Board q[QueueArraySize];
int temparraysize;
int maxarraysize;


//Allocate space for the board
Board allocate() {
Board p = malloc(sizeof(struct pnode));
    if (p==NULL) {
        printf("Malloc failed."); exit(1);
    }
    return p;
}

//Make the board using a string, swap two values if necessary, and calculate the cost of implementing a certain move
Board makeBoard(char * UniqueBoard,int x, int y,int cost){
    char *src = UniqueBoard;
   Board Starting = allocate();
   Starting->cost=cost;
   Starting->piece= NULL;
    Starting->dir = 0;
    copyString(Starting->board,src); //Use a method to copy the string to the string array in the board
    char temp = Starting->board[y]; //Swap two values if necessary
    Starting->board[y] =Starting->board[x];
    Starting->board[x] = temp;
    return Starting;
}

//Copy a pointer string to a string array
void copyString(char one[], char * two){
    int i;
    for ( i = 0; i < BoardSize; i++) {
        one[i] = two[i];
    }
}

//Check if two boards are equal
int checkEqual(Board one, Board two){
    int check=1;
    int i;
    for(i = 0; i < BoardSize; i++){
        if(one->board[i] != two->board[i]){
            check = 0;
            i=BoardSize;
        }
    }
   return check;
}

//Function to print a board
void printBoard(Board one){
    int i;
    for (i = 0; i < BoardHeight; i++) {
            printf("%.*s\n ",BoardWidth, one->board + i*BoardWidth);
    }
   printf("\n");
}

// HASH TABLE CODE:

//The hash function code
int hashCode(Board data) {
    int z;
    z = 128*(data->board[1]+  data->board[2]+  data->board[3]+  data->board[4]+  data->board[5]+  data->board[6]+ data->board[7])%HashArraySize;
    return z;
}

//Code to insert a value into a hash table
void insert(Board data) {
    int j;
    int x = hashCode(data);
    if (hashArray[x] == NULL) {
        data->next = NULL;
        hashArray[x] = data;
        } else{
        data->next=hashArray[x];
        hashArray[x] = data;
    }
}

//Code to search for a value and return a value determining whether or note it exists
int search(Board data) {
    int j = hashCode(data);
         if (hashArray[j]==NULL){
            return 0;
         } else {
             Board check = hashArray[j];
             while (check != NULL){
                 if (checkEqual(check,data)==1){
                    return 1;
                 } else{
                     check = check->next;
                }
             }
         }
         return 0;
}

//Queue Code

//Code to enqueue a value
void enqueue(Board data) {
    if( (front==rear+1) || (front == 0 && rear == size-1)) {
        printf("Queue overflowed");
        exit(1);
    }
    else{
        if(front==-1){
            front=0;
        }
        rear=(rear+1) % size;
        q[rear]=data;
    }
}

//Code to dequeue a value
Board  dequeue()
{
   Board temp;
    if(front== -1 ){
    printf("Queue underflowed");
    return(temp);
    } else
    {
        temp=q[front];
        if(front==rear){
            front=-1;
            rear=-1;
        } else
            front=(front+1) % size;
            return(temp);
    }
}

//Code to search for the ending value in hash table
Board searchEnd(Board temp){
    int key = hashCode(temp);
    Board check = hashArray[key];
    while(checkEqual(check,temp)==0){
        check = check->next;
    }
    return check;
}



//Code to reverse the pointers for the solution
int printString(){
    int j;
    int helements=0;
    int biggestbucket=0;
    int arraysize[50];
    for (j = 0; j < BoardSize; j++) {
        int tempbucket=0;
        if(hashArray[j]!=NULL){
            helements++;
            Board check = hashArray[j];
             while (check != NULL){
                tempbucket++;
                arraysize[tempbucket]++;
                check = check->next;

             }
        }
        if (tempbucket>biggestbucket){
            biggestbucket=tempbucket;
        }
    }
    Board Goal  = makeBoard(GoalBoard,1,1,1);
    Board Starting  = makeBoard(StartBoard,1,1,1);
    Board y = searchEnd(Goal);
    Board x = NULL;
    Board z = NULL;
    int counter = 0;
    while (y!=NULL ) {
        z = (y->back);
        y->back = x;
        x = y;
        y = z;
        counter++;
        if (counter>16)
            OutputPosition(y->board,(counter-17),y->piece,y->dir);
            if (checkEqual(y,Goal)){
                QueueStats(QueueArraySize,maxarraysize,front,rear);
                HashStats(HashArraySize,helements,biggestbucket);
                int i;
//                for (i=0; i<=sizeof arraysize; i++){ Bucket Stats
//                    if (arraysize[i]!=0){
//                        BucketStat(i,arraysize[i]);
//                    }
//                }
                return 1;
            }
    }
}

//Main method that makes moves and implements the algorithm
int main(){
    Board Starting= makeBoard(StartBoard,1,1,costtemp);
    costtemp++;
    Board Goal  = makeBoard(GoalBoard,1,1,1);
    temparraysize=0;
    printf("%d \n",1);
    enqueue(Starting);
    temparraysize++;
    insert(Starting);
    int j;
    while (search(Goal)==0){
        if (temparraysize>maxarraysize){
            maxarraysize=temparraysize;
        }
        Board start = dequeue();
        temparraysize--;
        if (checkEqual(start,Goal)!=1){
            costtemp++;
            for (j = 0; j < BoardSize; j++) {
                if (start->board[j]==SymbolBlank){
                    int pos1 = j-BoardWidth;
                    int pos2 = j+BoardWidth;
                    int pos3 = j+1;
                    int pos4 = j-1;
                    if (pos1>=0 && start->board[pos1]!=SymbolFixed && start->board[pos1]!=SymbolBlank){
                        Board temp1= makeBoard(start->board,pos1,j,costtemp);
                        temp1->back=start;
                        if (search(temp1)==0){
                            temp1->piece=start->board[pos1];
                            temp1->dir=2;
                            enqueue(temp1);
                            temparraysize++;
                            insert(temp1);
                        }
                    }
                    if (pos2<BoardSize && start->board[pos2]!=SymbolFixed && start->board[pos2]!=SymbolBlank){
                        Board temp2= makeBoard(start->board,pos2,j,costtemp);
                        temp2->back=start;
                        if (search(temp2)==0){
                            temp2->piece=start->board[pos2];
                            temp2->dir=0;
                            enqueue(temp2);
                            temparraysize++;
                            insert(temp2);
                        }
                    }
                    if (j%(BoardWidth)!=(BoardWidth-1)  && start->board[pos3]!=SymbolFixed && start->board[pos3]!=SymbolBlank){
                        Board temp3= makeBoard(start->board,pos3,j,costtemp);
                        temp3->back=start;
                        if (search(temp3)==0){
                            temp3->piece=start->board[pos3];
                            temp3->dir=3;
                            enqueue(temp3);
                            temparraysize++;
                            insert(temp3);
                        }
                    }
                  if (j%(BoardWidth)!=0  && start->board[pos4]!=SymbolFixed && start->board[pos4]!=SymbolBlank){
                        Board temp4= makeBoard(start->board,pos4,j,costtemp);
                        temp4->back=start;
                        if (search(temp4)==0){
                            temp4->piece=start->board[pos4];
                            temp4->dir=1;
                            enqueue(temp4);
                            temparraysize++;
                            insert(temp4);
                        }
                    }

                }
            }
        }
    }
    printString();
    return 1;
}
