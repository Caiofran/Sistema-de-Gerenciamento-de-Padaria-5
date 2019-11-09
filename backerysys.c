#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "prog2Utils.h"

// Structs do Programa
// Cliente
struct clients{
	int id;
	char name[51];
	char address[51];
	char phone[20];
	float debt;
};
typedef struct clients clients;

// Produto
struct product{
	int id;
	char name[31];
	float price;
	int amount;
};
typedef struct product product;

// Vendas
struct sales{
	int id;
	int idCliente;
	int dataVenda[3];
	int amount;
	float value;

};
typedef struct sales sales;

/* Função: newClient
 * ----------------
 * Identifica qual ação será executada
*/
int readOption(){
	// Recebe o valor referente a opção a ser executada
	int value = 0;
	// Imprime as opções disponiveis
	printf("____________Opções:____________\n");
	printf("[1] Cadastrar Cliente:_________\n");
	printf("[2] Cadastrar Produto:_________\n");
	printf("[3] Alterar Produto:___________\n");
	printf("[4] Realizar venda:____________\n");
	printf("[5] Listar Clientes/Devedores:_\n");
	printf("[6] Listar Vendas Feitas Hoje:_\n");
	printf("[7] Fechar Caixa:______________\n");
	printf("Opção: ");
	scanf("%d", &value);

	return value;
}

/* Função: newClient
 * ----------------
 * Registra um novo cliente no sistema
*/
void newClient(){
	clients cliente;
	// Recebendo as informações
	printf("Digite as informações do cliente: \n");
	printf("Digite o id do cliente: ");
	scanf("%d", &cliente.id);
	printf("Nome: ");
	getchar();
	fgets(cliente.name, sizeof(cliente.name), stdin);
	printf("Endereço: ");
	fgets(cliente.address, sizeof(cliente.address), stdin);
	printf("Telefone: ");
	fgets(cliente.phone, sizeof(cliente.phone), stdin);
	cliente.debt = 0.0;
	// Removendo a quebra de linha da string
	strtok(cliente.name, "\n");
	strtok(cliente.address, "\n");
	strtok(cliente.phone, "\n");
	// Verifica se as informações estão corretas
  printf("%d,%s,%s,%s,%.2f\n", cliente.id, cliente.name, cliente.address, cliente.phone, cliente.debt);
	// Escaneando o arquivo
	FILE *client = fopen(":cliente.txt", "r");
	if(client == NULL){
		printf("Arquivo não encontrado!");
		exit(0);
	}
	// Gravando as informações do cliente no arquivo
	client = fopen(":cliente.txt", "a");
	if(client == NULL){
		printf("Arquivo não encontrado!");
		exit(0);
	}
	fprintf(client,"%d,%s,%s,%s,%.2f\n", cliente.id, cliente.name, cliente.address, cliente.phone, cliente.debt);
	fclose(client);
}

/* Função newFile
 * --------------
 * Cria um novo arquivo ".txt"
 * fileName: Nome do arquivo
 * action: Comando de execução do arquivo
*/
void newFile(char fileName[], char action[]){
	FILE *myFile = fopen(fileName, action);
	if(myFile == NULL){
		printf("Arquivo não encontrado.");
		exit(0);
	}
}

/* Função: newProduct
 * ----------------
 * Registra um novo produto no sistema
*/
void newProduct(){
	
	product produto; // Variavel para produto
	// Recebendo as informações
	printf("Digite as informações do produto: \n");
	printf("Digite o id do produto: ");
	scanf("%d", &produto.id);
	printf("Nome: ");
	getchar();
	fgets(produto.name, 51, stdin);
	printf("Preço: ");
	scanf("%f", &produto.price);
	printf("Quantidade: ");
	scanf("%d", &produto.amount);
	// Remove a quebra de linha
	strtok(produto.name, "\n");	
	// Adicionando o produto no arquivo
	FILE *product = fopen(":produto.txt", "a");
	if(product == NULL){
		printf("Arquivo não encontrado!");
		exit(0);
	}
	fprintf(product,"%d,%s,%.2f,%d\n", produto.id, produto.name, produto.price, produto.amount);
	fclose(product);
}

/* Função: verifyFile
 * ----------------
 * Verifica se o arquivo existe
 * myFile: parametro que o nome do arquivo
*/
int verifyFile(char myFile[]){
	FILE *fileToVerify = fopen(myFile, "r");
	if(fileToVerify)
		return 1; 
	else
		return 0;
}

