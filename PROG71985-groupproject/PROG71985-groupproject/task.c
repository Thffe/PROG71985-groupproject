
#include "task.h"

TASK createTask(int o, char t[]) {
	TASK ta;
	ta.order = o;
	strncpy_s(ta.text, MAXSTRING, t, MAXSTRING);
	return ta;
}

int getOrder(TASK* t) {
	return t->order;
}
char* getText(TASK* t) {
	return t->text;
}
void setOrder(TASK* t, int o) {
	t->order = o;
}
void setText(TASK* t, char c[]) {
	strncpy_s(t->text, MAXSTRING, c, MAXSTRING);
}
void incOrder(TASK* t) {
	t->order++;
}
void decOrder(TASK* t) {
	t->order--;
}
TASK readTask(FILE* fp) {
	char line[MAXSTRING];
	int id;
	
	fgets(line, MAXSTRING, fp);
	id = atoi(line);
	fgets(line, MAXSTRING, fp);
	return createTask(id, line);
}

void writeTask(TASK* t, FILE* fp) {
	fprintf(fp, "%d\n", t->order);
	fprintf(fp, "%s", t->text);
}

void printTask(TASK* t) {
	printf("%d: %s", t->order, t->text);
}