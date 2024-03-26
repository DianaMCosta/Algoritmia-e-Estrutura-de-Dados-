#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>

// Header file for LINKED_LIST
#ifndef _LINKED_LIST_DEFINITIONS
#define _LINKED_LIST_DEFINITIONS

//-------------------------------------------------------
#ifndef _LOGICAL
#define _LOGICAL
typedef enum { ERROR = 0, OK = 1 } STATUS;
typedef enum { FALSE = 0, TRUE = 1 } BOOLEAN;
#endif // !_LOGICAL

#define MAX_CHARS 20

//-------------------------------------------------------
// linked node and list definitions

typedef struct {
    char nome[MAX_CHARS];
    float custo;
    BOOLEAN estado;
    int liga;
}STATION;


typedef struct _LIST_NODE {
    STATION* data;
    struct _LIST_NODE* pNext;
}LIST_NODE;

typedef LIST_NODE* LINKED_LIST;

//-------------------------------------------------------
#ifndef _DATA_MACRO
#define _DATA_MACRO
// macro definition for easy access to single node data field
#define DATA(X) ((X)->data)
#endif // !_DATA_MACRO

//-------------------------------------------------------
#ifndef _LINK_LIST_MACRO
#define _LINK_LIST_MACRO
// macro definition for easy access to single LIST_NODE link field
#define NEXT(X) ((X)->pNext)
#endif // !_LINK_LIST_MACRO

//-------------------------------------------------------
// Functions Declaration --------------------------------
//-------------------------------------------------------

// Constructors and Destructors -------------------------
STATUS newLinkedList(LINKED_LIST*);
STATUS newListNode(LIST_NODE**, STATION*);
STATUS destroyLinkedList(LINKED_LIST*);

// Input and Output -------------------------------------
STATUS putHeadLinkedList(LINKED_LIST*, STATION*);
STATUS removeHeadLinkedList(LINKED_LIST*, STATION**);

// Query ------------------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST);
int lengthLinkedList(LINKED_LIST);
LIST_NODE* getHeadLinkedList(LINKED_LIST);
LIST_NODE* getTailLinkedList(LINKED_LIST);
STATUS printLinkedList(LINKED_LIST);
#endif // !_LINKED_LIST_DEFINITIONS

STATUS startMetroLines(LINKED_LIST*, int);
STATUS addStation(LINKED_LIST*);
void printMetroLine(LINKED_LIST);
void destroyMetroNetwork(LINKED_LIST*);
STATUS ReadLine(LINKED_LIST*, const char*);
float custoLinha(LINKED_LIST);
BOOLEAN stationExist(LINKED_LIST, const char*);
STATUS deleteStation(LINKED_LIST*, const char*);
int getPosition(LINKED_LIST, const char*);


int main()
{
    LINKED_LIST metroNetwork = NULL;
    int c, nLines;
    BOOLEAN out = FALSE;
    printf("Metro network number of lines: ");
    scanf("%d", &nLines);


    char nome[50];
    //flush the input buffer
    while ((c = getchar()) != '\n');
    system("cls");
    if (startMetroLines(&metroNetwork, nLines) == ERROR)
        return ERROR;
    do {
        fprintf(stdout, "\n\n");
        fprintf(stdout, "0 -- Exit\n");
        fprintf(stdout, "1 -- Add station (enter Line, Station and Position)\n");
        fprintf(stdout, "2 -- Delete Station (enter Line and Station)\n");
        fprintf(stdout, "3 -- Get Station Position\n");
        fprintf(stdout, "4 -- Journey Fare (enter Origin and Destination)\n");
        fprintf(stdout, "5 -- Print line (enter Line)\n");
        fprintf(stdout, "6 -- Price of the full line\n");
        fprintf(stdout, "7 -- Station Exit\n");
        fprintf(stdout, "8 -- Change status\n");
        fprintf(stdout, "9 -- Save lines data\n");
        fprintf(stdout, "\nOption: ");
        scanf("%d", &c);
        //flush the input buffer
        while (getchar() != '\n');

        switch (c) {
        case 0: out = TRUE;
            break;
        case 1: if (addStation(metroNetwork, "Hospital") == OK)
            printf("Estação adicionada com sucesso!\n");
              else
            printf("ERRO!\n");
            break;
        case 2: deleteStation(&metroNetwork, "Lordelo");
                        break;
        case 3: printf("A estacao esta na posicao %d", getPosition(metroNetwork, "Lord"));
                        break;
                   /* case 4: ticketFares(metroNetwork, nLines);
                        break;
            */
        case 5: printMetroLine(metroNetwork);
            break;
        case 6: printf("A linha custa %.2f", custoLinha(metroNetwork));
            break;
        case 7: printf("NOME DA ESTAÇÃO: ");
            gets(nome);
            if (stationExist(metroNetwork, nome));
            break;
        case 8: printf("NOME DA ESTAÇÃO: ");
            gets(nome);
            changeStatus(metroNetwork, nome);

            break;
        case 9: saveMetroLines(metroNetwork, nLines);
            break;
        default:fprintf(stdout, "Invalid option\n\n");
        }
    } while (out != TRUE);

    destroyMetroNetwork(&metroNetwork);

    return OK;


}
STATUS startMetroLines(LINKED_LIST* list, int nlines)
{
    char nomeArquivo[20];

    sprintf(nomeArquivo, "line%d.txt", nlines);
    if (ReadLine(list, nomeArquivo))
        return OK;
    return ERROR;
}

