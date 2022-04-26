n, l, h, m = map(int, input().split())
price = []
price = [int(x) for x in input().split()]

for i in range(n):
    if(price[i] > l):
        continue
    else:
        price[i] = 0

    if(price[i] < h):
        continue
    else:
        price[i] = 0

for k in range(n):
    if price[k] == 0:
        price.remove(k)

sorted_price = sorted(price)
min_price = min(sorted_price)

money = m
ice_cream_kinds = 0
for j in range(0, len(price)):
    if((money//price[j]) >= 1):
        money -= price[j]
        ice_cream_kinds += 1
        if(money < min_price):
            print(ice_cream_kinds)
