amount = -1
while amount < 0:
    amount = input("Amount owed: ")
    try:
        amount = float(amount)
    except:
        amount = -1
        continue

cents = round(float(amount) * 100)
coins = 0

while cents > 0:
    if cents >= 25:
        cents -= 25
        coins += 1
    elif cents >= 10:
        cents -= 10
        coins += 1
    elif cents >= 5:
        cents -= 5
        coins += 1
    else:
        cents -= 1
        coins += 1

print(f"{str(coins)}")