# -*- coding: utf-8 -*-
"""Solução de PVIs para EDOs.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1UQ1n3H8onYuyttTWh4RX1udhiuvQ5_2O

# Solução aproximada de PVIs para EDOs

Consideramos um Problema de Valor Inicial (PVI) da forma

\begin{equation}\left\{\begin{aligned}
& y^\prime  = f(t, y), \qquad t_0 \leq t \leq t_f \\
& y(t_0) = y_{0}
\end{aligned}\right.
\end{equation}

onde a função $y(t)$ definida no intervalo $[t_0, t_f]$ é a nossa incógnita,  $y^\prime$ representa sua primeira derivada com relação à $t$, $f(t,y)$ é uma função conhecida e $y_0$ é a  condição inicial do problema.

Observamos que a Equação Diferencial Ordinária (EDO) $y^\prime  = f(t, y)$ possui, em geral, infinitas soluções, mas a solução do PVI que além da EDO deve satisfazer também a condição inicial é definida, de modo geral, de forma única. Assim, a condição inicial nos permite escolher uma solução individual da EDO.

## Método de Euler

Para obter uma solução aproximada desse PVI, escolhemos $N\geq 1$ (inteiro) e discretizamos o intervalo de interesse considerando os pontos $t_n = t_0 + n \Delta t$, $n=0,1,\dots,N$ onde $\Delta t = \frac{t_f-t_0}{N}$ representa o  tamanho do passo para o avanço no tempo. Assim as aproximações de $y(t_n)$, $n=0,1,\dots,N$ são dadas por $y_n$, $n=0,1,\dots,N$ e são calculadas de acordo com a equação

$$
y_{n+1} = y_n + \Delta t f(t_n, y_n), \quad n = 0,\dots, N-1.
$$

De forma geral, os erros dessas aproximações satisfazem as estimativas

$$ |y(t_n) - y_n| \leq C \Delta t ,\qquad n = 0,\dots, N, $$

onde a constante $C >0$ depende apenas da solução $y(t)$ no intervalo $[t_0, t_f]$. É importante frizar que essa constante não depende de $\Delta t$, assim quando $\Delta t\to 0$ os erros também tendem a zero.

Esse comportamento dos erros indica que o método possui convergência de primeira ordem (em relação ao $\Delta t$), e por isso é classificado como um método de primeira ordem.

Enfatizamos que no caso de um sistema de EDOs, o método de Euler é dado exatamente pela mesma fórmula acima mas levando em conta que $y$ e $f$ são funções vetoriais.

A seguir apresentamos o código em python de uma função que implementa esse método.
"""

####################################
# Metodo de Euler para o PVI
# y' = f(t,y), t0 <= t <= tf
# y(t0) = y0
####################################

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

"""## Método de Euler aperfeiçoado (ou método de Heun)

O método de Euler pode ser aprimorado para obter melhores aproximações. Uma das formas mais simples de conseguir isso é usar a aproximação dada pelo método de Euler na regra do trapézio, o método resultante é conhecido como método de Heun. Esse método é dado pela seguinte fórmula:

$$
\left.
\begin{aligned}
& {y}^E_{n+1} = y_n + \Delta t f(t_n, y_n)\\
& {y}_{n+1} = y_n + \frac{\Delta t}{2} \left( f(t_n, y_n) + f(t_{n+1}, {y}^E_{n+1}) \right)
\end{aligned}\right\}\quad n = 0,\dots, N-1.
$$

Os erros das aproximações desse método satisfazem as limitantes

$$ |y(t_n) - y_n| \leq C (\Delta t)^2 ,\qquad n = 0,\dots, N, $$

onde a constante $C>0$ não depende de $\Delta t$. Portanto esse método é de segunda ordem.

Esse método também representa um método de Runge-Kutta de segunda ordem (com dois estágios) já que pode ser re-escrito na forma

$$
\left.
\begin{aligned}
& k_1 = \Delta t f(t_n, y_n) \\
& k_2 = \Delta t f(t_n + \Delta t,  y_n + k_1 )\\
& {y}_{n+1} = y_n + \frac{1}{2} \left( k_1 + k_2) \right)
\end{aligned}\right\}\quad n = 0,\dots, N-1.
$$
"""

##############################################
# Metodo de Heun (ou Euler melhorado) para o PVI
# y' = f(t, y), t0 <= t <= tf
# y(t0) = y0
##############################################

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

"""## Exemplo: Uma EDO bem simples!

Vamos começar com um PVI bem simples, que possui solução analítica

$$
\left\{\begin{aligned}
& \frac{dy}{dt}  =  r y, \quad 0\leq t\leq 1\\
& y(0) = y_0
\end{aligned}
\right.
$$

onde $r$ é uma constante. A solução exata desse problema é
$$y(t) = y_0 e^{r t} .$$

Vamos usar nossos códigos para calcular a solução aproximada no caso $r=2.5$ e $y_0=1$ e compara-la com a solução exata.

###Primeiro usando o método de Euler.
"""

#@title
from math import exp

r = 2.50
def f(t, y):
    return r*y

