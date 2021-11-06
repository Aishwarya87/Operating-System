PIPE IS UNIDIRECTIONAL. BIDIrectional communication with the help of two pipes.

 fork switches midway between child and parent; if read is executed before write; then read is blocked and control gets to the other block for write system call.
  
#include<stdio.h> //printf
#include<unistd.h> //fork, pipe, read, write system calls
#include<string.h> //strlen, memset function
#include<stdlib.h> //for exit method
#include<sys/wait.h> //wait system call
#define SIZE 30
int main()
{
	int fd1[2],fd2[2]; //file descriptor array
	int status = pipe(fd1);
  pipe(fd2);
	if (status == -1)
	{
		printf("file creation FAILED");
		exit(1);
	}
	int p=fork();
	if(p<0)
	{
		printf("Fork failed");// too many processes already; finite resources
		exit(1); 
	}
	if(p>0) //parent executes
	{
		close(fd1[0]);
    close(fd2[1]);
		char *msg = "Hi child; this is the parent process";
		int wr = write(fd1[1],msg,strlen(msg));
    int rd = read(fd2[0],buff,SIZE);
		close(fd[1]);
		wait(NULL); // to not make orphan process; parent process waits for child process
	}
	else
	{
		close(fd1[1]);
    close(fd2[0]);
		char buff[SIZE];
		memset(buff,'\0',SIZE); //because printf prints till \0 is encountered. 
		int rd= read(fd1[0],buff,SIZE);  //here size represents how many bytes you want to read
    int wr= write(fd2[1],msg,strlen(msg));
		printf("Message from parent is: \n");
		printf("%s\n",buff); //or write(1,buff,SIZE); write system call is faster. 
    //printf is a buffer function
		close(fd[0]);
		
	}
	return 0;
}