STATUS ReadLine(LINKED_LIST* list, const char* filename)
{
    FILE* fp;
    STATION* pt;
    int ativa;

    if ((fp = fopen(filename, "r")) != NULL)
    {
        while (!feof(fp))
        {
            if ((pt = (STATION*)malloc(sizeof(STATION))) != NULL && (putHeadLinkedList(list, pt) != ERROR))
            {
                fscanf(fp, "%[^;];%f;%d;%d\n", pt->nome, &(pt->custo), &ativa, &(pt->liga));
                pt->estado = FALSE;
                if (ativa)
                    pt->estado = TRUE;
            }
            else
            {
                destroyMetroNetwork(list);
                return ERROR;
            }
        }
        fclose(fp);
        return OK;
    }
    else
        return ERROR;
}

STATUS saveMetroLines(LINKED_LIST list, int nline) {
    FILE* fp;
    char nomeArquivo[20];  // Defina o tamanho adequado para o nome do arquivo

    sprintf(nomeArquivo, "line%d_Copia.txt", nline);

    if ((fp = fopen(nomeArquivo, "w")) != NULL) {
        while (list != NULL) {
            fprintf(fp, "%s;%.2f;%d;%d;\n",
                ((STATION*)DATA(list))->nome,
                ((STATION*)DATA(list))->custo,
                ((STATION*)DATA(list))->estado,
                ((STATION*)DATA(list))->liga);
            list = NEXT(list);
        }
        fclose(fp);
        return OK;

    }
    else
        return ERROR;
}
STATUS addStation(LINKED_LIST* L, const char* afterStation)
{
    STATION* newStation;
    

    LIST_NODE* temp = L;
    LIST_NODE* NewNode;
    char op;

    if (stationExist(L, afterStation) == FALSE)
        return ERROR;

    //se não existir criamos uma nova estação
    newStation = (STATION*)malloc(sizeof(STATION));
    if (newStation == NULL)
        return ERROR;

    //preencher oss espaços/atributos da estação
    printf("Insert the name of the new station: ");
    gets(newStation->nome);

    printf("Price of the line: ");
    scanf("%f", &newStation->custo);

    printf("Ativa [s/n]: ");
    scanf("%c", &op);
    while(getchar() != '\n')

    if (op == 's')
        newStation->estado = TRUE;
    else
        newStation->estado = FALSE;

    //OUTRA OPÇÃO PARA AS QUATRO LINHAS ANTERIORES
    newStation->estado = (op == 's') ? TRUE : FALSE;
    newStation->liga = -1;

    //CRIA UM NOVO NÓ NA LISTA EXISTENTE ANTERIORMENTE
    if (newListNode(&NewNode, newStation) == ERROR)
        return ERROR;

    //vai comparar o nome e utiliza o Data para aceder as informações
    //encontrar a estação que tem o nome do parâmetro afterstation
    while (strcmp(DATA(temp)->nome, afterStation) != 0) {
        temp = NEXT(temp);
    }

    NEXT(NewNode) = NEXT(temp);
    NEXT(temp) = NewNode;


    return OK;
}

void printMetroLine(LINKED_LIST list)
{
    while (list != NULL)
    {
        printf("%s - %.2f - %d\n", DATA(list)->nome, list->data->custo, DATA(list)->estado);
        list = NEXT(list);
    }
}


//função para destruir a lista
void destroyMetroNetwork(LINKED_LIST* L)
{
    int* pX = NULL;
    // underflow
    if (emptyLinkedList(*L))
        return ERROR;
    // if pX = NULL - don't want to use the deleted data
    while (*L != NULL)
        removeHeadLinkedList(L, pX);
    return OK;
}


float custoLinha(LINKED_LIST L) {
    float custo = 0;
    while (L != NULL) {
        custo += DATA(L)->custo;
        L = NEXT(L);

    }
    return custo;
}


BOOLEAN stationExist(LINKED_LIST list , const char* nome) {
    
    //char /*ret[10];

    //if (nome == NULL) 
    //    return ERROR;

    //ret = strcmp(nome,getHeadLinkedList(LINKED_LIST ));*/

    while (list != NULL)
    {
        if (strcmp(nome, DATA(list)->nome) == 0) {
            return TRUE;
        }

        list = NEXT(list);
    }

    return FALSE;
    

}

