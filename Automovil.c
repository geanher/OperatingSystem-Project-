/*
  HERNANDEZ FRIAS GERLY ANDRES
  21061052
  ING DE SISTEMAS
  SISTEMAS OPERATIVOS 

  Proyecto final Sistemas Operativos
  Programa que Genera automoviles de forma aleatoria y los agrega a las diferentes vias 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <signal.h>

//------------------------------------------------------------------
int idvia,tv11,tv12,tv21,tv22,tv31,tv32,tv01,tv02;

void encolar(int *via){
    if(idvia==0 && via[2]==0){
        if(via[0]==0){
            via[idvia]++;
            tv01=via[4];
        }
        else if (via[0]==1){
            via[idvia]++;
            tv02=via[4];
        }
        else{
            via[6]++;
        }
        printf("encolo en 0\n");
        //cout<<"via[0]:"<<via[0]<<" cola0: "<<via[6]<<" tv1: "<<tv01<<" tiempo en tv2 "<<tv02<<endl;
    }

    else if(idvia==1 && via[3]==0){
        if(via[1]==0){
            via[idvia]++;
            tv11=via[4];
        }
        else if (via[1]==1){
            via[idvia]++;
            tv12=via[4];
        }
        else{
            via[7]++;
        }
        printf("encolo en 1\n");
        //cout<<"via[1]: "<<via[1]<<" cola1: "<<via[7]<<" tv1: "<<tv11<<" tiempo en tv2 "<<tv12<<endl;
    }

    else if(idvia==2 && via[0]==0){
        if(via[2]==0){
            via[idvia]++;
            tv21=via[4];
        }
        else if (via[2]==1){
            via[idvia]++;
            tv22=via[4];
        }
        else{
            via[8]++;
        }
        printf("encolo en 2\n");
        //cout<<"via[2]:"<<via[2]<<" cola2: "<<via[8]<<" tv1: "<<tv21<<" tiempo en tv2 "<<tv22<<endl;        
    }

    else if(idvia==3 && via[1]==0){
        if(via[3]==0){
            via[idvia]++;
            tv31=via[4];
        }
        else if (via[3]==1){
            via[idvia]++;
            tv32=via[4];
        }
        else{
            via[9]++;
        }
        printf("encolo en 3\n");
        //cout<<"via[3]:"<<via[3]<<" cola3: "<<via[9]<<" tv1: "<<tv31<<" tiempo en tv2 "<<tv32<<endl;
    }
  

}
void desencolar(int *via){

    printf("\nesto es T %d\n", via[5]);

    if(((via[5]-tv01)>3) && (tv01!=0)){
        if(via[6]>0)
            via[6]--;
        if(via[0]>0)
            via[0]--;
        tv01=tv02;
        tv02=0;
    }
    if(((via[5]-tv11)>3) && (tv11!=0)){
        if(via[7]>0)
            via[7]--;
        if(via[1]>0)
            via[1]--;
        tv11=tv12;
        tv12=0;
    }
    if(((via[5]-tv21)>3) && (tv21!=0)){
        if(via[8]>0)
            via[8]--;
        if(via[2]>0)
            via[2]--;
        tv21=tv22;
        tv22=0;
    }
    if(((via[5]-tv31)>3) && (tv31!=0)){
        if (via[9]>0)
            via[9]--;
        if(via[3] >0)
            via[3]--;
        tv31=tv32;
        tv32=0;
    }
}

//-----------------------------------------------------------------------------

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


    for (int i=0; i<10; i++){
        via[i]=0;
    }

    for (int i=0; i<100 ; i++){
        via[5]=(via[5]+(rand()%15)); //generar tiempo aleatorio entre 1y 5
        idvia=(rand()%4); // generar via aleatorio entre 0y3
        encolar(via);
        while(via[4] != via[5]){
            fflush(stdout); 
            fflush(stdin);
            printf("\nt2 = %d\n",via[4]);
            desencolar(via);
            sleep(1);
        }
    }


//----------------------------------------------------
  return 0;
}
