/*
Trabalho Final da Disciplina de Algoritmos 01: Gerenciador de PetShop.
Turma: EC41A.2023_01.C11 / Data:18/04/2023.
Nomes:André Antônio da Silva Queiroz    | RA:a2575310
......Mathias Vinicius Carcano Ferretti | RA:a2575396
......Gabriel Henrique Prado Affonso    | RA:a2618044
*/
//bibliotecas que o professor pediu para que tenha no máximo.
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Definimos as informações da data aqui em cima, para facilitar o encontro para a manuntenção dessas informações, entre os membros.
#define DIA 1
#define MES 12 
#define ANO 2023

#define MAX_SERVICO 4

#define INICIO "\n\n🏠 'h' para comandos, 🚪 'e' para terminar;\nDigite aqui:  "
#define MENU_DE_COMANDOS "\n🐾   '1' para realizar cadastros;\n🦁   '2' para conhecer ou pagar por nossos servicos\n📋   '3' para ver as listas;\n[]  'l' para limpar o console;\n🛑   'e' para terminar;\n"
#define MENU_CADASTRO "\nBem vindo ao Petshop 🐕 {AU AU!}\nDigite 'p' para cadastrar pets\nDigite 'c' para cadastrar cliente\nDigite 'e' para terminar!\n"
#define MENU_SERVICOS "\nDigite 'o' para saber os serviços que oferecemos!\nDigite 'p' caso você deseja pagar 🤑\nDigite 'e' para terminar!\n"
#define MENU_LISTAGEM "\nDigite '1' para buscar dados do cliente!\nDigite '2' para buscar animal pelo nome dele\nDigite '3' para ver os pets cadastrados!\nDigite '4' para saber quais os animais agressivos!\nDigite '5' para ver a lista de animais por espécie\nDigite '6' para ver os pets aniversariantes\nDigite '7' para ver os serviços não pagos (por animal)!\nDigite '8' para saber o serviço mais utilizado ou pressione 'e' para terminar!\n"

const char ESPECIES[][14] = {"Cachorro","Gato","Hamster","Pássaro", "Coelho"};

// Configuracao Tabela de Animais Por Especie
char *tabelaAnimaisPorEspecie[14]             = {"Especie", "Nome", "Data de Nascimento", "Agressivo"};
int confTabelaAnimaisPorEspecie[]             = {5, 14, 14, 12, 2}; // Primeiro Valor tamanho do Vetor

// Configuracao Tabela de Especies
char *tabelaEspecies[14]                      = {"#","Especie"};
int confTabelaEspecies[]                      = {3, 2, 14} ;

// Configuracao Tabela de Pesquisa por Clientes
char *tabelaPesquisaClientesNomeColunas[14]   = {"#","Nome"};
int confTabelaPesquisaClientes[]              = {3, 2, 14};

// Configuracao Tabela de Animais Aggressivos
char *tabelaAnimaisAggressivosNomeColunas[14] = {"Quantidade"}; // O nome das colunas quando tabeladas
int confTabelaAnimaisAggressivos[]            = {2, 13}; // Representa Tamanho de cada coluna em ordem, o primeiro valor e o tamanho do Vetor

// Configuracao Tabela Animais Completa
char *tabelaAnimaisNomeColunas[40]            = {"Dono", "Telefone", "Nome", "Especie", "Agressivo", "DOB"};
int confTabelaAnimais[]                       = {7, 14, 14, 14, 14, 11, 12}; 

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

//funcao que cria uma string de tamnaho dinamico
char *stringDinamica(int tamanho) {return (char*) malloc(tamanho*sizeof(char));}

//funcao que aumenta tamanho de string dinamico
char *aumentarTamString(char *string, int tamanho) {return (char*) realloc(string,tamanho*sizeof(char));}

//funcao que cria um vetor de strings dinamicos
char **vetorStringsDinamicos(int tamanhoVetor, int tamanhoString) {
    char **out = (char**) malloc(sizeof(char*)*tamanhoVetor);
    for (int i = 0; i < tamanhoVetor; i++) {
        out[i] = stringDinamica(tamanhoString);
    }
    return out;
}

//funcao que cria um vetor de inteiros de tamnaho dinamico
int *vetorIntDinamico(int tamanho) {int *out = (int*) malloc(tamanho*sizeof(int)); return out;}

int *aumentarVetorInt(int *vetor, int tamanho) {int *out = (int*) realloc(vetor,tamanho*sizeof(int)); return out;} //funcao que aumenta tamanho de vetor inteiro dinamico

// funcao que transforma uma string de minuscula para maiuscula
char *toUpper(char in[], int tamanho) {
	char *cpy = stringDinamica(tamanho);
    	for (int i = 0; i < tamanho; i++) {
	    cpy[i] = ((in[i] >= 'a' && in[i] <= 'z') ? in[i] + ('A' - 'a') : in[i]);
	}
    	return cpy;
}

// funcao que organiza animais alfabeticamente
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

void sortAnimaisEspecie(Animal *meusAnimais, int tamanho) {
	Animal meuAnimal;
    	for (int x = 0; x < tamanho-1; x++) {
    		for (int y = x+1; y < tamanho; y++) {
			// se a especie for pra vir depois                  ou                                   alfabeticamente depois             e      mesma especie
    			if (meusAnimais[x].especie > meusAnimais[y].especie || ((strcmp(meusAnimais[x].nomeAnimal, meusAnimais[y].nomeAnimal) > 0) && (meusAnimais[x].especie == meusAnimais[y].especie)) ) {
    				// trocar a ordem
				    meuAnimal = meusAnimais[x];
    				meusAnimais[x] = meusAnimais[y];
    				meusAnimais[y] = meuAnimal;
    			}
    		}
    	}
}

//função que organiza os clientes alfabeticamente
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

