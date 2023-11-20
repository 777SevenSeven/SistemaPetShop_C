/*
Trabalho Final da Disciplina de Algoritmos 01: Gerenciador de PetShop.
Turma: EC41A.2023_01.C11 / Data:18/04/2023.
Nomes:André Antônio da Silva Queiroz    | RA:a2575310
......Mathias Vinicius Carcano Ferretti | RA:a2575396
......Gabriel Henrique Prado Affonso    | RA:a2618044
*/
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Type def
typedef struct {
  int dia;
  int mes;
  int ano;
} Data;


typedef struct {
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

typedef struct {
  int identificador;//AUTO_INCREMENT
  Data dataServico;
  Animal pet;
  int tipoServico;
  char pago; //'S' sim 'N' nao
} Servico;

//Funcs
int charToPosInt(char *in) {
  int myInt = 0;
  for (int i = 0; i < strlen(*in); i++) {
    if (/* char is in range*/) {
      myInt *= 10;
      myInt += *in[i]; // nn sei notacao pra pegar o valor
    }
  }
  return myInt;
}

int nomeValido(char *in) { //Returns 1 em valido 0 em invalido
  int valid = 0;
  int sz = sizeof(*in)/sizeof(char);
  char Casted[sz];
  strcpy(Casted,*in);
  for (int i = 0; i < sz; i++) {
    if (/*not within range*/) {valid = -1; break;}
    else valid++;
  }
  if (valid >= 3) return 1; else return 0;
}

Animal* aumentarVetorAnimal(Animal* Animais, int tamanho) { //Aumenta o vetor de Animais em tamanho e retorna o mesmo
  return (Animal*) realloc(Animais, sizeof(Animais) + sizeof(Animal)*tamanho);
}

Animal* aumentarVetorAnimal(Animal* Animais, int tamanho) { //Aumenta o vetor de Animais em tamanho e retorna o mesmo
  return (Animal*) realloc(Animais, sizeof(Animais) + sizeof(Animal)*tamanho);
}

int main() {
  char[50] in;
  Animal MeusAnimais = (Animal*) malloc(sizeof(Animal)/* Vezes a quantidade*/);
  while (fgets(in,50,stdin)!=NULL) {
     
  }
  return 0;
}
