#include <bits/stdc++.h>

/*por mais elegante e curto que estejam as funções,
esse programa é de difícil entendimento, está completamente
baseado em recursões e referências*/

struct fruta{
    struct fruta *esq;
    struct fruta *dir;

    int data;
    int frutas_esquerdas;


    fruta(int d){
        data = d;
    }
};

struct fruta* &busca(struct fruta* &p_arvore, int b){
    if(p_arvore == nullptr || p_arvore->data == b){
        return p_arvore;
    }

    if(b < p_arvore->data){
        return busca(p_arvore->esq,b);
    }

    else{ // b > p_arvore->data
        return busca(p_arvore->dir,b);
    }
}

void insere(struct fruta* &p_arvore, int b){
    if(p_arvore == nullptr){
        p_arvore = new struct fruta(b);
        p_arvore->frutas_esquerdas = 0;

        return;
    }

    if(b < p_arvore->data){
        insere(p_arvore->esq,b);
        p_arvore->frutas_esquerdas++;
    }

    else{ //b >= p_arvore->data
        insere(p_arvore->dir,b);
    }
}

struct fruta* &menor_fruta(struct fruta* &p_arvore){
    if(p_arvore->esq == nullptr){
        return p_arvore;
    }
    return menor_fruta(p_arvore->esq);
}

void remover(struct fruta* &p_arvore){
    if(p_arvore == nullptr){
        return; //nada a remover
    }

    /*casos bons tem 0 ou 1 filhos*/
    int sucessores = 0;
    struct fruta* suc = nullptr;

    if(p_arvore->esq != nullptr){
        suc = p_arvore->esq;
        sucessores++;
    }
    if(p_arvore->dir != nullptr){
        suc = p_arvore->dir;
        sucessores++;
    }

    if(sucessores <= 1){
        //caso bom
        delete p_arvore;
        p_arvore = suc;

        return;
    }
    
    //caso ruim, tem dois sucessores
    struct fruta* &prox = menor_fruta(suc);
    p_arvore->data = prox->data;
    remover(prox);
    
    return;
}

void print_em_ordem(struct fruta* ptr){
    if(ptr == nullptr){
        return;
    }

    print_em_ordem(ptr->esq);
    std::cout << ptr->data << " ";
    print_em_ordem(ptr->dir);
}

// struct fruta* &select(struct fruta* &p_arvore, int i){
    
// }


int main(void){
    struct fruta* salada = nullptr;
    insere(salada,5);
    insere(salada,3);
    insere(salada,7);
    insere(salada,6);
    insere(salada,4);
    insere(salada,1);
    insere(salada,2);
    insere(salada,8);


    remover(busca(salada,2));
    print_em_ordem(salada);
    std::cout << std::endl;

    std::cout <<salada->frutas_esquerdas << std::endl;
    return 0;
}







