import math
import matplotlib.pyplot as plt
import matplotlib.lines as Line
import numpy as np

def n2_bottom_up(f_list : list, x_list : list):
    matrix = []
    matrix.append(f_list) #order 0
    #will do n^2 first, then O(n) for memory
    for i in range(1,len(f_list)):
        linha = []
        for j in range(len(f_list) - i):
            #unneeded but for clarity sake
            dif_0 = matrix[i-1][j]
            dif_1 = matrix[i-1][j+1]
            x_0 = x_list[j]
            x_1 = x_list[j+i]
            linha.append((dif_0 - dif_1)/(x_0 - x_1))
        matrix.append(linha)

    importantes = []
    for arr in matrix:
        importantes.append(arr[0])
    
    return importantes

def n_bottom_up(f_list : list, x_list : list):
    vector = f_list.copy()
    for i in range(len(vector)):
        pos = len(vector) - i - 1
        for j in range(i):
            dif_0 = vector[pos + j]
            dif_1 = vector[pos + j + 1]
            x_0 = x_list[pos]
            x_1 = x_list[pos + j + 1]

            vector[pos + 1 + j] = (dif_0 - dif_1)/(x_0 - x_1)

    return vector
         
def polinomio_newton(a, c_list : list, x_list : list):
    valor = 0
    for i in range(len(c_list) - 1, 0, -1):
        valor += c_list[i]
        valor*=(a - x_list[i-1])

    valor += c_list[0]
    return valor


def polinomio_lagrange(a, y_list: list, x_list: list):
    soma = 0
    for i in range(len(y_list)):
        prod = 1
        for j in range(len(y_list)): #x e y devem ter o mesmo tamanho
            if(j != i):
                prod *= (a - x_list[j])/(x_list[i] - x_list[j])
        
        soma += y_list[i] * prod
    
    return soma



# valoresx = [0, 0.35, 0.65, 1]
# tabelae = [1, 1.4190675, 1.9155408, 2.7182818]

# xpoints = np.array(valoresx)
# ypoints = np.array(tabelae)


# resp = n_bottom_up(tabelae,valoresx)
# x1 = np.linspace(0,1,1000, endpoint= True)
# y = np.array([polinomio_newton(a,resp,valoresx) for a in x1])

# lagrange_y = np.array([polinomio_lagrange(a,tabelae,valoresx) for a in x1])

# plt.plot(xpoints,ypoints,'bo', label = 'e')
# plt.plot(x1,y,'r',label = 'newton')
# plt.plot(x1,lagrange_y,'--g',label = 'lagrange')
# plt.legend()
# plt.ylabel('valores de e')

#a)
#valores de x inicialmente considerados
nx = []
for i in range(5,25,5):
    x = []
    for j in range(i+1):
        x.append(-1 + (2*j)/i)
    nx.append(x)

def runge(a):
    return 1/(1 + 25*a**2)

#valores para calcular interpolacao
ny = []
for list in nx:
    y = []
    for x in list:
        y.append(runge(x)) 
    ny.append(y)

#os valores de x que serao considerados
x_tilde = []
for i in range(100):
    x_tilde.append(-1 + (2*i + 1)/100)

#avaliacao de runge
y_tilde = []
for x in x_tilde:
    y_tilde.append(runge(x))

#avaliacao da interpolaçao 
aval_pn = []
for i in range(len(nx)):
    p = []
    c = n_bottom_up(ny[i],nx[i])

    for x in x_tilde:
        p.append(polinomio_newton(x,c,nx[i]))
    aval_pn.append(p)

#erro
n_err = []
for list in aval_pn:
    err = []
    for i in range(len(x_tilde)):
        err.append(abs(list[i] - runge(x_tilde[i])))
    n_err.append(err)

for i in range(len(n_err)):
    max = np.max(np.array(n_err[i]))
    print("erro maximo com p = ", (i+1)*5, " é :",max)
    
plt.title('Avaliação polinomial')
plt.plot(x_tilde,y_tilde,'b',label = 'Runge')
plt.plot(x_tilde,aval_pn[0],'r',label = 'p5')
plt.plot(x_tilde,aval_pn[1],'g',label = 'p10')
plt.plot(x_tilde,aval_pn[2],'y',label = 'p15')
plt.plot(x_tilde,aval_pn[3],'m',label = 'p20')
plt.legend()
plt.ylim(-1,1)

