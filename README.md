# GUI ROBOGait

Este proyecto esta dividido en dos partes **GUI** que hace referencia al cliente y a la interfaz grafica.
Y el **server** que hace referencia a los diferentes servidores y a los nodos con ros2 y el robot
## GUI
Dentro de este proyecto se incluye todo lo necesarios para compilar en Qt Creator.
### Pasos a seguir para instalar Qt Creator:
 + Te descargas del sitio oficial con la licencia de estudiante y el correo de la UPM [link](https://www.qt.io/qt-educational-license#application)
 + Si quieres usarlo para desarrollar android [pasos](https://doc.qt.io/qt-6/android-getting-started.html)
 + _Nota_: Debes activa la opcion de desarrollador en el móvil/tablet para poder compilar el codigo en tu dispositivo [Video](https://youtu.be/f91wxQdP8Ak?si=0kSbNOwmc2m3rqNe)


## Server
Se trata de la informacion necesaria para hacer de servidor y comunicarte con el cliente (Tablet/móvil) pero se debe complementar si se quiere usar con el codigo de robogait indoor v3 a día de hoy 31/03/2025.
### Pasos para intalar lo necesario
 + Instalar ROS2 Humble [Link](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html)
 + Dependencias:
 ```bash
 sudo apt install build-essential cmake libboost-system-dev libyaml-cpp-dev nlohmann-json3-dev libopencv-dev
 ```



## ERRORES Y SOLUCION
Si te falla en algun momento los qtquick ejecuta esto:
```bash
sudo apt install qml-module-qtquick-layouts
```
en gazebo si te falla ejecuta esto:
```bash
source /usr/share/gazebo/setup.sh
```
