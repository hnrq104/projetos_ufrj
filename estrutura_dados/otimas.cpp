#include <bits/stdc++.h>


std::vector<int> custos_base(std::vector<int> pesos){
    size_t tam = pesos.size();
    // int matrix[tam][tam];
    
    std::vector<int> custos(tam*tam);

    int primeiro_coluna = 0; //primeiro elemento de cada coluna
    for(size_t i = 0; i < tam; i++){
        primeiro_coluna += pesos.at(i);
        int soma = primeiro_coluna - pesos.at(0);
        
        for(size_t j = 0; j < tam - i; j++){
            soma += pesos.at(j);
            custos.at(j*tam + (j + i)) = soma;
            soma -= pesos.at(j);
        }
    }

    return ;

}