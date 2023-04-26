#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T>
class no{
    public:
        T data;
        no *prox;

        ~no(){
            if(prox!=nullptr){
                delete prox;
            }
        }
};

template<typename T>
class nos{
    public:
        no<T> *cbc;
        
        nos(){
            cbc = new no<T>;
            cbc->prox = nullptr;
        }

        nos(const nos &copy){
            cbc = new no<T>;
            no<T> *ptr_copy = copy.cbc->prox;
            no<T> *ptr = cbc;
            while(ptr_copy != nullptr){
                ptr->prox = new no<T>;
                ptr->prox->data = ptr_copy -> data;
                ptr = ptr->prox;
                ptr_copy = ptr_copy->prox;
            }
        
        }

        ~nos(){
            delete cbc;
        }

        void insere(T valor){
            no<T>* ptr = cbc;
            while(ptr->prox != nullptr){
                ptr = ptr->prox;
            }

            no<T>* novo = new no<T>;
            novo->data = valor;
            novo->prox = nullptr;

            ptr->prox = novo;
        }

        no<T> *get_first(void){
            return cbc->prox;
        }
};

template<typename T>
class vetor{
    private:
        T *data;
        int tamanho_alocado;
        int tamanho_imaginario;
        
        void overflow(void){
            //aloca dobro do tamanho
            T *ptr = new T[tamanho_alocado*2];
            for(int i = 0; i < tamanho_imaginario; i++){
                *(ptr + i) = *(data + i);
            }
            
            delete[] data;
            data = ptr;
        }

    public:

        vetor(){
            tamanho_alocado = 10;
            tamanho_imaginario = 0;
            data = new T[tamanho_alocado];
        }

        vetor(const vetor &copy){
            tamanho_alocado = copy.tamanho_alocado;
            tamanho_imaginario = copy.tamanho_imaginario;
            data = new T[tamanho_alocado];
            for(int i = 0; i < tamanho_imaginario; i++){
                *(data + i) = *(copy->data + i);
            }
        }

        ~vetor(){
            delete[] data;
        }
        
        void push_back(T coisa){
            *(data + tamanho_imaginario) = coisa;
            tamanho_imaginario++;
            if(tamanho_imaginario > tamanho_alocado - 1){
                overflow();
            }
        }

        T *at(int index){
            if(index < 0 || index >= tamanho_imaginario){
                return nullptr; // n pode usar throw
            }

            return (data + index);
        }

        int size(void){
            return tamanho_imaginario;
        }
};

bool isdigit(char *ptr){
    if(*ptr >= '0' && *ptr <= '9'){
        return true; 
    }
    
    else{
        return false;
    }
}

vetor<int> &ordem(vetor<nos<int>> &adjacencias){
    /*LEMBRA 0 É O PRIMEIRO ELEMENTO*/
    printf("OI FUNCAO FOI CHAMADA!!");

    // vetor<int> precedem; // precedem.at(2) = quantas tarefas precedem
    // //precedem eh inicializado por 0s
    // for(int i = 0; i < adjacencias.size(); i++){
    //     precedem.push_back(0);
    // }
    
    // // printf("precedem incializado com 0!!!");


    // //fill precedem
    // for(int i = 0; i < adjacencias.size(); i++){
    //     no<int> *ptr = adjacencias.at(i)->get_first();

    //     while(ptr != nullptr){
    //         (*precedem.at(ptr->data))++;
    //     }
    // }

    // // printf("precedem cheio!");


    // vetor<int> ordenado;
    // /*procura primeiros 0's*/
    // for(int i = 0; i < precedem.size(); i++){
    //     if(*precedem.at(i) == 0){
    //         ordenado.push_back(i);
    //     }
    // }

    // // printf("CHEGUEI AQUI!!!");


    // //começa de fato o algoritmo

    // for(int j = 0; j < ordenado.size(); j++){
    //     //reduz a precedencia das adjacencias;
    //     int num = *ordenado.at(j); // numero para ser analizado
    //     no<int> *ptr = adjacencias.at(num)->get_first(); // primeiro elemento da lista
        
    //     while(ptr!=nullptr){ //subtrai da lista de precedencia
    //         (*precedem.at(ptr->data))--;
    //         //se zerar adicionar a ordem
    //         if(*precedem.at(ptr->data) == 0){
    //             ordenado.push_back(ptr->data);
    //         }
    //         ptr = ptr->prox;
    //     }
    // }
    vetor<int> *novo = new vetor<int>;
    return *novo;
    // return ordenado;
}

int main(void){
    
    char *line;
    char *ptr;
    size_t str_size = 80;
    line = new char[str_size];

    vetor<nos<int>> adjacencias;
    nos<int> teste;

    while(true){
        getline(&line,&str_size,stdin);
        if(feof(stdin)) break;
        
        nos<int> lista;
        ptr = line;

        while(*ptr != '\0'){
            if(isdigit(ptr)){
                lista.insere(atoi(ptr));
                while(isdigit(ptr)){
                    ptr++;
                }
            }
            ptr++;
        }

        adjacencias.push_back(lista);
    }


    printf("valores lidos \n");

    printf("%d \n",adjacencias.size());

    int i;
    for(i = 0 ; i < adjacencias.size(); i++){
        printf("vertice %d -> ",i);
        no<int> *ptr = adjacencias.at(i)->get_first();
        while(ptr != nullptr){
            printf("%d ",ptr->data);
            ptr = ptr->prox;
        }

        printf("\n");
    }
    
    
    return 0;
}


