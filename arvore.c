#include <stdlib.h>
#include <stdio.h>

#include "arvore.h"

p_no criar_arvore(p_no esq, p_no dir) {
	p_no raiz = malloc(sizeof(No));
	if (raiz == NULL) {
		printf("Falha na alocação de memoria");
	}
	raiz->esq = esq;
	raiz->dir = dir;
	raiz->dado = NULL;

	return raiz;
}

void destruir_arvore(p_no raiz) {
	if (raiz == NULL) {
		return;
	}
	destruir_arvore(raiz->esq);
	destruir_arvore(raiz->dir);
	free(raiz->dado);
	free(raiz);
}
