#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"backerysys.h"
#include"prog2Utils.h"// Biblioteca de funções auxiliares. Por exemplo editar informações de arquivos.
#define MAX 300 // Quantidade maxima de vendas que podem ser salvas por dia

// Extruturas do programa

// Clientes
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
	char date[10];
	int id;
	clients cliente;
	product produto[300];
 	int amount;
 	float value;
};
typedef struct sales sales;

// Main program
int main(){
	setlocale(LC_ALL, "Portuguese");	
	sales vendas[300];

	int quantidade = 0;
	int opcao = 1;
	do{
		puts("Padaria da dona Joana");
		opcao = readOption();
		switch (opcao){
			case 1: // 1 - Registra um novo cliente

				// Se o arquivo não existir, gera um novo arquivo
				if(!verifyFile(":cliente.txt")){ 
					newFile(":cliente.txt","w");
					newClient();
				}// Executa a função
				else {
					newClient();
				}
			break;
    
			case 2: // 2- Registra um novo produto
				// Se o arquivo não existir, gera um novo arquivo
				if(!verifyFile(":produto.txt")){ 
					newFile(":produto.txt","w");
					newProduct();
				}// Executa a função
				else {
					newProduct();
				}
			break;
    
			case 3: // 3- Atualiza um produto
				updateFile();
			break;
                 
			case 4:  // 4- Venda
				// Se o arquivo não existir, gera um novo arquivo
				if(!verifyFile(":cliente.txt")){ 
					newFile(":cliente.txt","w");
					sell(vendas);
				}// Executa a função
				else {
					sell(vendas);
				}
			break;
                 
			case 5:  // 5- Listar Clientes/Devedores
				verifyDebt(":cliente.txt");
			break;
           
			case 6:  // 6- Listar vendas feitas na data
				listSales();
			break;
               
			case 7:  // 7- Fechar o caixa
				saveSales(vendas);
				exit(0);
			break;
    
			default:
				printf("Opcao invalida, tente novamente.\n");
			break;
                          
		}
		printf("Digite [0] para sair ou digite [1] para voltar ao inicio!");
		scanf("%d", &opcao);
	}while (opcao > 0);

	return 0;
}