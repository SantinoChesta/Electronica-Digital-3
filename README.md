# Electronica-Digital-3

Trabajo integrador para la materia "Electrónica Digital 3" de la Facultad de Ciencias Exactas Físicas y Naturales de la Universidad de Cordoba

## Requisitos minimos

Siguiendo las normativas impuestas en la clase del 21/05:

- Uso de teclado matricial
- Uso de pantalla LCD
- Uso de DMA
- Uso de UART
- Uso de interrupciones en general

## Concepto inicial

### Snake

En el juego de snake original y en el popularizado por estar en los telefonos celulares de la marca Nokia, controlamos una serpiente que se mueve axialmente por una habitacion recogiendo frutas que alargan el tamaño de su cuerpo siempre bajo la presion de que un choque frontal de la cabeza de la serpiente contra las paredes de la habitación o su propio cuerpo lleva a la derrota, por otro lado para ganar en el juego se debe ocupar todo el espacio disponible de la habitacion.

Esta es la idea basica del juego que se ha establecido invariable en nuevas versiones del mismo y que se quiere replicar en este trabajo con las siguientes especificaciones:

- Controles: El moviemiento de la serpiente esta encasquillado a una cuadricula por lo que siempre se utilizo cuatro botones para que el jugador pudiera controlarla, para este trabajo se usara un joystick analogico que provee de dos señales analogicas cada una representado cuanto se mueve en el axial horizontal y el axial vertical, estas señales seran multiplexadas y muestreadas por el modulo ADC del la LPC1769.

- Display: La idea principal para que el jugador pueda observar que esta haciendo en el juego es la de transmitir información a través del modulo UART hacia un ordenador que pueda leer el puerto al que llega información y gracias a esto mostrar en pantalla el juego, el programa para leer y mostrar el juego no esta decidido.

- Logica: Toda la logica sera implementada en el controlador, desde la adaptacion de las señales de moviemento, los fotogramas, las colisiones de la serpiente, la aparicion de las frutas, la capacidad de crecer de la serpiente al colisionar con una fruta y futuras ideas.

Se han propuestos cambios a considerar para aumentar la complejidad y cumplir los requerimientos:

- Sistema de puntos: Se le otorga al jugador una cantidad fija de puntos que decrementan en funcion del tiempo e incrementa al comer una fruta, asi recompensando la velocidad del jugardor, se desea que la forma de mostrar estos puntos sea a través de hardware, más especificamente una pantalla LCD.

- Sistema de accion o cambio de modo: A través de una interrupcion externa o por puerto el jugador es capaz de realizar una accion especifica o cambiar completamente la logica del juego. La idea inicial es utilizar el botón incorporado en el joystick analogico para que el jugador navege por un menú.