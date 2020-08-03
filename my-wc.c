//Evan Casey
//CS 451 Project 1

#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv){

	FILE *input;
	char output;
	int wrdcnt = 0, lncnt = 0;

	//check if real file
	if (argc == 1){
		printf("No input file given.\n");
		exit(0);
	}
	else{
		//open file in read mode
		input = fopen(argv[1], "r");
		//check that it is a real/useable file
		if (input == NULL){
			printf("\nmy-wc: cannot open %s\n", argv[1]);
			exit(1);
		}
		else{
			//read file
			output = fgetc(input);
			while (output != EOF){
				// ' ' means new word encountered
				if (output == ' '){
					wrdcnt++;
				}
				// '\n' means new line and word encountered
				if (output == '\n'){
					wrdcnt++;
					lncnt++;
				}

				output = fgetc(input);
			}

			printf("\n The word count is: %d\n",wrdcnt);
			printf("\n The line count is: %d\n",lncnt);
			}
	}
	fclose(input);
	return 0;
}