/* Função: updateFile
 * ----------------
 * Atualiza as informações do arquivo
*/
void updateFile(){

	FILE *fileToUpdate = fopen(":produto.txt", "r");
	if(fileToUpdate == NULL){
		printf("Arquivo não encontrado!");
		exit(0);
	}
	// Armazena as informações do produto a ser alterado
	product alter;
	char *token = calloc(2, sizeof(char));
	char *s = calloc(2, sizeof(char));
	// Lista todas as informações armazenadas no arquivo
	printf("Lista de produtos em estoque: \n");
	while (!feof(fileToUpdate)){
		char *line = calloc(100, sizeof(char));
		char *result;
		result = fgets(line, 100+1, fileToUpdate);
		if (result)
			token = strtok(result, s);
  	while( token != NULL ){
    	printf( "%s", token );
    	token = strtok(NULL, s);
  	}
  }
	printf("\n");
	s = ",";
	int position;
	int id;
	// Identifica o produto a ser alterado
	printf("digite o id do produto a ser alterado: ");
	scanf("%d", &id);
	// Identifica qual posição vai ser alterada
	printf("O deseja alterar: ");
	printf("[1] nome ");
	printf("[2] preço ");
	printf("[3] Quantidade: ");
	scanf("%d", &position);
	if(position == 1){
	// Muda o nome do produto
		printf("Digite o novo nome: ");
		getchar();
		fgets(alter.name, 100+1, stdin);
		strtok(alter.name, s);
		strtok(alter.name, "\n");
		editFile(":produto.txt", s, id, position, alter.name);
		fclose(fileToUpdate);
	}else if(position == 2){
	// Muda o preço do produto
		char *productPrice = calloc(10, sizeof(char));
		printf("Digite o novo preço: ");
		getchar();
		fgets(productPrice, 6, stdin);
		strtok(productPrice, s);
		strtok(productPrice, "\n");
		editFile(":produto.txt", s, id, position, productPrice);
		fclose(fileToUpdate);
	}else if(position == 3){
	// Atualiza o estoque do produto
		char productAmount[6];
		printf("Produto atualize o estoque: ");
		getchar();
		fgets(productAmount, 6, stdin);
		strtok(productAmount, s);
		strtok(productAmount, "\n");
		editFile(":produto.txt", s, id, position, productAmount);
		fclose(fileToUpdate);
	}else if(position < 1 || position > 3){
		printf("Opção invalida!");
		fclose(fileToUpdate);
		exit(0);
	}
}

/* Função: gerarPvf
 * ----------------
 * Cria o nome do arquivo que armazena todas as vendas ralizadas na data
 * fileName: parametro da variavel que será alterada
*/
void gerarPvf(char fileName[]){
	int dia, mes, ano;
	
	// Recebendo as informações de data do sistema
	getToday(&dia, &mes, &ano);
	
	// Convertendo data de inteiro para caractere
	char day[3], month[3], year[5];
	sprintf(day, "%d", dia);
	sprintf(month, "%d", mes);
	sprintf(year, "%d", ano);

	// Concatenando as informações para gerar o nome do arquivo
	strcat(fileName, ":");
	strcat(fileName, day);
	strcat(fileName, month);
	strcat(fileName, year);
	strcat(fileName, ".pvf");
	strtok(fileName, "\n");
}

/* Função: sell
 * ----------------
 * Realiza uma venda fiada ou avista
 * venda: parametro que recebe um vetor de extrutras
*/
void sell(sales *venda){
	#define MAX 300 // Valor máximo de vendas que podem ser realiazadas
	char day[3];
	char month[3];
	char year[5];
	char linha[200];
	int verifica;
	int tipoVenda;
	int idCliente;
	int dia = 0;
	int mes = 0;
	int ano = 0;
	// Recebendo as informações de data do sistema
	getToday(&dia, &mes, &ano);
	// Identificando quel tipo de venda deve ser realizada
	printf("Venda avista ou fiado? [1]Avista [0]Fiado: ");
	scanf("%d", &tipoVenda);
	sprintf(day, "%d", dia);
	sprintf(month, "%d", mes);
	sprintf(year, "%d", ano);
	if(!tipoVenda){
		printf("Cliente cadastrado? [1]Sim [0]Não: ");
		scanf("%d", &verifica);
		if(!verifica){
			newClient();
		}
		printf("Digite o código do cliente: ");
		scanf("%d", &idCliente);
	}	else if(tipoVenda){
		// Zero é o id usado para todos os clientes que compram a vista
		idCliente = 0;
	}
	// Escaneando o arquivo
	FILE *fp = fopen(":produto.txt","r");
	if(fp == NULL){
		printf("Arquivo não encontrado");
		exit(0);
	}
	int idVenda = 0;
	int indice = 0;
	for (int i = 0; i < 300; i++){	
		if (venda[i].id != 0 || venda[i].amount != 0){
			indice++;
		}
	}
	idVenda = indice + 1;
	venda[indice].id = idVenda;
	char strtmp[10];
	int i = 0;
	int idProduto;
	int quantidade;
	int codigo;
	int finalizar = 1;
	float precoVenda = 0.0;
	float troco = 0.0;
	float valorPago = 0.0;
	// Adicionando um produto a venda
	while(codigo != -1){ 
		// Aqui é lido o código do produto afim de adicioná-lo a venda
		printf("Codigo do produto [Digite -1 para sair]: ");
		scanf("%d", &codigo);
		float valor = 0.0;
		while(fscanf(fp, "%d,%*s,%f,%d", &idProduto, &valor, &quantidade) != EOF){
			if(idProduto == codigo){
				printf("%d,%.2f,%d\n", idProduto, valor, quantidade);
				// Soma o valor do produto a venda
				precoVenda += valor;
				quantidade--;
				printf("%d,%.2f,%d\n", idProduto, valor, quantidade);
			}
		}
	}
	// Armazenando as informações da venda
	sprintf(strtmp, "%d", quantidade);
	editFile(":produto.txt", ",", idProduto, 3, strtmp);
	venda[indice].dataVenda[0] = dia;
	venda[indice].dataVenda[1] = mes;
	venda[indice].dataVenda[2] = ano;
	char data[15];
	strcat(data, day);
	strcat(data, "/");
	strcat(data, month);
	strcat(data, "/");
	strcat(data, year);
	printf("Preço: %.2f\n", precoVenda );
	// Caso a venda seja fiada, o programa retornará ao main
	if(!tipoVenda){
		return;
	}
	// Caso seja a vista, receberá o valor pago pelo cliente e informará o troco que será dado a mesmo
	printf("Valor Pago: ");
	scanf("%f", &valorPago);
	troco = valorPago - precoVenda;
	printf("Troco: %.2f\n", troco);
	printf("Tecle 0 para sair: ");
	scanf("%d", &finalizar);

	fclose(fp);
}

