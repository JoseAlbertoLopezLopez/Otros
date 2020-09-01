#include <iostream>
#include <algorithm> 
#include <time.h>
#include <map>
#include <array>
#include <vector>
#include <fstream>

using namespace std;


const int n = 5;
const int m = 5;
const int numClases = 2;
array<int,numClases> Ns {{9,0}};


//#############################################################################################################################


ofstream file("mallaVentana.pl");

int N;
int Naux;
const int espaciosMalla = n*m;
int malla[n+2][m+2];
array<array<int,2>,2> ventana;
array<array<int,2>,2> ventanaAux;
array<array<int,2>,2> matrizAux;
array<int,numClases> NsAux = Ns;
array<array<int, 2>, numClases+1> mayoresMenores;
array<array<int, 2>, numClases+1> mayoresMenoresAux;
array<array<int, 2>, numClases+1> mayoresMenoresAux2;
array<int, numClases+1> indicesMM;
int elementosVentana[numClases+1];
int minoria;
int minoriasTomadas;
int indice_preferencia;

int potencialesImposibles = (n-1)*(m-1);
array<array<int, m-1>, n-1> potencialesCuadrosImposibles; 
array<array<int, m-1>, n-1> potencialesCuadrosImposiblesAux;
array<bool, 4> minoriasEnVentana;
vector<array<int, 3>> listaPotencialesImposibles; 
int numPotencialesImpVentana;
int indiceImposibles;

array<int,numClases> tomarParaVentana;
array<int,numClases+1> repetidos;


// Variables algoritmo basado en puntuaciones /////////////////////////////////////////////////////////////////////////////////


// Total de formas de llenar una ventana.
array<array<int, 2>, 13> formasPosibles = {{{0,0},{1,0},{0,1},{1,1},{2,0},{0,2},{3,0},{0,3},{2,1},{1,2},{2,2},{3,1},{1,3}}};
vector<array<double, 5>> formasPosiblesPuntuacion;		// Formas posibles de llenar la ventana junto con su puntuación.
map<array<int, 2>, bool> elementosLiberados;	// Diccionario con las coordenadas de los elementos sujetables.


map<array<int, numClases>, vector<array<array<int, 2>, 2>>> dicMallasBaseEsquinas = {

	{ {3,0}, { {{{1,1},{1,0}}} } },
	{ {2,0}, { {{{1,0},{1,0}}}, {{{1,0},{0,1}}} } },
	{ {1,0}, { {{{1,0},{0,0}}} } },

	{ {0,3}, { {{{2,2},{2,0}}} } },
	{ {0,2}, { {{{2,0},{2,0}}}, {{{2,0},{0,2}}} } },
	{ {0,1}, { {{{2,0},{0,0}}} } },

	{ {1,3}, { {{{1,2},{2,2}}} } },
	{ {2,2}, { {{{1,1},{2,2}}}, {{{2,1},{1,2}}} } },
	{ {3,1}, { {{{1,1},{1,2}}} } },

	{ {1,2}, { {{{2,2},{1,0}}}, {{{1,2},{2,0}}} } },
	{ {2,1}, { {{{2,1},{1,0}}}, {{{1,2},{1,0}}} } },
	{ {1,1}, { {{{2,1},{0,0}}}, {{{2,0},{0,1}}} } },
	{ {0,0}, { {{{0,0},{0,0}}} } }
};


