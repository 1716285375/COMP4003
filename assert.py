import os
from tkinter import CHAR

assert_root = "./assets"

map_path = os.path.join(assert_root, 'Tiles')
character_path = os.path.join(assert_root, 'roles')
bg_path = os.path.join(assert_root, 'bg')
sound_path = os.path.join(assert_root, 'sounds')
font_path = os.path.join(assert_root, 'tonts')

save_path = os.path.join(assert_root, "assert.txt")

# single grid size
pic_size = [18, 18]

# texture
with open(save_path, "w") as f:
    tmp = os.listdir(map_path)
    if tmp:
        for t in tmp:
            f.write(f"Texture tile{int(t.split('.')[0].split('_')[1])}" + os.path.join(map_path, t) + "\n")
# role
with open(save_path, "a") as f:
    tmp = os.listdir(character_path)
    if tmp:
        for t in tmp:
            f.write(f"Texture role{int(t.split('.')[0])}" + os.path.join(character_path, t) + "\n")

# animation
with open(save_path, "a") as f:
    tmp = os.listdir(map_path)
    if tmp:
        for t in tmp:
            f.write(f"Texture tile{int(t.split('.')[0].split('_')[1])} 1 0" + "\n")
    tmp = os.listdir(character_path)
    if tmp:
        for t in tmp:
            f.write(f"Texture role{int(t.split('.')[0])} 1 0" + "\n")


# fonts
with open(save_path, "a") as f:
    tmp = os.listdir(font_path)
    if tmp:
        for t in tmp:
            f.write(f"Font {t.split('.')[0]}" + os.path.join(font_path, t) + "\n")
    else:
        print("don't exist Font file")

# sounds
with open(sound_path, "a") as f:
    tmp = os.listdir(sound_path)
    if tmp:
        for t in tmp:
            f.write(f"Sound {t.split('.')[0]}" + os.path.join(sound_path, t) + "\n")
    else:
        print("don't exist Sound file")