#ifndef ARVORE_H
#define ARVORE_H

typedef struct No {
	char* dado;
	int eh_constante;
	struct No *esq, *dir;
} No;

typedef No * p_no;

p_no criar_arvore(p_no esq, p_no dir);

#endif
