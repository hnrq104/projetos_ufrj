#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
vetor
*/
template<typename T>
class vetor{
    private:
        T* ponteiro;
        int alocado;
        int imaginario;

        void resize(){
            if(alocado - imaginario < 2){
                alocado*=2;
                T* novo = new T[alocado];
                for(int i = 0; i < imaginario; i++){
                    *(novo + i) = *(ponteiro + i);
                }
                delete[] ponteiro;
                ponteiro = novo;
            }
            return;
        }

    public:
        vetor(){
            alocado = 10;
            imaginario = 0;
            ponteiro = new T[alocado];
        }

        vetor(vetor& copia){
            alocado = copia.alocado;
            imaginario = copia.imaginario;
            ponteiro = new T[alocado];
            for(int i = 0; i < imaginario; i++){
                *(ponteiro + i) = *(copia.ponteiro + i);
            }
        }

        T &at(int i){
            return *(ponteiro + abs(i%imaginario)); /*não podemos usar exception*/
        }

        void anexa(T valor){
            *(ponteiro + imaginario) = valor;
            imaginario++;
            resize();
            return;
        }

        void remove(int index){
            if(index < 0 || index >= imaginario){
                //erro
                return;
            }
            
            imaginario--;
            for(int i = index; i < imaginario; i++){
                *(ponteiro + i) = *(ponteiro + i + 1); 
            }
            return;
        }

        int tam(){
            return imaginario;
        }
};

struct aresta{
    int a; //vertice 1
    int b; //vertice 2

    int pr; //prioridade
};

/*
heap
*/
class minheap{
    public:
        vetor<aresta> dados;

        int esq(int i){
            return (i<<1)+1;
        }

        int dir(int i){
            return (i+1)<<1;
        }

        int ant(int i){
            return (i-1)>>1;
        }

        void heapfica(int i){
            if(i< 0 || i >= dados.tam()) return;

            int e = esq(i);
            int d = dir(i);
            int menor = i;
            if(e < dados.tam() && dados.at(e).pr < dados.at(i).pr){
                menor = e;
            }

            if(d < dados.tam() && dados.at(d).pr < dados.at(menor).pr){
                menor = d;
            }

            if(menor != i){
                aresta tmp = dados.at(i);
                dados.at(i) = dados.at(menor);
                dados.at(menor) = tmp;

                heapfica(menor);
            }
        }

        void cria_heap(void){
            for(int i = dados.tam()/2; i >= 0; i--){
                heapfica(i);
            }
        }

        aresta min(void){
            return dados.at(0);
        }

        aresta extrai_min(void){
            if(dados.tam() < 1){
                /*underflow*/
                aresta vazia;
                return vazia;
            }

            aresta menor = dados.at(0);
            dados.at(0) = dados.at(dados.tam() - 1);
            dados.remove(dados.tam() - 1);
            heapfica(0);

            return menor;
        }

        void diminui_chave(int i, int chave){
            if(chave > dados.at(i).pr){
                return;
            }

            dados.at(i).pr = chave;
            while(i > 0 && dados.at(ant(i)).pr > dados.at(i).pr){
                aresta tmp = dados.at(ant(i));
                dados.at(ant(i)) = dados.at(i);
                dados.at(i) = tmp;

                i = ant(i);
            }
        }

        void insere(aresta a){
            dados.anexa(a);
            dados.at(dados.tam() - 1).pr = __INT32_MAX__;
            diminui_chave(dados.tam() - 1, a.pr);
        }
        

};

/*conjuntos disjuntos*/
class disjuntos{
    public:    
        vetor<int> conjuntos;
        vetor<int> tamanhos;

        disjuntos(int n){
            for(int i = 0; i < n; i++){
                conjuntos.anexa(i);
                tamanhos.anexa(1);
            }
        }

        int find(int i){
            if(i == conjuntos.at(i)){
                return i;
            }
            conjuntos.at(i) = find(conjuntos.at(i));
            return conjuntos.at(i);
        }

        bool uniao(int i, int j){
            int c_i = find(i);
            int c_j = find(j);

            if(c_i == c_j) return false;

            if(tamanhos.at(c_i) >= tamanhos.at(c_j)){
                tamanhos.at(c_i) += tamanhos.at(c_j);
                conjuntos.at(c_j) = c_i;
            }
            else{//tamanhos.at(c_i) < tamanhos.at(c_j)
                tamanhos.at(c_j) += tamanhos.at(c_i);
                conjuntos.at(c_i) = c_j;
            }

            return true;
        }
};


int main(void){
    minheap arestas;

    size_t tam_buffer = 80;
    char *linha = new char[tam_buffer];

    int maior = 0;
    
    getline(&linha,&tam_buffer, stdin);

    while(true){
        getline(&linha,&tam_buffer,stdin);
        if(feof(stdin)) break;
        
        aresta nova;
        sscanf(linha,"%d %d %d",&nova.a,&nova.b,&nova.pr);
        arestas.insere(nova);

        if(nova.a > maior){
            maior = nova.a;
        }
        if(nova.b > maior){
            maior = nova.b;
        }
    }

    int preco = 0;
    disjuntos d(maior + 1);
    while(arestas.dados.tam() != 0){
        aresta p = arestas.extrai_min();
        if(d.uniao(p.a,p.b)){
            preco += p.pr;
        }
    }

    printf("%d",preco);

    return 0;    
}