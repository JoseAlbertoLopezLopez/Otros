#include <iostream>
#include <algorithm> 
#include <time.h>
#include <array>
#include <map>
#include <fstream>

using namespace std;


const int n = 4;
const int m = 4;
const int numClases = 2;
/*const*/ int Ns[numClases] = {9,0};
const double bonoMaxProp = 0.0;		// 5.0


//#############################################################################################################################


ofstream file("mallaVentana.pl");

int N;
const int espaciosMalla = n*m;
double puntajeMalla;
int malla[n+2][m+2];/* = {
{0,0,0,0,0,0},
{0,2,1,2,0,0},
{0,0,0,2,1,0},
{0,1,1,2,0,0},
{0,2,0,1,2,0},
{0,0,0,0,0,0}
};*/

int mejoresMallas[3][n+2][m+2];
double mejoresPuntajes[3];
int contSinCambios = 0;
int contCambios = 0;
double puntajeAnterior;
double puntajeNuevo;
double puntajesMalla[n][m];
double puntajesVecindades[2][5];
int aux;
double aux2;

double propL[numClases+1];
double propG[numClases+1];


#include "aprendizajePorRefuerzo_2.h"


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




for(int iw=espaciosMalla; iw>=ceil(espaciosMalla/2.0)+1; iw--){
for(int jw=0; jw<=iw; jw++){

Ns[0] = iw-jw;
Ns[1] = jw;

contSinCambios = 0;

srand(time(NULL));
N = accumulate(Ns, Ns + numClases, 0);

for(int i=1; i<=numClases; i++) propG[i] = Ns[i-1]/(espaciosMalla*1.0);
propG[0] = (espaciosMalla-N)/(espaciosMalla*1.0);

if(N > espaciosMalla){ cout << "Error, más objetos que espacios disponibles." << endl; return 0; }
if(N < ceil(espaciosMalla/2.0)+1){ cout << "Caso trivial" << endl; return 0; }
if(*max_element(Ns, Ns + numClases) > espaciosMalla - floor(n/2.0)*floor(m/2.0)){
	cout << "El arreglo contiene elementos imposibles de tomar." << endl;
	continue;
}
	

// Inicializar malla.
for(auto &row:malla) fill(row, row+m+2, 0);
inicializarMallaAleatoriamente(malla);
imprimirVectorMatriz(malla, n, m);

puntajeMalla = puntajeMallaInicial();
cout << "Puntaje = " << puntajeMalla << endl << endl;

//return 0;

while(contSinCambios <= pow(espaciosMalla,2)){

for(int i1=1; i1<=n; i1++){

	for(int j1=1; j1<=m; j1++){
	
		for(int i2=1; i2<=n; i2++){

			for(int j2=1; j2<=m; j2++){
			
				if(i1!=i2 or j1!=j2){
					
					puntajeAnterior = puntajesMalla[i1-1][j1-1];
					if(i1>1) puntajeAnterior += puntajesMalla[i1-2][j1-1];
					if(j1<m) puntajeAnterior += puntajesMalla[i1-1][j1];
					if(i1<n) puntajeAnterior += puntajesMalla[i1][j1-1];
					if(j1>1) puntajeAnterior += puntajesMalla[i1-1][j1-2];

					if(!((i2==i1+1 or i2==i1-1) and j2==j1) and !((j2==j1+1 or j2==j1-1) and i2==i1)) puntajeAnterior += puntajesMalla[i2-1][j2-1];
					if((i2>1 and !(i1==i2-1 and abs(j2-j1)<2)) and !(j2==j1 and i2==i1+2)) puntajeAnterior += puntajesMalla[i2-2][j2-1];
					if((j2<m and !(j1==j2+1 and abs(i2-i1)<2)) and !(i2==i1 and j2==j1-2)) puntajeAnterior += puntajesMalla[i2-1][j2];
					if((i2<n and !(i1==i2+1 and abs(j2-j1)<2)) and !(j2==j1 and i2==i1-2)) puntajeAnterior += puntajesMalla[i2][j2-1];
					if((j2>1 and !(j1==j2-1 and abs(i2-i1)<2)) and !(i2==i1 and j2==j1+2)) puntajeAnterior += puntajesMalla[i2-1][j2-2];
				
					aux = malla[i1][j1];
					malla[i1][j1] = malla[i2][j2];
					malla[i2][j2] = aux;
					
					aux2 = puntajeElemento(i1, j1);
					puntajeNuevo = aux2;
					puntajesVecindades[0][0] = aux2;
					if(i1>1){ 
						aux2 = puntajeElemento(i1-1, j1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][1] = aux2;
					}
					if(j1<m){
						aux2 = puntajeElemento(i1, j1+1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][2] = aux2;
					}
					if(i1<n){
						aux2 = puntajeElemento(i1+1, j1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][3] = aux2;
					}
					if(j1>1){
						aux2 = puntajeElemento(i1, j1-1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][4] = aux2;
					}
				
					if(!((i2==i1+1 or i2==i1-1) and j2==j1) and !((j2==j1+1 or j2==j1-1) and i2==i1)){
						aux2 = puntajeElemento(i2, j2);
						puntajeNuevo += aux2;
						puntajesVecindades[1][0] = aux2;
					}
					if((i2>1 and !(i1==i2-1 and abs(j2-j1)<2)) and !(j2==j1 and i2==i1+2)){
						aux2 = puntajeElemento(i2-1, j2);
						puntajeNuevo += aux2;
						puntajesVecindades[1][1] = aux2;
					}
					if((j2<m and !(j1==j2+1 and abs(i2-i1)<2)) and !(i2==i1 and j2==j1-2)){
						aux2 = puntajeElemento(i2, j2+1);
						puntajeNuevo += aux2;
						puntajesVecindades[1][2] = aux2;
					}
					if((i2<n and !(i1==i2+1 and abs(j2-j1)<2)) and !(j2==j1 and i2==i1-2)){
						aux2 = puntajeElemento(i2+1, j2);
						puntajeNuevo += aux2;
						puntajesVecindades[1][3] = aux2;
					}
					if((j2>1 and !(j1==j2-1 and abs(i2-i1)<2)) and !(i2==i1 and j2==j1+2)){
						aux2 = puntajeElemento(i2, j2-1);
						puntajeNuevo += aux2;
						puntajesVecindades[1][4] = aux2;
					}
				
					if(puntajeNuevo > puntajeAnterior){
					
						puntajesMalla[i1-1][j1-1] = puntajesVecindades[0][0];
						if(i1>1) puntajesMalla[i1-2][j1-1] = puntajesVecindades[0][1];
						if(j1<m) puntajesMalla[i1-1][j1] = puntajesVecindades[0][2];
						if(i1<n) puntajesMalla[i1][j1-1] = puntajesVecindades[0][3];
						if(j1>1) puntajesMalla[i1-1][j1-2] = puntajesVecindades[0][4];

						if(!((i2==i1+1 or i2==i1-1) and j2==j1) and !((j2==j1+1 or j2==j1-1) and i2==i1)) puntajesMalla[i2-1][j2-1] = puntajesVecindades[1][0];
						if((i2>1 and !(i1==i2-1 and abs(j2-j1)<2)) and !(j2==j1 and i2==i1+2)) puntajesMalla[i2-2][j2-1] = puntajesVecindades[1][1];
						if((j2<m and !(j1==j2+1 and abs(i2-i1)<2)) and !(i2==i1 and j2==j1-2)) puntajesMalla[i2-1][j2] = puntajesVecindades[1][2];
						if((i2<n and !(i1==i2+1 and abs(j2-j1)<2)) and !(j2==j1 and i2==i1-2)) puntajesMalla[i2][j2-1] = puntajesVecindades[1][3];
						if((j2>1 and !(j1==j2-1 and abs(i2-i1)<2)) and !(i2==i1 and j2==j1+2)) puntajesMalla[i2-1][j2-2] = puntajesVecindades[1][4];
						
						puntajeMalla += (puntajeNuevo - puntajeAnterior);
						
						contSinCambios = 0;
						contCambios++;
					}
					else{ malla[i2][j2] = malla[i1][j1]; malla[i1][j1] = aux; contSinCambios++;}
				}
			}
		}
	}
}
}

file << "mallaV([\n";

for(int i=0; i<=n+1; i++){
	file << "[";
	for(int j=0; j<=m+1; j++) file << malla[i][j] << (j!=m+1 ? "," : "]");
	file << (i!=n+1 ? ",\n" : "]).\n");
}

cout << Ns[0] << "," << Ns[1] << endl;
imprimirVectorMatriz(malla, n, m);
cout << "Puntaje = " << puntajeMalla << endl;
cout << "Intercambios = " << contCambios << endl;

}}

file.close();

return 0;

}
