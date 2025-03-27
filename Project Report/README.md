# Towards Robotic Trash Removal with Autonomous Surface Vessels

**Chinmay Amrutkar¹, Anushka Satav G²**  

Masters Students in Robotics and Autonomous Systems (AI), Arizona State University, Tempe, AZ, USA  

---

## Abstract  
Plastic pollution severely threatens aquatic ecosystems, with Tempe Town Lake increasingly littered by single-use plastics, endangering wildlife and water quality. This project develops an autonomous robotic boat system to detect and remove surface trash using advanced computer vision and digital twin technologies. A YOLOv8-based trash detection system, trained on the 'Waste in Water' dataset (3,798 images, 19 classes), achieved an mAP50 of 0.264 on validation data. Static tests on two images reliably detected 'Plastic Bottle' (up to 0.938, 29 instances) but missed 'Can,' while video tests on a sample video consistently identified 'Plastic bottle' (up to 0.82, ~50 instances), frequently spotted 'Plastic cup' (~30 instances, 0.3–0.68), and occasionally found 'Plastic bag' (~15 instances, up to 0.79), with gaps for smaller items. Validation showed strong performance for 'Plastic Bottle' (mAP50=0.878) but none for 'Can' (mAP50=0.000), suggesting a unified 'trash' class. A Gazebo-integrated PX4 SITL simulation models a robotic boat for real-time trash identification, laying the groundwork for hardware deployment to improve urban lake cleanup.  

**_Keywords:_** Trash detection, robotic boat, Tempe Town Lake, computer vision, YOLOv8, Gazebo, PX4 SITL, plastic pollution, real-time detection  

---

## 1. Introduction  

### 1.1 Background  
Annually, over 380 million tons of plastic are produced, a material that resists natural breakdown and is challenging to recycle, leading to persistent environmental pollution. Approximately 80% of beach litter stems from single-use plastics like bottles and wrappers, posing lethal risks to marine life through ingestion or entanglement. Globally, over 8 million tons of plastic enter oceans yearly, smothering ecosystems, while beaches face constant littering from human activity. Without intervention, plastic may soon rival fish in ocean volume, necessitating urgent action to protect aquatic life.  

### 1.2 Project Significance  
With plastic pollution escalating—8 million tons entering oceans annually and 80% of beach litter from single-use items—Tempe Town Lake, a key urban site, faces growing trash accumulation, threatening its ecosystem. Manual cleanup is slow and inadequate. This project employs robotics and AI for real-time trash detection and removal, offering an efficient, scalable solution. Its potential extends beyond Tempe Town Lake, supporting global conservation efforts through sustainable technology.  

---

## 2. Goals and Scope  

### 2.1 Primary Goal  
The project aims to create an autonomous robotic boat system using computer vision and robotics to detect and eventually remove trash from Tempe Town Lake, reducing human effort and showcasing environmental applications of technology.  

### 2.2 Specific Objectives  
- **Real-Time Trash Detection:** Develop a computer vision system to identify floating debris on Tempe Town Lake in real time, fine-tuned on aquatic trash datasets, tested on sample images and videos, and later integrated into robotic hardware.  
- **Gazebo-Integrated PX4 SITL Simulation:** Build a simulation of a robotic boat performing a lawnmower survey pattern in a virtual Tempe Town Lake, enhanced with a camera to detect and collect simulated trash, proving the concept before hardware use.  

### 2.3 Project Scope  
The mid-term focuses on software—trash detection and simulation—for Tempe Town Lake’s surface trash. The final phase integrates this with provided robotic hardware, simulating collection without physical mechanisms, excluding underwater detection or multi-robot systems due to constraints.  

---

## 3. Methodology  

### 3.1 Computer Vision System Design  

#### 3.1.1 System Overview  
The trash detection system uses a YOLOv8 model, chosen for its speed and accuracy, initialized with COCO dataset weights and fine-tuned for aquatic trash detection, targeting deployment on a robotic boat.  

#### 3.1.2 Environment Setup  
A Python environment (3.8 or 3.9) was set up in a virtual workspace named "myenv" at C:\Users\ANUSHKA\Desktop\TrashDetect. Essential libraries—ultralytics, opencv-python, and numpy—were installed for YOLOv8 operations. A PowerShell restriction was bypassed to activate the environment, ensuring smooth training and testing workflows. Initial tests with a pre-trained YOLOv8n model on a sample image confirmed functionality, detecting COCO objects like cars but not trash, setting the stage for fine-tuning.  

#### 3.1.3 Data Acquisition and Preparation  
The 'Waste in Water' dataset from RoboFlow Universe (3,798 images, 19 classes) was used, pre-split into training (~70%), validation (~20%), and test (~10%) sets. Images were resized to 640x640 with augmentations (e.g., flips) and stored at C:\Users\ANUSHKA\Desktop\TrashDetect\data, supporting robust trash detection development.  

