#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <unistd.h>
#include <sys/wait.h>

#include "p1_process.h"
#include "p1_threads.h"
#include "Merge_Two_SortedLists.h"

void get_statistics(std::string class_name[], int num_processes, int num_threads) {
 
        // I'm creating multiple processes here
        // each process handles at least one file.)
        pid_t pid, wait_pid;
        int PidNumber = 5;
 	int COUNT = 0;
        if(num_processes < 5){
                PidNumber = num_processes;
        }      
 
        for(int COUNT = 0; COUNT < PidNumber; COUNT++){
        //if (COUNT < PidNumber){
        	
                pid = fork();
                if(pid == 0){//fork is successful
                        /*printf("Child process is created. (pid: %d) \n", 				 getpid());*/
                        Supervise(class_name, PidNumber, num_threads, 			        COUNT);
                        printf("Child process is created. (pid: %d) \n", 				 getpid());
                        break;
                }
                
               // COUNT++;
        }
       
        if(pid == 0){
                
                /*int Flag = 0;
                while ((wait_pid = wait(&Flag)) > 0);*/
                
                printf("Child process is terminated. (pid: %d)\n", 			 getpid());
                exit(0);
                                
        }
        else{
                /*printf("Child process is terminated. (pid: %d)\n", 			 getpid());
                exit(0);*/
                
                int Flag = 0;
                while ((wait_pid = wait(&Flag)) > 0);
                /*{
                printf("Child process is terminated. (pid: %d)\n", 			 getpid());
                }
                exit(0);*/
               }
        }
       
        // Each process should use the sort function which you have defined            
        // in the p1_threads.cpp for multithread sorting of the data.
       
        // My code is able to get the statistics and
        // generate the required outputs for any number of child processes and threads.
       


/* This function is used to dispatch Process Hierarchy:Main process (spawns) -> Child processes (spawns) -> Threads */

void Supervise(std::string class_name[], int PidNumber, int num_threads, int PidIndex){
 
        while (PidNumber == 1){
                for(int i = 0; i < 5; i++){
                        SortFile(class_name[i], num_threads);
                }
                return;
        }
 
        while (PidNumber == 2){
                if(PidIndex == 0){
                        SortFile(class_name[0], num_threads);
                        SortFile(class_name[1], num_threads);
                }
                else if(PidIndex == 1){
                        SortFile(class_name[2], num_threads);
                        SortFile(class_name[3], num_threads);
                        SortFile(class_name[4], num_threads);
                }
                return;
        }
 
        while (PidNumber == 3){
                if(PidIndex == 0){
                        SortFile(class_name[0], num_threads);
                        SortFile(class_name[1], num_threads);
                }
                else if(PidIndex == 1){
                        SortFile(class_name[2], num_threads);
                        SortFile(class_name[3], num_threads);
                }
                else if(PidIndex == 2){
                        SortFile(class_name[4], num_threads);
                }
                return;
        }
 
        while(PidNumber == 4){
                if(PidIndex == 0){
                        SortFile(class_name[0], num_threads);
                        SortFile(class_name[1], num_threads);
                }
                else if(PidIndex == 1){
                        SortFile(class_name[2], num_threads);
                }
                else if(PidIndex == 2){
                        SortFile(class_name[3], num_threads);
                }
                else if(PidIndex == 3){
                        SortFile(class_name[4], num_threads);
                }
                return;
        }
 
       while (PidNumber == 5){
                if(PidIndex == 0){
                        SortFile(class_name[0], num_threads);
                }
                else if(PidIndex == 1){
                        SortFile(class_name[1], num_threads);
                }
                else if(PidIndex == 2){
                        SortFile(class_name[2], num_threads);
                }
                else if(PidIndex == 3){
                        SortFile(class_name[3], num_threads);
                }
                else if(PidIndex == 4){
                        SortFile(class_name[4], num_threads);
                }
                return;
        }
}
 
 





