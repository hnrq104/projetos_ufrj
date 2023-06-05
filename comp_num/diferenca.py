import math

#diferencas divididas de newton
def diferenca(dif_0, dif_1, x_0, x_1):
    return (dif_0 - dif_1)/(x_0 - x_1)

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
            linha.append(diferenca(dif_0,dif_1,x_0,x_1))
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

            vector[pos + 1 + j] = diferenca(dif_0,dif_1,x_0,x_1)

    return vector
         

valoresx = [0, 0.35, 0.65, 1]
tabelae = [1, 1.4190675, 1.9155408, 2.7182818]

resp = n2_bottom_up(tabelae, valoresx)
for i in resp:
    print(i)

print("tentativa o(n)")
resp = n_bottom_up(tabelae,valoresx)
for i in resp:
    print(i)
