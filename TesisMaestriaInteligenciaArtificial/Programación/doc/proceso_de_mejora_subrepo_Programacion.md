# Proceso de mejora de sub-repositorio Programacion

En este documento se describe el proceso para reestructurar, refactorizar y limpiar todo el código y archivos de la carpeta Programación, generada como sub-repositorio del repositorio TesisMaestria, como ejercicio de diferenciación del nivel de programación y buenas prácticas que se tenía en 2020 y el de la actualidad.

La información del espacio utilizado por el repositorio local completo en su primera versión, así como de sus sub-directorios de mayor tamaño, se lista a continuación:

- La carpeta completa del repositorio tiene un tamaño de 6.8 GB (7.2 GB en otras interfaces).
- Los PDF de la carpeta `Mallas PDF/` ocupan 28 MB.
- La carpeta `Matrices evaluadas/` contiene un archivo CSV de 941 MB.
- Los archivos en la carpeta `Archivos casos/` tienen un tamaño en total de 231 MB.
- El contenido solo en el primer nivel de la carpeta `Bases de conocimiento/4x4/` es de 2.8 GB.
- El contenido de la carpeta `Bases de conocimiento/5x5/` es de 125 MB.
- La carpeta `Bases de conocimiento/4x4/Latex (mallas 10x10 pdfs)/` tiene un tamaño de 480 MB.
- La carpeta LaTeXGnuplot tiene un tamaño de 1.7 GB.

Todas las modificaciones que se hagan al repositorio local original en y a partir de su commit de creación se documentarán en este y otros archivos de documentación, que serán agregados al repositorio después de dicho commit y se mantendrán hasta que no sean relevantes para el último estado del repositorio.

## Archivos ignorados

Todos los archivos generados de extensión `.aux`, `.log`, `.out`, `.div` y `.gz` serán ignorados.

Los archivos generados, de extensiones `.pl`, `.txt`, `.tex`, `.gpl`, `.csv`, y de tamaño menor a 100KB serán agregados, y los mayores o iguales a 100KB se les tomará una muestra.
Algunos archivos generados completos de extensión `.eps` y `.pdf` también serán mantenidos como muestra.

Después del commit de creación también se agregará un archivo `README.md` y otros archivos de documentación, que contendrán una descripción y resumen del estado original de estos archivos en el directorio de trabajo, antes de tomar las muestras.
Con esto se pretende tener un panorama lo más cercano posible del estado del directorio de trabajo anterior al commit de creación del repositorio, sin que el tamaño del repositorio sea demasiado grande.

Después del commit de creación, estos archivos generados muestreados se restaurarán a su versión original y se ignorarán.
También se ignorará la mayoría del resto de archivos generados.
Esto debido a que, además del gran tamaño de algunos, la gran mayoría de estos archivos generados ya no son útiles, por lo que serán eliminados definitivamente del repositorio local en commits posteriores a la creación del repositorio, como parte del proceso de mejora.
Por lo cual no tiene caso arrastrar el tamaño original de estos solo en los primeros commits.

En el archivo `informacion_archivos_repositorio.csv`, añadido después del commit de creación, se encuentra la información de todos los nombres de los archivos del directorio de trabajo antes de la creación del repositorio, junto con sus rutas, tamaños originales, entre otros datos.
Esto como parte de la documentación del estado del repositorio local antes de su commit de creación y de la toma de muestras.

A continuación se presenta una síntesis de cuáles archivos (excepto los de las extensiones ignoradas mencionadas) fueron agregados, ignorados o se les tomó una muestra en el commit de creación:

- [X] `Word's/`: se incluirán como documentación.

- [X] `Mallas PDF/`: aunque se trata de archivos generados, se mantendrán todos como un tipo alternativo de documentación o visualización de algunos resultados, excepto `4x4 Cubos 5, Prismas 6.pdf` por su tamaño.

- [X] `Matrices evaluadas/`: se tomó una muestra del archivo `matrices_evaluadas_ordenadas.csv`.

