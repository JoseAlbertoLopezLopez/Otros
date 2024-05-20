#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>
#include <vector>
#include <boost/variant.hpp>

using namespace std;
using namespace boost;

typedef boost::variant<double, char, int> boostVar;

ifstream evaluacionMallas;
ifstream limitesPasos;

ofstream graficadorMatricesGnuplot;
ofstream matricesEvaluadasGnuplot;

float largoDocumento = 25.5;	// Pulgadas.
float altoDocumento;
float altoTabla = 2.5;	// Pulgadas.
int renglonesPDF;
int mallasPorRenglon = 10;
double anchoTabla = 0.078431372549;			// 1 = Ancho del documento.
double margenHorizontal = 0.0196078431373;	// 1 = Ancho del documento.
double margenVertical = 0.5;				// Pulgadas.
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




int main(){



lineas = numeroDeLineas("EvaluacionMallas.txt");
numMallas = lineas/lineasPorMalla;
renglonesPDF = ceil(1.0*numMallas/mallasPorRenglon);
altoDocumento = renglonesPDF*(altoTabla + margenVertical) + margenVertical;
margenVerticalUnidad = margenVertical/altoDocumento;
fraccionRenglon = (margenVertical + altoTabla)/altoDocumento;

graficadorMatricesGnuplot.open("GraficadorMatricesGnuplot.gpl");
matricesEvaluadasGnuplot.open("MatricesEvaluadasGnuplot.txt");

evaluacionMallas.open("EvaluacionMallas.txt");
limitesPasos.open("LimitesPasos.txt");


graficadorMatricesGnuplot << "set term eps enhanced color size " << largoDocumento << "," << altoDocumento << " font \"Helvetica\"" << endl << endl;
graficadorMatricesGnuplot << "set output \"Mallas.eps\"" << endl << endl;
graficadorMatricesGnuplot << "set tics scale 0" << endl << endl;
graficadorMatricesGnuplot << "set xtics 0,1,2" << endl;
graficadorMatricesGnuplot << "set ytics 0,1,2" << endl << endl;
graficadorMatricesGnuplot << "set xtics (''0,''1,''2)" << endl;
graficadorMatricesGnuplot << "set ytics (''0,''1,''2)" << endl << endl;
graficadorMatricesGnuplot << "set size 1,1" << endl << endl;
graficadorMatricesGnuplot << "unset border" << endl << endl;
graficadorMatricesGnuplot << "set grid front lt 1 lw 6 lc -1" << endl << endl;
graficadorMatricesGnuplot << "set datafile separator \",\"" << endl << endl;
graficadorMatricesGnuplot << "set pm3d implicit # Para que los objetos puedan tomar colores de la paleta." << endl << endl;
graficadorMatricesGnuplot << "set palette model RGB defined (0 \"red\", 0.5 \"yellow\", 1 \"green\")" << endl;
graficadorMatricesGnuplot << "unset colorbox" << endl << endl;
graficadorMatricesGnuplot << "set multiplot layout " << renglonesPDF << "," << mallasPorRenglon << endl << endl;
//graficadorMatricesGnuplot << "	set size " << anchoTabla << "," << altoTabla/altoDocumento << endl << endl;


limitesPasos.getline(buffer, 100, '/');
objetosPorClaseGrupo[0] = atoi(buffer);
limitesPasos.getline(buffer, 100, ',');
objetosPorClaseGrupo[1] = atoi(buffer);
limitesPasos.getline(buffer, 100, '/');
minPasosGrupo = atoi(buffer);
limitesPasos.getline(buffer, 100);
maxPasosGrupo = atoi(buffer);

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
	evaluacionMalla = leerMatrizExtendida(evaluacionMallas, renglonesMalla, columnasMalla);
	
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
		
	for(int i=renglonesMalla-1; i>=0; i--){
	
		for(int j=0; j<=columnasMalla-1; j++){
		
			if(malla[renglonesMalla-1-i][j]!=0){
			
				matricesEvaluadasGnuplot << j+0.5 << ',' << i+0.5 << ',' << 
				malla[renglonesMalla-1-i][j] << " (" << evaluacionMalla[renglonesMalla-1-i][j] << ")" << endl;
			}
			else{
			
				matricesEvaluadasGnuplot << j+0.5 << ',' << i+0.5 << ',' << endl;
			}
		}
	}
	
	// Leer "LimitesPasos.txt".
	
	if(objetosPorClaseGrupo[0] != objetosPorClase[0] or objetosPorClaseGrupo[1] != objetosPorClase[1]){

		limitesPasos.getline(buffer, 100, '/');
		objetosPorClaseGrupo[0] = atoi(buffer);
		limitesPasos.getline(buffer, 100, ',');
		objetosPorClaseGrupo[1] = atoi(buffer);
		limitesPasos.getline(buffer, 100, '/');
		minPasosGrupo = atoi(buffer);
		limitesPasos.getline(buffer, 100);
		maxPasosGrupo = atoi(buffer);
	}
	
	if(imposible){
	
		color = 0; 
	}
	else{
	
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
	<< ", Max=" << (imposible ? guion : maxPasosElementoMalla) << '\"' << endl;
	
	graficadorMatricesGnuplot << "set object 1 rectangle from graph 0, graph 0 to graph 1, graph 1 behind fc palette frac "
	<< color << " fs noborder"  << endl;

	graficadorMatricesGnuplot << "plot[0:" << renglonesMalla << "][0:" << columnasMalla << "] "
	<< "\"MatricesEvaluadasGnuplot.txt\" using 1:2:($0 >= " << n*celdas << " && $0 <= " << (n+1)*celdas-1 
	<< " ? $3 : \"\") with labels font ',20' t \"\"" << endl;
	
	graficadorMatricesGnuplot << "pr " << n << endl;
	
	graficadorMatricesGnuplot << "unset object 1" << endl << endl;
}

graficadorMatricesGnuplot << "unset multiplot" << endl << endl << "unset output" << endl;

limitesPasos.close();
evaluacionMallas.close();

matricesEvaluadasGnuplot.close();
graficadorMatricesGnuplot.close();



return 0;

}
