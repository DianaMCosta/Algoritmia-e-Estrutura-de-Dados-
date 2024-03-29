void Custo_Lote(List lista) {
	int codigo;
	Vacina* pt = (Vacina*)(lista->data);


	float custo_lote=0;


	printf("INTRODUZA O NUMERO DO LOTE: ");
	scanf("%d", &codigo);

	
	while (lista != NULL) {
		if (codigo == pt->lote) {
				float preço_unidade = pt->custo;
				float numero_unidade = pt->quantidade;
				custo_lote = preço_unidade * numero_unidade;	

				printf("Custo do lote: %.2f", custo_lote);

				break;
		}

		lista = lista->next;	
	}
	printf("LOTE NÃO ENCONTRADO");

}
