#ifndef __P1_THREADS
#define __P1_THREADS
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <math.h>
 
#include "p1_process.h"
#include "Merge_Two_SortedLists.h"
 
typedef struct ReadFileResult {
        int num_tracks;
        double SUM;
        RecordList *SortedList;
} Read_File_Result;
 
typedef struct WriteFileResult {
        int num_tracks;
        double AVG;
        double MID;
        double StdDev;
        RecordList *SortedList;
} Write_File_Result;
 

/* Properly read input files and give users relative hints(Correct FileName or error), depending on the file is able to be opened or not */
Read_File_Result *Read_FileResult(std::string FileName);
 
/* Track all ajustments of Sortedlist by camparing changes from previous RecordedList to newest RecordedList */
RecordList *GetSortedList(RecordList *SortedList, int num_tracks, int num_threads);

/* After successfully reading proper files, there exist a number of records of data, which should be applied to display Average, Median, and Standard Deviation, these data will be eventually matched(ID + GRADE). My final goal is to show output of both DataCSVfile&SortedCSVfile*/ 
void WriteFile(std::string FileName, Write_File_Result *WriteFileResult);
 
double GetAverage(double SUM, int num_tracks);
 
double GetMedian(RecordList *SortedList);
 
double GetStdDev(RecordList *SortedList, double avg, int num_tracks);

/* This function is used to sort files that are priviously read and written, depending on the number of records*/
void SortFile(std::string fileName, int num_threads);

void *Threads(void *arg);
 
#endif

