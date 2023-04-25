#include <bits/stdc++.h>

struct no{
    int data;
    no *prox;
};


class lista{
    private:
        no *ptlista;
    
    public:
        
        lista(void){
            ptlista = new no;
            ptlista->prox = nullptr;
        }

        void anexa(int n){
            no* ptr = ptlista;
            while(ptr->prox != nullptr){
                ptr = ptr->prox;
            }

            no *novo = new no;
            novo->data = n;
            novo->prox = nullptr;

            ptr->prox = novo;
        }

        no *primeiro(void){
            return ptlista -> prox;
        }
};


std::vector<int> ordem(std::vector<lista> adjacentes){
    std::vector<int> prioridades(adjacentes.size()); //quantos elementos apontam para i
    /* fila de prioridades comeca tudo zerado*/
    for(size_t i = 0; i < prioridades.size(); i++){
        prioridades.push_back(0);
    }

    
    /*encher a fila de prioridades*/
    for(size_t i = 0; i < adjacentes.size(); i++){
        no* ptr = adjacentes.at(i).primeiro();
        while(ptr != nullptr){
            prioridades.at(ptr->data)++;
            ptr = ptr->prox;
        }
        
    }

    std::vector<int> ordem; // a ordem
    //acha os primeiros elementos da ordem (os que  nao sao precedidos por ngm)
    for(size_t i = 0; i < prioridades.size(); i++){
        if(prioridades.at(i) == 0) ordem.push_back(i);
    }
    
    /*agora podemos comecar o algoritmo*/
    for(size_t j = 0; j < ordem.size(); j++){
        
        //vertice que usaremos
        size_t vertice = ordem.at(j);

        //para cada conexao do vertice, remover na lista de prioridades
        no* conexao = adjacentes.at(vertice).primeiro();
        while(conexao != nullptr){
            size_t tarefa = conexao->data;
            
            prioridades.at(tarefa)--;
            
            if(prioridades.at(tarefa) == 0){
                //precendentes ja foram contabilizados adicionar a lista de ordem
                ordem.push_back(tarefa);
            }

            conexao = conexao->prox;
        }
    }

    return ordem;

}

int main(void){
	

    //ler varios numeros em uma linha
    std::vector<lista> adj;
    std::string linha;
    std::stringstream ss;
    int num;
    int vertice = 0;
    while(std::cin >> linha){
        ss << linha;
        lista nova;
        while(ss >> num){
            nova.anexa(num);
        }
        ss.str("");
        vertice++;
    }

}
