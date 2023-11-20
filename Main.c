#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Type def
typedef struct{
  int dia;
  int mes;
  int ano;
} Data;


typedef struct{
  char nomeCliente[50];
  char telefoneCliente[15];
} Cliente;


typedef struct{
  Cliente cliente;
  char nomeAnimal[50];
  int especie;
  Data dataNascimento;
  char agressivo; //'S' sim 'N' nao
} Animal;

typedef struct{
  int identificador;//AUTO_INCREMENT
  Data dataServico;
  Animal pet;
  int tipoServico
  char pago; //'S' sim 'N' nao
} Servico;

//Funcs

int main() {
  //asdfsadf
  return 0;
}
