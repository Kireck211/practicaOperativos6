#include <sys/sem.h>

int semcreate(int);
void seminit(int, int);
void semwait(int);
void semsignal(int);
void semerase(int);