- [X] `Archivos casos/`: se tomaron muestras de los archivos de tamaño mayor a 100KB.

- [X] `Gnuplot/`: no se ignoró ningún archivo, ya que son necesarios para la generación de gráficas.

- [X] `Bases de conocimiento/`: se tomó una muestra del archivo `baseConocimientoMallasFiltradas.pl`.

  - [X] `Muestras 5x5/`: se tomaron muestras de todos los archivos.
  El archivo `Seguimiento.txt` se dejó completo.

  - [X] `4x4/`:
    - Se agregaron completos los archivos con nomenclatura $n$`,`$m$`.txt` en su nombre, menores o iguales a 100KB, de los demás se tomaron muestras.
    - Se tomaron muestras de los archivos `baseConocimientoMallasFiltradas`$n$`.pl` y `baseConocimientoMallasFiltradas.pl`.
    - Se tomaron muestras de los archivos `EvaluacionMallas.txt` y `EvaluacionMallas`$n$`.txt`.
    - Se agregaron completos los archivos `LimitesPasos`$n$`.txt`, así como el archivo `LimitesPasos.txt`.

    - [X] `Latex (mallas 10x10 pdfs)/`:
      - Se tomó una muestra del archivo `01MallasLatex.tex`.
      - Se tomaron como muestra algunos archivos `Mallas`$n$`-eps-converted-to.pdf` completos.

  - [X] `3x3/`: se mantuvieron completos los dos archivos.

- [X] `Versiones anteriores/`: se incluyeron todos los archivos para tener registro de las versiones anteriores en los commits iniciales.

- [X] `Pseudocódigos/`: se incluyeron todos los archivos monitoreables.

- [X] `LatexGnuplot/`:
  se tomaron muestras de todos los archivos `GraficadorMatricesGnuplot.gpl`.
  Solamente, se ignoraron archivos `.eps` y `.pdf` grandes, tomando algunos archivos completos de menor tamaño como muestras.

- [X] `Algoritmo de renderizado/`: se agregaron los tres scripts.

- [X] `Imágenes Word/`: se agregaron todas las imágenes.

- [X] `Puntajes/`: se agregaron los dos archivos.

## Archivos generados

En esta sección se describe cómo volver a crear los archivos generados que fueron ignorados o eliminados después del commit de creación.
Esto en el contexto del directorio de trabajo antes de la creación del repositorio, es decir, antes de tomar las muestras de los archivos generados (aunque debido a que en los primeros commits del repositorio muchos de los archivos y documentos no son útiles, serán pocos los casos en que se requiera volver a generarlos).

Las muestras de los archivos generados que se incluyeron en el commit de creación se ignoraron o eliminaron en commits posteriores, así como la gran mayoría de archivos que pudieran generarse con los scripts del repositorio, tanto archivos de gran tamaño como pequeños.

La siguiente es una lista de los archivos generados más importantes, junto con los scripts que pueden volver a generarlos a su tamaño original (no al de las muestras).
Para más información sobre estos archivos generados, consultar la documentación del archivo `proceso_para_generar_archivos_de_entrada_y_salida.md`.

- `Mallas PDF/*.pdf`: cada uno de los archivos PDF es generado al compilar el archivo `GraficadorMatricesGnuplot.gpl` correspondiente, que generará el archivo `.eps`, y posteriormente al ejecutar el archivo `MallasLatex.tex`, se generará el `.pdf`.
Los archivos `GraficadorMatricesGnuplot.gpl` y `MallasLatex.tex` se generan mediante el script `MatricesGnuplot2.cpp`.

- `Matrices evaluadas/matrices_evaluadas_ordenadas.csv`: en el archivo `Información importante.txt` (misma ruta) se encuentra la información de cómo se generaban los archivos `MatricesEvaluadasGnuplot`$n$`.txt`, mediante el script `MatricesGnuplot.cpp` ó `MatricesGnuplot2.cpp`.
Estos archivos `.txt` se convirtieron en el archivo `matrices_evaluadas_ordenadas.csv`, que en cada línea contiene la información de un archivo `.txt`.

