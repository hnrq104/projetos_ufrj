#include <bits/stdc++.h>


struct node{
    int marca;
    node* ant;
    node* dig[2]; /*digito*/
        
    node(){
        marca = 0;
        dig[0] = nullptr;
        dig[1] = nullptr;
    }
};


struct digital{
    node* cabeca;
    int tamanho;

    digital(){
        cabeca = new node;
        cabeca->marca = 1;
        tamanho = 0;
    }

    void insere(unsigned bits, unsigned submask){
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

int main(void){
    
    short ip[4] = {10,30,2,224};
    // unsigned submask = 21;

    unsigned number = ip[0];
    for(int i = 1; i < 4; i++){
        number = number << (8);
        number = number | ip[i];
    }
    std::cout << std::hex << number  << std::endl;
    
    for(int i = 0; i < 4; i++){
        std::cout << std::setfill('0') << std::setw(2) << std::hex << ip[i];
    }
    std::cout << std::endl;

    digital d;
    d.insere(number,21);

    node* ptr = d.find(number,21);
    std::cout <<std::endl;
    std::cout << ptr << std::endl;
    std::cout << ptr->marca << std::endl;




    return 0;
}