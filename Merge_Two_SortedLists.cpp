#include "Merge_Two_SortedLists.h"

/* Allow users to check the new recording of students data, this function is also crucial for updating records in the RecordList */
RecordList* NewRecord(char *ID, double GRADE) {
    
    RecordList *track = (RecordList*) malloc(sizeof(RecordList));
    strcpy(track->ID, ID);
    track->GRADE = GRADE;
    track->NEXT = NULL;
    return track;
    
}

/* This function is used to update real-time data which is added to the original record in the RecordedList */
RecordList* UpdateRecord(RecordList *SortedList, char *ID, double GRADE) {
    
    RecordList *track = NewRecord(ID, GRADE);
    track->NEXT = SortedList;
    return track;
    
}
 
/* Users are also able to delete List from RecordList, but List must be existed, or this function returns NOTHING */
void DeleteList(RecordList **ExistList){
    RecordList *temp_list = NULL;
 
    while((*ExistList)->NEXT != NULL){
        temp_list = (*ExistList)->NEXT;
        free((*ExistList));
        (*ExistList) = temp_list;
    }
 
    if((*ExistList) != NULL){
        free((*ExistList));
        (*ExistList) = NULL;
    }
    
    if((*ExistList) == NULL){
        return;
    }
   
}

/* After all previous operations of RecordList have been done, now users are able to Display the exact list */
void DisplayList(RecordList *SortedList){

    RecordList *temp_list = SortedList;
    while(temp_list != NULL){
        printf("%s: %f\n", temp_list->ID, temp_list->GRADE);
        temp_list = temp_list->NEXT;
        
    }
}

// Merge_Two_SortedLists

/* This function is used to hanle all possible conditions of two SortedLists, they might be appear either seperately together, and this function returns proper merged list of two SortedLists with all student data from the input CSV File */
RecordList* Merge(RecordList *SortedList1, RecordList *SortedList2) {
        if (SortedList1 == NULL){
                return SortedList2;
        }
        if (SortedList2 == NULL){
                return SortedList1;
        }
        RecordList *SortedList, *temp_list;
        if (SortedList1->GRADE > SortedList2->GRADE) {
                SortedList = SortedList1;
                SortedList1 = SortedList1->NEXT;
        } else {
                SortedList = SortedList2;
                SortedList2 = SortedList2->NEXT;
        }
        temp_list = SortedList;
 
        while (SortedList1 != NULL && SortedList2 != NULL) {
                if (SortedList1->GRADE > SortedList2->GRADE) {
                        temp_list->NEXT = SortedList1;
                        SortedList1 = SortedList1->NEXT;
                } else {
                        temp_list->NEXT = SortedList2;
                        SortedList2 = SortedList2->NEXT;
                }
                temp_list = temp_list->NEXT;
        }
        if (SortedList1 != NULL){
                temp_list->NEXT = SortedList1;
        }else if (SortedList2 != NULL){
                temp_list->NEXT = SortedList2;
        }
        return SortedList;
}

/* This function is used to deal with both of "high" and "low" conditions which are normally necessary for Merge_Two_SortedLists. Here, I apply "feedforward" to represent "high" and "feedbackward" to represent low" */
RecordList* Merge_Two_SortedLists(RecordList *SortedList) {
	RecordList *feedforward = SortedList;
	RecordList *feedback = SortedList;
                
        if (SortedList != NULL && SortedList->NEXT != NULL){
        
                RecordList *feedforward = SortedList;
		 RecordList *feedback = SortedList;
		 
                while (feedforward->NEXT != NULL && feedforward->NEXT
                ->NEXT != NULL) {
                        feedforward = feedforward->NEXT->NEXT;
                        feedback = feedback->NEXT;
                }
                
                feedforward = feedback;
                feedback = feedback->NEXT;
                feedforward->NEXT = NULL;
                feedforward = Merge_Two_SortedLists(SortedList);
                feedback = Merge_Two_SortedLists(feedback);
                return Merge(feedforward, feedback);
                
        }else {
                return SortedList;
               } 
               
        }

 
 


