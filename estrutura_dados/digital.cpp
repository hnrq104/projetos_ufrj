
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node{
    int marca;
    node* ant;
    node* dig[2]; /*digito*/
    /*nao é agradavel, mas vou botar um buffer de char aq, pq to com preguica de fazer vetor dnv*/
    char* str;

    node(){
        marca = 0;
        dig[0] = NULL;
        dig[1] = NULL;
        str = NULL;
    }
    ~node(){
        delete[] str;
    }
};

void copia_str(char* original, char* copia){
    /*80 é o tamanho da string, preguica de fazer com vetor*/
    for(int i = 0; i<80; i++){
        if(*original != '\n') *copia = *original;
        if(*original == '\0') break;
        copia++;
        original++;
    }
}

struct digital{
    node* cabeca;
    int tamanho;

    digital(){
        cabeca = new node;
        cabeca->marca = 1;

        char string[] = "N/A";
        cabeca->str = new char[80];
        copia_str(string,cabeca->str);

        tamanho = 0;
    }

    void insere(unsigned bits, unsigned submask, char* string){
        unsigned mascara = 1<<31;
        node* ptr = cabeca;
        for(unsigned i = 0; i < submask; i++){
            unsigned bit = (bits & mascara) != 0;
            mascara = mascara>>1;

            if(ptr->dig[bit] == NULL){
                ptr->dig[bit] = new node;
                ptr->dig[bit]->ant = ptr;
            }
            ptr = ptr->dig[bit];
        }
        ptr->marca = 1;
        ptr->str = new char[80];
        copia_str(string,ptr->str);
        tamanho++;
    }

    node* find(unsigned bits, unsigned submask){
        unsigned mascara = 1<<31;
        node* ptr = cabeca;
        for(unsigned i = 0; i < submask; i++){
            unsigned bit = (bits & mascara) != 0;
            mascara = mascara>>1;

            ptr = ptr->dig[bit];
            if(ptr == NULL){
                break;
            }
        }
        return ptr;
    }

    node* find_ultimo(unsigned bits, unsigned submask){
        unsigned mascara = 1<<31;
        node* ptr = cabeca;
        node* marcado = cabeca;
        for(unsigned i = 0; i < submask; i++){
            unsigned bit = (bits & mascara) != 0;
            mascara = mascara>>1;

            ptr = ptr->dig[bit];
            if(ptr == NULL){
                break;
            }
            if(ptr->marca){
                marcado = ptr;
            }
        }
        return marcado;
    }


    void del(unsigned bits, unsigned submask){
        node* ptr = find(bits,submask);
        if(ptr == NULL || ptr->marca == 0) return;
        ptr->marca = 0;
        while(ptr->marca == 0 && ptr->dig[0] == NULL && ptr->dig[1] == NULL){
            node* aux = ptr;
            ptr = ptr->ant;
            if(aux == ptr->dig[0]){
                ptr->dig[0] = NULL;
            }
            else{
                ptr->dig[1] = NULL;
            }
            delete aux;
        }
    }


};

unsigned binario(short ip[4]){
    unsigned number = ip[0];
    for(int i = 0; i < 4; i++){
        number = number<<8;
        number = number|ip[i];
    }
    return number;
}

/*input
146.127.30.0/24 henrique
192.255.50.20/30 beatriz
10.128.0.0/9 raul seixas
146.127.30.15/32 nityananda
*/

void print(char* ptr){
    while(*ptr != '\0'){
        printf("%c",*ptr);
        ptr++;
    }
}

int main(void){
    size_t tam_buffer = 80;
    char* linha = new char[tam_buffer];
    digital d;

    /*insercao*/
    getline(&linha,&tam_buffer,stdin);/*primeira linha não importa*/

    while(true){
        getline(&linha,&tam_buffer,stdin);
        if(feof(stdin) || *linha == '\n') break;

        char* aux = linha;
        unsigned submask;
        short ip[4];
        for(int i = 0; i < 4; i++){
            ip[i] = atoi(aux);
            while(*aux>='0' && *aux<='9') aux++;
            aux++; /*pula o '.'*/
        }
        
        if(*aux == '\0'){//não tem submascara
            node* ptr = d.find_ultimo(binario(ip),32);
            printf("%d.%d.%d.%d ",ip[0],ip[1],ip[2],ip[3]);
            print(ptr->str);
            printf("\n");
            continue;
        }
        
        submask = atoi(aux);
        while(*aux>='0' && *aux<='9') aux++;
        aux++;
        /*mensagem está aqui*/
        d.insere(binario(ip),submask,aux);

    }
    
    return 0;
}