- `Archivos casos/*.pl`: la generación de estos archivos es mediante alguno de los scripts (preferentemente las versiones más recientes):
  
  - `permutaciones2.cpp`
  - `permutaciones3.cpp`
  - `permutaciones4.cpp`
  - `permutaciones5.cpp`
  - `permutacionesMuestreo.cpp`
  - `permutacionesMuestreo2.cpp`
  - `permutacionesMuestreoCasosEspeciales.cpp`

- `baseConocimientoMallasFiltradas.pl`: la generación de este archivo es mediante alguno de los scripts (preferentemente las versiones más recientes):

  - `permutaciones5.cpp`
  - `permutaciones4.cpp`
  - `permutaciones3.cpp`
  - `permutaciones2.cpp`
  - `permutacionesMuestreo2.cpp`
  - `permutacionesMuestreo.cpp`
  - `permutacionesMuestreoCasosEspeciales.cpp`
  - `funcionDeEvaluacion4.pl`
  - `funcionDeEvaluacion3.pl`
  - `funcionDeEvaluacion2.pl`
  - `funcionDeEvaluacion.pl`

- `Bases de conocimiento/baseConocimientoMallasFiltradas.pl`: este archivo puede ser una modificación del archivo con el mismo nombre que se encuentra un nivel arriba o bien se generó mediante alguno de los mismos scripts que lo generan.

- `Bases de conocimiento/Muestras 5x5/Seguimiento.txt`: se puede obtener de las impresiones en terminal que hacen los scripts `permutaciones*.cpp`.

- `Bases de conocimiento/4x4/baseConocimientoMallasFiltradas`$n$`.pl`: pueden ser generados por el script `funcionDeEvaluacion4.pl` ó `permutaciones5.cpp`.

- `Bases de conocimiento/4x4/baseConocimientoMallasFiltradas.pl`: es la unión de los archivos `baseConocimientoMallasFiltradas`$n$`.pl` que se encuentran en la misma carpeta.

- `Bases de conocimiento/4x4/EvaluacionMallas`$n$`.txt`: son generados mediante los scripts `funcionDeEvaluacion*.pl`.
  El archivo `EvaluacionMallas.txt` en la misma ruta es simplemente la unión de estos.

- `Bases de conocimiento/4x4/LimitesPasos`$n$`.txt`: son generados mediante los scripts `funcionDeEvaluacion*.pl`.
  El archivo `LimitesPasos.txt` en la misma ruta es simplemente la unión de estos.

- `Bases de conocimiento/4x4/`$n$`,`$m$`.txt`: pueden ser generados de la misma forma que los archivos de la carpeta `Archivos casos/`.
  Posiblemente son generados con una versión anterior del script `permutaciones5.cpp`.

- `Bases de conocimiento/4x4/Latex (mallas 10x10 pdfs)/01MallasLatex.tex`: puede ser generado mediante el script `MatricesGnuplot2.cpp`.

- `Bases de conocimiento/4x4/Latex (mallas 10x10 pdfs)/Mallas`$n$`-eps-converted-to.pdf`: estos archivos son generados al compilar el archivo `GraficadorMatricesGnuplot.gpl` correspondiente, que generará los archivos `.eps`, y posteriormente, al ejecutar el archivo `01MallasLatex.tex`, ubicado en la misma carpeta, se generarán los archivos `.pdf`.
El `10x10` en el nombre de la carpeta que los contiene se refiere a que los archivos tienen 10 $\times$ 10 gráficas por hoja, es decir 100 gráficas (no confundir con que su contenido son gráficas de mallas de 10 $\times$ 10).

- `Bases de conocimiento/3x3/*.pl`: es probable que estos archivos sean generados de la misma forma que el archivo `baseConocimientoMallasFiltradas.pl` en la raíz del repositorio.
No se encuentra un script que genere un archivo con el nombre `baseConocimientoMallas.pl` como tal, por lo que es posible que sea resultado de un nombrado anterior del archivo de salida en el script.

