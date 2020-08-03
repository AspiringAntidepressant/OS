//Evan Casey
//CS 451 Project 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINES 512
#define MAX_CHARS 1024


int main(int argc, char **argv){

	FILE *input;
	char inputArr[MAX_LINES][MAX_CHARS];
	int i = 0, total = 0;

	//check for input
	if (argc == 1){
		input = stdin;
	}
	else{
		//open file in read mode
		input = fopen(argv[1], "r");
		//check that it is a real/useable file
		if (input == NULL){
			printf("\nmy-uniq: cannot open %s\n", argv[1]);
			exit(1);
		}
	}
	//Store file in array
	while (fgets(inputArr[i], MAX_LINES, input)){
		inputArr[i][strlen(inputArr[i])-1] = '\0';
		i++;
	}
	total = i;
	
	//remove duplicates
	int h, j, k;
	for (h = 0; h<total; h++){
		for (j = h+1; j < total; j++){
			//if any duplicates are found
			if (strcmp(inputArr[h], inputArr[j]) == 0){
				for (k = j; k < total; k++){
					strcpy(inputArr[k], inputArr[k+1]);
				}
				//Decrement total size and j if deletion occurs
				total--;
				j--;
			}
		}
	}
	//print updated info
	for(i = 0; i< total; i++){
		fprintf (stdout, "%s\n", inputArr[i]);
	}

	fclose(input);
	return 0;
}




































