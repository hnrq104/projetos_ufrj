import numpy as nup
from math import exp
def met_euler( f, t0, tf, y0, np ):

    # listas para armazenar  a discretização do intervalo
    # e as aproximações da solução
    t = [t0]
    y = [y0]
    tn = t0
    yn = y0

    # tamanho do passo no tempo
    dt = float(tf-t0)/np

    # laço para o avanço no tempo
    for n in range(np):
        # calculo da solução aproximada
        yn = yn + dt*f(tn,yn)
        # atualização do valor do tempo
        tn = t0 + (n+1)*dt

        # anexando os valores calculados nas listas
        y.append(yn)
        t.append(tn)

    return [t, y]

#####################################



def met_heun( f, t0, tf, y0, np ):

    t = [t0]
    y = [y0]
    tn = t0
    y1n = y0

    dt = float(tf-t0)/np

    for n in range(np):
        ye = y1n + dt*f(tn, y1n)

        y1n = y1n + dt/2*(f(tn, y1n)+f(tn+dt, ye))
        tn = t0 + (n+1)*dt

        y.append(y1n)
        t.append(tn)

    return [t, y]

#####################################

def runge_kutta(f,t0,tf,y0,np):
    t = [t0]
    y = [y0]
    tn = t0
    yn = y0

    dt = float(tf-t0)/np

    for n in range(np):
        k1 = dt*f(tn,yn)
        k2 = dt*f(tn + dt/2, yn + k1/2)
        k3 = dt*f(tn + dt/2, yn + k2/2)
        k4 = dt*f(tn + dt, yn + k3)

        yn = yn + (dt/6)*(k1 + 2*k2 + 2*k3 + k4)
        tn = t0 + (n+1)*dt
        y.append(yn)
        
        t.append(tn)

    return [t,y]

import matplotlib.pyplot as plt

y0=[150,50]

def biologo(t,y):
    return nup.array([y[0]*(0.5 - 0.01*y[1]),(0.001*y[0] - 0.2)*y[1]])

[t,y] = runge_kutta(biologo,0,1,y0,5)

# print(t[5],y[5])


#tarefa 2
g=9.81
m=75
c=12.5
y0 = 0
def vel_paraquedas(t,y):
    return g - (c/m)*y

def vel(t):
    return ((g*m)/c)*(1 - exp(-(c/m)*t))

ex = vel(25)

func = [met_euler,met_heun,runge_kutta]
num = []
val = [0 for i in range(3)]

for i in range(3):
    erro = 1
    np = 5
    while(erro > 10**-2):
        [t,y] = func[i](vel_paraquedas,0,25,y0,np)
        val[i] = y[np]
        erro = abs(ex - val[i])
        np+=5

    num.append(np)
print("#A")
print("met euler = " ,val[0], " nup = ", num[0])
print("met heun = " ,val[1], " nup = ", num[1])
print("met runge_kutta = " ,val[2], " nup = ", num[2])

#letra b
alfa = 0.2
beta = 1.1
vmax = 46
def C(y):
    return c*(1 + alfa*(y/vmax)**beta)

def empirica(t,y):
    return g - (C(y)/m)*y


valb = [0 for i in range(3)]
for i in range(3):
    [t,y] = func[i](empirica,0,25,y0,num[i])
    valb[i] = y[num[i]]

print("#B")
print("met euler = " ,valb[0], "a - b ", val[0] - valb[0])
print("met heun = " ,valb[1], " a - b ",val[1] - valb[1])
print("met runge_kutta = " ,valb[2], "a - b ", val[2] - valb[2])


b = 0.0003
gamma = 0.15
y0=[10000,1]

def doenca(t,y):
    return nup.array([-(b*y[0]*y[1] - gamma*y[1]), b*y[0]*y[1] - gamma*y[1]])

[t,y] = runge_kutta(doenca,0,21,y0,26)
print(y[26])
