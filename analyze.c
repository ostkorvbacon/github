#import <stdio.h>

#define LENGTH 7


int read(char* file, int rows) {

  int i=0;

  int temp[LENGTH];
  int index=0;
  int arrival=0;
  int proc_time=0;
  int period=0;
  int abs_deadline=0;
  int finished=0;
  int observed_proc_time=0;

  int total_response=0;
int total_lateness=0;

FILE *fp=fopen(file,"r");
printf("File: %s\n",file);
while (i<rows) {
    fscanf(fp,"f:%d:%d:%d:%d:%d:%d:%d\n",&index,&arrival,&proc_time,&period,&abs_deadline,&finished,&observed_proc_time);
    total_response=total_response+finished-arrival;
    total_lateness=total_lateness+finished-abs_deadline;
    i++;

    //printf("i: %d total response time: %d total lateness: %d \n",i,total_response,total_lateness);

}
i--;
printf("average response time: %d average lateness: %d \n\n",total_response/i,total_lateness/i);
fclose(fp);
return 0;

}

int main() {

read("trace-prog1-edf.data",1024);
read("trace-prog1-rm.data",1024);
read("trace-prog2-edf.data",1025);
read("trace-prog2-rm.data",1025);
  return 0;
}
//1-edf:38 9069
//1-rm: 39 9071
