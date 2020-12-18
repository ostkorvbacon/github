#define _POSIX_C_SOURCE 199309L
#include "analyze.h"
#include "algorithm.h"
/*#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>*/

#define NUMBEL 512 //The size of the array is determinded by NUMBEL*2^n
#define REP 1
#define REP2 1
#define KEY 6
#define NOTKEY 7

//
// Private
//


//
// Public

//

// Funktion that creates the best scenario for quicksort.
 void createBest(int *arr, int startPos, int sizeTemp, int startVal) {
    if (sizeTemp == 0)
        return;

    if (sizeTemp == 1)
    {
        arr[startPos] = startVal;

    }

    int sizeTemp1 = sizeTemp / 2;
    int sizeTemp2 = sizeTemp - sizeTemp1 - 1;
    int pivot_value_index = startPos + sizeTemp1;
    int pivotVal = startVal + sizeTemp1;

    createBest(arr, startPos, sizeTemp1, startVal);
    createBest(arr, pivot_value_index, sizeTemp2, pivotVal+1);
    arr[startPos + sizeTemp - 1] = pivotVal;
}

// Calls the funktion that creates the best array for quicksort
void GenerateBestCaseQuickSort(int *arr,int n)
{
    createBest(arr, 0, n, 1);

}

//Funktion that creates needed condition for best worst and average scenarios and saves time it takes for the algorithms to execute.
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
	double bursttime=0,times;
	int size;
	int arr[NUMBEL*((int)pow(2,n))];
	int i,k,m,temp;
	time_t t;
	clock_t start, stop;

	srand((unsigned) time(&t)); //Needed to use clock funktion.
	printf("Algorithm: ");
	if(a == bubble_sort_t) printf("Bubble sort"); //Prints what algorithm used.
	else if (a==insertion_sort_t) printf("Insertion sort");
	else if(a==quick_sort_t) printf("Quick sort");
	else if(a == linear_search_t) printf("Linear search");
	else printf("Binary search");

	printf("\tScenario: ");
	if(c == average_t) printf("Average\n"); //Prints what scenario used.
	else if(c == best_t) printf("Best\n");
	else printf("Worst\n");


	for(int j = 0; j < n; j++)
	{
		bursttime = 0; // Resets bursttime.
		size = NUMBEL*((int)pow(2,j)); // Calculates size of array.

		for(k = 0; k < REP; k++)
		{
			if(a == bubble_sort_t) // Enters here if Bubble sort was chosen in ui.c
			{
				if(c == average_t) for(i = 0; i < size; i++){arr[i] = rand()%size;} //Creates array that emulates average scenario.

				else if(c == best_t) for(i = 0; i < size; i++){arr[i] = i;} //Creates array that emulates best scenario.

				else for(i=0; i < size;i++){arr[i] = size-i;} //Creates array that emulates worst scenario.

				start = clock(); //Saves the time before algorithm is called.

				bubble_sort(arr, size);

				stop = clock(); //Saves the time after the algorithm has executed.
			}

			else if(a==insertion_sort_t) // Enters here if insertion sort was chosen in ui.c
			{
				if(c==average_t) for(i=0; i<size; i++) arr[i]=rand()%size; //Creates array that emulates average scenario.

				else if(c==best_t) for(i=0; i<size; i++) arr[i]=i; //Creates array that emulates best scenario.

				else for(i=0; i<size; i++) {arr[i]=size-i;} //Creates array that emulates worst scenario.

				start=clock(); //Saves the time before algorithm is called.

				insertion_sort(arr,size);

				stop=clock(); //Saves the time after the algorithm has executed.
			}
			else if(a==quick_sort_t) // Enters here if Quicksort was chosen in ui.c
			{
				if(c==average_t) for(i=0;i<size;i++) arr[i]=rand()%size; //Creates array that emulates average scenario.

				else if(c==best_t) GenerateBestCaseQuickSort(arr,size); //Creates array that emulates best scenario.

				else for(i=0;i<size;i++) {arr[i]=i+1;} //Creates array that emulates worst scenario.

				start = clock(); //Saves the time before algorithm is called.

				quick_sort(arr,size);

				stop = clock(); //Saves the time after the algorithm has executed.
			}

			else if(a == linear_search_t) // Enters here if linear search was chosen in ui.c
			{
				if(c == average_t) for(i=0;i<size;i++) arr[i]=rand()%size; //Creates array that emulates average scenario.

				else if(c == best_t) arr[0]=KEY; //Creates array that emulates best scenario.

				else for(i=0; i<size; i++) arr[i]=NOTKEY; //Creates array that emulates worst scenario.

				start = clock(); //Saves the time before algorithm is called.

				for (m=0;m<REP2;m++) linear_search(arr, size,KEY); // Calls the funktion REP2 times to get better test results.

				stop=clock(); //Saves the time after the algorithm has executed REP2 times.
			}
			else // Enters here if binary search was chosen in ui.c
			{

				if(c==average_t) for(i=0;i<size;i++) //Creates array that emulates average scenario and then calls the algorith funktion.
				{
					arr[i] = rand()%size;
					insertion_sort(arr,size);
				}
				else if(c==best_t) arr[(size-1)/2]=KEY; //Creates array that emulates best scenario.

				else for(i=0;i<size;i++) //Creates array that emulates worst scenario.
        {
					temp=rand()%size;
					if (temp==KEY) temp=NOTKEY;
					arr[i]=temp;
				}

				start=clock(); //Saves the time before algorithm is called.

				for (m=0;m<REP2;m++) binary_search(arr,size,KEY); // Calls the funktion REP2 times to get better test results.

				stop=clock(); //Saves the time after the algorithm has executed REP2 times.
			}
			times=(stop-start)/((double)CLOCKS_PER_SEC); // calculates time diferential

			bursttime=bursttime+times; // calculates burstime

		}
		bursttime=bursttime/REP; // calculates bursttime
		buf[j].time=bursttime; // stores bursttime in struct
		buf[j].size=size; //stores size in struct

	}
}
