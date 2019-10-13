#include <stdlib.h>
#include <stdio.h>

#include "arvore.h"

p_no criar_arvore(int x, p_no esq, p_no dir) {
	p_no raiz = malloc(sizeof(No));
	if (raiz == NULL) {
		printf("Falha na alocação de memoria");
	}
	raiz->dado = x;
	raiz->esq = esq;
	raiz->dir = dir;
	raiz->pai = NULL;
	return raiz;
}

void ligar_filho_pai(p_no filho, p_no pai) {
	filho->pai = pai;
}
