#include <bits/stdc++.h>

struct fruta{
    float chave;
    int ordem;
    fruta* ant;
    fruta* prox;
    fruta* sub;

    fruta(){
        ant = nullptr;
        prox = nullptr;
        sub = nullptr;
        ordem = 0;
    }
};

struct floresta{
    fruta* min;
    fruta* saladas;

    floresta(){
        saladas = nullptr; /*head*/
    }

    fruta* mistura_salada(fruta* a, fruta* b){
        fruta* menor;
        fruta* subjugada;
        fruta* proxima = b->prox;
        if(a->chave <= b->chave){
            menor = a;
            subjugada = b;
        }
        else{
            menor = b;
            subjugada = a;
        }

        subjugada->ant = menor;
        subjugada->prox = menor->sub;
        menor->sub = subjugada;
        menor->ordem++;
        
        menor->prox = proxima;
        return menor;
    }

    fruta* insere(float n){
        fruta* inserida = new fruta;
        inserida->chave = n;
        if(saladas == nullptr){
            saladas = inserida;
            min = inserida;
            return inserida;
        }

        // fruta* a = inserida;
        fruta* b = saladas;
        saladas = inserida;
        inserida->prox = b;

        while(b != nullptr && b->ordem == saladas->ordem){
            saladas = mistura_salada(saladas,b);
            // saladas = a;
            b = saladas->prox;
        }

        if(min->chave > n){
            min = inserida;
        }

        return inserida;
    }

};


void printa_fruta(fruta* ptr){
    std:: cout << "end = " << ptr;
    std::cout << " chave = " << ptr->chave;
    std::cout << " ordem = " << ptr->ordem;
    std::cout << " pai = " << ptr->ant;
    std:: cout << " filho = " << ptr->sub;
}
int main(void){
    floresta h;
    fruta* pt[5];
    pt[4] = h.insere(5.0);
    pt[3] = h.insere(4.0);
    pt[2] = h.insere(3.0);
    pt[0] = h.insere(1.0);
    pt[1] = h.insere(2.0);

    for(int i = 0; i < 5; i++){
        printa_fruta(pt[i]);
        std::cout << std::endl;
    }
    

    // fruta* ptr = h.saladas;
    // std::cout << h.min->chave << std::endl; 

    // while(ptr!= nullptr){
    //     std::cout << "chave :" << ptr->chave;
    //     std::cout << " ordem :" << ptr->ordem  << std::endl;

    //     ptr = ptr->prox;
    // }

    return 0;
}