# Observe que a função realmente não depende de t
# mas é preciso colocar esse parâmetro
# para garantir a compatibilidade com os
# códigos dos métodos implementados


# numero de passos
np = 10

[t, yap] = met_euler( f, 0, 1, 1, np )


# Calculo da solucao exata e do erro
yex = []
err = []
for i in range( len(t) ):
    yex.append( exp(r*t[i]) )
    err.append( exp(r*t[i]) - yap[i])

#######

# numero de passos
np = 100

[t1, yap1] = met_euler( f, 0, 1, 1, np )


# Calculo da solucao exata e do erro
yex1 = []
err1 = []
for i in range( len(t1) ):
    yex1.append( exp(r*t1[i]) )
    err1.append( exp(r*t1[i]) - yap1[i])

#######

"""Agora vamos mostrar os resultados gráficamente. Primeiro o caso $N=10$."""

#@title

# Usamos a biblioteca Matplotlib para mostrar gráficos
import matplotlib.pyplot as plt

plt.figure(figsize=(10,5))
plt.subplot(121)

plt.plot( t, yap, '.r')
plt.plot( t, yex, '.b-')

plt.xlabel('t')
plt.ylabel('x')
plt.title(u'Solução: $y=e^{r\,t}$ (N = %d)' %(len(t)-1))
plt.legend( ['Aproximada', 'Exata'], loc=2 )
plt.grid(True)


plt.subplot(122)
plt.plot( t, err, '.r')
plt.grid(True)
plt.xlabel('t')
plt.title('Erro')
plt.show()

"""Agora o caso $N=100$.


"""

#@title
plt.figure(figsize=(10,5))
plt.subplot(121)

plt.plot( t1, yap1, '.r')
plt.plot( t1, yex1, '.b-')

plt.xlabel('t')
plt.ylabel('x')
plt.title(u'Solução: $y=e^{r\,t}$ (N = %d)' %(len(t1)-1))
plt.legend( ['Aproximada', 'Exata'], loc=2 )
plt.grid(True)


plt.subplot(122)
plt.plot( t1, err1, '.r')
plt.xlabel('t')
plt.title('Erro')
plt.grid(True)
plt.show()

"""Comparando os resultados dos dois casos observamos que aumentando $N$ em dez vezes o erro também diminui aproximadamente em dez vezes! Isto é consequência de que o método de Euler é de primeira ordem (o erro é aproximadamente proporcional ao $\Delta t$).

###Agora usando o método de Heun.
"""

#@title
# numero de passos
np = 10

[t, yap] = met_heun( f, 0, 1, 1, np )


# Calculo da solucao exata e do erro
yex = []
err = []
for i in range( len(t) ):
    yex.append( exp(r*t[i]) )
    err.append( exp(r*t[i]) - yap[i])

#######

# numero de passos
np = 100

[t1, yap1] = met_heun( f, 0, 1, 1, np )


# Calculo da solucao exata e do erro
yex1 = []
err1 = []
for i in range( len(t1) ):
    yex1.append( exp(r*t1[i]) )
    err1.append( exp(r*t1[i]) - yap1[i])

#######

"""Agora vamos mostrar os resultados gráficamente. Primeiro o caso $N=10$."""

#@title

# Para mostrar resultados gráficos
import matplotlib.pyplot as plt

plt.figure(figsize=(10,5))
plt.subplot(121)

plt.plot( t, yap, '.r')
plt.plot( t, yex, '.b-')

plt.xlabel('t')
plt.ylabel('x')
plt.title(u'Solução: $y=e^{r\,t}$ (N = %d)' %(len(t)-1))
plt.legend( ['Aproximada', 'Exata'], loc=2 )
plt.grid(True)


plt.subplot(122)
plt.plot( t, err, '.r')
plt.xlabel('t')
plt.title('Erro')
plt.grid(True)
plt.show()

"""Agora o caso $N=100$.


"""

#@title
plt.figure(figsize=(10,5))
plt.subplot(121)

plt.plot( t1, yap1, '.r')
plt.plot( t1, yex1, '.b')

plt.xlabel('t')
plt.ylabel('x')
plt.title(u'Solução: $y=e^{r\,t}$ (N = %d)' %(len(t1)-1))
plt.legend( ['Aproximada', 'Exata'], loc=2 )
plt.grid(True)


plt.subplot(122)
plt.plot( t1, err1, '.r')
plt.xlabel('t')
plt.title('Erro')
plt.grid(True)
plt.show()

