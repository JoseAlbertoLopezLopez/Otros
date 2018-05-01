/*Este programa toma como entrada los espectros de señales para una cierta ventana de tiempo que va recorriendo
la señal cada cierto dt, para los espectros de cada ventana que toma tabula el tiempo en el que se tomó la ventana
en la señal, el eje que se está analizando, las amplitudes que tengan un valor absoluto por encima de un 
parámetro y su frecuencia correspondiente, la salida son 2 archivos con la anterior tabulación, uno para senos
y otro para cosenos, todos los ejes que cumplan la condición de tener una o más amplitudes mayores a la propuesta
serán tabulados en el mismo archivo*/


#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;

int Num_de_senales=318;            //Número de ventanas consecutivas que se van a analizar.
double ventana=15.0;
double Filtro_amplitud=1.0;
double delta_t = 0.01;             //Intervalo de muestreo de la señal de la que se obtuvieron los espectros. 

string Senal_de_entrada_fija1 = "Datos_";
string Senal_de_entrada_fija2 = ".txt";

//###############################################################################################################

int c1;
int c2;
int c3;

double k2;
double ACx;
double ASx;

char Senal_de_entrada[50];
char Eje[3]={'x','y','z'};
char a[100];

string coeficientes[3]={"coeficientes_x_", "coeficientes_y_", "coeficientes_z_"};

std::string i_to_s;                        //Variables para pasar de un entero a un string.
std::stringstream canal_string;

ifstream file_1;
ofstream file_0_C;
ofstream file_0_S;

int N_de_lineas(){                                     //Función para leer el número de datos.
ifstream arch(Senal_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}

void itoa(int x){                              //Función para pasar de entero a string.
canal_string << x;
i_to_s = canal_string.str();
canal_string.str(std::string());
} 

void Filtro_amplitudes(char a[]){         //Función para leer datos
file_1.getline(a, 100, '(');
file_1.getline(a, 100, ',');
ACx = 1.*atof(a);
file_1.getline(a, 100, ')');
ASx = 1.*atof(a);
file_1.getline(a, 100);

if(abs(ACx)>=Filtro_amplitud){
file_0_C << ventana+(c1-1)*5./10 << ' ' << M_PI*c2*(1/(k2*delta_t)) << ' ' << ACx << ' ' << Eje[c3] << endl;  //OJO: La "k2" aquí no es el número de datos, es el número de coeficientes por lo que el numerador no se multiplica por 2.
}

if(abs(ASx)>=Filtro_amplitud){
file_0_S << ventana+(c1-1)*5./10 << ' ' << M_PI*c2*(1/(k2*delta_t)) << ' ' << ASx << ' ' << Eje[c3] << endl;  //OJO: La "k2" aquí no es el número de datos, es el número de coeficientes por lo que el numerador no se multiplica por 2.
}

}



int main(){



file_0_C.open("Frecuencias_mas_altas_C.txt");
file_0_C << "Tiempo (s), Frecuencia (1/s), Amplitud (m/s^2), Eje" << endl;
file_0_S.open("Frecuencias_mas_altas_S.txt");
file_0_S << "Tiempo (s), Frecuencia (1/s), Amplitud (m/s^2), Eje" << endl;

for(c3=0; c3<=2; c3++){

   for(c1=1; c1<=Num_de_senales; c1++){

   itoa((c1-1)*5);
   
   strcpy(Senal_de_entrada, (coeficientes[c3] + i_to_s + Senal_de_entrada_fija2).c_str());

   k2=N_de_lineas();
   file_1.open(Senal_de_entrada);
   file_1.getline(a, 100);               //OJO: No se toma en cuenta la frec. más alta.
 
      for(c2=1; c2<=k2-1; c2++){
      Filtro_amplitudes(a);    
      }

   file_1.close();
   }

}

file_0_C.close();
file_0_S.close();

return 0;

}


