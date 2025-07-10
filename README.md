
# Proyecto ROBOGait – Cliente (GUI) y Servidor ROS2

Este proyecto contiene:

- Una **interfaz gráfica de usuario (GUI)** desarrollada con Qt para Android y escritorio.
- Un **servidor ROS 2 + Flask** que gestiona la lógica y comunicación con el robot ROBOGait.

---

## Requisitos previos

- Ubuntu 22.04
- Conexión a Internet
- Cuenta UPM para licencia educativa de Qt
- Ordenador con capacidad para ejecutar Android Studio
- Tablet con sistema operativo Android

---

## Interfaz gráfica (GUI)

El directorio `gui/` contiene todo lo necesario para compilar el proyecto en Qt Creator.

### Pasos para instalar Qt Creator

1. Descarga Qt Creator con licencia educativa desde este enlace:  
   👉 [Solicitar licencia educativa de Qt](https://www.qt.io/qt-educational-license#application)

2. Si deseas compilar para Android, sigue estos pasos oficiales:  
   👉 [Guía oficial: Android con Qt](https://doc.qt.io/qt-6/android-getting-started.html)

   También puedes apoyarte en este video para configurar correctamente el **NDK**, **SDK** y **JDK**:  
   🎥 [Video de configuración Android](https://www.youtube.com/watch?v=7U6Q7xG8N70)

3. **Importante:** Activa el modo desarrollador en tu tablet/móvil Android.  
   🎥 [Cómo activar el modo desarrollador](https://youtu.be/f91wxQdP8Ak?si=0kSbNOwmc2m3rqNe)

---

## Servidor ROS2 + Flask

El directorio `server/` contiene el servidor encargado de comunicarse con el cliente y controlar el robot. Este proyecto se complementa con **ROBOGait Indoor v3** (versión 06/07/2025).

### Instalación de dependencias

1. **Instalar ROS 2 Humble**  
   👉 [Guía oficial](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html)

2. **Instalar dependencias del sistema:**

   ```bash
   sudo apt update
   sudo apt install build-essential cmake libboost-system-dev libyaml-cpp-dev \
       nlohmann-json3-dev libopencv-dev
   ```

3. **Instalar dependencias de Python:**

   ```bash
   sudo apt install python3 python3-pip
   pip install Flask
   ```

4. **Instalar herramientas para la base de datos SQLite:**

   ```bash
   sudo apt install sqlite3 sqlitebrowser
   ```

---

## Configuración de puertos

Este proyecto utiliza un único puerto para comunicación:

```bash
sudo ufw enable
sudo ufw allow 45454
```

| Puerto | Protocolo | Uso                             |
|--------|-----------|----------------------------------|
| 45454  | UDP       | Descubrimiento y ACKs           |
| 45454  | TCP       | Comunicación de datos cliente-servidor |

---

## Instrucciones de uso

### Cliente (GUI)

1. **Clonar el repositorio:**

   ```bash
   git clone <URL_DEL_REPOSITORIO>
   cd GUI_ROBOGAIT/gui
   ```

2. **Abrir el proyecto con Qt Creator:**

   - Selecciona `Open Project`
   - Elige el archivo `CMakeLists.txt`

3. **Configurar Kit:**

   - En la sección `Kit Selection`, selecciona tanto `Desktop` como `Android`
   - Para Android, puedes usar `Clang armeabi-v7a` (u otro compatible)

4. **Compilar y ejecutar:**

   - Selecciona el modo de ejecución en la esquina inferior izquierda (Desktop o Android)
   - Pulsa el botón **Play**

---

### Servidor

1. **Clonar el repositorio:**

   ```bash
   git clone <URL_DEL_REPOSITORIO>
   cd GUI_ROBOGAIT/server
   ```

2. **Configurar ruta del proyecto:**

   En el archivo `node_manager/include/header.h`, modifica la siguiente línea con el path real del proyecto:

   ```cpp
   #define PATH "/home/tu_usuario/GUI_ROBOGait/"
   ```

3. **Compilar el proyecto con colcon:**

   ```bash
   colcon build
   source install/setup.bash
   ```

4. **Ejecutar el nodo principal:**

   ```bash
   ros2 run node_manager node_manager
   ```

---

## Solución a errores comunes

- **Error con módulos QtQuick:**

   ```bash
   sudo apt install qml-module-qtquick-layouts
   ```

- **Error al iniciar Gazebo:**

   ```bash
   source /usr/share/gazebo/setup.sh
   ```

- **Ejecutar Rviz2 con navegación Turtlebot3:**

   ```bash
   ros2 run rviz2 rviz2 -d $(ros2 pkg prefix nav2_bringup)/share/nav2_bringup/rviz/nav2_default_view.rviz
   ```
