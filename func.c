#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct datanode{
	char nome[30];
	int senha;
	int saldo;
}DataNode;

typedef struct node{
	DataNode data;
	struct node *next;	
 }Node;
 
typedef struct list{
	int size;
	Node *head;
}List;

short validaStr(List *l,char *str);
short existe(List *l,char *str);
DataNode *atPos(List *l,int index);
short  indexOf(List *l,char *str);

List * criaList(void){
	List *lista = (List *) malloc(sizeof(List *));
	
	lista->size = 0;
	lista->head = NULL;
	return lista;
}

void adiciona(List *l,DataNode d){
	Node *n = (Node*) malloc(sizeof(Node));
	
	n->data = d;
	n->next = l->head;
	l->head = n;
	
	l->size++;
}

DataNode preencheDado(List *l){
	DataNode  d;
	l1:
	printf("Nome do cliente:");
	scanf("%s",d.nome);
	if(validaStr(l,d.nome)==0){
		puts("\033[31mErro : nome nao devem conter numeros\033[m");
		goto l1;
	}
	if(existe(l,d.nome)==0){
		puts("\033[31mErro : usuario ja foi registado\033[m");
		goto l1;
	}
	l2:
	printf("Senha do cliente:");
	scanf("%d",&d.senha);
	if(d.senha < 1000) {
		puts("\033[31mErro : senha deve conter 4 ou mais digitos\033[m");
		goto l2;
	}
	printf("Saldo do cliente:");
	scanf("%d",&d.saldo);
	
	return d;
}

short validaStr(List *l,char *str){
	for(int i=0;str[i] != '\0';i++){
		if(isdigit(str[i])) return 0;
	}
	return 1;
}

short existe(List *l,char *str){
	Node *n = l->head;
	while(n != NULL){
		if(strcasecmp(n->data.nome,str) == 0)	return 0;
		n = n->next;
	}
	return 1;
}


DataNode *atPos(List *l,int index){
	if(index >= 0 && index < l->size){
		Node *no = l->head;
		
		for(int i=0;i<index;i++)
			no = no->next;
		
		return &no->data;
	}
	
	return NULL;
}

short indexOf(List *l,char *str){
	Node *n = l->head;
	int ind =0;
	while(n != NULL){
		if(strcasecmp(n->data.nome,str) == 0)	return ind;
		n = n->next;
		ind ++;
	}
	return -1;
}

short  login(List *l,char nome[],int senha){
	if(existe(l, nome) == 1){
		int ind = indexOf(l, nome);
		if(ind == -1){
			printf("\033[31Erro : usuario inexistente\033[m");
			return -1;
		}
		DataNode *d=atPos(l, ind);
		if(d->senha != senha){
			printf("\033[31Erro : senha incorrecta\033[m");
			return -1;
		}
		printf("Usuario logado com sucesso\n");
		return 0;
	}
	printf("\033[31Erro : usuario inexistente\033[m");
	return -1;
}

int saldo(List *l,char nome[]){
	if(existe(l, nome) == 0){
		int ind = indexOf(l, nome);
		if(ind == -1){
			printf("\033[31Erro : usuario inexistente\033[m");
			return -1;
		}
		DataNode *d=atPos(l, ind);
		return d->saldo;
	}
	printf("\033[31mErro : usuario inexistente\033[m\n");
	return -1;
}

short depo(List *l,char nome[],int qnt){
	DataNode *d = atPos(l, indexOf(l, nome));
	if(d == NULL) return 1;
	d->saldo += qnt;
	return 0;
}

short leva(List *l,char nome[],int qnt){
	DataNode *d = atPos(l, indexOf(l, nome));
	if(d == NULL) return -1;
	if(d->saldo - qnt < 0){
		return -1;
	}
	d->saldo -= qnt;
	return 1;
}

short trans(List *l,char de[],char para[],int qnt){
	if(leva(l, de, qnt) == 1){
		if(depo(l, para, qnt) == 1) return 1;
	}
	else return 0;
	return -1;
}

void mudaSenha(List *l,char nome[],int nova){
	if(existe(l, nome) ==0){
		DataNode *no = atPos(l, indexOf(l, nome));
		no->senha = nova;
	}
}
