#ifndef __P1_PROCESS
#define __P1_PROCESS
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
#include "p1_threads.h"
 
void get_statistics(std::string class_name[], int num_processes, int num_threads);

/* This function is used to dispatch Process Hierarchy:Main process (spawns) -> Child processes (spawns) -> Threads */
void Supervise(std::string class_name[], int PidNumber, int num_threads, int PidIndex);
 
#endif

