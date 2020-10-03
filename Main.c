#include "func.c"
#include <stdio.h>

int menu(void);
int vazia(List *l);

int main(){
	printf("Banco em C\n");
	int m,s1;
	char nome[30],nome2[30];
	List *l = criaList();
	do{
		m = menu();
		if(m == 0) {
			exit(1);
		}
		else if(m == 1)adiciona(l, preencheDado(l));
		if(vazia(l) == 1) continue;
		else if(m == 2){
			c1:
			printf("Digite o nome do cliente:");
			scanf("%s",nome);
			if(validaStr(l, nome) == 0){
				printf("\033[31mErro : nome invalido\033[m\n");
				goto c1;
			}
			s1 = saldo(l, nome);
			if(s1 == -1) continue;
			printf("Saldo do cliente %s e de %d\n",nome,s1);
		}
		else if(m == 3){
			c2:
			printf("Digite o nome do cliente:");
			scanf("%s",nome);
			if(validaStr(l, nome) == 0){
				printf("\033[31mErro : nome invalido\033[m\n");
				goto c2;
			}
			if(saldo(l, nome) ==-1)continue;
			printf("Quantia a depositar:");
			scanf("%d",&s1);
			depo(l,nome,s1);
			printf("Quantia depositada com sucesso\n");
		}
		else if(m == 4){
			l2:
			printf("Digite o nome do cliente:");
			scanf("%s",nome);
			if(validaStr(l, nome) == 0){
				printf("\033[31mErro : nome invalido\033[m\n");
				goto l2;
			}
			if(saldo(l, nome) ==-1)continue;
			printf("Quantia a levantar:");
			scanf("%d",&s1);
			if(leva(l,nome,s1) == 1)
			printf("Quantia levantada com sucesso\n");
			else
			printf("\033[31mErro : saldo insuficiente\n\033[m");
		}
		else if(m == 5 && l->size >= 1){
			t1:
			printf("Transferir de :");
			scanf("%s",nome);
			if(validaStr(l, nome) == 0){
				printf("\033[31mErro : nome invalido\033[m\n");
				goto t1;
			}
			t2:
			printf("Transferir para:");
			scanf("%s",nome2);
			if(validaStr(l, nome2) == 0){
				printf("\033[31mErro : nome invalido\033[m\n");
				goto t2;
			}
			printf("Quantia a transferir:");
			scanf("%d",&s1);
			if(trans(l, nome, nome2, s1) == 0){
				puts("\033[31mErro : saldo insuficiente\033[m" );
				continue;
			}
			else
				printf("Transferencia efetuada com sucesso\n");
		}
	}while(m >= 0);
}

int menu(void){
	int op;
	printf("Menu do banco\n");
	c1:
	puts("0 - para sair");
	puts("1 - para adicionar");
	puts("2 - para consultar o saldo");
	puts("3 - para depositar");
	puts("4 - para levantar");
	puts("5 - para transferir");
	printf("Sua opcao:");
	scanf("%d",&op);
	if(op < 0 || op > 5){
		  printf("\033[31mErro : opcao invalida \033[m\n");
		  goto c1;
	}
	return op;
}

int vazia(List *l){
	if(l->size == 0){
		puts("\033[31mErro : nenhum cliente registado\033[m");
		return 1;
	}
	return 0;
}
