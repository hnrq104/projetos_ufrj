# tarefa 2
import sin_cos
import math

def approx_p_der(foo, x0 ,h):
    der = -foo(x0 + 2*h) + 4*(foo(x0 + h)) - 3*foo(x0)
    return der/(2*h)

def approx_pp_der(foo,x0,h):
    return (foo(x0 + h) - foo(x0 - h))/(2*h)

def approx_s_der(foo,x0,h):
    der = -foo(x0 + 3*h) + 4*foo(x0 + 2*h) - 5*foo(x0 + h) + 2*foo(x0)
    return der/h**2

def approx_ss_der(foo,x0,h):
    der = foo(x0 + h) - 2*foo(x0) + foo(x0 - h)
    return der/h**2

def approx_t_der(foo,x0,h):
    der = 15*foo(x0 + 3*h) - 3*foo(x0 + 4*h) - 24*foo(x0 + 2*h)
    der += 18*foo(x0 + h) - 5*foo(x0)

    return der/2*(h**3) 

def approx_tt_der(foo,x0,h):
    der = foo(x0 + 2*h) - 2*foo(x0 + h) + 2*foo(x0 - h) - foo(x0 - 2*h)
    return der/(2*(h**3))

##professor nao gostou

def bar(vlist, x0, h):
    def foobar(x):
        return vlist[math.ceil((x - x0)/h)]
    return foobar



##depois

def primeira_dev_lista(vx, vy,j):
    der = -vy[j + 2] + 4*vy[j + 1] - 3*vy[j]
    return der/(vx[j + 2] - vx[j])

def segunda_dev_lista(vx, vy,j):
    der = -vy[j + 3] + 4*vy[j + 2] - 5*vy[j + 1] + 2*vy[j]
    return der/((vx[j + 1] - vx[j])**2)

def terceira_dev_lista(vx,vy,j):
    der = 15*vy[j + 3] - 3*vy[j + 4] - 24*vy[j + 2]
    der += 18*vy[j + 1] - 5*vy[j]

    return der/(2*((vx[j+1] - vx[j])**3)) 



def square(x):
    return x**2

def square_root(x,termos):
    n = x
    for i in range(termos):
        n = (n + x/n)/2
    return n

def sen_sq(x):
    return sin_cos.sin_taylor(square_root(x,10),10)/square_root(x,10)


def diff(h):
    vx = []
    vy = []
    i = 0
    while(i < 1):
        i+=h
        vx.append(i)
        vy.append(sen_sq(i))

    print("H = ",h,"\n")
    print("Avaliação da primeira derivada em : 1/4")
    print("primeira por lista", primeira_dev_lista(vx,vy,math.floor((1/h)*(1/4))))
    print("primeira por funcao", approx_p_der(sen_sq,0.25,h))
    print("diff = ",primeira_dev_lista(vx,vy,math.floor((1/h)*(1/4))) - approx_p_der(sen_sq,0.25,h))

    print("---------------------------------------------------------\n")

    print("Avaliação da primeira derivada em : 1/2")
    print("primeira por lista", primeira_dev_lista(vx,vy,math.floor((1/h)*(1/2))))
    print("primeira por funcao", approx_p_der(sen_sq,0.5,h))
    print("diff = ",primeira_dev_lista(vx,vy,math.floor((1/h)*(1/2))) - approx_p_der(sen_sq,0.5,h))

    print("---------------------------------------------------------\n")

    print("Avaliação da primeira derivada em : 3/4")
    print("primeira por lista", primeira_dev_lista(vx,vy,math.floor((1/h)*(3/4))))
    print("primeira por funcao", approx_p_der(sen_sq,0.75,h))
    print("diff = ",primeira_dev_lista(vx,vy,math.floor((1/h)*(3/4))) - approx_p_der(sen_sq,0.75,h))

    print("\n")
    return


vx = [0,0.002,0.006,0.012,0.018,0.024]
vy = [0,0.287,0.899,1.915,3.048,4.299]

u = 1.8 * (10**(-5))
print(u * primeira_dev_lista(vx,vy,0))

