#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

#define EH_CONSTANTE 1
#define NAO_EH_CONSTANTE 0

/* int ehOperador(char caracter) {
	return caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/';
}
*/
int realizar_operacao(p_no raiz) {
	if (raiz->dado[0] == '+') {
		return atoi(raiz->esq->dado) + atoi(raiz->dir->dado);
	} else if (raiz->dado[0] == '-') {
		return atoi(raiz->esq->dado) - atoi(raiz->dir->dado);
	} else if (raiz->dado[0] == '*') {
		return atoi(raiz->esq->dado) * atoi(raiz->dir->dado);
	} else {
		return atoi(raiz->esq->dado) / atoi(raiz->dir->dado);
	}
}
/*
void resolver_equacao(p_no raiz) {
	char caracterAnterior = '.';
	char caracter = '.';
	char* element = malloc(sizeof(char));
	short size = 1;
	
	scanf("%c", &caracter);
	int firstNumber = 1;
	while(1) {
		while (caracter != ' ') {
			element[size - 1] = caracter;
			element = realloc(element, size + 1);
			caracterAnterior = caracter;
			scanf("%c", &caracter);
		}
		caracterAnterior = caracter;
		if (caracter == '(') {
			if (caracterAnterior != '.' && ehOperador(caracterAnterior)) {
				resolver_equacao(raiz->dir);	
			} else {
				resolver_equacao(raiz->esq);
			}
		} else if (caracter == ')') {
			raiz->dado = atoi(raiz->esq->dado) + atoi(raiz->dir->dado);
			break;
		} else if (ehOperador(caracterAnterior)) {
			raiz->dado = element;
		} else if (firstNumber) {
			raiz->esq->dado = element;
			firstNumber = 0;
		} else {
			raiz->dir->dado = element;
		}
		//printf("\n depois de ler o caractere");
	}
	printf("\nResultado: %d", raiz->dado);
	
}

*/

char* buffer;

void operar_constantes(p_no raiz) {
	if (raiz->esq->eh_constante && raiz->dir->eh_constante) {
		int resultado = 0;
		resultado = realizar_operacao(raiz);

		free(raiz->dado);
		raiz->dado = malloc(12 * sizeof(char)); //12 é o máximo de caracteres de um int
		raiz->dado[0] = '0';

		destruir_arvore(raiz->esq);
		destruir_arvore(raiz->dir);

		raiz->esq = NULL;
		raiz->dir = NULL;

		sprintf(raiz->dado, "%d", resultado);
		raiz->eh_constante = 1;
	}
}

void simplificar_expressao(p_no raiz) {
	if (raiz != NULL && raiz->esq != NULL && raiz->dir != NULL) {

		simplificar_expressao(raiz->esq);
		simplificar_expressao(raiz->dir);
		operar_constantes(raiz);
	}
	/*if (raiz == NULL || (raiz->esq == NULL && raiz->dir == NULL)) {
		return;
	}

	if (raiz->esq->eh_constante && raiz->dir->eh_constante) {
		int resultado = 0;
		resultado = realizar_operacao(raiz);

		free(raiz->dado);
		raiz->dado = malloc(12 * sizeof(char));
		raiz->dado[0] = '0';

		destruir_arvore(raiz->esq);
		destruir_arvore(raiz->dir);

		raiz->esq = NULL;
		raiz->dir = NULL;

		sprintf(raiz->dado, "%d", resultado);
		raiz->eh_constante = 1;
	}
	//if (raiz->esq->eh_constante &&r raiz->dir->eh_constante) {
	//	raiz->
	//}
	simplificar_expressao(raiz->esq);
	simplificar_expressao(raiz->dir);
	*/
}

int tem_filhos(p_no raiz) {
	return raiz->esq != NULL || raiz->dir != NULL;
}


void imprimir_parenteses(char parenteses[], p_no raiz) {
	if (tem_filhos(raiz)) {
		printf(parenteses);
	}
}

void inordem(p_no raiz) {
	if (raiz != NULL) {
		imprimir_parenteses("( \0", raiz);
		inordem(raiz->esq);
		printf("%s ", raiz->dado);
		inordem(raiz->dir);
		imprimir_parenteses(") \0", raiz);
	}
}

void guardar_dados(p_no raiz, int inicio, int fim) {
	raiz->eh_constante = (fim - inicio == 0 || buffer[fim - 1] == '-') ? NAO_EH_CONSTANTE : EH_CONSTANTE;
	raiz->dado = malloc((fim - inicio + 2) * sizeof(char)); //tamanho = fim - inicio + 1; Quando eu somo 2, é porque
	                                                        // estou adicionando um espaço para o fim da string ('\0')
	raiz->dado[0] = '0';
	memcpy(raiz->dado, &buffer[inicio], fim - inicio + 1);
	raiz->dado[fim - inicio + 1] = '\0';
}

int eh_numero(char caracter) {
	return caracter >= '0' && caracter <= '9';
}

void percorre_numeros(int* i) {
	int contador_inicial = *i;
	while (eh_numero(buffer[*i]) || buffer[*i] == '-') {
		*i += 1;
	}

	if (*i > contador_inicial) {
		*i -= 1; //reduces one unit incremented before leaving while
	}
}

p_no criar_arvore_e_sub_arvores(int* i);
p_no inserir_dados_na_arvore(int *i);

p_no criar_arvore_e_sub_arvores(int* i) {
	if (buffer[*i] == '(') {
		*i += 2;
		return inserir_dados_na_arvore(i);
	}

	return criar_arvore(NULL, NULL);
}

void inserir_dado_no_filho_se_nao_houver(p_no filho, int *i) {
	int contador_inicial = *i;

	if (filho->dado == NULL) {
		percorre_numeros(i);
		guardar_dados(filho, contador_inicial, *i);
	}
}

p_no inserir_dados_na_arvore(int* i) {
	p_no raiz = criar_arvore(NULL, NULL);
	raiz->esq = criar_arvore_e_sub_arvores(i);

	inserir_dado_no_filho_se_nao_houver(raiz->esq, i);

	*i += 2;		
	guardar_dados(raiz, *i, *i); //guarda sinal de operação

	*i += 2;
	raiz->dir = criar_arvore_e_sub_arvores(i);
	
	inserir_dado_no_filho_se_nao_houver(raiz->dir, i);
	*i += 2;
	return raiz;
}

p_no criar_folha() {
	p_no raiz = criar_arvore(NULL, NULL);

	int i = 0;
	percorre_numeros(&i);
	guardar_dados(raiz, 0, i);

	return raiz;
}

int main() {
	int m;

	scanf("%d ", &m);

	for (int contador = 0; contador < m; contador++) {
		scanf("%m[^\n]%*c", &buffer);
		
		printf("%s", buffer); //TODO - remover esse print depois
		int i = 0;

		p_no raiz = NULL;
		if (buffer[i] == '(') {
			i += 2;
			raiz = inserir_dados_na_arvore(&i);
		} else {
			raiz = criar_folha();
		}

		free(buffer);

		simplificar_expressao(raiz);

		printf("\n"); //TODO - remover esse \n depois

		inordem(raiz);

		destruir_arvore(raiz);

		printf("\n");
	}

	return EXIT_SUCCESS;
}
