import torch
from PIL import Image
import sys

model = torch.hub.load("ultralytics/yolov5",
                       "yolov5s",
                       pretrained=True)

def detect_object(path):
    img = Image.open(path)
    res = model(img)

    return res.pandas.xyxy[0].to_json(orients="records")


if __name__ == "__main__":
    imgPath = sys.argv[1]
    result = detect_object(imgPath)
    print(result)




