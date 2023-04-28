#include <bits/stdc++.h>

template<typename T>
class no{
    public:
        T data;
        no *ant;
        no* prox;

        no(T d){
            data = d;
        }

        no(T d, no* anterior, no* proximo){
            data = d;
            ant = anterior;
            prox = proximo;
        }        
};

template<typename T>
class lista{
    public:
        no<T> *ptlista;

        lista(){
            ptlista = nullptr;
        }

        no<T> *busca(T x){
            no<T> *pt = ptlista;
            if(pt == nullptr) return pt;

            if(pt->data >= x){
                return pt;
            }

            pt = pt->prox;
            while(pt != ptlista &&  pt->data < x){
                pt = pt->prox;
            }
            return pt;
        }

        void insere(T x){
            if(ptlista == nullptr){
                no<T> *pt = new no(x);
                ptlista = pt;
                ptlista->ant = ptlista;
                ptlista->prox = ptlista;
                return;
            }

            no<T> *pt_b = busca(x);
            no<T> *ant = pt_b->ant;
            no<T> *novo = new no(x);

            ant->prox = novo;

            novo->ant = ant;
            novo->prox = pt_b;
            
            pt_b->ant = novo;
        }

        void remove(T x){
            no<T> *pt = busca(x);
            if(pt == nullptr){
                return;
            }

            if(pt->data != x){
                return;
            }

            pt->ant = pt->prox;
            pt->prox->ant = pt->ant;

            delete pt;
            pt = nullptr;
        }

};

int main(void){
    lista<int> l;

    for(int i = 0; i < 10; i++){
        l.insere(i);
    }

    no<int> *ptr = l.ptlista;
    for(int i = 0; i < 20; i++){
        std::cout << ptr->data << " ";
        ptr = ptr->prox;
    }
    std::cout << std::endl;

    return 0;
}