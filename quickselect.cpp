#include<iostream>
#include<stdlib.h>


class vetor{

	private:
		int tam_externo;
		int tam_interno;
		int* data;

		void resize(void){
			if(tam_interno - tam_externo < 2){
				int *novo = new int[2*tam_interno];
				for(int i = 0; i < tam_interno; i++){
					*(novo + i) = *(data + i);
				}
				delete[] data;
				data = novo;

				tam_interno*=2;
			}
		}


	public:
		vetor(void){
			tam_interno = 10;
			tam_externo = 0;
			data = new int[tam_interno];
		}

		vetor(vetor &copia){
			tam_interno = copia.tam_interno;
			tam_externo = copia.tam_externo;

			data = new int[tam_interno];
			for(int i = 0; i < tam_interno; i++){
				*(data + i) = *(copia.data + i);
			}
		}
		
		~vetor(void){
			delete[] data;
		}

		int &at(int index){
			if(index < 0 || index >= tam_externo){
				return *data; // não pode soltar exceção
			}

			return *(data + index);
		}

		void anexa(int n){
			*(data+tam_externo) = n;
			tam_externo++;
			resize();
		}

		void remove(int index){
			if(index < 0 || index >= tam_externo){
				return; //não pode soltar exceção
			}

			for(int i = index; i < tam_externo - 1; i++){
				*(data + i) = *(data + i + 1);
			}

			tam_externo--;
		}

		int tamanho(void){
			return tam_externo;
		}
  
};

int particiona(vetor &v, int inicio, int fim){
	int meio = (inicio + fim)/2;
	
	int pivot = v.at(meio);
	v.at(meio) = v.at(inicio);
	v.at(inicio) = pivot;

	int i = inicio + 1;
	int j = fim - 1;

	while(i <= j){
		while(i < fim && v.at(i) <= pivot){
			i++;
		}

		while(j > inicio && v.at(j) >= pivot){
			j--;
		}

		if(i < j){
			int tmp = v.at(i);
			v.at(i) = v.at(j);
			v.at(j) = tmp;
		}
	}

	int tmp = v.at(i - 1);
	v.at(inicio) = tmp;
	v.at(i-1) = pivot;

	return i-1;
}

/*
void quick_sort(vetor &v, int inicio, int fim){
	if(fim - inicio > 1){
		int pos = particiona(v,inicio,fim);
		quick_sort(v,inicio,pos);
		quick_sort(v,pos,fim);
	}
}
*/

int quick_select(vetor &v, int k, int inicio, int fim){
	int pos = particiona(v,inicio,fim);
	if(pos == k){
		return v.at(pos);
	}

	if(pos > k){
		return quick_select(v,k,inicio,pos);
	}

	else{//pos < k
		return quick_select(v,k,pos,fim);
	}
}


//atoi e sscanf não parecem estar funcionando


int main(int argc, char *argv[]){
	int k = atoi(argv[2]);

	vetor meu;
	int num;
	while(std::cin >> num){
		meu.anexa(num);
	}

	// if(k >= meu.tamanho()){
	// 	throw std::out_of_range("valor improprio de k");
	// }

	std::cout << quick_select(meu,k,0,meu.tamanho()) << std::endl;

/*
	quick_sort(meu,0,meu.tamanho());
	for(int i = 0 ; i < meu.tamanho(); i++){
		std::cout << meu.at(i) << " ";
	}
	std::cout << std::endl;
*/

	return 0;
}