#### 3.1.4 YOLOv8 Model Training  
The YOLOv8n model was trained on the dataset for 50 epochs over 9.314 hours on an AMD Ryzen 7 6800H CPU. Post-training weights were optimized to 6.3MB each, stored at runs\detect\train\weights\. Static tests detected 'Plastic Bottle' well (up to 0.938, 29 instances), while video tests on 'trash_floating_video.mp4' showed consistent 'Plastic bottle' detection (~50 instances, up to 0.82), frequent 'Plastic cup' (~30, 0.3–0.68), and occasional 'Plastic bag' (~15, up to 0.79).  

#### 3.1.5 Validation and Testing  
Validation on 157 images (588 instances) yielded an mAP50 of 0.264, with 'Plastic Bottle' at 0.878 but 'Can' at 0.000, suggesting class unification. Testing scripts processed static images and video, confirming strong detection of prominent trash but gaps for smaller items.  

![image](https://github.com/user-attachments/assets/e1e59383-db54-4098-8e9a-d926efc49324)


### 3.2 Gazebo and PX4 SITL Simulation Design  

#### 3.2.1 System Requirements and Setup  
The simulation runs on Ubuntu 22.04 with ROS2 Humble, Gazebo Classic (v11), and PX4 v1.14, using an AMD Ryzen 7 CPU. ROS2 and Gazebo were installed per official guides, with PX4 SITL launched via a standard command, verified by spawning a default boat model.  

#### 3.2.2 Boat Model Modifications  
A PX4 boat model was enhanced with a 640x640 RGB camera at the bow (90° FOV), streaming to a ROS2 topic. Control parameters set a 0.5 m/s speed and 1m waypoint tolerance for a lawnmower pattern, with a 5 kg, 1m x 0.5m hull for realistic dynamics.  

#### 3.2.3 Gazebo World Modifications  
The default boat.world was modified with Tempe Town Lake coordinates (33.4326° N, -111.9321° W) for QGroundControl display. Twenty trash objects (10 spheres, 10 rectangles, 0.01–0.1 kg) were added, floating via a custom libtrashbuoyancy.so plugin. Default daylight is used, with future lighting variations planned. Initial tests confirmed camera detection of trash.  

#### 3.2.4 Simulation and Testing  
The boat will follow a lawnmower pattern over 100m x 50m, with YOLOv8 processing camera data. Ten runs will assess coverage (>95%), detection rate (≥90%), and time (<15 min), integrating vision outputs to adjust navigation, planned for the final phase.  

---

## 4. Results  

### 4.1 Trash Detection Performance  
The YOLOv8 model achieved an mAP50 of 0.264 on validation (157 images, 588 instances). Static tests detected 'Plastic Bottle' accurately (up to 0.938, 29 instances) but missed 'Can.' Video tests consistently spotted 'Plastic bottle' (~50 instances, up to 0.82), often 'Plastic cup' (~30, 0.3–0.68), and occasionally 'Plastic bag' (~15, up to 0.79), with misses for small items. Inference averaged 25–35ms on CPU, meeting speed goals but needing broader class detection.  

![gif trash](https://github.com/user-attachments/assets/6b2fc31c-5150-4175-aed4-c02d18703d5d)



### 4.2 Simulation Outcomes  
The Gazebo-PX4 SITL setup includes a boat with a camera and plugins, operating in a modified boat.world with 20 dummy trash objects. Initial tests showed the camera detecting trash in a virtual Tempe Town Lake, establishing a base for navigation and collection algorithms, with metrics pending further control implementation.  

### 4.3 Analysis and Visualizations  
Errors occur in low-contrast settings (15% false negatives), and simulation misses edge objects. Visuals include detection outputs and a survey path with trash overlays, guiding refinements.  

---

## 5. Conclusion  
The YOLOv8 model, trained on 3,798 images, hit an mAP50 of 0.264, excelling at 'Plastic bottle' detection (0.938) but missing 'Can.' The Gazebo-PX4 simulation successfully detected simulated trash in a virtual Tempe Town Lake. Challenges include lighting variability, simulation realism, and CPU constraints. Next steps involve class unification, precision improvement (>90%), and real-world testing on Tempe Town Lake for hardware integration.  

---

## 6. References  
- Marine Mammal Center: Ocean Trash - https://www.marinemammalcenter.org/science-conservation/conservation/ocean-trash  
- ScienceDirect: Plastic Pollution - https://www.sciencedirect.com/science/article/pii/S2666016420300244  
- Schmaltz, E., et al. (2020). Plastic Pollution Solutions - https://www.sciencedirect.com/science/article/pii/S0160412020318476  
- RoboFlow Universe: Waste in Water Dataset - https://universe.roboflow.com/chinatele/waste-in-water/dataset/1, CC BY 4.0  
- EU Commission: Aquatic Biosensors - https://environment.ec.europa.eu/news/aquatic-biosensors-glow-fireflies-they-detect-disintegrating-plastic-debris-2023-07-05_en  

---

## 7. GitHub Link and Project Status  
**Link:** https://github.com/anushka002/PX4-Robotic-Boat-Lake

**Status:** As of March 26, 2025, the project meets mid-term goals. The vision system functions, targeting >90% precision and <80ms inference. The simulation is operational, needing navigation tuning. Next steps include optimization, realism enhancements, and hardware prep.  

**Final Goal:** Integrate real-time detection onto a physical boat, demonstrating autonomous trash survey and simulated collection at Tempe Town Lake.  
