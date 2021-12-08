#pragma once
#define MAXSTRING 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct task {
	int order;
	char text[MAXSTRING];
}TASK;

TASK createTask(int, char[]);
int getOrder(TASK*);
char* getText(TASK*);
void setOrder(TASK*, int);
void setText(TASK*, char[]);
TASK readTask(FILE*);
void writeTask(TASK*, FILE*);
void printTask(TASK*);