# Control de temperatura de un mini-biorreactor mediante un sensor de infrarrojos

Este repositorio recopila el código generado por Roberto Mateu en el desarrollo de su TFG.

## Matlab

La carpeta "1_IdentificacionModelo" contiene el código necesario para obtener modelos a partir de los datos experimentales de un bucle abierto mediante la herramienta SystemIdent. Además se incluye un ejemplo: datos reales e imágenes del modelo obtenido.

La carpeta "2_ValidacionModelo" contiene el código necesario para implementar el modelo obtenido en un simulador y comprobar si coincide con los datos experimentales.

Por último, la carpeta "3_SimuladorSimulink", contiene un simulador de un bucle de control en lazo cerrado con control de referencia.

## PCB

En la carpeta "pcb" se incluyen todos los archivos de Eagle usados para desarrollar/implementar la pcb del calentador basado en resistencias planas. También se incluyen imágenes con los resultados.
