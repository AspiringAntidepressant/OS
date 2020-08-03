//Evan Casey
//CS 451 Project 1

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#define MAXCOM 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 

//intro to shell, lets user know what is available
void welcome(){

	printf("~~Welcome to Evan Casey's shell~~\n");
	printf("       Available Commands:\n");
	printf("             help\n");
	printf("             my-cat\n");
	printf("             my-uniq\n");
	printf("             my-wc\n");
	printf("             quit\n\n\n");

	return;
}


// Function to handle input 
// Includes history while shell is running (can up arrow)
int takeInput(char* str) 
{ 
	char* buf; 

	buf = readline("\nmyshell> "); 
	if (strlen(buf) != 0) { 
		add_history(buf); 
		strcpy(str, buf); 
		return 0; 
	} else { 
		return 1; 
	} 
} 

// Execute given simple command
void execArgs(char** parsed) 
{ 
	
	// Forking a child 
	pid_t pid = fork();
	char run[MAXCOM + 3] = "./";
	//format run path	
	strcat(run, parsed[0]);

	if (pid == -1) { 
		printf("\nFailed forking child.."); 
		return; 
	} else if (pid == 0) { 
		char *args[] = {run, parsed[1], NULL};
		if (execvp(args[0], args) < 0) { 
			printf("\nCould not execute command.."); 
		} 
		exit(0); 
	} else { 
		// waiting for child to terminate 
		wait(NULL); 
		return; 
	} 
} 

// Execute piped command (Kind of working)
void execArgsPiped(char** parsed, char** parsedpipe) 
{ 
	// 0 is read end, 1 is write end 
	int pipefd[2]; 
	pid_t p1, p2; 

	if (pipe(pipefd) < 0) { 
		printf("\nPipe could not be initialized"); 
		return; 
	} 
	p1 = fork(); 
	if (p1 < 0) { 
		printf("\nCould not fork"); 
		return; 
	} 

	if (p1 == 0) { 
		// Child 1 executing.. 
		// It only needs to write at the write end 
		close(pipefd[0]); 
		dup2(pipefd[1], STDOUT_FILENO); 
		close(pipefd[1]); 
		char run[MAXCOM + 3] = "./";
		//format run path	
		strcat(run, parsed[0]);
		char *args[] = {run, parsed[1], NULL};

		if (execvp(args[0], args) < 0) { 
			printf("\nCould not execute command 1.."); 
			exit(0); 
		} 
	} else { 
		// Parent executing 
		p2 = fork(); 

		if (p2 < 0) { 
			printf("\nCould not fork"); 
			return; 
		} 

		// Child 2 executing.. 
		// It only needs to read at the read end 
		if (p2 == 0) { 
			close(pipefd[1]); 
			dup2(pipefd[0], STDIN_FILENO); 
			close(pipefd[0]); 
			char run2[MAXCOM + 3] = "./";
			//format run path	
			strcat(run2, parsedpipe[0]);
			char *args2[] = {run2, parsed[1], NULL};
			if (execvp(args2[0], args2) < 0) { 
				printf("\nCould not execute command 2.."); 
				exit(0); 
			} 
		} else { 
			// parent executing, waiting for two children 
			wait(NULL); 
			wait(NULL); 
		} 
	} 
} 

// Help command builtin 
void openHelp() 
{ 
	printf("       Available Commands:\n");
	printf("             help\n");
	printf("             my-cat\n");
	printf("             my-uniq\n");
	printf("             my-wc\n");
	printf("             quit\n\n\n");


	return; 
} 

// Function to execute builtin commands 
int ownCmdHandler(char** parsed) 
{ 

	int NoOfOwnCmds = 5, i, switchOwnArg = 0; 
	char* ListOfOwnCmds[NoOfOwnCmds]; 

	ListOfOwnCmds[0] = "quit"; 
	ListOfOwnCmds[1] = "my-cat"; 
	ListOfOwnCmds[2] = "my-uniq"; 
	ListOfOwnCmds[3] = "my-wc";
	ListOfOwnCmds[4] = "help"; 

	for (i = 0; i < NoOfOwnCmds; i++) { 
		if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) { 
			switchOwnArg = i + 1; 
			break; 
		} 
	} 
	
	switch (switchOwnArg) { 

		case 1: 
			printf("\nThis is the end\n"); 
			exit(0); 
		case 2: 
			execArgs(parsed); 
			return 1;
		case 3: 
			execArgs(parsed);
			return 1;
		case 4: 
			execArgs(parsed);
			return 1;
		case 5:
			openHelp();
			return 1;
		default: 
			break; 

		} 

	return 1; 
} 


int ownCmdHandlerPiped(char** parsed, char** parsedpipe) 
{ 

	int NoOfOwnCmds = 5, i, switchOwnArg = 0; 
	char* ListOfOwnCmds[NoOfOwnCmds]; 

	ListOfOwnCmds[0] = "quit"; 
	ListOfOwnCmds[1] = "my-cat"; 
	ListOfOwnCmds[2] = "my-uniq"; 
	ListOfOwnCmds[3] = "my-wc";
	ListOfOwnCmds[4] = "help"; 

	for (i = 0; i < NoOfOwnCmds; i++) { 
		if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) { 
			switchOwnArg = i + 1; 
			break; 
		} 
	} 
	
	switch (switchOwnArg) { 

		case 1: 
			printf("\nThis is the end\n"); 
			exit(0); 
		case 2: 
			execArgsPiped(parsed, parsedpipe); 
			return 2;
		case 3: 
			execArgsPiped(parsed, parsedpipe);
			return 2;
		case 4: 
			execArgsPiped(parsed, parsedpipe);
			return 2;
		case 5:
			openHelp();
			return 1;
		default: 
			break; 

		} 

	return 2; 
} 


// function for finding pipe 
int parsePipe(char* str, char** strpiped) 
{ 
	int i; 
	for (i = 0; i < 2; i++) { 
		strpiped[i] = strsep(&str, "|"); 
		if (strpiped[i] == NULL) 
			break; 
	} 

	if (strpiped[1] == NULL){
		return 0; // returns zero if no pipe is found.
	} 
	else { 
		return 1; 
	} 
} 

// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
	int i; 

	for (i = 0; i < MAXLIST; i++) { 
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL) 
			break; 
		if (strlen(parsed[i]) == 0) 
			i--; 
	}

} 

int processString(char* str, char** parsed, char** parsedpipe) 
{ 

	char* strpiped[2]; 
	int piped = 0; 

	piped = parsePipe(str, strpiped); 

	if (piped) { 
		
		parseSpace(strpiped[0], parsed); 
		parseSpace(strpiped[1], parsedpipe); 
		return 1 + piped;

	}

	else { 

		parseSpace(str, parsed);
		return 1; 
	} 

} 


int main() 
{ 
	//define input arrays and future arrays to hold all args
	char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
	char* parsedArgsPiped[MAXLIST]; 
	int execFlag = 0; 
	//run initial message to user
	welcome();
	
	//run until you don't
	while (1) { 
		// take input 
		if (takeInput(inputString)) 
			continue; 
		/* process
		return 1 if it is a simple command
		return 2 if it involves piping
		*/
		execFlag = processString(inputString, 
		parsedArgs, parsedArgsPiped);

		// execute based on pipe or not
		if (execFlag == 1){
			ownCmdHandler(parsedArgs);
		}

		if (execFlag == 2){
			ownCmdHandlerPiped(parsedArgs, parsedArgsPiped); 
		}
	} 
	return 0; 
} 

