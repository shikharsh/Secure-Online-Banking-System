#include"functions.h"

//Creates a customer node
CUST *newNode(ID id,CHOICES choice)
{
	CUST *newCustomer = ALLOCATE_MEMORY(CUST);
	newCustomer->id = id;
	newCustomer->choice = choice;
	newCustomer->next = NULL;
	return newCustomer;
}


//to store the value of the users in the queue
BANKQUEUE *createQueue()
{
	BANKQUEUE *q = ALLOCATE_MEMORY(BANKQUEUE); 
	if (q != NULL)
        {
		q->front = NULL;
		q->rear = NULL;
	} 
	return q; 
}

// The function to add a customer to the customerqueue
void enQueue(BANKQUEUE *q, ID CUSTid, CHOICES choice) 
{ 
    CUST *temp = newNode(CUSTid,choice); 

    if (temp != NULL)
    {
        // If queue is empty, then new node ispointed by both front and rear 
        if (q->rear == NULL) 
        { 
            q->front = temp;
		q->rear = temp;
	} 
	else
	{
     // Add the new node at the end of queue andchange rear 
            q->rear->next = temp; 
            q->rear = temp;
	}
    }
    else
    {
        PRINT_ERROR("Unable to create the node");
        exit (1);
    }
}


// Function to remove a key from customer queue 
void deQueue(BANKQUEUE* q) 
{ 

    // If queue is empty, return NULL. 
	if (q->front == NULL) 
	return ; 

    // Store previous front and move front one nodeahead 
	CUST* temp = q->front;

    /*called the task function, that will take theCUST id and the choice and perform tasks*/
	task(q->front); 
	
        q->front = q->front->next; 

    // If front becomes NULL, then change rear alsoas NULL 
	q->rear = (q->front == NULL)? NULL: q->rear;
	free(temp);	
} 

void show_queue (BANKQUEUE *q)
{
    CUST *tmp;

    if (q != NULL)
    {
        printf("Customers in Queue :");
	LOOP_Queue(tmp,q->front,NULL)
	{	
			printf("%d  ", tmp->id);
        }
	printf("\n");

    }
}

errno_t checkCorrectNumValue(char number[])
{
	LENGTH len = strlen(number);
	ITERATOR i;
	LOOP(i,0,len-1)
	{
		if(NOT_NUMBER_CONDITIONS(number[i]))
		{
			return 0;
		}
	}
	return 1;
}

errno_t task(CUST* CUSTomer)
{
	VAR_STRING buff;
	if(CUSTomer->id == 0) take_string_inp(buff,sizeof(buff));
	char CUSTChoice = CUSTomer->choice;
	AMOUNT(amt);
	if(CUSTChoice == Depo)
	{
		printf("\nEnter the amount you want to deposit(Rs) :\t");
		take_string_inp(amt, sizeof(amt));
		
		while(!checkCorrectNumValue(amt))
		{
			printf("\n!!ENTER CORRECT AMOUNT!!\nEnter the amount number you want to deposit(Rs) :\t");
			take_string_inp(amt, sizeof(amt));
		}
		printf("\nRs %s is deposited.\n",amt);
	}
	else if(CUSTChoice == Withd)
	{
		printf("\nEnter the amount you want to withdraw(Rs) :\t");
		take_string_inp(amt, sizeof(amt));
		
		while(!checkCorrectNumValue(amt))
		{
			printf("\n!!ENTER CORRECT AMOUNT!!\nEnter the amount you want to withdraw(Rs) :\t");
			take_string_inp(amt, sizeof(amt));
		}
		printf("\nRs %s is withdrawn\n",amt);
	}
	else if(CUSTChoice == Trans)
	{
		ACCOUNT(accNo);
		printf("\nEnter the account number you want to send to:\t");
		take_string_inp(accNo, sizeof(accNo));
		
		while(!checkCorrectNumValue(accNo))
		{
			printf("\n!!ENTER CORRECT ACCOUNT NUMBER!!\nEnter the account number you want to send to:\t");
			take_string_inp(accNo, sizeof(accNo));
		}
		printf("\nEnter the amount you want to send(Rs) :\t");
		take_string_inp(amt, sizeof(amt));
		
		printf("\nRs %s is sent to acc no. %s",amt,accNo);
	}
	else
	{
		return -1;
	}
	
	return 0;
}

/*inline*/ double calc_time(TIME time)
{
	double time_taken = ((double)time)/CLOCKS_PER_SEC;
	return time_taken;
}


errno_t time_delay(SECONDS delay_in_seconds) 
{ 
        // Converting time delay into milli seconds 
	SECONDS milSeconds = sec_to_mil(delay_in_seconds); 
	TIME start_time = STORE_TIME; 
	if(start_time == -1)
	{
		return -1;
	}
	while (STORE_TIME < start_time + milSeconds);
	
	return 0; 
} 


errno_t inpLine (VAR_STRING buff, SIZE sz) 
{
    int ch;
    errno_t extra = 0;

    // Get line with buffer overrun protection.
    fgets(buff, sz, stdin);
    if (buff == NULL)
        return NO_INPUT;

    if (buff[strlen(buff)-1] != '\n' ) 
    {
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;

        return (extra == 1) ? TOO_LONG : OK;
    }

    buff[strlen(buff)-1] = '\0';
    return OK;
}

errno_t take_string_inp(VAR_STRING buff, SIZE sz)
{
    if(buff == NULL || sz == 0) return -1;
    errno_t flag = inpLine(buff, sz);
    while(flag != OK)
    {
	if(flag == NO_INPUT)
	{ 
		PRINT_ERROR("!!NO INPUT!!");
	}
	else if( flag == TOO_LONG)
	{
		PRINT_ERROR("!!TOO LONG!!");
	}
	
	printf("\nTRY AGAIN:");
	flag = inpLine(buff,sz);	
    }
	return 0;
}
