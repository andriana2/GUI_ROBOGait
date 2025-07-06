# Proyecto ROBOGait – Cliente (GUI) y Servidor ROS2

Este proyecto contiene la interfaz gráfica desarrollada con Qt y la infraestructura del servidor con ROS2 y Flask para controlar el robot ROBOGait.

---
## Requisitos previos
- Ubuntu 22.04
- Conexión a Internet
- Cuenta de estudiante UPM para licencia Qt
- Odenador con capacidad para instalar Android Studio
- Tablet con un sistema operativo Android
--- 

## Graphical User Interface (GUI)
Dentro de este proyecto se incluye todo lo necesario para compilar en Qt Creator.

### Pasos para instalar Qt Creator:
1. Descarga Qt Creator desde el sitio oficial con la licencia de estudiante y el correo de la UPM: [link](https://www.qt.io/qt-educational-license#application).
2. Si deseas usarlo para desarrollar en Android, sigue estos [pasos](https://doc.qt.io/qt-6/android-getting-started.html). Si se te complica aquí los pasos para el NDK y SDK [ndk y sdk](https://www.youtube.com/watch?v=7U6Q7xG8N70) el jdk es con la linea de código
3. **Nota**: Debes activar la opción de desarrollador en el móvil/tablet para poder compilar el código en tu dispositivo. Aquí tienes un [video](https://youtu.be/f91wxQdP8Ak?si=0kSbNOwmc2m3rqNe) que explica cómo hacerlo.

---

## Server
Incluye la información necesaria para configurar el servidor y comunicarte con el cliente (tablet/móvil). Este servidor debe complementarse con el código de RoboGait Indoor v3 (a fecha de 06/07/2025).

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
4. Instalar dependencias de la base de datos:
    ```bash
    sudo apt update
    sudo apt install sqlite3
    sudo apt install sqlitebrowser
    ```
---

## Puertos
El proyecto utiliza un puerto, por lo que si estás en Linux, no olvides habilitarlos:

```bash
sudo ufw enable
sudo ufw allow 45454
```
| Puerto | Protocolo | Uso                                   |
|--------|-----------|----------------------------------------|
| 45454  | UDP   | Conexión entre cliente y servidor     |
| 45454  | TCP   | Conexión entre cliente y servidor     |

---

## Comenzando
### GUI

1. **Clonar el repositorio**  
   Clona el repositorio en tu máquina local utilizando el siguiente comando:
   ```bash
   git clone <URL_DEL_REPOSITORIO>
   cd GUI_ROBOGAIT/gui
   ```
2. **Abrir con Qt Creator** <br>
    Para abrir el proyecto, seleciona `Open Project`, seleciona el CMakeLists.txt.

3. **Configuración del proyecto**<br>
    Cuando llegas al `Kit Selection` asegurate de guardar elegir tanto el Desktop como Android (en mi caso fue el Clang armeaby-v7a).

4. **Play**<br>
    Seleciona la forma de ejecutar abajo a la izquierda si quieres hacerlo como Desktop o como Android y pulsa Play.

Con estos pasos, tendrás la interfaz configurado y listo para su uso.


### Servidor
Para comenzar a trabajar con este proyecto, sigue los pasos a continuación:

1. **Clonar el repositorio**  
   Clona el repositorio en tu máquina local utilizando el siguiente comando:
   ```bash
   git clone <URL_DEL_REPOSITORIO>
   cd GUI_ROBOGAIT/server
   ```

2. **Cambiar el path a param**
   Dentro del archivo `node_manager/include/header.h` se encuentra un `#define` que se debe cambiar al path en el que se encuentra el proyecto. Estructura:
   ```C 
   #define PATH "/home/robogait/GUI_ROBOGait/"
   ```

3. **Construir el proyecto**  
   Asegúrate de tener instalado ROS 2 y sus dependencias. Luego, ejecuta el siguiente comando para compilar el proyecto asegurate de estar en `GUI_ROBOGAIT/server`:
   ```bash
   colcon build
   source install/setup.bash
   ```

4. **Ejecutar el nodo principal**  
   Una vez completada la compilación, puedes ejecutar el nodo principal del proyecto con el siguiente comando:
   ```bash
   ros2 run node_manager node_manager
   ```

Con estos pasos, tendrás el servidor configurado y listo para su uso.


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