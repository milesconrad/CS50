from sys import argv, exit

if len(argv) != 3 or not argv[1].endswith(".csv"):
    print("Usage: python dna.py data.csv sequence.txt")
    exit()

try:
    csv_file = open(argv[1], "r")
    global csv_data
    csv_data = csv_file.readlines()
    csv_file.close()

    sequence_file = open(argv[2], "r")
    global sequence
    sequence = sequence_file.readline()
    sequence_file.close()
except:
    print("Usage: python dna.py data.csv sequence.txt")
    exit()

# storing the STRs in a list of strings, then removing that from the actual data
strs = csv_data[0].replace("\n", "")
strs = strs.split(",")
strs.remove("name")
csv_data.remove(csv_data[0])
repeat_count = [0] * len(strs)

# turning the "name" column into a key to a list of integers, which represents STR counts
database = {}
for row in csv_data:
    row = row.replace("\n", "")
    row = row.split(",")

    database[row[0]] = row[1:]
    for i in range(len(database[row[0]])):
        database[row[0]][i] = int(database[row[0]][i])

for i in range(len(strs)):
    cursor = sequence.find(strs[i])
    if cursor == -1:
        continue
    tmp = 1

    while cursor != -1:
        if sequence.find(strs[i], cursor + 1) == cursor + len(strs[i]):
            tmp += 1
        else:
            tmp = 1

        if tmp > repeat_count[i]:
            repeat_count[i] = tmp
        cursor = sequence.find(strs[i], cursor + 1)

for person in database:
    if database[person] == repeat_count:
        print(person)
        exit()
print("No match")