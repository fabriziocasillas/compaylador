Práctica 1 — Infraestructura básica del analizador léxico
Información general
Campo	Información
Asignatura	Compiladores
Número de práctica	1
Equipo	Equipo XX
Integrantes
Nombre completo	Número de cuenta
Hernandez Hernandez Jimmy	321210010	
Pendiente	Pendiente	Pendiente
Descripción

Esta práctica implementa la infraestructura básica de un analizador léxico para un lenguaje tipo MiniC.

El programa recibe como argumento la ruta de un archivo fuente, lo recorre de izquierda a derecha y genera una secuencia de tokens. Cada token contiene su tipo, lexema y posición dentro del archivo mediante número de línea y columna.

El alcance de esta práctica se limita a números enteros, operadores y símbolos básicos, además del manejo de caracteres no reconocidos mediante el token ERROR y la señalización del final del archivo mediante TOKEN_EOF.

Estructura del proyecto
Practica01_EquipoXX/
├── README.md
├── CHANGELOG.md
├── reporte.pdf
├── Makefile
├── include/
│   └── lexer/
│       ├── lexer.h
│       └── token.h
├── src/
│   ├── main.c
│   └── lexer/
│       ├── lexer.c
│       └── token.c
└── tests/
    ├── README.md
    ├── inputs/
    └── expected/
Módulos implementados
Archivo o módulo	
src/main.c Responsabilidad:	Punto de entrada del programa, validación de argumentos y apertura/cierre del archivo fuente.
src/lexer/lexer.c Responsabilidad: Recorrido del archivo, reconocimiento de tokens, seguimiento de línea y columna, manejo de espacios y errores.
src/lexer/token.c Responsabilidad: Representación, inicialización, impresión y liberación de tokens.
include/lexer/lexer.h Responsabilidad: Interfaz pública del analizador léxico.
include/lexer/token.h Responsabilidad: Definición de TokenType y Token, además de las funciones relacionadas.
Makefile Responsabilidad: Automatización de compilación, limpieza y ejecución de pruebas.
Requisitos
GCC con soporte para C11.
GNU Make.
Dependencias adicionales: ninguna.
Compilación

Desde el directorio raíz de la práctica, ejecutar:

make

La compilación genera el ejecutable:

./minic

Para eliminar los archivos generados durante la compilación:

make clean

Ejecución

El programa recibe exactamente un archivo fuente como argumento:

./minic programa.mc

Por ejemplo:

./minic tests/inputs/p5_integer_expression.mc

La salida se escribe en la salida estándar (stdout) con el siguiente formato:

línea:columna TIPO lexema

Por ejemplo:

1:0 INTEGER 10
1:3 PLUS +
1:5 INTEGER 20

Para el token TOKEN_EOF no se muestra lexema:

1:8 TOKEN_EOF

Los mensajes de error relacionados con la ejecución del programa se envían a la salida de error (stderr).

Funcionalidades implementadas

La implementación actual de la Práctica 1 incluye:

Lectura de un archivo fuente.
Representación de tokens mediante Token y TokenType.
Seguimiento de la posición mediante línea y columna.
Manejo de espacios y tabuladores.
Manejo de saltos de línea LF, CRLF y CR.
Reconocimiento de números enteros mediante [0-9]+.
Reconocimiento de operadores simples:
PLUS (+)
MINUS (-)
STAR (*)
SLASH (/)
ASSIGN (=)
LESS (<)
GREATER (>)
Reconocimiento de delimitadores:
LPAREN (()
RPAREN ())
LBRACE ({)
RBRACE (})
SEMICOLON (;)
Manejo de caracteres no reconocidos mediante el token ERROR.
Generación del token TOKEN_EOF al finalizar el archivo.
Manejo dinámico de lexemas de enteros de longitud arbitraria, dentro de los límites de memoria disponibles.
Tokens reconocidos en esta práctica

Token | Lexema

INTEGER | [0-9]+
PLUS | +
MINUS | -
STAR | *
SLASH | /
ASSIGN | =
LESS | <
GREATER | >
LPAREN | (
RPAREN | )
LBRACE | {
RBRACE | }
SEMICOLON | ;
ERROR | Carácter no reconocido
TOKEN_EOF | Fin del archivo

El enumerado TokenType también contiene tipos correspondientes a identificadores, palabras reservadas y operadores compuestos. Estos se encuentran preparados para futuras extensiones, pero no forman parte del alcance de la Práctica 1.

Pruebas

Las pruebas desarrolladas por el equipo se encuentran en:

tests/inputs/
tests/expected/

Cada archivo .mc de entrada tiene un archivo .out correspondiente que contiene la salida esperada del analizador léxico.

Para ejecutar toda la suite de pruebas:

make test

Actualmente se incluyen 14 casos de prueba que cubren:

archivo vacío;
espacios y tabuladores;
símbolos simples;
números enteros;
expresiones básicas;
múltiples líneas;
seguimiento de línea y columna;
caracteres no reconocidos;
múltiples errores en un mismo archivo;
números negativos como combinación de MINUS e INTEGER;
saltos de línea mediante CR;
espacios al final del archivo;
enteros de longitud considerable.

Las pruebas comparan automáticamente la salida generada por minic con los archivos de salida esperada. La ejecución de la suite debe finalizar con todos los casos reportados como OK.

Problemas conocidos

No se conocen problemas adicionales a las limitaciones propias del alcance de la Práctica 1 (aun creo).

Notas de ejecución

El programa debe ejecutarse desde el directorio raíz de la práctica cuando se utilicen las rutas relativas mostradas en los ejemplos.

La compilación utiliza:

-std=c11 -Wall -Wextra -Wpedantic

y utiliza include/ como directorio de búsqueda para los archivos de encabezado.

No se requieren bibliotecas o dependencias externas adicionales.