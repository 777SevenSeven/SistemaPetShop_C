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
#define MENU_DE_COMANDOS "\n'l' para limpar o console;\n'c' para cadastrar um cliente;\n'e' para terminar;\n\ndigite aqui: "

const char ESPECIES[][] = {"York","Yorkie","Yorkshire","York fofo", "Yorkiezinho", "Yorkiiiiee >///<"};
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
char* stringDinamica(int tamanho) return (char*) malloc(tamanho*sizeof(char));

char* aumentarTamString(char *string, int tamanho) return (char*) realloc(string,tamanho*sizeof(char));


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
	char *composto = definirStringDinamica(letras);
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
  char *myChar = definirStringDinamica(i+2);
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

char *dataParaChar(Data data) {
	int i = 0;
	char out[12];
	void anexarValor(char *valor, int letras) myStrCpy(out,valor,&i,letras,0);
	void anexarBarra() anexarValor("/",1);
	anexarValor(posIntToChar(data.dia),2);
	anexarBarra();
	anexarValor(posIntToChar(data.mes),2);
	anexarBarra();
	anexarValor(posIntToChar(data.ano),4);
	return out;
}

char confTANomeColunas[][] = {"Nome", "Especie", "Agressivo", "Data de Nascimento", "Nome do Cliente", "Telefone"};
int confTabelaAnimais[] = {7,14,12,20,13,14}; //Primeiro Valor tamanho do Array

