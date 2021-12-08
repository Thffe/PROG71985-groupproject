/*
William Kubica

PROG71985 Group Project


3
1
something
2
sometig
3
sometin

*/

#include "Source.h"

int main(void) {

	FILE* fpRead;
	FILE* fpWrite;
	char inFile[] = "tasks.txt";
	char outFile[] = "tasks.txt";

	if ((fpRead = fopen(inFile, "r")) == NULL) {
		fprintf(stderr, "Can't open %s for reading\n", inFile);
		exit(EXIT_FAILURE);
	}

	TASK* tasks = NULL;
	char line[MAXSTRING];
	int numofTasks;

	//getting the number of total tasks from the top of the save file
	fgets(line, MAXSTRING, fpRead);
	numofTasks = atoi(line);

	if (numofTasks > 0) {
		printf("%d tasks found\n", numofTasks);
		if ((tasks = (TASK*)malloc(sizeof(TASK) * numofTasks)) == NULL) {
			fprintf(stderr, "error allocating memory\n");
			exit(1);
		}
		for (int i = 0; i < numofTasks; i++) {
			tasks[i] = readTask(fpRead);
		}
	}
	else {
		printf("No tasks found\n");	
		numofTasks = 0;
	}


	if ((fpWrite = fopen(outFile, "w")) == NULL) {
		fprintf(stderr, "Can't open %s for writing\n", outFile);
		exit(EXIT_FAILURE);
	}
	writeTasks(fpWrite, outFile, tasks, numofTasks);
	

	int option;
	do {
		welcomeMenu();
		if (scanf_s("%d", &option)) {

			switch (option) {

			case 1:
				tasks = addTask(tasks, &numofTasks);
				writeTasks(fpWrite, outFile, tasks, numofTasks);
				break;
			case 3:
				printAllTasks(tasks, numofTasks);
				break;
			case 4:
				break;
			default:
				printf("Invalid entry\n");
				break;

			}
		}
		else {
			printf("Invalid entry\n");
		}
	} while (option != 4);

	fclose(fpRead);
	fclose(fpWrite);
	free(tasks);
	printf("\n");
	return 0;
}

TASK* addTask(TASK* tasks, int* numofTasks) {

	//getting the order of new task
	int num;
	printf("Enter a order (enter -1 to exit)\n");
	do {
		scanf_s("%d", &num);

		if (num == -1) {
			return tasks;
		}
	} while (num <= 0);

	
	*(numofTasks) = *(numofTasks) + 1;

	//setting new task's order to the lowest order + 1,
	//only if new task's order is greater than lowest order + 1
	if (num > *(numofTasks)+1) {
		num = *(numofTasks)+1;
	}

	TASK* newtasks;
	if ((newtasks = (TASK*)malloc(sizeof(TASK) * *numofTasks)) == NULL) {
		fprintf(stderr, "error allocating memory\n");
		exit(1);
	}
	//setting all tasks that come before the new task
	for (int i = 0; i < num - 1; i++) {
		newtasks[i] = tasks[i];
	}
	//slotting in the new task
	char str[MAXSTRING];
	printf("Enter the task\n");
	scanf_s("%99[^\n]", str, MAXSTRING);
	newtasks[num-1] = createTask(num, str);

	//clearing buffer
	//char c[MAXSTRING];
	//scanf_s("%s",c,MAXSTRING);

	//setting all tasks that come after the new task
	for (int i = num; i < *numofTasks; i++) {
		newtasks[i] = tasks[i-1];
	}

	//asking for confirmation
	printf("Task to be added:\n");
	printTask(&newtasks[num - 1]);
	int conf;
	printf("Is this ok?\n0) no\n1) yes\n");
	scanf_s("%d", &conf);
	if (conf == 1) {
		printf("new task has been added\n");
		free(tasks);
		return newtasks;
	}
	else {
		printf("new task has not been added\n");
		free(newtasks);
		*(numofTasks) = *(numofTasks)-1;
		return tasks;
	}
}

void writeTasks(FILE* fp, char* filename, TASK* tasks, int num) {

	//this clears the write file
	if ((fp = freopen(filename, "w", fp)) == NULL) {
		fprintf(stderr, "Failed to reopen %s for writing\n", filename);
		return;
	}

	fprintf(fp, "%d\n", num);
	for (int i = 0; i < num; i++) {
		writeTask(&tasks[i], fp);
	}
}

void printAllTasks(TASK* tasks, int num) {
	for (int i = 0; i < num; i++) {
		printTask(&tasks[i]);
	}
}

void welcomeMenu() {
	printf("\nWelcome to your task manager\n");
	printf("1) Add new task\n");
	printf("2)\n");
	printf("3) Display all tasks\n");
	printf("4) Exit\n");
}