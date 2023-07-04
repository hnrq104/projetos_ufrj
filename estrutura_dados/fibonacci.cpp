#include <bits/stdc++.h>

struct node{
    bool marca;
    double chave;
    int ordem;
    
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
};

void printa_arvore(node* a){
std::cout << "'"<< a->chave << "'";
    if(a->sucessores.size()!= 0){
        std::cout << "(";
        for(size_t i = 0; i < a->sucessores.size(); i++){
            printa_arvore(a->sucessores.at(i));
        }
        std::cout << ")";
    }
}

int main(void){
    fibonacci heap;
    heap.insere(10);
    std::cout << "min = " << heap.min->chave << std::endl;
    heap.insere(4);
    std::cout << "min = " << heap.min->chave << std::endl;
    heap.insere(7);
    std::cout << "min = " << heap.min->chave << std::endl;
    heap.insere(8);
    std::cout << "min = " << heap.min->chave << std::endl;
    heap.insere(15);
    std::cout << "min = " << heap.min->chave << std::endl;
    heap.insere(2);


    for(size_t i = 0; i < heap.arvores.size(); i++){
        if(heap.arvores.at(i) != nullptr){
            printa_arvore(heap.arvores.at(i));
            std::cout << std::endl;
        }
    }

    std::cout <<  heap.extrai_min() << std::endl;
    std::cout << "min = " << heap.min->chave << std::endl;


    for(size_t i = 0; i < heap.arvores.size(); i++){
        if(heap.arvores.at(i) != nullptr){
            printa_arvore(heap.arvores.at(i));
            std::cout << std::endl;
        }
    }

    return 0;
}