import math

def sin_taylor(h, termos):
    
    pn = 1
    x = h

    while(x < 0):
        x+= 2*math.pi

    while(x  > 2*math.pi):
        x-= 2*math.pi

    fat = 1
    potencia_x = 1
    soma = 0

    #kahan
    # e = 0

    for i in range(1,termos):
        fat*=i
        potencia_x*=x
        
        if(i%2 == 0):
            continue
        
        sinal = 2 - i%4
        # i%4 = {1,3}
        soma += sinal*(potencia_x/fat)

    return soma

def cos_taylor(h,termos):
    return sin_taylor(h + (math.pi)/2, termos)

            


