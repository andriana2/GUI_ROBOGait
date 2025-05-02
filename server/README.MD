# SERVIDOR

Este directorio contiene las carpetas y archivos necesarios para el robot. Se trata de carpetas tanto para comunicarse con ROS como para la base de datos.

## MAPS
La carpeta `maps` almacena los mapas utilizados por el programa. Contiene los siguientes tipos de archivos:
- **PGM**: Archivos en blanco y negro que representan la imagen del mapa y sus dimensiones.
- **YAML**: Archivos con información adicional del mapa, como el cost-map o la resolución.

## SRC
La carpeta `src` es el directorio principal del proyecto ROS 2. Aquí se encuentran todos los programas necesarios que se compilan utilizando `colcon build`. Está dividida en tres subcarpetas:

1. **Interface_srv**:  
   Contiene la estructura de los servicios de ROS. Estos servicios definen las interfaces de comunicación utilizadas en el proyecto.

2. **tf_service**:  
   Utiliza la estructura definida en `Interface_srv` para obtener los valores de las transformadas del robot. Esto incluye:
   - La posición del robot relativa al mapa inicial.
   - La transformación del robot hacia el `base_footprint` o `base_link`, que representa la base del robot.  
   
   Esta información es esencial para determinar la orientación y posición relativa del robot, especialmente útil durante la navegación.

3. **Node_manager**:  
   Es la carpeta central del proyecto. Contiene la lógica principal y las funcionalidades necesarias para gestionar las operaciones del robot.

## SERVER_DDBB.py
`server_ddbb.py` es un script en Python que actúa como servidor y se conecta a una base de datos SQLite. Su función es procesar los mensajes entrantes y enviar las respuestas correspondientes. La comunicación se realiza mediante HTTP en el puerto 5000.

## DB_ROBOGAIT.DB
`db_robogait.db` se trata del archivo de `SQLite` donde se almacena toda la información de los usuarios, pacientes y pruebas.
 - Instalar `SQLite`:
    ```bash
    sudo apt update
    sudo apt install sqlite3
    ```

 - Y si quieres un browser te recomiendo este:
    ```bash
    sudo apt update
    sudo apt install sqlitebrowser
    ```
 Para abrirlo `sqlitebrowser`


## Comenzando

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
