#include <bits/stdc++.h>


/*
0  0+1 0+1+2 ..
    1   1+2 .. ..
         2  2+3 .. 
             3  3+4
                 4



*/


//faz sentido que a matrix tenha lado peso+1,
//para aproveitar o resto de espaço, usam-se as frequencias extras
std::vector<int> sigma (std::vector<int> pesos){
    size_t tam = pesos.size();
    size_t lado = tam + 1;
    // int matrix[tam][tam];
    
    std::vector<int> custos(lado*lado);

    for(size_t i = 0; i < tam; i++){
        custos.at(i*tam + i) = 0;
    }

    int primeiro_coluna = 0; //primeiro elemento de cada coluna
    for(size_t i = 0; i < tam; i++){
        primeiro_coluna += pesos.at(i);
        int soma = primeiro_coluna;
        
        for(size_t j = 0; j < tam - i - 1; j++){
            custos.at(j*lado + (j + i + 1)) = soma;
            soma -= pesos.at(j);
            soma += pesos.at(j + 1);
        }

        custos.at(lado*(lado - i - 2) + (lado - 1)) = soma;
    }

    return custos;
}


std::vector<int> solut(std::vector<int> custos, size_t frutas){
    //casos base
    std::vector<int> sol = custos;


    size_t lado = frutas + 1;
    //casos não base
    // calculando diagonais
    for(size_t i = 0; i < frutas; i++){  //determina a diagonal
        for(size_t j = 0; j < frutas - i; j++){
            int minimal = INT_MAX;
            int raiz = i;

            //linha j, // col i + j + 1
            
            int fim = i + j + 1;

            for(size_t k = j; k < i + j + 1; k++){
                int soma = sol.at(lado*j + k) + sol.at(lado*(k+1) + fim);
                if(soma <= minimal){
                    minimal = soma;
                    raiz = k;
                }
            }

            sol.at(lado*j + fim) += minimal;
        }
    }

    return sol;
}

int main(void){
    std::vector<int> c = {220,10,5,1,5,6};
    std::vector<int> resp = sigma(c);
    size_t s = c.size() + 1;
    for(size_t i = 0; i < s; i++){
        for(size_t j = i; j <s; j++){
            std::cout << resp.at(i*s + j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "matriz de custos :" << std::endl;
    
    std::vector<int> sol = solut(resp,c.size());
    
    for(size_t i = 0; i < s; i++){
        for(size_t j = i; j <s; j++){
            std::cout << sol.at(i*s + j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

