import math
#pi
def approx_pi_fat(termos):
    pi = 0
    for k in range(0,termos):
        pi += (2**k)*(math.factorial(k)**2)/math.factorial(2*k + 1)
    return 2*pi

def approx_pi(termos):
    fatorial = 1
    produto_impar = 1
    soma = fatorial/produto_impar
    for k in range(1,termos):
        fatorial *= k
        produto_impar *= (2*k + 1)
        soma += fatorial/produto_impar


    return 2*soma


def approx_pi_inv(termos):
    pi = 0
    for k in range(termos-1,-1,-1):
        pi += (2**k)*(math.factorial(k)**2)/math.factorial(2*k + 1)
    return 2*pi

#e

def approx_e_fat(termos):
    soma = 0
    for i in range(0,termos):
        soma += 1/math.factorial(i)

    return soma


def approx_e(termos):
    soma = 1
    fatorial = 1
    for i in range(1,termos):
        fatorial *= i
        soma += 1/fatorial
    
    return soma

def approx_e_inv(termos):
    soma = 0
    for i in range(termos-1,-1,-1):
        soma+= 1/math.factorial(i)

    return soma

# def approx_e_rec(termos,fat = 1,e):
#     if(fat == termos){

#     }




term =  int(input("numero de termos : "))

# teste_pi_1 = approx_pi_fat(term)
# print("aprox_fat %pi = ",teste_pi_1)
# print("diferenca = ", abs(math.pi - teste_pi_1),"\n")

teste_pi_2 = approx_pi(term)
print("aprox %pi = ",teste_pi_2)
print("diferenca = ", abs(math.pi - teste_pi_2),"\n")

# teste_pi_3 = approx_pi_inv(term)
# print("aprox_inv %pi = ",teste_pi_3)
# print("diferenca = ", abs(math.pi - teste_pi_3),"\n")


# teste_e_1 = approx_e_fat(term)
# print("aprox_fat %e = ",teste_e_1)
# print("diferenca = ", abs(math.e - teste_e_1),"\n")


teste_e_2 = approx_e(term)
print("aprox %e = ",teste_e_2)
print("diferenca = ", abs(math.e - teste_e_2),"\n")

# teste_e_3 = approx_e_inv(term)
# print("aprox_inv %e = ",teste_e_3)
# print("diferenca = ", abs(math.e - teste_e_3),"\n")
