#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>
#include <vector>
#include <boost/variant.hpp>
#include <iomanip>
#include <sys/stat.h>

using namespace std;
using namespace boost;

typedef boost::variant<double, char, int> boostVar;

ifstream evaluacionMallas;
ifstream limitesPasos;

ofstream graficadorMatricesGnuplot;
ofstream matricesEvaluadasGnuplot;
ofstream mallasLatex;

string ruta_s;
char ruta[100];
char archivo[100];
char archivoGnuplot[100];
char archivoLatex[100];

float largoDocumento = 25.5;	// Pulgadas.
float altoDocumento;
float altoTabla = 0.025;	// Pulgadas.
int mallasPorRenglon = 100;
int renglonesPagina = 100;
int mallasPagina = (mallasPorRenglon*renglonesPagina);
int renglonesPDF;
double anchoTabla = 0.078431372549;			// 1 = Ancho del documento.
double margenHorizontal = 0.0196078431373;	// 1 = Ancho del documento.
double margenVertical = 0.005;				// Pulgadas.
double margenTitulo = 1.0;
double margenVerticalUnidad;				// 1 = Ancho del documento.
double fraccionRenglon;						// 1 = Ancho del documento.

int numMallas;
int lineas;
int lineasPorMalla = 5;

char buffer[100];

int renglonesMalla;
int columnasMalla;
int celdas;
int objetosPorClase[2];
int objetosPorClaseGrupo[2];

int sumaPasosMalla;
boostVar promedioPasosMalla;
boostVar guion = '-';
boostVar minPasosElementoMalla;
boostVar maxPasosElementoMalla;
int minPasosGrupo;
int maxPasosGrupo;

double color;

bool imposible = false;
bool cambioDeGrupo = false;

int cont = 0;
int contCasos = 1;


vector<vector<int>> malla;
vector<vector<int>> evaluacionMalla;

vector<vector<int>> leerMatrizExtendida(ifstream& archivo, int renglones, int columnas){

	vector<vector<int>> matriz(renglones, vector<int>(columnas));

	for(int i=1; i<=columnas+2; i++){
	
		archivo.getline(buffer, 100, ',');
	}
	
	for(int i=0; i<=renglones-1; i++){
	
		archivo.getline(buffer, 100, ',');
	
		for(int j=0; j<=columnas-1; j++){
			archivo.getline(buffer, 100, ',');
			matriz[i][j] = atoi(buffer);
		}
	
		archivo.getline(buffer, 100, ',');
	}
	
	archivo.getline(buffer, 100);
	
	return matriz;
}

unsigned int numeroDeLineas(string archivo){
	
	ifstream archivo_entrada(archivo, ifstream::in);
	int lin=0;
	while(archivo_entrada.good()) if(archivo_entrada.get()=='\n') lin++;
	return lin;
}

string intToString(int x){

	std::string itos;
	std::stringstream canal_string;
	canal_string << x;
	itos = canal_string.str();
	canal_string.str(std::string());

	return itos;
}


