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

const char ESPECIES[][14] = {"Cachorro","Gato","Hamster","Pássaro", "Coelho"};

// Configuracao Tabela de Especies
char tabelaEspecies[][]                      = {"#","Especie"};
int confTabelaEspecies[]                     = {3,2,14} ;// Primeiro Valor tamanho do Vetor

// Configuracao Tabela de Pesquisa por Clientes
char tabelaPesquisaClientesNomeColunas[][]   = {"#","Nome"};
int confTabelaPesquisaClientes[]             = {3,2,14};

// Configuracao Tabela de Animais Aggressivos
char tabelaAnimaisAggressivosNomeColunas[][] = {"Quantidade"}; // O nome das colunas quando tabeladas
int confTabelaAnimaisAggressivos[]           = {2,13}; // Representa Tamanho de cada coluna em ordem, o primeiro valor e o tamanho do Vetor

// Configuracao Tabela Animais Completa
char tabelaAnimaisNomeColunas[][]            = {"Nome", "Especie", "Agressivo", "Data de Nascimento", "Nome do Cliente", "Telefone"};
int confTabelaAnimais[]                      = {7,14,12,20,13,14}; 
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
char *stringDinamica(int tamanho) return (char*) malloc(tamanho*sizeof(char));

char *aumentarTamString(char *string, int tamanho) return (char*) realloc(string,tamanho*sizeof(char)); //funcao que aumenta tamanho de string dinamico

//funcao que cria um vetor de inteiros de tamnaho dinamico
int *vetorIntDinamico(int tamanho) return (int*) malloc(tamanho*sizeof(int));

int *aumentarVetorInt(int *vetor, int tamanho) return (int*) realloc(vetor,tamanho*sizeof(int)); //funcao que aumenta tamanho de vetor inteiro dinamico

// funcao que transforma uma string de minuscula para maiuscula
char *toupper(char in[], int tamanho) {
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

//função que transforma um numero inteiro positivo em um char
char *posIntToChar(int in) {
  	int i = 1+(int) log10(in); // Olha quantidade de numeros
  	int mx = i; // Quantidade maxima de numeros
 	char *myChar = definirStringDinamica(i+2); // Criar string com tamanho de Numeros+2
	while(i >= 1) {
      		int toInt = in/pow(10,i-1); // Dividir para ficar so um numero positivo com o resto em virgulas
      		myChar[mx-i] = 48+toInt; // Colocar a letra do numero na string
      		in -= toInt*pow(10,i-1); // Tirar o numero ja colocado do numero composto
      		i--;
  	}
  	myChar[mx] = '\0'; // colocar o byte nulo no fim da string
  	return myChar;
}

//função que transforma uma data em string e retorna ela
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
	out[10] = '\0';
	return out;
}

