#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

int ehOperador(char caracter) {
	return caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/';
}

void realizar_operacao(p_no raiz, char operador) {
	if (operador == '+') {
		raiz->dado = raiz->esq->dado + raiz->dir->dado;
	} else if (operador == '-') {
		raiz->dado = raiz->esq->dado - raiz->dir->dado;
	} else if (operador == '*') {
		raiz->dado = raiz->esq->dado * raiz->dir->dado;
	} else if (operador == '/') {
		raiz->dado = raiz->esq->dado / raiz->dir->dado;
	}
}

void resolver_equacao(int qtdParentesesAbertos, p_no raiz) {
	char caracterAnterior;
	char caracter = '.';
	
	while(1) {
		caracterAnterior = caracter;
		if (caracter == '(') {
			if (caracterAnterior != '.' && ehOperador(caracterAnterior)) {
				resolver_equacao(qtdParentesesAbertos + 1, raiz->dir);	
			} else {
				resolver_equacao(qtdParentesesAbertos + 1, raiz->esq);
			}
		} else if (caracter == ')') {
			break;
		} else {
			//printf("\nantes de começar a ler");
			scanf(" %d ", &raiz->esq->dado);
			scanf("%c", &caracter);
			//printf("\nantes de ler dir->dado");	
			scanf(" %d ", &raiz->dir->dado); 
			//printf("\nantes de realizar operação");			
			realizar_operacao(raiz, caracter);
			//printf("\n depois de realizar operação");
		}
		scanf(" %c", &caracter);
		//printf("\n depois de ler o caractere");
	}
	printf("\nResultado: %d", raiz->dado);
	
}

int main() {
	int m;

	scanf("%d", &m);
	int qtdParentesesAbertos = 0;
	char discardedWhiteSpace;
	scanf("%c", &discardedWhiteSpace);
	//scanf("%c", &discardedWhiteSpace);
	for (int i = 1; i <= m; i++) {
		//printf("\n%d", m);
		char primeiroParentese;
		scanf("%c", &primeiroParentese);
		//printf("Primeiro parêntese: %c", primeiroParentese);
		qtdParentesesAbertos++;
		p_no esq = malloc(sizeof(No));
		if (esq == NULL) {
			printf("Falha na alocação de memória");
			exit(1);
		}
		p_no dir = malloc(sizeof(No));
		if (dir == NULL) {
			printf("Falha na alocação de memória");
			exit(1);
		}
		p_no raiz = criar_arvore(0, esq, dir);
		resolver_equacao(qtdParentesesAbertos, raiz);
	}
	return EXIT_SUCCESS;
}
