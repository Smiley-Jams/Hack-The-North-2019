from random import randint
import json

if __name__ == "__main__":
    with open("out.json", "w+") as map:
        data = {
            # This is just the render info for the tilemap
            "tiles": [],
            # This contains specific information of resources in each tile
            "resources": []
        }
        for y in range(16):
            for x in range(16):
                data["tiles"].append(randint(1, 3))
                data["resources"].append({
                    "wood": randint(0, 10),
                    "ore": randint(0, 10),
                    "wool": randint(0, 10)
                })
        json.dump(data, map)