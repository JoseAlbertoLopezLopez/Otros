# Generación de archivos

A continuación se listan los diferentes scripts que leen o escriben uno o más archivos de entrada o salida, respectivamente, junto con la lista de estos archivos de entrada y/o salida.
Esto en el contexto del estado del repositorio antes de su creación o en el estado de su commit de creación.
Si los archivos o directorios de entrada o salida indicados en las descripciones ya no existen, simplemente se pueden cambiar las rutas de entrada o salida en los scripts para que no haya problemas al volver a leerlos o generarlos.

Su orden de aparición corresponde a un orden en el que se pueden ejecutar para que no exista ningún problema de dependencias, como puede ser el no contar con los archivos de entrada necesarios para ejecutar alguno de ellos.
Aunque muchos de estos se pueden ejecutar de forma independiente.

Solo se indicará la versión más reciente de estos scripts.
En la mayoría de casos, sus versiones anteriores también toman las mismas entradas y generan las mismas salidas.

- **RS_masivo.cpp** ó **RS.cpp**
  
  Al no tener ningún archivo de entrada, estos scripts se pueden ejecutar de forma independiente.

  <div>
    <div style="margin-bottom: 5px">
      <b>Archivo de salida</b>
    </div>
    <ul>
      <li><code>mallaVentana.pl</code></li>
    </ul>
  </div>

- **Genetico.cpp**
  
  Al no tener ningún archivo de entrada, este script se puede ejecutar de forma independiente.

  <div>
    <div style="margin-bottom: 5px">
      <b>Archivo de salida</b>
    </div>
    <ul>
      <li><code>mallaVentana.pl</code></li>
    </ul>
  </div>

- **algoritmoVentana_5_masivo.cpp** ó **algoritmoVentana_5.cpp**
  
  Estos archivos se encuentran en la carpeta `Algoritmo de renderizado/`.

  <div>
    <div style="margin-bottom: 5px">
      <b>Archivo de salida</b>
    </div>
    <ul>
      <li><code>mallaVentana.pl</code></li>
    </ul>
  </div>

  Al no tener ningún archivo de entrada, estos scripts se pueden ejecutar de forma independiente.

- **aprendizajePorRefuerzo_3_masivo.cpp**
  
  Al no tener ningún archivo de entrada, estos scripts se pueden ejecutar de forma independiente.

  <div>
    <div style="margin-bottom: 5px">
      <b>Archivo de salida</b>
    </div>
    <ul>
      <li><code>mallaVentana.pl</code></li>
    </ul>
  </div>

- **aprendizajePorRefuerzo_3.cpp**
  
  Al no tener ningún archivo de entrada, estos scripts se pueden ejecutar de forma independiente.

  <div>
    <div style="margin-bottom: 5px">
      <b>Archivo de salida</b>
    </div>
    <ul>
      <li><code>mallaRefuerzo.pl</code></li>
    </ul>
  </div>

- **permutaciones5.cpp** ó **permutacionesMuestreo2.cpp** ó **permutacionesMuestreoCasosEspeciales.cpp**

  Este script genera los archivos `.pl` ubicados en la carpeta `Archivos casos/` y `Bases de conocimiento/Muestras 5x5/`, los cuales posteriormente también toma como entrada para generar los archivos nombrados como `baseConocimientoMallasFiltradas.pl`.

  Algunas versiones anteriores de `permutaciones5.cpp` también pudieron generar los archivos `.txt` que tienen la misma nomenclatura que los `.pl`, ubicados en la carpeta `Bases de conocimiento/4x4/`.

  <div style="width: 40%; float: left; margin-right: 5%;">
    <div style="margin-bottom: 5px">
      <b>Archivos de entrada</b>
    </div>
    <ul>
      <li> $n$ <code>,</code> $m$ <code>.pl</code> (generados primero como salida) </li>
    </ul>
    <p></p>
  </div>
  
  <div style="float: none; overflow: hidden;">
    <div style="margin-bottom: 5px">
      <b>Archivos de salida</b>
    </div>
    <ul>
      <li> $n$ <code>,</code> $m$ <code>.pl</code></li>
      <li><code>casos.pl</code></li>
      <li><code>baseConocimientoMallasFiltradas.pl</code></li>
    </ul>
  </div>

  Es posible que estos scripts también hayan generado los archivos que se llaman solamente `baseConocimientoMallas.pl`.

  El archivo `Bases de conocimiento/Muestras 5x5/Seguimiento.txt` se generó de las impresiones en terminal de este script.

  Al solo tener archivos de entrada que son generados por el mismo script, este se puede ejecutar de forma independiente.

