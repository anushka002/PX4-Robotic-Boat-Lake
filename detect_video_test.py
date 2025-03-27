# detect_video.py
from ultralytics import YOLO
import cv2

# Load the trained YOLOv8 model
model_path = "runs/detect/train/weights/best.pt"
model = YOLO(model_path)

# Path to the video file
video_path = "C:/Users/ANUSHKA/Desktop/TrashDetect/trash_floating_video.mp4"
cap = cv2.VideoCapture(video_path)

# Check if video opened successfully
if not cap.isOpened():
    print("Error: Could not open video file.")
    exit()

# Process video frames
while True:
    ret, frame = cap.read()
    if not ret:
        break  # End of video

    # Run the model on the frame
    results = model(frame)

    # Plot detections on the frame
    annotated_frame = results[0].plot()

    # Display the frame with detections
    cv2.imshow("Trash Detection in Video", annotated_frame)

    # Collect and print detection results
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
    if detection_list:  # Print only if there are detections
        print(detection_list)

    # Press 'q' to quit early
    key = cv2.waitKey(1)  # 1ms delay per frame (adjustable)
    if key == ord('q'):
        break

# Release video and close windows
cap.release()
cv2.destroyAllWindows()