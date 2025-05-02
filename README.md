# 🧠 Proyecto ROBOGait – Cliente (GUI) y Servidor ROS2

Este proyecto contiene la interfaz gráfica desarrollada con Qt y la infraestructura del servidor con ROS2 y Flask para controlar el robot ROBOGait.

---
## Requisitos previos
- Ubuntu 22.04
- Conexión a Internet
- Cuenta de estudiante UPM para licencia Qt

--- 

## Graphical User Interface (GUI)
Dentro de este proyecto se incluye todo lo necesario para compilar en Qt Creator.

### Pasos para instalar Qt Creator:
1. Descarga Qt Creator desde el sitio oficial con la licencia de estudiante y el correo de la UPM: [link](https://www.qt.io/qt-educational-license#application).
2. Si deseas usarlo para desarrollar en Android, sigue estos [pasos](https://doc.qt.io/qt-6/android-getting-started.html).
3. **Nota**: Debes activar la opción de desarrollador en el móvil/tablet para poder compilar el código en tu dispositivo. Aquí tienes un [video](https://youtu.be/f91wxQdP8Ak?si=0kSbNOwmc2m3rqNe) que explica cómo hacerlo.

---

## Server
Incluye la información necesaria para configurar el servidor y comunicarte con el cliente (tablet/móvil). Este servidor debe complementarse con el código de RoboGait Indoor v3 (a fecha de 24/05/2025).

### Pasos para instalar lo necesario:
1. Instalar ROS 2 Humble: [Link](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html).
2. Instalar dependencias:
    ```bash
    sudo apt install build-essential cmake libboost-system-dev libyaml-cpp-dev nlohmann-json3-dev libopencv-dev
    ```
3. Instalar dependencias de Python en Linux:
    ```bash
    sudo apt update
    sudo apt install python3 python3-pip
    pip install Flask
    ```

---

## Puertos
El proyecto utiliza puertos, por lo que si estás en Linux, no olvides habilitarlos:

```bash
sudo ufw enable
sudo ufw allow 5000
sudo ufw allow 45454
```
| Puerto | Protocolo | Uso                                   |
|--------|-----------|----------------------------------------|
| 5000   | TCP       | Comunicación con base de datos SQLite |
| 45454  | TCP/UDP   | Conexión entre cliente y servidor     |

---

## ERRORES Y SOLUCION
Si te falla en algún momento los qtquick, ejecuta esto:
```bash
sudo apt install qml-module-qtquick-layouts
```
En Gazebo, si te falla, ejecuta esto:
```bash
source /usr/share/gazebo/setup.sh
```
Turtlebot3 navegación para ejecutar el rviz2:
```bash
ros2 run rviz2 rviz2 -d $(ros2 pkg prefix nav2_bringup)/share/nav2_bringup/rviz/nav2_default_view.rviz
```