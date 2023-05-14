#include <bits/stdc++.h>

/* copia de frutas */

struct fruta{
    struct fruta *esq;
    struct fruta *dir;

    int data; // = hesq - hdir
    int frutas_esquerdas;


    fruta(int d){
        data = d;
    }
};




//rotacoes

void rotacao_dir(struct fruta* &pt_a){
    struct fruta *pt_b = pt_a->esq;
    pt_a->esq = pt_b->dir;
    pt_b->dir = pt_a;

    //referencia
    pt_a = pt_b;
    pt_a->data = 0;
}

void rotacao_esq(struct fruta* &pt_a){
    struct fruta *pt_b = pt_a->dir;
    pt_a->dir = pt_b->esq;
    pt_b->esq = pt_a;

    //por referencia
    pt_a = pt_b;
    pt_a->data = 0;

}

/*
void rotacao_esq_dir(struct fruta* &pt_a){
    rotacao_esq(pt_a->esq);
    rotacao_dir(pt_a);
}
*/



//nullptr alt = 0;
char insere(struct fruta* &p_fruta, int k){
    if(p_fruta == nullptr){
        p_fruta = new fruta(k);
        p_fruta->esq = nullptr;
        p_fruta->dir = nullptr;
        //esq = null, dir = null logo data = 0
        p_fruta->data = 4;
        
        return 0;
    }
    int valor = p_fruta->data;
    
    char antigo; //3 bit significa q altura mudou, 2-1 bit é o caminho
    char direcao;
    

    if(k < p_fruta->data){
        antigo = insere(p_fruta->esq,k);
        direcao = 1; //esq
    }
    
    else{ 
        antigo = insere(p_fruta->dir, k);
        direcao = 0;//dir
    }

    //3 bit vivo
    if(antigo && 4){
        if(direcao){
            p_fruta->data++;
        } 
        else{
            p_fruta->data--;
        }
    }

    //ou tá desbalanceado e rotaciona
    // ou ta ok e cresceu. ou ta ok e nao cresceu

    if(p_fruta->data < -1 || p_fruta->data > 1){
        // casos
    }



}