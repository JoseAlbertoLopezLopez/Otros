#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;

char a[100];
int pa = 0;
double S = 0.0;
double P = 0.0;
double ACx;
double ASx;

fstream file3("coeficientes.txt");
fstream file4("coeficientes.txt");

int N_de_lineas_coef(){                                     //Función para leer el número de coeficientes
ifstream arch("coeficientes.txt", ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}

void Leer_amplitudes_s(char a[]){         //Función para leer datos
file3.getline(a, 100, ',');
file3.getline(a, 100, ')');
ASx = 1.*atof(a);
file3.getline(a, 100);
}

void Leer_amplitudes_c(char a[]){         //Función para leer datos
file4.getline(a, 100, '(');
file4.getline(a, 100, ',');
ACx = 1.*atof(a);
file4.getline(a, 100);
}



int main(){



int d = N_de_lineas_coef();

file3.getline(a, 99);                     //Saltarse la primera línea
file4.getline(a, 99, '(');                //Leer sólo el coeficiente correspondiente a la mayor frecuencia
file4.getline(a, 99, '('); 
file4.getline(a, 99, ','); 
ACx = 1.*atof(a);
S = S + abs(ACx);
file4.getline(a, 99);

for(int k=1; k <= d - 1; k++){    

Leer_amplitudes_s(a);
Leer_amplitudes_c(a);

S = S + abs(ASx) + abs(ACx);

   if(abs(ASx>8.64204e-05)){     //Contar cuantas amplitudes están arriba del promedio
   cout << pa++ << endl;
   }

   if(abs(ACx>8.64204e-05)){     
   cout << pa++ << endl;
   }

}

P = S/((2.*d)-1);

cout << P << endl;

/*/###############################################################################################################

if(eje == 2){

int d = N_de_lineas_coef();

file3.getline(a, 99);                     //Saltarse la primera línea
file4.getline(a, 99, '(');                //Leer sólo el coeficiente correspondiente a la mayor frecuencia
file4.getline(a, 99, '('); 
file4.getline(a, 99, ','); 
ACx = 1.*atof(a);
S = S + abs(ACx);
file4.getline(a, 99);

for(int k=1; k <= d - 1; k++){    

Leer_amplitudes_s(a);
Leer_amplitudes_c(a);

S = S + abs(ASx) + abs(ACx);

   if(abs(ASx>8.64204e-05)){     
   cout << pa++ << endl;
   }

   if(abs(ACx>8.64204e-05)){     
   cout << pa++ << endl;
   }

}

P = S/((2.*d)-1);

cout << P << endl;

}

//###############################################################################################################

if(eje == 3){

int d = N_de_lineas_coef();

file3.getline(a, 99);                     //Saltarse la primera línea
file4.getline(a, 99, '(');                //Leer sólo el coeficiente correspondiente a la mayor frecuencia
file4.getline(a, 99, '('); 
file4.getline(a, 99, ','); 
ACx = 1.*atof(a);
S = S + abs(ACx);
file4.getline(a, 99);

for(int k=1; k <= d - 1; k++){    

Leer_amplitudes_s(a);
Leer_amplitudes_c(a);

S = S + abs(ASx) + abs(ACx);

   if(abs(ASx>8.64204e-05)){     
   cout << pa++ << endl;
   }

   if(abs(ACx>8.64204e-05)){     
   cout << pa++ << endl;
   }

}

P = S/((2.*d)-1);

cout << P << endl;

}

*/

return 0;

}



















