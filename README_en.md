# 🧠 ROBOGait Project – Client (GUI) and ROS2 Server

This project includes the graphical user interface developed with Qt and the server infrastructure using ROS2 and Flask to control the ROBOGait robot.

---

## Prerequisites
- Ubuntu 22.04  
- Internet connection  
- UPM student account for Qt license
- Computer to install Android Studio
- Tablet with Android
--- 

## Graphical User Interface (GUI)
This project includes everything needed to build it in Qt Creator.

### Steps to install Qt Creator:
1. Download Qt Creator from the official website using your UPM student email and license: [link](https://www.qt.io/qt-educational-license#application).
2. If you want to develop for Android, follow these [steps](https://doc.qt.io/qt-6/android-getting-started.html).
3. **Note**: You must enable developer mode on your phone/tablet to compile the code on your device. Here is a [video](https://youtu.be/f91wxQdP8Ak?si=0kSbNOwmc2m3rqNe) explaining how to do it.

---

## Server
This section includes the necessary information to set up the server and communicate with the client (tablet/mobile). This server must be complemented with the code from RoboGait Indoor v3 (as of 24/05/2025).

### Steps to install dependencies:
1. Install ROS 2 Humble: [Link](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html)
2. Install system dependencies:
    ```bash
    sudo apt install build-essential cmake libboost-system-dev libyaml-cpp-dev nlohmann-json3-dev libopencv-dev
    ```
3. Install Python dependencies on Linux:
    ```bash
    sudo apt update
    sudo apt install python3 python3-pip
    pip install Flask
    ```

---

## Ports
This project uses ports, so if you are on Linux, don’t forget to enable them:

```bash
sudo ufw enable
sudo ufw allow 45454
```

| Port   | Protocol | Purpose                                |
|--------|----------|----------------------------------------|
| 45454  | UDP  | Connection between client and server   |
| 45454  | TCP  | Connection between client and server   |

---

## Troubleshooting

If you encounter errors related to QtQuick, run:
```bash
sudo apt install qml-module-qtquick-layouts
```

If Gazebo fails to run, try:
```bash
source /usr/share/gazebo/setup.sh
```

To launch RViz2 with Turtlebot3 navigation:
```bash
ros2 run rviz2 rviz2 -d $(ros2 pkg prefix nav2_bringup)/share/nav2_bringup/rviz/nav2_default_view.rviz
```

<!-- ## Getting Started

To get started with this project, follow the steps below:

1. **Clone the repository**  
   Clone the repository to your local machine using the following command:
   ```bash
   git clone <REPOSITORY_URL>
   cd GUI_ROBOGAIT/server
   ```

2. **Build the project**  
   Make sure you have ROS 2 and its dependencies installed. Then, run the following command to build the project, ensuring you are in the `GUI_ROBOGAIT/server` directory:
   ```bash
   colcon build
   source install/setup.bash
   ```

3. **Run the main node**  
   Once the build is complete, you can run the main node of the project with the following command:
   ```bash
   ros2 run node_manager node_manager
   ```

With these steps, you'll have the server set up and ready for use. -->