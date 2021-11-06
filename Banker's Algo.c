#include<stdio.h>
#include<stdbool.h>

struct process_info
{
	int max[10];
	int allocated[10];
	int need[10];
};

int no_of_process, no_of_resource;

void input(struct process_info process[no_of_process], int available[no_of_resource])
{
	for(int i=0;i<no_of_process;i++)
	{
		printf("Enter process[%d] info\n",i);
		printf("Enter maximum need: ");
		for(int j=0;j<no_of_resource;j++)
			scanf("%d",&process[i].max[j]);
		printf("Enter no. of allocated resources for this process: ");
		for(int j=0;j<no_of_resource;j++)
		{
			scanf("%d",&process[i].allocated[j]);
			process[i].need[j]=process[i].max[j]-process[i].allocated[j];
		}
	}
	printf("\nEnter Available resources: ");
	for(int i=0;i<no_of_resource;i++)
	{
		scanf("%d",&available[i]);
	}
}

void showInfo(struct process_info process[no_of_process])
{
	printf("PID\tMaximum\tAllocated\tNeed\n");
	for(int i=0;i<no_of_process;i++)
	{
		printf("P[%d]\t",i);
		for(int j=0;j<no_of_resource;j++)
			printf("%d ",process[i].max[j]);
		printf("\t\t");
		for(int j=0;j<no_of_resource;j++)
			printf("%d ",process[i].allocated[j]);
		printf("\t\t");
		for(int j=0;j<no_of_resource;j++)
			printf("%d ",process[i].need[j]);
		printf("\n");
	}
}
bool applySafetyAlgo(struct process_info process[no_of_process], int available[no_of_resource], int safeSeq[no_of_process])
{
	bool finish[no_of_process]; //of size 5
	int work[no_of_resource];
	for(int i=0;i<no_of_resource;i++)
	{
		work[i]=available[i];
	}
	for(int i=0;i<no_of_process;i++)
	{
		finish[i]=false;
	}
	bool proceed=true;
	int k=0;
	while(proceed)
	{	
		proceed=false;
		for(int i=0;i<no_of_process;i++)
		{	bool flag = true;
			if(finish[i]==false)
			{	
				for(int j=0;j<no_of_resource;j++)
				{
					if(process[i].need[j] <= work[j])
					{
						continue; //skip the next lines and go on for the next iteration in the same loop
					}
					else
					{
						flag= false;
						break; //comes out of the inside for loop
					}
				}
				if (flag==false)
				continue; //check for the next process in the loop
				for(int j=0;j<no_of_resource;j++)
				{
					work[j]= work[j]+ process[i].allocated[j];
					
				}
				finish[i]=true;
				safeSeq[k++]=i;
				proceed =true;
			}
		}
	}
	int i;
	for(i=0;i<no_of_process&&finish[i]==true;i++)
	{
		continue;
	}
	if (i==no_of_process)
	return true;
	return false;
}

bool isSafeState(struct process_info process[no_of_process], int available[no_of_resource], int safeSeq[no_of_process])
{
	if(applySafetyAlgo(process,available,safeSeq)==true)
		return true;
	return false;
}

int main()
{
	printf("Enter no. of Processes\n");
	scanf("%d",&no_of_process);
	printf("Enter No. of resource instance in system\n");
	scanf("%d",&no_of_resource);
	
	int available[no_of_resource];
	int safeSeq[no_of_process];
	
	struct process_info process[no_of_process];
	
	printf("******Enter Details of processes*********\n");
	input(process,available);
	showInfo(process);
	
	if(isSafeState(process,available,safeSeq))
	{
		printf("\nSystem is in safe state\n");
		printf("Safe sequence is: ");
		for(int i=0;i<no_of_process;i++)
			printf("P[%d] ",safeSeq[i]);
			
	}	
	else{
		printf("\nSystem is in Unsafe state\n");
		
	}
	return 0;
}

