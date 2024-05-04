#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 20
#define STAGES 15

typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;

typedef struct _BTREE_NODE
{
	PLAYER* pData;
	struct _BTREE_NODE* pL;
	struct _BTREE_NODE* pR;
} BTREE_NODE;


typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pL)
#define RIGHT(node) ((node)->pR)

BTREE_NODE* NewBtreeNode(PLAYER* data);
BTREE_NODE* InitNode(PLAYER*, BTREE_NODE*, BTREE_NODE*);
BTREE_NODE* CreateBtree(PLAYER**, int, int);
STATUS ReadPlayersFromFile(PLAYER**, char*);
BOOLEAN BtreeLeaf(BTREE_NODE* node);
int CountLeafs(BTREE);
int CountLeafs2(BTREE);
int BtreeSize(BTREE);
int TotalSize(BTREE);
void PrintLeafs(BTREE);
void PrintGame(BTREE);
void PrintAllGame(BTREE);
int PlayerSetsGanhos(BTREE, char* nome);


int main()
{
	BTREE Btree;

	PLAYER* players[STAGES];
	char file_name[MAX_NAME];
	char nome[MAX_NAME];
	char Novonome[MAX_NAME];

	if (ReadPlayersFromFile(players, "torneio.txt"))
	{
		Btree = CreateBtree(players, 0, STAGES);
		printf("\nNumero de participantes: %d\n", CountLeafs2(Btree));
		printf("\nNumero de participantes 2 : %d\n", CountLeafs2(Btree));

		//------------------ AULA 18/04 -------------------------
		printf("\nNumero de jogos: %d\n", BtreeSize(Btree) / 2);
		printf("\nVencedor do torneio: %s\n", DATA(Btree)->name);
		printf("\n Total de sets jogados: %d\n", TotalSets(Btree));
		printf("\nLista de jogadores: %s\n");
		PrintLeafs(Btree);
		printf("\n Jogo da final:\n");
		PrintGame(Btree);
		printf("\nLista todos os jogos:\n");
		PrintAllGame(Btree);
		printf("\nSets ganhos %d\n", PlayerSetsGanhos(Btree, DATA(Btree)->name));

		// DATA(Btree)->name generalização para o primeiro nó
		// se colocarmos por exemplo em vez disso o Player7 retorna o numero de jogos que ele ganhou
		//-------------------------------------------------------
	}
	else
		printf("ERRO na leitura do ficheiro\n");

	return 0;
}

//metodo pré order que estamos a utilizar para criar a arvore binaria
BTREE_NODE* NewBtreeNode(PLAYER* data)
{
	BTREE_NODE* tmp_pt;

	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

BTREE_NODE* InitNode(PLAYER* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

BTREE_NODE* CreateBtree(PLAYER** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

STATUS ReadPlayersFromFile(PLAYER** players, char* file_name)
{
	FILE* fp;
	int j, i = 0;

	PLAYER* ptr_data;

	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = (PLAYER*)malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%[^;];", ptr_data->name);
				fscanf(fp, "%d\n", &ptr_data->sets);
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}


BOOLEAN BtreeLeaf2(BTREE_NODE* btree) {
	if ((LEFT(btree)==NULL && RIGHT(btree)==NULL))
		return TRUE;
	else 
		return FALSE;
}

int CountLeafs2(BTREE btree) {
	if (BtreeLeaf2(btree))
		return 1;
	int folha_esquerda = CountLeafs2(LEFT(btree));
	int folha_direita = CountLeafs2(RIGHT(btree));
	int total_folhas = folha_esquerda + folha_direita;

	return total_folhas;
}


int BtreeSize2(BTREE btree) {
	if (btree == NULL) {
		return 0;
	}
	int tamanhoEsq = BtreeSize2(LEFT(btree));
	int tamanhoDir = BtreeSize2(RIGHT(btree));

	return 1 + tamanhoEsq + tamanhoDir;
}

int TotalSets2(BTREE btree) {
	if (btree == NULL)
		return 0;
	int setAtual = DATA(btree)->sets;
	int setEsq = TotalSets2(LEFT(btree));
	int setDir = TotalSets2(RIGHT(btree));

	return setAtual + setEsq + setDir;
}


void PrintLeafs(BTREE btree) {

	if (BtreeLeaf(btree)) {
		printf("\t%s\n", DATA(btree)->name);
	}
	else {
		PrintLeafs(LEFT(btree));
		PrintLeafs(RIGHT(btree));
	}
}

void PrintGame(BTREE btree) {

	if (!BtreeLeaf(btree) && btree != NULL) {
		printf("\t%s (%d)  <------> (%d) %s\n",
			DATA(LEFT(btree))->name,
			DATA(LEFT(btree))->sets,
			DATA(RIGHT(btree))->sets,
			DATA(RIGHT(btree))->name

		);
	}
}

void PrintAllGame(BTREE btree) {
	if (!BtreeLeaf(btree) && btree != NULL) {
		PrintAllGame(LEFT(btree));
		PrintAllGame(RIGHT(btree));
		PrintGame(btree);
	}
}

int PlayerSetsGanhos(BTREE btree, char* nome) {
	int total = 0;
	if (btree != NULL) {
		if (strcmp(DATA(btree)->name, nome) == 0) {
			total += DATA(btree)->sets;
		}
		total += PlayerSetsGanhos(LEFT(btree), nome) + PlayerSetsGanhos(RIGHT(btree), nome);
	}

	return total;
}
