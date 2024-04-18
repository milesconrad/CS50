text = input("Text: ")

L = 0
S = 0
words = 0
skip = False
for char in text:
    if skip:
        skip = False
        continue

    char_int = ord(char)
    if (char_int >= 65 and char_int <= 90) or (char_int >= 97 and char_int <= 122):
        L += 1

    elif char == '.' or char == '!' or char == '?':
        skip = True
        S += 1
        words += 1

    elif char == " ":
        words += 1

S = (100 / words) * S
L = (100 / words) * L
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {str(index)}")