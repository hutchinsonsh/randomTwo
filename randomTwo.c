#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//	This program builds off randomOne.c. Except instead of the sqaure method
//for finding a new random number, it's the linear congurential generator. 
//I'm using the double-linked list to store and sort numbers since I already programmed
//it and i'm planning on only going up to 200 numbers. 

struct Node
{       
        int data;
        struct Node* next;
        struct Node* prev;
};

void printList(struct Node* node);             	// prints out linked list
void printArray(int Array[], int num);		// prints out array
int addList(struct Node** node_ref, int newSeed);               // adds each seed to list

int main()
{
	int a = 1645;		// I got these values from numerical recipies on wikipedia
	int c = 101398;
	long m = pow(2, 16);		// 
	int seed = 12345;

	int i;				// for iterating
	long long temp;
	int goTill = 200;		// # of total iterations
	int gotTo = 0;
	int alreadyThere;			// checks if num has already been repeated	

	struct Node* randTwoList = NULL;                // linked list sorted numerically
        int randTwoArray[goTill];                       // array sorted chronologically

	for(i = 0; i < goTill; i++)
	{
		alreadyThere = addList(&randTwoList, seed);
		randTwoArray[i] = seed;
		if(alreadyThere == -10)
			i = goTill;
		else
		{
			temp  = (a * seed + c) % m;	// math for linear congruential generator
			gotTo++;
			seed = temp;
			if(seed < 0)			// overflow error
			{
				alreadyThere = -100;
				i = goTill;
			}
		}
	}
	
	if(alreadyThere == -100)
		printf("overflow error occured\n");
	else if(alreadyThere == -10)
		printf("\nRepeated number: %d\n", seed);
	else
		printf("\nNo repeated numbers.\nLast num = %d\n# of iterations: %d\n", seed, i);
	printList(randTwoList);
	printArray(randTwoArray, gotTo);

}

int addList(struct Node** nodeRef, int newSeed)
{
        if(*nodeRef == NULL)            // checks to see if linked list is empty
        {
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->data = newSeed;
                newNode->next = newNode->prev = newNode;
                *nodeRef = newNode;
                return 0;
        }

        struct Node *startTemp = *nodeRef;              // points to first element
        struct Node *endTemp = (*nodeRef)->prev;                // points to last element
        struct Node *addHere = (struct Node*)malloc(sizeof(struct Node));
        int endLoop = 0;

        // if replacing first element
        if(newSeed < startTemp->data)             // checks if header or not
        {
                addHere = (*nodeRef)->prev;
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode-> data = newSeed;

                newNode->next = *nodeRef;
                newNode->prev = addHere;
                addHere->next = (*nodeRef)->prev = newNode;
                *nodeRef = newNode;

                return 0;
        }
        while(endLoop == 0)
        {
                if(startTemp->data == newSeed)
                {
                        return -10;                     // already exits

                }
		if(endTemp->data == newSeed)
                        return -10;                     // already exits

                // for startTemp- 1st element onward
                if(startTemp->data < newSeed)           // move to next element
                {
                        startTemp = startTemp->next;
                        if(endTemp->data > newSeed)             // move back one element
                                endTemp = endTemp->prev;
                        else    
                        {
                                endLoop = -1;                   // exits out of loop
                                addHere = endTemp;
                        }
                }
                else
                {
                        endLoop = -1;                           // exits out of loop
                        addHere = startTemp->prev;
                }
        }

        struct Node* next = addHere->next;
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 
        newNode-> data = newSeed;

        addHere->next = newNode;                // adds in newNode between addHere and next
        newNode->prev = addHere;
        newNode->next = next;
        next->prev = newNode;

        return 0;
}


void printList(struct Node* node)
{
        printf("linked list : \n");
        struct Node *temp = node;
        while(temp->next != node)
        {
                printf("%d ", temp->data);
                temp = temp->next;
        }
        printf("%d ", temp->data);
}

void printArray(int Array[], int num)
{
        int i;
        printf("\nArray: \n");
        for(i = 0; i < num; i++)
        {
                printf("%d ", Array[i]);
        }
        printf("\n\n");
}








