void removeList(List* lista) {
	List current = *lista;
	List previous = NULL;

	char farma[50];

	printf("INTRODUZA O NOME DA FARMACIA QUE PRETENDE REMOVER DA LISTA");
	scanf("%s", farma);

	if (current == NULL) {
		printf("A LISTA ENCONTRA-SE VAZIA");
	}

	while (current != NULL) {
		Vacina* pt = (Vacina*)(current->data);

		int cmp = strcmp(farma, pt->farmacia);

		if (cmp == 0) {
			if (previous == NULL) {
				*lista = current->next;

			}
			else {
				previous->next = current->next;
			}
			free(current);
			free(pt);

			current = (previous == NULL) ? *lista : previous->next;
			//Current = *lista // caso Previous == NULL
			//Current = Previous->next // caso contrario
		}else {
		previous = current;
		current = current->next;
	}

	}
	
}
