#include <iostream>
#include <algorithm> 
#include <vector> // next_permutation, sort
#include <time.h>

using namespace std;



const int n=4;
const int m=4;
int espaciosMalla = n*m;
int N0 = ceil(espaciosMalla/2.0) + 1;
int N1;
int N2;

bool salir = false;
bool similarQ = false;
int cont=0;

clock_t t1;
clock_t t2;

vector<vector<vector<int>>> listaMatrices(2200000,vector<vector<int>>(n,vector<int>(m)));
vector<vector<int>> listaVectores2(2200000,vector<int>(n*m));
vector<vector<int>> listaVectores;
vector<vector<int>> matriz;

// PROBAR MÉTODO.
vector<vector<vector<int>>> matricesSimilares(8, vector<vector<int>>(n,vector<int>(m)));

vector<vector<int>> matriz1(n, vector<int>(m));
vector<vector<int>> matriz2(n, vector<int>(m));
vector<vector<int>> matriz3(n, vector<int>(m));
vector<vector<int>> matriz4(n, vector<int>(m));
vector<vector<int>> matriz5(n, vector<int>(m));
vector<vector<int>> matriz6(n, vector<int>(m));
vector<vector<int>> matriz7(n, vector<int>(m));
vector<vector<int>> matriz8(n, vector<int>(m));

vector<vector<int>> matrizPrueba = {{0,2,1,1},
									{1,2,2,2},
									{2,0,0,0},
									{1,1,0,0}};

vector<int> vectorPrueba = {0,2,1,1,1,2,2,2,2,0,0,0,1,1,0,0};
//vector<int> vectorPrueba = {0,0,0,0,0,0,1,1,1,2,1,2,2,2,2,1};
//vector<int> arrayPrueba[n*m] = {0,2,1,1,1,2,2,2,2,0,0,0,1,1,0,0};

