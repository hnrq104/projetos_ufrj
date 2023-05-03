#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T>
class no{
    public:
        T data;
        no *prox;

        no(){
            prox = nullptr;
        }

        ~no(){
            if(prox!=nullptr){
                delete prox;
            }
        }

        void insere(T valor){
            no<T>* ptr = this;
            while(ptr->prox != nullptr){
                ptr = ptr->prox;
            }

            no<T>* novo = new no<T>;
            novo->data = valor;
            ptr->prox = novo;
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
            tamanho_alocado *=2;
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
                *(data + i) = *(copy.data + i);
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

        T &at(int index){
            if(index < 0 || index >= tamanho_imaginario){
                return *(data); // n pode usar throw
            }

            return *(data + index);
        }

        int size(void){
            return tamanho_imaginario;
        }
};

bool isdigit(char *ptr){
    if(*ptr >= '0' && *ptr <= '9'){
        return true; 
    }
    return false;
}

vetor<int> ordem(vetor<no<int>*> &adj){
    vetor<int> precedem;
    //precedem eh inicializado por 0s
    for(int i = 0; i < adj.size(); i++){
        precedem.push_back(0);
    }

    
    //fill precedem
    no<int> *ptr;
    for(int i = 0; i < adj.size(); i++){
        ptr = adj.at(i)->prox;
        while(ptr != nullptr){
            precedem.at(ptr->data)++;
            ptr = ptr->prox;
        }

    }
    // printf("precedem cheio!");


    vetor<int> ordenado;
    /*procura primeiros 0's*/
    for(int i = 0; i < precedem.size(); i++){
        if(precedem.at(i) == 0){
            ordenado.push_back(i);
        }
    }

    // //começa de fato o algoritmo

    for(int j = 0; j < ordenado.size(); j++){
        //reduz a precedencia das adjacencias;
        int num = ordenado.at(j); // numero para ser analizado
        no<int> *ptr = adj.at(num)->prox; // primeiro elemento da lista
        
        while(ptr!=nullptr){ //subtrai da lista de precedencia
            precedem.at(ptr->data)--;
            //se zerar adicionar a ordem
            if(precedem.at(ptr->data) == 0){
                ordenado.push_back(ptr->data);
            }
            ptr = ptr->prox;
        }
    }
    
    return ordenado;
    // return ordenado;
}

int main(void){
    
    char *line; //inicio do buffer
    char *ptr_char; 
    size_t str_size = 80; //tamanho do buffer
    line = new char[str_size]; //buffer

    vetor<no<int>*> adj;// lista de adjacencias

    while(true){
        getline(&line,&str_size,stdin);
        
        if(feof(stdin)) break;
        
        no<int> *lista = new no<int>;// adjacencias da linha
        ptr_char = line;

        while(*ptr_char != '\0'){
            if(isdigit(ptr_char)){
                lista->insere(atoi(ptr_char));
                while(isdigit(ptr_char)){// terminar a leitura de número
                    ptr_char++;
                }
            }
            ptr_char++;
        }
        adj.push_back(lista);
    }

/*
    printf("valores lidos \n");
    no<int> *ptr_no;
    for(int i = 0; i < adj.size(); i++){
        ptr_no = adj.at(i)->prox;
        printf("vertice %d -> ",i);
        while(ptr_no != nullptr){
            printf("%d ",ptr_no->data);
            ptr_no = ptr_no->prox;
        }
        printf("\n");
    }
*/

    vetor<int> resposta = ordem(adj);
    for(int i = 0; i < resposta.size(); i++){
        printf("%d",resposta.at(i));
    }

    return 0;
}


