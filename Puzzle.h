/*************************************************************************************/
/*AB Test Puzzle                                                                     */
/*************************************************************************************/

/*Special symbols.*/
#define SymbolBlank '.' /*Symbol that denotes a blank square.*/
#define SymbolFixed '$' /*Symbol that cannot move.*/

/*Board dimensiona.*/
#define BoardHeight 3
#define BoardWidth  3
#define BoardSize   9

/*Start position.*/
/* A B $ */
/* $ . . */
/* $ . $ */
#define StartBoard "AB$$..$.$"

/*Goal position.*/
/* B A $ */
/* $ . . */
/* $ . $ */
#define GoalBoard  "BA$$..$.$"

/*Number of moves in a minimal length solution for this puzzle,*/
/*   where one move is defined as s moving a piece vertically or horizontally*/
/*   to an adjacent unoccupied square (and the SymbolFixed piece cannot move).*/
#define MinSolution 10

/*Data structure parameters.*/
#define QueueArraySize 25 /*Queue goes from 0 to QueueArraySize-1.*/
#define HashArraySize 23  /*Hash table goes from 0 to HashArraySize-1.*/
#define HashStatsMAX 10   /*Max number of hash bucket size statistics to keep.*/
