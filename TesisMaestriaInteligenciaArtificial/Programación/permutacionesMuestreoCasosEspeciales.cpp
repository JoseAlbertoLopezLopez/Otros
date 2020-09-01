#include <iostream>
#include <fstream> 
#include <algorithm> 
#include <vector>   // next_permutation, sort
#include <time.h>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <stdio.h>	//printf
#include <stdlib.h>	//getenv()
#include <bits/stdc++.h>
#include <map>
#include <omp.h>
#include <boost/multiprecision/cpp_int.hpp>


using namespace boost::multiprecision;
using namespace std;

int maxMuestras = 2400000;
const int n=7;
const int m=7;


// ############################################################################################################################


#include "Especiales.h"

ofstream archivosSalida;
char nombreArchivo[100];

const int espaciosMalla = n*m;
int N0 = ceil(espaciosMalla/2.0) + 1;
int k;
int i2;

int malla[espaciosMalla];
int contUniv = 0;
vector<vector<int>> casos;
vector<vector<int>> casosAux;
vector<vector<int>> casosAux2;
vector<vector<int>> nombresCasos;
vector<vector<vector<int>>> nombresCasosPorCaso;
vector<vector<vector<int>>> cambiosPorCaso;

bool salir = false;
bool similarQ = false;
unsigned int cont=0;
unsigned int contAux=-1;
unsigned int filtradas=0;

double tp1;
double tp2;
double t1;
double t1_2;
double t2;

int matriz22[espaciosMalla];
int matriz33[espaciosMalla];
int matriz44[espaciosMalla];
int matriz55[espaciosMalla];
int matriz66[espaciosMalla];
int matriz77[espaciosMalla];
int matriz88[espaciosMalla];

vector<vector<int>> permutaciones;


void inicializarMallaAleatoriamente(int (&malla)[espaciosMalla], vector<int> &caso){

	int numObjetosEnMalla = 0;
	vector<vector<int>> casoAux;
	vector<int> desocupados(espaciosMalla);
	int N = accumulate(caso.begin(), caso.end()-1, 0);
	int cont = 0;
	
	for(int i=0; i<=espaciosMalla-1; i++) malla[i]=0;
	for(int i=0; i<=espaciosMalla-1; i++) desocupados[i] = i;
	for(int i=0; i<=caso.size()-2; i++) if(caso[i]>0) casoAux.push_back({i+1,caso[i]});

	int celda;
	int clase;
	
	while(numObjetosEnMalla<N){

		celda = rand()%desocupados.size();
		clase = rand()%casoAux.size();

		malla[desocupados[celda]] = casoAux[clase][0];
		
		casoAux[clase][1]--;
		if(casoAux[clase][1]==0) casoAux.erase(casoAux.begin()+clase);
		
		desocupados.erase(desocupados.begin()+celda);
		
		numObjetosEnMalla++;
	}
}


double factorial(int x){

	double factorial_=1;                         

	if(x<=1) return 1;
		
	for(int i=0; i<=(x-2); i++){
		factorial_*=(x-i);
	}

	return factorial_;
}

map<array<int, 2> , double> permutacionesPorCaso;
map<array<int, 2> , double> filtradasCaso;
int sumaN = 0;
void filtradasPorCaso(){

	int limUpNs;
	int limDownNs;
	int numCasos=0;
	int Ns[2];
	double maxComp=0;
	double casosAux;
	double sumaCasos = 0;
	double sumaCasosFiltrados = 0;
	
	vector<int> aux2(2);

	limUpNs = n*m - floor(n/2.0)*floor(m/2.0);
	limDownNs = ceil((n*m)/2.0)+1;

	for(int i=n*m; i>=limDownNs; i--){
		for(int j=(i>=limUpNs ? i-limUpNs : 0); j<=(i>=limUpNs ? limUpNs : i); j++){

			Ns[0] = i-j;
			Ns[1] = j;
			
			aux2 = {Ns[0],Ns[1]};
			if(find(especiales.begin(), especiales.end(), aux2) != especiales.end()) sumaN += Ns[0] + Ns[1]; 
		
			casosAux = factorial(n*m)/(factorial(Ns[0])*factorial(Ns[1])*factorial(n*m - i));
			permutacionesPorCaso[{i-j, j}] = casosAux;
			filtradasCaso[{i-j, j}] = (size_t) ceil(casosAux/6)*2;
			if(maxComp<casosAux) maxComp = casosAux;
			sumaCasos += casosAux;
			sumaCasosFiltrados += casosAux/6;
			numCasos++;
		
			cout << Ns[0] << "," << Ns[1] << ": " << "Perm. = " << casosAux << ", Filt. = " << casosAux/6 << endl;
		}
	}
	
	cout << endl << "Num. casos = " << numCasos << endl;
	cout << "Total permutaciones = " << sumaCasos << endl;
	cout << "Aproximado conservador filtradas = " << sumaCasosFiltrados << endl;
	cout << "Max perm./caso = " << maxComp <<  ", Max aproximado conservador filtradas/caso = " << maxComp/6 << endl;
	cout << "Memoria requerida por hilo = " << (double) (maxComp/6)*n*m*4/(1024*1024) << "MB" << endl << endl;
}