//função que copia a segunda string na primeira a partir do ponto i, escrevendo nela lee characteres vazios, tem configuracao adaptada para montar uma coluna, ou fileira de linha
//Msm funcao de str cpy soq ele comeca por int i dado, agregando a ele conforme escreve, e int lee, de leeway para limite de escrita, substituindo com espacos brancos | pft para escrever fileiras
void myStrCpy (char *str1, char *str2, int *i, int lee, int writeColuna) { 
        int len;
        char cpyFrm[2] = {' ', '|'};
    	if (writeColuna < 0) {cpyFrm[0] = '-'; cpyFrm[1] = '+';}
    	len = strlen(str2);
    	if (writeColuna > -3 && writeColuna < 3 && writeColuna != 0) {str1[(*i)] = cpyFrm[1]; (*i)++;}
        for (int j = (*i);(*i)-j < lee-1; (*i)++) {
        	str1[(*i)] = ((len > (*i)-j) ? str2[(*i)-j] : cpyFrm[0]); //se escrevo primeira coluna copio de um a menos para um a mai
        }
    	if (writeColuna > 1 || writeColuna < -1) {str1[(*i)] = cpyFrm[1]; (*i)++;}
	str1[(*i)] = '\0';
}

//função que transforma um numero inteiro positivo em um char
char *posIntToChar(int in) {
  	int mx = ((in == 0) ? 1 : 1+(int) log10(in)); // Quantidade maxima de numeros
 	char *myChar = (char*) malloc(mx+1); // Criar string com tamanho de Numeros+2
	for (int i = 0; i < mx; i++) {
      		int toInt = in/pow(10,(mx-i)-1); // Dividir para ficar so um numero positivo com o resto em virgulas
      		myChar[i] = 48+toInt; // Colocar a letra do numero na string
      		in -= toInt*pow(10,mx-i-1); // Tirar o numero ja colocado do numero composto
  	}
  	myChar[mx] = '\0'; // colocar o byte nulo no fim da string
  	return myChar;
}

//função que transforma uma data em string e retorna ela
char *dataParaChar(Data data) {
	int i = 0;
	char *out = (char*) malloc(12);
	void anexarValor(char *valor, int letras) {myStrCpy(out,valor,&i,letras+1,0);}
	void anexarBarra() {anexarValor("/",1);}
	anexarValor(posIntToChar(data.dia),2);
	anexarBarra();
	anexarValor(posIntToChar(data.mes),2);
	anexarBarra();
	anexarValor(posIntToChar(data.ano),4);
	out[10] = '\0';
	return out;
}

//função que anexa retorna uma fileira de tabela baseada nas configuracoes de coluna e coluna tamanho, pode ser primeira fileira ou nao
char *anexarFileira(char **colunas, int confTabela[], int primeiraFileira) {
	int cursor = 0, // Posicao em que se esta escrevendo
		flT = 0; // Fileira linha Tamanho
    	char *minhaFileiraLinha = stringDinamica(1), // A linha que separa conteudo das fileiras
    		*minhaImpressao = stringDinamica(1); // A string da tabela inteira que vou montar
    	void criacaoFileiraLinha() { // Inicializa a Fileira Linha
    		for (int i = 1; i < confTabela[0]; i++) flT += confTabela[i]+1; // Contar tamanho total da fielira
 		    minhaFileiraLinha = aumentarTamString(minhaFileiraLinha,flT+2);
		    for (int i = 1; i < confTabela[0]; i++)
    			myStrCpy(minhaFileiraLinha, "", &cursor, confTabela[i], ((i == 1) ? -2 : -3)); // -2 quer dizer que irá criar o inicial e o segundo, -3 vai acrescentando
    		minhaFileiraLinha[cursor] = '\n';
		    minhaFileiraLinha[cursor+1] = '\0';
		    cursor = 0;
    	}
	void anexarColuna(char *valor, int coluna) {
	    minhaImpressao = aumentarTamString(minhaImpressao, confTabela[coluna]+cursor+2 ); // nn sei pq caralhos ta funcionando com 15 e com menos me da erro??????
	    myStrCpy(minhaImpressao, valor, &cursor, confTabela[coluna], ((coluna == 1) ? 2 : 3));} // Se for primeira linha quero linha de coluna antes tambem
	void anexarFL() {
	    minhaImpressao = aumentarTamString(minhaImpressao, flT+cursor+2 );
	    myStrCpy(minhaImpressao,minhaFileiraLinha,&cursor,strlen(minhaFileiraLinha),0);} // Anexar fileira linha
	void anexarNL() {
	    minhaImpressao = aumentarTamString(minhaImpressao, cursor+2 );
	    minhaImpressao[cursor] = '\n';
	    minhaImpressao[cursor+1] = '\0';
	    cursor ++;}
	    //myStrCpy(minhaImpressao,"\n",&cursor,1,0);} // Anexar "New Line" (enter)
	criacaoFileiraLinha();
	if (primeiraFileira == 1) anexarFL();
	anexarNL();
	for (int i = 0; i < confTabela[0]-1; i++) {
		anexarColuna(colunas[i], i+1);
	}
	anexarNL();
	anexarFL();
	anexarNL();
	minhaImpressao[cursor+1] = '\0';
	return minhaImpressao;
}

