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
#define MENU_DE_COMANDOS "\n'a' para cadastrar um novo animal;\n'q' para mostrar quantidade de animais agressivos\n'p' para listar animais;\n'l' para limpar o console;\n'c' para cadastrar um cliente;\n'e' para terminar;\n\ndigite aqui: "

const char ESPECIES[][] = {"York","Yorkie","Yorkshire","York fofo", "Yorkiezinho", "Yorkiiiiee >///<"};

// Configuracao Tabela de Pesquisa por Clientes
char tabelaPesquisaClientesNomeColunas[][]   = {"#","Nome"};
int confTabelaPesquisaClientes[]             = {3,2,14};

// Configuracao Tabela de Animais Aggressivos
char tabelaAnimaisAggressivosNomeColunas[][] = {"Quantidade"}; // O nome das colunas quando tabeladas
int confTabelaAnimaisAggressivos[]           = {2,13}; // Representa Tamanho de cada coluna em ordem, o primeiro valor e o tamanho do Vetor

// Configuracao Tabela Animais Completa
char tabelaAnimaisNomeColunas[][]            = {"Nome", "Especie", "Agressivo", "Data de Nascimento", "Nome do Cliente", "Telefone"};
int confTabelaAnimais[]                      = {7,14,12,20,13,14}; // Primeiro Valor tamanho do Array
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
char *stringDinamica(int tamanho) return (char*) malloc(tamanho*sizeof(char));

char *aumentarTamString(char *string, int tamanho) return (char*) realloc(string,tamanho*sizeof(char));

int *vetorIntDinamico(int tamanho) return (int*) malloc(tamanho*sizeof(int));

int *aumentarVetorInt(int *vetor, int tamanho) return (int*) realloc(vetor,tamanho*sizeof(int));

void sortAnimais(Animal *meusAnimais, int tamanho) {
    	Animal meuAnimal;
    	for (int x = 0; x < tamanho-1; x++) {
    		for (int y = x+1; y < tamanho; y++) {
    			if (strcmp(meusAnimais[x].nomeAnimal, meusAnimais[y].nomeAnimal) > 0) {
    				meuAnimal = meusAnimais[x];
    				meusAnimais[x] = meusAnimais[y];
    				meusAnimais[y] = meuAnimal;
    			}
    		}
    	}
}

