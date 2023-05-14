#include <bits/stdc++.h>


struct galho{
    int dado;
    galho *asc; /*ascendente*/
    galho *esq; /*esquerda*/
    galho *dir; /*direita*/
    
    galho(void){
        asc = nullptr;
        esq = nullptr;
        dir = nullptr;
    }
};


class binaria{
    private:
        galho *cbc;
        size_t tamanho;

    public:
        binaria(void){
            cbc = new galho; //a raiz eh galho->esq
            cbc->dado = INT_MIN;
            tamanho = 0;
        }

        /*
        void inserir(int x){ //ptr pra ptr 
            galho **ptr = &raiz;
            while(*ptr != nullptr){
                if(x >= (*ptr)->dado){
                    ptr = &((*ptr)->dir);
                }
                else{ 
                    ptr = &((*ptr)->dir);
                }
            }

            *ptr = new galho;
            (*ptr)->dado = x;
        }
        */

        void inserir(int x){ // o ideal é usar ponteiro para ponteiro
            galho *ptr = cbc->dir;
            galho *ant = cbc;
            while(ptr != nullptr){
                ant = ptr;
                if(x >= ptr->dado){
                    ptr = ptr->dir;
                }
                else{ // x < ptr->dado
                    ptr = ptr->esq;
                }
            }

            ptr = new galho();
            ptr->dado = x;
            ptr->asc = ant;

            if(x >= ant->dado){
                ant->dir = ptr;
            }
            else{
                ant->esq = ptr;
            }

            tamanho++;
            //tira esse if else
        }

        galho *busca(int x){
            galho *ptr = cbc->dir;
            while(ptr != nullptr){
                if(ptr->dado == x){
                    return ptr;
                }

                if(x > ptr->dado){
                    ptr = ptr->dir;
                }

                else{/*x < ptr->dado*/
                    ptr = ptr->esq;
                }
            }

            return nullptr;
        }        


    private:
        void remove_incompleto(galho *rem){
            galho *ant = rem->asc;
            galho **ordem_rem; //sucessor esquerdo ou direito de asc
            
            if(rem->dado >= ant->dado){ //rem eh sucessor direito
                ordem_rem = &(ant->dir); 
            }
            else{ //rem eh sucessor esquerdo
                ordem_rem = &(ant->esq);
            }

            //se for uma folha
            if(rem->esq == nullptr && rem->dir == nullptr){
                *ordem_rem = nullptr;
                delete rem;
                return;
            }

            //else
            //achamos o sucessor unico
            galho *suc;
            if(rem->esq != nullptr){
                suc = rem->esq;
            }
            else{//rem->dir != nullptr
                suc = rem->dir;
            }

            *ordem_rem = suc;
            delete rem;
            return;

        }

        void remove_completo(galho *rem){//remover elemento com 2 sucessores
            // olha pra o menor sucessor da direita
            galho *ptr = rem->dir;
            while(ptr->esq != nullptr){
                ptr = ptr->esq;
            }

            rem->dado = ptr->dado;
            remove_incompleto(ptr);
        }

    public:
        void remove(galho *rem){
            if(rem->esq != nullptr && rem->dir != nullptr){
                remove_completo(rem);
            }
            else{
                remove_incompleto(rem);
            }

            return;
        }
};


int main(void){
    binaria arvore;
    arvore.inserir(10);
    arvore.inserir(5);
    arvore.inserir(11);
    arvore.inserir(3);
    arvore.inserir(9);

    galho *t = arvore.busca(5);
    arvore.remove(t);
    
    
    std::cout << "Valor de t : " << t->dado << std::endl;

    return 0;
}
