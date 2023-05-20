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


def square(x):
    return x**2

def square_root(x,termos):
    n = x
    for i in range(termos):
        n = (n + x/n)/2
    return n

def sen_sq(x):
    return sin_cos.sin_taylor(square_root(x,10),10)/square_root(x,10)


def tensao(lista,x):    
    



vl = []
h = 0.001
i = 0.0001
while (i <= 1):
    vl.append(sen_sq(i))
    i+=h

func = bar(vl,0,h)

print(approx_p_der(sen_sq,0.0001,h))
print(approx_p_der(func,0.0001,h))



lista = []
lista.append([0,0])
lista.append([0.002,0.287])
lista.append([0.006,0.899])
lista.append([0.012,1.915])
lista.append([0.018,3.048])
lista.append([0.024,4.299])




#tarefa 3