void imprimirPreambulo(){

//graficadorMatricesGnuplot << "set term eps enhanced color font \"Helvetica\"" << endl;
//graficadorMatricesGnuplot << "set term eps enhanced color size " << largoDocumento << "," << altoDocumento << " font \"Helvetica\"" << endl;
graficadorMatricesGnuplot << "set term eps enhanced color size 51,63 font \"Helvetica\"" << endl;

graficadorMatricesGnuplot << "set tics scale 0" << endl;

//MODIFICAR
graficadorMatricesGnuplot << "set xtics 0,1,3" << endl;
graficadorMatricesGnuplot << "set ytics 0,1,3" << endl;
graficadorMatricesGnuplot << "set xtics (''0,''1,''2,''3,''4)" << endl;
graficadorMatricesGnuplot << "set ytics (''0,''1,''2,''3,''4)" << endl;


graficadorMatricesGnuplot << "set size ratio 1" << endl;
graficadorMatricesGnuplot << "unset border" << endl;
graficadorMatricesGnuplot << "set grid front lt 1 lw 1 lc -1" << endl;
graficadorMatricesGnuplot << "set datafile separator \",\"" << endl;
graficadorMatricesGnuplot << "set pm3d implicit # Para que los objetos puedan tomar colores de la paleta." << endl;
graficadorMatricesGnuplot << "set palette model RGB defined (0 \"red\", 0.5 \"yellow\", 1 \"green\")" << endl;
graficadorMatricesGnuplot << "unset colorbox" << endl;
graficadorMatricesGnuplot << "set title offset 0,-0.3" << endl;


mallasLatex << "% !TEX encoding = UTF-8 Unicode" << endl;
mallasLatex << "\\documentclass[12pt,letterpaper,oneside]{report}" << endl;
mallasLatex << "\\usepackage[utf8]{inputenc}" << endl;
mallasLatex << "\\usepackage[T1]{fontenc}" << endl;
mallasLatex << "\\usepackage[absolute,overlay]{textpos}" << endl;
mallasLatex << "\\usepackage{amssymb}" << endl;
mallasLatex << "\\usepackage{amsmath}" << endl;
mallasLatex << "\\usepackage[normalem]{ulem}" << endl;
mallasLatex << "\\usepackage{color}" << endl;
mallasLatex << "%\\usepackage[demo]{graphicx}" << endl;
mallasLatex << "\\usepackage{subcaption}" << endl;
mallasLatex << "\\usepackage{geometry}" << endl;
mallasLatex << "\\geometry{" << endl;
mallasLatex << "papersize={25.5in,31.5in}," << endl;
mallasLatex << "right=0mm," << endl;
mallasLatex << "left=0mm," << endl;
mallasLatex << "top=0mm," << endl;
mallasLatex << "bottom=0mm" << endl;
mallasLatex << "}" << endl;
mallasLatex << "\\usepackage{anyfontsize}" << endl;
mallasLatex << "\\usepackage{float}" << endl;
mallasLatex << "\\usepackage{graphicx}" << endl;
mallasLatex << "\\usepackage{tikz}" << endl;
mallasLatex << "\\usepackage[spanish]{babel}" << endl;
mallasLatex << "\\spanishdecimal{.}" << endl;
mallasLatex << "\\begin{document}" << endl;
}




