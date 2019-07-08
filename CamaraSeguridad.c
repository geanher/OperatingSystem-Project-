/*
  HERNANDEZ FRIAS GERLY ANDRES
  21061052
  ING DE SISTEMAS
  SISTEMAS OPERATIVOS 

Proyecto Final Sistemas Operativos 
Programa que monitoriza la llegada de los carros y las muestra
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <signal.h>

void exit_signal(int);

int main (){

  key_t idmemoria = ftok("/bin/gerly",0424);
  signal(SIGINT, exit_signal);
  int memoriacompartida = shmget(idmemoria, sizeof(int), IPC_CREAT | 0660 );
  pid_t monpid = getpid();
  if (memoriacompartida == -1){
  	printf("%s\n","Hay un error al crear el segmento de memoria");
  	return -1;
  }
  int * via = shmat (memoriacompartida, NULL, 0);
  if (via == NULL){
  	printf("%s\n","Hay un error al vincular el segmento de memoria");
  	return -1;
  }
  for(int i=0; i<10;i++){
    via[i]=0;
  }

  while(1){
    system("clear");
    printf("\n______Monitor de Via________\n\n");
    printf("\t-------------------------\n");
    printf("via\t carros\t cola\t tiempo: %d \n",via[4]);
    printf("0\t %d\t%d\n",via[0],via[6]);
    printf("1\t %d\t%d\n",via[1],via[7]);
    printf("2\t %d\t%d\n",via[2],via[8]);
    printf("3\t %d\t%d\n",via[3],via[9]);
    fflush(stdout); 
    fflush(stdin);
    sleep(1);
    via[4]++;
  }

  return 0;
}

void exit_signal(int num_signal)
{
  int i = 0;
  key_t idmemoria = ftok("/bin/gerly",0424);
  int memoriacompartida = shmget(idmemoria, sizeof(int), IPC_CREAT | 0660 );
  if (memoriacompartida == -1){
    printf("%s\n","Hay un error al crear el segmento de memoria");
    perror("shmctl(IPC_RMID)");
    exit(EXIT_FAILURE);
  }
	if (shmctl(memoriacompartida, IPC_RMID, 0) < 0){
		perror("shmctl(IPC_RMID)"); 
		exit(EXIT_FAILURE);
	}
	printf("%s\n","Terminó el juego!\n");
  exit(EXIT_SUCCESS);  
}