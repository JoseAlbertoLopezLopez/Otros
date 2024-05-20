// Declarando el vector de filtradas dinámicamente (new) dentro del for.
#include <iostream>     // cout
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

using namespace std;


ofstream archivosSalida;
char nombreArchivo[100];

const int n=3;
const int m=5;
const int espaciosMalla = n*m;
int N0 = ceil(espaciosMalla/2.0) + 1;
int N1;
int N2;
int k;
int i2;

int malla[espaciosMalla];
int contUniv = 0;
vector<vector<int>> casos;
vector<vector<int>> casosAux;
vector<vector<int>> casosAux2;
vector<vector<int>> nombresCasos;
vector<vector<vector<int>>> nombresCasosPorCaso;

bool salir = false;
bool similarQ = false;
size_t cont=0;
size_t contAux=-1;
size_t filtradas=0;

double tp1;
double tp2;
double t1;
double t1_2;
double t2;

int matriz1[espaciosMalla];
int* matriz2;
int* matriz3;
int* matriz4;
int* matriz5;
int* matriz6;
int* matriz7;
int* matriz8;


int matriz22[espaciosMalla];
int matriz33[espaciosMalla];
int matriz44[espaciosMalla];
int matriz55[espaciosMalla];
int matriz66[espaciosMalla];
int matriz77[espaciosMalla];
int matriz88[espaciosMalla];

vector<vector<int>> permutaciones;


// PROBAR MÉTODO.
//int* matricesSimilares[8];

double factorial(int x){

	double factorial_=1;                         

	if(x<=1) return 1;
		
	for(int i=0; i<=(x-2); i++){
		factorial_*=(x-i);
	}

	return factorial_;
}

map<array<int, 2> , size_t> permutacionesPorCaso;
map<array<int, 2> , size_t> filtradasCaso;
void filtradasPorCaso(){

	int limUpNs;
	int limDownNs;
	int numCasos=0;
	int Ns[2];
	double maxComp=0;
	double casosAux;
	double sumaCasos = 0;
	double sumaCasosFiltrados = 0;

	limUpNs = n*m - floor(n/2.0)*floor(m/2.0);
	limDownNs = ceil((n*m)/2.0)+1;

	for(int i=n*m; i>=limDownNs; i--){
		for(int j=(i>=limUpNs ? i-limUpNs : 0); j<=(i>=limUpNs ? limUpNs : i); j++){

			Ns[0] = i-j;
			Ns[1] = j;
		
			casosAux = factorial(n*m)/(factorial(Ns[0])*factorial(Ns[1])*factorial(n*m - i));
			permutacionesPorCaso[{i-j, j}] = casosAux;
			filtradasCaso[{i-j, j}] = (size_t) ceil(casosAux/6)*4;
			if(maxComp<casosAux) maxComp = casosAux;
			sumaCasos += casosAux;
			sumaCasosFiltrados += casosAux/6;
			numCasos++;
		
			cout << Ns[0] << "," << Ns[1] << " :" << "Perm. = " << casosAux << ", Filt. = " << casosAux/6 << endl;
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
			
			aux = vec[i+(n-1-j)*m];
			vec2[i+(n-1-j)*m] = vec[(n-1-j)*m+m-1-i];
			vec2[(n-1-j)*m+m-1-i] = aux;
		}
	}
}