int main(){



lineas = 23569500;//numeroDeLineas("EvaluacionMallas.txt");

cout << "Líneas = " << lineas << endl;

numMallas = lineas/lineasPorMalla;
renglonesPDF = ceil(1.0*numMallas/mallasPorRenglon);
altoDocumento = renglonesPagina*(altoTabla + margenVertical) + margenVertical + margenTitulo;
margenVerticalUnidad = margenVertical/altoDocumento;
fraccionRenglon = (margenVertical + altoTabla)/altoDocumento;

evaluacionMallas.open("EvaluacionMallas.txt");
limitesPasos.open("LimitesPasos.txt");

limitesPasos.getline(buffer, 100, '/');
objetosPorClaseGrupo[0] = atoi(buffer);
limitesPasos.getline(buffer, 100, ',');
objetosPorClaseGrupo[1] = atoi(buffer);
limitesPasos.getline(buffer, 100, '/');
minPasosGrupo = atoi(buffer);
limitesPasos.getline(buffer, 100);
maxPasosGrupo = atoi(buffer);

ruta_s = "./LatexGnuplot/" + intToString(objetosPorClaseGrupo[0]) + "," + intToString(objetosPorClaseGrupo[1]);
strcpy(ruta, (ruta_s).c_str());
mkdir(ruta, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
strcpy(archivoLatex, (ruta_s + "/MallasLatex.tex").c_str());
mallasLatex.open(archivoLatex);
	
strcpy(archivoGnuplot, (ruta_s + "/GraficadorMatricesGnuplot.gpl").c_str());
graficadorMatricesGnuplot.open(archivoGnuplot);
			
imprimirPreambulo();




for(int n=0; n<=numMallas-1; n++){

	// Leer "EvaluacionMallas.txt".

	evaluacionMallas.getline(buffer, 100, 'x');
	renglonesMalla = atoi(buffer);
	evaluacionMallas.getline(buffer, 100, ',');
	columnasMalla = atoi(buffer);
	celdas = renglonesMalla*columnasMalla;
	
	evaluacionMallas.getline(buffer, 100, ',');
	objetosPorClase[0] = atoi(buffer);
	evaluacionMallas.getline(buffer, 100);
	objetosPorClase[1] = atoi(buffer);
	
	malla = leerMatrizExtendida(evaluacionMallas, renglonesMalla, columnasMalla);
	evaluacionMallas.getline(buffer, 100);
	//evaluacionMalla = leerMatrizExtendida(evaluacionMallas, renglonesMalla, columnasMalla);
	
	evaluacionMallas.getline(buffer, 100, ',');
	
	if(buffer[0] == '-'){
	
		evaluacionMallas.getline(buffer, 100);
		evaluacionMallas.getline(buffer, 100);
		imposible = true;
	}
	else{

		sumaPasosMalla = atoi(buffer);
		evaluacionMallas.getline(buffer, 100, ',');
		promedioPasosMalla = atof(buffer);
		evaluacionMallas.getline(buffer, 100, ',');
		minPasosElementoMalla = atoi(buffer);
		evaluacionMallas.getline(buffer, 100);
		maxPasosElementoMalla = atoi(buffer);
		
		evaluacionMallas.getline(buffer, 100);
		imposible = false;
	}
	
	if(objetosPorClaseGrupo[0] != objetosPorClase[0] or objetosPorClaseGrupo[1] != objetosPorClase[1]){
	
		cambioDeGrupo = true;
		
		contCasos++;
		
		limitesPasos.getline(buffer, 100, '/');
		objetosPorClaseGrupo[0] = atoi(buffer);
		limitesPasos.getline(buffer, 100, ',');
		objetosPorClaseGrupo[1] = atoi(buffer);
		limitesPasos.getline(buffer, 100, '/');
		minPasosGrupo = atoi(buffer);
		limitesPasos.getline(buffer, 100);
		maxPasosGrupo = atoi(buffer);
		
		graficadorMatricesGnuplot << "unset label" << endl << "unset multiplot" << endl << "unset output" << endl;
		mallasLatex << "\\end{document}" << endl;
		
		mallasLatex.close();
		graficadorMatricesGnuplot.close();
		
		ruta_s = "./LatexGnuplot/"+intToString(objetosPorClaseGrupo[0])+","+intToString(objetosPorClaseGrupo[1]);
		strcpy(ruta, (ruta_s).c_str());
		mkdir(ruta, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		strcpy(archivoLatex, (ruta_s + "/MallasLatex.tex").c_str());
		mallasLatex.open(archivoLatex);
	
		strcpy(archivoGnuplot, (ruta_s + "/GraficadorMatricesGnuplot.gpl").c_str());
		graficadorMatricesGnuplot.open(archivoGnuplot);
			
		imprimirPreambulo();
		
		cont = 0;
	}
		
	if(cont%mallasPagina==0 or cambioDeGrupo){

		graficadorMatricesGnuplot << "set output \"Mallas" << setfill('0') << setw(4) << n << ".eps\"" << endl;
		
		mallasLatex << "\\begin{textblock*}{\\paperwidth}(-0.6cm,0cm)" << endl;
		mallasLatex << "\\includegraphics[width=\\paperwidth, height=\\paperheight]{Mallas" << setfill('0') << setw(4) << n << ".eps}" << endl;
		mallasLatex << "\\end{textblock*}" << endl << endl << "\\ \\pagebreak" << endl;
		
		if(cambioDeGrupo or n==0){
		
			graficadorMatricesGnuplot << "set label \"N = " << objetosPorClase[0] + objetosPorClase[1] << ", Cubos = " << objetosPorClase[0] 
			<< ", Prismas = " << objetosPorClase[1] << "\" at screen 0.5,0.97 center font \"Helvetica,160\"" << endl;
			
			graficadorMatricesGnuplot << "set multiplot layout " << renglonesPagina << "," << mallasPorRenglon << 
			" margins 0.01,0.99,0.01,0.94 spacing 0.002,0.002"  << endl;
		}
		else{
		
			graficadorMatricesGnuplot << "set multiplot layout " << renglonesPagina << "," << mallasPorRenglon << 
			" margins 0.01,0.99,0.01,0.99 spacing 0.002,0.002"  << endl;
		}
	}
	
	/*strcpy(archivo, ("Matrices evaluadas/MatricesEvaluadasGnuplot" + intToString(n) + ".txt").c_str());
	matricesEvaluadasGnuplot.open(archivo);
		
	for(int i=renglonesMalla-1; i>=0; i--){
	
		for(int j=0; j<=columnasMalla-1; j++){
		
			if(malla[renglonesMalla-1-i][j]!=0){
				
				matricesEvaluadasGnuplot << j+0.5 << ',' << i+0.5 << ',' << malla[renglonesMalla-1-i][j] << 
				" (" << (evaluacionMalla[renglonesMalla-1-i][j] == -1 ? "-" : intToString(evaluacionMalla[renglonesMalla-1-i][j])) << ")" << endl;
			}
			else{
			
				matricesEvaluadasGnuplot << j+0.5 << ',' << i+0.5 << ',' << endl;
			}
		}
	}
	
	matricesEvaluadasGnuplot.close();*/
	
	// Leer "LimitesPasos.txt".
	
	/*if(cambioDeGrupo){

		limitesPasos.getline(buffer, 100, '/');
		objetosPorClaseGrupo[0] = atoi(buffer);
		limitesPasos.getline(buffer, 100, ',');
		objetosPorClaseGrupo[1] = atoi(buffer);
		limitesPasos.getline(buffer, 100, '/');
		minPasosGrupo = atoi(buffer);
		limitesPasos.getline(buffer, 100);
		maxPasosGrupo = atoi(buffer);
	}*/
	
	if(!imposible){
	
		if(maxPasosGrupo != minPasosGrupo){
			
			color = 1.0 - (1.0*sumaPasosMalla-minPasosGrupo)/(maxPasosGrupo-minPasosGrupo);
		}
		else{

			color = 1;
		}
	}
	
	//graficadorMatricesGnuplot << "set origin " << margenHorizontal+(n%mallasPorRenglon)*(anchoTabla+margenHorizontal) 
	//<< ',' << 1-ceil((1.0*n+1)/mallasPorRenglon)*fraccionRenglon << endl;
	
	graficadorMatricesGnuplot << "set title \"Promedio=" << (imposible ? guion : promedioPasosMalla) << ", Min=" << (imposible ? guion : minPasosElementoMalla) 
	<< ", Max=" << (imposible ? guion : maxPasosElementoMalla) << "\" font ',3'" << endl;
	
	if(!imposible){
	
		graficadorMatricesGnuplot << "set object 1 rectangle from graph 0, graph 0 to graph 1, graph 1 behind fc palette frac "
		<< color << " fs noborder"  << endl;
	}
	else{
	
		graficadorMatricesGnuplot << "set object 1 rectangle from graph 0, graph 0 to graph 1, graph 1 behind fc \"gray\" fs noborder"  << endl;
	}

	graficadorMatricesGnuplot << "plot[0:" << renglonesMalla << "][0:" << columnasMalla << "] "
	<< "\"/home/j6/Desktop/Función de evaluación/Matrices evaluadas/MatricesEvaluadasGnuplot" << n << ".txt\" using 1:2:3 with labels font ',4' t \"\"" << endl;
	
	if(n%10000==0){ graficadorMatricesGnuplot << "pr " << n << endl; cout << n << endl;}
	
	graficadorMatricesGnuplot << "unset object 1" << endl;
	
	if(cont%mallasPagina==mallasPagina-1){
	
		graficadorMatricesGnuplot << "unset label" << endl << "unset multiplot" << endl << "unset output" << endl;
	}
	
	cambioDeGrupo = false;
	cont++;
}

graficadorMatricesGnuplot << "unset label" << endl << "unset multiplot" << endl << "unset output" << endl;
mallasLatex << "\\end{document}" << endl;

limitesPasos.close();
evaluacionMallas.close();

mallasLatex.close();
graficadorMatricesGnuplot.close();



return 0;

}
