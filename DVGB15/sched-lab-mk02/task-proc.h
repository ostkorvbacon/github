// *********************************************************************
//
//  - Name: task-proc.h
//  - Created on: Sep 23, 2020
//  - Author: Marcus Pieskä
// 
// *********************************************************************
 
#ifndef TASK_PROCESSOR
#define TASK_PROCESSOR
 
#include "defined-types.h"

// *********************************************************************

f64 box_muller_trans(void);
void init_processor_state(char* trace_dir);
void set_proc_stdev(i64 stdev);
void set_time_tick(i64 time);
void increment_proc(i64 time);
void trace_task_template(sch_task* task);
void commit_trace_to_file(f64 load, i64 time_limit);

// function to call when discarding late task that was never processed
void discard_task(sch_task* task);

// abort task, do this if completing the task is no longer desirable
void abort_task(void);

// retrieve current task being processed, and make processor idle
sch_task* preempt_task(void);

// peek to see if there is a task being processed
sch_task* peek_task(void);

// hand over task for processor to handle
void process_task(sch_task* task);

#endif 

// *********************************************************************
