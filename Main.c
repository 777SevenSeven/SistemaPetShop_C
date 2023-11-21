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

#define DIA 1
#define MES 2
#define ANO 1997
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
  Animal *pet;
  int tipoServico;
  char pago; //'S' sim 'N' nao
} Servico;

//Funcs

//retornar a ordem alfabetica das entradas atravez dum array array[posicao alfabetica] = posicaoRealNoArrayDeEntrada
int *meuSort(Animal *meusAnimais) {
        int *out = (int*) malloc(sizeof(int)*7);
    	char **meusNomes[7];// = {};
    	int cursor = 0, res = 0;
    	void sw(int a, int b) {
    		char **ptr = meusNomes[a];
    		meusNomes[a] = meusNomes[b];
    		meusNomes[b] = ptr;
    	}
    	for (int i = 0; i < 7; i++) {
    	    meusNomes[i] = &meusAnimais[i].nomeAnimal;
    	}
    	while (1) {
    		if (cursor == 6) if (res == 0) break; else {cursor = 0; res = 0;}
    		
    		if (strcmp(*meusNomes[cursor],*meusNomes[cursor+1]) > 0) {sw(cursor,cursor+1); cursor++; res = 1;}
    		else if (cursor > 0) {cursor = 0; res = 0;} else {res = 0; cursor++;}
    	}
	return out;
	/*char meuArray[7][6] = {"Abcde","Bcde","Cdari","Abdee","Macad","Zeta","zeta"};
    int *meuSort() {
        int *out = (int*) malloc(sizeof(int)*7);
        char meuArray[7][6] = {"Abcde","Bcde","Cdari","Abdee","Macad","Zeta","zeta"};
    	char **meusNomes[7]; 
    	for (int i = 0; i < 7; i ++) meusNomes[i] = (char **) &meuArray[i];
    	int cursor = 0, res = 0;
    	void sw(int a, int b) {
    		char **ptr = meusNomes[a];
    		meusNomes[a] = meusNomes[b];
    		meusNomes[b] = ptr;
    	}
    	/*for (int i = 0; i < 7; i++) {
    	    meusNomes[i] = &meusAnimais[i];
    	}*/
    	while (1) {
    		if (cursor == 6) if (res == 0) break; else {cursor = 0; res = 0;}
    		
    		if (strcmp(*meusNomes[cursor],*meusNomes[cursor+1]) > 0) {sw(cursor,cursor+1); cursor++; res = 1;}
    		else if (cursor > 0) {cursor = 0; res = 0;} else {res = 0; cursor++;}
    	}
    }
    int *meuPtr = (int*) malloc(sizeof(int)*7);
    meuPtr = meuSort();
    for (int i = 0; i < 7; i++){
        puts(meuArray[meuPtr[i]]);
    }
    return 0;*/
}

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
    // Verifica se o telefone tem tamanho entre 11 e 12 e se o primeiro caractere é '0'
    if (!(strlen(telefoneCliente) >= 11 && strlen(telefoneCliente) <= 12 && telefoneCliente[0] == '0')) {
        return -1; // Inválido
    }
	
    // Verifica se todos os caracteres restantes são dígitos numéricos válidos
    for (int j = 1; j < strlen(telefoneCliente); j++) {
        if (telefoneCliente[j] < '0' || telefoneCliente[j] > '9') {
            return -1; // Inválido
        }
    }
    return 1; // Válido
}

int ValidarData(int dia, int mes, int ano) {
    // Verifica se o dia está entre 1 e 21 (utilizei 21 pois temos a regra de não permitir datas futuras)
    if (!(dia >= 1 && dia <= 21)) {
        return -1; // Inválido
    }

    // Verifica se o mês está entre 1 e 11  (utilizei 11 pois temos a regra de não permitir datas futuras)
    if (!(mes >= 1 && mes <= 11)) {
        return -1; // Inválido
    }

    // Verifica se o ano é maior ou igual a 1900 (mínimo) ou 2023 (atual)
    if (!(ano <= 2023 && >= 1900)) { 
        return -1; // Inválido
    }

    // Se todas as verificações passarem, a data é válida
    return 1;
}

//Cadastro de clientes
int cadastrarCliente(Cliente *MeusClientes, int *tamanhoClientes) { //Fiquei confuso aqui, eu basicamente redeclarei a variavél, será que é necessário?
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
    }
} //tava faltando aqui, acho q corto qndo colou, se estiver errado so tirar

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

typedef enum {Animal, Cliente, Data}StructType;

typedef struct{
    int *value;
    int flag;
} RowSize;

typedef struct{
    char **value;
    int flag;
} RowName;

typedef struct{
    char **value;
    int flag;
} Conditions;

typedef struct{
    void *value;
    char *pseudo; //pseudo name used in where cons
    StructType type; //type of struct
} Origin;

typedef struct{
    Origin *origin;
    int flag; //size
} From;

typedef struct{
    RowSize rowSize;
    RowName rowName;
    Conditions where;
    From *from; //mallocc'ed to size of FROM entries
} tablePrinter;

typedef struct{
    
} cursor;

void PrintTable(tablePrinter tp) {
    char Table[1000];
    int wCursor = 0, rlCursor = 0;
    int *wc = &wCursor, *rlc = &rlCursor;
    char *rowLine = (char*) malloc(1);
    char *createRowLine(int size) {
        char *out = (char*) malloc(sizeof(char)*(size+1))
        for (int i = 0; i < size-1; i++) {
            out[i] = '-';
        }
        out[size-1] = '\0';
        return out;
    }
    void startUpRowLine(){
        char *myLn = createRowLine(tp.rowSize.value[0]);
        rowLine = (char *) realloc(rowLine,((int)strlen(myLn)+1+rlc)*sizeof(char));
        myStrCpy(rowLine, myLn, rlc, tp.rowSize.value[0], 3);
        for (int i = 1; i < tp.rowSize.flag; i++) {
            myLn = createRowLine(tp.rowSize.value[i]);
            rowLine = (char *) realloc(rowLine,((int)strlen(myLn)+1+rlc)*sizeof(char));
            myStrCpy(rowLine, myLn, rlc, tp.rowSize.value[i], 6);
        }
    }
    void annexRowLine() myStrCpy(Table, rowLine, wc, rlc, 0);
    for (int i = 0; i < tp.from.flag; i++) {
        switch(tp.from.origin[i].type) {
            case 0 :
                
        }
    }
    //we need to iterate through every single origin mixed into every single origin
    myStrCpy(Table, tp.rowName.value[0],wc,tp.rowSize.value[0], 1);
    for (int i = 1; i < tp.rowSize.flag; i++) {
        myStrCpy(Table, tp.rowName.value[i],wc,tp.rowSize.value[i], 2);
    }
    Table[wCursor] = '\n';
    wCursor++;
}

int main ()
{
    int *a = &max[0];
    int *b = &max[1];
    printf ("%p %p %p %p %p", a, b, &a, &b, &max);
    return 0;
}
*/ IGNORAR
