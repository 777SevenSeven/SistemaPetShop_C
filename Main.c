/*
Trabalho Final da Disciplina de Algoritmos 01: Gerenciador de PetShop.
Turma: EC41A.2023_01.C11 / Data:18/04/2023.
Nomes:André Antônio da Silva Queiroz    | RA:a2575310
......Mathias Vinicius Carcano Ferretti | RA:a2575396
......Gabriel Henrique Prado Affonso | RA:a2618044
*/
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
int charToPosInt(char *in){
  int myInt = 0;
  for (int i = 0; i < strlen(*in); i++) {
    if (/* char is in range*/) {
      myInt *= 10;
      myInt += *in[i]; // nn sei notacao pra pegar o valor
    }
  }
  return myInt;
}

int main() {
  char[50] in;
  while (fgets(in,50,stdin)!=NULL) {
     
  }
  return 0;
}
