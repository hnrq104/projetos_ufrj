#include <bits/stdc++.h>


struct node{
    int marca;
    node* ant;
    node* dig[2]; /*digito*/
    /*nao é agradavel, mas vou botar um buffer de char aq, pq to com preguica de fazer vetor dnv*/
    char* str;

    node(){
        marca = 0;
        dig[0] = nullptr;
        dig[1] = nullptr;
        str = nullptr;
    }
};

void copia_str(char* original, char* copia){
    /*80 é o tamanho da string, preguica de fazer com vetor*/
    for(int i = 0; i<80; i++){
        *copia = *original;
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
        tamanho = 0;
    }

    void insere(unsigned bits, unsigned submask, char* string){
        unsigned mascara = 1<<31;
        node* ptr = cabeca;
        for(unsigned i = 0; i < submask; i++){
            unsigned bit = (bits & mascara) != 0;
            mascara = mascara>>1;
            if(ptr->dig[bit] == nullptr){
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
            ptr = ptr->dig[bit];
            if(ptr == nullptr){
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
            ptr = ptr->dig[bit];
            if(ptr == nullptr){
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
        if(ptr == nullptr || ptr->marca == 0) return;
        ptr->marca = 0;
        while(ptr->marca == 0 && ptr->dig[0] == nullptr && ptr->dig[1] == nullptr){
            node* aux = ptr;
            ptr = ptr->ant;
            if(aux == ptr->dig[0]){
                ptr->dig[0] = nullptr;
            }
            else{
                ptr->dig[1] = nullptr;
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


bool isdigit(char* ptr){
    if(*ptr >= '0' && *ptr<= '9') return true;
    return false;
}

void print(char* ptr){
    while(*ptr != '\0'){
        std::cout << *ptr;
        ptr++;
    }
}

int main(void){

    char h[] = "146.127.30.0/24 henrique";
    char b[] = "192.255.50.20/30 beatriz";
    char r[] = "10.128.0.0/9 raul seixas";
    char n[] = "146.127.30.15/32 nityananda";

    char* ponteiros[] = {h,b,r,n};

    digital d;
    unsigned numeros[4];
    for(int i = 0; i < 4; i++){
        char* aux = ponteiros[i];
        unsigned submask;
        short ip[4];
        for(int i = 0; i < 4; i++){
            ip[i] = atoi(aux);
            while(isdigit(aux)) aux++;
            aux++; /*pula o '.'*/
        }

        for(int i = 0; i < 4; i++){
            std::cout << std::hex << std::setw(2) << std::setfill('0') << ip[i];
        }
        std::cout<<std::endl;
        numeros[i] = binario(ip);
        std::cout<< std::hex << numeros[i] << std::endl;

        submask = atoi(aux);
        while(isdigit(aux)) aux++;
        aux++;
        print(aux);
        std::cout << std::endl;
        /*pula o espaço*/
        /*mensagem está aqui*/
        d.insere(numeros[i],submask,aux);

    }

    node* nitya = d.find_ultimo(numeros[0],24);
    std::cout << nitya << std::endl;
    print(nitya->str);
    std::cout << std::endl;




    return 0;
}