
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<conio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}NODE;

void printList(NODE* l);
void deleteList(NODE** l);
int sizeList(NODE* l);
int coountList(NODE* l);

int main() {
    NODE* primeiro = NULL;
    NODE* segundo = NULL;
    NODE* terceiro = NULL;

    primeiro = (NODE*)malloc(sizeof(NODE));
    segundo = (NODE*)malloc(sizeof(NODE));
    terceiro = (NODE*)malloc(sizeof(NODE));

    primeiro->data = 5;
    primeiro->next = segundo;

    segundo->data = 12;
    segundo->next = terceiro;

    terceiro->data = 13;
    terceiro->next = NULL;

    //printList(primeiro->next);         // aparece o 2 e 3 numero
    printList(primeiro);                //aparecem tds os numeros

    //deleteList(&primeiro);              // apaga a lista

    printList(primeiro);

    sizeList(primeiro);                 // apresenta o tamanho da lista

    countList(primeiro);
}

void printList(NODE* l) {
    if (l == NULL) {
        printf("\n Lista Vazia");
        return;
    }
    while (l != NULL) {
        printf(" %d ", l->data);        // l --- nome da lista
        l = l->next;
    }

}

void deleteList(NODE** l) {

    NODE* current = *l;
    NODE* seguinte;

    while (current != NULL) {
        seguinte = current->next;
        free(current);
        current = seguinte;
    }

    *l = NULL;

}

//imprime o tamanho 
int sizeList(NODE* l) {
    int size = 0;

    while (l != NULL) {
        size++;
        l = l->next;
        
    }
    printf("\na lista tem o tamanho : %d", size);
    return size;
}

int countList(NODE* l) {
    int count = 0;

    while (l != NULL) {
        count = count++;
        l = l->next;

    }
    printf("\nsoma : %d", count);
    return count;
}
