#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h> 
#include<stdlib.h> 
#include<conio.h> 

typedef struct data {
	int dia;
	int mes;
	int ano;
}DATA;

typedef struct {
	int numero;
	char nome[50];
	DATA data_nascimento;
}ALUNO;

typedef struct {
	int numero;
	char nome[50];
	DATA* data_nascimento;
}ALUNOP;

typedef struct _pessoa {
	char nome[50];
	int idade;
	struct _pessoa* pai;
}PESSOA;


void main() {
	ALUNO a;
	ALUNO* b;

	//utilizamos ponto por ser um objeto
	a.numero = 12345;
	strcpy(a.nome, "Joao Pereira");		//para escrever strings numa variavel

	a.data_nascimento.ano = 2000;
	a.data_nascimento.mes = 12;
	a.data_nascimento.dia = 25;

	printf("\nNome: %s\nNumero: %d\nDia: %d\nMes: %d\nAno: %d", a.nome, a.numero, a.data_nascimento.dia, a.data_nascimento.mes, a.data_nascimento.ano);


	//utilizamos seta por ser um ponteiro
	b = (ALUNO*)malloc(sizeof(ALUNO));		//reserva memória para a variabel b
	b->numero = 13145;
	strcpy(b->nome, "Joana Pereira");

	b->data_nascimento.ano = 2023;
	b->data_nascimento.mes = 11;
	b->data_nascimento.dia = 26;

	printf("\n\nNome: %s\nNumero: %d\nDia: %d\nMes: %d\nAno: %d", b->nome, b->numero, b->data_nascimento.dia, b->data_nascimento.mes, b->data_nascimento.ano);

	ALUNOP x;
	ALUNOP* y;
	//declaramos os valores da data por ser um ponteiro dentro da estrutura
	DATA d;
	d.dia = 12;
	d.mes = 5;
	d.ano = 2021;


	x.numero = 56789;
	strcpy(x.nome, "Ana Marques");
	x.data_nascimento = &d;

	printf("\n\nNome: %s\nNumero: %d\nDia: %d\nMes: %d\nAno: %d", x.nome, x.numero, x.data_nascimento->dia, x.data_nascimento->mes, x.data_nascimento->ano);

	y = (ALUNOP*)malloc(sizeof(ALUNOP));
	y->data_nascimento = (DATA*)malloc(sizeof(DATA));

	printf("\n\nintroduzaos valores do aluno");
	printf("\t Nome: ");
	gets(y->nome);
	printf("\tNumero: ");
	scanf("%d", &(y->numero));		//temos de colocar o endereço para o local onde está alocada a memória
	printf("\t Dia: ");
	scanf("%d", &(y->data_nascimento->dia));
	printf("\t Mes: ");
	scanf("%d", &(y->data_nascimento->mes));
	printf("\t Ano: ");
	scanf("%d", &(y->data_nascimento->ano));

	printf("\n\nNome: %s\nNumero: %d\nDia: %d\nMes: %d\nAno: %d\n", y->nome, y->numero, y->data_nascimento->dia, y->data_nascimento->mes, y->data_nascimento->ano);

	PESSOA s;
	PESSOA* t;

	s.idade = 13;
	strcpy(s.nome, "Joãozinho ");
	s.pai = NULL;


	t = (PESSOA*)malloc(sizeof(PESSOA));
	t->idade = 50;
	strcpy(t->nome, "Xico Silva");
	t->pai = NULL;

	s.pai = t;


	printf("\n\nNome: %s\nIdade: %d\nNome do Pai: %s\nIdade do Pai: %d", s.nome, s.idade, s.pai->nome, s.pai->idade);

}
