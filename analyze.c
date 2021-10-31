#import <stdio.h>

#define LENGTH 7


int read(char* file, int rows) {

  int i=0;
  int index=0;
  int arrival=0;
  int proc_time=0;
  int period=0;
  int abs_deadline=0;
  int finished=0;
  int observed_proc_time=0;
  int total_observed_proc_time=0;
  int total_observed_proc_time2=0;
  int turnaround=0;
  int nrlate=0;
  int late5=0;
  int  late10=0;
  int  late20=0;
  int  late40=0;
  int  late80=0;
  int nrtask2=0;
  int nrtask1=0;
  int nrtask0=0;


  int total_response=0;
int total_lateness=0;

FILE *fp=fopen(file,"r");
printf("File: %s\n",file);

while (i<rows) {
    fscanf(fp,"f:%d:%d:%d:%d:%d:%d:%d\n",&index,&arrival,&proc_time,&period,&abs_deadline,&finished,&observed_proc_time);
    if (index==2) nrtask2++;
    if (index==1) nrtask1++;
    if (index==0) nrtask0++;

    total_response=total_response+finished-arrival;
    total_lateness=total_lateness+finished-abs_deadline;
    if (index==1)  total_observed_proc_time=total_observed_proc_time+observed_proc_time;
    if (index==1)  turnaround=turnaround+(finished-arrival);

    total_observed_proc_time2=total_observed_proc_time2+observed_proc_time;

    if (proc_time!=observed_proc_time ) //printf("\nrad:%d f:%d:%d:%d:%d:%d:%d:%d\n",i,index,arrival,proc_time,period,abs_deadline,finished,observed_proc_time);
    if (finished-abs_deadline>0 ) {
      nrlate++;
         printf("\nrad:%d f:%d:%d:%d:%d:%d:%d:%d\n",i+1,index,arrival,proc_time,period,abs_deadline,finished,observed_proc_time);
      if (finished-abs_deadline>0 && finished-abs_deadline<5) late5++;
    if (finished-abs_deadline>5 && finished-abs_deadline<10) late10++;
    if (finished-abs_deadline>10 && finished-abs_deadline<20) late20++;
    if (finished-abs_deadline>20&& finished-abs_deadline<40) late40++;
    if (finished-abs_deadline>40&& finished-abs_deadline<80) late80++;
    }
    i++;

    //printf("i: %d total response time: %d total lateness: %d \n",i,total_response,total_lateness);

}
i--;
printf("\n\n");
//printf("nr task 0 %d nr task 1 %d",nrtask0,nrtask1);
//printf("nr task 2 %d nr task 2 late %d",nrtask2,nrlate);
printf("Avagrege turnaround task 1: %f\n",(float) turnaround/i);
printf("Avagrege observed_proc_time task 1: %f\n",(float)total_observed_proc_time/i);
printf("Avagrege observed_proc_time: %f\n",(float)total_observed_proc_time2/i);
printf("average response time: %f average lateness: %f Nr of late tasks: %d Nr 0-5 late: %d Nr 5-10 late: %d Nr 10-20 late: %d Nr 20-40 late: %d Nr 40-80 late: %d  \n\n",(float) total_response/i,(float) total_lateness/i,nrlate,late5,late10,late20,late40,late80);

fclose(fp);
return 0;

}

int main() {

read("trace-prog1-edf.data",1124);
read("trace-prog1-rm.data",1124);
read("trace-prog2-edf.data",1125);
read("trace-prog2-rm.data",1125);
  return 0;
}
//1-edf:38 9069
//1-rm: 39 9071