//função que procura para ver se o termo to se encontra no string from
int find(char from[], char to[]) {
	if (strcmp(to,"") == 0) return 1; // se nn tem nada pra procurar ele encontrou
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

//função que verifica se o animal é aniversariante
int animalAniversariante(int diaInscricao, int mesInscricao) {
    int tamanhoMes[] = {0, 31, ((ANO % 4 == 0) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Se o mês de aniversário é igual ao mês de inscrição, verifica se o dia de aniversário é posterior ao de inscrição
    if (MES == mesInscricao && DIA > diaInscricao) {
        return DIA - diaInscricao <= 7;
    }

    // Se o mês de aniversário é posterior ao mês de inscrição
    if (MES > mesInscricao) {
        // Calcula os dias restantes no mês de inscrição
        int diasRestantes = tamanhoMes[mesInscricao] - diaInscricao;

        // Calcula os dias desde o dia seguinte ao da inscrição até o dia do aniversário no mês seguinte
        int diasParaAniversario = diasRestantes + DIA;

        return diasParaAniversario <= 7;
    }

    return 0; // Caso contrário, não está aniversariando nos próximos 7 dias
}

//função que cria a configuracao de coluna da tabela de especies dada o numero inteiro da especie
char **criarColunaEspecies(int numero) {
	char **coluna = vetorStringsDinamicos(2,14);
	strcpy(coluna[0], posIntToChar(numero));
	strcpy(coluna[1], ESPECIES[numero]);
	return coluna;
}

//função que ele imprime a tabela de todas as especies com o numero associado
void imprimirTabelaEspecies() {
	int quantidadeEspecies = sizeof(ESPECIES) / sizeof(ESPECIES[0]);
	char fileira[1000];
	strcpy(fileira, anexarFileira(tabelaEspecies,confTabelaEspecies,1));
	fileira[strlen(fileira)-1] = '\0';
	printf("%s", fileira);
	for (int i = 0; i < quantidadeEspecies; i++) {
	    strcpy(fileira, anexarFileira(criarColunaEspecies(i),confTabelaEspecies,2));
	    fileira[strlen(fileira)-1] = '\0';
		printf("%s",fileira);
	}
	printf("\n");
}

//função que cria configuracao da fileira de impressao de tabela de Cliente com o numero associado // usada na busca de clientes cadastrados
char **criarColunaPesquisaClientes(Cliente oC, int numero) { //oC O Cliente
	char **coluna = vetorStringsDinamicos(2,14);
	strcpy(coluna[0], posIntToChar(numero));
	strcpy(coluna[1], oC.nomeCliente);
	return coluna;
}

//função que organiza os clientes alfabeticamente, depois ele procura por clientes que foram pesquisados por string termo, e faz a tabela com eles // se o termo for vazio quer dizer que é pra imprimir tudo
int *mapaListagemClientesPorPesquisa(Cliente *Clientes, int tamanho, char termo[]) {
	sortClientes(Clientes, tamanho); // Organizar os clientes em ordem alfabetica pra ficar mais bonitinho
	int *meuVetor = vetorIntDinamico(101),
	    i = 1,
	    tamanhoTabela;
	char minhaTabela[1000];
	strcpy(minhaTabela, anexarFileira(tabelaPesquisaClientesNomeColunas,confTabelaPesquisaClientes,1)); // Colocar primeira fileira na tabela
	for (int j = 0; j < tamanho; j++) {
		if (find(Clientes[j].nomeCliente, termo) == 1) { // Se eu encontrar baseado no conceito da pesquisa:
			char *novaFileira = anexarFileira(criarColunaPesquisaClientes(Clientes[j],i), confTabelaPesquisaClientes, 0);
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

char **criarColunaTabelaAnimaisPorEspecie(Animal oA) { //oC O Cliente
	char **coluna = vetorStringsDinamicos(5,14);
    	char stringDeAgressivo[] = {oA.agressivo,'\0'};
	strcpy(coluna[0], ESPECIES[oA.especie]);
	strcpy(coluna[1], oA.nomeAnimal);
	strcpy(coluna[2], dataParaChar(oA.dataNascimento));
	strcpy(coluna[3], stringDeAgressivo);
	return coluna;
}

char* imprimirTabelaAnimaisPorEspecie(Animal Animais[],int *tamanho) {
	sortAnimaisEspecie(Animais, *tamanho);
	if (*tamanho == 0) return "Nenhum Resultado Encontrado\n";
	int cursor = 0;
 	char *impressao = stringDinamica(1),
  		fileira[1000];
    	strcpy(fileira, anexarFileira(tabelaAnimaisPorEspecie,confTabelaAnimaisPorEspecie,1));
     	impressao = aumentarTamString(impressao, (int) (strlen(fileira)+2));
	myStrCpy(impressao, fileira, &cursor, strlen(fileira),0);
    	for(int i = 0; i < (*tamanho); i++) {
		Animal oA = Animais[i];// oA de O Animal
		strcpy(fileira,  anexarFileira(criarColunaTabelaAnimaisPorEspecie(Animais[i]),confTabelaAnimaisPorEspecie,2));
     	impressao = aumentarTamString(impressao, (int) (strlen(fileira)+30+cursor));
		myStrCpy(impressao, fileira, &cursor, strlen(fileira),0);
	}
 	return impressao;
}

//função retorna a tabela de quantidade de animais agressivos para ser impresso
char *qntdAnimaisAgressivos(Animal *MeusAnimais, int quantidadeDeAnimais) {
	int contagem = 0,
	    cursor = 0;
	char *impressao = stringDinamica(1),
	     *fileiraComQuantidade = stringDinamica(100),
	     **colunaComQuantidadeDeAgressivos = &fileiraComQuantidade,
  	     fileira[1000];
	for (int i = 0; i < quantidadeDeAnimais; i++) {
  		if (MeusAnimais[i].agressivo  == 'S') contagem++;
  	}
	strcpy(fileiraComQuantidade,posIntToChar(contagem));
    strcpy(fileira, anexarFileira(tabelaAnimaisAggressivosNomeColunas,confTabelaAnimaisAggressivos,1));
     	impressao = aumentarTamString(impressao, (int) (strlen(fileira)+2));
	myStrCpy(impressao, fileira, &cursor, strlen(fileira),0);
	strcpy(fileira,  anexarFileira(colunaComQuantidadeDeAgressivos,confTabelaAnimaisAggressivos,0));
     	impressao = aumentarTamString(impressao, (int) (strlen(fileira)+30+cursor));
	myStrCpy(impressao, fileira, &cursor, strlen(fileira),0);
 	return impressao;
}

// funcao que retorna a configuracao de uma coluna de uma tabela de animais baseado em um animal especifico, essa conf e usada na funcao de impressao para criar uma fileira da tabela
char **criarColunaAnimais(Animal oA) {
    char **coluna = vetorStringsDinamicos(6,52);// vetorStringsDinamicos(6, 20);
    char stringDeAgressivo[] = {oA.agressivo,'\0'};
	strcpy(coluna[0], oA.cliente->nomeCliente);
	strcpy(coluna[1], oA.cliente->telefoneCliente);
	strcpy(coluna[2], oA.nomeAnimal);
	strcpy(coluna[3], ESPECIES[oA.especie]);
	strcpy(coluna[4], stringDeAgressivo);
	strcpy(coluna[5], dataParaChar(oA.dataNascimento)); // data para char ainda nn funciona
	return coluna;
}

// função que retorna uma tabela de uma fileira com as caracteristicas do animal com o nome para ser impresso
char *baseadoEmNomePet (char *Nome, Animal *Pets, int tamanhoVetorAnimais){
	char *impressao = stringDinamica(1000);
  	for (int i = 0; i < tamanhoVetorAnimais; i++){
  		if (strcmp (Pets[i].nomeAnimal, Nome) == 0) {
			char *primeiraFileira   = anexarFileira(tabelaAnimaisNomeColunas,confTabelaAnimais,1); //nn sei se pode
			char *fileiraDeConteudo = anexarFileira(criarColunaAnimais(Pets[i]),confTabelaAnimais,0);
			int tamanhoDaPrimeiraFileira = strlen(primeiraFileira) - 1;
			int tamanhoFileiraDeConteudo = strlen(fileiraDeConteudo);
			strcpy  (impressao, primeiraFileira);                                             // Copiar a primeira fileira para impressao
			myStrCpy(impressao, fileiraDeConteudo, &tamanhoDaPrimeiraFileira, tamanhoFileiraDeConteudo, 0); // Copiar fileira de conteudo
			return impressao;
 		}
	}
	return "Pet nao encontrado";
}

// função que leva o tamanho do vetor animais, e o vetor | ele organiza alfabeticamente, e depois retorna uma tabela com todos os animais e suas caracteristicas para ser impresso
char* imprimirAnimais(Animal Animais[],int *tamanho) {
	if (*tamanho == 0) return "Nenhum Resultado Encontrado\n";
	int cursor = 0;
 	char *impressao = stringDinamica(1),
  		fileira[1000];
    	strcpy(fileira, anexarFileira(tabelaAnimaisNomeColunas, confTabelaAnimais, 1));
     	impressao = aumentarTamString(impressao, (int) (strlen(fileira)+2));
	myStrCpy(impressao, fileira, &cursor, strlen(fileira),0);
    	for(int i = 0; i < (*tamanho); i++) {
		Animal oA = Animais[i];// oA de O Animal
		strcpy(fileira,  anexarFileira(criarColunaAnimais(oA), confTabelaAnimais, 0));
     	impressao = aumentarTamString(impressao, (int) (strlen(fileira)+30+cursor));
		myStrCpy(impressao, fileira, &cursor, strlen(fileira),0);
	}
 	return impressao;
}

char* imprimirAnimaisAniversariantes(Animal Animais[],int *tamanho) {
	if (*tamanho == 0) return "Nenhum Resultado Encontrado\n";
	int cursor = 0,
	    ctr = 0;
 	char *impressao = stringDinamica(1),
  		fileira[1000];
    	strcpy(fileira, anexarFileira(tabelaAnimaisNomeColunas, confTabelaAnimais, 1));
     	impressao = aumentarTamString(impressao, (int) (strlen(fileira)+2));
	myStrCpy(impressao, fileira, &cursor, strlen(fileira),0);
    	for(int i = 0; i < (*tamanho); i++) {
			Animal oA = Animais[i];// oA de O Animal
		    if (animalAniversariante(oA.dataNascimento.dia,oA.dataNascimento.mes) == 1) {
			    ctr = 1;
			    strcpy(fileira,  anexarFileira(criarColunaAnimais(oA), confTabelaAnimais, 0));
	     		impressao = aumentarTamString(impressao, (int) (strlen(fileira)+30+cursor));
			    myStrCpy(impressao, fileira, &cursor, strlen(fileira),0);
		}
	}
	if (ctr > 0)
	 	return impressao;
	else return "Nenhum Resultado Encontrado\n";
}
// Função para validar nomes
int nomeValido(char *in) {
    int valid = 0;

    for (int i = 0; i < strlen(in); i++) {
        if ((in[i] < 'A' || (in[i] > 'Z' && in[i] < 'a') || in[i] > 'z') && in[i] != ' ') { 
            valid = -1;
            break;
            } else if (in[i] != ' ') {
            valid++;
            }
        }

    if (valid >= 3) { //pois tem que ter 3 letras
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

//função que verifica os dias validos dependendo do mês de inscrição
int verificarDiaValido(int dia, int mes, int ano) {
    int tamanhoMes[] = {0, 31, ((ano % 4 == 0) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return (dia >= 1 && dia <= tamanhoMes[mes]);
}

//função que valida a data dependendo do ano que o usuário se cadastrou
int validarData(int dia, int mes, int ano) {
    if (ano < 1977 || ano > ANO) {
        return 0; // Inválido
    } else if (ano == ANO) {
        if (mes < 1 || mes > MES) {
            return 0; // Inválido
        } else if (mes == MES) {
            return (dia >= 1 && dia <= DIA);
        } else {
            return verificarDiaValido(dia, mes, ano);
        }
    } else {
        return (mes >= 1 && mes <= 12) && verificarDiaValido(dia, mes, ano);
    }
}

// Função para cadastrar os clientes
Cliente* cadastrarCliente(Cliente *MeusClientes, int *tamanhoClientes) {
    char nomeCliente[50];
    char telefoneCliente[15];

    // Recebe o nome do cliente e armazena dentro do char
    do { 
        printf("Nome do cliente: ");
        fgets(nomeCliente, sizeof(nomeCliente) / sizeof(char), stdin); 
        nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

        // Irá realizar a validação do nome
        if (!nomeValido(nomeCliente)) {
            printf("Nome inválido, E para desistir, ou algum botão para continuar\n");
            fgets(nomeCliente, sizeof(nomeCliente) / sizeof(char), stdin);
            nomeCliente[strcspn(nomeCliente, "\n")] = '\0';
            
            // Caso o usuário desista de inserir, ele pode pressionar E ou e para desistir
            if (nomeCliente[0] == 'E' || nomeCliente[0] == 'e') return 0;

            // Continue para a próxima iteração do loop para que o usuário insira o nome novamente
            continue;
        } else break;
    } while (1);

    do {
        // Recebe o telefone do cliente e armazena dentro do char
        printf("Telefone do cliente: ");
        fgets(telefoneCliente, sizeof(telefoneCliente) / sizeof(char), stdin);
        telefoneCliente[strcspn(telefoneCliente, "\n")] = '\0';

        // irá realizar a validação do telefone
        if (!validarTelefone(telefoneCliente)) {
            printf("Telefone inválido, E para desistir, ou algum botão para continuar.\n");
            fgets(telefoneCliente, sizeof(telefoneCliente)/sizeof(char), stdin);
            telefoneCliente[strcspn(telefoneCliente, "\n")] = '\0';
            
            if (telefoneCliente[0] == 'E' || telefoneCliente[0] == 'e') return 0; // Caso o usuário desista de inserir, ele pode pressionar E ou e para desistir
            continue; // Continue para a próxima iteração do loop para que o usuário insira o telefone novamente
        } else break;
    } while (1);

    strcpy(MeusClientes[(*tamanhoClientes)].nomeCliente, nomeCliente);
    strcpy(MeusClientes[(*tamanhoClientes)].telefoneCliente, telefoneCliente);
    (*tamanhoClientes)++; 
    return &MeusClientes[(*tamanhoClientes)-1]; // O ponteiro aponta para a última posição válida da lista de clientes, que é MeusClientes[(*tamanhoClientes)-1]
}

// Função para buscar o cliente e imprimir os seus dados e do pet, se existir
Cliente* buscarClienteImprimir(Cliente *Clientes, int tamanhoClientes, Animal *MeusAnimais, int tamanhoAnimais, int opcao) {
    char nomeBusca[50];
    Cliente* ClienteEncontrado = NULL; 
	int encontrei = 0;

	printf("Digite o nome do cliente que deseja procurar: ");
    fgets(nomeBusca, sizeof(nomeBusca)/sizeof(char), stdin); // Solicita uma entrada de nome para realizar a busca
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

	for (int i = 0; i < tamanhoClientes; i++) {
        if (strcmp(Clientes[i].nomeCliente, nomeBusca) == 0) { //Percorre o loop e vê se o cliente existe
            ClienteEncontrado = &Clientes[i];
            // Cliente encontrado, imprime os dados
            printf("\nDados do Cliente:\n");
            printf("Nome: %s\n", Clientes[i].nomeCliente);
            printf("Telefone: %s\n", Clientes[i].telefoneCliente);

 			
 	if (opcao == 0) {
 	    printf("\nPets do Cliente:\n");
    for (int j = 0; j < tamanhoAnimais; j++) { // Percorre o loop de pet e vê se tem pet cadastrado
                if (MeusAnimais[j].cliente == &Clientes[i]) {
					encontrei = 1; // Pet encontrado, imprime os dados
                    printf("Nome do Pet: %s\n", MeusAnimais[j].nomeAnimal);
                    printf("Espécie: %s\n", ESPECIES[MeusAnimais[j].especie]);
                    printf("Agressivo: %c\n", MeusAnimais[j].agressivo);
                    printf("Data de Nascimento: %02d/%02d/%04d\n", MeusAnimais[j].dataNascimento.dia, MeusAnimais[j].dataNascimento.mes, MeusAnimais[j].dataNascimento.ano);
                    printf("-------------------------\n");
				}
			}
			if (encontrei == 0) {
				printf("O cliente não possui pets."); 
			}
 	    }
 	    return ClienteEncontrado;
        } 
    }
	
	printf("Cliente não encontrado.\n");
	return ClienteEncontrado;
}

// Função de cadastrar os pets
Animal* cadastrarPet(Animal *MeusAnimais, int *tamanhoAnimais, Cliente *MeusClientes, int *tamanhoClientes) {
    char nomeAnimal[50], agressivo, escolhaClienteStr[50];
    int especie, especiePet, bugDaData = 0;
    Cliente *ClienteEscolhido;
    Animal meuPet;
    Data dataNascimento;

    while (1) {
    printf("Já possui cadastro de cliente? S para sim, N para não ou E para desistir: ");
    fgets(escolhaClienteStr, sizeof(escolhaClienteStr), stdin);
    escolhaClienteStr[strcspn(escolhaClienteStr, "\n")] = '\0';

    if (escolhaClienteStr[0] == 'S') {
        ClienteEscolhido = buscarClienteImprimir(MeusClientes, *tamanhoClientes, MeusAnimais, *tamanhoAnimais, 1);
        if (ClienteEscolhido != NULL) break;
            else continue;
    } else if (escolhaClienteStr[0] == 'N') {
        ClienteEscolhido = cadastrarCliente(MeusClientes, tamanhoClientes);
        break;
    } else if (escolhaClienteStr[0] == 'E') {
        return NULL;
    } else {
        printf("Escolha inválida. Digite S, N ou E.\n");
        continue;
    }
}

    do {
        printf("Nome do seu Pet: ");
        fgets(nomeAnimal, sizeof(nomeAnimal) / sizeof(char), stdin);
        nomeAnimal[strcspn(nomeAnimal, "\n")] = '\0';

        if (!nomeValido(nomeAnimal)) {
            printf("Nome inválido. Digite um nome válido.\n");
            continue;
        }
        break;
    } while (1);

    printf("Qual dessas opções é seu pet? \n");
    imprimirTabelaEspecies();

    do {
        printf("Digite o número da espécie de seu Pet: ");
        char opcao[2];
        fgets(opcao, sizeof(opcao) / sizeof(char), stdin);
        opcao[1] = '\0';
        especiePet = atoi(opcao);
        if (especiePet < 0 || especiePet >= sizeof(ESPECIES) / sizeof(ESPECIES[0])) {
            printf("Escolha inválida. Digite um número válido.\n");
            continue;
        }
        break;
    } while (1);

    do {
        char dataNascimentoStr[12];
        printf("Informe a data de nascimento do seu pet (DD MM AAAA): ");
        fgets(dataNascimentoStr, sizeof(dataNascimentoStr)/sizeof(char), stdin);
        if (bugDaData == 0) {
            bugDaData = 1;
            fgets(dataNascimentoStr, sizeof(dataNascimentoStr)/sizeof(char), stdin);
        }
        sscanf(dataNascimentoStr, "%2d %2d %d", &dataNascimento.dia, &dataNascimento.mes, &dataNascimento.ano);

        if (!validarData(dataNascimento.dia, dataNascimento.mes, dataNascimento.ano)) {
            printf("Data inválida. Por favor, informe uma data válida.\n");
        }

    } while (!validarData(dataNascimento.dia, dataNascimento.mes, dataNascimento.ano));

    do {
        printf("O seu Pet é agressivo? (S para sim, N para não): ");
        char agressivoStr[2];
        fgets(agressivoStr, sizeof(agressivoStr) / sizeof(char), stdin);
		
        if (agressivoStr[0] == 'S' || agressivoStr[0] == 'N') {
            meuPet.agressivo = agressivoStr[0];
            break;
        } else {
            printf("Escolha inválida. Digite S para sim ou N para não.\n");
            continue;
        }
    } while (1);

    meuPet.cliente = ClienteEscolhido;
    strcpy(meuPet.nomeAnimal, nomeAnimal);
    meuPet.especie = especiePet;
    meuPet.dataNascimento = dataNascimento;
    MeusAnimais[(*tamanhoAnimais)] = meuPet;
    (*tamanhoAnimais)++;
    return &MeusAnimais[(*tamanhoAnimais) - 1];
}

// Função para mostrar o serviço mais utilizado
void servicosMaisUtilizados(Servico servicos[], int numServicos) {
	int tipoServicoContagem[MAX_SERVICO]; // Ele vai pegar todos elementes do array e inicializar em zero, isso vai servir p poder ver com qual recorrencia os serviços são usados
	int maxQuantidade = 0;
    int tiposServicosMaisUtilizados[MAX_SERVICO];
    int contadorTiposServicos = 0;
        for (int i = 1; i < MAX_SERVICO; i++) {
        tipoServicoContagem[i] = 0;
    }
        for (int i = 1; i < MAX_SERVICO; i++) {
        tiposServicosMaisUtilizados[i] = 0;
    }
		for (int i = 1; i < numServicos; i++) {
			tipoServicoContagem[servicos[i].tipoServico]++; //vai pegar o tipo de serviço e acrescentar +1 sempre que o serviço for escolhido
    	}

		for (int i = 1; i < MAX_SERVICO; i++) { //percorre todos os tipos de serviço possíveis começando do índice 0 até MAX_SERVICO
		    if (tipoServicoContagem[i] > maxQuantidade) { // verifica se a contagem de ocorrências do serviço[i] é maior que a contagem máxima, se for atualiza as variáveis 
		        maxQuantidade = tipoServicoContagem[i];
		        contadorTiposServicos = i; //ele redefini p 1 pq um novo máximo foi encontrado
		        tiposServicosMaisUtilizados[0] = i;
		    } else if (tipoServicoContagem[i] == maxQuantidade) {
		        tipoServicoContagem[contadorTiposServicos] = i; //aqui se dois serviços forem utilizados c a msm frequencia, vai exibir os dois, basicamente vai apontar o proximo na outra posição
		        contadorTiposServicos++;
		    }
		}
		
		printf("Tipos de serviços mais utilizados (com %d ocorrências):\n", tipoServicoContagem[contadorTiposServicos]);
        printf("Tipo de Serviço %d\n", contadorTiposServicos); //vai imprimir qual o serviço mais utilizado
}

void listarContasNaoPagas(Servico servicos[], int numContas) {
    printf("Contas Pendentes:\n"); 
    for (int i = 0; i < numContas; i++) {
        // Vai percorrer todo o loop e exibirá uma lista de contas pendentes de pagamento
        if (servicos[i].pago == 'N') {
            printf("%d. Conta %d - Não paga\n", i + 1, servicos[i].identificador);
        }
	}
}
void pagarConta(Servico servicos[], int numContas) {
char entrada[51];

    if (numContas == 0) {
        printf("Não há contas pendentes.\n");
        return;
    }
	
   listarContasNaoPagas(servicos, numContas);
    printf("Escolha o número da conta que deseja verificar (1 a %d): ", numContas);
    int escolha;
    fgets(entrada, sizeof(entrada)/sizeof(char), stdin);
    sscanf(entrada, "%d", &escolha);

    if (escolha >= 1 && escolha <= numContas) {
        printf("A Conta %d não foi paga. Deseja pagar agora? (S/N): ", servicos[escolha - 1].identificador);
    
        char resposta;
        fgets(entrada, sizeof(entrada)/sizeof(char), stdin);
        sscanf(entrada, "%c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            printf("Você pagou a Conta %d.\n", servicos[escolha - 1].identificador);
            servicos[escolha - 1].pago = 'S';
        } else {
            printf("A Conta %d não foi paga.\n", servicos[escolha - 1].identificador);
        }
    } else {
        printf("Escolha inválida.\n");
    }
}

void comprarServicos(Animal *MeusAnimais, int *tamanhoAnimais, Servico *novoServico, Cliente *MeusClientes, int *tamanhoClientes, int *tamanhoServicos) { //exibe todos os serviços
char entrada[51];
int opcaoServico;
Data data;
Animal* meuAnimal;

    printf("\nMenu de Serviços:\n");
    printf("1. BANHO - R$40,00\n");
    printf("2. TOSA  - R$65,00\n");
    printf("3. VACINA - R$120,00\n");
    printf("Selecione o serviço desejado (1-3): ");

int obterOpcaoServico() { //recebe do cliente a opção do serviço
    int opcao;
    fgets(entrada, sizeof(entrada)/sizeof(char), stdin);
    opcao = atoi (entrada);
    while (opcao < 1 || opcao > MAX_SERVICO) {
        printf("Opção inválida. Selecione o serviço desejado (1-3): ");
        fgets(entrada, sizeof(entrada)/sizeof(char), stdin);
        opcao = atoi (entrada);
    }
    return opcao;
}

Data obterData() { //Recebe e verifica a data do serviço
    Data data;
    do {
        printf("Informe a data do serviço (DD MM AAAA): ");
        fgets(entrada, sizeof(entrada)/sizeof(char), stdin);
        sscanf(entrada, "%2d %2d %d", &data.dia, &data.mes, &data.ano);

        if (!validarData(data.dia, data.mes, data.ano)) {
            printf("Data inválida. Por favor, informe uma data válida.\n");
        }

    } while (!validarData(data.dia, data.mes, data.ano));
	
    return data;
}


Animal* buscarPet() {//aqui ele vai percorrer o loop de pets para ver se o pet está cadastrado
    do {
    printf("Você já cadastrou um pet? 's' para sim e 'n' para não: ");
    fgets(entrada, sizeof(entrada)/sizeof(char), stdin);
    } while(!((entrada[0] == 'n')||(entrada[0] == 's')));
    
    if (entrada[0] == 's') {
        do {
        printf("Digite o nome do seu pet: ");
        fgets(entrada, sizeof(entrada)/sizeof(char), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
        for (int i = 0; i < *tamanhoAnimais; i++) {
            if (strcmp(MeusAnimais[i].nomeAnimal, entrada) == 0) {
                return &MeusAnimais[i];
            }
        }
        continue;  // se não achar pet vai retornar 0
        } while(1);
    } else if (entrada[0] == 'n')
        return cadastrarPet(MeusAnimais, tamanhoAnimais, MeusClientes, tamanhoClientes);
}

void registrarServico(Animal *pet, int tipoServico, Data data) { // armazenar todos os valores informados ao serviço escolhido
    	novoServico[*tamanhoServicos].pet = pet; //aqui ele armazena o ponteiro para o animal no serviço
    	novoServico[*tamanhoServicos].tipoServico = tipoServico; //armazena o tipo de serviço escolhido
    	novoServico[*tamanhoServicos].pago = 'N'; //define pago como Não
    	novoServico[*tamanhoServicos].dataServico = data; //armazena a data ao serviço escolhido
    	novoServico[*tamanhoServicos].identificador = *tamanhoServicos;
    	(*tamanhoServicos)++;
	}
	opcaoServico = obterOpcaoServico();
	data = obterData();
	meuAnimal = buscarPet();
	registrarServico(meuAnimal, opcaoServico, data);
	printf("Serviço registrado com sucesso, número da conta: %d\n", *tamanhoServicos - 1);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
	char in[51]; // Variavel que guarda a entrada do Usuario no console | maior entrada valida e de 50, precisamos +1 pelo \n que fgets() pega
	int tamanhos[] = {1,1,0}; // Quantidade de entradas por vetor ordem: MeusClientes, MeusAnimais
	Cliente MeusClientes[100]; // Inicializacao dos vetores
	Animal MeusAnimais[100];
	Servico MeuServicos[100];
	Data data;
	data.dia = 27;
	data.mes = 11;
	data.ano = 2023;
	MeuServicos[0].pago = 'T';
	strcpy(MeusAnimais[0].nomeAnimal,"Amigo");
	MeusAnimais[0].dataNascimento = data;
	MeusAnimais[0].especie = 1;
	strcpy(MeusClientes[0].nomeCliente, "felipe");
	strcpy(MeusClientes[0].telefoneCliente, "043984851658");
	MeusAnimais[0].cliente = &MeusClientes[0];
	//strcpy(MeusAnimais[0].cliente->telefoneCliente, "012341235623");
	MeusAnimais[0].agressivo = 'S';
	printf("   _______   \n");
        printf("  //     \\\\\n");
        printf(" //       \\\\            SEJA BEM VINDO!\n");
        printf("//_________\\\\              __________\n");      
        printf("|    _    |  |            | PET SHOP |\n");
        printf("|[] | | []|[]|    <-----  |   DO     |\n");
        printf("|   | |   |  |            | GABARITO |\n");

	printf(INICIO);
	while (strcmp(fgets(in,50,stdin), "e\n")!= 0) { // Enquanto o que se lee, nao for 'e', continuemos leendo os comandos..
		switch(in[0]) { // Controle de menus
			case '1' : // Menu de Cadastros
			    printf(MENU_CADASTRO);
				while (strcmp(fgets(in,50,stdin), "e\n")!= 0) {
					switch(in[0]) {
						case 'c' : // Cadastro Cliente
							do {
								cadastrarCliente(MeusClientes,&tamanhos[0]); // Funcao cadastro cliente
								printf("Cliente cadastrado com sucesso! deseja cadastrar outro cliente? 's' para sim ou 'n' para não: ");
								do { // Enquanto a resposta nao for valida, continue lendo
									fgets(in,50,stdin); 
								} while (!((in[0] == 'n') || (in[0] == 's')));
								if (in[0] == 'n') break; // Se a resposta for Nao, pare de cadastrar, se nao, continue
							} while(1);
							break;
						case 'p' : // Cadastro Pet
							do {
								cadastrarPet(MeusAnimais, &tamanhos[1], MeusClientes,&tamanhos[0]);
								printf("Pet cadastrado com sucesso! deseja cadastrar outro pet? 's' para sim ou 'n' para não: ");
								do {	
									fgets(in,50,stdin);
								} while (!((in[0] == 'n') || (in[0] == 's')));
								if (in[0] == 'n' || in[0] == 'N') break;
							} while(1);
					}
					printf(MENU_CADASTRO);
				}
				break;
			case '2' : // Menu de Servicos
					printf(MENU_SERVICOS);
				while (strcmp(fgets(in,50,stdin), "e\n")!= 0) {
					switch(in[0]) {
						case 'p' : // Pagar Conta
							do {
								pagarConta(MeuServicos, tamanhos[2]);
								printf("Deseja realizar o pagamento de outra conta? 's' para sim ou'n' para não: ");	
								do{
									fgets(in,50,stdin);
								} while (!((in[0] == 'n') || (in[0] == 's')));
								if (in[0] == 'n' || in[0] == 'N') break;
							} while(1);
							break;
						case 'o' : // Comprar Servico
							do {
								comprarServicos(MeusAnimais, &tamanhos[1], MeuServicos, MeusClientes, &tamanhos[0], &tamanhos[2]);
								printf("Deseja comprar outro serviço? 's' para sim ou'n' para não: ");
								do{
									fgets(in,50,stdin);
								} while (!((in[0] == 'n') || (in[0] == 's')));
								if (in[0] == 'n' || in[0] == 'N') break;
							} while(1);
							break;
					}
					printf(MENU_SERVICOS);
				}
				break;
			case '3' : // Menu de listagem
					printf(MENU_LISTAGEM);
				while (strcmp(fgets(in,50,stdin), "e\n")!= 0) {
					switch(in[0]) {
						case '1' : // Buscar Cliente pelo Nome
							do {
								buscarClienteImprimir(MeusClientes, tamanhos[0], MeusAnimais, tamanhos[1], 0);
								printf("Deseja buscar outro cliente? \n");
								do {	
									fgets(in,50,stdin);
								} while (!((in[0] == 'n') || (in[0] == 's')));
								if (in[0] == 'n' || in[0] == 'N') break;
							} while(1);
							break;
						case '2' : // Buscar Animal pelo Nome
							do {
								    printf("Informe o nome do pet: ");
									fgets(in,50,stdin);
									in[strcspn(in,"\n")] = '\0';
									printf("%s\n",baseadoEmNomePet(in,MeusAnimais,tamanhos[1]));
									{
										printf("'c' para imprimir novamente, 'e' para sair.\nDigite aqui: ");
										fgets(in,50,stdin);
									} while (!(in[0] == 'e' || in[0] == 'c'));
								} while (in[0] == 'c');
							break;
						case '3' : // Listar Animais
							sortAnimais(MeusAnimais,tamanhos[1]); // Organizar os Animais Alfabeticamente
							printf("%s\n\nEnter para voltar", imprimirAnimais(MeusAnimais,&tamanhos[1])); // Imprimir a Tabela dos Animais
							fgets(in, 51, stdin);
							break;
						case '4' : // Quantidade de Animais Agressivos
							printf("%s\n\nEnter para voltar", qntdAnimaisAgressivos(MeusAnimais, tamanhos[1]));
							fgets(in, 51, stdin);
							break;
						case '5' : // Listar Animais Separados Por Especie
							printf("%s\n\nEnter para voltar", imprimirTabelaAnimaisPorEspecie(MeusAnimais,&tamanhos[1]));
							fgets(in, 51, stdin);
							break;
						case '6' : // Listar Animais Aniversariantes
							printf("%s\n\nEnter para voltar", imprimirAnimaisAniversariantes(MeusAnimais,&tamanhos[1]));
							fgets(in, 51, stdin);
							break;
						case '7' : // Listar Servicos nao pagos
							listarContasNaoPagas(MeuServicos, tamanhos[2]);
							printf("\n\nEnter para voltar");
							fgets(in, 51, stdin);
							break;
						case '8' : // Listar Sevico mais Utilizado
							servicosMaisUtilizados(MeuServicos, tamanhos[2]);
							printf("\n\nEnter para voltar");
							fgets(in, 51, stdin);
							break;
						case '9':
						        printf("%c %d", MeuServicos[0].pago, tamanhos[2]);
							printf("\n\nEnter para voltar");
							fgets(in, 51, stdin);
						        break;
					}
					printf(MENU_LISTAGEM);
				}
				break;
			case 'h' : // Menu de comandos
				printf(MENU_DE_COMANDOS);
				break;
			case 'l' : // Commando limpar o console
				system("clear");
				break;
  		}
		printf(INICIO);
	}
  	return 0;
}
