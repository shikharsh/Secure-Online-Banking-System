#include"functions.h"

int main(int argc, char** argv)
{
	errno_t (*check)(VAR_STRING);
	
	CLEAR_SCREEN;
	printf("KIPU BANK\n");
	printf("***********\n");
	
	VAR_STRING cust_nums;
	
	printf("\nHow many customers are there in the queue?\n");
	scanf("%s",cust_nums);
	
	check = &checkCorrectNumValue;
	//checks for valid input
	errno_t success_flag = check(cust_nums);
	if(success_flag == 0)
	{
		PRINT_ERROR("Not a valid numerical value. Exiting...");
		time_delay(1);
		exit(-1);
	}
	
	COUNT no_of_customers = STRING_TO_NUM(cust_nums), CUST_id;
	
	//creates the queue
	BANKQUEUE* entryQueue = createQueue();
        insert_dummy(entryQueue);
	
	//interface for each user
	LOOP(CUST_id,1,no_of_customers)
	{
		CLEAR_SCREEN;
		printf("KIPU BANK\n");
		printf("***********\n");
		printf("\nWhat do you want to do?[MAKE A CHOICE]\n");
		printf("1.Deposit Cash\n2.Withdraw Cash\n3.Transfer Money\n");
		
		printf("\nCustomer %d\n", CUST_id);
		printf("************\n");
		char choice;
		printf("YOUR CHOICE[1/2/3]: ");
		choice = getche();
		
		//checks for valid choice input
		if(CHOICE_CONDITIONS(choice))
		{
			enQueue(entryQueue,CUST_id, choice);
			printf("\nYour Customer id is %d\n\n",CUST_id);
		}
		else
		{
			printf("\n!!ENTER VALID CHOICE!!\n");
			CUST_id--;
		}
		time_delay(1);
	}
printf("**************************************************************\n");
	deQueue(entryQueue);
		
	LOOP(CUST_id,1,no_of_customers)
	{
		CLEAR_SCREEN;
		printf("KIPU BANK\n");
		printf("***********\n");
		show_queue(entryQueue);
		TIME time; 
		time = STORE_TIME;       
//calculates time at start
		deQueue(entryQueue);
		time = FIND_TIME_SPENT;        
 //total time spent
		
		printf("\nTIME TAKEN: %f seconds\n", calc_time(time));
		time_delay(2);
	}
	
	return 0;
}