/* Função: quitarDivida
 * ----------------
 * Diminui ou zera o saldo do cliente que pagar suas dividas
*/
void quitarDivida(){
	FILE *fp = fopen(":cliente.txt","r");
	if(fp == NULL){
		printf("Arquivo não encontrado!");
		exit(0);
	}

	char valorPagoChar[10];
	int id;
	int idValidacao;
	float debito;
	float pagamento = 0.0;
	float valorPago = 0.0;

	printf("Digite o id do cliente: ");
	scanf("%d", &idValidacao);
	printf("Digite o total a ser pago: ");
	scanf("%f", &pagamento);

	while(fscanf(fp,"%d,%*s,%*s,%*s,%f", &id, &debito) != EOF){
		if(idValidacao == id && debito > 0.0){
			valorPago = debito - pagamento;
			sprintf(valorPagoChar, "%.2f", valorPago);
			editFile(":cliete.txt", ",", idValidacao, 4, valorPagoChar);
		}
	}

	fclose(fp);
}

/* Função: listSales
 * ----------------
 * Lista todas as vendas realizadas na data
*/
void listSales(){

	char path[20];
	gerarPvf(path);

	char infoVenda[100];

	FILE *fpBin = fopen(path,"rb");
	fread(infoVenda, 100, 5, fpBin);

	while(fread(infoVenda, 100, 5, fpBin) != EOF){
		printf("%s\n", infoVenda);
	}
	
	fclose (fpBin);
}

/* Função: verifyDebt
 * ----------------
 * Lista todos os clientes que estão em debito ativo e realiza o pagamento da divida caso o cliente queira
 * path: parametro que recebe o caminho do arquivo de clientes
*/
void verifyDebt(char *path){
	FILE *fp = fopen(path,"r");
	if(fp == NULL){
		printf("Arquivo não encontrado!");
		exit(0);
	}
	char nome[25];
	int id = 0;
	float debito = 0.0;
	// Listando os devedores
	printf("Devedores: \n");
	while(fscanf(fp,"%d,%s,%*s,%*s,%f", &id, nome, &debito) != EOF){
		if(debito > 0.0){
			printf("id: %d | nome: %s | divida: %.2f", id, nome, debito);
		}
	}
	// Invocando a função quitarDivida
	int opcao;
	printf("Quitar divida? [1]Sim [0]Não: ");
	scanf("%d", &opcao);
	if(opcao){
		quitarDivida();
	}

	fclose(fp);
}

/* Função: saveSales
 * ----------------
 * Salva as vendas realizadas na data
 * salesDate: parametro que recebe um vetor de extruturas
*/
void saveSales(sales *salesDate){
	char path[20];
	// Criando um arquivo binário
	gerarPvf(path);
	FILE *fpBin = fopen(path,"wb");
	if(fpBin == NULL){
		printf("Arquivo não encontrado!");
		exit(0);
	}
	// Criando um vetor de strings e armazenando no arquivo
	char infoVenda[100];
  snprintf (infoVenda, 100,"%d %d %.2d/%.2d/%d", salesDate[0].idCliente, salesDate[0].amount, salesDate[0].dataVenda[0], salesDate[0].dataVenda[1], salesDate[0].dataVenda[2]);
  printf ("%s", infoVenda);
	fwrite(infoVenda, 100, 6, fpBin);
	fclose(fpBin);
}
