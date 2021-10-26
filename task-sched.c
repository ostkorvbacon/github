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

#define LENGTH 200

//#define PRINT_CORRECT

// *********************************************************************

int i=0;
sch_task* queue[LENGTH]={NULL};
FILE *fp;

void init_task_buf_state(void) {
for (int j=0;j<200;j++) {
		queue[j]=NULL;
}

	fp=fopen("output.txt","w");
 i=0;
	// Initialize your local queue / task storage
	// and any other variables your scheduler will use
}

void sort() {
	int k=1;
	int j=0;
	sch_task* temp=NULL;
	while(k){
		k=0;
		while (queue[j+1]!=NULL) {

			if (queue[j]->deadline<queue[j+1]->deadline){

				temp=queue[j+1];
				queue[j+1]=queue[j];
				queue[j]=temp;
				k=1;

			}

			if (queue[j]->deadline==queue[j+1]->deadline && queue[j]->arrival<queue[j+1]->arrival){

				temp=queue[j+1];
				queue[j+1]=queue[j];
				queue[j]=temp;
				k=1;

			}

			j++;
		}
	}
}

void sort2() {
	int k=1;
	int j=0;
	sch_task* temp=NULL;
	while(k){
		k=0;
		while (queue[j+1]!=NULL) {

			if (queue[j]->abs_deadline<queue[j+1]->abs_deadline){

				temp=queue[j+1];
				queue[j+1]=queue[j];
				queue[j]=temp;
				k=1;

			}
			j++;
		}
	}
}


void remlate(){
	for (int l=0;l<i;l++) {
			if (queue[l]!=NULL) fprintf(fp, "Time: %ld Abs Deadline: %ld Index:%ld\n",get_time(),queue[l]->abs_deadline, queue[l]->index);

		if (queue[l]!=NULL && queue[l]->abs_deadline<=get_time()) {

			for(int index=l;index<i;index++){
			 discard_task(queue[index]);
					queue[index]=queue[index+1];

			}

			queue[i]=NULL;
			if (i!=0) i--;
		}

	}

	if (queue[i]!=NULL) fprintf(fp, "Time: %ld Abs Deadline: %ld Index:%ld\n",get_time(),queue[i]->abs_deadline, queue[i]->index);
	if (queue[i]!=NULL && queue[i]->abs_deadline<=get_time()){
 	discard_task(queue[i]);
		queue[i]=NULL;
		if (i!=0) i--;
	}


}

/////////////////////////////////////////RM SOFT

i64 sched_with_rm(void) {

	if (tasks_remain() || queue[0]!=NULL || peek_task()!=NULL){
		//printf("Start\n");
		sch_task* temp=get_current_sch_task();
		if (i==0 && queue[i]==NULL) {
			queue[i]=temp;
			temp=get_current_sch_task();

		}
			while (temp) {
				i++;
				queue[i]=temp;
				temp=get_current_sch_task();
			}




		if (i!=0 || 1){
		fprintf(fp,"\n");
		fprintf(fp,"%ld\n",get_time());
		fprintf(fp,"%p\n",peek_task());
		//if (peek_task()) fprintf(fp, "%ld\n",peek_task()->arrival );

		for (int w=0;w<=i;w++)	{

			fprintf(fp,"task: %p i=%d\n", queue[w],i);
			if (queue[w]) fprintf(fp, "arrival: %ld Deadline: %ld\n",queue[w]->arrival,queue[w]->deadline);
		}
		fprintf(fp,"\n");
}
		sort();

		for (int w=0;w<=i;w++)	{

			fprintf(fp,"task: %p i=%d\n", queue[w],i);
			if (queue[w]) fprintf(fp, "arrival: %ld Deadline: %ld\n",queue[w]->arrival,queue[w]->deadline);
		}

		if(!peek_task()){
			process_task(queue[i]);
			queue[i]=NULL;
			if (i!=0) i--;
		}

		else if (queue[i]!=NULL && peek_task()->deadline>queue[i]->deadline ) {
			sch_task* temp2=preempt_task();
			process_task(queue[i]);
			queue[i]=temp2;
		}


//printf("Slut 1\n\n");
		return 1;


	}
//printf("Slut 0\n\n" );
  fclose(fp);
	return 0;
}