"""Comparando os resultados dos dois casos observamos que **quando aumentamos $N$ em dez vezes agora o erro diminui aproximadamente em $100$ vezes!** Isto é consequência de que o método de Heun é de segunda ordem (o erro é aproximadamente proporcional ao $(\Delta t)^2$).

## Exemplo: O pêndulo simples

**Representação esquemática (fonte: wikimedia.org)**

![pendulum](https://upload.wikimedia.org/wikipedia/commons/a/a3/HarmOs9.png)


---

Nesse modelo considera-se que apenas a força de gravidade atúa sobre o corpo e que o movimento do mesmo acontece num plano vertical. Nesse caso as equações da mecânica clássica tomam a seguinte forma:

$$
\left\{\begin{aligned}
& \frac{d^2\theta}{dt^2} + \frac{g}{l}\,\sin(\theta) = 0\\
& \theta(0) = \theta_0,\quad \frac{d\theta}{dt}(0) = w_0
\end{aligned}
\right.
$$

onde $\theta$ é o ângulo com a vertical, $g$ é a aceleração da gravidade, $l$ é o comprimento da haste, e $\theta_0$ e $w_0$ representam o ângulo e a velocidade angular iniciais, respectivamente.

Essa EDO de 2$^{da}$ ordem pode ser rescrita como um sistema de duas EDOs de 1$^{ra}$ ordem. Assim temos o seguinte PVI

$$
\left\{\begin{aligned}
& y_1^\prime  = y_2\\
& y_2^\prime = -\frac{g}{l}\,\sin(y_1) \\
& y_1(0) = y_{1,0},\quad y_2(0) = y_{2,0}
\end{aligned}
\right.
$$

onde $y_1 = \theta$, $y_2 = \frac{d \theta}{dt}$, $y_{1,0} = \theta_0$ e $y_{2,0} = w_0$.

---

O seguinte código determina a solução aproximada desse PVI quando $\theta_0 = \pi/3$, $w_0=0$, $g=9.81$ e $l=1$ no intervalo de tempo $[0, 10]$,  usando os dois métodos descritos acima (M. de Euler e M. de Heun).
Como neste caso temos um sistema de dois EDOs, vamos a usar a funcionalidade do [NumPy](https://http://www.numpy.org/)  para trabalhar com dados vetoriais (*ndarrays*).
"""

#@title
import numpy as nup
from math import pi, sin, cos

#constantes

#gravidade
g = 9.81

#comprimento do pêndulo
l = 1.0

def f(t, y):
    # a função retorna um vetor (objeto numpy.ndarray), construido a partir das duas
    # componentes x[0] e x[1] do vetor x usando a função numpy.array.
    return nup.array( [ y[1], -(g/l)*sin(y[0]) ] )

np = 1000
t0 = 0.0
tf = 10.0
y0 = [pi/3, 0.0]

[t1, y1ap] = met_euler( f, t0, tf, y0, np )
[t2, y2ap] = met_heun( f, t0, tf, y0, np )

"""Agora vamos comparar as soluções obtidas. Observe que existe uma grande diferença entre as duas curvas mostradas na figura."""

#@title
import matplotlib.pyplot as plt

fig = plt.figure(figsize=(10,5))

# Como a solução aproximada foi armazenada como uma lista
# de vetores (ndarrays), usamos essa funcionalidade para
# termos accesso a lista da primeira e a segunda componente
# de cada vetor das listas x1ap e x2ap.
plt.plot( nup.array(y1ap)[:,0], nup.array(y1ap)[:,1], 'b--')
plt.plot( nup.array(y2ap)[:,0], nup.array(y2ap)[:,1], 'r-')

plt.xlabel(u'ângulo')
plt.ylabel('velocidade angular')
plt.title(u'Trajetória no espaço de fase')
plt.legend( ['M.Euler', 'M.Heun'] )

plt.grid(True)

"""A trajetória por ser periódica deve corresponder a uma curva fechada. Observamos que o método de Euler não reproduz esse comportamento. O resultado do método de Heun é bem melhor, a trajetória parece ser fechada!

Agora vamos apresentar um video (animação) dos resultados. Observe como no movimento obtido pelo método de Euler, de forma errada, a energía do pêndulo vai aumentando a cada ciclo.
"""

#@title
# Código para criar a animação dos resultados

from matplotlib import animation, rc
from IPython.display import HTML


# First set up the figure, the axes, and the plot element
fig, ax = plt.subplots()
plt.close()

ax.set_xlim(-1.1*l, 1.1*l)
ax.set_ylim(-1.1*l, 1.35*l)
ax.set_aspect('equal')

ln1, = ax.plot([], [], '--bo')
ln2, = ax.plot([], [], '-ro')
time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)
time_template = 'time = %.2f s'
ax.legend( ['M. Euler', 'M. Heun'] )

# initialization function: plot the background of each frame
def init():
    ln1.set_data([], [])
    ln2.set_data([], [])
    time_text.set_text('')

    return ln1, ln2, time_text


# animation function: this is called sequentially
def animate(i):
    xdata = [0, l*sin(y1ap[i][0])]
    ydata = [0, -l*cos(y1ap[i][0])]
    ln1.set_data(xdata, ydata)


    xdata = [0, l*sin(y2ap[i][0])]
    ydata = [0, -l*cos(y2ap[i][0])]
    ln2.set_data(xdata, ydata)

    time_text.set_text(time_template % (t0+i*(tf-t0)/np))

    return ln1, ln2, time_text


anim = animation.FuncAnimation(fig, animate, init_func=init, frames=range(0,np+1,20),
                               interval=200, repeat_delay=500, blit=True)
rc('animation', html='jshtml')
anim