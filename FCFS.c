#include<stdio.h>
#include<stdlib.h>
struct process_struct
{
	int pid;
	int at;
	int bt;
	int ct,wt,tat,rt,start_time;
}ps[100];


int comparatorAt(const void* a, const void* b)
{
	int x= ((struct process_struct *)a) -> at;
	int y= ((struct process_struct*)b) ->at;
	if(x<y)
	return -1;
	else if (x>=y)
	return 1;
}

int findmax(int a,int b)
{
	return a>b?a:b;
}

int main()
{
	int n;
	float sum_tat=0, sum_wt=0, sum_rt=0 , total_idle_time=0;
	int length_cycle;
	float cpu_utilization;
	printf("Enter the total number of processes: ");
	scanf("%d",&n);
	
	
	for(int i=0;i<n;i++)
	{
		printf("\nEnter Process %d Arrival Time: ",i);
		scanf("%d",&ps[i].at);
		ps[i].pid=i;
	}
	
	for(int i=0;i<n;i++)
	{
		printf("\nEnter Process %d Burst Time: ",i);
		scanf("%d",&ps[i].bt);
	}
	
	//Sort the structure based on the arrival time
	//qsort is inbuilt
	qsort((void*)ps, n, sizeof(struct process_struct),comparatorAt);
	
	//Calculations
	for(int i=0;i<n;i++) //for each box
	{
		ps[i].start_time= (i==0) ? ps[i].at : findmax(ps[i].at,ps[i-1].ct);
		ps[i].ct = ps[i].start_time + ps[i].bt;
		ps[i].tat = ps[i].ct -ps[i].at;
		ps[i].wt = ps[i].tat - ps[i].bt;
		ps[i].rt = ps[i].wt;
		
		sum_tat +=ps[i].tat;
		sum_wt+= ps[i].wt;
		sum_rt+=ps[i].rt;
		total_idle_time+= (i==0) ? 0: (ps[i].start_time- ps[i-1].ct);
		
		
	}
	length_cycle = ps[n-1].ct-ps[0].start_time;
	
	printf("\nProcess No. \tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
	}
	
	printf("\n");
	
	cpu_utilization = (float) (length_cycle- total_idle_time)/length_cycle;
	
	printf("\nAverage Turn around time= %f", sum_tat/n);
	printf("\nAverage waiting time= %f", sum_wt/n);
	printf("\nAverage response time= %f", sum_rt/n);
	printf("\nThroughput= %f", n/(float)length_cycle);
	printf("\nCPU utilization(Percentage) = %f", cpu_utilization*100);
	printf("\n");
	return 0;
}

