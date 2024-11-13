#include "p1_threads.h"
#include "Merge_Two_SortedLists.h"
 
// This file includes functions that actually perform the computation.
// I'm creating the thread with these function
// Or directly calling this function
 
/* Properly read input files and give users relative hints(Correct FileName or error), depending on the file is able to be opened or not */

Read_File_Result *Read_FileResult(std::string FileName){
        Read_File_Result *ReadFileResult = (Read_File_Result 	*)malloc(sizeof(Read_File_Result));
        
        std::string Name = "input/" + FileName + ".csv";
        RecordList *SortedList = NULL;
        
        int num_tracks = 0;
        double SUM = 0;

        const char *file_name = Name.c_str();
        FILE *File = fopen(file_name, "r");
        
        if (File == NULL) {
                //printf("ERROR!");
                return NULL;
        }
        char line[128];
        fgets(line, 128, File);
        char *segment1;
        char *segment2;
        
        while (fgets(line, 128, File)) {
        
                segment1 = strtok(line, ",");
                segment2 = strtok(NULL, ",");
                
                SUM += atof(segment2);
                num_tracks++;
                
                SortedList = UpdateRecord(SortedList, segment1, 			atof(segment2));
        }
        fclose(File);
        ReadFileResult->SortedList = SortedList;

 	ReadFileResult->num_tracks = num_tracks;
        ReadFileResult->SUM = SUM;
        return ReadFileResult;
}
 
 
/* Track all ajustments of Sortedlist by camparing changes from previous RecordedList to newest RecordedList */
RecordList *GetSortedList(RecordList *SortedList, int num_tracks, int num_threads){
        int record = num_tracks / num_threads;
        RecordList *temp_list = SortedList;
        RecordList *previous = NULL;
        int COUNT = record;
        while(COUNT > 0){
                previous = temp_list;
                temp_list = temp_list->NEXT;
                if(COUNT == 1){
                        previous->NEXT = NULL;
                }
                COUNT--;
        }
        return temp_list;
}
 
double GetAverage(double SUM, int num_tracks){
        return SUM / num_tracks;
}
 
double GetMedian(RecordList *SortedList){

        RecordList *feedforward = SortedList;
        RecordList *feedback 	 = SortedList;
        
        while (feedforward->NEXT != NULL && feedforward->NEXT->NEXT != NULL) {
                feedforward = feedforward->NEXT->NEXT;
                feedback = feedback->NEXT;
        }
        if(feedforward->NEXT != NULL){
                
                return (feedback->GRADE + feedback->NEXT->GRADE) / 2;
                
        }else{
        
                return feedback->GRADE;
                
        }
}
 
double GetStdDev(RecordList *SortedList, double AVG, int num_tracks){
        double Numerator = 0;
 	RecordList *temp_list = SortedList;
 	
 	//Numerator: Square of Sigma(Xi - Xmean)
        while(temp_list != NULL){
       
                Numerator += pow(temp_list->GRADE - AVG, 2);
                temp_list = temp_list->NEXT;
                
        }
        return sqrt(Numerator / num_tracks);
}

