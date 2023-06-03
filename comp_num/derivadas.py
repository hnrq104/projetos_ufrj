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
    der = 14*foo(x0 + 3*h) - 3*foo(x0 + 4*h) - 24*foo(x0 + 2*h)
    der += 18*foo(x0 + h) - 5*foo(x0)

    return der/2*(h**3) 

def approx_tt_der(foo,x0,h):
    der = foo(x0 + 2*h) - 2*foo(x0 + h) + 2*foo(x0 - h) - foo(x0 - 2*h)
    return der/(2*(h**3))


def primeira_avancada(v,h):
    #v[] = fx, f(x + h) , f(x + 2h)
    soma = -3*v[0] + 4*v[1] - v[2]
    return soma/(2*h)

def primeira_centrada(v,h):
    #v  = f(x-h),f(x),f(x+h)
    soma = v[2] - v[0]
    return soma/(2*h)

def segunda_avancada(v,h):
    soma = 2*v[0] - 5*v[1] + 4*v[2] - v[3]
    return soma/h**2

def segunda_centrada(v,h):
    soma = v[0] - 2*v[1] + v[2]
    #-h , 0, + h
    return soma/(h**2)

def terceira_avancada(v,h):
    soma = -5*v[0] + 18*v[1] - 24*v[2] +  14*v[3] - 3*v[4]
    return soma/2*(h**3)

def terceira_centrada(v,h):
    #-2h, -h, h, 2h
    soma = -v[0] + 2*v[1] - 2*v[2] + v[3]
    return soma/2*(h**3)
    

# def square(x):
#     return x**2

# def square_root(x,termos):
#     n = x
#     for i in range(termos):
#         n = (n + x/n)/2
#     return n

def sen_sq(x):
    sqr = math.sqrt(x)
    return math.sin(sqr)/sqr


def derivada(x):
    sqr = math.sqrt(x)
    return (math.cos(sqr)*sqr - math.sin(sqr))/(2*x*sqr)

def diff(h,x):
    #algebrica
    resp = []
    resp.append(derivada(x))

    #avancada
    lista1 = []
    for i in range(3):
        lista1.append(sen_sq(x + i*h))
    
    resp.append(primeira_avancada(lista1,h))

    #centrada
    lista2 = []
    for i in range(-1,2):
        lista2.append(sen_sq(x + i*h))
    
    resp.append(primeira_centrada(lista2,h))
    
    return resp


h_values = [0.1,0.01,0.001,0.0001]
x_values = [0.25, 0.5, 1]

for i in x_values:
    print("funcao avaliada em : ", i)
    for j in h_values:
        resp = diff(j,i)
        print("h = ", j)

        print("algebrica = ", resp[0])
        print("avancada = ", resp[1], " diff = ", resp[1] - resp[0])
        print("centrada = ", resp[2], " diff = ", resp[2] - resp[0])

        print("\n")