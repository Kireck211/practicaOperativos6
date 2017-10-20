ll :	sol_procesos sol_semaforos sol_mensajes

sol_mensajes : sol_mensajes.o
		gcc -o sol_mensajes sol_mensajes.o 

sol_mensajes.o : sol_mensajes.c
		gcc -c sol_mensajes.c 

sol_procesos : sol_procesos.o
		gcc -o sol_procesos sol_procesos.o -l pthread

sol_procesos.o : sol_procesos.c
		gcc -c sol_procesos.c -l pthread

sol_semaforos : sol_semaforos.o
		gcc -o sol_semaforos sol_semaforos.o 

sol_semaforos.o : sol_semaforos.c
		gcc -c sol_semaforos.c

clean :
		rm sol_mensajes.o sol_procesos.o sol_semaforos.o sol_mensajes sol_procesos sol_semaforos
