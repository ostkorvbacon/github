// *********************************************************************
//
//  - Name: task-gen.h
//  - Created on: Sep 23, 2020
//  - Author: Marcus Pieskä
// 
// *********************************************************************
 
#ifndef TASK_GENERATOR 
#define TASK_GENERATOR
 
#include "defined-types.h"

#define STD_DURATION 20000

// *********************************************************************

// get current time 
i64 get_time(void);

// get number of tasks remaining in program
i64 tasks_remain(void);

// get the first task scheduled for this tick, if there are any
sch_task* get_current_sch_task(void);

// run a simple program for debugging
void init_simple_test(i64 (*sched)(void), const char* suffix);

// run a test program with the given scheduler
void init_test_prog1(i64 (*sched)(void), const char* suffix);
void init_test_prog2(i64 (*sched)(void), const char* suffix);

// setup a custom program, this will not run immediately 
void init_custom_prog(i64 time_limit, const char* suffix);

// add a custom task to your custom program - see the above function
void add_custom_task(i64 arrival, i64 duration, i64 deadline);

// run your custom program, with you custom tasks
void run_custom_prog(i64 (*sched)(void));

#endif 

// *********************************************************************
