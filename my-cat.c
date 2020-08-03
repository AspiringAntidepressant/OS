//Evan Casey
//CS 451 Project 1

#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv){

	FILE *input;
	char output;
	//check for input
	if (argc == 1){
		printf("No input file given.\n");
		exit(0);
	}
	//input found
	else{
		//open file in read mode
		input = fopen(argv[1], "r");
		//check that it is a real/useable file
		if (input == NULL){
			printf("\nmy-cat: cannot open %s\n", argv[1]);
			exit(1);
		}
		//read file
		else{
			output = fgetc(input);
			while (output != EOF){
				printf ("%c", output);
				output = fgetc(input);
			}
		}
	}

	fclose(input);
	return 0;
}
