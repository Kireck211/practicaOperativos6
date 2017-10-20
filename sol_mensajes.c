#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <wait.h>

#define CICLOS 10

typedef struct {
	long msg_type;		// Tipo de mensaje, debe ser long
	char mensaje[100];	// Contenido
	} MSGTYPE; 


char *pais[3]={"Peru","Bolvia","Colombia"};
int msgqid;

void proceso(int i)
{
	int k;
	int l;
	int retval;
	MSGTYPE m;

	for(k=0;k<CICLOS;k++)
	{
		// Entrada a la sección crítica	
		retval = msgrcv(msgqid,&m,sizeof(MSGTYPE)-sizeof(long),1,0); // Recieve bloqueante
		printf("Entra %s",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		// Salida de la sección crítica
		
		m.msg_type=1;
		sprintf(m.mensaje,"Hola, este es el mensaje %d",i);
		msgsnd(msgqid,&m,sizeof(MSGTYPE)-sizeof(long),0); // Send no bloqueante

		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}

	exit(0); // Termina el proceso
}

int main()
{
	int pid;
	int status;
	int args[3];
	int i;

	msgqid=msgget(0x1234,0666|IPC_CREAT);
	MSGTYPE m;
	m.msg_type=1;
	sprintf(m.mensaje,"Hola, este es el mensaje %d",i);
	msgsnd(msgqid,&m,sizeof(MSGTYPE)-sizeof(long),0); // Send no bloqueante

	srand(getpid());

	for(i=0;i<3;i++)
	{
		// Crea un nuevo proceso hijo que ejecuta la función proceso()
		pid=fork();
		
		if(pid==0)
		proceso(i);
	}

	for(i=0;i<3;i++)
		pid = wait(&status);

	msgctl(msgqid,IPC_RMID,NULL);
}