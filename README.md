# PX4-Robotic-Boat-Lake

# PX4 Lake Boat Simulator

Welcome to the **PX4 Lake Boat Simulator**! This project uses PX4 Autopilot and Gazebo to simulate a robotic boat navigating a lake, equipped with a camera to detect floating trash on the water surface. The goal is to create a foundation for environmental cleanup robotics, with trash detection and removal as future enhancements.

## Project Overview
This repository simulates:
- A robotic boat operating in a lake environment.
- A camera mounted on the boat to visually detect floating trash (e.g., plastic bottles, debris).
- Placeholder trash objects in the simulation.

 **Current Scope**: Focus is on setting up and running the simulation. Future work includes adding a trash detection algorithm and a capture mechanism.

## What is PX4 Autopilot?
PX4 is an open-source flight control software primarily for drones, but it’s flexible enough to support boats, rovers, and more. Here, we use PX4 with Gazebo to simulate our robotic boat.

## Prerequisites
- **Operating System**: Ubuntu 20.04 or 22.04 (native or via VM).
- **Hardware**: A computer with at least 8GB RAM and a decent GPU for Gazebo.
- **Software**:
  - Git
  - PX4 Firmware
  - Gazebo Simulator (included with PX4)
  - QGroundControl
- Basic terminal and Git knowledge.

## Installation

### 1. Install Required Software
1. **Update Ubuntu**:
   ```
   sudo apt update && sudo apt upgrade -y
   Ensures your system is up-to-date.
   ```
2. **Install Git**:
   ```
   sudo apt install git -y
   ```
4. **Download QGroundControl**:
   Get it from [here](https://docs.qgroundcontrol.com/master/en/qgc-user-guide/getting_started/download_and_install.html) and install it:
   ```
   chmod +x ./QGroundControl.AppImage
   ./QGroundControl.AppImage
   ```
---

### 2. Clone This Repository
Run on a New Terminal:
```
git clone https://github.com/[YourUsername]/PX4-LakeBoatSim.git
cd PX4-LakeBoatSim
```
---

### 3. Set Up PX4 Firmware
  1. Clone PX4 Firmware:
     
    git clone https://github.com/PX4/PX4-Autopilot.git --recursive
    cd PX4-Autopilot
    
  --recursive ensures all submodules are included.
  
  2. Install PX4 Dependencies:

    bash ./Tools/setup/ubuntu.sh
    
  If errors occur, install Python 3 manually:

    sudo apt install python3-pip -y


---

### 4. Boat Simulation on PX4 and Gazebo Classic:

The existing UUV models only work on Gazebo Classic, hence we install gazebo-classic as follows:

1. On Terminal run:

        curl -sSL http://get.gazebosim.org | sh
2. Run

        gazebo




### **1. Add the Boat Model:**
This repo includes a basic boat model in /models/boat_lake.sdf.

Copy it to the PX4 Gazebo models directory:

cp ../models/boat_lake.sdf ./Tools/sitl_gazebo/models/

### **2. Add the Lake Environment:**

Use the included lake world file (/worlds/lake.world):


cp ../worlds/lake.world ./Tools/sitl_gazebo/worlds/

### **3. Update PX4 Configuration:**
Modify the SITL launch file to use the boat and lake:


nano ./ROMFS/px4fmu_common/init.d-posix/rcS
Replace the default vehicle line (e.g., iris) with:

vehicle boat_lake
Save and exit (Ctrl+O, Enter, Ctrl+X).

### **4. Run the Simulation**

Launch the Simulation:

    make px4_sitl gazebo

This starts Gazebo with the lake environment and the boat. You’ll see a simple boat model in a water world with floating objects (placeholders for trash).

### **5. Connect QGroundControl:**

Open QGroundControl to view the camera feed and monitor the boat.

---
### Simulate Trash Detection

Floating objects (e.g., cubes, cylinders, etc.) are spawned in the lake as mock trash.
The boat’s camera (defined in boat_lake.sdf) captures the scene.
Trash detection is a placeholder—future work will integrate an algorithm (e.g., OpenCV).

---

### Current Features
  Simulated robotic boat with a camera in Gazebo.
  Lake environment with water and floating objects (mock trash).
  Integration with PX4 SITL and QGroundControl.

### Future Plans
  Develop a trash detection algorithm using the camera feed.
  Simulate a trash capture mechanism (e.g., a net or arm).
  Enhance boat autonomy for trash collection missions.

---

---
### Troubleshooting
Gazebo crashes: Update graphics drivers:

    sudo ubuntu-drivers autoinstall
    
Boat not visible: Verify boat_lake.sdf is in Tools/sitl_gazebo/models/.
No camera feed: Check the <sensor> tag in boat_lake.sdf.

**Notes:**
The boat model (boat_lake.sdf) is basic. You may need to tweak its physics or appearance.
Trash objects are static for now—dynamic spawning is a future enhancement.