string intToString(int x){

	string itos;
	std::stringstream canal_string;
	canal_string << x;
	itos = canal_string.str();
	canal_string.str(string());

	return itos;
}


string repeat(string s, int n) { 
    // Copying given string to temparory string. 
    string s1 = s; 
  
    for (int i=1; i<n;i++) 
        s += s1; // Concatinating strings 
  
    return s; 
}


void espejo(int *vec, int* vec2, int n, int m){

	int aux;
	
	for(int i=0; i<=ceil(m/2.0)-1; i++){
	
		for(int j=0; j<=ceil(n/2.0)-1; j++){
		
			aux = vec[i+j*m];
			vec2[i+j*m] = vec[((j+1)*m-1)-i];
			vec2[((j+1)*m-1)-i] = aux;
			
			aux = vec[i+(m-1-j)*m];
			vec2[i+(m-1-j)*m] = vec[(((m-1-j)+1)*m-1)-i];
			vec2[(((m-1-j)+1)*m-1)-i] = aux;
		}
	}
}


void transpuesta(int *src, int *dst, const int n, const int m){
	
	int I;
	int J;
    //#pragma omp parallel for
    
    for(int i = 0; i<n*m; i++) {
        I = i/n;
        J = i%n;
        dst[i] = src[m*J + I];
    }
}


void escribirMallas1(ofstream& archivo, unsigned int cont, int** listaVectores, int kk, double fraccionMax){

	double fraccion = (1.0*(casosAux[kk][0] + casosAux[kk][1])/sumaN)/fraccionMax;
	
	for(int i=0; i<=cont-1; i++){

		if(((double) 1.0*rand()/RAND_MAX)<=fraccion){

			archivo << "malla" << casosAux[kk][0] << "_" << casosAux[kk][1] << "([[" << repeat("0,",m+1) << "0],";
		
			for(int j=0; j<=n-1; j++){

				archivo << "[0,";

				for(int k=0; k<=m-1; k++){
   
					archivo << listaVectores[i][j*n+k] << (k==m-1 ? ",0" : ",");
				}
				archivo << (j==n-1 ? "]" : "],");
			}  
			archivo << ",[" << repeat("0,",m+1) << "0]])." << endl;
		}
	}
}


void escribirMallas2(ofstream& archivo, unsigned int cont, int** listaVectores, int kk, int i2, double fraccionMax){

	double fraccion = (1.0*(nombresCasosPorCaso[kk][i2][0] + nombresCasosPorCaso[kk][i2][1])/sumaN)/fraccionMax;

	for(int i=0; i<=cont-1; i++){
	
		if(((double) 1.0*rand()/RAND_MAX)<=fraccion){
		
			archivo << "malla" << nombresCasosPorCaso[kk][i2][0] << "_" << nombresCasosPorCaso[kk][i2][1] << "([[" << repeat("0,",m+1) << "0],";
		
			for(int j=0; j<=n-1; j++){

				archivo << "[0,";

				for(int k=0; k<=m-1; k++){
   
					archivo << (listaVectores[i][j*n+k]==1 ? cambiosPorCaso[kk][i2][0] : (listaVectores[i][j*n+k]==2 ? cambiosPorCaso[kk][i2][1] : cambiosPorCaso[kk][i2][2])) << (k==m-1 ? ",0" : ",");
				}
				archivo << (j==n-1 ? "]" : "],");
			}   
			archivo << ",[" << repeat("0,",m+1) << "0]])." << endl;
		}
	}
}


vector<vector<int>> permutacionesCaso(vector<int> caso){

	int vec[3];
	vector<int> aux(3);
	vector<vector<int>> permutaciones_caso;
	
	copy(caso.begin(), caso.end(), vec);
	sort(vec, vec + 3);
	
	do{

		aux[0]=vec[0];
		aux[1]=vec[1];
		aux[2]=vec[2];
		permutaciones_caso.push_back(aux);

	}while(next_permutation(vec, vec + 3));
	return permutaciones_caso;
}