//função que anexa retorna uma fileira de tabela baseada nas configuracoes de coluna e coluna tamanho, pode ser primeira fileira ou nao
char *anexarFileira(char **colunas, int confTabela[], int PrimeiraFileira) {
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
    	}
	void anexarColuna(char *valor, int coluna) myStrCpy(minhaImpressao, valor, &cursor, confTabela[coluna], ((i == 0) ? 2 : 3); // Se for primeira linha quero linha de coluna antes tambem
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

"Affonso"
"fo"

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

//função que cria a configuracao de coluna da tabela de especies dada o numero inteiro da especie
char **criarColunaEspecies(int numero) {
	char coluna[][] = {     atoi(numero),
				ESPECIES[numero]};
	return coluna;
}

//função que ele imprime a tabela de todas as especies com o numero associado
void imprimirTabelaEspecies() {
	int quantidadeEspecies = sizeof(ESPECIES) / sizeof(int);
	printf("%s",annexarFileira(tabelaEspecies,confTabelaEspecies,1));
	for (int i = 0; i < quantidadeEspecies; i++) {
		printf("%s",annexarFileira(criarColunaEspecies(i),confTabelaEspecies,2));
	}
}

//função que cria configuracao da fileira de impressao de tabela de Cliente com o numero associado // usada na busca de clientes cadastrados
char **criarColunaPesquisaClientes(Cliente oC, int numero) { //oC O Cliente
	char coluna[][] = {     posIntToChar(numero),
	                        oC.nomeCliente};
	return coluna;
}

//função que organiza os clientes alfabeticamente, depois ele procura por clientes que foram pesquisados por string termo, e faz a tabela com eles // se o termo for vazio quer dizer que é pra imprimir tudo
int *mapaListagemClientesPorPesquisa(Cliente *Clientes, int tamanho, char[] termo) {
	sortClientes(Clientes, tamanho); // Organizar os clientes em ordem alfabetica pra ficar mais bonitinho
	int meuVetor[101],
	    i = 1
	    tamanhoTabela;
	char minhaTabela[1000];
	strcpy(minhaTabela, anexarFileira(tabelaPesquisaClientesNomeColuna,confPesquisaClientes,1)); // Colocar primeira fileira na tabela
	for (int j = 0; j < tamanho; j++) {
		if (find(Clientes[j].nomeCliente, termo) == 1) { // Se eu encontrar baseado no conceito da pesquisa:
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

//função retorna a tabela de quantidade de animais agressivos para ser impresso
char *qntdAnimaisAgressivos(Animal *MeusAnimais, int quantidadeDeAnimais) {
	int contagem = 0,
	    tamanhoPrimeiraFileira; // Se refere a posicao no string da primeira fileira, pra escrever a partir dela na segunda
	char impressao[400],
	     confColunaComQuantidadeDeAgressivos[1][4];
	     primeiraFileira*; // nn sei se pode
	     fileiraDeConteudo*;
	for (int i = 0; i < quantidadeDeAnimais; i++) {
  		if (MeusAnimais[i].agressivo  == 'S') contagem++;
  	}
	strcpy(colunaComQuantidadeDeAgressivos[0],posIntToChar(contagem)); // Montar a coluna com o numero de Aggressivos
	strcpy(primeiraFileira, anexarFileira(tabelaAnimaisAggressivosNomeColunas,confTabelaAnimaisAggressivos,1));
	strcpy(fileiraDeConteudo, anexarFileira(colunaComQuantidadeDeAgressivos,confTabelaAnimaisAggressivos,0));
	tamanhoPrimeiraFileira = strlen(primeiraFileira);
	strcpy(impressao, primeiraFileira);
	myStrCpy(impressao, fileiraDeConteudo, &tamanhoPrimeiraFileira, strlen(fileiraConteudo),0);
	return impressao;
}

// funcao que retorna a configuracao de uma coluna de uma tabela de animais baseado em um animal especifico, essa conf e usada na funcao de impressao para criar uma fileira da tabela
char **criarColunaAnimais(Animal oA) {
	char coluna[][] = {     oA.nomeAnimal,
				ESPECIE[oA.especie],
				oA.agressivo,
				dataParaChar(oA.dataNascimento),
				oA.cliente->nomeCliente,
				oA.cliente->telefoneCliente};
	return coluna;
}

// função que retorna uma tabela de uma fileira com as caracteristicas do animal com o nome para ser impresso
char *baseadoEmNomePet (char *Nome, Animal *Pets, int tamanhoVetorAnimais){
	char impressao[1000];
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

// função que leva o tamanho do vetor animais, e o vetor | ele organiza alfabeticamente, e depois retorna uma tabela com todos os animais e suas caracteristicas para ser impresso
char *imprimirAnimais(Animal Animais[],int *tamanho) {
	int cursor = 0;
	char *minhaImpressao = stringDinamica(1);
	anexarFileira(tabelaAnimaisNomeColunas, confTabelaAnimais, 1);
    	for(int i = 0; i < (*tamanho); i++) {
		Animal oA = Animais[i];// oA de O Animal
		anexarFileira(criarColunaAnimais(oA), confTabelaAnimais, 0);
	}
	return minhaImpressao;
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
	
//Função de validar Datas
int ValidarData(int dia, int mes, int ano) {
    // Verifica se o dia está entre 1 e 21 (utilizei 21 pois temos a regra de não permitir datas futuras)
    if ((dia < 1 && dia > DIA)) {
        return 0; // Inválido
    }

    // Verifica se o mês está entre 1 e 11  (utilizei 11 pois temos a regra de não permitir datas futuras)
    if (mes < 1 && mes > MES) {
        return 0; // Inválido
    }

    // Verifica se o ano é maior ou igual a 1900 (mínimo) ou 2023 (atual)
    if (ano < 1977 && ano > ANO) { 
        return 0; // Inválido
    }

    // Se todas as verificações passarem, a data é válida
    return 1;
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
        printf("Nome inválido, E para desistir, qualquer coisa pra continuar.\n");
        fgets(nomeCliente, sizeof(nomeCliente) / sizeof(char), stdin);
        nomeCliente[strcspn(nomeCliente, "\n")] = '\0';
		
	// Caso o usuário desista de inserir, ele pode pressionar E ou e para desistir
        if (nomeCliente[0] == 'E' || nomeCliente[0] == 'e') return 0;

        // Continue para a próxima iteração do loop para que o usuário insira o nome novamente
        continue;
    } else break;
 }

do {
    // Recebe o telefone do cliente e armazena dentro do char
    printf("Telefone do cliente: ");
    fgets(telefoneCliente, sizeof(telefoneCliente) / sizeof(char), stdin);
    telefoneCliente[strcspn(telefoneCliente, "\n")] = '\0';

    // irá realizar a validação do telefone
    if (!ValidarTelefone(telefoneCliente)) {
        printf("Telefone inválido, E para desistir, qualquer coisa pra continuar.\n");
        fgets(telefoneCliente, sizeof(telefoneCliente)/sizeof(char), stdin);
        telefoneCliente[strcspn(telefoneCliente, "\n")] = '\0';

        // Caso o usuário desista de inserir, ele pode pressionar E ou e para desistir
	if (telefoneCliente[0] == 'E' || telefoneCliente[0] == 'e') return 0;

        // Continue para a próxima iteração do loop para que o usuário insira o telefone novamente
        continue;
    } else break;
}

strcpy(meusClientes[(*tamanho)].nomeCliente, nomeCliente);
strcpy(meusClientes[(*tamanho)].telefoneCliente, telefoneCliente);
(*tamanhoClientes)++; 
return &meusClientes[(*tamanho)-1];
}

// Função de cadastrar os pets
int cadastrarPet(Animal *MeusAnimais, int *tamanhoAnimais, Cliente *MeusClientes, int *tamanhoClientes) {
	char nomeAnimal[50], agressivo, escolhaClienteStr[50];
	int especie, diaNascimento, mesNascimento, anoNascimento;
	Cliente *ClienteEscolhido;
	Animal meuPet;
	int especiePet;	
    Data dataNascimento;
   
	while (1) {
		printf("Já possui cadastro? S para sim, N para não ou E para desistir: "); //Usuario irá informar se ele possui cadastro para cadastrar um pet
    	fgets(escolhaClienteStr, sizeof(escolhaClienteStr)/sizeof(char), stdin);
		escolherClientesStr = toupper(escolherClientesStr, 50); //transformar em uppercase p facilitar a verificação
    	if (escolherClienteStr[0] == 'S') {
            // Chama a função que retorna um vetor para listar os clientes
			printf("Termo de Pesquisa: ");
    		fgets(escolhaClienteStr, sizeof(escolhaClienteStr)/sizeof(char), stdin);
            int *clientesEncontrados = mapaListagemClientesPorPesquisa(MeusClientes, *tamanhoClientes, escolherClientesStr);

    		if (clientesEncontrados[0] > 0) {
			do {
    	            int numeroEscolhido; // Se houver clientes, o usuário vai escolher um número
    	            char numeroEscolhidoStr[5];
    	            printf("Digite o número correspondente ao cliente desejado: ");
    	            fgets(numeroEscolhidoStr, sizeof(numeroEscolhidoStr)/sizeof(char), stdin);
    	            numeroEscolhido = atoi(numeroEscolhidoStr);
    
    		        if (numeroEscolhido < 1 || numeroEscolhido > clientesEncontrados[0]) {
    	                printf("Escolha inválida. Digite um número válido.\n");
    	                continue;
                    } else {
                        ClienteEscolhido = &MeusClientes[clientesEncontrados[numeroEscolhido]]; //Essa parte vai atribuir o endereço de memória do cliente escolhido ao ponteiro ClienteEscolhido
                        break;
                    }
			}	while(1);
    		} else {
                printf("Nenhum cliente encontrado.\n");
                continue;
            }
        } else if (escolherClienteStr[0] == 'N') {
            // Se ele escolher N ele vai ser redirecionado pro cadastro
            ClienteEscolhido = cadastrarCliente(MeusClientes, tamanhoClientes);
    	} else if (escolhaClienteStr[0] == 'E') {
            // Se ele escolher E, desiste
            return -1;
	} else {
            printf("Escolha inválida. Digite S, N ou E.\n");
            continue; 
		}
	}
	// TRAVEI AQUI Ó -----------
		

	// Informar o nome do pet
    do {
        printf("Nome do seu Pet: ");
        fgets(nomeAnimal, sizeof(nomeAnimal)/sizeof(char), stdin);
        nomeAnimal[strcspn(nomeAnimal, "\n")] = '\0';
        // Validação do nome do pet
        if (!nomeValido(nomeAnimal)) {
            printf("Nome inválido. Digite um nome válido.\n");
            continue;
        }
        break;  
    } while (1); 


	// Informar a espécie do pet
	printf("Qual dessas opções é seu pet? \n");
    imprimirTabelaEspecies()

	// Essa parte vai receber qual é a espécie do pet e vai armazenar
	do {
        printf("Digite o número da espécie de seu Pet: ");
        char opcao[2];
        fgets(opcao, sizeof(opcao)/sizeof(char), stdin);
        especiePet = atoi(opcao);

		// Aqui vai verificar se a escolha da espécie é valida
        if (especiePet < 1 || especiePet > sizeof(ESPECIES)/sizeof(ESPECIES[0])) {
            printf("Escolha inválida. Digite um número válido.\n") 
		    continue;
        }
		break;
    } while (1);

	// Aqui é onde será definido a data de nascimento do pet e armazenada no struct data
	do {
        printf("Digite a data de nascimento do seu Pet: (DD/MM/AAAA): ");
        char dataNascimentoStr[12];
        fgets(dataNascimentoStr, sizeof(dataNascimentoStr)/sizeof(char), stdin); //Vai armazenar o valor

	int diaNascimento, mesNascimento, anoNascimento; //Aqui eu declarei cada variavel especifica p armazenar
	sscanf(dataNascimentoStr, "%d/%d/%d", &dataNascimento.dia, &dataNascimento.mes, &dataNascimento.ano); //usei o sscanf p poder analisar a string dataNascimentoStr, ai ele extrai os valores formatados com dia/mes/ano

	// Aqui vai fazer a verificação da data de nascimento
	if (ValidarData(dataNascimento.dia, dataNascimento.mes, dataNascimento.ano) == 0) {
            printf("Data de nascimento inválida. Digite novamente.\n");
            continue;
        }
    break;
    } while (1);

	// Aqui vai ser a parte pra ver se o pet é agressivo ou não
	do {
    	printf("O seu Pet é agressivo? (S para sim, N para não): "); 
    	char agressivoStr[2]; 
    	fgets(agressivoStr, sizeof(agressivoStr)/sizeof(char), stdin);
//Retirar o \n!!!!
		
	agressivoStr = toupper(agressivoStr, 2); // Transformar em uppercase p facilitar a verificação
    // Verificar se o usuário digitou S ou N, se S ou N, armazenar na struct Animal
    if (agressivoStr[0] == 'S' || agressivoStr[0] == 'N') {
        meuPet.agressivo = agressivoStr[0];
        break;
    } else {
        printf("Escolha inválida. Digite S para sim ou N para não.\n");
		continue;
    }
} while (1);
	meuPet.cliente = ClienteEscolhido;  //associando o pet ao cliente
	meuPet.nomeAnimal = nomeAnimal;
	meuPet.especie = especiePet;
	meuPet.dataNascimento = dataNascimento;
	meusAnimais[(*tamanhoAnimais)] = meuPet;
	(*tamanhoAnimais)++; 
	return 1;
}

// Função para buscar o cliente e imprimir os seus dados e do pet, se existir
void buscarClienteImprimir(Cliente *Clientes, int tamanhoClientes, Animal *MeusAnimais, int tamanhoAnimais) {
    char nomeBusca[50];
	int encontrei = 0;
	
	printf("Digite o nome do cliente que deseja procurar: ");
    fgets(nomeBusca, sizeof(nomeBusca)/sizeof(char), stdin); // Solicita uma entrada de nome para realizar a busca
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

	for (int i = 0; i < tamanhoClientes; i++) {
        if (strcmp(Clientes[i].nomeCliente, nomeBusca) == 0) { //Percorre o loop e vê se o cliente existe
            // Cliente encontrado, imprime os dados
            printf("\nDados do Cliente:\n");
            printf("Nome: %s\n", Clientes[i].nomeCliente);
            printf("Telefone: %s\n", Clientes[i].telefoneCliente);

 			printf("\nPets do Cliente:\n");
    for (int j = 0; j < tamanhoAnimais; j++) { // Percorre o loop de pet e vê se tem pet cadastrado
                if (MeusAnimais[j].cliente == &Clientes[i]) {
                    // Pet encontrado, imprime os dados
					encontrei = 1;
                    printf("Nome do Pet: %s\n", MeusAnimais[j].nomeAnimal);
                    printf("Espécie: %s\n", ESPECIES[MeusAnimais[j].especie]);
                    printf("Agressivo: %c\n", MeusAnimais[j].agressivo);
                    printf("Data de Nascimento: %02d/%02d/%04d\n", MeusAnimais[j].dataNascimento.dia, MeusAnimais[j].dataNascimento.mes, MeusAnimais[j].dataNascimento.ano);
                    printf("-------------------------\n");
					}
		}
			if (encontrei == 0) 
						printf("O cliente não possui pets."); 
            return; // Cliente encontrado e impresso, a função pode encerrar
        } 
    }
	printf("Cliente não encontrado.\n");
	continue;
}



///////////////

int main() {
	char[5] in; // Variavel que guarda a entrada do Usuario no console | maior entrada valida e de 50, precisamos +1 pelo \n que fgets() pega
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
			case 'b' : // Buscar cliente pelo nome e demonstrar dados

				break;
			case 's' : // Buscar pet pelo nome e demostrar dados
				do {
					fgets(in,50,stdin);
					in[strcspn(in,'\n')] = '\0';
					printf("%s\n",baseadoEmNomePet(in,MeusAnimais,tamanhos[1]));
					{
						printf("'c' para imprimir novamente, 'e' para sair.\nDigite aqui: ");
						fgets(in,50,stdin);
					} while (in[0] != 'e' || in[0] != 'c');
				} while (in[0] == 'c');
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
