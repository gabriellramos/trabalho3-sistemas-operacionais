//descrição
#include <stdio.h>
#include <stdlib.h>
#define N 8

void ordena(int *array){
	int i, j, menor, aux;
	
	for (i=0;i<N;i++){
		menor=i;
		for (j=i+1;j<N; j++)
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

void inicializaDesperdicado(int *particoes, int *desperdicado){
	int i;
	for (i=0;i<N;i++)
		desperdicado[i] = particoes[i];
}

void imprimeMemoria(int *particoes, int *alocacao, int *desperdicado){
	int i;
	printf ("-----------------------------------------------------\n");
	printf ("%15s", "TAM. PARTICAO");
	for (i=0;i<N;i++){
		printf ("%6d", particoes[i]);
	}
	printf ("\n%15s", "ALOCACADO");
	for (i=0;i<N;i++)
		printf ("%6d", alocacao[i]);
	printf ("\n%15s", "DESPERDICADO");
	for (i=0;i<N;i++)
		printf ("%6d", desperdicado[i]);
		
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

void firstFit(int *particoes, int *alocacao, int *desperdicado, int *casos, int tamCasos){
	int i, j, k=0, aloca;
	
	for (j=0;j<tamCasos; j++){
		aloca=0;
		for (i=0;i<N;i++){
			if (casos[j] <= desperdicado[i]){
				printf ("Aloca %d na particao %d\n", casos[j], i);
				aloca=1;
				alocacao[i] = alocacao[i] == -1 ? casos[j] : (alocacao[i] + casos[j]);
				desperdicado[i] = desperdicado[i] - casos[j];
				break;	
			}
		}
	
		if (!aloca) 
			printf ("Nao foi possivel alocar o processo %d\n", casos[j]);
		
	}
}

void bestFit(int *particoes, int *alocacao, int *desperdicado, int *casos, int tamCasos){
	int i, j, menor=-1, aux, pos, aloca;
	
	for (j=0;j<tamCasos;j++){
		aloca = 0;
		for (i=0;i<N;i++)
			if (casos[j] <= desperdicado[i]){
				menor = desperdicado[i] - casos[j];
				pos = i;
				break;
			}
		
		for (i=pos+1;i<N;i++)
			if (casos[j] <= desperdicado[i]){
				aux = desperdicado[i] - casos[j];
				if (aux < menor){
					menor = aux;
					pos = i;
				}
			}
		if (menor!=-1){
			alocacao[pos] = alocacao[pos] == -1 ? casos[j] : (alocacao[pos] + casos[j]);
			desperdicado[pos] = desperdicado[pos] - casos[j];
			printf ("Aloca %d na particao %d\n", casos[j], pos);
		}else
			printf ("Nao foi possivel alocar o processo %d\n", casos[j]);
		
	}
}

void worstFit(int *particoes, int *alocacao, int *desperdicado, int *casos, int tamCasos){
	int i, j, maior=-1, aux, pos;
	
	for (j=0;j<tamCasos;j++){
		
		for (i=0;i<N;i++)
			if (casos[j] <= desperdicado[i]){
				maior = desperdicado[i] - casos[j];
				pos = i;
				break;
			}
		
		for (i=pos+1;i<N;i++)
			if (casos[j] <= desperdicado[i]){
				aux = desperdicado[i] - casos[j];
				if (aux >= maior){
					maior = aux;
					pos = i;
				}
			}
			
		if (maior!=-1){
			alocacao[pos] = alocacao[pos] == -1 ? casos[j] : (alocacao[pos] + casos[j]);
			desperdicado[pos] = desperdicado[pos] - casos[j];
			printf ("Aloca %d na particao %d\n", casos[j], pos);
		}else
			printf ("Nao foi possivel alocar o processo %d\n", casos[j]);
			
		maior = -1;
		
	}
}

void nextFit(int *particoes, int *alocacao, int *desperdicado, int *casos, int tamCasos){
	int i=0, j, pos, alocou=0;
	pos = 0;
	
	for (j=0;j<tamCasos; j++){
		alocou = 0;
		for (i=pos;i<N;i++){
			if (casos[j] <= desperdicado[i]){
				printf ("Aloca %d na particao %d\n", casos[j], i);
				alocou=1;
				pos = i;
				alocacao[i] = alocacao[i] == -1 ? casos[j] : (alocacao[i] + casos[j]);
				desperdicado[i] = desperdicado[i] - casos[j];
				break;	
			}
		}
			
		if (pos == N-1) pos = 0;
		
		if (!alocou)
			printf ("Nao foi possivel alocar o processo %d\n", casos[j]);
		
	}
	
}


int main(){
	int particoes[] = {10,4,20,18,7,9,12,15};
	int alocacao[N];
	int desperdicado[N];
	int casos[] = {12,10,9};
	ordena(particoes);
	iniciaAlocacao(alocacao);
	inicializaDesperdicado(particoes,desperdicado);
	
	
	printf ("ALOCACAO DE MEMORIA USANDO ESTRATEGIA FIRST-FIT\n");
	firstFit(particoes,alocacao,desperdicado,casos,3);
	imprimeMemoria(particoes,alocacao,desperdicado);
	iniciaAlocacao(alocacao);
	inicializaDesperdicado(particoes,desperdicado);
	
	printf ("\n\nALOCACAO DE MEMORIA USANDO ESTRATEGIA BEST-FIT\n");
	bestFit(particoes,alocacao,desperdicado,casos,3);
	imprimeMemoria(particoes,alocacao,desperdicado);
	iniciaAlocacao(alocacao);
	inicializaDesperdicado(particoes,desperdicado);
	
	printf ("\n\nALOCACAO DE MEMORIA USANDO ESTRATEGIA WORST-FIT\n");
	worstFit(particoes,alocacao,desperdicado,casos,3);
	imprimeMemoria(particoes,alocacao,desperdicado);
	iniciaAlocacao(alocacao);
	inicializaDesperdicado(particoes,desperdicado);

	return 0;
}