- **funcionDeEvaluacion4.pl**
  
  Los archivos de salida `comparacionAlgoritmos.txt` se encuentran en la carpeta `Gnuplot/`, renombrados de acuerdo al tamaño de malla que corresponde su información.

  <div style="width: 40%; float: left; margin-right: 5%;">
    <div style="margin-bottom: 5px">
      <b>Archivos de entrada</b>
    </div>
    <ul>
      <li><code>casos.pl</code></li>
      <li><code>mallaVentana.pl</code></li>
      <li><code>mallaRefuerzo.pl</code></li>
    </ul>
    <p></p>
  </div>
  
  <div style="float: none; overflow: hidden;">
    <div style="margin-bottom: 5px">
      <b>Archivos de salida</b>
    </div>
    <ul>
      <li><code>LimitesPasos.txt</code></li>
      <li><code>baseConocimientoMallasFiltradas.pl</code></li>
      <li><code>comparacionAlgoritmos.txt</code></li>
      <li><code>EvaluacionMallas.txt</code> (solo versiones anteriores)</li>
    </ul>
  </div>

  Algunas versiones anteriores de este script también toman los archivos `baseConocimientoMalla*.pl` como entrada y/o escriben el archivo `EvaluacionMallas.txt` como salida.
  La versión más reciente también tiene comentado el archivo `matrix.pl` como entrada.

- **unirArchivos.cpp**
  
  Une los archivos `EvaluacionMallas`$n$`.txt`

  <div style="width: 40%; float: left; margin-right: 5%;">
    <div style="margin-bottom: 5px">
      <b>Archivos de entrada</b>
    </div>
    <ul>
      <li><code>EvaluacionMallas1.txt</code></li>
      <li><code>EvaluacionMallas2.txt</code></li>
      <li><code>EvaluacionMallas3.txt</code></li>
      <li><code>EvaluacionMallas4.txt</code></li>
    </ul>
    <p></p>
  </div>
  
  <div style="float: none; overflow: hidden; margin-bottom: 68px">
    <div style="margin-bottom: 5px">
      <b>Archivo de salida</b>
    </div>
    <ul>
      <li><code>EvaluacionMallas.txt</code></li>
    </ul>
  </div>

  La ubicación de estos archivos es la carpeta `Bases de conocimiento/`.
  También hay uno en la raíz pero es de tamaño más pequeño.

- **MatricesGnuplot2.cpp**

  Además de las salidas indicadas, este script también generaba los archivos `MatricesEvaluadasGnuplot`$n$`.txt` en la carpeta `Matrices evaluadas/`, el código que las generaba actualmente está comentado.

  <div style="width: 40%; float: left; margin-right: 5%;">
    <div style="margin-bottom: 5px">
      <b>Archivos de entrada</b>
    </div>
    <ul>
      <li><code>EvaluacionMallas.txt</code></li>
      <li><code>LimitesPasos.txt</code></li>
    </ul>
    <p></p>
  </div>
  
  <div style="float: none; overflow: hidden;">
    <div style="margin-bottom: 5px">
      <b>Archivos de salida</b>
    </div>
    <ul>
      <li><code>GraficadorMatricesGnuplot.gpl</code></li>
      <li><code>MallasLatex.tex</code></li>
    </ul>
  </div>

  Los archivos de entrada se encuentran en la ruta `Bases de conocimiento/4x4/` o en la raíz, mientras que los de salida se encuentran en las sub-carpetas de `LatexGnuplot/`.

