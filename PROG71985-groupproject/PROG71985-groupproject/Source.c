/*
William Kubica
Anthony Rooyakkers
Abdelrahman Hashad

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

int main(void)
{
	FILE* fpRead;
	FILE* fpWrite;
	char inFile[] = "tasks.txt";
	char outFile[] = "tasks.txt";
	//Modified by AR to make program create file if there is no file found
	if (!createFile())
	{
		fprintf(stderr, "Can't open %s for reading\n", inFile);
		printf("Generating blank file\n");
		fpRead = fopen(inFile, "w"); //create a new file by writing
		fclose(fpRead); //close writing file
		fpRead = fopen(inFile, "r"); //open for reading
	}
	else {
		//file found open for reading
		fpRead = fopen(inFile, "r");
	}
	//end of AR modification

	TASK* tasks = NULL;
	char line[MAXSTRING];
	int numofTasks;

	//getting the number of total tasks from the top of the save file
	fgets(line, MAXSTRING, fpRead);
	numofTasks = atoi(line);

	if (numofTasks > 0)
	{
		printf("%d tasks found\n", numofTasks);
		if ((tasks = (TASK*)malloc(sizeof(TASK) * numofTasks)) == NULL)
		{
			fprintf(stderr, "error allocating memory\n");
			exit(1);
		}
		for (int i = 0; i < numofTasks; i++)
		{
			tasks[i] = readTask(fpRead);
		}
	}
	else
	{
		printf("No tasks found\n");
		numofTasks = 0;
	}

	if ((fpWrite = fopen(outFile, "w")) == NULL)
	{
		fprintf(stderr, "Can't open %s for writing\n", outFile);
		exit(EXIT_FAILURE);
	}
	writeTasks(fpWrite, outFile, tasks, numofTasks);

	int option;
	do
	{
		welcomeMenu();
		if (scanf_s("%d", &option))
		{
			clearInputSt();
			switch (option)
			{

			case 1:
				tasks = addTask(tasks, &numofTasks);
				writeTasks(fpWrite, outFile, tasks, numofTasks);
				break;
			case 2:
				deleteTask(tasks, &numofTasks);
				break;
			case 3:
				updateTask(tasks, numofTasks);
				break;
			case 4:
				printAllTasks(tasks, numofTasks);
				break;
			case 5:
				printSingleTask(tasks, numofTasks);
				break;
			case 6:
				printRangeTasks(tasks, numofTasks);
				break;
			case 7:
				searchForTask(tasks, numofTasks);
				break;
			case 8:
				break;
			default:
				printf("Invalid entry\n");
				break;
			}
		}
		else
		{
			printf("Invalid entry\n");
			clearInputSt();
		}
	} while (option != 8);

	fclose(fpRead);
	fclose(fpWrite);
	free(tasks);
	printf("\n");
	return 0;
}

//for checking if the file already exists or needs to be created - AR
bool createFile() {
	FILE* fptr;
	if (fptr = fopen("tasks.txt", "r") == NULL) {
		return false; //file not found
	}
	else {
		if (fptr != 0)
			fclose(fptr);

		return true;//file found
	}
}

TASK* addTask(TASK* tasks, int* numofTasks)
{

	//getting the order of new task
	int neworder;
	printf("Enter an order (enter -1 to exit)\n");
	do
	{
		scanf_s("%d", &neworder);
		clearInputSt();
		if (neworder == -1)
		{
			return tasks;
		}
	} while (neworder <= 0);

	//setting new task's order to the lowest order + 1,
	//only if new task's order is greater than lowest order + 1
	if (neworder > *(numofTasks)+1)
	{
		neworder = *(numofTasks)+1;
		printf("defaulting to order %d\n", neworder);
	}
	*(numofTasks) = *(numofTasks)+1;

	TASK* newtasks;
	if ((newtasks = (TASK*)malloc(sizeof(TASK) * *numofTasks)) == NULL)
	{
		fprintf(stderr, "error allocating memory\n");
		exit(1);
	}
	//setting all tasks that come before the new task
	for (int i = 0; i < neworder - 1; i++)
	{
		newtasks[i] = tasks[i];
	}

	//slotting in the new task
	char str[MAXSTRING];
	printf("Enter the task\n");
	fgets(str, MAXSTRING, stdin);
	//clearInputSt();
	newtasks[neworder - 1] = createTask(neworder, str);

	//setting all tasks that come after the new task
	for (int i = neworder; i < *numofTasks; i++)
	{
		newtasks[i] = tasks[i - 1];
		incOrder(&newtasks[i]);
	}

	//asking for confirmation
	printf("\nTask to be added:\n");
	printTask(&newtasks[neworder - 1]);
	int conf;
	printf("\nIs this ok?\n0) no\n1) yes\n");

	scanf_s("%d", &conf);
	clearInputSt();
	if (conf == 1)
	{
		printf("new task has been added\n");
		free(tasks);
		return newtasks;
	}
	else
	{
		printf("new task has not been added\n");
		free(newtasks);
		*(numofTasks) = *(numofTasks)-1;
		return tasks;
	}
}

void deleteTask(TASK* tasks, int* numofTasks)
{
	printf("Enter the order number of the task that you would like to delete.\n");



}

void updateTask(TASK* tasks, int* numofTasks)
{
	printf("Enter the order number of the task that you would like to update.\n");

	int selectedorder;
	char* newtask[MAXSTRING];

	scanf_s("%d", &selectedorder);
	clearInputSt();
		if (selectedorder >= 1 || selectedorder <= numofTasks)
		{
			printf("Enter the updated task to replace the current task.\n");
			scanf_s("%s", newtask);

			tasks->order = selectedorder;

			setText(tasks, newtask);

			//asking for confirmation
			printf("\nTask to be added:\n");
			printTask(&newtask[selectedorder - 1]);
			int conf;
			printf("\nIs this ok?\n0) no\n1) yes\n");

			scanf_s("%d", &conf);
			clearInputSt();
			printf("new task has been added\n");
			
		}
		else
		{
			printf("Doesn't exist.\n");
			exit(1);
		}
}

void writeTasks(FILE* fp, char* filename, TASK* tasks, int num)
{

	//this clears the write file
	if ((fp = freopen(filename, "w", fp)) == NULL)
	{
		fprintf(stderr, "Failed to reopen %s for writing\n", filename);
		return;
	}

	fprintf(fp, "%d\n", num);
	for (int i = 0; i < num; i++)
	{
		writeTask(&tasks[i], fp);
	}
}

void printAllTasks(TASK* tasks, int num)
{
	for (int i = 0; i < num; i++)
	{
		printTask(&tasks[i]);
	}
}

//Menu item 5 - AR
void printSingleTask(TASK* tasks, int num)
{
	int taskNum;
	printf("Enter the task number you wish you view (Enter -1 to exit)");
	do
	{
		scanf_s("%d", &taskNum);
		clearInputSt();
		if (taskNum == -1)
		{
			break;
		}
		if (taskNum < num && taskNum > 0)
			printTask(&tasks[taskNum - 1]);
	} while (taskNum <= 0 && taskNum < num);
}
//Menu item 6 - AR
void printRangeTasks(TASK* tasks, int num)
{
	int lowEnd, highEnd;
	printf("Enter the lowest task number to view: ");
	if (scanf_s("%d", &lowEnd) && lowEnd > 0 && lowEnd < num) //user input is non negative and less than the total number of tasks
	{
		printf("Enter the highest task number to view: ");
		if (scanf_s("%d", &highEnd) && highEnd > lowEnd && highEnd <= num)
		{
			printf("\nDisplaying tasks %d through %d\n", lowEnd, highEnd);
			while (lowEnd <= highEnd)
			{
				printTask(&tasks[lowEnd - 1]);
				lowEnd++;
			}
		}
		else
		{
			printf("High end out of bounds\n");
			clearInputSt();
		}
	}
	else
	{
		printf("Low end out of bounds\n");
		clearInputSt();
	}
}
//Menu item 7 - AR
void searchForTask(TASK* tasks, int taskAmt) {
	char searchKey[MAXSTRING];
	int exitKey;
	bool searchRunning = true;
	printf("Enter a search key (Enter -1 to exit): ");
	fgets(searchKey, MAXSTRING, stdin);

	if (exitKey = atoi(searchKey) == -1)//exit if user enters -1
		searchRunning = false;
	if (searchRunning) {
		bool taskFound = false;
		int taskNum = 0;
		printf("Searching for tasks using search key: %s", searchKey);
		while (!taskFound && taskNum < taskAmt) {
			if (!strcmp(searchKey, tasks[taskNum].text)) {
				printf("Task found at task number %d: %s", tasks[taskNum].order, tasks[taskNum].text);
				taskFound = true;
			}
			else
				taskNum++;
		}
		if (!taskFound)
			printf("Task not found using search key: %s", searchKey);
	}
}

void clearInputSt()
{
	char c[MAXSTRING];
	fgets(c, MAXSTRING, stdin);
}
void welcomeMenu()
{
	printf("\nWelcome to your task manager\n");
	printf("1) Add new task\n");
	printf("2) Delete an existing task\n");
	printf("3) Update an existing task\n");
	printf("4) Display all tasks\n");
	printf("5) Display a single task\n");
	printf("6) Display a range of tasks\n");
	printf("7) Search for a task\n");
	printf("8) Exit\n");
}