- `LatexGnuplot/**/GraficadorMatricesGnuplot.gpl`: estos archivos, y el ubicado en la raíz del repositorio, se pueden generar mediante el script `MatricesGnuplot2.cpp`.

- `LatexGnuplot/**/MallasLatex.tex`: estos archivos se pueden generar mediante el script `MatricesGnuplot2.cpp`.
  
- `LatexGnuplot/**/Mallas`$n$`.eps`: se generan mediante el archivo `GraficadorMatricesGnuplot.gpl` que se encuentra al mismo nivel.

- `LatexGnuplot/**/MallasLatex.pdf`: se genera mediante el archivo `MallasLatex.tex` que se encuentra al mismo nivel, el cual solo toma la o las imágenes `.eps` generadas por `GraficadorMatricesGnuplot.gpl` y las une en un `.pdf`.

Para verificar la generación correcta de los archivos, se puede consultar el archivo `informacion_archivos_repositorio.csv`, agregado después del commit de creación del repositorio, donde se indica el nombre y tamaño de todos los archivos del directorio de trabajo antes de la creación del repositorio.

## Proceso de creación y mejora del repositorio

Primero crear una copia de la carpeta del repositorio por si algo sale mal.

### Creación y carga de repositorio (commit 0)

Respecto a los archivos generados, se tomaron muestras de los archivos y documentos que, individualmente o en conjunto, requerían mucho espacio de almacenamiento, esto es, recortar el contenido de cada archivo hasta una cantidad mínima, o en el caso de documentos PDF y EPS, tomar una pequeña cantidad de documentos como muestra.
En ambos casos se dejaron los nombres originales de archivos y documentos.

En el siguiente commit se sustituirán las muestras por los archivos originales, pero estos se ignorarán o eliminarán, ya sea por que son archivos generados y/o por que ya no se requieran.

- [X] Crear `.gitignore` e ignorar archivos y elementos compilados que no son de interés.

- [X] Identificar archivos que requieran mucho espacio de almacenamiento, ya sea individualmente o en conjunto.
  También verificar cuáles de estos archivos son generados por scripts.
  Tomar una muestra de estos archivos según las reglas mencionadas.

- [X] Registrar todo como está para el commit 0, solo eliminar lo realmente necesario.
  De manera que, mediante las muestras tomadas, el repositorio tenga un tamaño manejable, a la vez que su estado en este commit sea lo más fiel posible al estado del repositorio local con los archivos originales, manteniendo los errores y malas prácticas.

### Primera ronda de commits: limpieza, reestructuración y renombrado de directorios y archivos

Debido a que en este proceso se modificarán rutas y nombres de archivos, y a que la modificación de código está reservada para la segunda ronda de commits, se deberá agregar un aviso en cada commit de esta ronda, así como en el archivo `README.md` (una vez que se agregue), en el que se mencione que en el estado actual del repositorio algunos scripts pueden no ejecutarse correctamente, debido al proceso de reestructuración que está en curso.

- [X] Se debe hacer un mapeo general de archivos de entrada y salida de los scripts, en el cual se incluyan todos los archivos generados (monitoreados e ignorados), con esto se podrá identificar cuáles scripts utilizan los archivos generados que serán ignorados.
  Generar un archivo `.md` en la carpeta `doc/`, donde se describa el orden y dependencias de ejecución de los scripts para que puedan ser generados sin mayores problemas.
  Este archivo solo permanecerá en el índice hasta el siguiente commit, o bien, hasta el inicio de la segunda ronda de commits.
  
- [X] Crear carpeta `doc/` y archivo `.csv` en esta, con la información de todos los archivos originales del directorio de trabajo antes del commit de creación.
  Los campos que deberá tener este archivo son:

  - `nombre_archivo`
  - `tamaño_original`
  - `estatus_commit_0`: `monitoreado`, `ignorado`, `monitoreado_muestreado`
  - `es_generado`
  - `ruta`

  Este archivo solo permanecerá en el índice hasta el siguiente commit, o bien, hasta el inicio de la segunda ronda de commits.