- **GraficadorMatricesGnuplot.gpl**

  Estos archivos, generados por el script `MatricesGnuplot2.cpp`, sirven para generar archivos `.eps` que contienen gráficas de matrices, con diferentes números en cada celda y de diferentes colores, representando las diferentes posibilidades de arreglos para una malla de cierto tamaño y con un número fijo de objetos de cada clase.

  En cada hoja de un archivo `.eps` se pueden mostrar hasta 10,000 combinaciones de arreglos.
  Para generar cada una de estas 10,000 sub-gráficas, tomaban como entrada los archivos `MatricesEvaluadasGnuplot`$n$`.txt`, donde $n$ va de `0` a `9999`, y que eran generados por el script `MatricesGnuplot2.cpp`.

  Actualmente ni los archivos, ni la ruta donde se encontraban existe, por lo que correr estos scripts con sus entradas actuales generará un error.
  Para que se ejecuten correctamente se deberá hacer un cambio para que se lea la información del archivo `matrices_evaluadas_ordenadas.csv` (generado por `files_to_rows_in_csv.cpp`) en vez de los archivos `MatricesEvaluadasGnuplot`$n$`.txt`.

  <div style="width: 40%; float: left; margin-right: 5%;">
    <div style="margin-bottom: 5px">
      <b>Archivos de entrada</b>
    </div>
    <ul>
      <li><code>MatricesEvaluadasGnuplot</code> $n$ <code>.txt</code></li>
    </ul>
    <p></p>
  </div>
  
  <div style="float: none; overflow: hidden;">
    <div style="margin-bottom: 5px">
      <b>Archivos de salida</b>
    </div>
    <ul>
      <li><code>Mallas</code> $n$ <code>.eps</code> (un archivo por cada 10,000 archivos de entrada)</li>
    </ul>
  </div>

  Los archivos `.eps` generados luego pueden ser unidos por los scripts `MallasLatex.tex`.
  Los PDF ubicados en la carpeta `Mallas PDF/` fueron generados mediante este proceso en las sub-carpetas de `LatexGnuplot/` y luego movidos a dicha carpeta.

- **MallasLatex.tex**
  
  Este script solo se encarga de unir en un PDF los archivos `.eps` generados por `GraficadorMatricesGnuplot.gpl`.

  <div style="width: 40%; float: left; margin-right: 5%;">
    <div style="margin-bottom: 5px">
      <b>Archivos de entrada</b>
    </div>
    <ul>
      <li><code>Mallas</code> $n$ <code>.eps</code></li>
    </ul>
    <p></p>
  </div>
  
  <div style="float: none; overflow: hidden;">
    <div style="margin-bottom: 5px">
      <b>Archivo de salida</b>
    </div>
    <ul>
      <li><code>MallasLatex.pdf</code></li>
    </ul>
  </div>

  También existe un script `01MallasLatex.tex` en el directorio `Bases de conocimiento/4x4/Latex (mallas 10x10 pdfs)/` que hace los mismo, solo que trabaja con archivos de 100 gráficas por página en vez de 10,000 y sus archivos `.eps` de entrada ya no existen (tampoco el de salida).
  Aún así este script es complicado de ejecutar debido a la gran cantidad de archivos de entrada que tiene que manejar.

- **comparacionAlgoritmos.gpl** ó **comparacionAlgoritmosLaTeX.gpl**

  Estos scripts generan un archivo `.eps` con una gráfica comparativa de los resultados de dos algoritmos.

  <div style="width: 40%; float: left; margin-right: 5%;">
    <div style="margin-bottom: 5px">
      <b>Archivos de entrada</b>
    </div>
    <ul>
      <li><code>comparacionAlgoritmos*.txt</code></li>
	  <li><code>LimitesPasos*.txt</code></li>
    </ul>
    <p></p>
  </div>
  
  <div style="float: none; overflow: hidden; margin-bottom: 45px">
    <div style="margin-bottom: 5px">
      <b>Archivo de salida</b>
    </div>
    <ul>
      <li><code>comparacionAlgoritmos*.(eps|tex)</code></li>
    </ul>
  </div>

  Los archivos `Muestreo_VS_RS_*.eps` de la carpeta también pudieron haber sido generados mediante estos scripts.

- **files_to_rows_in_csv.cpp**

  Este archivo tomaba todos los archivos de la carpeta `Matrices evaluadas/`, de nombres `MatricesEvaluadasGnuplot`$n$`.txt`, generados por el script `MatricesGnuplot2.cpp`, los cuales ya no existen.
  Almacenaba su contenido en el archivo CSV `matrices_evaluadas.csv` ó `matrices_evaluadas_ordenadas.csv`.
  El proceso se describe en el archivo `Información importante.txt`.

  A menos que se vuelvan a generar los archivos que toma como entrada, no es posible ejecutar de forma exitosa este script en su estado actual.