map<array<int, numClases>, vector<array<array<int, 2>, 2>>> dicMallasBaseBordes = {

	{ {3,0}, { {{{1,1},{1,0}}} } },
	{ {2,0}, { {{{1,1},{0,0}}}, {{{0,1},{1,0}}} } },
	{ {1,0}, { {{{1,0},{0,0}}} } },

	{ {0,3}, { {{{2,2},{2,0}}} } },
	{ {0,2}, { {{{0,2},{2,0}}}, {{{2,2},{0,0}}} } },
	{ {0,1}, { {{{2,0},{0,0}}} } },

	{ {1,3}, { {{{1,2},{2,2}}} } },
	{ {2,2}, { {{{1,1},{2,2}}}, {{{2,1},{1,2}}} } },
	{ {3,1}, { {{{1,1},{2,1}}} } },

	{ {1,2}, { {{{2,1},{2,0}}}, {{{1,2},{2,0}}} } },
	{ {2,1}, { {{{1,1},{2,0}}}, {{{2,1},{1,0}}} } },
	{ {1,1}, { {{{2,1},{0,0}}}, {{{0,1},{2,0}}} } },
	{ {0,0}, { {{{0,0},{0,0}}} } }
};


map<array<int, numClases>, vector<array<array<int, 2>, 2>>> dicMallasBaseCentro = {

	{ {3,0}, { {{{1,1},{1,0}}} } },
	{ {2,0}, { {{{1,1},{0,0}}}, {{{0,1},{1,0}}} } },
	{ {1,0}, { {{{1,0},{0,0}}} } },

	{ {0,3}, { {{{2,2},{2,0}}} } },
	{ {0,2}, { {{{0,2},{2,0}}}, {{{2,2},{0,0}}} } },
	{ {0,1}, { {{{2,0},{0,0}}} } },

	{ {1,3}, { {{{1,2},{2,2}}} } },
	{ {2,2}, { {{{1,1},{2,2}}}, {{{2,1},{1,2}}} } },
	{ {3,1}, { {{{1,1},{2,1}}} } },

	{ {1,2}, { {{{2,1},{2,0}}}, {{{1,2},{2,0}}} } },
	{ {2,1}, { {{{1,1},{2,0}}}, {{{2,1},{1,0}}} } },
	{ {1,1}, { {{{2,1},{0,0}}}, {{{0,1},{2,0}}} } },
	{ {0,0}, { {{{0,0},{0,0}}} } }
};


#include "algoritmoVentana_3.h"


void correrVentana(int r, int c){

	ventana[0][0] = malla[r-1][c-1];
	ventana[0][1] = malla[r-1][c];
	ventana[1][0] = malla[r][c-1];
	ventana[1][1] = malla[r][c];
}


bool llenarMalla(int r, int c, array<array<int,2>,2> mallaBase){

	
}


array<array<int,2>,2>& llenarVentana(int r, int c){
	
	//Contar espacios a llenar.
	int espacios_a_llenar = 0; 
	for(auto &row:ventana) espacios_a_llenar += count(row.begin(), row.end(), -1);

	fill(tomarParaVentana.begin(), tomarParaVentana.end(), 0);
	fill(repetidos.begin(), repetidos.end(), 0);
	
	int indice = 0;
	minoria = 0;
	minoriasTomadas = 0;

	//Contar elementos en la ventana y llenar "tomarParaVentana".
	for(int i=0; i<=1; i++){
	
		for(int j=0; j<=1; j++){
		
			for(int k=1; k<=mayoresMenores.size()-1; k++) if(ventana[i][j] == mayoresMenores[k][0]) minoriasTomadas++;

			if(ventana[i][j] > 0){
				tomarParaVentana[ventana[i][j]-1]++;
				repetidos[ventana[i][j]]++;
			}
			if(ventana[i][j] == 0) repetidos[0]++;
		}
	}
	
	//for(int i=1; i<=mayoresMenores.size()-1; i++) minoria += mayoresMenores[i][1];
		
	//cout << mayoresMenores[0][1] << " " << mayoresMenores[1][1] << " " << mayoresMenores[2][1] << endl;
	//cout << mayoresMenores[0][0] << " " << mayoresMenores[1][0] << " " << mayoresMenores[2][0] << endl << endl;
	//cout << "Minoria = " << minoria << endl;

	//imprimirMatriz2(potencialesCuadrosImposibles);
	//cout << minoriaNecesaria() << endl;

	llenadosPosibles(r, c);

	sort(formasPosiblesPuntuacion.begin(), formasPosiblesPuntuacion.end(), ordenamiento3);

	//cout << "Hola" << endl;
	//for(auto &row:formasPosiblesPuntuacion){ for(auto &elem:row){cout << elem << " ";}; cout << endl;} cout << endl;
	//cout << r << " " << c << endl;

	if(formasPosiblesPuntuacion.size() > 0) colocarVentana(r, c, formasPosiblesPuntuacion[0]);
	else noColocarVentana(r, c);
	
	// Actualizar objetos no colocados.
	for(int i=0; i<=3; i++) mayoresMenores[indicesMM[formasPosiblesPuntuacion[0][i]]][1]--;
	for(int i=0; i<=numClases; i++) mayoresMenores[indicesMM[i]][1] += repetidos[i];
	sort(mayoresMenores.begin(), mayoresMenores.end(), ordenamiento);
	llenar_indicesMM();
	
	eliminarImposiblesPotenciales(r, c, potencialesCuadrosImposibles, ventanaAux, mayoresMenores);

	verificarLiberados(r, c);

	formasPosiblesPuntuacion.clear();
}
					   



