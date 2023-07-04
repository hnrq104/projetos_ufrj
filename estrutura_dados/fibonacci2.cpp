#include <bits/stdc++.h>

struct fruta{
    double chave;
    int ordem;
    bool marca;

    fruta* semente;
    fruta* galho;
    fruta* prox;
    fruta* ant;

    fruta(double c){
        chave = c;
        ordem = 0;
        semente = nullptr;
        galho = nullptr;
        prox = nullptr;
        ant = nullptr;
        marca = false;
    }
};


struct fibonacci{
    fruta* min;
    std::vector<fruta*> arvores;

    fibonacci(){
        min = nullptr;
    }

    fruta* subjuga(fruta* a, fruta* b){
        fruta* dom;
        fruta* sub;

        if(a->chave < b->chave){
            dom = a;
            sub = b;
        }

        else{
            dom = b;
            sub = a;
        }

        sub->galho = dom;
        if(dom->semente != nullptr){
            dom->semente->ant = sub;
        }
        sub->prox = dom->semente;
        sub->ant = nullptr;
        dom->semente = sub;
        
        dom->ordem++;
        sub->marca = false;

        return dom;
    }

    fruta* insere_arvore(fruta* a){
        
        a->ant = nullptr;
        a->prox = nullptr;
        a->galho = nullptr;

        if(min == nullptr){
            arvores.push_back(a);
            min = a;
            return a;
        }

        if(a->chave < min->chave){
            min = a;
        }

        size_t i;
        fruta* ptr = a;
        for(i = a->ordem; i < arvores.size(); i++){
            ptr->marca = true;
            if(arvores.at(i) == nullptr){
                arvores.at(i) = ptr;
                break;
            }
            ptr = subjuga(ptr,arvores.at(i));
            arvores.at(i) = nullptr;
        }
        if(i == arvores.size()){
            arvores.push_back(ptr);
        }

        return ptr;
    }

    double extrai_min(void){
        if(min == nullptr) throw std::runtime_error("min = nullptr");
        double ret = min->chave;
        arvores.at(min->ordem) = nullptr;
        std::vector<fruta*> lista;
        fruta* ptr = min->semente;

        while(ptr!=nullptr){
            lista.push_back(ptr);
            ptr = ptr->prox;
        }

        for(size_t i = 0; i < lista.size(); i++){
            insere_arvore(lista.at(i));
        }

        double menor = MAXFLOAT;
        for(size_t i = 0; i < arvores.size(); i++){
            if(arvores.at(i) != nullptr && arvores.at(i)->chave < menor){
                menor = arvores.at(i)->chave;
                min = arvores.at(i);
            }
        }

        return ret;
    }

    void diminui_prioridade(fruta* a, double n){
        if(a == nullptr || n > a->chave) return;
        a->chave = n;
        if(a->galho == nullptr){
            return;
        }
        
        fruta* ptr = a;
        fruta* g = ptr->galho;
        while(g != nullptr){

            // if(ptr->ant == nullptr){
            //     g->semente = ptr->prox;
            //     if(g->semente)
            //     g->semente->ant = nullptr;
            // }
            // else{
            //     ptr->ant->prox = ptr->prox;
            //     ptr->prox->ant = ptr->ant;
            // }

            if(ptr->ant == nullptr){
                g->semente = ptr->prox;
            }

            else{

                if(ptr->prox != nullptr){
                    ptr->prox->ant = ptr->ant;
                }
                ptr->ant->prox = ptr->prox;
            }

            insere_arvore(ptr);

            g->ordem--;
            if(g->marca == false){
                g->marca = true;
                break;
            }
            ptr = g;
            g = g->galho;
        }

        if(g == nullptr){
            arvores.at(ptr->ordem + 1) = nullptr;
            insere_arvore(ptr);
        }
    }

};
void printa(fruta* a){
    std::cout<< "'" << a->chave << "'";
    if(a->semente!=nullptr){
        std::cout << "(";
        fruta* ptr = a->semente;
        while(ptr!=nullptr){
            printa(ptr);
            ptr=ptr->prox;
        }
        std::cout<<")";
    }
}

int main(void){
    fibonacci f;
    fruta* ptr10 = new fruta(10);
    f.insere_arvore(new fruta(9));
    f.insere_arvore(new fruta(4));
    f.insere_arvore(new fruta(7));
    f.insere_arvore(new fruta(3));
    f.insere_arvore(ptr10);
    // f.insere_arvore(new fruta(25));
    // f.insere_arvore(new fruta(15));
    // f.insere_arvore(new fruta(11));
    // f.insere_arvore(new fruta(80));
    std::cout << f.extrai_min() << std::endl;
    std::cout << f.extrai_min() << std::endl;
    
    f.diminui_prioridade(ptr10,0);
    for(size_t i = 0; i < f.arvores.size(); i++){
        if(f.arvores.at(i) == nullptr){
            std::cout << "null" << std::endl;
        }
        else{
            printa(f.arvores.at(i));
            std::cout << std::endl;
        }
    }



    return 0;
}