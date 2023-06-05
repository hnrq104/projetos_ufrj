import math

def produto_interno(v1 : list, v2: list):
    if(len(v1) != len(v2)): return None

    soma = 0
    for i in range(len(v1)):
        soma += v1[i]*v2[i]
    return soma

def prod_escalar(v1: list, alpha):
    vet = []
    for i in v1:
        vet.append(i*alpha)
    return vet

def normaliza(vetor : list):
    normalizado = []
    norma = 0
    for i in vetor:
        norma += i**2
    
    norma = math.sqrt(norma)
    for i in vetor:
        normalizado.append(i/norma)
    
    return normalizado

#altera o vetor
def vetor_sub(a: list, b: list):
    if(len(a) != len(b)): return None
    #vetor = []
    for i in range(len(a)):
        a[i] = a[i] - b[i]
        #vetor.append(a[i] - b[i])

    return a

def gram_schmidt(vetores : list):
    base = []
    for vetor in vetores:
        w = vetor.copy()
        for b in base:
            prod = produto_interno(vetor,b)
            sub = prod_escalar(b,prod)
            w = vetor_sub(w,sub)
        
        zero = True
        for k in w:
            if(k!= 0): zero = False
        
        if (not zero): base.append(normaliza(w))

    return base


vs = [[1,1,0,1],[1,-1,0,0],[1,1,0,-1]]
base = gram_schmidt(vs)
for v in base:
    print(v)