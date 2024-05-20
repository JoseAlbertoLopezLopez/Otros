#include <iostream>
#include <algorithm> 
#include <time.h>
#include <map>
#include <array>
#include <vector>
#include <fstream>

using namespace std;


const int n = 4;
const int m = 4;
const int numClases = 2;
array<int,numClases> N_clase {{10,6}};


//#############################################################################################################################


ofstream file("mallaVentana.pl");

int N;
array<array<int, 2>, numClases+1> Nx;
const int espaciosMalla = n*m;
int malla[n+2][m+2];
array<array<int,2>,2> ventana;
array<array<int,2>,2> ventanaAux;


map<array<int, numClases>, vector<array<array<int, 2>, 2>>> dicVentanas = {

	{ {3,1}, { {{{1,1},{1,2}}} } },
	{ {1,3}, { {{{1,2},{2,2}}} } },
	{ {3,0}, { {{{1,1},{1,0}}} } },
	{ {0,3}, { {{{2,2},{2,0}}} } },
	{ {2,2}, { {{{2,1},{1,2}}}, {{{1,2},{1,2}}} } },
	{ {2,1}, { {{{2,1},{1,0}}}, {{{1,2},{1,0}}} } },
	{ {1,2}, { {{{1,2},{2,0}}}, {{{2,2},{1,0}}} } },
	{ {2,0}, { {{{1,0},{0,1}}}, {{{1,0},{1,0}}} } },
	{ {0,2}, { {{{2,0},{0,2}}}, {{{2,0},{2,0}}} } },
	{ {1,1}, { {{{1,0},{0,2}}}, {{{1,2},{0,0}}} } },
	{ {1,0}, { {{{1,0},{0,0}}} } },
	{ {0,1}, { {{{2,0},{0,0}}} } },
	{ {0,0}, { {{{0,0},{0,0}}} } }
};

// Están ordenadas de acuerdo a "dicVentanas".
array< array<int, 2>, 13 > ventanasSeparadas2 = {{{3,1},{1,3},{3,0},{0,3},{2,2},{2,1},{1,2},{2,0},{0,2},{1,1},{1,0},{0,1},{0,0}}};
int ventanasSeparadas1[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


#include "algoritmoVentana_5.h"


int cont = 0;
void colocarVentana(int r, int c){

	for(int i=0; i<=12; i++){
	
		if(ventanasSeparadas1[i]>0){

			ventana = dicVentanas[ventanasSeparadas2[i]][0];

			if(i<=3 or i>=10){
			
				if(cont%2==0){ 
					malla[r-1][c-1] = ventana[0][0]; 
					malla[r-1][c] = ventana[0][1]; 
					malla[r][c-1] = ventana[1][0]; 
					malla[r][c] = ventana[1][1];
				}
				else{  
					reflejar(ventana);
					transpuesta(ventana);
					malla[r-1][c-1] = ventana[0][0]; 
					malla[r-1][c] = ventana[0][1]; 
					malla[r][c-1] = ventana[1][0]; 
					malla[r][c] = ventana[1][1];
				}
			}
			else{
			
				malla[r-1][c-1] = ventana[0][0]; 
				malla[r-1][c] = ventana[0][1]; 
				malla[r][c-1] = ventana[1][0]; 
				malla[r][c] = ventana[1][1];
			}
			
			cont++;
			ventanasSeparadas1[i]--;
			break;
		}
	}
}
					   



int main(){



for(int iw=espaciosMalla; iw>=ceil(espaciosMalla/2.0)+1; iw--){
for(int jw=0; jw<=iw; jw++){

N_clase[0] = iw-jw;
N_clase[1] = jw;

cout << N_clase[0] << " " << N_clase[1] << endl;

// Inicializar N's.
N = accumulate(N_clase.begin(), N_clase.end(), 0);
Nx =  {{{0, espaciosMalla-N}, {1, N_clase[0]}, {2, N_clase[1]}}};
sort(Nx.begin(), Nx.end(), ordenamiento);


if(N > espaciosMalla){ cout << "Error, más objetos que espacios disponibles." << endl; return 0; }
if(N < ceil(espaciosMalla/2.0)+1){ cout << "Caso trivial" << endl; return 0; }
if(*max_element(N_clase.begin(), N_clase.end()) > espaciosMalla - floor(n/2.0)*floor(m/2.0)){
 cout << "El arreglo contiene elementos imposibles de tomar." << endl; continue;}


// Inicializar malla (celdas a -1 y fronteras a 0).
for(int i=0; i<=n+1; i++){
	for(int j=0; j<=m+1; j++){
		
		if((i!=0 and i!=n+1) and (j!=0 and j!=n+1)) malla[i][j] = -1;
		else malla[i][j] = 0;
	}
}
imprimirMalla();


// Determinar ventanas separadas.
ventanasSeparadas();


// Correr ventana. Los indices apuntan a la esquina inferior derecha de esta.
for(int i=2; i<=n; i++){

	for(int j=2; j<=m; j++){
		
		if(i%2==0 and j%2==0) colocarVentana(i, j);
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




















