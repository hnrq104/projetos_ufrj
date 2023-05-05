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

//ToDo
/*implementar espertamente o remove, para que mantenha estrutura da arvore (FEITO)
implementar o select para arvore binaria de busca (FEITO) :)
*/

int remove_rec(struct fruta* &p_arvore, int r){
    /*casos base*/
    if(p_arvore == nullptr){
        return 0;
    }
    if(p_arvore->data == r){
        remover(p_arvore);
        return 1;
    }
    /*casos recursivos */
    if(r < p_arvore->data){
        if(remove_rec(p_arvore->esq,r)){
            p_arvore->frutas_esquerdas--;
            return 1;
        }
    }
    else{ //r > p_arvore -> data
        if(remove_rec(p_arvore->dir,r)){
            return 1;
        }
    }

    return 0; //nenhum elemento foi removido
}

int select(struct fruta *p_arvore, int k){
    if(p_arvore == nullptr){
        throw std::out_of_range("posicao invalida de select"); // erro posição invalida
    }

    if(k == p_arvore->frutas_esquerdas){
        return p_arvore->data;
    }

    if(k < p_arvore->frutas_esquerdas){
        return select(p_arvore->esq,k);
    }

    else{ //k > p_arvore->frutas_esquerda
        int relativa = k - (p_arvore->frutas_esquerdas + 1);
        return select(p_arvore->dir,relativa);
    }
}

int main(void){
    struct fruta* salada = nullptr;
    for(int i = 0; i < 1000000; i++){
        insere(salada,rand());
    }

    std::cout << "pos 0 "  << select(salada,500000) << std::endl;
    return 0;
}







