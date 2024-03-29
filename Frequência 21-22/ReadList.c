void ReadList(List* lista, const char* filename) {

	FILE* fp;
	Vacina* pt;
	filename = "dados.txt";

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("ERRO AO ABRIR/ENCONTRAR O FICHEIRO DOS DADOS");
		return;
	}

	char* line = (char*)malloc(sizeof(char)*MAX);

	while (fgets(line, MAX, fp)) {
		Vacina* pt = (Vacina*)malloc(sizeof(Vacina));

		strcpy(pt->farmacia, strtok(line, ";"),MAX);

		//o NULL permite que ele identifique o valor correto a converter
		//porque começa onde ele parou, ou seja, começa após o nome
		pt->custo = atoi(strtok(NULL, ";"));
		pt->quantidade = atoi(strtok(NULL, ";"));

		char* price_str = strtok(NULL, "\0");
		char* ptr = strchr(price_str, ',');
		if (ptr != NULL) { //caso exista a virgula;
			*ptr = '.';
		}

		pt->custo = atof(price_str);

		List_Node* novo = (List_Node*)malloc(sizeof(List_Node)); 

		if (*lista == NULL) {
			novo->data = pt;
			novo->next = NULL;
			*lista = novo;

		}
		else {
			novo->data = pt;
			novo->next = *lista;
			*lista = novo;
		}
	}
	fclose(fp);
	free(line);
}
