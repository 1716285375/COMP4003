import os
import json


with open("./assets/map.json", "r") as f:
    data = json.load(f)

# print(data['layers'][0]['data'])
print(len(data['layers'][0]['data']))
map = data['layers'][0]['data']

info = {
    'water': [13, 14, 15, 29, 30, 31, 45, 46, 47, 78, 79, 94, 95],
    'sling': [7, 8, 23, 24, 39, 40, 55, 56, 71, 72],
    'pipe': [59, 75, 91, 107, 76, 77, 92, 93, 108, 109, 110, 111],
    'ground': [1, 2, 3, 4, 5, 6, 20, 21, 22, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51, 62, 63, 87, 88, 89, 90, 103, 104, 105, 106],
    'stair': [11, 27, 43, 36, 38, 52, 68],
    'dec': [12, 28, 44, 25, 26, 41, 42, 57, 58, 64, 65, 66, 67, 73, 74, 80, 81, 82, 96, 97, 98],
    'obstacle': [9, 10, 37, 53, 54, 70, 69, 83, 84, 85, 86, 99, 100, 101, 102],
    'stuff': [60, 61]
    }

number = []
for key, value in info.items():
    number += info[key]

number.sort()
# print(len(info['water']), len(set(info['water'])))

assert(len(info['water']) == len(set(info['water'])))
assert(len(info['sling']) == len(set(info['sling'])))
assert(len(info['pipe']) == len(set(info['pipe'])))
assert(len(info['ground']) == len(set(info['ground'])))
assert(len(info['stair']) == len(set(info['stair'])))
assert(len(info['dec']) == len(set(info['dec'])))
assert(len(info['obstacle']) == len(set(info['obstacle'])))
assert(len(info['stuff']) == len(set(info['stuff'])))
assert(len(number) == len(set(number)))

# print(len(number), len(set(number)))

lst = [i for i in range(112)]

diff = list(set(lst) - set(number))
diff.sort()
# print(diff)


cfg = ""
for i in range(60):
    for j in range(100):
        if map[i * 100 + j] != 0:
            for key, value in info.items():
                if map[i * 100 + j] in info[key]:
                    data = "{} tile{} {} {}".format(key, map[i * 100 + j] - 1, j, i) + "\n"
                    print(data)
                    cfg += data

# print(cfg)

with open("./assets/level_1.txt", "w") as f:
    f.write(cfg)