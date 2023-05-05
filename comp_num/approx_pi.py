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

def approx_pi_kahan(termos):
    fatorial = 1
    produto_impar = 1
    soma = 1
    
    e = 0 #erro
    for k in range(1,termos):
        fatorial *= k
        produto_impar *= (2*k + 1)

        #kahan
        tmp = soma
        y = fatorial/produto_impar + e
        soma = tmp + y
        e = (tmp - soma) + y


    return 2*soma
    

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

def approx_e_kahan(termos):
    soma = 1
    fatorial = 1

    e = 0 #erro
    for i in range(1,termos):
        fatorial *= i

        #kahan
        tmp = soma
        y = 1/fatorial + e
        soma = tmp + y
        e = (tmp - soma) + y
    
    return soma




term =  int(input("numero de termos : "))

# teste_pi_1 = approx_pi_fat(term)
# print("aprox_fat %pi = ",teste_pi_1)
# print("diferenca = ", abs(math.pi - teste_pi_1),"\n")

teste_pi_2 = approx_pi(term)
print("aprox %pi = ",teste_pi_2)
print("diferenca = ", math.pi - teste_pi_2,"\n")

# teste_pi_3 = approx_pi_inv(term)
# print("aprox_inv %pi = ",teste_pi_3)
# print("diferenca = ", abs(math.pi - teste_pi_3),"\n")

teste_pi_4 = approx_pi_kahan(term)
print("aprox_kahan %pi = ",teste_pi_2)
print("diferenca = ", math.pi - teste_pi_4,"\n")


# teste_e_1 = approx_e_fat(term)
# print("aprox_fat %e = ",teste_e_1)
# print("diferenca = ", abs(math.e - teste_e_1),"\n")


teste_e_2 = approx_e(term)
print("aprox %e = ",teste_e_2)
print("diferenca = ", math.e - teste_e_2,"\n")

# teste_e_3 = approx_e_inv(term)
# print("aprox_inv %e = ",teste_e_3)
# print("diferenca = ", abs(math.e - teste_e_3),"\n")


teste_e_4 = approx_e_kahan(term)
print("aprox_kahan %e = ",teste_e_4)
print("diferenca = ", math.e - teste_e_4,"\n")
