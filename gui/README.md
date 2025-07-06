# Graphical User Interface (GUI) Intefaz gráfica de usuario

El directorio `gui` se trata de la interfaz grafica de usuario donde se encuentran los componentes del `front-end` con `qml` y `back-end` con `c++`.

## Estructura del Directorio

La estructura del directorio `gui` es la siguiente:

``` bash
gui/
├── android/            # Carpeta donde se crea el icono de la aplicacion en android
├── images/             # Images e iconos del proyecto
├── include/            # Parámetros de configuración
├── qml/                # Archivos del front-end
├── src/                # Código fuente de la implementación del gestor de nodos
├── test/               # Donde se ejecutan los test del proyecto
└── CMakeLists.txt      # Configuración del sistema de construcción
```

## Uso

1. **Directorio Include**  
   Contiene los archivos `.h` con las funcionalidades principales. Inclúyelos en tu proyecto para acceder a las herramientas necesarias desde el backend.
2. **Directorio QML**  
   Aquí se encuentran los archivos de interfaz de usuario (frontend). Puedes modificar estos archivos para cambiar la apariencia o comportamiento visual de la GUI.
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

+ **RegisterMap.qml RegisterMapForm.ui.qml**: Pagina donde se rellena el formulario del mapa.

+ **CreateMap.qml CreateMapForm.ui.qml**: La pantalla donde se realiza el movimiento del robot y se ve los resultados por pantalla.

+ **main.qml**: Inicia el frontend.


### Extras
+ **Battery.qml BatteryForm.ui.qml**: Batteria de la base del robot.

+ **BoxImages.qml BoxImagesForm.ui.qml**: Las imagenes de las pruebas.

+ **ConfigurationMenu.qml**: Submenu donde apagas el robot o cierras sesión.

+ **CustomBottomBar.qml CustomBottomBarForm.ui.qml**: Barra de abajo.

+ **DescriptionMapForm.qml**: Cuadro a la derecha de cuando selecionas un mapa con toda la información.

+ **DescriptionPatientForm.qml**: Cuadro a la derecha de cuando selecionas un paciente con toda la información.

+ **ErrorRectangle.qml**: Cuadro de error el cual sale cuando hay un error.

+ **InformationRectangle.qml**: Cuadro de información cuando el robot es detectado.

+ **ImageTest.qml**: Imagen y texto debajo.

+ **Joystick.qml JoystickForm.ui.qml**: Joystick.

+ **Map.qml**: Juntar dierentes modulos de cuando haces una prueba.

+ **OrientationCircle.qml OrientationCircleForm.ui.qml**: Ruleta para decir la orientación del robot.

+ **PopUpInfoForm.qml**: JCuadro de información el cual sale cuando pulsas el boton de información.

+ **SavePage.qml SavePageForm.ui.qml**: Cuadro donde hay botones para guardar no guardar y cancelar.

+ **Login.qml LoginForm.ui.qml**: Pantalla de login.

+ **Guest.qml GuestForm.ui.qml**: Pantalla de inicio de sesion como invitado.

+ **SignInForm.qml SignInFormForm.ui.qml**: Pantalla de registrase.

