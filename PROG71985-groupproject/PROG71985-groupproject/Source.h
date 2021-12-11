#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"

void welcomeMenu();
TASK* addTask(TASK*, int*);
void deleteTask(TASK*, int*);
void updateTask(TASK*, int*);
void clearInputSt();
void writeTasks(FILE*, char*, TASK*, int);
void printAllTasks(TASK*, int);
void printSingleTask(TASK*, int);
void printRangeTasks(TASK*, int);
void searchForTask(TASK*, int);
bool createFile();