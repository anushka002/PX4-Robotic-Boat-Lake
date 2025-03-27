from ultralytics import YOLO
import cv2

# Load the trained YOLOv8 model
model_path = "runs/detect/train/weights/best.pt"
model = YOLO(model_path)

# Path to the sample image
sample_image_path = "C:/Users/ANUSHKA/Desktop/TrashDetect/trash_sample_image.jpg"

# Load the sample image using OpenCV
img = cv2.imread(sample_image_path)

# Run the model on the sample image
results = model(img)

# Plot the detections on the image
annotated_img = results[0].plot()

# Display the image with detections using OpenCV
cv2.imshow("Sample Image Detection", annotated_img)
cv2.waitKey(0)  # Wait until any key is pressed
cv2.destroyAllWindows()

# Optionally, print the detection results
for res in results:
    for box in res.boxes:
        class_id = box.cls[0].item()
        confidence = box.conf[0].item()
        x1, y1, x2, y2 = box.xyxy[0].detach().cpu().numpy()
        class_name = model.names[class_id]
        print(f"Class: {class_name}, Confidence: {confidence}, Coordinates: ({x1}, {y1}, {x2}, {y2})")