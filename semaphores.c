#include "semaphores.h"

int semcreate(int key)
{
	int idsem;
	idsem = semget(key,1,0666|IPC_CREAT);

	return idsem;
}

void seminit(int idsem, int val)
{
	semctl(idsem,0,SETVAL,val);

	if(idsem == -1)
	{
		perror("Error en la creación del semáforo");
		exit(1);
	}

	return;		
}

void semwait(int idsem)
{
	struct sembuf s;
	s.sem_num=0;
	s.sem_op=-1;	// Wait
	s.sem_flg=SEM_UNDO;
	semop(idsem,&s,1);
	return;
}

void semsignal(int idsem)
{
	struct sembuf s;
	s.sem_num=0;
	s.sem_op=1;		// Signal
	s.sem_flg=SEM_UNDO;
	semop(idsem,&s,1);
	return;
}

void semerase(int idsem)
{
	semctl(idsem,0,IPC_RMID,0);
	return;
}