# Graphical User Interface (GUI) Intefaz gráfica de usuario

El directorio `gui` se trata de la interfaz grafica de usuario donde se encuentran los componentes del `front-end` con `qml` y `back-end` con `c++`.

## Estructura del Directorio

La estructura del directorio `gui` es la siguiente:

```
gui/
├── android/            # Archivos de encabezado para las funcionalidades principales del gestor de nodos
├── images/        # Images e iconos del proyecto
├── include/              # Parámetros de configuración
├── qml/              # Archivos del front-end
├── src/                # Código fuente de la implementación del gestor de nodos
├── test/                # Donde se ejecutan los test del proyecto
├── CMakeLists.txt      # Configuración del sistema de construcción
└── README.md           # Documentación del gestor de nodos
```

## Uso


## Uso

1. **Directorio Include**  
   Contiene los archivos `.h` con las funcionalidades principales. Inclúyelos en tu proyecto para acceder a las herramientas necesarias desde el backend.
2. **Directorio QML**  
   Aquí se encuentran los archivos de interfaz de usuario (front-end). Puedes modificar estos archivos para cambiar la apariencia o comportamiento visual de la GUI.
3. **Directorio Images**  
   Contiene los íconos e imágenes usados en la interfaz gráfica. Puedes añadir o reemplazar imágenes según el diseño de tu aplicación.
4. **Directorio Android**  
   Contiene archivos necesarios para la compatibilidad y compilación en dispositivos Android. Asegúrate de tener configurado el entorno correctamente si deseas compilar para móviles.
5. **Directorio SRC**  
   Contiene el código fuente de la lógica del proyecto. Aquí se implementan las funcionalidades principales de la aplicación GUI.
6. **Directorio TEST**  
   Contiene los scripts de prueba para verificar el correcto funcionamiento del proyecto. Úsalo para hacer pruebas automáticas o manuales.
7. **Sistema de Construcción (CMakeLists.txt)**  
   Archivo que gestiona la compilación del proyecto. Úsalo con `cmake` para generar los binarios correctamente.

## Include y Src

+ **utils.h utils.cpp**: Archivos donde se encuentran los `enum` y `struct` del proyecto, además de algunas funciones generales.

+ **cliente.h cliente.cpp**: Se trata de los archivos donde se conecta y comunica con el servidor a través de sockets.

+ **StringHandler.h StringHandler.cpp**: Cuenta con la información general necesaria para el front-end, como el nombre del paciente seleccionado, el mapa, el estado de la batería, etc.

+ **database.h database.cpp**: Toda la información relacionada con la base de datos, como nombre de usuario, rol o información del paciente.

+ **MapInfo.h MapInfo.cpp**: Información relacionada con el mapa, como el tamaño original, el tamaño de la pantalla, el nombre del mapa, etc.

+ **NetworkDDBB.h NetworkDDBB.cpp**: Archivo donde se envían los comandos SQL.

+ **utils_ddbb.h utils_ddbb.cpp**: Funciones usadas para enviarlas a la base de datos.

+ **ToJson.h ToJson.cpp**: Entre el cliente y el servidor se envían los mensajes por JSON, y en este archivo se transforman a JSON los mensajes que se quieran enviar.
## QML
El proyecto está separado en `.qml` y `.ui.qml`, donde el primero contiene toda la lógica, como el click de los botones, por ejemplo. Y el `ui.qml` tiene el diseño de la pantalla, el cual se puede editar con `QtDesignStudio`.

+ **ApplicationFlow.qml ApplicationFlowForm.ui.qml**: Es el corazón de todo el proyecto, donde se gestionan las diferentes pantallas del proyecto.

+ **Home.qml HomeForm.ui.qml**: La primera pantalla, donde se encuentra el botón "START" del proyecto.

+ **RobotConnection.qml RobotConnectionForm.ui.qml**: La segunda pantalla, donde tienes las instrucciones de cómo conectarte al robot.

+ **RegisterPage.qml**: La tercera pantalla, donde inicias sesión, te registras o inicias sesión como invitado.

+ **MainMenu.qml MainMenuForm.ui.qml**: La cuarta pantalla, donde se encuentran el Control Manual, Seleccionar Paciente, Seleccionar Mapa y Comenzar el Test.

+ **ManualControl.qml ManualControlForm.ui.qml**: Joystick donde puedes mover el robot.

+ **MapPage.qml MapPageForm.ui.qml**: Página de la prueba.

+ **SelectMap.qml SelectMapForm.ui.qml**: Donde seleccionas el mapa.

+ **SelectPatient.qml SelectPatientForm.ui.qml**: Donde seleccionas el paciente.

+ **RegisterPatient.qml RegisterPatientForm.ui.qml**: Pagina donde se registra a los pacientes.

+ **main.qml**: Inicia el front-end.


### Extras



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