void espejoV(int *vec, int* vec2, int n, int m){

	int aux;
	
	for(int i=0; i<=ceil(n/2.0)-1; i++){
	
		for(int j=0; j<=ceil(m/2.0)-1; j++){
		
			aux = vec[i*m+j];
			vec2[i*m+j] = vec[m*(n-1-i)+j];
			vec2[m*(n-1-i)+j] = aux;
			
			aux = vec[i*m+m-j-1];
			vec2[i*m+m-j-1] = vec[m*(n-1-i)+m-j-1];
			vec2[m*(n-1-i)+m-j-1] = aux;
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


void escribirMallas1(ofstream& archivo, unsigned long cont, int** listaVectores, int n, int m, int kk){
//printf("cont = %d, Thread %d\n",(int) cont,omp_get_thread_num());
	for(int i=0; i<=cont-1; i++){
//printf("i = %d, Thread %d\n",i,omp_get_thread_num());
		archivo << "malla" << casosAux[kk][0] << "_" << casosAux[kk][1] << "([[" << repeat("0,",m+1) << "0],";
		
		for(int j=0; j<=n-1; j++){

			archivo << "[0,";

			for(int k=0; k<=m-1; k++){
   
				archivo << listaVectores[i][j*m+k] << (k==m-1 ? ",0" : ",");
			}
			archivo << (j==n-1 ? "]" : "],");
		}  
		archivo << ",[" << repeat("0,",m+1) << "0]])." << endl;  
	}
}

//void escribirMallas2(ofstream& archivo, int lista[][espaciosMalla] documentar.
void escribirMallas2(ofstream& archivo, unsigned long cont, int** listaVectores, vector<vector<int>> &nombresCasos, int n, int m, vector<int> cambio, int i2){

	
	for(int i=0; i<=cont-1; i++){
		
		archivo << "malla" << nombresCasos[i2][0] << "_" << nombresCasos[i2][1] << "([[" << repeat("0,",m+1) << "0],";
		
		for(int j=0; j<=n-1; j++){

			archivo << "[0,";

			for(int k=0; k<=m-1; k++){
   
				archivo << (listaVectores[i][j*m+k]==1 ? cambio[0] : (listaVectores[i][j*m+k]==2 ? cambio[1] : cambio[2])) << (k==m-1 ? ",0" : ",");
			}
			archivo << (j==n-1 ? "]" : "],");
		}   
		archivo << ",[" << repeat("0,",m+1) << "0]])." << endl;   
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
	vector<int> aux2(3);
	bool asignado[3] = {false,false,false};
	
	for(int i=0; i<=permutaciones.size()-1; i++){
	
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
	
	return aux1;
}


vector<vector<vector<int>>> cambiosPorCaso;
void generarCasos(){

	vector<int> aux(3);
	int cont=0;
	ofstream file;
	file.open("casos.pl");
	
	file << "casos([\n";
	
	int limUpNs = n*m - floor(n/2.0)*floor(m/2.0);
	int limDownNs = ceil((n*m)/2.0)+1;

	for(int i=espaciosMalla; i>=limDownNs; i--){
	
		for(int j=(i>=limUpNs ? i-limUpNs : 0); j<=(i>=limUpNs ? limUpNs : i); j++){

			casos.push_back({i-j,j,espaciosMalla-i});
			casosAux2.push_back({i-j,j,espaciosMalla-i});
			file << i-j << "/" << j << (i==limDownNs and j==i ? "\n" : ",\n");
			cont++;
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

filtradasPorCaso();

generarCasos();
system("exec rm -r ./Archivos\\ casos/*");

omp_set_num_threads(4);
//Cont_Univ = 44705
#pragma omp parallel for private(k,malla,cont,contAux,matriz22,matriz33,matriz44,matriz55,matriz66,matriz77,matriz88,archivosSalida,nombreArchivo,i2,t1,t2,t1_2) firstprivate(similarQ) schedule(dynamic) // nowait
for(k=0; k<=casosAux.size()-1; k++){

	int** listaVectores = new int*[filtradasCaso[{casosAux[k][0],casosAux[k][1]}]];
	
	for(int i=0; i<=filtradasCaso[{casosAux[k][0],casosAux[k][1]}]-1;i++){
	
		listaVectores[i] = new int[espaciosMalla];
	}

	fill(malla, malla + casosAux[k][0], 1);
	fill(malla + casosAux[k][0], malla + casosAux[k][0] + casosAux[k][1], 2);
	fill(malla + casosAux[k][0] + casosAux[k][1], malla + espaciosMalla, 0);

	cont=0;
	
	printf("(Hilo %d) Caso %d,%d. Permutaciones = %d\n", omp_get_thread_num(), casosAux[k][0], casosAux[k][1], (int) permutacionesPorCaso[{casosAux[k][0],casosAux[k][1]}]);

	sort(malla, malla + espaciosMalla);
	
	t1 = omp_get_wtime();
	
	do{

		//Caso n=m.
		/*
		transpuesta(malla, matriz22, n, m);
		espejo(matriz22, matriz33, n, m);
		transpuesta(matriz33, matriz44, n, m);
		espejo(matriz44, matriz55, n, m);
		transpuesta(matriz55, matriz66, n, m);
		espejo(matriz66, matriz77, n, m);
		transpuesta(matriz77, matriz88, n, m);
		*/
		
		//Caso n!=m.
		espejo(malla, matriz22, n, m);
		espejoV(matriz22, matriz33, n, m);
		espejo(matriz33, matriz44, n, m);
		
		/*if(k==0 and j==6){
		imprimirVectorMatriz(listaVectores[j], n, m);
		imprimirVectorMatriz(matriz2, n, m);
		imprimirVectorMatriz(matriz3, n, m);
		imprimirVectorMatriz(matriz4, n, m);
		imprimirVectorMatriz(matriz5, n, m);
		imprimirVectorMatriz(matriz6, n, m);
		imprimirVectorMatriz(matriz7, n, m);
		imprimirVectorMatriz(matriz8, n, m);
		
		return 0;}*/
		
		//for(unsigned int i=0; i<= cont-1; i++){
		//	printf("Mal i = %d, %d, Thread %d\n",i, (unsigned int) cont, omp_get_thread_num());
		//}

		//for(auto mallaFiltrada : listaMatrices){
		if(cont!=0){ for(int i=0; i<=cont-1; i++){
		//printf("%d,Thread %d\n",(unsigned int) cont,omp_get_thread_num());
			/*for(int f=0; f<=espaciosMalla-1; f++){
				matriz22[f]=matriz2[f];
				matriz33[f]=matriz3[f];
				matriz44[f]=matriz4[f];
				matriz55[f]=matriz5[f];
				matriz66[f]=matriz6[f];
				matriz77[f]=matriz7[f];
				matriz88[f]=matriz8[f];
			}*/
		
			// Mejor opción para comparar vectores dinámicos.
			/*if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[1].begin())){similarQ=true; break;}
			else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[2].begin())){similarQ=true; break;}
			else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[3].begin())){similarQ=true; break;}
			else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[4].begin())){similarQ=true; break;}
			else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[5].begin())){similarQ=true; break;}
			else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[6].begin())){similarQ=true; break;}
			else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[7].begin())){similarQ=true; break;}*/
			
			if(memcmp(matriz22, listaVectores[i], sizeof(matriz22))==0){similarQ=true; break;}
			else if(memcmp(matriz33, listaVectores[i], sizeof(matriz33))==0){similarQ=true; break;}
			else if(memcmp(matriz44, listaVectores[i], sizeof(matriz44))==0){similarQ=true; break;}
			/*
			else if(memcmp(matriz55, listaVectores[i], sizeof(matriz55))==0){similarQ=true; break;}
			else if(memcmp(matriz66, listaVectores[i], sizeof(matriz66))==0){similarQ=true; break;}
			else if(memcmp(matriz77, listaVectores[i], sizeof(matriz77))==0){similarQ=true; break;}
			else if(memcmp(matriz88, listaVectores[i], sizeof(matriz88))==0){similarQ=true; break;}
			*/
			
			/*if(equal(matriz2, matriz2 + espaciosMalla, listaVectores[i])){similarQ=true; break;}
			else if(equal(matriz3, matriz3 + espaciosMalla, listaVectores[i])){similarQ=true; break;}
			else if(equal(matriz4, matriz4 + espaciosMalla, listaVectores[i])){similarQ=true; break;}
			else if(equal(matriz5, matriz5 + espaciosMalla, listaVectores[i])){similarQ=true; break;}
			else if(equal(matriz6, matriz6 + espaciosMalla, listaVectores[i])){similarQ=true; break;}
			else if(equal(matriz7, matriz7 + espaciosMalla, listaVectores[i])){similarQ=true; break;}
			else if(equal(matriz8, matriz8 + espaciosMalla, listaVectores[i])){similarQ=true; break;}*/
			//printf("i = %d, Thread %d\n",i,omp_get_thread_num());
		}}
		
		/*if(rand()%100>=2){similarQ=true;}
		else{similarQ=false;}*/
		//if(similarQ){cout << "Hola " << cont << endl;break;}
		
		//if(!similarQ){listaMatrices[cont].assign(matricesSimilares[0].begin(), matricesSimilares[0].end());cont++;}
		//if(!similarQ){listaVectores[cont].assign(listaVectores[j].begin(), listaVectores[j].end());cont++;}
		//if(!similarQ){copy(listaVectores[j].begin(), listaVectores[j].end(), listaVectores[cont].begin());cont++;}

		if(!similarQ){copy(malla, malla+espaciosMalla, listaVectores[cont]); cont++;}
		//#pragma omp atomic
		//contUniv++;
		//if(contUniv==44705){ printf("%s\n","Yaaaaaaaaaaa"); }
		//}
		if(cont%10000==0 and contAux!=cont){t2 = omp_get_wtime(); printf("(Hilo %d) Filtrando... %u t = %f min\n", omp_get_thread_num(), (size_t) cont, (t2-t1)/60.0); t1=t2; contAux=cont;}
		similarQ=false;

	}while(next_permutation(malla, malla + espaciosMalla));
	
	t1_2 = omp_get_wtime();
	
	#pragma omp atomic
	filtradas+=cont*(cambiosPorCaso[k].size()+1);
	
	printf("(Hilo %d) Filtradas (%d, %d) x %d = %u\n", omp_get_thread_num(), casosAux[k][0], casosAux[k][1], (int) (cambiosPorCaso[k].size()+1), (size_t) cont);
	printf("(Hilo %d) Filtradas al momento = %u\n", omp_get_thread_num(), (size_t) filtradas);
	
	strcpy(nombreArchivo, ("Archivos casos/" + intToString(casosAux[k][0]) + "," + intToString(casosAux[k][1]) + ".pl").c_str());
	
	archivosSalida.open(nombreArchivo);
	escribirMallas1(archivosSalida, cont, listaVectores, n, m, k);
	archivosSalida.close();
	
	if(cambiosPorCaso[k].size()>0){
	
		for(i2=0; i2<=cambiosPorCaso[k].size()-1; i2++){

			strcpy(nombreArchivo, ("Archivos casos/" + intToString(nombresCasosPorCaso[k][i2][0]) + "," + intToString(nombresCasosPorCaso[k][i2][1]) + ".pl").c_str());
			archivosSalida.open(nombreArchivo);
			escribirMallas2(archivosSalida, cont, listaVectores, nombresCasosPorCaso[k], n, m, cambiosPorCaso[k][i2], i2);
			archivosSalida.close();
		}
	}

	t2 = omp_get_wtime();

	//cout << "Archivos escritos en " << t2-t1_2 << "s." << endl << endl;
	
	cont=0;
	
	for(int i=0; i<=filtradasCaso[{casosAux[k][0],casosAux[k][1]}]-1;i++){
	
		delete [] listaVectores[i];
	}
	
	delete [] listaVectores;
}

ifstream leerCaso;
ofstream archivoFinal;
string contenido;

archivoFinal.open("baseConocimientoMallasFiltradas.pl", ios::binary);

//printf("CasosSize = %d\n", (int) casos.size());

for(int i=0; i<=casos.size()-1; i++){

	strcpy(nombreArchivo, ("Archivos casos/" + intToString(casos[i][0]) + "," + intToString(casos[i][1]) + ".pl").c_str());
	leerCaso.open(nombreArchivo, ios::binary);
	
	archivoFinal << leerCaso.rdbuf();
	
	leerCaso.close();
}

archivoFinal.close();

tp2 = omp_get_wtime();;

cout << "Filtradas totales = " << filtradas << endl;
cout << "Tiempo total = " << tp2-tp1 << 's' << endl;



return 0;
}
