#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"

void welcomeMenu();
TASK* addTask(TASK*, int*);
void clearInputSt();
void writeTasks(FILE*, char*, TASK*, int);
void printAllTasks(TASK*, int);
void printSingleTask(TASK* tasks, int);
void printRangeTasks(TASK* tasks, int, int);
void searchForTask(TASK*, int, char[]);