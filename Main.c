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
  Cliente *cliente;
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

//write coluna -1 escreve primeira | 0 nao escreve | 1 escreve primeira e segunda | 2 escreve segunda | nota ele consome um espaco dado por leeWay por coluna impressa
void myStrCpy (char *str1, char *str2, int *i, int lee, int writeColuna) { //Msm funcao de str cpy soq ele comeca por int i dado, agregando a ele conforme escreve, e int lee, de leeway para limite de escrita, substituindo com espacos brancos | pft para escrever fileiras
    int len = strlen(str2);
		if (writeColuna%2 == 1) str1[(*i)] = '|';
		(*i)++;
    for (int j = (*i);(*i)-j < lee-1; (*i)++) {
    	str1[(*i)] = ((len > (*i)-j) ? str2[(*i)-j] : ' ');
    }
		if (writeColuna > 0) str1[(*i)-1] = '|'; 
    str1[(*i)] = '\0';
}

char *baseadoEmNomePet (char *Nome, Animal *Pets, Cliente *Clientes){
	int letras = 400;
	char *composto = (char *) malloc (sizeof (char) * letras);
  void aggregate (Cliente MeuCliente, Animal MeuAnimal) {//CliNome | CliNum | nomeAnimal[50] | int especie | dataNascimento | char agressivo; //'S' sim 'N' nao
    int i = 0;
    char meuChar[100];
    myStrCpy (meuChar, MeuCliente.nomeCliente, &i, 14);
    //myStrCpy (meuChar, MeuCliente.telefoneCliente, &i, 13);
    myStrCpy (meuChar, MeuAnimal.nomeAnimal, &i, 10);
  	myStrCpy (meuChar, MeuAnimal.cliente->nomeCliente, &i, 14);
    i = 0;
    myStrCpy (composto, meuChar, &i,350);
    composto[letras] = '\0';
    //myStrCpy (meuChar, MeuAnimal.especie, &i, 10);
  }
  int sz[] = {100, 100}; // Corresponde ao tamanho de entradas em Clientes e Animais Correspondentemente
  for (int i = 0; i < sz[1]; i++){
  	if (strcmp (Pets[i].nomeAnimal, Nome) == 0) {
    	aggregate (*Pets[i].cliente, Pets[i]); return composto;
 		}
	}
}
int qntdAnimaisAgressivos(Animal *MeusAnimais) {
  int contagem = 0;
  int sz = 100; // se tivermos quantia de entradas assignar aqui para otimizacao so funciona se for tudo em ordem sem pular
  for (int i = 0; i < sz; i++) {
    if (MeusAnimais[i].agressivo == 'S') contagem++;
  }
  return contagem;
}

char *posIntToChar(int in) {
  int i = 1+(int) log10(in);
  int mx = i;
  char *myChar = (char *) malloc(sizeof(char)*(i+2));
  while(i >= 1) {
      int toInt = in/pow(10,i-1);
      myChar[mx-i] = 48+toInt;
      in -= toInt*pow(10,i-1);
      i--;
  }
  myChar[mx] = '\0';
  return myChar;
}

int charToPosInt(char *in) {
  int myInt = 0;
  for (int i = 0; i < strlen(in); i++) {
      myInt *= 10;
      myInt += in[i]-48;
  }
  return myInt;
}

//Função de validar nomes
  int nomeValido (char *in) {//Returns 1 em valido 0 em invalido
    int valid = 0;
    for (int i = 0; i < strlen(in); i++) {
	    if (in[i] < 65 || (in[i] > 90 && in[i] < 97) || in[i] > 122) {
    	    valid = -1;
    	    break;
    	} else valid++;
    }
    if (valid >= 3) return 1;
    else return 0;
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

//Cadastro de clientes
int cadastrarCliente(Cliente *MeusClientes, int *tamanhoClientes) {
    char nomeCliente[50];
    char telefoneCliente[15];

 printf("Nome do cliente: ");
    fgets(nomeCliente, sizeof(nomeCliente), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0'; ; //Aqui é pra tirar aquele \n no char

 // Validação do nome
    if (!nomeValido(nomeCliente)) {
        printf("Nome inválido, insira um nome válido.\n");
        return 0;
    }

    // Telefone do cliente
    printf("Telefone do cliente: ");
    fgets(telefoneCliente, sizeof(telefoneCliente), stdin);
    telefoneCliente[strcspn(telefoneCliente, "\n")] = '\0';

    // Validação do telefone
    if (!ValidarTelefone(telefoneCliente)) {
        printf("Telefone inválido, insira um telefone válido.\n");
        return 0;

int main() {
  char[50] in;
  tamanhos[] = {0,0}; //quantidade de entradas por vetor ordem: MeusClientes, MeusAnimais
  Cliente MeusClientes[100];
  Animal MeusAnimais[100];
  while (fgets(in,50,stdin)!=NULL) {
     
  }
  return 0;
}

/* IGNORAR
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    char nomeCliente[50];
    char telefoneCliente[15];
} Cliente;

typedef struct
{
  Cliente *cliente;
  char nomeAnimal[50];
  int especie;
  //Data dataNascimento;
  char agressivo;		//'S' sim 'N' nao
} Animal;

char *baseadoEmNomePet (char Nome[50], Animal *Pets, Cliente *Clientes){
    int letras;
    char *composto = (char *) malloc (sizeof (char) * letras);
    void myStrCpy (char *str1, char *str2, int *i, int lee) {
        int len = strlen(str2);
        for (int j = 0; j < lee; j++, (*i)++) {
    	    str1[*i+j] = ((len > j) ? str2[j] : ' ');
        }
    }
    void aggregate (Cliente MeuCliente, Animal MeuAnimal) {//CliNome | CliNum | nomeAnimal[50] | int especie | dataNascimento | char agressivo; //'S' sim 'N' nao
        int i = 0;
        char meuChar[100];
        myStrCpy (meuChar, MeuCliente.nomeCliente, &i, 14);
        //myStrCpy (meuChar, MeuCliente.telefoneCliente, &i, 13);
        myStrCpy (meuChar, MeuAnimal.nomeAnimal, &i, 10);
        myStrCpy (meuChar, MeuAnimal.cliente->nomeCliente, &i, 14);
        composto[letras] = '\0';
        //myStrCpy (meuChar, MeuAnimal.especie, &i, 10);
    }
    int sz[] = {100, 100}; // Corresponde ao tamanho de entradas em Clientes e Animais Correspondentemente
    for (int i = 0; i < sz[1]; i++){
        if (strcmp (Pets[i].nomeAnimal, Nome) == 0) {
            aggregate (*Pets[i].cliente, Pets[i]); return composto;
        }
    }
}

int main ()
{
    Animal Animais[100];
    Cliente Clientes[100];
    Animais[0].nomeAnimal = "TRex";
    Animais[0].cliente = &Clientes[1];
    Clientes[1].nomeCliente = "Joao";
    Animais[2].nomeAnimal = "Fofo";
    Animais[2].cliente = &Clientes[3];
    Clientes[3].nomeCliente = "Martin";
    
    printf ("%s", baseadoEmNomePet("TRex",Animais,Clientes));
    return 0;
}
*/ IGNORAR
