/*
  HERNANDEZ FRIAS GERLY ANDRES
  21061052
  ING DE SISTEMAS
  SISTEMAS OPERATIVOS 

  Proyecto final Sistemas Operativos
  Programa que Genera automoviles de forma aleatoria y los agrega a las diferentes vias 
*/


/**
* @file Automovil.c
* @Author Gerly Andres Hernandez
* @version 1.0
* @date 09/07/2019
* @title Generador de Automoviles
* @brief Implementacion y generacion de carros aleatorios 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <signal.h>

int idvia,tv11,tv12,tv21,tv22,tv31,tv32,tv01,tv02;
/**
* @brief encolar autos en las diferentes vias
* @param la memoria compartida 
*/
void encolar(int *via){
    fflush(stdout); 
            fflush(stdin);
    if((idvia==0) && (via[2]==0) && via[1]==0 && via[3]==0){
        if (via[0]==0){
            via[0]++;
            tv01=via[4];
        }
        else if (via[0]==1){
            via[0]++;
        }
        printf("encolo en 0\n");
    }
    else if((idvia==1) && (via[0]==0) && via[2]==0 && via[3]==0){
        if (via[1]==0){
            via[1]++;
            tv11=via[4];
        }
        else if (via[1]==1){
            via[2]++;
        }
        printf("encolo en 1\n");
    }

    else if((idvia==2) && (via[0]==0) && via[1]==0 && via[3]==0){
        if (via[2]==0){
            via[2]++;
            tv21=via[4];
        }
        else if (via[2]==1){
            via[2]++;
        }
        printf("encolo en 2\n");
    }

    else if((idvia==3) && (via[0]==0) && via[1]==0 && via[2]==0){
        if (via[3]==0){
            via[3]++;
            tv31=via[4];    
        }
        else if (via[3]==1){
            via[3]++;
        }
        printf("encolo en 3\n");
    }
  

}
/**
* @brief Desencolar los autos cada 3 seg luego de haber entrado en la via
* @param la memoria compartida 
*/
void desencolar(int *via){
    fflush(stdout); 
    fflush(stdin);
    if(((via[5]-tv01)>4) && (tv01>0) && via[0]>0){
        via[0]--;
        tv01=via[4];
        printf("\ndesencoló via[0]\n");
    }
    if(((via[5]-tv11)>4) && (tv11>0) && via[1]>0){
        via[1]--;
        tv11=via[4];
        printf("\ndesencoló via[1]\n");
    }
    if(((via[5]-tv21)>4) && (tv21>0) && via[2]>0){
        via[2]--;
        tv21=via[4];
        printf("\ndesencoló via[2]\n");
    }
    if(((via[5]-tv31)>4) && (tv31>0) && via[3]>0){
        via[3]--;
        tv31=via[4];
        printf("\ndesencoló via[3]\n");
    }
}


int main (){
  srand(getpid());
  key_t idmemoria = ftok("/bin/gerly",0424);
  int memoriacompartida = shmget(idmemoria, sizeof(int), IPC_CREAT | 0660 );
  if (memoriacompartida == -1){
    printf("%s\n","Hay un error al crear el segmento de memoria");
    return -1;
  }
  int * via = shmat (memoriacompartida, NULL, 0);
  if (via == NULL){
    printf("%s\n","Hay un error al vincular el segmento de memoria");
    return -1;
  }
  fflush(stdout); 
            fflush(stdin);


    for (int i=0; i<10; i++){
        via[i]=0;
    }
via[4]=1;
    for (int i=0; i<100 ; i++){
        int ramd;
        ramd=1+rand()%(7-1);
        via[5]=via[5]+ramd; //generar tiempo aleatorio entre 1y 5
        printf("Proximo carro en %d seg\t ", ramd);
        idvia=(rand()%4); // generar via aleatorio entre 0y3
        printf("por la via %d\n ", idvia);
        
        encolar(via);
        fflush(stdout); 
            fflush(stdin);
        while(via[4] < via[5]){
            sleep(1);
            fflush(stdout); 
            fflush(stdin);
            via[4]++;
            desencolar(via);
            
        }
    }


//----------------------------------------------------
  return 0;
}
