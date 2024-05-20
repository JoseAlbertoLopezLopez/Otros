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
#include <omp.h>

using namespace std;


ofstream archivosSalida;
char nombreArchivo[100];

const int n=4;
const int m=4;
const int espaciosMalla = n*m;
int N0 = ceil(espaciosMalla/2.0) + 1;
int N1;
int N2;
int k;
int i2;

int malla[espaciosMalla];

const int numCasos = ((espaciosMalla+1)*(espaciosMalla+1)+espaciosMalla+1)/2 - (N0*N0+N0)/2;
vector<vector<int>> casos;
vector<vector<int>> casosAux;
vector<vector<int>> casosAux2;
vector<vector<int>> nombresCasos;
vector<vector<vector<int>>> nombresCasosPorCaso;

bool salir = false;
bool similarQ = false;
unsigned long cont=0;
unsigned long cont1=0;
unsigned long contAux=-1;
int contUniv=0;
unsigned long filtradas=0;

double tp1;
double tp2;
double t1;
double t1_2;
double t2;

const int long1 = 2018029;
const int long2 = 240240;

//vector<vector<vector<int>>> listaMatrices(2200000,vector<vector<int>>(n,vector<int>(m)));
vector<vector<int>> listaVectores3(long1,vector<int>(n*m));

int listaVectores2[long2][espaciosMalla];
int listaVectores[long1][espaciosMalla];

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

/*int matrizPrueba2[n*m] = {1,2,3,4,
						 5,6,7,8,
					     9,10,11,12,
						 13,14,15,16};*/
						
/*int matrizPrueba2[(n)*(m)] = {1,2,3,
						 	   4,5,6,
							   7,8,9};*/


//int vectorPrueba[n*m] = {0,2,1,1,1,2,2,2,2};

int vectorAux[espaciosMalla];


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


vector<vector<int>> convertirVectorMatriz(vector<int>& v, int n, int m){

	vector<vector<int>> v2(n, vector<int>(m));
	int cont2=0;
	
	for(int i=0; i<=n-1; i++){
	
		for(int j=0; j<=m-1; j++){
		
			v2[i][j] = v[cont2];
			cont2++;
		}
	}
	
	return v2;
}


