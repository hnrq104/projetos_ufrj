import math

def sin_taylor(h, termos):
    fat = 1
    potencia_h = 1
    soma = 0

    #kahan
    # e = 0

    for i in range(1,termos):
        fat*=i
        potencia_h*=h
        
        if(i%2 == 0):
            continue
        
        sinal = 2 - i%4
        # i%4 = {1,3}
        soma += sinal*(potencia_h/fat)

    return soma

print("taylor sin (pi/6 , 10) = ", sin_taylor(math.pi/6,100))
            


