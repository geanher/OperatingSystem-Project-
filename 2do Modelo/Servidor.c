/*
	HERNANDEZ FRIAS GERLY ANDRES
	21061052
	ING DE SISTEMAS
	SISTEMAS OPERATIVOS 

  2do modelo Sistemas operativos
  */
/**
* @file Servidor.c
* @Author Gerly Andres Hernandez
* @version 1.0
* @date 09/07/2019
* @title Servidor(Via)
* @brief Ejecutaremos ./Servidor.out [puerto] por ejemplo ./Servidor.out 1001
* @brief Recibimos a traves de un msj el auto que generó manualmente el usuario y lo procesamos
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<signal.h>


/**
* @brief cuerpo de programa
*/
int main(int argc, char **argv){
  //inicializacion de variables
  int ServerConnect;
  int ClientConnect;
  int Port; 
  int zero=0;
  int one=0;
  int two=0;
  int three=0;
  int t1z, t1o, t1t, t13 =0;

/*verificacion de que se ingreso el puerto*/
  if(argc<2){
    printf("%s [Port]\n",argv[0]);
    return 1;
  }

  socklen_t ClientLe;
  struct sockaddr_in Server, Client;
  char str[200];
  Port = atoi(argv[1]);
  ServerConnect = socket(AF_INET, SOCK_STREAM, 0); 
  Server.sin_family = AF_INET;
  Server.sin_port = htons(Port);
  Server.sin_addr.s_addr = INADDR_ANY;
  if(bind(ServerConnect, (struct sockaddr *)&Server, sizeof(Server)) == -1){ 
    printf("Falló la asociacion con el socket\n");
    close(ServerConnect);
    return -1;
  }
  listen(ServerConnect, 20);
  printf("Esperando por el Puerto: %d\n", ntohs(Server.sin_port));
  ClientLe = sizeof(Client);
  ClientConnect = accept(ServerConnect, (struct sockaddr *)&Client, &ClientLe);
  if(ClientConnect == -1){
    printf("No se pudo aceptar la conexion\n");
    close(ServerConnect);
    return -1;
  }
  system("clear");
  printf("Esperando por llegada de auto");
  for (int i=2; i<100; i++){
    //verificando que hay un msj
	  if(recv(ClientConnect, str, 200, 0) < 0){ 
	    printf("Parece que hubo un error, No se pudo recibir un msj\n");
      
	    close(ServerConnect);
	    return 1;
	  }
	  else{	
      //luego de recibir el msj (carro) encolarlo si hay chance (no hay carros en las demas vias)
      if ((strcmp(str, "0")==0) && (zero<2) && one==0 && two==0 && three==0){
        if(zero==0){
          zero++;
          t1z=i;
        }
        else if (zero==1){
          zero++;
        }
        send(ClientConnect, "Encoló en Zero", 200, 0);
      }
      else if (strcmp(str, "1")==0 && one<2 && zero==0 && two==0 && three==0){
         if(one==0){
           one++;
           t1o=i;
         }
         else if(one==1){
          one++;
         }
        send(ClientConnect, "Encoló en one", 200, 0);
      }
      else if (strcmp(str, "2" )==0 && two<2 && one==0 && zero==0 && three==0){
        if(two==0){
          two++;
          t1t=i;
        }
        else if(two==1){
        two++;
        }
        send(ClientConnect, "Encoló en Two", 200, 0);
      }
      else if (strcmp(str, "3")==0 && three<2 && one==0 && two==0 && zero==0){
        if (three==0){
          three++;
          t13=i;
        }
        else if (three==1)
          {
            three++;
          }
          
        send(ClientConnect, "Encoló en three", 200, 0);
      }
      else {

        send(ClientConnect, "nNoValido", 200, 0);
      }
	  }

    //apartir de aqui desencolo los carros de las diferentes vias luego de 3 iteraciones 

    if(((i-t1z)>3) && (t1z>0) && zero>0){
        zero--;
        t1z=i;
        printf("\ndesencoló via[0]\n");
    }
    if(((i-t1o)>3) && (t1o>0) && one>0){
        one--;
        t1o=i;
        printf("\ndesencoló via[1]\n");
    }
    if(((i-t1t)>3) && (t1t>0) && two>0){
        two--;
        t1t=i;
        printf("\ndesencoló via[2]\n");
    }
    if(((i-t13)>3) && (t13>0) && three>0){
        three--;
        t13=i;
        printf("\ndesencoló via[3]\n");
    }
    /*muestro el monitor. PD: Prof Disculpe si uso la funcion system()
    ya que usted reiteradamente nos ha indicado que no se debe usar tal funcion
    pero como son programas sencillos pues decicidí usarla. disculpe. */
    system("clear");
    printf("\t\n______Monitor de Via________\n\n");
    printf("\t----------------------\n");
    printf("\t|  via |\tcarros\n" );
    printf("\t---------------------\n");
    printf("\t|  0   |\t %d\n",zero);
    printf("\t|  1   |\t %d\n",one);
    printf("\t|  2   |\t %d\n",two);
    printf("\t|  3   |\t %d\n",three);

    fflush(stdout); 
    fflush(stdin);
	}
  //cierro conexion 
  close(ServerConnect);
  return 0;
}