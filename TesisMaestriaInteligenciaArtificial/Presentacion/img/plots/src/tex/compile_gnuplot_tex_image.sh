file_name=${1::-4};

cd ../gnuplot/
gnuplot -e "load \"$file_name.gpl\""

#cd ../tex/
#latex -output-directory=../../ $file_name.tex;
#dvipdf -sOutputFile=../../$file_name.pdf $file_name.dvi;