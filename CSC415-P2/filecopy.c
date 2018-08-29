#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//You may also add more include directives as well.

//THIS VALUE CANNOT BE CHANGED.
//You should use this value when creating your buffer.
// And also to limit the amount each read CAN do.
#define BUFF_MAX 13

int main(int argc, char const *argv[])
{
	char readBuffer[BUFF_MAX] = {0};
	char fileToCopy[100], fileToCopyTo[100];  // declaring variables 

	int source; 
	int destination;

	size_t numberOfbytesRead = 0; 
	size_t numberOfbytesWritten = 0; 
	size_t totalNumberBytesRead = 0;
	
	char * name = "Ahmad Rangeen";
	printf("Welcome to the File Copy Program by %s!\n" , name);

	printf("Enter the name of the file to copy from : ");
	scanf("%s", fileToCopy);

	printf("Enter the name of the file to copy to : ");
	scanf("%s", fileToCopyTo);

	//open file for reading 
	source = open(fileToCopy, O_RDONLY);
	if(source < 0)
	{
		perror("Error opening the file to copy\n");
		close(source);
		return -1;
	}

	// open another file for writing 
	destination = open(fileToCopyTo, O_WRONLY|O_EXCL|O_CREAT, 0);

	if(destination < 0)
	{
		perror("Error making the file to copy to.");
		close(source);
		close(destination);
		return -1;
	}

	do {
		// read from file 
		numberOfbytesRead = read(source, readBuffer, BUFF_MAX - 1 );
		//write to file
		numberOfbytesWritten = write(destination, readBuffer , numberOfbytesRead);
		//updates the bytes being read
		totalNumberBytesRead += numberOfbytesWritten;

	} while (numberOfbytesRead != 0);

	printf("File Copy Successful, %lu bytes copied\n", totalNumberBytesRead);
	close(source);
	close(destination);

	return 0;
}