# SERVER

Esta carpeta cuenta con dos carpetas y un .py

## MAPS
Se trata de la carpeta donde se guardan los mapas del programa para luego usarse.
 + **PGM**: Se trata de los archivos en blanco y negro donde se encuentra la imagen y el tamaño
 + **YAML**: Se trata de informacion adicional como el cost-map o su resolución

## SRC
Colcon build se compila con un src donde se guardan todos los programas necesarios a compilar con ros2.<br>
Se divide en 3 carpetas:
 + Interface_srv: Donde se almacena la estructura de los servicios de ros.
 + tf_service: Donde uso la estructura de interface_srv y la uso para obtener los valores de las trasformadas del robot. Es decir que conozco la posicion del mapa inicial al robot y del robot al base_footprint o base_link que es basicamente la base del robot y eso me da la orientacion relativa del robot muy util a la hora de conocer el robot cuando navegas.
 + Node_manager: Se trata de la carpeta central del proyecto



## SERVER_DDBB.py
Es el servidor que se conecta a la base de datos sqlite y se encarga de procesar los mensajes y enviar una respuesta. La comunicacion es con http en el puerto 5000

