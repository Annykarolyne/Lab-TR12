#include "heap.h"

/* Funcao para acessar, por meio do ponteiro, as variaveis da struct para a criaçao da heap */
HEAP* HEAP_create(int n, COMP* compara) {
	HEAP* heap = malloc(sizeof(HEAP));
	heap->elems = malloc(n * sizeof(void*));
	heap->N = n;
	heap->P = 0;
	heap->comparador = compara;

	return heap;
}
/* Funcao para adicionar o novo elemento na heap */
void HEAP_add(HEAP* heap, void* newelem){

	/* verifica se ha espaco na heap para adicionar o novo elemento */
	if(heap->P < heap->N){
		heap->elems[heap->P] = newelem; // adiciona na ultima posicao vaga da heap
		int posicao = heap->P;

		/* enquanto o novo elemento for menor do que o elemento 
		anterior dividido por dois, vai ocorrer uma reordenacao */
		while(heap->comparador(heap->elems[posicao], heap->elems[(posicao - 1) / 2]) > 0){
			void* aux = heap->elems[posicao];
			heap->elems[posicao] = heap->elems[(posicao - 1) / 2]; // ordenação
			heap->elems[(posicao - 1) / 2] = aux;	
			posicao = (posicao - 1) / 2;
		}	
	heap->P++; // aumenta o numero de elementos 
	}
}
/* Funcao para remover */
void* HEAP_remove(HEAP* heap){

	void* min = heap->elems[0];

	heap->elems[0] = heap->elems[heap->P - 1]; // primeira posicao recebe o ultimo elemento
	heap->elems[heap->P - 1] = min; // ultima posicao recebe o primeiro elemento
	
	heap->P--; // diminui o numero de elementos 

	int pai = 0;
	int filho = pai * 2 + 1;
	
	while(filho < heap->P){ 

		if(filho + 1 < heap->P){

			/* compara se o filho atual eh maior do que o proximo filho. Se for, atualiza o filho atual para o proximo */
			if(heap->comparador(heap->elems[filho], heap->elems[filho + 1]) < 0){
				filho += 1;
			}
		}
		/* compara se o pai eh maior do que o filho. Se for, reordena */
		if(heap->comparador(heap->elems[pai], heap->elems[filho]) < 0){
			void* aux = heap->elems[pai];
			heap->elems[pai] = heap->elems[filho]; // ordenacao
			heap->elems[filho] = aux;

			pai = filho;
			filho = pai * 2 + 1;

		/* se nao, atualiza o filho para sair do while */
		}else{
			filho = heap->P + 1;
		}
	}
	return min; // retorna ponteiro para o elemento removido
}