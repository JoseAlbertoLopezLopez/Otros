#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;

double x;              //Aceleraciones en x,y,z y tiempo
double y;
double z;
double t;

char c[32]={0};

ifstream file2("datos.txt");
ofstream file3("coeficientes.txt");

const int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch("datos.txt", ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
const int u=lin;
return u;
}

void Aceleraciones(char c[]){         //Función para leer datos
file2.getline(c, 32, ',');
t = atof(c);
file2.getline(c, 32, ',');
x = atof(c);
file2.getline(c, 32, ',');
y = atof(c);
file2.getline(c, 32);
z = atof(c);
}



int main(){  


const int N = N_de_lineas() - 1;
int a[N]={0};
double b[N];
complex<double> d[N];
int n=N/2;


a[1]=N/2;

for(int i=1; i<=N/2 ; i++){
   if (a[i]==0){
      n /= 2;
      for(int j=0; j<i; j++){ 
      a[i+j]=a[j]+n;
      }
   i = 1;
   }
}
for(int i=0; i<N; i++){
cout << a[i] << endl;
}


int k=0;                                             
complex<double> Cpx, Cix, Ckx, Ckx_;                        //Coeficientes pares, impares y totales de acel. en x 
complex<double> w = complex<double>(0.,(-2.*M_PI)*k*n/N);   //Argumento de la exponencial compleja de la fórmula
complex<double> e = exp(w);
complex<double> m = complex<double>(1.,0.);                 //Sirve para actualizar variables

file2.close();

for(int i=0; i<=N-1; i++){

file2.open("datos.txt");
file2.getline(c,32);
   for(int j=0; j<=a[i]; j++){
   Aceleraciones(c);
   }
b[i]=x;
file2.close();
}


for(int i=0; i<=N-1; i++){
d[i]=b[i];
//cout << b[i] << endl;
}

/*for(int i=0; i<=N-1; i++){
cout << d[i] << endl;
}*/

n=N/2;
w = complex<double>(0.,(-2.*M_PI)*k*n/N);
e = exp(w);

for(int k=0; k<=(N/2)-1; k++){
Ckx = complex<double>(0.,0.);         
Ckx_ = complex<double>(0.,0.);
n=N/2;
w = complex<double>(0.,(-2.*M_PI)*k*n/N);
e = exp(w);
//cout << n << "," << k << endl;
//cout << e << endl;

   for(int i=0; i<=N-1; i++){
   d[i]=b[i];
   }

   for(int j=0; j<=log(N)/log(2)-1; j++){

      for(int i=0; i<=n-1; i++){
      d[i] = d[2*i] + e*d[2*i+1];
      }

   n/=2;
   w = complex<double>(0.,(-2.*M_PI)*k*n/N);
   e = exp(w);
//   cout << n << endl;
//   cout << e << endl;
  
   }
Ckx = d[0] + e*d[1];                   //Coeficientes pares e impares sumados
Ckx_ = d[0] - e*d[1]; 

if (abs(real(Ckx)) < 1e-4) real(Ckx) = 0.;
if (abs(imag(Ckx)) < 1e-4) imag(Ckx) = 0.;
if (abs(real(Ckx_)) < 1e-4) real(Ckx_) = 0.;
if (abs(imag(Ckx_)) < 1e-4) imag(Ckx_) = 0.;

file3 << (2./N)*Ckx << "," << (2./N)*Ckx_ << endl;

}

file3.close();

return 0;

}






