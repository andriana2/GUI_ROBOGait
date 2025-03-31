# GUI ROBOGait

This project is divided into two parts: **GUI**, which refers to the client and graphical interface, and **Server**, which includes various servers, ROS2 nodes, and the robot.

## GUI
This section contains everything needed to compile the project in Qt Creator.

### Steps to Install Qt Creator:
+ Download it from the official website using a student license and your UPM email. [Link](https://www.qt.io/qt-educational-license#application)
+ If you want to use it for Android development, follow these [steps](https://doc.qt.io/qt-6/android-getting-started.html).
+ _Note_: You must enable the developer option on your mobile/tablet to compile the code on your device. [Video](https://youtu.be/f91wxQdP8Ak?si=0kSbNOwmc2m3rqNe)

## Server
This section provides the necessary information to set up the server and communicate with the client (tablet/mobile). However, it must be complemented with the **RoboGait Indoor V3** code (as of **March 31, 2025**).

### Steps to Install the Required Dependencies:
+ Install ROS2 Humble [Link](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html)
+ Dependencias con el robot:
  ```bash
  sudo apt install build-essential cmake libboost-system-dev libyaml-cpp-dev nlohmann-json3-dev libopencv-dev
  ```
+ Dependencias con la base de datos:
````bash
sudo apt install sqlite3 libsqlite3-dev
````

## ERRORS AND SOLUTIONS
If you encounter issues with **QtQuick**, run:
```bash
sudo apt install qml-module-qtquick-layouts
```
If you experience issues with **Gazebo**, run:
```bash
source /usr/share/gazebo/setup.sh
```

