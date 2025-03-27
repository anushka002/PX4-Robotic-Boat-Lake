from ultralytics import YOLO

# Load the model
model = YOLO("yolov8n.pt")  # Pre-trained nano model

# Train the model
model.train(
    data="C:/Users/ANUSHKA/Desktop/TrashDetect/data/data.yaml",
    epochs=50,
    imgsz=640
)