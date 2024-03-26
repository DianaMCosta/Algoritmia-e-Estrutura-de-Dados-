#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<conio.h>
#include <stdlib.h>


//ESTRUTURA QUE DEFINE O NÓ DA LISTA 
//CADA NÓ SÓ TEM ACESSO AO SEGUINTE 
typedef struct Node {
	int data;
	struct Node* next;
}NODE;

//ESTA DECLARAÇÃO PERMITE EM VEZ DE DECLARARMOS UMA LISTA COMO
// NODE* L PODERMOS DECLARAR COMO LIST L
typedef NODE* List;

// DECLARAÇÕES DE FUNÇÕES QUE VÃO SER DEFINIDAS POSTERIORMENTE
void printList(List L);
void deleteList(List L);
int sizeList(List L);
int countList(List l);

//MAIN
int main() {
	List primeiro = NULL;
	List segundo = NULL;
	List terceiro = NULL;
	//List quarto = NULL;

	primeiro=(NODE*)malloc(sizeof(NODE));
	segundo=(NODE*)malloc(sizeof(NODE));
	terceiro=(NODE*)malloc(sizeof(NODE));
	//quarto=(NODE*)malloc(sizeof(NODE));


	primeiro->data = 2;
	primeiro->next = segundo;

	
	segundo->data = 4;
	segundo->next = terceiro;

	terceiro->data = 7;
	terceiro->next = NULL;//quarto;

	//quarto->data = 10;
	//quarto->next = NULL;

	printList(primeiro);

	
	sizeList(primeiro);

	countList(primeiro);
}


void printList(List L) {
	if (L == NULL) {
		printf("\n \n\nA LISTA ENCONTRA-SE VAZIA");
		return;
	}

	while (L != NULL) {

		printf("\n %d", L->data);
		L = L->next;
	}

}

void deleteList(List L) {
	Node* current = L;
	Node* seguinte;

	while (current != NULL) {
		seguinte = current->next;
		free(current);
		current = seguinte;
	}

	L = NULL;

}

int sizeList(List L) {
	int size = 0;

	while (L != NULL) {
		size++;
		L = L->next;

	}

	printf("\n \n A lista apresenta %d de elementos", size);
	return size;
}

// calcula a soma dos elementos da lista
int countList(List L) {
	int count = 0;

	while (L != NULL) {
		count = count + L->data;
		L = L->next;
	}

	printf("\n \n A soma e igual a %d\n \n ", count);
	return count;
}
