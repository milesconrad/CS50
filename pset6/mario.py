depth = -1
while depth < 1 or depth > 8:
    depth = input("Height: ")
    try:
        depth = int(depth)
    except:
        depth = -1
        continue
line_length = depth * 2 + 2

line = ""
for i in range(1, depth + 1):
    for j in range(depth):
        if j < depth - i:
            line += ' '
        else:
            line += "#"

    line += "  "

    for j in range(depth + 2, line_length):
        if j < depth + 2 + i:
            line += '#'
        else:
            break

    print(line)
    line = ""