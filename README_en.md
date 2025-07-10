
# ROBOGait Project – Client (GUI) and ROS2 Server

This project includes:

- A **Graphical User Interface (GUI)** developed with Qt for Android and desktop.
- A **ROS 2 + Flask server** that manages logic and communication with the ROBOGait robot.

---

## Prerequisites

- Ubuntu 22.04
- Internet connection
- UPM student account for Qt educational license
- Computer capable of running Android Studio
- Tablet with Android operating system

---

## Graphical Interface (GUI)

The `gui/` directory contains everything needed to build the project in Qt Creator.

### Steps to install Qt Creator

1. Download Qt Creator with an educational license from:  
   👉 [Apply for Qt educational license](https://www.qt.io/qt-educational-license#application)

2. If you want to build for Android, follow the official guide:  
   👉 [Official guide: Android with Qt](https://doc.qt.io/qt-6/android-getting-started.html)

   You can also follow this video tutorial to set up **NDK**, **SDK**, and **JDK**:  
   🎥 [Android setup video](https://www.youtube.com/watch?v=7U6Q7xG8N70)

3. **Important:** Enable developer mode on your Android tablet/phone.  
   🎥 [How to enable developer mode](https://youtu.be/f91wxQdP8Ak?si=0kSbNOwmc2m3rqNe)

---

## ROS2 + Flask Server

The `server/` directory contains the backend server that communicates with the client and controls the robot. This project complements **ROBOGait Indoor v3** (as of 06/07/2025).

### Installing dependencies

1. **Install ROS 2 Humble**  
   👉 [Official guide](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html)

2. **Install system dependencies:**

   ```bash
   sudo apt update
   sudo apt install build-essential cmake libboost-system-dev libyaml-cpp-dev \
       nlohmann-json3-dev libopencv-dev
   ```

3. **Install Python dependencies:**

   ```bash
   sudo apt install python3 python3-pip
   pip install Flask
   ```

4. **Install SQLite tools:**

   ```bash
   sudo apt install sqlite3 sqlitebrowser
   ```

---

## Port Configuration

This project uses a single communication port:

```bash
sudo ufw enable
sudo ufw allow 45454
```

| Port  | Protocol | Usage                               |
|-------|----------|--------------------------------------|
| 45454 | UDP      | Discovery and heartbeats (ACKs)      |
| 45454 | TCP      | Client-server data communication     |

---

## Getting Started

### Client (GUI)

1. **Clone the repository:**

   ```bash
   git clone <REPOSITORY_URL>
   cd GUI_ROBOGAIT/gui
   ```

2. **Open the project in Qt Creator:**

   - Select `Open Project`
   - Choose the `CMakeLists.txt` file

3. **Configure Kit:**

   - In the `Kit Selection` screen, select both `Desktop` and `Android`
   - For Android, use `Clang armeabi-v7a` (or a compatible option)

4. **Build and run:**

   - Select the build/run target in the bottom left (Desktop or Android)
   - Click **Play**

---

### Server

1. **Clone the repository:**

   ```bash
   git clone <REPOSITORY_URL>
   cd GUI_ROBOGAIT/server
   ```

2. **Set the project path:**

   Edit `node_manager/include/header.h` and update the following line with your actual path:

   ```cpp
   #define PATH "/home/your_user/GUI_ROBOGait/"
   ```

3. **Build the project using colcon:**

   ```bash
   colcon build
   source install/setup.bash
   ```

4. **Run the main node:**

   ```bash
   ros2 run node_manager node_manager
   ```

---

## Common Issues and Solutions

- **QtQuick module not found:**

   ```bash
   sudo apt install qml-module-qtquick-layouts
   ```

- **Gazebo launch fails:**

   ```bash
   source /usr/share/gazebo/setup.sh
   ```

- **Run Rviz2 with Turtlebot3 navigation:**

   ```bash
   ros2 run rviz2 rviz2 -d $(ros2 pkg prefix nav2_bringup)/share/nav2_bringup/rviz/nav2_default_view.rviz
   ```
