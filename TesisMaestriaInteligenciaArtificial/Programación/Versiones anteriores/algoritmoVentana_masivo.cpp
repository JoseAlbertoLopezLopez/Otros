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
/*const*/ array<int,numClases> Ns {{0,6}};


//#############################################################################################################################


ofstream file("mallaVentana.pl");

int N;
int Naux;
const int espaciosMalla = n*m;
int malla[n][m];
array<array<int,2>,2> ventana;
array<array<int,2>,2> matrizAux;
array<int,numClases> NsAux = Ns;

bool imposiblesQ = false;
bool noQuedanObjetosQ = false;
const int puntosClaveR = (int) floor(n/2.0);
const int puntosClaveC = (int) floor(m/2.0);
int cuadrosImposibles[puntosClaveR][puntosClaveC]; 

map<array<int,3>, array<array<int,2>,2>> dicMallasBase;

#include "algoritmoVentana.h"

array<array<int, 3>, 20> claves = {{
									{3,1,0},
									{2,2,0},
									{2,2,1},
									{1,3,0},
									
									{3,0,0},
									{2,1,0},
									{2,1,1},
									{1,2,0},
									{1,2,1},
									{0,3,0},
									
									{2,0,0},
									{2,0,1},
									{1,1,0},
									{1,1,1},
									{0,2,0},
									{0,2,1},
									
									{1,0,0},
									{0,1,0},
									
									{4,0,0},
									{0,4,0},
									}};

array<array<array<int, 2>, 2>,20> mallasBase = {{

								 {{{2,1},
								   {1,1}}},

					   			 {{{2,1},
								   {1,2}}},
								   
								 {{{2,1},
								   {2,1}}},

					   			 {{{2,2},
								   {2,1}}},


					   			 {{{1,1},
								   {1,0}}},
					   
					   			 {{{2,1},
								   {1,0}}},	
								   
								 {{{1,2},
								   {1,0}}},			   
					   
					   			 {{{2,1},
								   {2,0}}},
								   
								 {{{1,2},
								   {2,0}}},
					   
					   			 {{{2,2},
								   {2,0}}},
					   
					   
					   			 {{{1,0},
								   {0,1}}},
								   
								 {{{1,0},
								   {1,0}}},
					   
					   			 {{{2,0},
								   {0,1}}},
								   
								 {{{2,0},
								   {1,0}}},
					   
					   			 {{{2,0},
								   {0,2}}},
								   
								 {{{2,0},
								   {2,0}}},
								   
								 {{{1,0},
								   {0,0}}},
								   
								 {{{2,0},
								   {0,0}}},
								  
					   			 {{{1,1},
								   {1,1}}},
								  
					   			 {{{2,2},
								   {2,2}}}}};

void correrVentana(int r, int c){

	ventana[0][0] = malla[r-1][c-1];
	ventana[0][1] = malla[r-1][c];
	ventana[1][0] = malla[r][c-1];
	ventana[1][1] = malla[r][c];
}


array<int,numClases+1> tomarParaVentana;
array<array<int,2>,2>& llenarVentana(int r, int c){
	
	//Contar espacios a llenar.
	int espacios_a_llenar = 0; 
	for(auto &row:ventana) espacios_a_llenar += count(row.begin(), row.end(), -1);

	fill(tomarParaVentana.begin(), tomarParaVentana.end(), 0);
	array<int,numClases> repetidos;
	fill(repetidos.begin(), repetidos.end(), 0);
	
	int objetosTomados = 0;
	
	int indiceMayor;
	int vaciosPorAsignar;

	//Contar elementos en la ventana.
	for(int i=0; i<=1; i++){
	
		for(int j=0; j<=1; j++){

			if(ventana[i][j] > 0){
				tomarParaVentana[ventana[i][j]-1]++;
				repetidos[ventana[i][j]-1]++;
			}
		}
	}
	
	//LLENADO DE VENTANA BASADO EN PROPORCIONES.
	/*//Determinar cantidad de elementos para los espacios faltantes y añadirlos a la lista para tomar.
	for(int i=0; i<=numClases-1; i++){
		tomarParaVentana[i] += round(espacios_a_llenar*NsAux[i]/(1.0*Naux));
		objetosTomados += round(espacios_a_llenar*NsAux[i]/(1.0*Naux));
	}
	
	while(objetosTomados>espacios_a_llenar) {tomarParaVentana[rand()%numClases]--; objetosTomados--;}
		
	//Actualizar elementos restantes.
	for(int i=0; i<=numClases-1; i++){
		NsAux[i] -= tomarParaVentana[i]-repetidos[i];
	}*/
	
	//LLENADO DE VENTANA BASADO EN MAYORIAS.
	vaciosPorAsignar = Naux - accumulate(NsAux.begin(), NsAux.end(), 0);
	
	while(espacios_a_llenar>0){
	
		if(numClases>1){
			for(int i=0; i<=numClases-2; i++){ 

				if(NsAux[i]<NsAux[i+1]) indiceMayor=i+1;
				else indiceMayor=i;
			}
		
			if(NsAux[indiceMayor]>=vaciosPorAsignar){ tomarParaVentana[indiceMayor]++; NsAux[indiceMayor]--; }
			else{ vaciosPorAsignar--; }
		}
		else{
			if(NsAux[0]>=vaciosPorAsignar){ tomarParaVentana[0]++; NsAux[0]--; }
			else{ vaciosPorAsignar--; }
		}
		
		espacios_a_llenar--; 
	}
	
	
	//Verificar si la ventana es imposible.
	for(int i=0; i<=numClases-1; i++) if(tomarParaVentana[i]==4) cuadrosImposibles[(int) floor((r-1)/2.0)][(int) floor((c-1)/2.0)]++;
	
	Naux -= (r>1 ? (c>1 ? 1 : 2) : (c>1 ? 2 : 4));
	
	if(Naux <= 0) noQuedanObjetosQ = true;
	
	return dicMallasBase.find(tomarParaVentana)->second;
}


