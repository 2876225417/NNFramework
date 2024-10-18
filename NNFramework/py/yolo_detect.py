import torch
from PIL import Image
import sys


# py-inter
model = torch.hub.load("ultralytics/yolov5",
                       "yolov5s",
                       pretrained=True)

def detect_object(path):
    img = Image.open(path)
    res = model(img)

    return res.pandas().xyxy[0].to_json(orient="records")


if __name__ == "__main__":

    result = detect_object("2.jpg")
    print("结果为")
    print(result)




