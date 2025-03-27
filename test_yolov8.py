from ultralytics import YOLO
import cv2

# Load the pre-trained YOLOv8 model
model = YOLO("yolov8n.pt")  # 'n' for nano (smallest, fastest)

# Load a sample image
img = cv2.imread("sample.jpg")  # Replace with a real image path

# Run detection
results = model(img)

# Show results
results[0].show()  # Displays the image with detections