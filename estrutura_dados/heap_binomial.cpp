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

    /*lembrar que preservamos a preservamos a próxima de b*/
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

    fruta* diminui_chave(fruta* ptr, float n){
        if(ptr->chave > n){
            /*operacao invalida*/
            return ptr;
        }

        ptr->chave = n;

        while(ptr->ant != nullptr && ptr->ant->chave > n){
            ptr->chave = ptr->ant->chave;
            ptr->ant->chave = n;
            ptr = ptr->ant;
        }
    }

    float extrai_minimo(void){
        if(saladas == nullptr){
            throw std::runtime_error("nada na heap");
        }

        fruta* extraido = min;

        float r = extraido->chave;
        fruta* sem_galho = extraido->sub;
        fruta* desconectado = extraido->prox;
        delete extraido;


        
        std::vector<fruta*> apatridas; //esse vetor tá ao contrario
        fruta* minima = sem_galho;
        
        while(sem_galho != nullptr){
            if(sem_galho->chave < minima->chave) minima = sem_galho;

            fruta* tmp = sem_galho;
            apatridas.push_back(sem_galho);
            sem_galho = sem_galho->prox;
            tmp->ant = nullptr;
            tmp->prox = nullptr;
        }

        int tam = apatridas.size();
        std::vector<fruta*> arvores(tam + 1);
        fruta* ptr = saladas;
        for(int ordem = 0; ordem < tam + 1; ordem++){
            if(ptr->ordem == ordem){
                
                if(ptr->chave < minima->chave) minima = ptr;
                
                arvores.at(ordem) = ptr;
                ptr = ptr->prox;
            }
            else{
                arvores.at(ordem) = nullptr;
            }
        }
        
        for(int ordem = 0; ordem < tam; ordem++){
            fruta* a = apatridas.at(tam - ordem - 1);
            
            int i = 0;
            while(arvores.at(ordem + i) != nullptr){
                a = mistura_salada(a,arvores.at(ordem + i));
                arvores.at(ordem + i) = nullptr;
                i++;
            }

            arvores.at(ordem + i) = a;
        }

        fruta* prato = nullptr;
        size_t i = 0;
        while(arvores.at(i) == nullptr) i++;
        prato = arvores.at(i);
        saladas = prato;

        for(i = i+1; i < arvores.size() ; i++){
            if(arvores.at(i) != nullptr){
                prato->prox = arvores.at(i);
                prato = prato->prox;
            }
        }

        prato->prox = desconectado;
        
        prato = desconectado;
        while(prato != nullptr){
            if(prato->chave < minima->chave){
                minima = prato;
            }
        }

        min = minima;
        return r;
    }
};


int main(void){
    floresta h;
    h.insere(10.0);
    h.insere(20.0);
    h.insere(7.0);
    h.insere(13.0);

    std::cout << "extrai h :"  << h.extrai_minimo() << std::endl;
    h.insere(30);
    std::cout << "extrai h :"  << h.extrai_minimo() << std::endl;
    
    h.insere(25);
    std::cout << "extrai h :"  << h.extrai_minimo() << std::endl;
    std::cout << "extrai h :"  << h.extrai_minimo() << std::endl;

    std::cout << "min h = " << h.min->chave << std::endl;


    return 0;
}