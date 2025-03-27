# validate.py
from ultralytics import YOLO
model = YOLO("runs\\detect\\train\\weights\\best.pt")  # Load your model
results = model.val(data="data\\data.yaml")  # Run validation
print(results)  # See the output