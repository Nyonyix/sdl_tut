import json
import os

def loadImage(img_path: str, json_path: str) -> list:

    raw = []
    tiles_def = {}
    row = []
    image = []
    size = []

    with open(img_path, 'r') as f:
        raw = f.readlines()

    with open(json_path, 'r') as f:
        tiles_def = json.load(f)
    
    image_map = {}
    c_iter = 0
    for i in range(len(raw)):
        if i <=1:
            continue

        elif i == 2:
            size = raw[i].split()[0:2]
            size[0] = size[0][1:]
            continue

        elif 'c' in raw[i]:
            image_map[raw[i][1]] = []
            image_map[raw[i][1]].append(raw[i][5:12])
            image_map[raw[i][1]].append(c_iter)
            c_iter += 1
            continue

        else:
            print(raw[i][1:int(size[0])+1])
            for char in raw[i][1:int(size[0])+1]:
                if char in image_map.keys():
                    colour = image_map[char][0]
                    
                    for var, val in tiles_def.items():

                        if colour == val["colour"]:
                            row.append(var)

            image.append(row)
            row = []

    return image

def writeImage(path: str, image: list) -> None:
    
    new_line = ""

    if os.path.exists(path):
        yes = ["y", "Y", "yes", "YES"]
        no = ["n", "N", "no", "NO"]
        usr_input  = "y"
        usr_input = input("Output file already exists, Overwrite existing File?\n")

        if usr_input in yes:
            os.remove(path)
        elif usr_input not in no:
            exit("Unrecognised response")

    with open(path, 'a') as f:
        for line in image:
            for char in line:
                new_line += char +","

            new_line = new_line[:-1]
            new_line += '\n'
            f.write(new_line)
            new_line = ""

if __name__ == "__main__":
    if len(os.sys.argv) < 4:
        exit("Error: Unrecognised or missing arguments")

    writeImage(os.sys.argv[3], loadImage(os.sys.argv[1], os.sys.argv[2]))
    os.remove(os.sys.argv[1])