vector<vector<int>> cambios;
//vector<vector<int>> nombresCasos; // Declarado arriba.
vector<vector<int>> generarCambiosObjetos(vector<int> caso, vector<vector<int>> permutaciones, vector<vector<int>> &nombresCasos){

	vector<vector<int>> aux1;
	vector<int> aux3(2);
	vector<int> aux2(3);
	bool asignado[3] = {false,false,false};
	
	for(int i=0; i<=permutaciones.size()-1; i++){
	
		aux3 = {permutaciones[i][0],permutaciones[i][1]};
		if(find(especiales.begin(), especiales.end(), aux2) != especiales.end()){
	
			if(permutaciones[i][0]+permutaciones[i][1]<N0 or permutaciones[i]==caso) continue;
	
			for(int j=0; j<=2; j++){
		
				if(permutaciones[i][0]==caso[j] and !asignado[0]){ aux2[j]=1; asignado[0]=true; continue;}
				if(permutaciones[i][1]==caso[j] and !asignado[1]){ aux2[j]=2; asignado[1]=true; continue;}
				if(permutaciones[i][2]==caso[j] and !asignado[2]){ aux2[j]=0; asignado[2]=true; continue;}
			}
			
			aux1.push_back(aux2);
			nombresCasos.push_back(permutaciones[i]);
			asignado[0]=false;
			asignado[1]=false;
			asignado[2]=false;
		}
	}
	
	return aux1;
}


// vector<vector<vector<int>>> cambiosPorCaso;  // Declarado arriba.
void generarCasos(){

	vector<int> aux(3);
	vector<int> aux2(2);
	int cont=0;
	ofstream file;
	file.open("casos.pl");
	
	file << "casos([\n";
	
	int limUpNs = n*m - floor(n/2.0)*floor(m/2.0);
	int limDownNs = ceil((n*m)/2.0)+1;

	for(int i=espaciosMalla; i>=limDownNs; i--){
	
		for(int j=(i>=limUpNs ? i-limUpNs : 0); j<=(i>=limUpNs ? limUpNs : i); j++){
			
			aux2 = {i-j,j};
			if(find(especiales.begin(), especiales.end(), aux2) != especiales.end()){

				casos.push_back({i-j,j,espaciosMalla-i});
				casosAux2.push_back({i-j,j,espaciosMalla-i});
				file << i-j << "/" << j << (i==limDownNs and j==i ? "\n" : ",\n");
				cont++;
			}
		}	
	}
	
	file << "])." << endl;
	file << "dimensionesMallas(" << n << "," << m << ")." << endl;
	file.close();

	for(int i=0; i<=casosAux2.size()-1; i++){
		
		permutaciones = permutacionesCaso(casosAux2[i]);
		cambios = generarCambiosObjetos(casosAux2[i], permutaciones, nombresCasos);
		
		if(cambios.size()>0) for(int j=0; j<=cambios.size()-1; j++){
		
			casosAux2.erase(remove(casosAux2.begin(), casosAux2.end(), nombresCasos[j]), casosAux2.end());
		}
		
		cambiosPorCaso.push_back(cambios);
		casosAux.push_back(casosAux2[i]);
		nombresCasosPorCaso.push_back(nombresCasos);
		nombresCasos.clear();
	}
}



