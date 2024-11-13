#ifndef __MERGE_TWO_SORTEDLISTS
#define __MERGE_TWO_SORTEDLISTS
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
 

typedef struct track {
        char ID[20];
        double GRADE;
        struct track *NEXT;
} RecordList;

/* Allow users to check the new recording of students data, this function is also crucial for updating records in the RecordList */ 
RecordList* NewRecord(char *ID, double GRADE);

/* This function is used to update real-time data which is added to the original record in the RecordedList */
RecordList* UpdateRecord(RecordList *SortedList, char *ID, double GRADE);

/* Users are also able to delete List from RecordList, but List must be existed, or this function returns NOTHING */
void DeleteList(RecordList **ExistList);

/* After all previous operations of RecordList have been done, now users are able to Display the exact list */ 
void DisplayList(RecordList *SortedList);

/* This function is used to hanle all possible conditions of two SortedLists, they might be appear either seperately together, and this function returns proper merged list of two SortedLists with all student data from the input CSV File */
RecordList* Merge(RecordList *SortedList1, RecordList *SortedList2);
 
/* This function is used to deal with both of "high" and "low" conditions which are normally necessary for Merge_Two_SortedLists. Here, I apply "feedforward" to represent "high" and "feedbackward" to represent low" */
RecordList* Merge_Two_SortedLists(RecordList *SortedList);
 
#endif