- [X] Añadir también este archivo como documentación.
  Este archivo solo permanecerá en el índice hasta el siguiente commit, o bien, hasta el inicio de la segunda ronda de commits.

- [X] Restaurar archivos a los que se les tomó una muestra e ignorarlos.
  También deberían ser eliminados como parte de la limpieza, solo que esto no será tomado en cuenta por el repositorio, por lo que puede hacerse en cualquier momento.

- [X] Ignorar la mayoría de los archivos generados (salvo las excepciones mencionadas).
  Archivos generados que no hayan faltado por ser ignorados en este paso pueden ignorarse más adelante.
  También deberían ser eliminados como parte de la limpieza, solo que esto no será tomado en cuenta por el repositorio, por lo que puede hacerse en cualquier momento.

- [X] Modificar documentación para que concuerde con eliminación de archivos y directorios generados.

- [ ] Agregar archivo `README.md` con descripción sencilla en la raíz del repositorio.
  Mencionar la información documentada en los archivos agregados en `doc/` y eliminar esta referencia cuando estos se eliminen.

- [ ] Agregar archivo de comandos Git y mensajes de commits que están en el borrador e ignorarlo para tenerlo como registro local de las acciones realizadas.

- [ ] Añadir el `.sh` que se usó para tomar las muestras de archivos en masa y `.py` que se usó para generar el `.csv` con el estatus de todos los archivos del proyecto.
  Estos archivos solo permanecerán en el índice hasta el siguiente commit, o bien, hasta el inicio de la segunda ronda de commits.

- [ ] Crear una carpeta para versiones anteriores de códigos y moverlos todos ahí, para tenerlos como documentación.
  Esta carpeta y su contenido solo permanecerá en el índice hasta el siguiente commit, o bien, hasta el inicio de la segunda ronda de commits.

- [ ] Mover los scripts `algoritmoVentana_*.cpp` y `algoritmoVentana_*.h` a la carpeta `Algoritmo de renderizado/`, o bien eliminarlos directamente.
  Estos corresponden a una metodología descartada.
  Estos archivos solo permanecerán en el índice hasta el siguiente commit, o bien, hasta el inicio de la segunda ronda de commits.

- [ ] El archivo `mallaVentana.pl` ubicado en la raíz del repositorio, es un archivo generado pequeño con información específica de un caso de un número específico de objetos en una malla.
  Es el único con ese patrón de nombre, su información ya no es útil, por lo que se puede ignorar o eliminar.
  
- [ ] El archivo `mallaRefuerzo.pl` ubicado en la raíz es un archivo generado con información específica de un tamaño de malla y el único con ese patrón de nombre, su información ya no es útil, por lo que se puede ignorar o eliminar.
  
- [ ] Verificar en qué difieren las versiones anteriores de `aprendizajePorRefuerzo_3_masivo.cpp` y `aprendizajePorRefuerzo_3.cpp` y si no es en algo significativo, eliminar esas versiones.
  
- [ ] Remover las versiones anteriores de `MatricesGnuplot2.cpp`.

- [ ] Los archivos `EvaluacionMallas.txt`, `LimitesPasos.txt` y `comparacionAlgoritmos.txt` de la raíz contienen información especifica de la ejecución de los scripts que los generan, por lo que pueden ser eliminados o ignorados.

- [ ] El archivo `GraficadorMatricesGnuplot.gpl` de la raíz contienen información especifica de la ejecución del script que lo genera, además de que los archivos que toma como entrada ya no existen, por lo que se puede eliminar o ignorar.

- [ ] El archivo `casos.pl` es un archivo generado, es leído como entrada de `funcionDeEvaluacion4.pl`, verificar si se se puede ignorar o eliminar.

- [ ] Eliminar todas las versiones anteriores de `permutaciones5.cpp` y `permutacionesMuestreo2.cpp`.
  Falta analizar los scripts `permutacionesMuestreo2.cpp` y `permutacionesMuestreoCasosEspeciales.cpp` con más detenimiento para ver si aportan algo distinto.

