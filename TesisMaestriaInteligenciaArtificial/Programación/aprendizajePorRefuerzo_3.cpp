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
/*const*/ int Ns[numClases] = {96,25};


//#############################################################################################################################


ofstream file("mallaRefuerzo.pl");

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
double puntajesVecindades[2][9];
int aux;
double aux2;


double t1;
double t2;

double t_rechazados_min = 100000000;
double t_rechazados_max = 0;

double t_aceptados_min = 100000000;
double t_aceptados_max = 0;

double sumaTaceptados = 0;
double sumaTrechazados = 0;

int cont_aceptados = 0;
int cont_rechazados = 0;


#include "aprendizajePorRefuerzo_3.h"


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
imprimirVectorMatriz(malla, n, m);

puntajeMalla = puntajeMallaInicial();
cout << "Puntaje = " << puntajeMalla << endl << endl;


while(contSinCambios <= pow(espaciosMalla,2)){

for(int i1=1; i1<=n; i1++){

	for(int j1=1; j1<=m; j1++){

		for(int i2=1; i2<=n; i2++){

			for(int j2=1; j2<=m; j2++){
			
				if(i1!=i2 or j1!=j2){
				
					// Cálculo puntaje actual.
					
					t1 = 1.0*clock()/CLOCKS_PER_SEC;
					
					puntajeAnterior = puntajesMalla[i1-1][j1-1];
					if(i1>1) puntajeAnterior += puntajesMalla[i1-2][j1-1];
					if(j1<m) puntajeAnterior += puntajesMalla[i1-1][j1];
					if(i1<n) puntajeAnterior += puntajesMalla[i1][j1-1];
					if(j1>1) puntajeAnterior += puntajesMalla[i1-1][j1-2];
					if(i1>1 and j1>1) puntajeAnterior += puntajesMalla[i1-2][j1-2];
					if(i1>1 and j1<m) puntajeAnterior += puntajesMalla[i1-2][j1];
					if(i1<n and j1<m) puntajeAnterior += puntajesMalla[i1][j1];
					if(i1<n and j1>1) puntajeAnterior += puntajesMalla[i1][j1-2];

					if(!(abs(i2-i1)<2 and abs(j2-j1)<2)) puntajeAnterior += puntajesMalla[i2-1][j2-1];
					if(i2>1 and !(abs(i2-(i1+1))<2 and abs(j2-j1)<2)) puntajeAnterior += puntajesMalla[i2-2][j2-1];
					if(j2<m and !(abs(i2-i1)<2 and abs(j2-(j1-1))<2)) puntajeAnterior += puntajesMalla[i2-1][j2];
					if(i2<n and !(abs(i2-(i1-1))<2 and abs(j2-j1)<2)) puntajeAnterior += puntajesMalla[i2][j2-1];
					if(j2>1 and !(abs(i2-i1)<2 and abs(j2-(j1+1))<2)) puntajeAnterior += puntajesMalla[i2-1][j2-2];
					if((i2>1 and j2>1) and !(abs(i2-(i1+1))<2 and abs(j2-(j1+1))<2)) puntajeAnterior += puntajesMalla[i2-2][j2-2];
					if((i2>1 and j2<m) and !(abs(i2-(i1+1))<2 and abs(j2-(j1-1))<2)) puntajeAnterior += puntajesMalla[i2-2][j2];
					if((i2<n and j2<m) and !(abs(i2-(i1-1))<2 and abs(j2-(j1-1))<2)) puntajeAnterior += puntajesMalla[i2][j2];
					if((i2<n and j2>1) and !(abs(i2-(i1-1))<2 and abs(j2-(j1+1))<2)) puntajeAnterior += puntajesMalla[i2][j2-2];
				
					// Intercambio supuesto.
				
					aux = malla[i1][j1];
					malla[i1][j1] = malla[i2][j2];
					malla[i2][j2] = aux;
					
					// Cálculo puntaje intercambio.
					
					aux2 = puntajeElemento(i1, j1);
					puntajeNuevo = aux2;
					puntajesVecindades[0][0] = aux2;

					if(i1>1){ 
						aux2 = puntajeElemento(i1-1, j1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][1] = aux2;}
					if(j1<m){
						aux2 = puntajeElemento(i1, j1+1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][2] = aux2;}
					if(i1<n){
						aux2 = puntajeElemento(i1+1, j1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][3] = aux2;}
					if(j1>1){
						aux2 = puntajeElemento(i1, j1-1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][4] = aux2;}
					if(i1>1 and j1>1){
						aux2 = puntajeElemento(i1-1, j1-1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][5] = aux2;}
					if(i1>1 and j1<m){
						aux2 = puntajeElemento(i1-1, j1+1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][6] = aux2;}
					if(i1<n and j1<m){
						aux2 = puntajeElemento(i1+1, j1+1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][7] = aux2;}
					if(i1<n and j1>1){
						aux2 = puntajeElemento(i1+1, j1-1);
						puntajeNuevo += aux2;
						puntajesVecindades[0][8] = aux2;}
				
					if(!(abs(i2-i1)<2 and abs(j2-j1)<2)){
						aux2 = puntajeElemento(i2, j2);
						puntajeNuevo += aux2;
						puntajesVecindades[1][0] = aux2;}
					if(i2>1 and !(abs(i2-(i1+1))<2 and abs(j2-j1)<2)){
						aux2 = puntajeElemento(i2-1, j2);
						puntajeNuevo += aux2;
						puntajesVecindades[1][1] = aux2;}
					if(j2<m and !(abs(i2-i1)<2 and abs(j2-(j1-1))<2)){
						aux2 = puntajeElemento(i2, j2+1);
						puntajeNuevo += aux2;
						puntajesVecindades[1][2] = aux2;}
					if(i2<n and !(abs(i2-(i1-1))<2 and abs(j2-j1)<2)){
						aux2 = puntajeElemento(i2+1, j2);
						puntajeNuevo += aux2;
						puntajesVecindades[1][3] = aux2;}
					if(j2>1 and !(abs(i2-i1)<2 and abs(j2-(j1+1))<2)){
						aux2 = puntajeElemento(i2, j2-1);
						puntajeNuevo += aux2;
						puntajesVecindades[1][4] = aux2;}
					if((i2>1 and j2>1) and !(abs(i2-(i1+1))<2 and abs(j2-(j1+1))<2)){
						aux2 = puntajeElemento(i2-1, j2-1);
						puntajeNuevo += aux2;
						puntajesVecindades[1][5] = aux2;}
					if((i2>1 and j2<m) and !(abs(i2-(i1+1))<2 and abs(j2-(j1-1))<2)){
						aux2 = puntajeElemento(i2-1, j2+1);
						puntajeNuevo += aux2;
						puntajesVecindades[1][6] = aux2;}
					if((i2<n and j2<m) and !(abs(i2-(i1-1))<2 and abs(j2-(j1-1))<2)){
						aux2 = puntajeElemento(i2+1, j2+1);
						puntajeNuevo += aux2;
						puntajesVecindades[1][7] = aux2;}
					if((i2<n and j2>1) and !(abs(i2-(i1-1))<2 and abs(j2-(j1+1))<2)){
						aux2 = puntajeElemento(i2+1, j2-1);
						puntajeNuevo += aux2;
						puntajesVecindades[1][8] = aux2;}
				
					if(puntajeNuevo > puntajeAnterior){
					
						puntajesMalla[i1-1][j1-1] = puntajesVecindades[0][0];
						if(i1>1) puntajesMalla[i1-2][j1-1] = puntajesVecindades[0][1];
						if(j1<m) puntajesMalla[i1-1][j1] = puntajesVecindades[0][2];
						if(i1<n) puntajesMalla[i1][j1-1] = puntajesVecindades[0][3];
						if(j1>1) puntajesMalla[i1-1][j1-2] = puntajesVecindades[0][4];
						if(i1>1 and j1>1) puntajesMalla[i1-2][j1-2] = puntajesVecindades[0][5];
						if(i1>1 and j1<m) puntajesMalla[i1-2][j1] = puntajesVecindades[0][6];
						if(i1<n and j1<m) puntajesMalla[i1][j1] = puntajesVecindades[0][7];
						if(i1<n and j1>1) puntajesMalla[i1][j1-2] = puntajesVecindades[0][8];

						if(!(abs(i2-i1)<2 and abs(j2-j1)<2)) puntajesMalla[i2-1][j2-1] = puntajesVecindades[1][0];
						if(i2>1 and !(abs(i2-(i1+1))<2 and abs(j2-j1)<2)) puntajesMalla[i2-2][j2-1] = puntajesVecindades[1][1];
						if(j2<m and !(abs(i2-i1)<2 and abs(j2-(j1-1))<2)) puntajesMalla[i2-1][j2] = puntajesVecindades[1][2];
						if(i2<n and !(abs(i2-(i1-1))<2 and abs(j2-j1)<2)) puntajesMalla[i2][j2-1] = puntajesVecindades[1][3];
						if(j2>1 and !(abs(i2-i1)<2 and abs(j2-(j1+1))<2)) puntajesMalla[i2-1][j2-2] = puntajesVecindades[1][4];
						if((i2>1 and j2>1) and !(abs(i2-(i1+1))<2 and abs(j2-(j1+1))<2)) puntajesMalla[i2-2][j2-2] = puntajesVecindades[1][5];
						if((i2>1 and j2<m) and !(abs(i2-(i1+1))<2 and abs(j2-(j1-1))<2)) puntajesMalla[i2-2][j2] = puntajesVecindades[1][6];
						if((i2<n and j2<m) and !(abs(i2-(i1-1))<2 and abs(j2-(j1-1))<2)) puntajesMalla[i2][j2] = puntajesVecindades[1][7];
						if((i2<n and j2>1) and !(abs(i2-(i1-1))<2 and abs(j2-(j1+1))<2)) puntajesMalla[i2][j2-2] = puntajesVecindades[1][8];
						
						puntajeMalla += (puntajeNuevo - puntajeAnterior);
						
						contSinCambios=0;
						contCambios++;
					}
					else{ malla[i2][j2] = malla[i1][j1]; malla[i1][j1] = aux; contSinCambios++;}
					
					cont_aceptados++;
					t2 = 1.0*clock()/CLOCKS_PER_SEC;
					if((t2-t1)>t_aceptados_max) t_aceptados_max = t2-t1;
					if((t2-t1)<t_aceptados_min) t_aceptados_min = t2-t1;
					sumaTaceptados+=t2-t1;
					//cout.precision(16);
					//cout << M_PI << endl;
					//cout << 1.0*sumaTaceptados << endl;
				}
			}
		}
	}
}
}

file << "mallaR([\n";

for(int i=0; i<=n+1; i++){
	file << "[";
	for(int j=0; j<=m+1; j++) file << malla[i][j] << (j!=m+1 ? "," : "]");
	file << (i!=n+1 ? ",\n" : "]).\n");
}

cout << Ns[0] << "," << Ns[1] << endl;
imprimirVectorMatriz(malla, n, m);
cout << "Puntaje = " << puntajeMalla << endl;
cout << "Intercambios = " << contCambios << endl;

file.close();

cout << n << 'x' << m << ": " << t_aceptados_min << ", " << sumaTaceptados/cont_aceptados << ", " << t_aceptados_max << ", " << cont_aceptados << endl;

//cout << "Min t aceptado = " << t_aceptados_min << endl;
//cout << "Promedio t aceptado = " << sumaTaceptados/cont_aceptados << endl;
//cout << "Max t aceptado = " << t_aceptados_max << endl << endl;

return 0;

}