#nos de chebychev
n_chev = []
for i in range(5,25,5):
    x = []
    for j in range(i+1):
        x.append(math.cos((math.pi * j)/i))
    n_chev.append(x)

#valores de runge avaliados em chev
chev_y = []
for list in n_chev:
    y = []
    for x in list:
        y.append(runge(x))
    chev_y.append(y)

#considerando os valores de x_tilde
aval_chev = []
for i in range(len(n_chev)):
    c = n_bottom_up(chev_y[i],n_chev[i])
    aval = []
    for x in x_tilde:
        aval.append(polinomio_newton(x,c,n_chev[i]))
    aval_chev.append(aval)

chev_err = []
for aval in aval_chev:
    err = []
    for i in range(len(x_tilde)):
        err.append(abs(aval[i] - runge(x_tilde[i])))
    chev_err.append(err)

for i in range(len(chev_err)):
    max = np.max(np.array(chev_err[i]))
    print('erro maximo com nos de chev : ',(i+1)*5, 'é :', max)


plt.title('Nós de Chebyshev')
plt.plot(x_tilde,y_tilde,'b',label = 'Runge')
plt.plot(x_tilde,aval_chev[0],'r',label = 'chev5')
plt.plot(x_tilde,aval_chev[1],'g',label = 'chev10')
plt.plot(x_tilde,aval_chev[2],'y',label = 'chev15')
plt.plot(x_tilde,aval_chev[3],'m',label = 'chev20')
plt.legend()
plt.ylim(-1,1)
plt.show()


#3
#a
col_x_4 = [80,53.50,38.43,30.39,30]
val = [2*i for i in range(5)]

#linear usa 2 pontos
#se y = 3.2, usamos os mais proximos 2 e 4
print(polinomio_lagrange(3.2,col_x_4[1:3],val[1:3]) , 'linear [2,4]')

#quadratica usa 3 pontos, podemos escolher 0,2,4 ou 2,4,6 (como 3.2 tá mais perto de 6 do que 0, vou escolher o segundo)
print(polinomio_lagrange(3.2,col_x_4[1:4],val[1:4]), 'quadratica [2,4,6]')
print(polinomio_lagrange(3.2,col_x_4[0:3],val[0:3]), 'quadratica [0,2,4]')

#cubica usa 4 pontos mas a ideia é a mesma
print(polinomio_lagrange(3.2,col_x_4[1:5],val[1:5]), 'cubica [2,4,6,8]')
print(polinomio_lagrange(3.2,col_x_4[0:4],val[0:4]), 'cubica [0,2,4,6]')


#b
#escolhi os pontos mais próximos, vê se uma convergência em algo sobre 43.5

#c
#vou escolher os valores vou interpolar em x = [2,4,6], e depois interpolar o resultado
col_x_2 = [90,64.49,48.90,38.78,35]
col_x_6 = [70,48.15,35.03,27.07,25]

#usarei 0,2,4 nessa interpolacao
i_2 = polinomio_lagrange(2.7,col_x_2[0:3],val[0:3]) #x = 2 , y = 2.7
i_4 = polinomio_lagrange(2.7,col_x_4[0:3],val[0:3]) #x = 4 , y = 2.7
i_6 = polinomio_lagrange(2.7,col_x_6[0:3],val[0:3]) #x = 6 , y = 2.7
#resultado: 
print(polinomio_lagrange(4.5,[i_2,i_4,i_6],val[1:4]), 'interpolando primeiro em y e depois em x')


#trocando a ordem de interpolação
line_y_0 = [100,90,80,70,60]
line_y_2 = [85,64.49,53.50,48.15,50]
line_y_4 = [70,48.90,38.43,35.03,40]

#y = 0, x = 4.5
j_0 = polinomio_lagrange(4.5,line_y_0[1:4],val[1:4]) #x = [2,4,6]

#y = 2, x = 4.5
j_2 = polinomio_lagrange(4.5,line_y_2[1:4],val[1:4])

#y = 4, x = 4.5
j_4 = polinomio_lagrange(4.5,line_y_4[1:4],val[1:4])

print(polinomio_lagrange(2.7,[j_0,j_2,j_4],val[0:3]), 'interpolando primeiro em x e depois em y')


