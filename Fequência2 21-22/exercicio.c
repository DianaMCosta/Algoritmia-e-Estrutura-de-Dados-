#include <stdlib.h>
#include <stdio.h>
typedef enum _STATUS { ERROR, OK } STATUS;
typedef enum _BOOLEAN { FALSE, TRUE } BOOLEAN;
#define MAX 20
typedef struct _DIR {
	char desig[MAX];
	int tamanho, Kb;
}DIR;
typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;
typedef BTREE_NODE* BTREE;
#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)
int main()
{
	BTREE btree = NULL;
	if (CreateBtree(&btree))
	{
		...
	}
	return 1;
}

// PRIMEIRA PERGUNTA
//Faça uma função (ou mais) que liste no ecrã todos os dados das diretorias com mais de 20
//ficheiros(tamanho > 20).

void PrintDiretoria(BTREE btree) {

	if (btree == NULL) {
		return;
	}

	DIR* dir = ((DIR*)DATA(btree));

	if (dir->tamanho > 20) {
		printf("DESIGN= %s, TAMANHO=%d, KB= %d", dir->desig, dir->tamanho, dir->Kb);
	}

	PrintDiretoria(LEFT(btree));
	PrintDiretoria(RIGHT(btree));

}

//SEGUNDA PERGUNTA
//Faça uma função (ou mais) que calcule, e devolva, o numero total de Kb (Kb) de todas as
//diretorias com mais de 10 ficheiros(tamanho > 10).

int CalculoKB(BTREE btree) {
	if (btree == NULL)
		return 0;

	DIR* dir = ((DIR*)DATA(btree));
	int KBtotal = 0;

	if (dir->tamanho > 10) {
		KBtotal += dir->Kb;
	}

	KBtotal+=CalculoKB(LEFT(btree));
	KBtotal+=CalculoKB(RIGHT(btree));

	return KBtotal;
}
//--------------------------------- duas formas de fazer a função------------------
int CalculoKB(BTREE btree) {
	if (btree == NULL)
		return 0;

	DIR* dir = ((DIR*)DATA(btree));

	if (dir->tamanho > 10) {
		return dir->Kb + CalculoKB(LEFT(btree)) + CalculoKB(RIGHT(btree));
	}
	else {

		return CalculoKB(LEFT(btree)) + CalculoKB(RIGHT(btree));
	}
	return 0;
}