void imprimirMatriz(vector<vector<int>>& matriz){
	                       
	
	if(matriz.size()!=0){
	     
	for(int i=0; i<=matriz.size()-1; i++){

		for(int j=0; j<=matriz[0].size()-1; j++){
   
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}   
	cout << endl;  
	}  
}


void imprimirVectorMatriz(int* vec, int n, int m){
	                            
	for(int i=0; i<=n-1; i++){

		for(int j=0; j<=m-1; j++){
   
			cout << vec[i*n+j] << " ";
		}
		cout << endl;
	}   
	cout << endl;    
}


void imprimirVector(vector<int>& vec){
	                            
	for(int i=0; i<=vec.size()-1; i++){
   
		cout << vec[i] << " ";
	}
	cout << endl;
}


void imprimirVector2(int* vec){

	const int len = n*m;
	                            
	for(int i=0; i<=len-1; i++){
   
		cout << vec[i] << " ";
	}
	cout << endl;
}


vector<vector<int>> rotar90(vector<vector<int>>& matriz, int n){

	vector<vector<int>> matriz2(n,vector<int>(n));
	
	for (int i=0; i<n/2; i++){

		for (int j=i; j<n-i-1; j++){

			matriz2[i][j] = matriz[n-1-j][i]; 
			matriz2[n-1-j][i] = matriz[n-1-i][n-1-j]; 
			matriz2[n-1-i][n-1-j] = matriz[j][n-1-i]; 
			matriz2[j][n-1-i] = matriz[i][j];
		} 
	}
	
	return matriz2;
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


void escribirMallas1(ofstream& archivo, unsigned long cont, int listaVectores2[][espaciosMalla], int n, int m, int kk){
//printf("cont = %d, Thread %d\n",(int) cont,omp_get_thread_num());
	for(int i=0; i<=cont-1; i++){
//printf("i = %d, Thread %d\n",i,omp_get_thread_num());
		archivo << "malla" << casosAux[kk][0] << "_" << casosAux[kk][1] << "([[" << repeat("0,",m+1) << "0],";
		
		for(int j=0; j<=n-1; j++){

			archivo << "[0,";

			for(int k=0; k<=m-1; k++){
   
				archivo << listaVectores2[i][j*n+k] << (k==m-1 ? ",0" : ",");
			}
			archivo << (j==n-1 ? "]" : "],");
		}  
		archivo << ",[" << repeat("0,",m+1) << "0]])." << endl;  
	}
}

//void escribirMallas2(ofstream& archivo, int lista[][espaciosMalla] documentar.
void escribirMallas2(ofstream& archivo, unsigned long cont, int listaVectores2[][espaciosMalla], vector<vector<int>> &nombresCasos, int n, int m, vector<int> cambio, int i2){

	
	for(int i=0; i<=cont-1; i++){
		
		archivo << "malla" << nombresCasos[i2][0] << "_" << nombresCasos[i2][1] << "([[" << repeat("0,",m+1) << "0],";
		
		for(int j=0; j<=n-1; j++){

			archivo << "[0,";

			for(int k=0; k<=m-1; k++){
   
				archivo << (listaVectores2[i][j*n+k]==1 ? cambio[0] : (listaVectores2[i][j*n+k]==2 ? cambio[1] : cambio[2])) << (k==m-1 ? ",0" : ",");
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
	
	file << "]).";
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

generarCasos();
system("exec rm -r ./Archivos\\ casos/*");

omp_set_num_threads(4);
//Cont_Univ = 44705
#pragma omp parallel for private(k,malla,listaVectores,listaVectores2,cont1,cont,contAux,matriz22,matriz33,matriz44,matriz55,matriz66,matriz77,matriz88,archivosSalida,nombreArchivo,i2,t1,t2,t1_2) firstprivate(similarQ) // nowait
for(k=0; k<=casosAux.size()-1; k++){

	fill(malla, malla + casosAux[k][0], 1);
	fill(malla + casosAux[k][0], malla + casosAux[k][0] + casosAux[k][1], 2);
	fill(malla + casosAux[k][0] + casosAux[k][1], malla + espaciosMalla, 0);

	cont=0;
	cont1=0;
	
	sort(malla, malla + espaciosMalla);
	do{

		copy(malla, malla + espaciosMalla, listaVectores[cont1]);
		cont1++;

	}while(next_permutation(malla, malla + espaciosMalla));
	
	printf("Caso %d,%d (Hilo %d). Permutaciones = %d\n", casosAux[k][0], casosAux[k][1], omp_get_thread_num(), (unsigned int) cont1);
	t1 = omp_get_wtime();

	for(int j=0; j<=cont1-1; j++){

		transpuesta(listaVectores[j], matriz22, n, m);
		espejo(matriz22, matriz33, n, m);
		transpuesta(matriz33, matriz44, n, m);
		espejo(matriz44, matriz55, n, m);
		transpuesta(matriz55, matriz66, n, m);
		espejo(matriz66, matriz77, n, m);
		transpuesta(matriz77, matriz88, n, m);
		
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
		if(cont!=0) for(int i=0; i<=cont-1; i++){
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
			
			if(memcmp(matriz22, listaVectores2[i], sizeof(matriz22))==0){similarQ=true; break;}
			else if(memcmp(matriz33, listaVectores2[i], sizeof(matriz33))==0){similarQ=true; break;}
			else if(memcmp(matriz44, listaVectores2[i], sizeof(matriz44))==0){similarQ=true; break;}
			else if(memcmp(matriz55, listaVectores2[i], sizeof(matriz55))==0){similarQ=true; break;}
			else if(memcmp(matriz66, listaVectores2[i], sizeof(matriz66))==0){similarQ=true; break;}
			else if(memcmp(matriz77, listaVectores2[i], sizeof(matriz77))==0){similarQ=true; break;}
			else if(memcmp(matriz88, listaVectores2[i], sizeof(matriz88))==0){similarQ=true; break;}
			
			/*if(equal(matriz2, matriz2 + espaciosMalla, listaVectores2[i])){similarQ=true; break;}
			else if(equal(matriz3, matriz3 + espaciosMalla, listaVectores2[i])){similarQ=true; break;}
			else if(equal(matriz4, matriz4 + espaciosMalla, listaVectores2[i])){similarQ=true; break;}
			else if(equal(matriz5, matriz5 + espaciosMalla, listaVectores2[i])){similarQ=true; break;}
			else if(equal(matriz6, matriz6 + espaciosMalla, listaVectores2[i])){similarQ=true; break;}
			else if(equal(matriz7, matriz7 + espaciosMalla, listaVectores2[i])){similarQ=true; break;}
			else if(equal(matriz8, matriz8 + espaciosMalla, listaVectores2[i])){similarQ=true; break;}*/
			//printf("i = %d, Thread %d\n",i,omp_get_thread_num());
		}
		
		/*if(rand()%100>=2){similarQ=true;}
		else{similarQ=false;}*/
		//if(similarQ){cout << "Hola " << cont << endl;break;}
		
		//if(!similarQ){listaMatrices[cont].assign(matricesSimilares[0].begin(), matricesSimilares[0].end());cont++;}
		//if(!similarQ){listaVectores2[cont].assign(listaVectores[j].begin(), listaVectores[j].end());cont++;}
		//if(!similarQ){copy(listaVectores[j].begin(), listaVectores[j].end(), listaVectores2[cont].begin());cont++;}

		if(!similarQ){copy(listaVectores[j], listaVectores[j]+espaciosMalla, listaVectores2[cont]); cont++;
		#pragma omp atomic
		contUniv++;
		if(contUniv==44705){ printf("%s\n","Yaaaaaaaaaaa"); }
		}
		if(cont%10000==0 and contAux!=cont){t2 = omp_get_wtime(); printf("Filtrando... %u t = %f min\n", (unsigned int) cont, (t2-t1)/60.0); t1=t2; contAux=cont;}
		similarQ=false;
	}
	
	t1_2 = omp_get_wtime();
	
	#pragma omp atomic
	filtradas+=cont*(cambiosPorCaso[k].size()+1);
	
	printf("Filtradas (%d, %d) x %d (Hilo %d) = %u\n", casosAux[k][0], casosAux[k][1], (int) (cambios.size()+1), omp_get_thread_num(), (unsigned int) cont);
	printf("Filtradas al momento = %u\n", (unsigned int) filtradas);
	//cout << "Escribiendo archivos... " << cont << endl;
	
	strcpy(nombreArchivo, ("Archivos casos/" + intToString(casosAux[k][0]) + "," + intToString(casosAux[k][1]) + ".pl").c_str());
	
	archivosSalida.open(nombreArchivo);
	escribirMallas1(archivosSalida, cont, listaVectores2, n, m, k);
	archivosSalida.close();
	
	if(cambiosPorCaso[k].size()>0){
	
		for(i2=0; i2<=cambiosPorCaso[k].size()-1; i2++){

			strcpy(nombreArchivo, ("Archivos casos/" + intToString(nombresCasosPorCaso[k][i2][0]) + "," + intToString(nombresCasosPorCaso[k][i2][1]) + ".pl").c_str());
			archivosSalida.open(nombreArchivo);
			escribirMallas2(archivosSalida, cont, listaVectores2, nombresCasosPorCaso[k], n, m, cambiosPorCaso[k][i2], i2);
			archivosSalida.close();
		}
	}

	t2 = omp_get_wtime();

	//cout << "Archivos escritos en " << t2-t1_2 << "s." << endl << endl;
	
	cont=0;
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