/////////////////////////////////////////RM HARD

i64 sched_with_rm_hard(void) {

	if (tasks_remain()|| queue[0]!=NULL || peek_task()!=NULL){

		sch_task* temp=get_current_sch_task();
		if (i==0 && queue[i]==NULL) {
			queue[i]=temp;
			temp=get_current_sch_task();

		}
			while (temp) {
				i++;
				queue[i]=temp;
				temp=get_current_sch_task();
			}




		if (i!=0 || 1){
		fprintf(fp,"\n");
		fprintf(fp,"%ld\n",get_time());
		fprintf(fp,"%p\n",peek_task());
		//if (peek_task()) fprintf(fp, "%ld\n",peek_task()->arrival );

		for (int w=0;w<=i;w++)	{

			fprintf(fp,"task: %p i=%d\n", queue[w],i);
			if (queue[w]) fprintf(fp, "arrival: %ld Deadline: %ld\n",queue[w]->arrival,queue[w]->abs_deadline);
		}
		fprintf(fp,"\n");
}
		sort();
		remlate();
		for (int w=0;w<=i;w++)	{

			fprintf(fp,"task: %p i=%d\n", queue[w],i);
			if (queue[w]) fprintf(fp, "arrival: %ld Deadline: %ld\n",queue[w]->arrival,queue[w]->abs_deadline);
		}


	/*	if (queue[i]!=NULL && queue[i]->abs_deadline<=get_time()+queue[i]->duration){

			discard_task(queue[i]);
			queue[i]=NULL;
			if (i!=0) i--;

		}
*/
		if(!peek_task()){
			process_task(queue[i]);
			queue[i]=NULL;
			if (i!=0) i--;
		}
		else if (peek_task()->abs_deadline<=(get_time())){
				abort_task();
				process_task(queue[i]);
				queue[i]=NULL;
				if (i!=0) i--;
		}

		else if (queue[i]!=NULL && peek_task()->deadline>queue[i]->deadline ) {
			sch_task* temp2=preempt_task();
			process_task(queue[i]);
			queue[i]=temp2;
		}


//printf("Slut 1\n\n");
		return 1;


	}
//printf("Slut 0\n\n" );
  fclose(fp);
	return 0;
}

/////////////////////////////////////////EDF Soft

i64 sched_with_edf(void) {

	if (tasks_remain()|| queue[0]!=NULL || peek_task()!=NULL){
		//printf("Start\n");
		sch_task* temp=get_current_sch_task();

//printf("Hit i=%d\n",i );
	if (i==0 && queue[i]==NULL) {
			queue[i]=temp;
			temp=get_current_sch_task();

		}

			while (temp) {
				i++;
				queue[i]=temp;
				temp=get_current_sch_task();
			}




		/*if (i!=0 || 1){
		fprintf(fp,"\n");
		fprintf(fp,"%ld\n",get_time());
		fprintf(fp,"%p\n",peek_task());
		//if (peek_task()) fprintf(fp, "%ld\n",peek_task()->arrival );

		for (int w=0;w<=i;w++)	{

			fprintf(fp,"task: %p i=%d\n", queue[w],i);
			if (queue[w]) fprintf(fp, "%ld %ld\n",queue[w]->arrival,queue[w]->abs_deadline);
		}
		fprintf(fp,"\n");
}*/
		sort2();

	/*	for (int w=0;w<=i;w++)	{

			fprintf(fp,"task: %p i=%d\n", queue[w],i);
			if (queue[w]) fprintf(fp, "%ld %ld\n",queue[w]->arrival,queue[w]->abs_deadline);
		}*/

 	if(!peek_task()|| queue[0]!=NULL || peek_task()!=NULL){
			process_task(queue[i]);
			queue[i]=NULL;
			if (i!=0) i--;
		}

		else if (queue[i]!=NULL && peek_task()->abs_deadline>queue[i]->abs_deadline) {
			sch_task* temp2=preempt_task();
			process_task(queue[i]);
			queue[i]=temp2;
		}
		return 1;
	}
	fclose(fp);
	return 0;

}
/////////////////////////////////////////EDF HARD

