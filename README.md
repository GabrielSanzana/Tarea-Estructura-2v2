# Tarea-Estructura-2v2
 En la resolución del problema planteado para la tarea 2, se optó por realizar los TDA mapa, lista y pila debido a la efectividad que presentan para las funciones requeridas.

 Para almacenar los jugadores, se utiliza mapa, dado que los nombres de los jugadores representan de forma efectiva la clave en una tupla clave-valor de un mapa; implicando una complejidad temporal eficiente con respecto a las funciones que se puedan realizar; además, se implementa una lista de items por jugador. Para las acciones, se utilza el TDA pila, dado que es eficiente en operaciones en las que se procesa primero el último dato ingresado. Para la función 6, se creó un mapa de items, en la cuál, la clave es el nombre de un item, y el valor es una lista de jugadores que tienen dicho item, esto dado que al utilizar un mapa, el acceso al item que nos interesa es eficiente, y el mostrar jugadores es un recorrido lineal por una lista. 


(1)Como compilar y ejecutar el codigo:

 Para que el código funcione, se debe tener un compilador de C, además, se deben tener en la misma carpeta de directorio los siguientes archivos:
-main.c, es el código ejecutable.
-hashmap.c y hashmap.h, son la implementación del TDA mapa y son la base para la construcción de este código.
-list.c y list.h
-stack.h
-El archivo players1000.cvs , dado que es el archivo a analizar principalmente, por lo que si no está incluido en el directorio, el código tiene error de segmentación y falla.()

(2) Las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas;

Todas las funciones presentan un aparente buen funcionamiento 

-Registrar jugador: Se crea la función registrar_Jugador, almacenando los datos del jugador ingresado en el mapa de jugadores, como el jugador al ser registrado no tiene items no es nesesacio usar el mapa de items.
-Mostrar Jugador: Esta función muestra los datos del jugador, recibiendo de argumento el mapa de jugadores y el nombre del jugador a buscar.
-Agregar item: Esta funcion recibe  de argumento el mapa de jugadores y el mapa de items,  la funcion le pide al usuario el nombre del jugador, para luego agregarle un item dado por el usuario.
Para esta función, no se pueden introducir items repetidos en la lista de items del jugador, dado que consideramos que el tener items repetidos incrementa la complejidad operacional en esta función, además que este apartado pierde sentido cuando se ingresan, por ejemplo, dos cascos para un jugador.
-Eliminar Item: Esta función elimina items a un jugador recibe de argumento el mapa de jugadores y 
el mapa de items; luego lee el nombre del jugador y de un item dado, y si el jugador tiene el item
, se elimina; en caso contrario, no realiza acciones.
-Agregar puntos de habilidad: Esta función tiene de argumento el mapa de jugador, luego
lee el nombre del jugador y se aumentan los puntos ingresados por el usuario.
-Mostrar todos los jugadores con el mismo item: 
-Deshacer la ultima accion: Esta función recibe de argumento los mapa de jugador y de item, luego revisa cual fue la última acción realizada en la pila acciones, junto con los datos posiblemente eliminados, y en base a la acción, realiza la operación inversa a la pila para deshacer el cambio, y finalmente elimina la acción de la pila.
-Exportar datos a archivo de txt: Esta funcion recibe un nombre dado por el usuario para el nuevo archivo txt y tambien el mapa de jugadores. La funcion hace un recorrido del mapa e imprime todos los datos en el nuevo archivo.
-Importar datos a archivo de txt:  Esta funcion recibe un nombre dado por el usuario para el nuevo archivo txt y tambien el mapa de jugadores. La funcion lee un archivo ingresado con formato txt y agrega los datos a los mapa de jugadores y de items.

(3) coevaluación del trabajo en equipo (usando rúbrica).

 Nuestro equipo se destaca por nuestra excelente colaboración a través de la plataforma Repl.it para realizar todas nuestras tareas de manera eficiente. Todos compartimos un objetivo común y trabajamos juntos para alcanzarlo. Nos comunicamos de manera fluida y clara, lo que nos mantiene en sintonía en todo momento. Cada miembro del equipo aporta habilidades y conocimientos únicos que se complementan mutuamente, lo que nos permite abordar cualquier tarea con éxito. La confianza y el respeto son valores fundamentales en nuestro equipo, lo que nos permite trabajar con eficacia y obtener resultados de alta calidad

╔═══════════════╦═══════════════════════════════════╦══════════════════════════╦══════════════╦══════════════════╦═════════════╦═══════════╗
║    Nombre     ║ Participación activa y equitativa ║ Resolución de conflictos ║ Colaboración ║  Responsabilidad ║ Comunicación║ Pje Total ║
╠═══════════════╬═══════════════════════════════════╬══════════════════════════╬══════════════╬══════════════════╬═════════════╩═══════════╝
║   Overfore    ║               20                  ║            20            ║      20      ║        20        ║      20     ║    100    ║
╚═══════════════╩═══════════════════════════════════╩══════════════════════════╩══════════════╩══════════════════╩═════════════╩═══════════╝

(4) coevaluación del aporte individual de cada integrante (usando rúbrica).

╔══════════════════╦═══════════════╦══════════════════╦══════════════╦════════════════════╦═══════════╗
║    Nombre        ║ Participación ║  Responsabilidad ║ Comunicacion ║ Calidad de Trabajo ║ Pje Total ║
╠══════════════════╬═══════════════╬══════════════════╬══════════════╬════════════════════╬═══════════╣
║  Gabriel Cuibin  ║      20       ║        20        ║      20      ║         20         ║    100    ║
╠══════════════════╬═══════════════╬══════════════════╬══════════════╬════════════════════╬═══════════╣
║  Lucas Zamora    ║      20       ║        20        ║      20      ║         20         ║    100    ║
╠══════════════════╬═══════════════╬══════════════════╬══════════════╬════════════════════╬═══════════╣
║  Marcelo Flores  ║      20       ║        20        ║      20      ║         20         ║    100    ║
╠══════════════════╬═══════════════╬══════════════════╬══════════════╬════════════════════╬═══════════╣
║Patricio Figueroa ║      20       ║        20        ║      20      ║         20         ║    100    ║
╚══════════════════╩═══════════════╩══════════════════╩══════════════╩════════════════════╩═══════════╝

Gabriel Cuibin    : Su contribución que tuvo fue muy buena, ya que ha demostrado habilidad para detectar errores en el código de forma ágil y encontrar soluciones efectivas para los problemas planteados. Además, su capacidad para comprender y ejecutar las ideas propuestas por el grupo es notable.

Lucas Zamora      : Su responsabilidad en el trabajo fue notable, manteniendo una actitud seria y comprometida en todo momento. Desde el comienzo del proyecto, se esforzó por comprender claramente sus responsabilidades y objetivos, trabajando diligentemente para cumplirlos dentro de los plazos establecidos.

Marcelo Flores    : La comunicación dentro del grupo era efectiva, ya que los miembros lograban entender las ideas y se explicaban mutuamente cuando había confusiones. El integrante se destacó en su habilidad para mediar entre los demás miembros cuando surgían desacuerdos. Gracias a esta comunicación fluida, el trabajo en equipo fue más eficiente y se lograron los objetivos de manera efectiva.

Patricio Figueroa : El integrante participó activamente y de forma muy productiva en el trabajo. En todo momento aportó ideas para solucionar los problemas que surgieron, lo que nos ayudó a encontrar soluciones originales y efectivas. Además, mantuvo una buena comunicación con el equipo y siempre colaboró para lograr los objetivos del proyecto en el tiempo acordado.