for file_path in ../*.tex
	do 
		file_name=${file_path:3:-4};
		echo $file_name;

		if [ $file_name != "arbol" ]; then
			latex -output-directory=../../ ../$file_name.tex;
			dvipdf -sOutputFile=../../$file_name.pdf ../../$file_name.dvi;
		fi
	done

pdflatex -output-directory=../../ ../arbol.tex

shopt -s extglob;
rm ../../*.!(tex|pdf|sh);