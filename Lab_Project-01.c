#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define size 100
int playerScore=0,computerScore=0,drawScore=0;
int resultArray[size];
int roundNumber=0;
int stack[size];
int top=-1;
int queue[size];
int rear=-1;
int front=0;
struct Match
{
    int round;
    int playerMove;
    int computerMove;
    int result;

    struct Match *next;
};
struct Match *head = NULL;
void push(int value);
int pop(void);
void enqueue(int move);
void insertMatch(int round, int playerMove, int computerMove, int result);
const char* resultName(int r);
const char* moveName(int m){
    if(m==1) return "Rock";
    if(m==2) return "Paper";
    return "Scissors";
}
const char* resultName(int r){
    if(r == 0) return "Draw";
    if(r == 1) return "Player Wins";
    return "Computer Wins";
}
void newGame()
{
    int playerMove;
    int computerMove;
    int result;

    printf("\n==============================\n");
    printf("         NEW GAME\n");
    printf("==============================\n");

    printf("1. Rock\n");
    printf("2. Paper\n");
    printf("3. Scissors\n");

    printf("\nEnter Your Move : ");
    scanf("%d",&playerMove);

    if(playerMove < 1 || playerMove > 3)
    {
        printf("\nInvalid Move!\n");
        return;
    }

    computerMove = rand()%3 + 1;

    printf("\n------------------------------\n");
    printf("Your Move     : %s\n", moveName(playerMove));
    printf("Computer Move : %s\n", moveName(computerMove));
    printf("------------------------------\n");

    if(playerMove == computerMove)
    {
        result = 0;
        drawScore++;

        printf("Result : Draw\n");
    }
    else if(
            (playerMove == 1 && computerMove == 3) ||
            (playerMove == 2 && computerMove == 1) ||
            (playerMove == 3 && computerMove == 2)
           )
    {
        result = 1;
        playerScore++;

        printf("Result : Player Wins!\n");
    }
    else
    {
        result = 2;
        computerScore++;

        printf("Result : Computer Wins!\n");
    }
    roundNumber++;
    resultArray[roundNumber-1] = result;
    push(result);
    enqueue(computerMove);
    insertMatch(
        roundNumber,
        playerMove,
        computerMove,
        result
    );

    printf("\nRound Saved Successfully!\n");
}
void insertMatch(int round, int playerMove, int computerMove, int result)
{
    struct Match *newNode, *temp;

    newNode = (struct Match*)malloc(sizeof(struct Match));

    newNode->round = round;
    newNode->playerMove = playerMove;
    newNode->computerMove = computerMove;
    newNode->result = result;
    newNode->next = NULL;

    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}
void showMatchHistory()
{
    struct Match *temp;

    if(head == NULL)
    {
        printf("\n=================================\n");
        printf("No Match History Available!\n");
        printf("=================================\n");
        return;
    }

    temp = head;

    printf("\n========================================\n");
    printf("           MATCH HISTORY\n");
    printf("========================================\n");

    while(temp != NULL)
    {
        printf("\nRound          : %d\n", temp->round);

        printf("Player Move    : %s\n",
               moveName(temp->playerMove));

        printf("Computer Move  : %s\n",
               moveName(temp->computerMove));

        printf("Result         : %s\n",
               resultName(temp->result));

        printf("----------------------------------------\n");

        temp = temp->next;
    }
}
void deleteLastMatch()
{
    struct Match *temp;
    struct Match *prev;
    if(head == NULL)
    {
        return;
    }
    if(head->next == NULL)
    {
        free(head);
        head = NULL;
        return;
    }
    temp = head;
    while(temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    free(temp);
}
void undoLastRound()
{
    int lastResult;

    if(roundNumber == 0)
    {
        printf("\nNo Round Available!\n");
        return;
    }
    lastResult = pop();
    if(lastResult == -1)
    {
        printf("\nNothing To Undo!\n");
        return;
    }
    if(lastResult == 0)
    {
        drawScore--;
    }
    else if(lastResult == 1)
    {
        playerScore--;
    }
    else
    {
        computerScore--;
    }
    resultArray[roundNumber-1] = -1;
    if(rear >= front)
    {
        rear--;
    }
    deleteLastMatch();
    roundNumber--;
    printf("\n=================================\n");
    printf("Last Round Removed Successfully!\n");
    printf("=================================\n");
}
void showMoveQueue()
{
    int i;

    if(front > rear)
    {
        printf("\n=================================\n");
        printf("No Computer Moves Available!\n");
        printf("=================================\n");
        return;
    }
    printf("\n========================================\n");
    printf("        COMPUTER MOVE QUEUE\n");
    printf("========================================\n");

    for(i = front; i <= rear; i++)
    {
        printf("Round %d : %s\n",
               i + 1,
               moveName(queue[i]));
    }
    printf("========================================\n");
}
void showScoreBoard()
{
    printf("\n=================================\n");
    printf("          SCORE BOARD\n");
    printf("=================================\n");

    printf("Player Wins   : %d\n", playerScore);
    printf("Computer Wins : %d\n", computerScore);
    printf("Draws         : %d\n", drawScore);

    printf("=================================\n");
}
void push(int value)
{
    if(top == size-1)
    {
        printf("\nStack Overflow!\n");
        return;
    }

    top++;

    stack[top] = value;
}
int pop()
{
    if(top == -1)
    {
        return -1;
    }

    return stack[top--];
}
void enqueue(int move)
{
    if(rear == size-1)
    {
        printf("\nQueue Full!\n");
        return;
    }

    rear++;

    queue[rear] = move;
}

int main(){
int choice;
srand(time(NULL));
 while(1)
    {
        printf("\n=====================================\n");
        printf("   ROCK PAPER SCISSORS GAME\n");
        printf("=====================================\n");

        printf("1. New Game\n");
        printf("2. Match History\n");
        printf("3. Undo Last Round\n");
        printf("4. Show Move Queue\n");
        printf("5. Show Score Board\n");
        printf("6. Exit\n");

        printf("\nEnter Choice : ");

    scanf("%d",&choice);
switch(choice)
        {
            case 1:
                newGame();
                break;

            case 2:
                showMatchHistory();
                break;

            case 3:
                undoLastRound();
                break;

            case 4:
                showMoveQueue();
                break;

            case 5:
                showScoreBoard();
                break;

            case 6:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}