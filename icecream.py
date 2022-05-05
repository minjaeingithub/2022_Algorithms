f = open('./input.txt', 'r')
n, l, h, m = map(int, f.readline().split())
price = []
price = [int(x) for x in f.readline().split()]


def find_min(A):
    Temp = 0
    for i in A:
        if Temp == 0 or i < Temp:
            Temp = i
    return Temp


for i in range(n):
    if(price[i] > l):
        continue
    else:
        price[i] = 0

    if(price[i] < h):
        continue
    else:
        price[i] = 0

new_price = []
for k in range(n):
    if price[k] != 0:
        new_price.append(price[k])

min_price = find_min(new_price)

money = m
ice_cream_kinds = 0
for j in range(0, len(new_price)):
    if((money//new_price[j]) >= 1):
        money -= new_price[j]
        ice_cream_kinds += 1
        if(money < min_price):
            fw = open('./output.txt', 'w')
            fw.write(str(ice_cream_kinds))
            fw.close()
