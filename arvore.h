#ifndef ARVORE_H
#define ARVORE_H

typedef struct No {
	int dado;
	struct No *esq, *dir, *pai;
} No;

typedef No * p_no;

p_no criar_arvore(int x, p_no esq, p_no dir);

#endif
