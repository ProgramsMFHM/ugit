# Proyecto UGIT
El presente es un respositorio para almacenar el proyecto ugit, proyecto parcial de la asignatura de Estructuras de Datos de la Universidad de Magallanes.

Proyecto realizado por:
- Alan Nicolás Almonacid
- Milton Fabricio Hernández

## Documentación de comandos de ugit

**Modo de uso:** `./ugit <comando> [<parámetro 1, parámetro 2, …>]`

***ES RECOMENDABLE EJECUTAR ESTE PROGRAMA EN UN DIRECTORIO DEDICADO PARA EL MISMO (PUEDEN BORRARSE ARCHIVOS NO RASTREADOS POR UGIT)***

### Comandos disponibles:

- **add <archivo1> <archivo2>...**
  Agrega los archivos deseados al Staging Area. Puede recibir como parámetros nombres de varios archivos (separados por espacios) agregando varios al mismo tiempo al Staging Area.
  Adicionalmente, es posible usar el carácter `*` de la misma manera que se usaría en la terminal para representar una cantidad indefinida de caracteres en una posición de una cadena.
  Por ejemplo, `"add *.c"` agrega todos los archivos que terminen en `.c` al Staging Area.

- **checkout <commit_ID>**
  Lleva el directorio actual a su estado al momento de hacer el commit con el id: `commit_ID`.
  Si no conoce el ID de un commit, basta con ejecutar el comando `log` para conocer el ID de cada uno de ellos.

- **commit <"mensaje">**
  Genera un commit con los datos del Staging Area.
  El mensaje del commit tiene una longitud máxima de 256 caracteres.
  No se puede ejecutar `commit` si el Staging Area está vacío.

- **config**
  Inicializa una configuración para un usuario.
  Se pedirá un nombre de usuario (de máximo 40 caracteres) así como un correo electrónico (de máximo 35 caracteres).

- **log**
  Genera una lista de los commits realizados hasta el momento.
  Podrás ver un indicador `(main)` que representa el último commit que se ha realizado, así como un indicador `(HEAD)` que representa el commit donde se encuentra la visualización actual del directorio.

- **help [comando]**
  Imprime información sobre el funcionamiento de los comandos en uGit.
  Puedes indicar el nombre de un comando específico para conocer una descripción más completa de su funcionamiento.

- **init**
  Inicia un repositorio vacío en el directorio actual.
  Si el repositorio existe, no podrá inicializarse de nuevo.
  Se crean algunas carpetas y archivos que serán usados por el programa para su correcto funcionamiento; la eliminación de estos archivos podría corromper el funcionamiento de uGit.

- **status**
  Indica los archivos presentes en el Staging Area.
  Los archivos que se encuentran en el Staging Area están en la versión en que se encontraban al momento de usar el comando `add`. Nuevas modificaciones deberán incluirse en el Staging Area antes de hacer `commit` si deseas que sean guardadas.

## Documentación de errores
Se tiene la función `printError(int num, char* aux, char* obs)` que dependiendo del código pasado en num enviará uno u otro error. A continuación se describen todos los errores:

| Código | Mensaje de error                                                           |
| ------ | -------------------------------------------------------------------------- |
| 100    | Archivo <aux> no encontrado                                                |
| 101    | Directorio <aux> no encontrado                                             |
| 103    | Ugit inicializado en este directorio                                       |
| 104    | Comando <aux> no existe                                                    |
| 105    | Mensaje no ingresado                                                       |
| 106    | Mensaje demasiado largo                                                    |
| 107    | No se logró asignar un ID al commit                                        |
| 108    | StagingArea vacío                                                          |
| 109    | No se logró leer el archivo <aux>                                          |
| 110    | No se logró crear el archivo <aux>                                         |
| 111    | No se logró guardar el archivo <aux>                                       |
| 112    | No se logró abrir el archivo <aux>                                         |
| 113    | No se logró crear el directorio <aux>                                      |
| 114    | No se logró guardar el usuario                                             |
| 115    | No se encontró la información de la posición del HEAD en el log            |
| 116    | El commit <aux> no existe                                                  |
| 117    | No se logró formatear la fecha                                             |
| 118    | El archivo <aux> no recibió ningún cambio                                  |
| 119    | Entrada demasiado larga                                                    |
| 120    | Error en la entrada                                                        |
| 200    | No se logró almacenar <aux> bytes en memoria                               |
| 201    | No se logró cambiar de versión                                             |
| 202    | No se ingresó un comando                                                   |
| 300    | No se guardó ningún archivo en el StagingArea                              |
| 301    | El <aux> fue truncado por ser demasiado largo                              |
| 302    | ID leído en el archivo de configuración no coincide con el tamaño esperado |
| 303    | No se logró guardar archivos antiguos                                      |
| 304    | No se logró eliminar el directorio <aux>                                   |

## Compilación del programa
Para compilar el programa Ugit se recomienda ejecutar los siguientes comandos en la terminal:
- `make folders` generará las carpetas necesarias para el correcto funcionamiento de la compilación del programa.
- `make` Compilará el programa y dejará el ejecutable en la carpeta `build/` **Se recomienda entrar a esta carpeta cuando se deseen ejecutar comandos de Ugit**
- `make run` Mostrará la documentación interna ugit, sin embargo, insistimos en la recomendación de entrar a la carpeta `build` y ejecutar en ella las llamadas al binario `ugit`
- `make doc` Generará una documentación con [Doxygen](https://www.doxygen.nl/), que se presentará en la carpeta `docs/doxygen`, se recomienda abrir el archivo `docs/doxygen/html/index.html` para visualizar la documentación completa del programa.
  - Alternativamente puede ejecutar `make` dentro de `docs/doxygen/latex/` para obtener un `refman.pdf` correspondiente a la documentación del proyecto en formato PDF.