void sortClientes(Cliente *meusClientes, int tamanho) {
    	Cliente meuCliente;
    	for (int x = 0; x < tamanho-1; x++) {
    		for (int y = x+1; y < tamanho; y++) {
    			if (strcmp(meusClientes[x].nomeCliente, meusClientes[y].nomeCliente) > 0) {
    				meuCliente = meusClientes[x];
    				meusClientes[x] = meusClientes[y];
    				meusClientes[y] = meuCliente;
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

char *anexarFileira(char **colunas, int confTabela[], int PrimeiraFileira) {
	int cursor = 0, // Posicao em que se esta escrevendo
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

int find(char from[], char to[]) {
	if (strcmp(to,"") == 0) return 1;
    	int cursor = 0,
            valid;
    	while (from[cursor] != '\0') {
        valid = 0;
        for (int i = 0; i < strlen(to) && cursor+i < strlen(from); i++) {
            	if (!(from[cursor+i] == to[i])) {
                	break;
            	} else if (i+1 == strlen(to)) valid = 1;
        }
        if (valid == 1) break;
        	cursor++;
    	}
    	return valid;
}

char **criarColunaPesquisaClientes(Cliente oC, int numero) {
	char coluna[][] = {     posIntToChar(numero),
	                        oC.nomeCliente};
	return coluna;
}

int *mapaListagemClientesPorPesquisa(Cliente *Clientes, int tamanho, char[] termo) {
	int meuVetor[101],
	    i = 1
	    tamanhoTabela;
	char minhaTabela[1000];
	strcpy(minhaTabela, anexarFileira(tabelaPesquisaClientesNomeColuna,confPesquisaClientes,1)); // Colocar primeira fileira na tabela
	for (int j = 0; j < tamanho; j++) {
		if (find(Clientes[j].nomeCliente, termo) == 1) {
			char *novaFileira = anexarFileira(criarColunaPesquisaClientes(Clientes[j],i), confPesquisaClientes, 0));
			int tamanhoNovaFileira = strlen(novaFileira);
			tamanhoTabela = strlen(minhaTabela);
			myStrCpy(minhaTabela, novaFileira, &tamanhoTabela, tamanhoNovaFileira, 0);
			meuVetor[i] = j;
			i++;
		}
	}
	meuVetor[0] = i-1; // meuVetor[0] Vai ser a quantidade de valores retornados
	if (meuVetor[0] > 0) printf("%s\n",minhaTabela);
	return meuVetor;
}

char *qntdAnimaisAgressivos(Animal *MeusAnimais, int quantidadeDeAnimais) {
	int contagem = 0,
	    tamanhoPrimeiraFileira; // Se refere a posicao no string da primeira fileira, pra escrever a partir dela na segunda
	char impressao[400],
	     confColunaComQuantidadeDeAgressivos[1][4];
	     primeiraFileira*; // nn sei se pode
	     fileiraDeConteudo*;
	for (int i = 0; i < quantidadeDeAnimais; i++) {
  		if (MeusAnimais[i].  == 'S') contagem++;
  	}
	strcpy(colunaComQuantidadeDeAgressivos[0],posIntToChar(contagem)); // Montar a coluna com o numero de Aggressivos
	strcpy(primeiraFileira, anexarFileira(tabelaAnimaisAggressivosNomeColunas,confTabelaAnimaisAggressivos,1));
	strcpy(fileiraDeConteudo, anexarFileira(colunaComQuantidadeDeAgressivos,confTabelaAnimaisAggressivos,0));
	tamanhoPrimeiraFileira = strlen(primeiraFileira);
	strcpy(impressao, primeiraFileira);
	myStrCpy(impressao, fileiraDeConteudo, &tamanhoPrimeiraFileira, strlen(fileiraConteudo),0);
	return impressao;
}

char **criarColunaAnimais(Animal oA) {
	char coluna[][] = {     oA.nomeAnimal,
				ESPECIE[oA.especie],
				oA.agressivo,
				dataParaChar(oA.dataNascimento),
				oA.cliente->nomeCliente,
				oA.cliente->telefoneCliente};
	return coluna;
}

char *baseadoEmNomePet (char *Nome, Animal *Pets, int tamanhoVetorAnimais){
	char impressao[400];
  	for (int i = 0; i < tamanhoVetorAnimais; i++){
  		if (strcmp (Pets[i].nomeAnimal, Nome) == 0) {
			char *primeiraFileira   = anexarFileira(tabelaAnimaisNomeColunas,confTabelaAnimais,1); //nn sei se pode
			char *fileiraDeConteudo = anexarFileira(criarColunaAnimais(Pets[i]),confTabelaAnimais,0);
			int tamanhoDaPrimeiraFileira = strlen(primeiraFileira);
			int tamanhoFileiraDeConteudo = strlen(fileiraDeConteudo);
			strcpy  (impressao, primeiraFileira);                                             // Copiar a primeira fileira para impressao
			myStrCpy(impressao, fileiraDeConteudo, &tamanhoDaPrimeiraFileira, tamanhoFileiraDeConteudo, 0); // Copiar fileira de conteudo
			return impressao;
 		}
	}
	return "Pet nao encontrado";
}

char *imprimirAnimais(Animal Animais[],int *tamanho) {
	int cursor = 0;
	char *minhaImpressao = stringDinamica(1);
	anexarFileira(tabelaAnimaisNomeColunas, confTabelaAnimais, 1);
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

// Função para validar nomes
int nomeValido(char *in) {
    int valid = 0;

    for (int i = 0; i < strlen(in); i++) {
        if ((in[i] < 65 || (in[i] > 90 && in[i] < 97) || in[i] > 122) && in[i] != ' ') { //os números 65, 90, 97 e 122 estão em formato da representação ASCII
            valid = -1;
            break;
            } else if (in[i] != ' ') {
            valid++;
            }
        }

    if (valid >= 3) {
        return 1; // Válido
        } else {
        return 0; // Inválido
        }
    }

// Função para validar telefones
    int validarTelefone(char telefoneCliente[15]) {
    // Verifica se o telefone tem tamanho entre 11 e 12 e se o primeiro caractere é '0'
    if (!(strlen(telefoneCliente) >= 11 && strlen(telefoneCliente) <= 12 && telefoneCliente[0] == '0')) {
        return 0; // Inválido
    }

    // Verifica se todos os caracteres restantes são dígitos numéricos válidos
    for (int j = 1; j < strlen(telefoneCliente); j++) {
        if (telefoneCliente[j] < '0' || telefoneCliente[j] > '9') {
            return 0; // Inválido
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
			case 'a' : // Menu de cadastro de animal

				break;
			case 'c' : // Menu de cadastro de cliente
				do {
					cadastrarCliente(); // Funcao cadastro cliente
					printf("Deseja cadastrar outro cliente? 's' para sim, 'n' para não: ");
					do {                // Enquanto a resposta nao for valida, continue lendo
						fgets(in,50,stdin);
					} while (in[0] != 'n' || in[0] != 's')
					if (in[0] == 'n') break; // Se a resposta for Nao, pare de cadastrar, se nao, continue
				} while(1)
				break;
			case 'p' : // Menu impressao de animais alfabeticamente
				sortAnimais(MeusAnimais,&tamanhos[1]); // Organizar os Animais Alfabeticamente
				printf("%s\n", imprimirAnimais(MeusAnimais,&tamanhos[1])); // Imprimir a Tabela dos Animais
				break;
			case 'l' : // Commando limpar o console
				system("clear");
				break;
			case 'q' : // Mostrar quantidade de Animais Agressivos
				printf("%s\n", qntdAnimaisAgressivos(MeusAnimais, tamanhos[1]));
				break;
		}
		free(); // Limpar memoria alocada dinamicamente (Strings dinamicas/ Vetores inteiros Dinamicos)
  	}
  	return 0;
}