vector<int> vectorAux;


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
	                            
	for(int i=0; i<=matriz.size()-1; i++){

		for(int j=0; j<=matriz[0].size()-1; j++){
   
			cout << matriz[i][j] << " ";
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





int main(){



//int vector[] = {1,1,2,0};
//int vector[] = {1,1,1,2,2,2,0,0,0};
int vector[] = {1,1,1,1,1,2,2,2,2,2,0,0,0,0,0,0};

vectorAux.resize(espaciosMalla);

sort(vector,vector+espaciosMalla);

do{

	vectorAux.assign(begin(vector), end(vector));
	listaVectores.push_back(vectorAux);

} while(next_permutation(vector,vector+espaciosMalla));

t1 = 1.0*clock()/CLOCKS_PER_SEC;

const int num = listaMatrices.size();
const int num2 = listaVectores.size();
//const int* ptr = (num > 0) ? listaMatrices.data() : nullptr;
//const int* ptr2 = (num > 0) ? matricesSimilares.data() : nullptr;


for(int j = 0; j < num2; j++){

	matricesSimilares[0] = convertirVectorMatriz(listaVectores[j], n, m);
	matricesSimilares[1] = rotar90(matricesSimilares[0], n);
	matricesSimilares[2] = rotar90(matricesSimilares[1], n);
	matricesSimilares[3] = rotar90(matricesSimilares[2], n);
	
	reverse_copy(matricesSimilares[0].begin(), matricesSimilares[0].end(), matricesSimilares[4].begin());
	reverse_copy(matricesSimilares[1].begin(), matricesSimilares[1].end(), matricesSimilares[5].begin());
	reverse_copy(matricesSimilares[2].begin(), matricesSimilares[2].end(), matricesSimilares[6].begin());
	reverse_copy(matricesSimilares[3].begin(), matricesSimilares[3].end(), matricesSimilares[7].begin());
	
	/*imprimirMatriz(matricesSimilares[0]);
	imprimirMatriz(matricesSimilares[1]);
	imprimirMatriz(matricesSimilares[2]);
	imprimirMatriz(matricesSimilares[3]);
	imprimirMatriz(matricesSimilares[4]);
	imprimirMatriz(matricesSimilares[5]);
	imprimirMatriz(matricesSimilares[6]);
	imprimirMatriz(matricesSimilares[7]);
	
	break;*/
	
	//for(auto mallaFiltrada : listaMatrices){
	for(int i = 0; i < num; i++){
		
		if(i>cont) break;
	
		/*if(ptr[i] == &matricesSimilares[1]){similarQ=true; break;}
		else if(ptr[i] == &matricesSimilares[2]){similarQ=true; break;}
		else if(ptr[i] == &matricesSimilares[3]){similarQ=true; break;}
		else if(ptr[i] == &matricesSimilares[4]){similarQ=true; break;}
		else if(ptr[i] == &matricesSimilares[5]){similarQ=true; break;}
		else if(ptr[i] == &matricesSimilares[6]){similarQ=true; break;}
		else if(ptr[i] == &matricesSimilares[7]){similarQ=true; break;}*/
			
		/*if(listaMatrices[i] == matricesSimilares[1]){similarQ=true; break;}
		else if(listaMatrices[i] == matricesSimilares[2]){similarQ=true; break;}
		else if(listaMatrices[i] == matricesSimilares[3]){similarQ=true; break;}
		else if(listaMatrices[i] == matricesSimilares[4]){similarQ=true; break;}
		else if(listaMatrices[i] == matricesSimilares[5]){similarQ=true; break;}
		else if(listaMatrices[i] == matricesSimilares[6]){similarQ=true; break;}
		else if(listaMatrices[i] == matricesSimilares[7]){similarQ=true; break;}*/
		
		// Mejor opción para comparar.
		/*if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[1].begin())){similarQ=true; break;}
		else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[2].begin())){similarQ=true; break;}
		else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[3].begin())){similarQ=true; break;}
		else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[4].begin())){similarQ=true; break;}
		else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[5].begin())){similarQ=true; break;}
		else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[6].begin())){similarQ=true; break;}
		else if(equal(listaMatrices[i].begin(), listaMatrices[i].end(), matricesSimilares[7].begin())){similarQ=true; break;}*/
		
		if(equal(listaVectores2[i].begin(), listaVectores2[i].end(), vectorPrueba.begin())){similarQ=true; break;}
		else if(equal(listaVectores2[i].begin(), listaVectores2[i].end(), vectorPrueba.begin())){similarQ=true; break;}
		else if(equal(listaVectores2[i].begin(), listaVectores2[i].end(), vectorPrueba.begin())){similarQ=true; break;}
		else if(equal(listaVectores2[i].begin(), listaVectores2[i].end(), vectorPrueba.begin())){similarQ=true; break;}
		else if(equal(listaVectores2[i].begin(), listaVectores2[i].end(), vectorPrueba.begin())){similarQ=true; break;}
		else if(equal(listaVectores2[i].begin(), listaVectores2[i].end(), vectorPrueba.begin())){similarQ=true; break;}
		else if(equal(listaVectores2[i].begin(), listaVectores2[i].end(), vectorPrueba.begin())){similarQ=true; break;}

	}
	
	
	
	//if(!similarQ){listaMatrices[cont].assign(matricesSimilares[0].begin(), matricesSimilares[0].end());cont++;}
	if(!similarQ){listaVectores2[cont].assign(listaVectores[j].begin(), listaVectores[j].end());cont++;}
	//if(!similarQ){copy(listaVectores[j].begin(), listaVectores[j].end(), listaVectores2[cont].begin());cont++;}
	if(cont%10000==0){t2 = 1.0*clock()/CLOCKS_PER_SEC; cout << cont << "  t = " << (t2-t1)/60.0 << "min" << listaVectores2.size() << endl; imprimirVector(listaVectores2[cont-1]);imprimirVector(listaVectores2[cont]);t1=t2;}
	similarQ=false;
}

cout << cont << endl;

/*for(int i=0; i<=listaVectores.size()-1; i++){

	if(i%100000==0) cout << i << endl;
	matriz = convertirVectorMatriz(listaVectores[i],4,4);
	if(matriz==matrizPrueba) cout << "Encontrada." << endl;
}
imprimirMatriz(matriz);*/



return 0;
}
