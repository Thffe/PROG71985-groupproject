#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"

void welcomeMenu();
TASK* addTask(TASK*, int*);
void writeTasks(FILE*, char*, TASK*, int);
void printAllTasks(TASK*, int);