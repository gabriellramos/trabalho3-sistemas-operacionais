//descrição
#include <stdio.h>
#include <stdlib.h>
#define N 8

void ordena(int *array){
	int i, j, menor, aux;
	
	for (i=0;i<N;i++){
		menor=i;
		for (j=i+1;j<N-1; j++)
			if (array[j]<array[menor])
				menor = j;
				
		if (menor!= i){
			aux = array[i];
			array[i] = array[menor];
			array[menor] = aux;
		}
	}	
}

void iniciaAlocacao(int *array){
	int i;
	for (i = 0; i<N; i++)
		array[i] = -1;
}

void inicializaDisperdicado(int *particoes, int *disperdicado){
	int i;
	for (i=0;i<N;i++)
		disperdicado[i] = particoes[i];
}

void imprimeMemoria(int *particoes, int *alocacao, int *disperdicado){
	int i;
	printf ("-----------------------------------------------------\n");
	printf ("%15s", "PARTICAO");
	for (i=0;i<N;i++){
		printf ("%6d", particoes[i]);
	}
	printf ("\n%15s", "ALOCACADO");
	for (i=0;i<N;i++)
		printf ("%6d", alocacao[i]);
	printf ("\n%15s", "DISPERDICADO");
	for (i=0;i<N;i++)
		printf ("%6d", disperdicado[i]);
		
	printf ("\n%15s","");
	for (i=0;i<N;i++)
		printf ("%6s", "^");
	printf ("\n%15s","");
	for (i=0;i<N;i++)
		printf ("%6s", "|");
	printf ("\n%15s","INDICE");
	for (i=0;i<N;i++)
		printf ("%6d", i);
	
	printf ("\n-----------------------------------------------------\n");
}

void firstFit(int *particoes, int *alocacao, int *disperdicado, int *casos, int tamCasos){
	int i, j, k=0, aloca;
	
	for (j=0;j<tamCasos; j++){
		aloca=0;
		for (i=0;i<N;i++){
			if (casos[j] <= disperdicado[i]){
				printf ("Aloca %d na particao %d\n", casos[j], i);
				aloca=1;
				alocacao[i] = alocacao[i] == -1 ? casos[j] : (alocacao[i] + casos[j]);
				disperdicado[i] = disperdicado[i] - casos[j];
				break;	
			}
		}
	
		if (!aloca) 
			printf ("Nao foi possivel alocar o processo %d\n", casos[j]);
		
	}
}

void bestFit(int *particoes, int *alocacao, int *disperdicado, int *casos, int tamCasos){
	int i, j, menor=-1, aux, pos, aloca;
	
	for (j=0;j<tamCasos;j++){
		aloca = 0;
		for (i=0;i<N;i++)
			if (casos[j] <= disperdicado[i]){
				menor = disperdicado[i] - casos[j];
				pos = i;
				break;
			}
		
		for (i=pos+1;i<N;i++)
			if (casos[j] <= disperdicado[i]){
				aux = disperdicado[i] - casos[j];
				if (aux < menor){
					menor = aux;
					pos = i;
				}
			}
		if (menor!=-1){
			alocacao[pos] = alocacao[pos] == -1 ? casos[j] : (alocacao[pos] + casos[j]);
			disperdicado[pos] = disperdicado[pos] - casos[j];
			printf ("Aloca %d na particao %d\n", casos[j], pos);
		}else
			printf ("Nao foi possivel alocar o processo %d\n", casos[j]);
		
	}
}

void worstFit(int *particoes, int *alocacao, int *disperdicado, int *casos, int tamCasos){
	int i, j, maior=-1, aux, pos;
	
	for (j=0;j<tamCasos;j++){
		
		for (i=0;i<N;i++)
			if (casos[j] <= disperdicado[i]){
				maior = disperdicado[i] - casos[j];
				pos = i;
				break;
			}
		
		for (i=pos+1;i<N;i++)
			if (casos[j] <= disperdicado[i]){
				aux = disperdicado[i] - casos[j];
				if (aux >= maior){
					maior = aux;
					pos = i;
				}
			}
			
		if (maior!=-1){
			alocacao[pos] = alocacao[pos] == -1 ? casos[j] : (alocacao[pos] + casos[j]);
			disperdicado[pos] = disperdicado[pos] - casos[j];
			printf ("Aloca %d na particao %d\n", casos[j], pos);
		}else
			printf ("Nao foi possivel alocar o processo %d\n", casos[j]);
			
		maior = -1;
		
	}
}

void nextFit(int *particoes, int *alocacao, int *disperdicado, int *casos, int tamCasos){
	int i=0, j, pos, alocou=0;
	pos = 0;
	
	for (j=0;j<tamCasos; j++){
		alocou = 0;
		for (i=pos;i<N;i++){
			if (casos[j] <= disperdicado[i]){
				printf ("Aloca %d na particao %d\n", casos[j], i);
				alocou=1;
				pos = i;
				alocacao[i] = alocacao[i] == -1 ? casos[j] : (alocacao[i] + casos[j]);
				disperdicado[i] = disperdicado[i] - casos[j];
				break;	
			}
		}
			
		if (pos == N-1) pos = 0;
		
		if (!alocou)
			printf ("Nao foi possivel alocar o processo %d\n", casos[j]);
		
	}
	
}


int main(){
	int particoes[] = {10,4,20,18,7,9,12,13};
	int alocacao[N];
	int disperdicado[N];
	int casos[] = {5,10,15,8,9,7,6};
	iniciaAlocacao(alocacao);
	inicializaDisperdicado(particoes,disperdicado);
	
	
	printf ("ALOCACAO DE MEMORIA USANDO ESTRATEGIA FIRST-FIT\n");
	firstFit(particoes,alocacao,disperdicado,casos,7);
	imprimeMemoria(particoes,alocacao,disperdicado);
	iniciaAlocacao(alocacao);
	inicializaDisperdicado(particoes,disperdicado);
	
	printf ("\n\nALOCACAO DE MEMORIA USANDO ESTRATEGIA BEST-FIT\n");
	bestFit(particoes,alocacao,disperdicado,casos,7);
	imprimeMemoria(particoes,alocacao,disperdicado);
	iniciaAlocacao(alocacao);
	inicializaDisperdicado(particoes,disperdicado);
	
	printf ("\n\nALOCACAO DE MEMORIA USANDO ESTRATEGIA WORST-FIT\n");
	worstFit(particoes,alocacao,disperdicado,casos,7);
	imprimeMemoria(particoes,alocacao,disperdicado);
	iniciaAlocacao(alocacao);
	inicializaDisperdicado(particoes,disperdicado);
	
	printf ("\n\nALOCACAO DE MEMORIA USANDO ESTRATEGIA NEXT-FIT\n");
	nextFit(particoes,alocacao,disperdicado,casos,7);
	imprimeMemoria(particoes,alocacao,disperdicado);
	iniciaAlocacao(alocacao);
	inicializaDisperdicado(particoes,disperdicado);
	
	return 0;
}