int main(){



for(int iw=espaciosMalla; iw>=ceil(espaciosMalla/2.0)+1; iw--){
for(int jw=0; jw<=iw; jw++){
	
Ns[0] = iw-jw;
Ns[1] = jw;

cout << Ns[0] << " " << Ns[1] << endl;

//Inicializar N.
N = accumulate(Ns.begin(), Ns.end(), 0);
Naux = espaciosMalla;

// Verificar casos especiales.
if(N > espaciosMalla){ cout << "Error, más objetos que espacios disponibles." << endl; return 0; }
if(N < ceil(espaciosMalla/2.0)+1){ cout << "Caso trivial" << endl; return 0; }
if(*max_element(Ns.begin(), Ns.end()) > espaciosMalla - floor(n/2.0)*floor(m/2.0)){
	cout << "El arreglo contiene elementos imposibles de tomar." << endl;
	continue;
}

//Inicializar malla (celdas a -1 y fronteras a 0).
for(int i=0; i<=n+1; i++){
	for(int j=0; j<=m+1; j++){
		
		if((i!=0 and i!=n+1) and (j!=0 and j!=n+1)) malla[i][j] = -1;
		else malla[i][j] = 0;
	}
}
imprimirMalla();
 

for(int i=0; i<=Ns.size()-1; i++){ mayoresMenores[i+1][0] = i+1; mayoresMenores[i+1][1] = Ns[i]; }
mayoresMenores[0][0] = 0;
mayoresMenores[0][1] = Naux - accumulate(Ns.begin(), Ns.end(), 0);
sort(mayoresMenores.begin(), mayoresMenores.end(), ordenamiento);
llenar_indicesMM();

//Inicializar mtriz de cuadros imposibles (todos los valores a 1).
for(auto &row:potencialesCuadrosImposibles) fill(row.begin(), row.end(), 1);
potencialesCuadrosImposiblesAux = potencialesCuadrosImposibles;


//Correr ventana. Los indices apuntan a la esquina inferior derecha de esta.
for(int i=2; i<=n; i++){

	for(int j=2; j<=m; j++){
		
		correrVentana(i, j);
		llenarVentana(i, j);
		
		//for(auto &elem:NsAux) cout << elem << " "; cout << endl;
		//imprimirMalla();
	}
}

imprimirMalla();

file << "mallaV([\n";

for(int i=0; i<=n+1; i++){
	file << "[";
	for(int j=0; j<=m+1; j++) file << malla[i][j] << (j!=m+1 ? "," : "]");
	file << (i!=n+1 ? ",\n" : "]).\n");
}

}
}

file.close();


return 0;
}




















