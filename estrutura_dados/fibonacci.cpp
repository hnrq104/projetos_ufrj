#include <bits/stdc++.h>

struct node{
    bool marca;
    double chave;
    int ordem;
    int pos;
    
    node* anterior;
    std::vector<node*> sucessores;

    node(){
        ordem = 0;
        marca = false;
        anterior = nullptr;
    }

};

struct fibonacci{
    node* min;
    std::vector<node*> arvores;

    fibonacci(){
        min = nullptr;
    }

    node* subjuga(node* a, node* b){
        node* dominante;
        node* subjugado;
        if(a->chave < b->chave){
            dominante = a;
            subjugado = b;
        }
        else{
            dominante = b;
            subjugado = a;
        }
        subjugado->anterior = dominante;
        subjugado->marca = false;
        dominante->sucessores.push_back(subjugado);
        subjugado->pos = dominante->sucessores.size() - 1;
        dominante->ordem++;
        return dominante;
    }

    node* insere(double n){
        node* novo = new node;
        novo->chave = n;
        if(min == nullptr || n < min->chave){
            min = novo;
        }

        if(arvores.size() == 0){
            arvores.push_back(novo);
            return novo;
        }
        
        size_t i;
        for(i = 0; i < arvores.size(); i++){
            novo->marca = true;
            if(arvores.at(i) == nullptr){
                arvores.at(i) = novo;
                break;
            }
            novo = subjuga(novo,arvores.at(i));
            arvores.at(i) = nullptr;
        }

        if(i == arvores.size()){
            arvores.push_back(novo);
        }

        novo->pos = i;
        return novo;
    }

    node* insere_arvore(node* a){
        node* novo = a;
        novo->anterior = nullptr;

        size_t i;
        for(i = a->ordem; i < arvores.size(); i++){
            novo->marca = true;
            if(arvores.at(i) == nullptr){
                arvores.at(i) = novo;
                break;
            }
            novo = subjuga(novo,arvores.at(i));
            arvores.at(i) = nullptr;
        }

        if(i == arvores.size()){
            arvores.push_back(novo);
        }

        novo->pos = i;
        return novo;
    }

    double extrai_min(void){
        if(min == nullptr){
            throw std::runtime_error("heap vazia");
        }

        double extraida = min->chave;
        arvores.at(min->ordem) = nullptr;
        for(size_t i = 0; i < min->sucessores.size(); i++){
            node* ptr = min->sucessores.at(i);
            if(ptr!=nullptr) insere_arvore(ptr);
        }
        delete min;
        min = nullptr;
        double menor = MAXFLOAT;
        for(size_t i = 0; i < arvores.size(); i++){
            if(arvores.at(i) != nullptr && arvores.at(i)->chave < menor){
                min = arvores.at(i);
                menor = arvores.at(i)->chave;
            }
        }

        return extraida;
    }

    node* diminui_prioridade(node* a, double n){
        if(a->chave <= n){
            return a; //not diminishing
        }

        a->chave = n;
        if(n < min->chave){
            min = a;
        }

        if(a->anterior == nullptr) return a; //don't have to do anything

        //terrible idea, will have to look up which position it is in the previous vector,
        // a way to change this, is to keep track of where it was inserted. (boring)
        // will spend a lot of memory doing this but it will be easier

        
        node* ptr = a;
        while(ptr->anterior != nullptr){
            node* ant = ptr->anterior;
            ant->sucessores.at(ptr->pos) = nullptr;
            ant->ordem--;
            insere_arvore(ptr);
            if(ant->marca == false){
                ant->marca = true;
                break;
            }
            ptr = ant;
        }

        if(ptr->anterior == nullptr){
            //chegou na raiz;
            arvores.at(ptr->ordem + 1) = nullptr;
            insere_arvore(ptr);
        }

        return a;
    }
};

void printa_arvore(node* a){
    std::cout << "'"<< a->chave << "'";
    if(a->sucessores.size()!= 0){
        std::cout << "(";
        for(size_t i = 0; i < a->sucessores.size(); i++){
            if(a->sucessores.at(i) != nullptr){
                printa_arvore(a->sucessores.at(i));
            }
        }
        std::cout << ")";
    }
}

int main(void){
    fibonacci heap;
    node* ptr10 = heap.insere(10);
    std::cout << "min = " << heap.min->chave << std::endl;
    node* ptr4 = heap.insere(4);
    std::cout << "min = " << heap.min->chave << std::endl;
    heap.insere(7);
    std::cout << "min = " << heap.min->chave << std::endl;
    heap.insere(8);
    std::cout << "min = " << heap.min->chave << std::endl;
    heap.insere(15);
    std::cout << "min = " << heap.min->chave << std::endl;
    return 0;
}