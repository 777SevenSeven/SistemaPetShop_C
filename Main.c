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
#define MENU_DE_COMANDOS "\n'c' para cadastrar um cliente;\n'e' para terminar;\n\ndigite aqui: "
//Type def

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct {
  char nomeCliente[50];
  char telefoneCliente[15];
  char opcao;
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
void meuSort(Animal *meusAnimais, int *tamanho) {
    	Animal meuAnimal;
    	for (int x = 0; x < (*tamanho)-1; x++) {
    		for (int y = x+1; y < (*tamanho); y++) {
    			if (strcmp(meusAnimais[x].nomeAnimal, meusAnimais[y].nomeAnimal) > 0) {
    				meuAnimal = meusAnimais[x];
    				meusAnimais[x] = meusAnimais[y];
    				meusAnimais[y] = meuAnimal;
    			}
    		}
    	}
    }

//write coluna | -3 escrv s sub | -2 escrv p e s sub | -1 escrv p sub | 0 n escrv | 1 escrv p | 2 escrv p e s | 3 escreve s | **nota nao consome espaco de leeway por coluna, so anexa ao lado
void myStrCpy (char *str1, char *str2, int *i, int lee, int writeColuna) { //Msm funcao de str cpy soq ele comeca por int i dado, agregando a ele conforme escreve, e int lee, de leeway para limite de escrita, substituindo com espacos brancos | pft para escrever fileiras
        char cpyFrm[2] = {' ', '|'};
    	if (writeColuna < 0) {cpyFrm[0] = '-'; cpyFrm[1] = '+';}
    	int len = strlen(str2);
    	if (writeColuna > -3 && writeColuna < 3 && writeColuna != 0) {str1[(*i)] = cpyFrm[1]; (*i)++;}
        for (int j = (*i);(*i)-j < lee-1; (*i)++) {
        	str1[(*i)] = ((len > (*i)-j) ? str2[(*i)-j] : cpyFrm[0]); //se escrevo primeira coluna copio de um a menos para um a mai
        }
    	if (writeColuna > 1 || writeColuna < -1) {str1[(*i)] = cpyFrm[1]; (*i)++;}
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

int confTabelaAnimais[] = {5,14,12,24,56} //Primeiro Valor tamanho do Array
char *imprimirAnimais(Animal Animais[],int *tamanho) {
    	int flI = 0, flC = 0;
    	char *minhaFileiraLinha = (char*) malloc(sizeof(char)),
    		*minhaImpressao = (char*) malloc(sizeof(char));
    	void criacaoFileiraLinha() {
    		for (int i = 1; i < confTabelaAnimais[0]; i++) {
    			flC += confTabelaAnimais[i]+1;
    			minhaFileiraLinha = (char*) realloc(minhaFileiraLinha,sizeof(char)*(flC+2));
    			myStrCpy(minhaFileiraLinha,"",&flI,confTabelaAnimais[i], ((i == 1) ? -2 : -3));
    		}
    		minhaFileiraLinha[flI] = '\n';
		minhaFileiraLinha[flI+1] = '\0';
    	}
	void anexarFL() myStrCpy(minhaImpressao,minhaFileiraLinha,&flI,strlen(minhaFileiraLinha),0);
	flI = 0;
    	criacaoFileiraLinha();
    	for(int i = 0; i < (*tamanho); i++) {
		int j = 0;
		Animal oa = Animais[i];
		anexarFL();
		// Aqui imprimo todas os conteudos da tabela por ordem
		myStrCpy(minhaImpressao, oa.nomeAnimal,confTabelaAnimais[1+j++])
	}
	anexarFL();
	return minhaImpressao;
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
	
//Função de validar Datas
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
int cadastrarCliente(Cliente *MeusClientes, int *tamanhoClientes) {
    char nomeCliente[50];
    char telefoneCliente[15];

//Recebe o nome do cliente e armazena dentro do char
 do {
	printf("Nome do cliente: ");
    fgets(nomeCliente, sizeof(nomeCliente)/sizeof(char), stdin); //Recebe e armazena o nome
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0'; //Aqui é pra tirar aquele \n no char

 // Validação do nome, chama a função do nome e informa que o nome está inválido
    if (!nomeValido(nomeCliente)) {
        printf("Nome inválido, insira um nome válido ou E para desistir.\n");
        continue; 
    }
 }
    // Recebe o telefone do cliente e coloca dentro do char
    printf("Telefone do cliente: ");
    fgets(telefoneCliente, sizeof(telefoneCliente)/sizeof(char), stdin); //rececebe e armazena o telefone
    telefoneCliente[strcspn(telefoneCliente, "\n")] = '\0';

    // Validação do telefone, chama uma função e informa que o telefone é inválido
    if (a letra la == 'e') return 0;
	else if (!ValidarTelefone(telefoneCliente)) {
        printf("Telefone inválido, insira um telefone válido ou E para desistir.\n");
        continue;
    }
 } while (opcao == 'S' || opcao == 's');
	return 1;
//	meusCliente[*tamanho].nome = nomeClie;
	
//	meusCliente[*tamanho].nome = telefone;
//	(*tamanho)++;
//	return 1;
} //tava faltando aqui, acho q corto qndo colou, se estiver errado so tirar

int main() {
  char[50] in;
  tamanhos[] = {0,0}; //quantidade de entradas por vetor ordem: MeusClientes, MeusAnimais
  Cliente MeusClientes[100];
  Animal MeusAnimais[100];
	printf("'h' para comandos, 'e' para terminar;\n");
  while (strcmp(fgets(in,50,stdin), "e")!= 0) {
	switch(in[0]) { //controle de menus
		case 'h' : //menu de comandos
			printf("%s",MENUDECOMANDOS);
			break;
		case 'c' : //menu de cadastro
			do {
				cadastrarCliente();
				printf("Deseja cadastrar outro cliente? 's' para sim, 'n' para não: ");
				do {
					fgets(in,50,stdin);
				} while (in[0] != 'n' || in[0] != 's')
				if (in[0] == 'n') break;
			} while(1)
			break;
		case 'a' : //menu impressao de animais alfabeticamente
			meuSort(MeusAnimais,&tamanhos[1]);
			printf("%s\n", imprimirAnimais(MeusAnimais,&tamanhos[1]));
			break;
	}
	free();
  }
  return 0;
}

		/* IGNORAR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    void myStrCpy (char *str1, char *str2, int *i, int lee, int writeColuna) { //Msm funcao de str cpy soq ele comeca por int i dado, agregando a ele conforme escreve, e int lee, de leeway para limite de escrita, substituindo com espacos brancos | pft para escrever fileiras
        char meuString[24], meuSRR[24];
        int testInt = -1;
        void strAAA() {
            strcpy(meuString,str1);
            strcpy(meuSRR,str2);
        }
        char cpyFrm[2] = {' ', '|'};
        strAAA();
    	if (writeColuna < 0) {cpyFrm[0] = '-'; cpyFrm[1] = '+';}
    	int len = strlen(str2);
    	if (writeColuna > -3 && writeColuna < 3 && writeColuna != 0) str1[(*i)] = cpyFrm[1];
    	strAAA();
    	(*i)++;
        for (int j = (*i);(*i)-j < lee-1; (*i)++) {
        	testInt = (*i);
        	str1[(*i)] = ((len > (*i)-j) ? str2[(*i)-j] : cpyFrm[0]); //se escrevo primeira coluna copio de um a menos para um a mai
        
            strAAA();
            
        }
    	if (writeColuna > 1 || writeColuna < -1) {str1[(*i)] = cpyFrm[1]; (*i)++;}
    	strAAA();
        str1[(*i)] = '\0';
        strAAA();
        
    }
    int confTabelaAnimais[] = {4,12,5,3}; //20
    char *imprimirAnimais(int *tamanho) {
    	int flI = 0, flC = 0;
    	char *minhaFileiraLinha = (char*) malloc(sizeof(char)),
    		*minhaFileira,
    		*minhaImpressao = (char*) malloc(sizeof(char));
    	void criacaoFileiraLinha() {
    		for (int i = 1; i < confTabelaAnimais[0]; i++) {
    			flC += confTabelaAnimais[i]+1;
    			minhaFileiraLinha = (char*) realloc(minhaFileiraLinha,sizeof(char)*(flC+2));
    			myStrCpy(minhaFileiraLinha,"",&flI,confTabelaAnimais[i],-3);
    		}
    		char copiaDaMinhaFileiraCompleta[flC+2];
    		strcpy(copiaDaMinhaFileiraCompleta,minhaFileiraLinha);
    		flI = 0;
    		myStrCpy(minhaFileiraLinha,copiaDaMinhaFileiraCompleta,&flI,flC,-1);
    		minhaFileiraLinha[flI] = '\n';
    	}
    	criacaoFileiraLinha();
    	minhaFileiraLinha[flC-1] = '\0'; 
        return minhaFileiraLinha;
    }
    int a = 5;
    char *mf = (char*) malloc(sizeof(char)*100);
    mf = imprimirAnimais(&a);
    puts(mf);
    printf("\n%d",(int)strlen(mf));
    return 0;
*/
