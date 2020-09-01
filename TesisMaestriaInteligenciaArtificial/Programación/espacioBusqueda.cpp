#include <iostream>
#include <algorithm> 
#include <time.h>
#include <array>
#include <map>
#include <fstream>

using namespace std;


const int n = 5;
const int m = 5;
const int numClases = 2;
int limUpNs;
int limDownNs;
int Ns[numClases];

int numCasos=0;
double maxComp=0;
double casosAux;
double sumaCasos = 0;
double sumaCasosFiltrados = 0;


double factorial(int x){

	double factorial_=1;                         

	if(x<=1) return 1;
		
	for(int i=0; i<=(x-2); i++){
		factorial_*=(x-i);
	}

	return factorial_;
}



int main(){



limUpNs = n*m - floor(n/2.0)*floor(m/2.0);
limDownNs = ceil((n*m)/2.0)+1;

for(int i=n*m; i>=limDownNs; i--){
	for(int j=(i>=limUpNs ? i-limUpNs : 0); j<=(i>=limUpNs ? limUpNs : i); j++){

		Ns[0] = i-j;
		Ns[1] = j;
		
		casosAux = factorial(n*m)/(factorial(Ns[0])*factorial(Ns[1])*factorial(n*m - i));
		if(maxComp<casosAux) maxComp = casosAux;
		sumaCasos += casosAux;
		sumaCasosFiltrados += casosAux/6;
		
		cout << Ns[0] << "," << Ns[1] << " :" << "Perm. = " << casosAux << ", Filt. = " << casosAux/6 << endl;
		
		numCasos++;
	}
}

//std::cout.precision(20);
cout << endl << "Num. casos = " << numCasos << endl;
cout << "Total permutaciones = " << sumaCasos << endl;
cout << "Aproximado conservador filtradas = " << sumaCasosFiltrados << endl;
cout << "Max perm./caso = " << maxComp <<  ", Max aproximado conservador filtradas/caso = " << maxComp/6 << endl;
cout << "Memoria requerida por hilo = " << (double) (maxComp/6)*n*m*4/(1024*1024) << "MB" << endl;


return 0;

}
