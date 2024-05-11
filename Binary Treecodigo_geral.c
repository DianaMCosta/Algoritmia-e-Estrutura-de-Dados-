//FREQUENCIA 21/22

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

	KBtotal += CalculoKB(LEFT(btree));
	KBtotal += CalculoKB(RIGHT(btree));

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


//TERCEIRA PERGUNTA
//Faça uma função que calcule, e devolva, o total de KB de uma diretoria (e todas as suas subdiretorias) 
//cuja designação deve ser recebida como parâmetro

int TotalKBdiretoria(BTREE btree, char* designacao) {

	DIR* dir = ((DIR*)DATA(btree));
	int valor;

	if (btree == NULL)
		return 0;

	if (strcmp(dir->desig, designacao)==0)
		valor += dir->Kb;
	
	valor += TotalKBdiretoria(LEFT(btree),designacao);
	valor += TotalKBdiretoria(RIGHT(btree),designacao);


	return valor;
}

//-------------------------------------------------------------------------------
//FREQUENCIA 2018/2019

typedef struct _PERSON {
	char name[50];
	int age;
	BOOLEAN alive;
}PERSON;

typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)

typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

int main(int argc, char* argv[])
{
	BTREE btree;
	void* persons[15];
	char file_name[20];
	printf("Nome do ficheiro: ");
	scanf("%s", file_name);
	if (ReadFile(persons, file_name))
	{
		btree = CreateBtree(persons, 0, 15);

		BtreeFree(btree);
	}
	else
		printf("ERRO na leitura do ficheiro\n");
	return 1;
}


BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL) {
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

void BtreeFree(BTREE btree)
{
	if (btree != NULL) {
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(DATA(btree));
		free(btree);
	}
}

BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

STATUS ReadFile(void** persons, char* file_name)
{
	FILE* fp;
	int aux, j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL) {
		while (!feof(fp)) {
			if ((ptr_data = malloc(sizeof(PERSON))) != NULL) {
				fscanf(fp, "%[^;];%d;%d\n", ((PERSON*)ptr_data)->name, &((PERSON*)ptr_data)->age, &aux);
				if (aux) ((PERSON*)ptr_data)->alive = TRUE;
				else ((PERSON*)ptr_data)->alive = FALSE;
				persons[i] = ptr_data;
				i++;
			}
			else {
				for (j = i; j >= 0; j--)
					free(persons[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}

BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size) return(NULL);
	else return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

//01 Desenvolva o código necessário para contar o número de pessoas da árvore que estão vivas (alive = TRUE).

int NumeroVivas(BTREE btree) {

	int p_vivas = 0;
	if (btree == NULL)
		return 0;

	PERSON* pp = (PERSON*)DATA(btree);

	if (pp->alive == TRUE)
		p_vivas++;

	p_vivas += NumeroVivas(LEFT(btree));
	p_vivas += NumeroVivas(RIGHT(btree));

	return p_vivas;
}

//Desenvolva o código necessário para alterar o nome de uma pessoa cujo nome original, e o final, devem ser
//lidos através do teclado.

STATUS alterarNome(BTREE btree, char* nome_novo, char* nome_antigo) {
	
	if (btree == NULL)
		return ERROR;

	PERSON* pp = (PERSON*)DATA(btree);

	if (strcmp(pp->name, nome_antigo) == 0) {
		strcpy(pp->name, nome_novo);
		return OK;
	}

	alterarNome(LEFT(btree), nome_novo, nome_antigo);
	alterarNome(RIGHT(btree), nome_novo, nome_antigo);

	return OK;

}

//Desenvolva o código necessário para acrescentar 2 nós de árvore (filho da esquerda e da direita) à folha mais
//à direita da árvore.NOTA: os dados dos novos nós devem ser introduzidos através do teclado.


//BST - 
STATUS adicionar(BTREE btree) {

	if (btree == NULL)
		return ERROR;

	PERSON* pp = (PERSON*)DATA(btree);

	if (RIGHT(btree) != NULL) {
		adicionar(RIGHT(btree));
	}

	return OK;
}


void AdicionarNosFolhaDireita(BTREE btree, void* dataEsquerda, void* dataDireita) {
	if (btree == NULL) {
		return; // Árvore vazia, não faz nada
	}

	// Encontrar a folha mais à direita
	BTREE atual = btree;
	while (atual->right != NULL) {
		atual = atual->right;
	}

	// A folha mais à direita foi encontrada, agora adicionar os dois nós
	atual->left = NewBtreeNode(dataEsquerda);  // Adiciona o nó filho da esquerda
	atual->right = NewBtreeNode(dataDireita);  // Adiciona o nó filho da direita
}


//------------------------------------------------------------------------------------
//FREQUÊNCIA 2017/2018

typedef struct _DEPT {
	char desig[20];
	float ganhos, despesas;
	int n_pessoas;
}DEPT;

typedef struct _BTREE_NODE {
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)

typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

int main(int argc, char* argv[])
{
	BTREE btree;
	void* depts[15];
	char file_name[20];
	printf("Nome do ficheiro: ");
	scanf("%s", file_name);
	if (ReadFile(depts, file_name)) {
		btree = CreateBtree(depts, 0, 15);

		BtreeFree(btree);
	}
	else printf("ERRO na leitura do ficheiro\n");
	return 1;
}

BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL) {
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

void BtreeFree(BTREE btree)
{
	if (btree != NULL) {
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(DATA(btree));
		free(btree);
	}
}
BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}
STATUS ReadFile(void** depts, char* file_name)
{
	FILE* fp;
	int j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL) {
		while (!feof(fp)) {
			if ((ptr_data = malloc(sizeof(DEPT))) != NULL) {
				fscanf(fp, "%[^;];%d;%f;%f\n", ((DEPT*)ptr_data)->desig, &((DEPT*)ptr_data)->n_pessoas,
					&((DEPT*)ptr_data)->ganhos, &((DEPT*)ptr_data)->despesas);
				depts[i] = ptr_data;
				i++;
			}
			else {
				for (j = i; j >= 0; j--)
					free(depts[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}
BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size) return(NULL);
	else return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

//PRIMEIRA PERGUNTA
//Desenvolva o código necessário para apresentar no 
// ecrã os lucros da empresa: volume de ganhos - volume de despesas.


//nota: cada nó é um departamento
float LucrosEmpresa(BTREE btree) {
	if (btree == NULL)
		return;

	float lucros = 0;

	DEPT* dept = (DEPT*)DATA(btree);
	lucros = lucros + ((dept->ganhos) - (dept->despesas));

	lucros += LucrosEmpresa(RIGHT(btree));
	lucros += LucrosEmpresa(LEFT(btree));

	return lucros;
}

//Desenvolva o código necessário para mostrar 
//no ecrã os dados do departamento com o maior número de pessoas.

STATUS maiorPessoas(BTREE btree) {

	if (btree == NULL)
		return ERROR;

	DEPT* dept = (DEPT*)DATA(btree);

	return MAX(maiorPessoas(LEFT(btree), maiorPessoas(RIGTH(btree)));

}

//Desenvolva o código necessário para eliminar todos os sub-departamentos de um determinado
//departamento, cuja designação deve ser lida através do teclado, 
// transferindo todos os trabalhadores dos sub -departamentos para este.




//FREQUÊNCIA 2016/2017

typedef struct _DIR {
	char nome[20];
	int n_fich;
	int n_Kb;
}DIR;

typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)

typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

int main(int argc, char* argv[])
{
	BTREE btree;
	void* dirs[15];
	char file_name[20];
	printf("Nome do ficheiro: ");
	scanf("%s", file_name);
	if (ReadFile(dirs, file_name))
	{
		btree = CreateBtree(dirs, 0, 15);

		BtreeFree(btree);
	}
	else
		printf("ERRO na leitura do ficheiro\n");
	return 1;
}

BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL) {
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

void BtreeFree(BTREE btree)
{
	if (btree != NULL) {
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(DATA(btree));
		free(btree);
	}
}

BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

//PRIMEIRA PERGUNTA
//Desenvolva o código necessário para mostrar no ecrã todos os dados das diretorias que contenham mais de
//1000 Kbytes armazenados.

void Dados_maior(BTREE btree) {

	if (btree == NULL)
		return;

	DIR* dir = (DIR*)DATA(btree);

	if (dir->n_Kb > 1000)
		printf("%s   - %d     -  %d", dir->nome, dir->n_fich, dir->n_Kb);

	Dados_maior(RIGHT(btree));
	Dados_maior(LEFT(btree));
}

//Desenvolva o código necessário para mostrar no ecrã o número total de ficheiros armazenado por uma
//diretoria(e suas subdiretorias) cujo nome deve ser lido através do teclado.

float nFicheiros(BTREE btree, char* nome) {

	if (btree == NULL)
		return;

	float total = 0;
	DIR* dir = (DIR*)DATA(btree);

	

	if (strcmp((dir->nome), nome))
		total = dir->n_fich;


	total += nFicheiros(LEFT(btree),nome);
	total += nFicheiros(RIGHT(btree),nome);

	return total;
}

//Desenvolva o código necessário para contar e mostrar no ecrã o número de diretorias vazias.

 int diretoriasVazias(BTREE btree) {

	int vazias = 0;

	if (btree == NULL)
		return;

	DIR* dir = (DIR*)DATA(btree);

	if (dir->n_Kb == NULL)
		vazias++;

	vazias += diretoriasVazias(LEFT(btree));
	vazias += diretoriasVazias(RIGHT(btree));

	return vazias;
}
