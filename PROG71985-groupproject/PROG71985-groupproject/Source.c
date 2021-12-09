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
	

	int option, userDefinedTaskNum;
	do {
		welcomeMenu();
		if (scanf_s("%d", &option)) {

			switch (option) {

			case 1:
				tasks = addTask(tasks, &numofTasks);
				writeTasks(fpWrite, outFile, tasks, numofTasks);
				break;
			case 2:

				break;
			case 3:
				
				break;
			case 4:
				printAllTasks(tasks, numofTasks);
				break;
			case 5:
				printf("Enter the task number you wish you view: ");
				if (scanf_s("%d", &userDefinedTaskNum) && userDefinedTaskNum <= numofTasks && userDefinedTaskNum > 0) {
					printSingleTask(tasks, userDefinedTaskNum);
				}
				else {
					printf("Task number out of readable task range or invalid.");
				}
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			default:
				printf("Invalid entry\n");
				break;
			}
		}
		else {
			printf("Invalid entry\n");
		}
	} while (option != 8);

	fclose(fpRead);
	fclose(fpWrite);
	free(tasks);
	printf("\n");
	return 0;
}

TASK* addTask(TASK* tasks, int* numofTasks) {

	//getting the order of new task
	int neworder;
	printf("Enter a order (enter -1 to exit)\n");
	do {
		scanf_s("%d", &neworder);

		if (neworder == -1) {
			return tasks;
		}
	} while (neworder <= 0);




	//setting new task's order to the lowest order + 1,
	//only if new task's order is greater than lowest order + 1
	if (neworder > *(numofTasks)+1) {
		neworder = *(numofTasks)+1;
		printf("defaulting to order %d\n", neworder);
	}
	*(numofTasks) = *(numofTasks)+1;

	TASK* newtasks;
	if ((newtasks = (TASK*)malloc(sizeof(TASK) * *numofTasks)) == NULL) {
		fprintf(stderr, "error allocating memory\n");
		exit(1);
	}
	//setting all tasks that come before the new task
	for (int i = 0; i < neworder - 1; i++) {
		newtasks[i] = tasks[i];
	}

	//slotting in the new task
	char str[MAXSTRING];
	printf("Enter the task\n");
	fgets(str, MAXSTRING, stdin);
	fgets(str, MAXSTRING, stdin);
	newtasks[neworder - 1] = createTask(neworder, str);


	//setting all tasks that come after the new task
	for (int i = neworder; i < *numofTasks; i++) {
		newtasks[i] = tasks[i - 1];
		incOrder(&newtasks[i]);
	}

	//asking for confirmation
	printf("\nTask to be added:\n");
	printTask(&newtasks[neworder - 1]);
	int conf;
	printf("\nIs this ok?\n0) no\n1) yes\n");

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

void printSingleTask(TASK* tasks, int num) {
	printTask(&tasks[num - 1]);
}

void welcomeMenu() {
	printf("\nWelcome to your task manager\n");
	printf("1) Add new task\n");
	printf("2) Delete existing task\n");
	printf("3) Update existing task\n");
	printf("4) Display all tasks\n");
	printf("5) Display a single task\n");
	printf("6) Display a range of tasks\n");
	printf("7) Search for a task\n");
	printf("8) Exit\n");
}