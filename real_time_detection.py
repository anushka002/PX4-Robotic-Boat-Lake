from ultralytics import YOLO
import cv2

# Load the trained YOLOv8 model
model_path = "runs/detect/train/weights/best.pt"
model = YOLO(model_path)

# Initialize the camera (default camera index is 0)
cap = cv2.VideoCapture(0)

while True:
    # Read a frame from the camera
    ret, frame = cap.read()
    if not ret:
        break

    # Run the model on the frame
    results = model(frame)

    # Plot the detections on the frame
    annotated_frame = results[0].plot()

    # Display the frame with detections
    cv2.imshow("Trash Detection", annotated_frame)

    # Collect detection results in a list
    detection_list = []
    for res in results:
        for box in res.boxes:
            class_id = box.cls[0].item()
            confidence = box.conf[0].item()
            x1, y1, x2, y2 = box.xyxy[0].detach().cpu().numpy()
            class_name = model.names[class_id]
            detection_list.append({
                'class': class_name,
                'coordinates': [x1, y1, x2, y2],
                'confidence': confidence
            })

    # Print the list of detections
    print(detection_list)

    # Wait for a key press (press 'q' to quit)
    key = cv2.waitKey(1)
    if key == ord('q'):
        break

# Release the camera and close windows
cap.release()
cv2.destroyAllWindows()