import math
import numpy as np

def trapezio(h, lista_f:list):
    soma = lista_f[0] + lista_f[len(lista_f) - 1]
    for i in range(1,len(lista_f) - 1):
        soma += 2*lista_f[i]
    return (h/2)*soma

def simpson(h,lista_f:list):
    soma = lista_f[0] + lista_f[len(lista_f) - 1]
    for i in range(2,len(lista_f) - 1,2):
        soma += 2*lista_f[i]

    for j in range(1,len(lista_f) - 1,2):
        soma+= 4*lista_f[j]
    
    return (h/3)*soma

def b_trapezio(a,b,nos,f):
    lista_x = np.linspace(a,b,nos,endpoint=True)
    lista_f = [f(i) for i in lista_x]

    return trapezio(lista_x[1] - lista_x[0], lista_f)


def b_simpson(a,b,nos,f):
    lista_x = np.linspace(a,b,nos,endpoint=True)
    lista_f = [f(i) for i in lista_x]

    return simpson(lista_x[1] - lista_x[0], lista_f)

n = [10,50,100,200]
for i in n:
    print(i,"nós")
    trap =  b_trapezio(0,math.pi,i,math.sin)
    print("trapezio ", trap, " erro = ", 2 - trap)
    simp =  b_simpson(0,math.pi,i,math.sin)
    print("~(_8^(I) ", simp , " erro = ", 2 - simp)
    print()