i64 sched_with_edf_hard(void) {
	if (tasks_remain()|| queue[0]!=NULL || peek_task()!=NULL){
		//printf("Start\n");
		sch_task* temp=get_current_sch_task();

//printf("Hit i=%d\n",i );
	if (i==0 && queue[i]==NULL) {
			queue[i]=temp;
			temp=get_current_sch_task();

		}

			while (temp) {
				i++;
				queue[i]=temp;
				temp=get_current_sch_task();
			}




		/*if (i!=0 || 1){
		fprintf(fp,"\n");
		fprintf(fp,"%ld\n",get_time());
		fprintf(fp,"%p\n",peek_task());
		//if (peek_task()) fprintf(fp, "%ld\n",peek_task()->arrival );

		for (int w=0;w<=i;w++)	{

			fprintf(fp,"task: %p i=%d\n", queue[w],i);
			if (queue[w]) fprintf(fp, "%ld %ld\n",queue[w]->arrival,queue[w]->abs_deadline);
		}
		fprintf(fp,"\n");
}*/
		sort2();
		remlate();
	/*	for (int w=0;w<=i;w++)	{

			fprintf(fp,"task: %p i=%d\n", queue[w],i);
			if (queue[w]) fprintf(fp, "%ld %ld\n",queue[w]->arrival,queue[w]->abs_deadline);
		}*/

 	if(!peek_task()){
			process_task(queue[i]);
			queue[i]=NULL;
			if (i!=0) i--;
		}
		else if (peek_task()->abs_deadline<=(get_time())){
				abort_task();
				process_task(queue[i]);
				queue[i]=NULL;
				if (i!=0) i--;
		}

		else if (queue[i]!=NULL && peek_task()->abs_deadline>queue[i]->abs_deadline) {
			sch_task* temp2=preempt_task();
			process_task(queue[i]);
			queue[i]=temp2;
		}
		return 1;
	}
	fclose(fp);
	return 0;
}

// *********************************************************************

int main(int argc, char *argv[]) {

	i64 run_tests = 1;
	i64 run_prog1_prog2 = 0;

	if(run_tests) {

		init_task_buf_state();
		init_custom_prog(STD_DURATION, "test-comp-rm");
		add_custom_task(0, 25, 50);
		add_custom_task(0, 30, 75);
		run_custom_prog(sched_with_rm);
	}
	if(run_tests || 0) {
		init_task_buf_state();
		init_custom_prog(STD_DURATION, "test-comp-edf");
		add_custom_task(0, 25, 50);
		add_custom_task(0, 30, 75);

		run_custom_prog(sched_with_edf);
	}
	if(run_tests || 0) {
		init_task_buf_state();
		init_custom_prog(STD_DURATION, "test-comp-rm-hard");
		add_custom_task(0, 25, 50);
		add_custom_task(0, 30, 75);
		run_custom_prog(sched_with_rm_hard);
	}
	if(run_tests || 0) {
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

/*int j=0;
int test=0;

	sch_task* temp=NULL;
	if (tasks_remain() || i>0 || peek_task()|| test) { // Check if there are more tasks to be processed
		test=0;
		queue[i]=get_current_sch_task();



		while (1) {
			i++;
			queue[i]=get_current_sch_task();
			if (queue[i]==NULL) {
				i--;
				break;
			}

		}

		sort();



		sch_task* current=peek_task();
		if (!peek_task() && queue[i]!=NULL) {
			printf("Inne %d\n",i);
			process_task(queue[i]);
			queue[i]=NULL;
			printf("Prosseseras: %p\n",peek_task());
			if (i>0) i--;
			else {test=1;}
		}
	else if (queue[i]!=NULL && current->duration>queue[i]->duration) {
			temp=preempt_task();
			process_task(queue[i]);
			queue[i]=temp;

	}*/
