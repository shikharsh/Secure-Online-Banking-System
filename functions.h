#include "headers.h"

#define insert_dummy(x) enQueue((x),0,0)
#define STRING_TO_NUM(x) atoi(x)
#define PRINT_ERROR(X) fprintf(stderr,X)
#define ALLOCATE_MEMORY(type) (void*)malloc(sizeof(type))

#define CLEAR_SCREEN system("cls")
#define STORE_TIME clock()
#define sec_to_mil(secs) ((Sec_Mil) * (secs))
#define FIND_TIME_SPENT STORE_TIME - time

#define LOOP(x,y,z) for((x) = (y); (x)<=(z); ++(x))
#define LOOP_Queue(x,y,z) for((x) = (y); (x)!=(z); (x) = (x->next))

#define CHOICE_CONDITIONS(choice) ((choice) == '1' || (choice) == '2' || (choice) == '3')
#define NOT_NUMBER_CONDITIONS(X) ((X)<'0' || (X)>'9')

#define errno_t int
#define LENGTH int
#define COUNT int
#define ITERATOR int

#define AMOUNT(X) char X[MAX_AMOUNT_DIGITS+1]
#define ACCOUNT(X) char X[MAX_ACCOUNT_DIGITS+1]

enum {OK = 0, NO_INPUT = 1, TOO_LONG = 2};
enum {Sec_Mil = 1000, MAX_AMOUNT_DIGITS = 9, MAX_ACCOUNT_DIGITS = 15};

typedef float SECONDS;
typedef int ID;
typedef enum{Depo = '1', Withd = '2', Trans = '3'} CHOICES;
typedef char* VAR_STRING;
typedef clock_t TIME;
typedef size_t SIZE;
typedef struct CUSTomerNode
{
	CHOICES choice;
	ID id;
	struct CUSTomerNode *next; 
}CUST;

//structure for the queue that will provide the multi user interface
typedef struct Bankqueue
{
	CUST *front;
	CUST *rear;
}BANKQUEUE;

//Creates a customer node
CUST *newNode(ID,CHOICES);

//to store the value of the users in the queue
BANKQUEUE *createQueue();

// The function to add a customer to the customerqueue
void enQueue(BANKQUEUE*, ID, CHOICES); 

// Function to remove a key from given queue q 
void deQueue(BANKQUEUE*);

void show_queue (BANKQUEUE*); 

//Performs the respective task
errno_t task(CUST*);

//secured string input
errno_t inpLine (VAR_STRING, SIZE);

//function for calling getLine while checking forerrors
errno_t take_string_inp(VAR_STRING, SIZE); 


//Calculates time in seconds
/*inline*/ double calc_time(TIME);

//Gives a delay between functions
errno_t time_delay(float);

// Checks for valid entry of number of customers
errno_t checkCorrectNumValue(VAR_STRING);
