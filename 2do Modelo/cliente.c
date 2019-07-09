/*
  HERNANDEZ FRIAS GERLY ANDRES
  21061052
  ING DE SISTEMAS
  SISTEMAS OPERATIVOS 
  2do modelo Sistemas operativos
*/

/**
* @file cliente.c
* @Author Gerly Andres Hernandez
* @version 1.0
* @date 09/07/2019
* @title Cliente (Generador de automoviles )
* @brief Ejecutaremos ./cliente.out [host] [puerto] por ejemplo ./cliente.out localhost 1001
* @brief en este caso los autos se introduciran de forma manual 
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


/**
* @brief Main del .c
*/

int main(int argc, char **argv){
  if(argc<2){
    printf("[host] [Port]\n");
    return -1;
  }
  int Port, Connect;
  char str[200];
  int flags;
  struct sockaddr_in Client;
  struct hostent *server; 
  server = gethostbyname(argv[1]);
  Port=(atoi(argv[2]));
  if(server == NULL){ 
    printf("No se Obtuvo el Host Correcto\n");
    return -1;
  }
  Connect = socket(AF_INET, SOCK_STREAM, 0); 
  Client.sin_family = AF_INET;
  Client.sin_port = htons(Port);
  bcopy((char *)server->h_addr, (char *)&Client.sin_addr.s_addr, sizeof(server->h_length));
  if(connect(Connect,(struct sockaddr *)&Client, sizeof(Client)) < 0){ 
    printf("No se pudo conectar :(\n");
    close(Connect);
    return -1;
  }
  system ("clear");
  do{
        fflush(stdout); 
    fflush(stdin);
    /*los carros entraran de forma manual dirigida por el usuario*/
    printf("Escriba porque via entra el carro(0/1/2/3): ");
    scanf ("%s",str);
    send(Connect, str, sizeof(str), 0);
    recv(Connect, str, sizeof(str), 0);
    printf("%s\n", str);
    printf("desea agregar otro carro?(0/1) ");
    scanf("%d", &flags);
  }while ((flags != 0) && (flags = 1));
  close(Connect);
  return 0;
}

