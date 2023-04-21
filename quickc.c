#include <stdio.h>
#include <stdlib.h>


typedef struct vetor{
    int tam_interno;
    int tam_externo;
    int *data;
}vetor;

struct vetor init(void){
    struct vetor v;
    v.tam_interno = 10;
    v.tam_externo = 0;
    v.data = malloc(sizeof(int) * v.tam_interno);

    return v;
}

void overflow(struct vetor *v){
    int *ptr = malloc(2*sizeof(int)*(v->tam_externo));
    int i;
    for(i = 0; i < v->tam_interno; i++){
        *(ptr+i) = *(v->data + i); 
    }

    free(v->data);
    v->data = ptr;
    v->tam_interno *= 2;
    return;
}

void anexa(struct vetor *v, int x){
    *(v->data + v->tam_externo) = x;
    v->tam_externo++;

    if(v->tam_interno - v->tam_externo < 2){
        overflow(v);
    }

    return;
}

int at(struct vetor *v, int ind){ //retorna por referencia
    if(ind < 0 || ind > v->tam_externo){
        //acesso fora
        return -1;
    }
    return *(v->data + ind);
}



//não precisa remover


int particiona(vetor *v, int inicio, int fim){
    // particiona no meio por enquanto
    int meio = (inicio + fim)/2;
    int pivot = at(v,meio);
    //troca pivot com inicio

    *(v->data + meio) = *(v->data + inicio);
    *(v->data + inicio) = pivot;

    int i = inicio + 1; // indice do inicio
    int j = fim - 1 ; // indice do final

    while(i<=j){
        while(i < fim && *(v->data + i) <= pivot){
            i++;
        }

        while(j > inicio && *(v->data + j) >= pivot){
            j--;
        }

        if(i < j){
            int tmp = *(v->data + i);
            *(v->data + i) = *(v->data + j);
            *(v->data + j) = tmp;
        }
    }

    //troca pivot com posição encontrada
    int tmp = *(v->data + i - 1);
    *(v->data + i - 1) = pivot;
    *(v->data + inicio) = tmp;

    return i-1;
}

int quick_select(struct vetor *v, int inicio, int fim, int k){
    int pos = particiona(v,inicio,fim);
    if(pos == k){
        return *(v->data + pos);
    }

    if(pos > k){
        return quick_select(v,inicio,pos,k);
    }

    else{ // pos < k
        return quick_select(v,pos,fim,k);
    }
}


int main(int argc, char* argv[]){
    int k = atoi(argv[2]);
    struct vetor v = init();
    int num;
    
    while(!feof(stdin)){
        scanf("%d",&num);

        if(feof(stdin)) break;        
        anexa(&v,num);

    }

    printf("%d", quick_select(&v,0,v.tam_externo,k));

    return 0;
}

