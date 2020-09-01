#include <iostream>
#include <algorithm> 
#include <time.h>
#include <math.h>
#include <numeric>
#include <array>
#include <map>
#include <fstream>

using namespace std;


const int n = 5;
const int m = 5;
const int numClases = 2;
int Ns[numClases] = {9,16};

double T = 50000000;	// 50000000
int k = 0;
double coefT = 0.0000001;
int numIntercambios = 1;

//#############################################################################################################################


ofstream file("mallaVentana.pl");

int N;
const int espaciosMalla = n*m;
double puntaje_malla;
int malla[n+2][m+2];/* = {
{0,0,0,0,0},
{0,2,1,2,0},
{0,1,2,1,0},
{0,2,1,2,0},
{0,0,0,0,0}
};*/
int mallaNew[n+2][m+2];

int mejorMalla[n+2][m+2];
double mejorPuntaje = 0;
double mejoresPuntajes[3];
int contSinCambios = 0;
int contCambios = 0;
double puntajeAnterior;
double puntajeNuevo;
double puntajesMalla[n][m];
int aux;
double aux2;


#include "RS.h"


void inicializarMallaAleatoriamente(int (&malla)[n+2][m+2]){

	int numObjetosEnMalla = 0;
	int NsAux[numClases];
	int NsTotal = N;
	int cont = 0;
	double aleatorio;
	float limInf = 0.0;
	float limSup = 0.0;

	copy(Ns, Ns + numClases, NsAux);
	
	while(numObjetosEnMalla < N){
	
		aleatorio = (double) rand()/(RAND_MAX);
		
		if(malla[(int) floor(cont/n)%n + 1][cont%m + 1] == 0 and aleatorio <= 1.0*N/espaciosMalla){
		
			aleatorio = (double) rand()/(RAND_MAX);
			
			limInf = 0.0;
			limSup = 0.0;
			
			for(int i=0; i<=numClases-1; i++){
				
				if(NsAux[i] == 0) continue;
				limSup += 1.0*NsAux[i]/NsTotal;
		
				if(aleatorio > limInf and aleatorio <= limSup){
			
					malla[(int) floor(cont/n)%n+1][cont%m+1] = i+1;
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
}




int main(){




srand(time(NULL));
N = accumulate(Ns, Ns + numClases, 0);


if(N > espaciosMalla){ cout << "Error, más objetos que espacios disponibles." << endl; return 0; }
if(N < ceil(espaciosMalla/2.0)+1){ cout << "Caso trivial" << endl; return 0; }
if(*max_element(Ns, Ns + numClases) > espaciosMalla - floor(n/2.0)*floor(m/2.0)){
	cout << "El arreglo contiene elementos imposibles de tomar." << endl;
}
	

// Inicializar malla.
inicializarMallaAleatoriamente(malla);
copiarMalla(malla, mallaNew);
imprimirVectorMatriz(malla, n, m);

puntajeAnterior = puntajeMalla(malla);
cout << "Puntaje = " << puntajeAnterior << endl << endl;


double a = 0.99991; // 0.99991
double b= 1;
double iteraciones = 0;
while(T>(1.0*b/(1.0-a))+0.00001){	// T>(1.0*b/(1.0-a))+0.00001

	cambiosAleatorios(numIntercambios);
	puntajeNuevo = puntajeMalla(mallaNew);
	
	if(rand()/(RAND_MAX) < exp(-(puntajeAnterior-puntajeNuevo)/(coefT*T)) or puntajeAnterior <= puntajeNuevo){
		
		copiarMalla(mallaNew, malla);
		contCambios++;
		//cout << "malla" << endl;
		//imprimirVectorMatriz(malla, n, m);
		puntajeAnterior = puntajeNuevo;
		
		if(mejorPuntaje<puntajeNuevo){ copiarMalla(mallaNew, mejorMalla); mejorPuntaje = puntajeNuevo; }
		//T--;
		//k=0;
	}
	else{copiarMalla(malla, mallaNew);}
	
	//T--;
	
	//T = 0.9*T;
	
	//T = 1.0/log(k);
	
	//T--;elseT = 0.99998*T;
	
	T = a*T + b;
	iteraciones++;
}



file << "mallaV([\n";

for(int i=0; i<=n+1; i++){
	file << "[";
	for(int j=0; j<=m+1; j++) file << mejorMalla[i][j] << (j!=m+1 ? "," : "]");
	file << (i!=n+1 ? ",\n" : "]).\n");
}

cout << Ns[0] << "," << Ns[1] << endl;
imprimirVectorMatriz(mejorMalla, n, m);
cout << "Puntaje = " << puntajeAnterior << endl;
cout << "Iteraciones = " << iteraciones << endl;
cout << "Intercambios = " << contCambios << endl;

file.close();

return 0;

}
