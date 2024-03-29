void printList(List lista) {
	printf("\n");


	while (lista != NULL) {
		Vacina* vacina = (Vacina*)(lista->data);

		printf("%s - %d - %d - %.2f\n\n", vacina->farmacia, vacina->quantidade, vacina->lote, vacina->lote);

		lista = lista->next;
	}
}
