file_name=${1::-4};

if [ $file_name != "arbol" ]; then
	latex -output-directory=../../ ../$file_name.tex;
	dvipdf -sOutputFile=../../$file_name.pdf ../../$file_name.dvi;
else
	pdflatex -output-directory=../../ ../$file_name.tex
fi

shopt -s extglob;
rm ../../*.!(tex|pdf|sh);