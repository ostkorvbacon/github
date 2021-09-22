// *********************************************************************
//
//  - Name: task-sched.c
//  - Created on: Sep 23, 2020
//  - Author: Marcus Pieskä
// 
// *********************************************************************

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "task-gen.h"
#include "task-proc.h"

//#define PRINT_CORRECT 

// *********************************************************************


void init_task_buf_state(void) {
	// Initialize your local queue / task storage
	// and any other variables your scheduler will use
}

i64 sched_with_rm(void) {
	if (0) { // Check if there are more tasks to be processed
		return 1;
	}
	return 0;
}

i64 sched_with_rm_hard(void) {
	if (0) { // Check if there are more tasks to be processed
		return 1;
	}
	return 0;
}

i64 sched_with_edf(void) {
	if (0) { // Check if there are more tasks to be processed
		return 1;
	}
	return 0;
}

i64 sched_with_edf_hard(void) {
	if (0) { // Check if there are more tasks to be processed
		return 1;
	}
	return 0;
}

// *********************************************************************

int main(int argc, char *argv[]) { 

	i64 run_tests = 0; 
	i64 run_prog1_prog2 = 0; 

	if(run_tests) {
		init_task_buf_state();
		init_custom_prog(STD_DURATION, "test-comp-rm");
		add_custom_task(0, 25, 50);
		add_custom_task(0, 30, 75);
		run_custom_prog(sched_with_rm);
	}  
	if(run_tests) {
		init_task_buf_state();
		init_custom_prog(STD_DURATION, "test-comp-edf");
		add_custom_task(0, 25, 50);
		add_custom_task(0, 30, 75);
		run_custom_prog(sched_with_edf);
	}  
	if(run_tests) {
		init_task_buf_state();
		init_custom_prog(STD_DURATION, "test-comp-rm-hard");
		add_custom_task(0, 25, 50);
		add_custom_task(0, 30, 75);
		run_custom_prog(sched_with_rm_hard);
	}  
	if(run_tests) {
		init_task_buf_state();
		init_custom_prog(STD_DURATION, "test-comp-edf-hard"); 
		add_custom_task(0, 25, 50);
		add_custom_task(0, 30, 75);
		run_custom_prog(sched_with_edf_hard);
	}  


	if(run_prog1_prog2) {
		init_task_buf_state();
		init_test_prog1(sched_with_rm, "rm");
	}    
	if(run_prog1_prog2) {
		init_task_buf_state();
		init_test_prog2(sched_with_rm, "rm");
	}    
	if(run_prog1_prog2) {
		init_task_buf_state();
		init_test_prog1(sched_with_edf, "edf");
	}    
	if(run_prog1_prog2) {
		init_task_buf_state();
		init_test_prog2(sched_with_edf, "edf");
	}

	printf("*** exiting normally\n");
	return 0;
}

// *********************************************************************
