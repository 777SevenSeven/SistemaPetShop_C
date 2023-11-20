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
char[] baseadoEmNomePet(char Nome[50], Animal Pets*, Cliente Clientes*) {
  char *composto = (char*) malloc(sizeof(char));
  void myStrCpy(char[] str1, char[] str2, int *i, int lee) {
    int len = strlen(str2);
    for(int j = 0; j < lee; j++, *i++) {
      str[i+j] = ((len > j) ? str2[j] : ' ');
    }
  }
  void aggregate(Cliente MeuCliente, Animal MeuAnimal) { //CliNome | CliNum | nomeAnimal[50] | int especie | dataNascimento | char agressivo; //'S' sim 'N' nao
    int i = 0;
    char meuChar[];
    myStrCpy(meuChar,MeuCliente.nomeCliente,&i,14);
    myStrCpy(meuChar,MeuCliente.telefoneCliente,&i,13);
    myStrCpy(meuChar,MeuAnimal.nomeAnimal,&i,10);
    myStrCpy(meuChar,MeuAnimal.especie,&i,10);
  }
  int sz[] = {sizeof(*Clientes)/sizeof(Animal), sizeof(*Pets)/sizeof(Animal)};
  for (int i = 0; i < sz[1]; i++) {
    if (strcmp(Pets[i].nomeAnimal,Nome) == 0) {
      for (int j = 0; j < sz[0]; j++) {
        if (strcmp(Clientes[j].nomeCliente, Pets[i].cliente) {aggregate(Clientes[j],Pets[i]); break;}
      }
    }
  }
}

int qntdAnimaisAgressivos(Animal *MeusAnimais) {
  int contagem = 0;
  int sz = sizeof(*MeusAnimais)/sizeof(Animal);
  for (int i = 0; i < sz; i++) {
    if (MeusAnimais[i].agressivo == 'S') contagem++;
  }
  return contagem;
}

char posIntToChar[](int in) {
  int i = 0;
  float myIn = (float) in/ pow(10,1+(int) log10(in));
  char *myChar = (char*) malloc(sizeof(char));
  while(in >= 1) {
    myIn *= 10;
    myChar[i] = (int) floor(myIn);
    myIn -= floor(myIn);
    myChar = (char*) realloc(myChar,sizeof(mychar)+sizeof(char));
    i++;
  }
  myChar[i] = '\0';
  return myChar;
}

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

//Função de validar nomes
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

//Função de validar Telefones
int ValidarTelefone(char telefoneCliente[15]) {
    int valido = 0; //-1 invalido 1 valido
    if(!(strlen(telefoneCliente) <= 12 && strlen(telefoneCliente) >= 11 && telefoneCliente[0] == '0')) return 0;
    for(int j = 0; j < strlen(telefoneCliente); j++) {
    //Caso Verdadeiro
    if(strlen(telefoneCliente) <= 12 && telefoneCliente[j] >= 48 && telefoneCliente[j] <= 57) {
        valido = 1;
    }
        else {
        valido = 0;
        break;
        }
    }
    return valido;
}

Animal* aumentarVetorAnimal(Animal* Animais, int tamanho) { //Aumenta o vetor de Animais em tamanho e retorna o mesmo
  return (Animal*) realloc(Animais, sizeof(Animais) + sizeof(Animal)*tamanho);
}

Cliente* aumentarVetorClientes(Cliente* Clientes, int tamanho) { //Aumenta o vetor de Animais em tamanho e retorna o mesmo
  return (Cliente*) realloc(Clientes, sizeof(Clientes) + sizeof(Cliente)*tamanho);
}

int main() {
  char[50] in;
  Cliente *MeusClientes = (Cliente*) malloc(sizeof(Cliente));
  Animal *MeusAnimais = (Animal*) malloc(sizeof(Animal));
  while (fgets(in,50,stdin)!=NULL) {
     
  }
  return 0;
}