/* After successfully reading proper files, there exist a number of records of data, which should be applied to display Average, Median, and Standard Deviation, these data will be eventually matched(ID + GRADE). My final goal is to show output of both DataCSVfile&SortedCSVfile*/ 
void WriteFile(std::string FileName, Write_File_Result *WriteFileResult){
        std::string Name = "output/" + FileName + "_stats.csv";
        const char *file_name = Name.c_str();
        FILE *file_open = fopen(file_name, "w+");
        if (file_open == NULL) {
                fprintf(stderr, "fopen() failed.\n");
                exit(EXIT_FAILURE);
        }
        
        char Average[12];
        char Median[12];
        char Std_Dev[12];
        
        sprintf(Average, "%.3lf", WriteFileResult->AVG);
        sprintf(Median, "%.3lf", WriteFileResult->MID);
        sprintf(Std_Dev, "%.3lf", WriteFileResult->StdDev);
 
        fprintf(file_open, "Average,Median,Std. Dev\n");
 
        if(WriteFileResult->num_tracks != 0){
                fprintf(file_open, "%s", Average);
                fprintf(file_open, ",");
                fprintf(file_open, "%s", Median);
                fprintf(file_open, ",");
                fprintf(file_open, "%s", Std_Dev);
                fprintf(file_open, "\n");
        }
        fclose(file_open);
 
        std::string sname = "output/" + FileName + "_sorted.csv";
        file_name = sname.c_str();
        FILE *File = fopen(file_name, "w+");
        if (File == NULL) {
                fprintf(stderr, "fopen() failed.\n");
                exit(EXIT_FAILURE);
        }
        char GRADE[12];
        fprintf(file_open, "Rank,Student ID,Grade\n");
        RecordList *temp_list = WriteFileResult->SortedList;
        int Flag = 1;
        while(temp_list != NULL){
                fprintf(File, "%d", Flag);
                fprintf(File, ",");
                fprintf(File, "%s", temp_list->ID);
                fprintf(File, ",");
                fprintf(File, "%f", temp_list->GRADE);
                fprintf(File, "\n");
                Flag++;
                temp_list = temp_list->NEXT;
        }
 
        fclose(File);
}

/* This function is used to sort files that are priviously read and written, depending on the number of records*/
void SortFile(std::string FileName, int num_threads){
 
        Read_File_Result *ReadFileResult = Read_FileResult(FileName);
        
        if(ReadFileResult == NULL){
        	return;
        }
 
        RecordList *SortedList = NULL;
        RecordList *SortedArray[num_threads];
        pthread_t tid[num_threads];
 
        if(ReadFileResult->num_tracks == 0){
        
        
        Write_File_Result *WriteFileResult = (Write_File_Result
        *)malloc(sizeof(Write_File_Result));
        
        WriteFileResult->num_tracks = ReadFileResult->num_tracks;
        WriteFileResult->SortedList = SortedList;
 
        if(ReadFileResult->num_tracks == 0){
        	WriteFileResult->AVG = 0;
                WriteFileResult->MID = 0;
                WriteFileResult->StdDev = 0;
        
            
        }
        
        else{
              
                WriteFileResult->AVG = GetAverage(ReadFileResult->SUM,
                ReadFileResult->num_tracks);
                WriteFileResult->MID = GetMedian(SortedList);
                WriteFileResult->StdDev = GetStdDev(SortedList, 			WriteFileResult->AVG, ReadFileResult->num_tracks);
                
        }
        
	WriteFile(FileName, WriteFileResult);
	
    	DeleteList(&SortedList);
    	
        free(ReadFileResult);
        free(WriteFileResult);
        
        return;
                
        }
 
        if(ReadFileResult->num_tracks < num_threads){
                num_threads = ReadFileResult->num_tracks;
        }
 
        for(int i = 0; i < num_threads; i++){
        
 		if(i == 0){
                        SortedArray[i] = ReadFileResult->SortedList;
                }
                
                else{
                        SortedArray[i] = GetSortedList(SortedArray[i-1],
                        ReadFileResult->num_tracks, num_threads);
                }
        }
 
        for(int i = 0; i < num_threads; i++){
                pthread_create(&tid[i], NULL, Threads, (void *)
                (SortedArray[i]));
        }
 
        for(int i = 0; i < num_threads; i++){
                pthread_join(tid[i], (void **)(&SortedArray[i]));
        }
 
        SortedList = SortedArray[0];
        for(int i = 0; i < num_threads - 1; i++){
                SortedList = Merge(SortedList, SortedArray[i+1]);
        }
 
}

void *Threads(void *arg){
        RecordList *SortedList = Merge_Two_SortedLists((RecordList *)arg);
        return SortedList;
}
