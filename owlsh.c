#include <stdio.h>



int main (int argc, char** argv) 
{



	//if there be args, then do the batch mode
	if (argc > 1) {


		return 0;
	}


	//else, it's interactive mode time

	//this is the size of the buffer when reading commands
	const BUFFER_SIZE = 2048;
	
	//interactive mode time
	while (1) 
	{
		printf("\nowlsh> ");



		//make a buffer (aka a c style array) that is big
		char buffer[BUFFER_SIZE * sizeof(char)]; 



		//source: https://c-for-dummies.com/blog/?p=1112
		ssize_t getline(buffer, BUFFER_SIZE, stdin);


	}
}