char *anexarFileira(char **colunas, int confTabela[], int PrimeiraFileira) {
int     cursor = 0, // Posicao em que se esta escrevendo
		flT = 0; // Fileira linha Tamanho
    	char *minhaFileiraLinha = stringDinamica(1), // A linha que separa conteudo das fileiras
    		*minhaImpressao = stringDinamica(1); // A string da tabela inteira que vou montar
    	void criacaoFileiraLinha() { // Inicializa a Fileira Linha
    		for (int i = 1; i < confTabela[0]; i++) flT += confTabela[i]+1;
 		minhaFileiraLinha = aumentarTamString(minhaFileiraLinha,flT+2);
		for (int i = 1; i < confTabela[0]; i++)
    			myStrCpy(minhaFileiraLinha, "", &cursor, confTabela[i], ((i == 1) ? -2 : -3)); // Se for primeira linha quero linha de coluna antes tambem
    		minhaFileiraLinha[cursor] = '\n';
		minhaFileiraLinha[cursor+1] = '\0';
    	}
	void anexarColuna(char *valor, int coluna) myStrCpy(minhaImpressao, valor, &cursor, confTabela[coluna], ((i == 0) ? 2 :3); // Se for primeira linha quero linha de coluna antes tambem
	void anexarFL()                            myStrCpy(minhaImpressao,minhaFileiraLinha,&cursor,strlen(minhaFileiraLinha),0); // Anexar fileira linha
	void anexarNL()                            myStrCpy(minhaImpressao,"\n",&flI,1,0); // Anexar "New Line" (enter)
	if (primeiraFileira == 1) anexarFL();
	for (int i = 0; i < confTabela[0]; i++) {
		anexarColuna(colunas[i], i);
	}
	anexarNL();
	anexarFL();
	return minhaImpressao;
}


char *imprimirAnimais(Animal Animais[],int *tamanho) {
	int cursor = 0;
	char *minhaImpressao = stringDinamica(1);
	anexarFileira(confTAColunas, confTabelaAnimais, 1);
    	for(int i = 0; i < (*tamanho); i++) {
		int j = 0;
		Animal oA = Animais[i];
		char colunas[][] = {    oA.nomeAnimal,
					ESPECIE[oA.especie],
					oA.agressivo,
					dataParaChar(oA.dataNascimento),
					oA.cliente->nomeCliente,
					oA.cliente->telefoneCliente};
		anexarFileira(colunas, confTabelaAnimais, 0);
	}
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

// Função para cadastrar os clientes
int cadastrarCliente(Cliente *MeusClientes, int *tamanhoClientes) {
    char nomeCliente[50];
    char telefoneCliente[15];

// Recebe o nome do cliente e armazena dentro do char
 do {
    printf("Nome do cliente: ");
    fgets(nomeCliente, sizeof(nomeCliente) / sizeof(char), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

    // Irá realizar a validação do nome
    if (!nomeValido(nomeCliente)) {
        printf("Nome inválido, insira um nome válido ou E para desistir.\n");
        fgets(opcao, sizeof(opcao) / sizeof(char), stdin);
        opcao[strcspn(opcao, "\n")] = '\0';

	// Caso o usuário desista de inserir, ele pode pressionar E ou e para desistir
        if (opcao[0] == 'E' || opcao[0] == 'e') return 0;

        // Continue para a próxima iteração do loop para que o usuário insira o nome novamente
        continue;
    }

    // Recebe o telefone do cliente e armazena dentro do char
    printf("Telefone do cliente: ");
    fgets(telefoneCliente, sizeof(telefoneCliente) / sizeof(char), stdin);
    telefoneCliente[strcspn(telefoneCliente, "\n")] = '\0';

    // irá realizar a validação do telefone
    if (!ValidarTelefone(telefoneCliente)) {
        printf("Telefone inválido, insira um telefone válido ou E para desistir.\n");
        fgets(opcao, sizeof(opcao) / sizeof(char), stdin);
        opcao[strcspn(opcao, "\n")] = '\0';

        // Caso o usuário desista de inserir, ele pode pressionar E ou e para desistir
	if (opcao[0] == 'E' || opcao[0] == 'e') return 0;

        // Continue para a próxima iteração do loop para que o usuário insira o telefone novamente
        continue;
    }

    // Se chegou até aqui, os dados são válidos
    break;

} while (1);

return 1;

// Função de cadastrar os pets
int cadastrarPet(Animal *MeusAnimais, int *tamanhoAnimais, Cliente *MeusClientes, int tamanhoClientes) {





//	meusCliente[*tamanho].nome = nomeClie;
	
//	meusCliente[*tamanho].nome = telefone;
//	(*tamanho)++;
//	return 1;
} //tava faltando aqui, acho q corto qndo colou, se estiver errado so tirar

int main() {
	char[51] in; // Variavel que guarda a entrada do Usuario no console | maior entrada valida e de 50, precisamos +1 pelo \n que fgets() pega
	tamanhos[] = {0,0}; // Quantidade de entradas por vetor ordem: MeusClientes, MeusAnimais
	Cliente MeusClientes[100]; // Inicializacao dos vetores
	Animal MeusAnimais[100];
	printf("Bem Vindo!\n'h' para comandos, 'e' para terminar;\n"); // Mensagem de inicio
	while (strcmp(fgets(in,50,stdin), "e\n")!= 0) { // Enquanto o que se lee, nao for 'e', continuemos leendo os comandos..
		switch(in[0]) { // Controle de menus
			case 'h' : // Menu de comandos
				printf(MENUDECOMANDOS);
				break;
			case 'c' : // Menu de cadastro
				do {
					cadastrarCliente(); // Funcao cadastro cliente
					printf("Deseja cadastrar outro cliente? 's' para sim, 'n' para não: ");
					do {                // Enquanto a resposta nao for valida, continue lendo
						fgets(in,50,stdin);
					} while (in[0] != 'n' || in[0] != 's')
					if (in[0] == 'n') break; // Se a resposta for Nao, pare de cadastrar, se nao, continue
				} while(1)
				break;
			case 'a' : // Menu impressao de animais alfabeticamente
				meuSort(MeusAnimais,&tamanhos[1]); // Organizar os Animais Alfabeticamente
				printf("%s\n", imprimirAnimais(MeusAnimais,&tamanhos[1])); // Imprimir a Tabela dos Animais
				break;
			case 'l' : // Commando limpar o console
				system("clear");
				break;
		}
		free(); // Limpar memoria alocada dinamicamente (Strings dinamicas)
  	}
  	return 0;
}
