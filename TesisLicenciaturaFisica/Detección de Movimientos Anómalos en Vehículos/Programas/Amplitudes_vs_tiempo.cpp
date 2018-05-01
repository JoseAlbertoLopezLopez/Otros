/*Este programa toma como entrada archivos de espectros de frecuencias provenientes de una ventana de cierta 
dimensión que se corrió en una serie de tiempo, dando como resultado varios archivos de espectros de 
dimensión menor correspondientes a cada "foto" que hizo la ventana en la señal original. Para cada espectro de 
cada foto toma las amplitudes de las frecuencias que estén entre frec +- df y el tiempo correspondiente a esa 
foto, suma las amplitudes multiplicadas por su correspondiente seno o coseno (cuyo argumento contiene a la 
frecuencia correspondiente) y los escribe en 3 archivos de salida que sirven para graficar las contribuciones de 
las frecuencias que se encuentren en el margen de frec +- df vs el tiempo, un archivo es sólo para cosenos, otro 
para senos y otro para el total.*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;

int eje = 1;                        // 1:x, 2:y, 3:z.
int todos_los_ejes = 1;             // 0: Desactivado, 1: Activado.
int Num_de_archivos = 439;          // Número de archivos por eje.

double frecs[10000]={0};
double vec_AS[10000]={0};
double vec_AC[10000]={0};
double frec = 0.6;                 // OJO: Las frecuencias pueden estar en rads/s.
double df = 0.3;                   // +- El margen que abarca la frecuencia en cuestión.
double ventana = 15.0;
double delta_t = 0.01;              //Intervalo de muestreo de la señal de la que se obtuvieron los espectros.

string entrada_fija1 = "coeficientes_";
string entrada_fija2 = ".txt";

string salida_fija1 = "Amplitud_vs_tiempo_";
string salida_fija2 = "(frec=";
string salida_fija3 = ").txt";

//###############################################################################################################

char archivo_de_entrada[50];
char archivo_de_salida[50];

ifstream file_1;
ofstream file_0_C;
ofstream file_0_S;
ofstream file_0;

std::string i_to_s;                        //Variables para pasar de un entero a un string.
std::stringstream canal_string;

int c1;
int c2;
int c3;
int c4;
int N;        // Número de líneas de cada archivo de coeficientes.

double t=0;
double AC;    // Amplitud de coseno.
double AS;    // Amplitud de seno.
double suma_ASsin=0;
double suma_ACcos=0;

char a[100];
char coeficientes[3][100]={"coeficientes_x.txt", "coeficientes_y.txt", "coeficientes_z.txt"};

string Eje[3]={"x_","y_","z_"};

void Leer_amplitudes(char a[]){         //Función para leer datos
file_1.getline(a, 100, '(');
file_1.getline(a, 100, ',');
AC = 1.*atof(a);
file_1.getline(a, 100, ')');
AS = 1.*atof(a);
file_1.getline(a, 100);
}

int N_de_lineas(){                                     //Función para leer el número de datos.
ifstream arch(archivo_de_entrada, ifstream::in);       //OJO: Cambio el nombre de la variable.
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}

void itoa(double x){                              //Función para pasar de entero a string.
canal_string << x;
i_to_s = canal_string.str();
canal_string.str(std::string());
}  



int main(){



if(todos_los_ejes==1){
eje=1;
cout << endl;
cout << "ALERTA: Se trabajará con todos los ejes" << endl;
cout << endl;
}

for(c2=0; c2<=todos_los_ejes*2; c2++){

itoa(frec);

strcpy(archivo_de_salida, (salida_fija1 + Eje[c2+not(todos_los_ejes)*(eje-1)] + "C_" + salida_fija2 + i_to_s + salida_fija3).c_str());
file_0_C.open(archivo_de_salida);
strcpy(archivo_de_salida, (salida_fija1 + Eje[c2+not(todos_los_ejes)*(eje-1)] + "S_" + salida_fija2 + i_to_s + salida_fija3).c_str());
file_0_S.open(archivo_de_salida);
strcpy(archivo_de_salida, (salida_fija1 + Eje[c2+not(todos_los_ejes)*(eje-1)] + "S+C_" + salida_fija2 + i_to_s + salida_fija3).c_str());
file_0.open(archivo_de_salida);

   for(c1=0; c1 <= Num_de_archivos-1; c1++){
  
   itoa(c1*5);

   strcpy(archivo_de_entrada, (entrada_fija1 + Eje[c2+not(todos_los_ejes)*(eje-1)] + i_to_s + entrada_fija2).c_str());
   file_1.open(archivo_de_entrada);

   t = ventana + c1*50.0*delta_t;                                         //OJO: Modificar cuando sea necesario el número (cuando el intervalo de tiempo cambie)

   N = N_de_lineas();

   file_1.getline(a, 100);

      for(c3=1; c3<=N-1; c3++){
      Leer_amplitudes(a);                                               

      if(c3*M_PI/(N*delta_t)<=frec+df and c3*M_PI/(N*delta_t)>=frec-df){      //OJO: La "N" aquí no es el número de datos, es el número de coeficientes por lo que el numerador no se multiplica por 2.
      frecs[c3]=(M_PI*c3)/(N*delta_t);                                    //Puede actualizarse sólo una vez siempre y cuando N siempre sea la misma.
      vec_AC[c3]=AC;
      vec_AS[c3]=AS;
      suma_ACcos+=vec_AC[c3]*cos(frecs[c3]*t);    
      suma_ASsin+=vec_AS[c3]*sin(frecs[c3]*t);
      }
       
      }
  
   file_0_C << t << " " << suma_ACcos << endl;
   file_0_S << t << " " << -suma_ASsin << endl;
   file_0 << t << " " << abs(-suma_ASsin + suma_ACcos) << endl;
   file_1.close();
   suma_ACcos=0;
   suma_ASsin=0;
   }

eje++;
file_0_C.close();
file_0_S.close();
file_0.close();

}

return 0;

}