void llenarMalla(int r, int c, array<array<int,2>,2> mallaBase){

	while(true){
	
	//Caso llenar 1 vacío (casi siempre).
	if(r>1 and c>1){

		//INNECESARIO TERCER ARGUMENTO?
		if(llenarAux3(r,c,mallaBase)) break;
		//imprimirMatriz(mallaBase);
		reflejar(mallaBase);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) break;
		reflejar(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) break;
		reflejar(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) break;
		reflejar(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) break;
		
		tomarParaVentana[numClases]++;
		mallaBase = dicMallasBase.find(tomarParaVentana)->second;
	}

	//Casos llenar 2 vacíos.
	if(c>1 and r==1){

		if(llenarAux1(r,c,mallaBase)) break;
		reflejar(mallaBase);
		if(llenarAux2(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		if(llenarAux2(r,c,mallaBase)) break;
		reflejar(matrizAux);
		if(llenarAux2(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		if(llenarAux2(r,c,mallaBase)) break;
		reflejar(matrizAux);
		if(llenarAux2(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		if(llenarAux2(r,c,mallaBase)) break;
		reflejar(matrizAux);
		if(llenarAux2(r,c,mallaBase)) break;
		
		tomarParaVentana[numClases]++;
		mallaBase = dicMallasBase.find(tomarParaVentana)->second;
	}
	
	if(r>1 and c==1){

		if(llenarAux5(r,c,mallaBase)) break;
		reflejar(mallaBase);
		if(llenarAux6(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		if(llenarAux6(r,c,mallaBase)) break;
		reflejar(matrizAux);
		if(llenarAux6(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		if(llenarAux6(r,c,mallaBase)) break;
		reflejar(matrizAux);
		if(llenarAux6(r,c,mallaBase)) break;
		transpuesta(matrizAux);
		if(llenarAux6(r,c,mallaBase)) break;
		reflejar(matrizAux);
		if(llenarAux2(r,c,mallaBase)) break;
		
		tomarParaVentana[numClases]++;
		mallaBase = dicMallasBase.find(tomarParaVentana)->second;
	}
	
	//Caso llenar 4 vacíos (al inicio).
	if(r==1 and c==1){
	
		malla[0][0] = mallaBase[0][0];
		malla[0][1] = mallaBase[0][1];
		malla[1][0] = mallaBase[1][0];
		malla[1][1] = mallaBase[1][1];
		break;
	}
	
	}
}
					   



int main(){




// Inicializar diccionario claves->mallas atómicas.
for(int i=0; i<=claves.size()-1; i++){

	dicMallasBase.insert(pair<array<int,3>, array<array<int,2>,2>>(claves[i], mallasBase[i]));
}

for(int iw=16; iw>=9; iw--){

	for(int jw=0; jw<=iw; jw++){
	
Ns[0] = iw-jw;
Ns[1] = jw;

NsAux = Ns;

imposiblesQ = false;
noQuedanObjetosQ = false;

N = accumulate(Ns.begin(), Ns.end(), 0);

if(N > espaciosMalla){ cout << "Error, más objetos que espacios disponibles." << endl; return 0; }
if(N < ceil(espaciosMalla/2.0)+1){ cout << "Caso trivial" << endl; return 0; }
if(*max_element(Ns.begin(), Ns.end()) > espaciosMalla - floor(n/2.0)*floor(m/2.0)){
 cout << "El arreglo contiene elementos imposibles de tomar." << endl; continue;}


//Inicializar N.
N = accumulate(Ns.begin(), Ns.end(), 0);
Naux = espaciosMalla;

//Inicializar malla (todos los valores a -1).
for(auto &row:malla) fill(row, row+m, -1);

// Inicializar matriz de cuadros imposibles a 0's.
for(auto &row:cuadrosImposibles) fill(row, row + (int) floor(m/2.0), 0);

//Correr ventana. Los indices apuntan a la esquina inferior izquierda de esta.
for(int i=1; i<=n-1; i++){

	for(int j=1; j<=m-1; j++){
		
		correrVentana(i, j);
		llenarMalla(i,j,llenarVentana(i,j));
		
		//for(auto &elem:NsAux) cout << elem << " "; cout << endl;
		//imprimirMalla();
		
		if(noQuedanObjetosQ){
			for(auto &row:malla) replace(row, row + m, -1, 0);
			break;
		}
	}
	
	if(noQuedanObjetosQ) break;
}

//imprimirMalla();

//for(auto &row:cuadrosImposibles) {for(auto &elem:row) cout << elem << " "; cout << endl;}
//cout << endl;

//Corregir imposibles.
corregirImposibles();

cout << Ns[0] << "," << Ns[1] << endl;
imprimirMalla();

//for(auto &row:cuadrosImposibles) {for(auto &elem:row) cout << elem << " "; cout << endl;} cout << endl;


file << "mallaV([\n[";

for(int j=0; j<=m+1; j++) file << (j!=m+1 ? "0," : "0],\n");

for(int i=0; i<=n-1; i++){
	file << "[0,";
	for(int j=0; j<=m-1; j++) file << malla[i][j] << (j!=m-1 ? "," : ",0],\n");
}

file << "[";
for(int j=0; j<=m+1; j++) file << (j!=m+1 ? "0," : "0]]).\n");

}
}

file.close();


return 0;
}




