STATUS deleteStation(LINKED_LIST* list, const char* nome)
{
    LIST_NODE* temp, * ant;
    temp = ant = *list;

    while (temp != NULL) {
        if (strcmp(DATA(temp)->nome, nome) == 0) {
            if (temp == *list)
                *list = NEXT(temp);     //NEXT(*list)
        
        else
            NEXT(ant) = NEXT(temp);
        free(DATA(temp));
        free(temp);

        return OK;
        
        }

        ant = temp;
        temp = NEXT(temp);
    }

    return ERROR;
}

int getPosition(LINKED_LIST list, const char* nome)
{
    //começa em 1 porque se encontrar logo na primeira iteração ele sai e não contabiliza como sendo 1
    int pos = 1;
    while (list != NULL && (strcmp(DATA(list)->nome, nome))) {
        pos++;
        list = NEXT(list);
    }
    if (list != NULL)
        return pos;
    else
        return 0;
}

STATUS changeStatus(LINKED_LIST list, const char* nome) {
    while (list != NULL) {
        if (strcmp(nome, DATA(list)->nome) == 0) {
            DATA(list)->estado = (DATA(list)->estado == 0) ? 1 : 0;

            return OK;
        }
    }
}


// Source file for LINKED_LIST
//-------------------------------------------------------
// Constructor functions --------------------------------
STATUS newLinkedList(LINKED_LIST* pL)
{
    *pL = NULL;
    return OK;
}

//-------------------------------------------------------
STATUS newListNode(LIST_NODE** pN, STATION* X)
{
    LIST_NODE* pTempN;
    // node allocation
    if ((pTempN = (LIST_NODE*)malloc(sizeof(LIST_NODE))) == NULL) {
        printf("\nLinkedList node: memory allocation error");
        return ERROR;
    }
    // list node update
    *pN = pTempN;
    DATA(pTempN) = X;
    //pTempN->data = X;
    NEXT(pTempN) = NULL;
    return OK;
}
//-------------------------------------------------------
// Destructor functions ---------------------------------
STATUS destroyLinkedList(LINKED_LIST* pL)
{
    STATION* pX = NULL;
    // underflow
    if (emptyLinkedList(*pL))
        return ERROR;
    // if pX = NULL - don't want to use the deleted data
    while (*pL != NULL)
        removeHeadLinkedList(pL, &pX);
    return OK;
}
//-------------------------------------------------------
// Input functions --------------------------------------
STATUS putHeadLinkedList(LINKED_LIST* pL, STATION* X)
{
    LIST_NODE* pTempN;
    // node creation
    if (newListNode(&pTempN, X) == ERROR)
        return ERROR;
    // list update
    NEXT(pTempN) = *pL;
    *pL = pTempN;
    return OK;
}
//-------------------------------------------------------
// Output functions -------------------------------------
STATUS removeHeadLinkedList(LINKED_LIST* pL, STATION** pX)
{
    LIST_NODE* pAuxN;
    //underflow
    if (emptyLinkedList(*pL))
        return ERROR;
    // node deletion
    pAuxN = *pL;
    *pL = NEXT(*pL);
    // node data and memory handling
    if (pX != NULL) // if pX = NULL - don't want to use the returned data
        *pX = DATA(pAuxN);
    else
        free(pAuxN);
    return OK;
}
//-------------------------------------------------------
// Query functions --------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST L)
{
    return ((L == NULL) ? TRUE : FALSE);
}
//-------------------------------------------------------
int lengthLinkedList(LINKED_LIST L)
{
    int size = 0;
    LIST_NODE* pAuxL = NULL;
    for (pAuxL = L; pAuxL != NULL; pAuxL = NEXT(pAuxL))
        size++;
    return size;
}
//-------------------------------------------------------
LIST_NODE* getHeadLinkedList(LINKED_LIST L)
{
    if (!emptyLinkedList(L))
        return (L);
    else
        return NULL;
}
//-------------------------------------------------------
LIST_NODE* getTailLinkedList(LINKED_LIST L)
{
    if (emptyLinkedList(L))
        return NULL;
    LIST_NODE* pTempL = L;
    while (NEXT(pTempL) != NULL)
        pTempL = NEXT(pTempL);
    return pTempL;
}
//-------------------------------------------------------
STATUS printLinkedList(LINKED_LIST L)
// non-generic - suitable only for int data
{
    int i = 0;
    LIST_NODE* pAuxL = NULL;
    if (emptyLinkedList(L)) {
        printf("\nEmpty List.\n");
        return ERROR;
    }
    for (pAuxL = L; pAuxL != NULL; pAuxL = NEXT(pAuxL), i++)
        printf("\nList element [%d]: %d", i, DATA(pAuxL));
    return OK;
}