- [ ] Mover `Genetico.cpp` y `Genetico.h` a una carpeta de versiones anteriores, métodos alternativos, etc., o eliminarlos.

- [ ] Eliminar el archivo `funcionDeEvaluacion (borrador).pl`.

- [ ] Eliminar las versiones anteriores de `funcionDeEvaluacion4.pl`.

- [ ] Los archivos `comparacionAlgoritmos*.txt` de cualquier carpeta se pueden ignorar o eliminar, ya que son archivos generados.
  
- [ ] Los archivos en la carpeta `Pseudocódigos/` se pueden mover a directorios de documentación.
  Eliminar los que ya no se necesiten.

- [ ] Los archivos en la carpeta `Gnuplot/` se pueden mover a un directorio de resultados.
  Eliminar los que ya no se necesiten.
  
- [ ] Es poco probable que se vuelva a utilizar el archivo `files_to_rows_in_csv.cpp`, ya que su propósito está cumplido.
  Se puede incluir en una carpeta `misc/`, `tools/` o de un nombre por el estilo.
  
- [ ] La documentación del archivo `Información importante.txt` en `Matrices evaluadas/` se puede mover a una carpeta `doc/` o incluirla en el mismo archivo `files_to_rows_in_csv.cpp`.

- [ ] Mover las carpetas `Puntajes/`, `Imágenes Word/` y `Word's/` dentro de la carpeta `Algoritmo de renderizado/`.
  Opcionalmente pasar los documentos Word a LaTeX.
  La carpeta `Algoritmo de renderizado/` y su contenido debe sobrevivir a lo más hasta la segunda ronda de commits.

- [ ] Monitorear los `.pdf` de `Mallas PDF/` excepto el de mayor tamaño, que se ignorará o eliminará.
  Posteriormente decidir si unirlos, ignorarlos o eliminarlos.
  Si se van a conservar, se deben mover a una carpeta de documentación o resultados.

- [ ] Mover el notebook de Mathematica a una carpeta `other/`, `misc/`, etc., o si es adecuado, a la carpeta `doc/`.

- [ ] Unir los PDF de la carpeta `Bases de conocimiento/4x4/Latex (mallas 10x10 pdfs)/` en uno solo para conservarlos localmente o eliminarlos si ya no se utilizarán.
  
- [ ] Los 4 archivos `baseConocimientoMallasFiltradas`$n$`.pl` en la carpeta `Bases de conocimiento/4x4/` pueden ser eliminados ya que el archivo `baseConocimientoMallasFiltradas.pl` es su unión, verificar esto mediante los números de líneas, y si es así, eliminarlos y decidir si se conservará localmente el archivo unido.

- [ ] Analizar el archivo con el mapeo de archivos de entrada y salida de los scripts e identificar el resto de archivos que queden en el índice que ya no se utilizan o que ya no son importantes, ignorarlos o eliminarlos.

- [ ] Eliminar gráficas y sus archivos fuente que ya no se necesiten.
  
- [ ] Renombrar carpetas (revisar cuáles deberán ser eliminadas antes de este renombramiento para no hacerlo en vano).
  
En este punto solo deben quedar en el índice los elementos esenciales del proyecto, ya que la segunda ronda de commits solo estará enfocada en la corrección y mejora del contenido de los scripts y archivos.
El último commit de la segunda ronda será el que contenga el proyecto totalmente corregido y actualizado.

### Segunda ronda de commits: limpieza, corrección, refactorización y optimización de código

- [ ] Modificar rutas en scripts de acuerdo a nueva estructura de carpetas para que tomen sus entradas y generen sus salidas en las rutas correctas.
  
- [ ] Verificar que los scripts se ejecuten correctamente y retirar comentario en `README.md` sobre repositorio inestable.

- [ ] Refactorizar, limpiar y corregir todos los códigos.

- [ ] Agregar descripción en `README.md` de lo que hace cada script.
