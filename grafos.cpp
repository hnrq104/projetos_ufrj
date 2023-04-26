#include <stdio.h>


template <typename T>
class no{
    public:
        T data;
        no *prox;
};

template<typename T>
class nos{
    public:
        no<T> *cbc;
        
        nos(void){
            ptr = new no<T>;
            cbc->prox = nullptr;
        }

        void insere(T valor){
            no* ptr = cbc;
            while(ptr->prox != nullptr){
                ptr = ptr->prox;
            }

            no* novo = new no;
            novo->data = valor;
            novo->prox = nullptr;

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
        }

    public:

        vetor(){
            tamanho_alocado = 10;
            tamanho_imaginario = 0;
            data = new T[tamanho_alocado];
        }

        ~vetor(){
            delete[] data;
        }
        
        void push_back(T coisa){
            *(data + tamanho_imaginario) = coisa;
            if(tamanho_imaginario > tamanho_alocado - 1){
                overflow();
            }
        }
};

int main(void){
    
    char *line;
    size_t str_size = 80;
    line = new char[str_size];
    while(true){
        getline(&line,&str_size,stdin);
        if(feof(stdin)) break;
        printf("string : %s",line);
    }

    return 0;
}



