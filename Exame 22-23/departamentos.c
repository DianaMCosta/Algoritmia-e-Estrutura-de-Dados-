#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//definimos o estados e os booleano a usar ao longo do programa
typedef enum _STATUS {ERROR, OK} STATUS;
typedef enum _BOOLEAN {TRUE, FALSE} BOOLEAN;

#define MAX 20

//representação do departamento de uma empresa de um determinado departamento
typedef struct _DEP {
	char design[MAX];		//designação do departamento
	int n_func;				//numero de funcionarios
	float despesas, ganhos;	//valor de despesas e o valor de ganhos do referido departamento
}DEPT;


//representa a criação do novo nó de uma lista (para acrescentar novas informações)
typedef struct _LIST_NODE {
	void* data;
	struct _LIST_NODE* next;
}LIST_NODE;

//em vez de estarmos sempre a referir uma lista como sendo LIST_NODE* LISTA PODEMOS DEFINIR LIST LISTA
typedef struct LIST_NODE* LIST;

#define DATA(node)((node)->data)
#define DATA(node)((node)->next)


//A LISTA List já foi criada préviamente e apresenta as informações de um determinado departamento


// esta função apresenta o balanço de ganhos na empresa de acordo com todos os departamentos
void Balanco(LIST lista) {
	float soma=0;
	float diferença=0;
	
	while (lista != NULL) {
		DEPT* dept = (DEPT*)(lista->data);
		float valor_despesas = dept->despesas;
		float valor_ganhos = dept->ganhos;
		diferença = valor_ganhos - valor_despesas;
		soma = soma + diferença;

		lista = lista->next;
	}

	if (soma==0) {
		printf("A LISTA ENCONTRA-SE VAZIA");
	}
	else {
		printf("O BALANÇO TOTAL DA EMPRESA É: %.4f (GANHOS)", soma);
	}
}


void Elimina(LIST* lista) {
	if (*lista == NULL) {
		printf("A LISTA ESTA VAZIA, NÃO HÁ NADA PARA ELIMINAR");
		return;
	}
	LIST current = *lista;
	*lista = (*lista)->next;
	free(current);
	printf("PRIMEIRO NÓ ELIMINADO COM SUCESSO");
}
