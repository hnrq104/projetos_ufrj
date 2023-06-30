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


def fresnel(t):
    return math.cos((math.pi*(t**2))/2)

def n_min_desejado(a,b,err):
    maior = max(abs(a),abs(b))
    resto_lagrange = abs(((math.pi**2)*(maior**2) + 1)*((b-a)**3))
    erro_quadrado = resto_lagrange/(12*err)
    return math.ceil(math.sqrt(erro_quadrado))


valores = [2,0.5,1,5]
comparar = [0.48825340607534075450,
             0.49234422587144639288,
             0.77989340037682282947,
             0.56363118870401223110]
print("TRAPEZIO")
print()
for i in range(0,len(valores)):
    nos = n_min_desejado(0,valores[i],10**-8)
    print("trapezio nos = ",nos)
    valor =  b_trapezio(0,valores[i],nos,fresnel)
    print("/fresnel(",valores[i],") = ",valor , " err = ", abs(valor - comparar[i]))

#usando simpson

print("simpson")
print()

def n_min_simpson(a,b,err):
    maior = max(abs(a),abs(b))
    m4 = 6*(math.pi**3)*(maior**2) + (math.pi**4)*(maior**4) + 3*(math.pi**2)
    resto_lagrange = abs((maior**5)*m4)
    n4 = resto_lagrange/(180*err)
    return math.ceil(n4**(1/4))


for i in range(0,len(valores)):
    nos = n_min_simpson(0,valores[i],10**-8)
    print("simpsons nos = ",nos)
    valor =  b_simpson(0,valores[i],nos,fresnel)
    print("/fresnel(",valores[i],") = ",valor , " err = ", abs(valor - comparar[i]))

