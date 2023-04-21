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
    for(int i = 0; i < v->tam_interno; i++){
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

int at(struct vetor *v, int ind){
    if(ind < 0 || ind > v->tam_externo){
        //acesso fora
        return -1;
    }
    return *(v->data + ind);
}

//não precisa remover


int main(int argc, char* argv[]){
    int k = atoi(argv[2]);
    struct vetor v = init();
    int num;
    
    int counter = 0;
    while(!feof(stdin)){
        scanf("%d",&num);

        if(feof(stdin)) break;
        
        anexa(&v,num);
        counter++;
    }


    for(int i = 0; i < v.tam_externo; i++){
        printf("%d ",*(v.data + i));
    }
    printf("\n");

    printf("K = %d counter = %d \n", k,counter);

    return 0;
}

