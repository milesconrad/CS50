def luhns(credit_card):
    digit_sum = 0

    i = len(credit_card) - 2
    tmp = 0
    while i >= 0:
        tmp = int(credit_card[i]) * 2
        # division will return a float, we just want the number in the 10s place
        digit_sum += int(tmp / 10)
        digit_sum += tmp % 10

        i -= 2

    i = len(credit_card) - 1
    while i >= 0:
        digit_sum += int(credit_card[i])
        i -= 2

    return (digit_sum % 10 == 0)


def main():
    card_number = -1
    while type(card_number) == int:
        card_number = input("Number: ")
        try:
            if int(card_number) <= 0:
                raise TypeError()
        except:
            card_number = -1
            continue

    if luhns(card_number):
        length = len(card_number)
        if length == 13 or length == 15 or length == 16:
            if card_number[0] == "3":
                if card_number[1] == '4' or card_number[1] == '7':
                    print("AMEX")
                    return
                else:
                    print("INVALID")
            elif card_number[0] == "4":
                print("VISA")
                return
            elif card_number[0] == "5":
                for i in range(1, 6):
                    if i == int(card_number[1]):
                        print("MASTERCARD")
                        return
                print("INVALID")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()