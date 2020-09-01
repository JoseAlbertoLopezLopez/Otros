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
const array<int,numClases> Ns {{4,12}};


//#############################################################################################################################


ofstream file("mallaVentana.pl");

int N;
int Naux;
const int espaciosMalla = n*m;
int malla[n][m];
array<array<int,2>,2> ventana;
array<array<int,2>,2> matrizAux;
array<array<int,2>,2> matrizAux2;
array<int,numClases> NsAux = Ns;
array<array<int, 2>, numClases+1> mayoresMenores;
array<int, numClases+1> indicesMM;
int minoria;
int minoriasTomadas;
int indice_preferencia;

int potencialesImposibles = (n-1)*(m-1);
array<array<int, m-1>, n-1> potencialesCuadrosImposibles; 
array<array<int, m-1>, n-1> potencialesCuadrosImposiblesAux; 
vector<array<int, 3>> listaPotencialesImposibles; 
int indiceImposibles;

array<int,numClases> tomarParaVentana;


#include "algoritmoVentana_2.h"


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


void correrVentana(int r, int c){

	ventana[0][0] = malla[r-1][c-1];
	ventana[0][1] = malla[r-1][c];
	ventana[1][0] = malla[r][c-1];
	ventana[1][1] = malla[r][c];
}


bool llenarMalla(int r, int c, array<array<int,2>,2> mallaBase){

	while(true){
	
	//Caso llenar 1 vacío (casi siempre).
	if(r>1 and c>1){

		//INNECESARIO TERCER ARGUMENTO?
		if(llenarAux3(r,c,mallaBase)) return true;
		//imprimirMatriz(mallaBase);
		reflejar(mallaBase);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		//imprimirMatriz(matrizAux);
		if(llenarAux4(r,c,mallaBase)) return true;
		
		return false;
	}

	//Casos llenar 2 vacíos.
	if(c>1 and r==1){

		if(llenarAux1(r,c,mallaBase)) return true;
		reflejar(mallaBase);
		if(llenarAux2(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		if(llenarAux2(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		if(llenarAux2(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		if(llenarAux2(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		if(llenarAux2(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		if(llenarAux2(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		if(llenarAux2(r,c,mallaBase)) return true;
		
		return false;
	}
	
	if(r>1 and c==1){

		if(llenarAux5(r,c,mallaBase)) return true;
		reflejar(mallaBase);
		if(llenarAux6(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		if(llenarAux6(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		if(llenarAux6(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		if(llenarAux6(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		if(llenarAux6(r,c,mallaBase)) return true;
		transpuesta(matrizAux);
		if(llenarAux6(r,c,mallaBase)) return true;
		reflejar(matrizAux);
		if(llenarAux6(r,c,mallaBase)) return true;
		
		return false;
	}
	
	//Caso llenar 4 vacíos (al inicio).
	if(r==1 and c==1){
	
		malla[0][0] = mallaBase[0][0];
		malla[0][1] = mallaBase[0][1];
		malla[1][0] = mallaBase[1][0];
		malla[1][1] = mallaBase[1][1];
		return true;
	}
	
	}
}


array<array<int,2>,2>& llenarVentana(int r, int c){
	
	//Contar espacios a llenar.
	int espacios_a_llenar = 0; 
	for(auto &row:ventana) espacios_a_llenar += count(row.begin(), row.end(), -1);

	fill(tomarParaVentana.begin(), tomarParaVentana.end(), 0);
	array<int,numClases> repetidos;
	fill(repetidos.begin(), repetidos.end(), 0);
	
	int indice = 0;
	minoria = 0;
	minoriasTomadas = 0;

	//Contar elementos en la ventana.
	for(int i=0; i<=1; i++){
	
		for(int j=0; j<=1; j++){
		
			for(int k=1; k<=mayoresMenores.size()-1; k++) if(ventana[i][j] == mayoresMenores[k][0]) minoriasTomadas++;

			if(ventana[i][j] > 0){
				tomarParaVentana[ventana[i][j]-1]++;
				repetidos[ventana[i][j]-1]++;
			}
		}
	}
	
	//LLENADO DE VENTANA BASADO EN PROPORCIONES.
	/*int objetosTomados = 0;
	//Determinar cantidad de elementos para los espacios faltantes y añadirlos a la lista para tomar.
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
	for(int i=0; i<=NsAux.size()-1; i++){ mayoresMenores[i+1][0] = i+1; mayoresMenores[i+1][1] = NsAux[i]; }
	mayoresMenores[0][0] = 0;
	mayoresMenores[0][1] = Naux - accumulate(NsAux.begin(), NsAux.end(), 0);
	
	sort(mayoresMenores.begin(), mayoresMenores.end(), ordenamiento);
	llenar_indicesMM();
	
	for(int i=1; i<=mayoresMenores.size()-1; i++) minoria += mayoresMenores[i][1];
	
	while(espacios_a_llenar>0){
		
		cout << mayoresMenores[0][1] << " " << mayoresMenores[1][1] << " " << mayoresMenores[2][1] << endl;
		cout << mayoresMenores[0][0] << " " << mayoresMenores[1][0] << " " << mayoresMenores[2][0] << endl << endl;
		cout << "Minoria = " << minoria << endl;
		
		// Tomar un elemento de la minoria y actualizar variables.
		if(!minoriasTomadas){
		
			indice_preferencia = indicePreferencia(r, c);
		
			if(indice_preferencia == -1) indice_preferencia = 1;
		
			if(mayoresMenores[indice_preferencia][0]-1>=0){
				tomarParaVentana[mayoresMenores[indice_preferencia][0]-1]++; 
				NsAux[mayoresMenores[indice_preferencia][0]-1]--;
			}
			mayoresMenores[indice_preferencia][1]--;
			minoria--;
			espacios_a_llenar--;
			minoriasTomadas++;
			
			sort(mayoresMenores.begin(), mayoresMenores.end(), ordenamiento);
			llenar_indicesMM();
			continue; 
		}

		eliminarImposiblesPotenciales2(r, c, potencialesCuadrosImposibles);
		imprimirMatriz2(potencialesCuadrosImposibles);
		cout << minoriaNecesaria() << endl;
		
		//Preguntar si se puede volver a tomar otro elemento de la minoria.
		if(minoriasTomadas<2 and (minoria>0 and minoria-1 >= minoriaNecesaria())){
		
			indice_preferencia = indicePreferencia(r, c);
		
			if(indice_preferencia == -1) indice_preferencia = 1;
		
			if(mayoresMenores[indice_preferencia][0]-1>=0){
				tomarParaVentana[mayoresMenores[indice_preferencia][0]-1]++; 
				NsAux[mayoresMenores[indice_preferencia][0]-1]--;
			}
			mayoresMenores[indice_preferencia][1]--;
			minoria--;
			espacios_a_llenar--; 
			minoriasTomadas++;
			
			sort(mayoresMenores.begin(), mayoresMenores.end(), ordenamiento);
			llenar_indicesMM();
			continue;
		}
		
		// Tomar elementos restantes de la mayoría.	
		if(minoriasTomadas){
		
			if(mayoresMenores[0][0]-1>=0){
				tomarParaVentana[mayoresMenores[0][0]-1]++; 
				NsAux[mayoresMenores[0][0]-1]--;
			}
			mayoresMenores[0][1]--;
			espacios_a_llenar--; 
			sort(mayoresMenores.begin(), mayoresMenores.end(), ordenamiento);
			llenar_indicesMM();
			
			//Si estoy en los bordes o esquinas y la ventana llena contiene un 1 y 2 2's y aún quedan 1's y no hay que 
			//preocuparse por los imposibles potenciales si quito un uno; cambiar un quitar un 2 y poner un 1.
			if((espacios_a_llenar==0 and (tomarParaVentana[0]==1 and tomarParaVentana[1]==2)) and (mayoresMenores[indicesMM[1]][1]>0 and minoria-1 >= minoriaNecesaria())){
				
				tomarParaVentana[0]++; tomarParaVentana[1]--;
				NsAux[0]--; NsAux[1]++;
				mayoresMenores[indicesMM[1]][1]--; mayoresMenores[indicesMM[2]][1]++;
				sort(mayoresMenores.begin(), mayoresMenores.end(), ordenamiento);
				llenar_indicesMM();
			}
		}
	}
	
	Naux -= (r>1 ? (c>1 ? 1 : 2) : (c>1 ? 2 : 4));
	
	if( (r>1 and c>1) and (r<n-1 and c<m-1) ){
	
		while( !llenarMalla(r, c, dicMallasBaseCentro.find(tomarParaVentana)->second[indice]) ) indice++;
	}
	
	if( ((r==1 and (c>1 and c<m-1)) or (r==n-1 and (c>1 and c<m-1))) or 
	((c==1 and (r>1 and r<n-1)) or (c==m-1 and (r>1 and r<n-1))) ){ 
	
		while( !llenarMalla(r, c, dicMallasBaseBordes.find(tomarParaVentana)->second[indice]) ) indice++;
	}
	
	if( ((r==1 and c==1) or (r==1 and c==m-1)) or ((r==n-1 and c==1) or (r==n-1 and c==m-1)) ){
	
		if(mayoresMenores[0][0]!=2 or (tomarParaVentana[0] != 2 or tomarParaVentana[1] != 2)){
			while( !llenarMalla(r, c, dicMallasBaseEsquinas.find(tomarParaVentana)->second[indice]) ) indice++;
		}
		else{
			matrizAux2 = dicMallasBaseEsquinas.find(tomarParaVentana)->second[indice];

			transpuesta2(matrizAux2);
			reflejar2(matrizAux2);
			transpuesta2(matrizAux2);
			
			imprimirMatriz(matrizAux2);
			
			llenarMalla(r, c, matrizAux2);
		}
	}
}
					   



int main(){




N = accumulate(Ns.begin(), Ns.end(), 0);

if(N > espaciosMalla){ cout << "Error, más objetos que espacios disponibles." << endl; return 0; }
if(N < ceil(espaciosMalla/2.0)+1){ cout << "Caso trivial" << endl; return 0; }
if(*max_element(Ns.begin(), Ns.end()) > espaciosMalla - floor(n/2.0)*floor(m/2.0)){
 cout << "El arreglo contiene elementos imposibles de tomar." << endl;}


//Inicializar N.
N = accumulate(Ns.begin(), Ns.end(), 0);
Naux = espaciosMalla;

//Inicializar malla (todos los valores a -1).
for(auto &row:malla) fill(row, row+m, -1);

//Inicializar mtriz de cuadros imposibles (todos los valores a 1).
for(auto &row:potencialesCuadrosImposibles) fill(row.begin(), row.end(), 1);
potencialesCuadrosImposiblesAux = potencialesCuadrosImposibles;


//Correr ventana. Los indices apuntan a la esquina inferior derecha de esta.
for(int i=1; i<=n-1; i++){

	for(int j=1; j<=m-1; j++){
		
		correrVentana(i, j);
		llenarVentana(i, j);
		
		for(auto &elem:NsAux) cout << elem << " "; cout << endl;
		imprimirMalla();
	}
}

imprimirMalla();

file << "mallaV([\n[";

for(int j=0; j<=m+1; j++) file << (j!=m+1 ? "0," : "0],\n");

for(int i=0; i<=n-1; i++){
	file << "[0,";
	for(int j=0; j<=m-1; j++) file << malla[i][j] << (j!=m-1 ? "," : ",0],\n");
}

file << "[";
for(int j=0; j<=m+1; j++) file << (j!=m+1 ? "0," : "0]]).\n");

file.close();


return 0;
}




















