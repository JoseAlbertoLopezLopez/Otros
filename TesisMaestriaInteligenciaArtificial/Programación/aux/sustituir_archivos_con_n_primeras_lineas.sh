#!/bin/bash
# 
# Script para tomar muestras de archivos (n primeras líneas) de 
# manera automática.
# 
# Para cada carpeta del repositorio con muchos archivos a los que se 
# les tuviera que tomar muestra se aplicó el siguiente fragmento de 
# código que toma las n primeras líneas de cada archivo que coincida 
# con el nombre o patrón indicado, en el directorio indicado.
# 
# Solo los parámetros de una carpeta se encuentran descomentados.

# Archivos casos/
# Bases de conocimiento/Muestras 5x5/
#main_directory="Programación/Bases de conocimiento/Muestras 5x5/"
#name_pattern="*.pl"
#n=200

# Bases de conocimiento/4x4/
#main_directory="Programación/Bases de conocimiento/4x4/"
#name_pattern="*.txt"
#n=200

# LatexGnuplot/
main_directory="Programación/LatexGnuplot/"
name_pattern="GraficadorMatricesGnuplot.gpl"
n=101

# Recorrer todos los subdirectorios del directorio principal
find "$main_directory" -type f -name "$name_pattern" -size +95k -print0 | 
while IFS= read -r -d '' file; do
	# Tomar muestra
    head -n $n "$file" > "$file.tmp" && mv "$file.tmp" "$file"
	# Solo para "LatexGnuplot/"
	#echo -e "unset label\nunset multiplot\nunset output" >> $file
done

# Verificar antes el número de líneas
# while IFS= read -r -d '' file; do
# 	num_lines=$(wc -l < $file)
# 	if [ $num_lines -ge $min_lines ]; then
# 		head -n $n $file > $file.tmp && mv $file.tmp $file
# 		echo -e "unset label\nunset multiplot\nunset output" >> $file
# 	fi
# done