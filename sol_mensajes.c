#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <wait.h>

#define CICLOS 10
char *pais[3]={"Peru","Bolvia","Colombia"};

typedef struct {
	long msg_type;		// Tipo de mensaje, debe ser long
	char mensaje[100];	// Contenido
	} MSGTYPE; 

int msgqid;

void receptor();
void transmitter(int);

int main()
{
	int msgqid = msgget(0x1234,0666|IPC_CREAT);
	int pid;
	int status;
	int args[3];
	int i;

	srand(getpid());

	for(i=0;i<3;i++)
	{
		// Crea un nuevo proceso hijo que ejecuta la función proceso()
		pid=fork();
		
		if(pid==0)
			transmitter(i);

		receptor();	// El padre es el receptor
		wait(NULL);
		wait(NULL);
		msgctl(msgqid,IPC_RMID,NULL);
		return(0);
	}

	for(i=0;i<3;i++)
		pid = wait(&status);
}

void transmitter(int i)
{
	int k;
	int l;
	MSGTYPE m;

	for(k=0;k<CICLOS;k++)
	{
		// Entrada a la sección crítica
		m.msg_type=1;
		printf("Entra %s",pais[i]);
		msgsnd(msgqid,&m,sizeof(MSGTYPE)-sizeof(long),0);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		// Salida de la sección crítica

		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
	printf("Aqui si llega\n");
	m.msg_type=1;
	strcpy(m.mensaje,"Fin");
	msgsnd(msgqid,&m,sizeof(MSGTYPE)-sizeof(long),0);

	exit(0); // Termina el proceso
}

void receptor()
{
	MSGTYPE m;	// Donde voy a recibir el mensaje
	int retval;
	
	do
	{
		retval=msgrcv(msgqid,&m,sizeof(MSGTYPE)-sizeof(long),1,0);
		//printf("Recibido: %s\n",m.mensaje);
	}
	while(strcmp(m.mensaje,"Fin")!=0); // Hasta que el mensaje sea "Fin"
	return;
}