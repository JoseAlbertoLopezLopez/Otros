#include <iostream>
#include <algorithm> 
#include <time.h>
#include <array>
#include <map>
#include <fstream>

using namespace std;


const int n = 11;
const int m = 11;
const int numClases = 2;
int Ns[numClases] = {96,25};


const int poblacion = 1000;
const int hijosPorPareja = 2;
const int parejas = 0.5*poblacion;
const double probMutacion = 1;
const int cambiosMutacion = 1;
const int limGeneraciones = 100;


//#############################################################################################################################


const int descendencia = parejas*hijosPorPareja;
int generacionActual = 0;
int indicesPadres[parejas*2];

ofstream file("mallaVentana.pl");

int N;
const int espaciosMalla = n*m;
int mallas[poblacion + descendencia][n+2][m+2];/* = {
{0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0},
{0,1,2,1,2,1,2,0},
{0,1,1,1,1,1,1,0},
{0,1,2,1,2,1,2,0},
{0,1,1,1,1,1,1,0},
{0,1,2,1,2,1,2,0},
{0,0,0,0,0,0,0,0}
};*/
int mallasAux[poblacion + descendencia][n+2][m+2];
//int mallasDescendencia[parejas*hijosPorPareja][n+2][m+2];

int mejoresMallas[3][n+2][m+2];
double mejoresPuntajes[3];
int contSinCambios = 0;
int contCambios = 0;
array<array<double, 2>, poblacion + descendencia> puntajesPoblacion;
//array<array<double, 2>, parejas*hijosPorPareja> puntajesDescendencia;
double sumaPuntajes = 0;
double intervalos[poblacion+1];
double puntajesMallas[poblacion + descendencia][n+2][m+2];
array<int, numClases+1> sinColocar;
array<int, numClases+1> sinColocarAux;
vector<array<int, 2>> noColocados;
int aux;
double aux2;
int aux3;

double aleatorio;


#include "Genetico.h"


int numObjetosEnMalla = 0;
int NsAux[numClases];
int NsTotal = N;
int cont = 0;
float limInf = 0.0;
float limSup = 0.0;
void inicializarMallasAleatoriamente(){

	// Solo se inicializan las mallas y puntajes de las primeras componentes de poblacion.

	for(int k=0; k<=poblacion-1; k++){

	numObjetosEnMalla = 0;
	NsTotal = N;
	cont = 0;
	limInf = 0.0;
	limSup = 0.0;

	copy(Ns, Ns + numClases, NsAux);
	
	while(numObjetosEnMalla < N){

		aleatorio = (double) rand()/(RAND_MAX);
		
		if(mallas[k][(int) floor(cont/n)%n + 1][cont%m + 1] == 0 and aleatorio <= 1.0*N/espaciosMalla){
		
			aleatorio = (double) rand()/(RAND_MAX);
			
			limInf = 0.0;
			limSup = 0.0;
			
			for(int i=0; i<=numClases-1; i++){
				
				if(NsAux[i] == 0) continue;
				limSup += 1.0*NsAux[i]/NsTotal;

				if(aleatorio > limInf and aleatorio <= limSup){
			
					mallas[k][(int) floor(cont/n)%n+1][cont%m+1] = i+1;
					numObjetosEnMalla++;
					NsAux[i]--;
					NsTotal--;
					cont++;
					break;
				}
				
				limInf = limSup;
			}
		}
		else cont++;
	}

	puntajesPoblacion[k][0] = puntajeMalla(mallas[k], puntajesMallas[k]);
	sumaPuntajes += puntajesPoblacion[k][0];
	puntajesPoblacion[k][1] = k;
	//imprimirVectorMatriz(mallas[k], n, m);
	//cout << "Puntaje = " << puntajesPoblacion[k][0] << endl << endl;
	
	}
}




int main(){




srand(time(NULL));
N = accumulate(Ns, Ns + numClases, 0);

for(int i=1; i<=numClases; i++) sinColocar[i] = Ns[i-1];
sinColocar[0] = espaciosMalla - N;

if(N > espaciosMalla){ cout << "Error, más objetos que espacios disponibles." << endl; return 0; }
if(N < ceil(espaciosMalla/2.0)+1){ cout << "Caso trivial" << endl; return 0; }
if(*max_element(Ns, Ns + numClases) > espaciosMalla - floor(n/2.0)*floor(m/2.0)){
	cout << "El arreglo contiene elementos imposibles de tomar." << endl;
}
	

// Inicializar malla.
inicializarMallasAleatoriamente();


while(generacionActual <= limGeneraciones){

	escogerPadres2();
	recombinacion_mutacion();
	seleccion();
	
	generacionActual++;
	
	//cout << "----------------Generación " << generacionActual << "----------------" << endl;
	
	//for(int i=0; i<=poblacion+descendencia-1; i++){ imprimirVectorMatriz(mallas[i], n, m); cout << "Puntaje = " << puntajesPoblacion[i][0] << endl << endl;}
}

//ordenarPoblacion();
//for(int i=0; i<=poblacion+descendencia-1; i++){ imprimirVectorMatriz(mallas[i], n, m); cout << i << " Puntaje = " << puntajesPoblacion[i][0] << endl << endl;}
//for(int i=0; i<=poblacion+descendencia-1; i++) cout << i << " " << puntajesPoblacion[i][0] << endl;

file << "mallaV([\n";

for(int i=0; i<=n+1; i++){
	file << "[";
	for(int j=0; j<=m+1; j++) file << mallas[0][i][j] << (j!=m+1 ? "," : "]");
	file << (i!=n+1 ? ",\n" : "]).\n");
}

cout << Ns[0] << "," << Ns[1] << endl;
imprimirVectorMatriz(mallas[0], n, m);
cout << "Puntaje = " << puntajesPoblacion[0][0] << endl;
//cout << "Iteraciones = " << iteraciones << endl;
cout << "Intercambios = " << contCambios << endl;

file.close();

return 0;

}