int main(){



tp1 = omp_get_wtime();

srand(time(NULL));
filtradasPorCaso();

generarCasos();

system("exec rm -r ./Archivos\\ casos/*");

omp_set_num_threads(4);

#pragma omp parallel for private(k,malla,cont,contAux,matriz22,matriz33,matriz44,matriz55,matriz66,matriz77,matriz88,archivosSalida,nombreArchivo,i2,t1,t2,t1_2) firstprivate(similarQ) schedule(dynamic)
for(k=0; k<=casosAux.size()-1; k++){
	
	int max = 0;
	if(nombresCasosPorCaso[k].size()>0){
		for(int i=0; i<=nombresCasosPorCaso[k].size()-1; i++){
				
			if(max < nombresCasosPorCaso[k][i][0] + nombresCasosPorCaso[k][i][1]) max = nombresCasosPorCaso[k][i][0] + nombresCasosPorCaso[k][i][1];
		}
	}
	else{ max = casosAux[k][0] + casosAux[k][1]; }
//cout << omp_get_thread_num() << " " << &malla << endl;
	double fraccion = 1.0*max/sumaN;
	size_t comp = (size_t) 1.0*fraccion*maxMuestras;
	double perm = (double) permutacionesPorCaso[{casosAux[k][0], casosAux[k][1]}]/8.0;
	
	int** listaVectores = new int*[comp];
	
	for(int i=0; i<=comp-1;i++){
	
		listaVectores[i] = new int[espaciosMalla];
	}

	cont=0;

	printf("(Hilo %d) Caso %d,%d.\n", omp_get_thread_num(), casosAux[k][0], casosAux[k][1]);

	while(cont < comp and cont < perm){

		t1 = omp_get_wtime();
		
		inicializarMallaAleatoriamente(malla, casosAux[k]);

		transpuesta(malla, matriz22, n, m);
		espejo(matriz22, matriz33, n, m);
		transpuesta(matriz33, matriz44, n, m);
		espejo(matriz44, matriz55, n, m);
		transpuesta(matriz55, matriz66, n, m);
		espejo(matriz66, matriz77, n, m);
		transpuesta(matriz77, matriz88, n, m);

		if(cont!=0){ for(int i=0; i<=cont-1; i++){

			if(memcmp(matriz22, listaVectores[i], sizeof(matriz22))==0){similarQ=true; break;}
			else if(memcmp(matriz33, listaVectores[i], sizeof(matriz33))==0){similarQ=true; break;}
			else if(memcmp(matriz44, listaVectores[i], sizeof(matriz44))==0){similarQ=true; break;}
			else if(memcmp(matriz55, listaVectores[i], sizeof(matriz55))==0){similarQ=true; break;}
			else if(memcmp(matriz66, listaVectores[i], sizeof(matriz66))==0){similarQ=true; break;}
			else if(memcmp(matriz77, listaVectores[i], sizeof(matriz77))==0){similarQ=true; break;}
			else if(memcmp(matriz88, listaVectores[i], sizeof(matriz88))==0){similarQ=true; break;}
		}}

		if(!similarQ){copy(malla, malla+espaciosMalla, listaVectores[cont]); cont++;}
		
		if(cont%10000==0 and contAux!=cont){t2 = omp_get_wtime(); printf("(Hilo %d) Filtrando... %d t = %f min\n", omp_get_thread_num(), cont, (t2-t1)/60.0); t1=t2; contAux=cont;}
		similarQ=false;
	
		t1_2 = omp_get_wtime();
	}

	#pragma omp atomic
	filtradas+=cont*(cambiosPorCaso[k].size()+1);
	
	printf("(Hilo %d) Filtradas (%d, %d) x %d = %d\n", omp_get_thread_num(), casosAux[k][0], casosAux[k][1], (int) (cambiosPorCaso[k].size()+1), cont);
	printf("(Hilo %d) Filtradas al momento = %d\n", omp_get_thread_num(), filtradas);
	
	strcpy(nombreArchivo, ("Archivos casos/" + intToString(casosAux[k][0]) + "," + intToString(casosAux[k][1]) + ".pl").c_str());

	archivosSalida.open(nombreArchivo);
	escribirMallas1(archivosSalida, cont, listaVectores, k, fraccion);
	archivosSalida.close();
	
	if(cambiosPorCaso[k].size()>0){
	
		for(i2=0; i2<=cambiosPorCaso[k].size()-1; i2++){

			strcpy(nombreArchivo, ("Archivos casos/" + intToString(nombresCasosPorCaso[k][i2][0]) + "," + intToString(nombresCasosPorCaso[k][i2][1]) + ".pl").c_str());
			archivosSalida.open(nombreArchivo);
			escribirMallas2(archivosSalida, cont, listaVectores, k, i2, fraccion);
			archivosSalida.close();
		}
	}

	t2 = omp_get_wtime();
	
	cont=0;
	
	for(int i=0; i<=comp-1;i++){
	
		delete [] listaVectores[i];
	}
	
	delete [] listaVectores;
}

ifstream leerCaso;
ofstream archivoFinal;
string contenido;

archivoFinal.open("baseConocimientoMallasFiltradas.pl", ios::binary);

for(int i=0; i<=casos.size()-1; i++){

	strcpy(nombreArchivo, ("Archivos casos/" + intToString(casos[i][0]) + "," + intToString(casos[i][1]) + ".pl").c_str());
	leerCaso.open(nombreArchivo, ios::binary);
	
	archivoFinal << leerCaso.rdbuf();
	
	leerCaso.close();
}

archivoFinal.close();

tp2 = omp_get_wtime();;

cout << endl << "Filtradas totales = " << filtradas << endl;
cout << "Tiempo total = " << tp2-tp1 << 's' << endl << endl;



return 0;
}
