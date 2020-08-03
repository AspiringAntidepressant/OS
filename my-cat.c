//Evan Casey
//CS 451 Project 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>



int main(int argc, char **argv){

	FILE *input;
	char output;
		

	if (argc == 1){
		int tmp = fgetc(stdin);
		if (stdin != NULL){
			while (tmp != EOF){
				putchar(tmp);
				tmp = fgetc(stdin);
			}
		}
	}
	else {
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
				fprintf (stdout, "%c", output);
				output = fgetc(input);
			}
		}
	}

	fclose(input);
	return 0;
}
