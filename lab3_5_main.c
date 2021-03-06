/** lab3_main.c: Implements a front end for lab3_5_lib.c.
*
*
* Name: Timothy Becker
* Email: becker43@purdue.edu
* Course: CNIT 315
* Lab batch: 008
* Lab assignment: 3.5
* Date: March 4, 2015
*
* Collaborators:
* Chris Fox
* Everett Kennedy
* Matt Depue
*
* Select Statement Resource: http://www.tutorialspoint.com/cprogramming/c_decision_making.htm
* Find time of exection: http://stackoverflow.com/questions/5248915/execution-time-of-c-program
* Malloc Help: http://en.wikipedia.org/wiki/C_dynamic_memory_allocation
*
*/

#include <time.h> //for time()
#include <stdio.h>
#include <stdlib.h>
#include "lab3_5_lib.h"


/*
 * Calls the functions implemented in lab3_lib.c and implements a menu system
 * for them.
 *
 * 	@return 	0 - Successful completion of the program.
 * 				1 - An error during execution.
 */
int main(){
	/* Initialize */

	srand(time(NULL));

  // Set the array size HERE
  int input;
  int temp;
  int i = 0;
  int k = 0;
  int top = 0; // counter
  int selection = 0; // Menu Selection Variable
  
  int searchfor; //value to search with binary search
  int found_loc; // location of searched for value by binary

  clock_t begin, end;
  double time_spent, sort_time_spent = 0, total_time_spent = 0;

	/* Menu */
  printf("\e[1;1H\e[2J");

  int * primary_array = malloc(top * sizeof(int)); // holds main array values
  int * temp_array = malloc(top * sizeof(int));  // used to hold values while size increases


	//Your code goes here!
  
	
	// Checks for a failed array creation
  if ( NULL == (primary_array = malloc(top * sizeof(int))) ) {
  printf("Unsorted Array Malloc Failed\n");
  return(-1);
  }

  if ( NULL == (temp_array = malloc(top * sizeof(int))) ) {
  printf("Sorted Array Malloc Failed\n");
  return(-2);
  }
  

  while (1) 
  {
    printf("Please Enter a positive value that you would like to add to the array.\n To perform other functions, enter -1\n");
    scanf("%d", &input);
    //printf("%d\n", input); // debugging
    if (input == -1) {
      temp = 0;

      printf("\n\nWhat would you like to do?\n");
      printf(" 1) View the Array\n 2) Sort the Array\n 3) Search for a Value in the Array\n-1) Exit\n");
      scanf("%d", &selection);
      printf("\e[1;1H\e[2J");
    
      switch(selection)
      {
      case -1 :
        printf("\e[1;1H\e[2J");
        printf("\n\n\nGoodbye... \n\n\n");
        return 0;
      case 1 :
        // 1) View Values in the Array
        for (k = 0; k < top; k++)
        {
          printf("%d\n", primary_array[k]);
        }
      break;
      case 2 :
        //2) Sort the Array

        printf("Sorting %d values...\n", top);
        begin = clock();

        insertion_sort(primary_array, top, temp_array);

        end = clock();
        time_spent = ((double)(end - begin) / CLOCKS_PER_SEC)*1000000; // in microseconds

        for (k = 0; k < top; k++)
        {
          primary_array[k] = temp_array[k];
        }
        
        printf("Selection Sort Completed\n");
        printf("Execution Time: %lf Micro-Seconds\n", time_spent);
      break;
      case 3 :
        // Search for a Value in the array
        printf("What integer value would you like to search for?\n");
        scanf("%d", &searchfor);

        printf("Sorting %d values...\n", top);
        begin = clock();
        insertion_sort(primary_array, top, temp_array); 
        end = clock();
        
        time_spent = ((double)(end - begin) / CLOCKS_PER_SEC)*1000000; // in microseconds
        sort_time_spent = time_spent;
        total_time_spent = time_spent;

        printf("Searching for your requested value...\n");
        begin = clock();
        binary_search(temp_array, top, searchfor, &found_loc);
        end = clock();
        
        time_spent = ((double)(end - begin) / CLOCKS_PER_SEC)*1000000; // in microseconds
        total_time_spent = total_time_spent + time_spent;
        
        // Output Results
        printf("\n\nTime Spent Sorting:                     %lf Micro-Seconds \n", sort_time_spent);
        printf("Time Spent Searching:                   %lf  Micro-Seconds\n", time_spent);
        printf("Total Time Spent Sorting and Searching: %lf Micro-Seconds\n", total_time_spent);
        
        if (found_loc != -1) {
          printf("\nThe binary search found the value \"%d\" in the array!\nLocation in Array = %d\n\n", searchfor, found_loc);

          printf("Here are the surrounding 5 numbers around the found number\n");

          for (i = (found_loc - 5); i <= found_loc + 5; i++)
            { 
              if (i < 0) {
                // do nothing
              } 
              else if (i >= top) {
                //do nothing
              }
              else if (i == found_loc) {
                printf("%d) %d <-- Your Searched Value!\n", i, temp_array[i]);
              } 
              else {
                printf("%d) %d\n", i, temp_array[i]);
              }
            }
        }
        else {
          printf("The value you searched for was not found\n\n");
        }
      break;
      default :
        //Option if an invalid selection is made
        printf("You did not make a valid selection.\n" );
      }
    }
    // ===========================================================
    // If -1 is not entered, continues to add integer to the array
    // ===========================================================
    else {
      if (top == 0) {
        primary_array[top] = input;
				top++;
      }
      else {

        temp_array = malloc(top * sizeof(int));
        int * temp_array = malloc(top * sizeof(int));  // used to hold values while size increases
        temp_array = primary_array;
				primary_array = (int*)realloc(primary_array, sizeof(int)*(top+1));

        if (primary_array == NULL) {
        fprintf(stderr, "failed to allocate memory, reverting to previous state\n");
        primary_array = temp_array;
        }
        else {
          primary_array[top] = input;
        }

				//printf("%d\n", primary_array[top]); // debugging
				top++;
      }
    }
  }

	/* Wrap up */


	return 0;
}
