#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
#include "Red_neuronal.h"
using namespace std;

int eje = 1;
int todos_los_ejes = 1;                         // 0: Desactivado, 1: Activado.
int N_de_senales = 318;                           // 1: Desactivado, >1: Activado

char Datos_de_entrada[50] = "";
char coeficientes[3][100]={"coeficientes_x.txt", "coeficientes_y.txt", "coeficientes_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica

char G_Espectro_senos[3][100]={"G_Espectro_senos_x.txt", "G_Espectro_senos_y.txt", "G_Espectro_senos_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica
char G_Espectro_cosenos[3][100]={"G_Espectro_cosenos_x.txt", "G_Espectro_cosenos_y.txt", "G_Espectro_cosenos_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de

string Senal_de_entrada_fija1 = "Datos_";
string Senal_de_entrada_fija2 = ".txt";

string Senal_de_salida_fija2 = ".gpl";

int evento = 1;
string eventos[5]={"Regular ","Rebase ","Frenado ","Zig-zag ","Otro "};
string color_evento[5]={"1","1","1","1","1"}; //Poner 62710 
string intervalo="plot[][] ";

//###############################################################################################################

int color_evento_C;
int color_evento_S;

const int C = 0;
const int S = 1;
const int x = 0;
const int y = 1;
const int z = 2;

char a[100];

double t;
double f;
double f2;
double frecmax;

double amplitudes_CSxyzf[2][3][3];

string xyz[3]={"x","y","z"};

string d;

std::string i_to_s;                        //Variables para pasar de un entero a un string.
std::stringstream canal_string;

ifstream file_1x;
ifstream file_1y; 
ifstream file;
ifstream file2x;
ifstream file2y;
ofstream file3;
ofstream file4;
ofstream file5;

int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch(Datos_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}

int N_de_lineasC(int contador){                                     //Función para leer el número de coeficientes
ifstream arch(coeficientes[contador], ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}

int n = N_de_lineas()-1;

void escribir_columna_1(char a[]){         //Función para leer datos
file.getline(a, 32, ',');
t = atof(a);
file3 << a << " ";                      //CAMBIO
file.getline(a, 32, ',');
f = atof(a);
file3 << f << endl;
file.getline(a, 32);
}

void escribir_columna_2(char a[]){         //Función para leer datos
file.getline(a, 32, ',');
t = atof(a);
file3 << a << " ";
file.getline(a, 32, ',');
file.getline(a, 32, ',');
f = atof(a);
file3 << f << endl;
file.getline(a, 32);
}

void escribir_columna_3(char a[]){         //Función para leer datos
file.getline(a, 32, ',');
t = atof(a);
file3 << a << " ";
file.getline(a, 32, ',');
file.getline(a, 32, ',');
file.getline(a, 32);
f = atof(a);
file3 << f << endl;
}

/*
void escribir_f2(char a[]){         //Función para leer datos_sin_ruido
file.getline(a, 32, ',');
t = atof(a);
file3 << t << " ";
file.getline(a, 32, ',');
f = atof(a);
file3 << f << endl;
file.getline(a, 32);
}
*/

void escribir_CSx(char a[]){         //Función para leer datos
file2x.getline(a, 100, '(');
file2x.getline(a, 100, ',');
f = atof(a);
d = a;
file2x.getline(a, 100, ')');
f2 = atof(a);
file2x.getline(a, 100);
}

void escribir_CSy(char a[]){         //Función para leer datos
file2y.getline(a, 100, '(');
file2y.getline(a, 100, ',');
f = atof(a);
d = a;
file2y.getline(a, 100, ')');
f2 = atof(a);
file2y.getline(a, 100);
}

void itoa(int x){                              //Función para pasar de entero a string.
canal_string << x;
i_to_s = canal_string.str();
canal_string.str(std::string());
}   

void Leer_amplitudes(){         //Modificar 2º subindice.
file_1x.getline(a, 100);
file_1x.getline(a, 32, '(');
file_1x.getline(a, 32, ',');
amplitudes_CSxyzf[C][0][0] = abs(atof(a));
file_1x.getline(a, 32, ')');
amplitudes_CSxyzf[S][1][0] = abs(atof(a));
file_1x.getline(a, 100);
file_1x.getline(a, 32, '(');
file_1x.getline(a, 32, ',');
amplitudes_CSxyzf[C][0][1] = abs(atof(a));
file_1x.getline(a, 32, ')');
amplitudes_CSxyzf[S][1][1] = abs(atof(a));
file_1y.getline(a, 100);
file_1y.getline(a, 100);
file_1y.getline(a, 100);
file_1y.getline(a, 100);
file_1y.getline(a, 32, '(');
file_1y.getline(a, 32, ',');
amplitudes_CSxyzf[C][0][2] = abs(atof(a));
file_1y.getline(a, 32, ')');
amplitudes_CSxyzf[S][1][2] = abs(atof(a));
file_1y.getline(a, 100);
}



int main(){



#include "Pesos_red_neuronal.h"

if(todos_los_ejes==1){
eje=1;
cout << endl;
cout << "ALERTA: Se trabajará con todos los ejes" << endl;
cout << endl;
}

for(int c2=1; c2 <= N_de_senales; c2++){

if(N_de_senales>1){                                
eje=eje*(!todos_los_ejes)+todos_los_ejes;          //Reiniciar la variable de los ejes cada vez que se cambie de archivo de datos

itoa((c2-1)*5);

//strcpy(coeficientes, (Senal_de_entrada_fija1 + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(coeficientes[0], ("coeficientes_x_" + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(coeficientes[1], ("coeficientes_y_" + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(coeficientes[2], ("coeficientes_z_" + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(G_Espectro_cosenos[0], ("G_Espectro_cosenos_x_" + i_to_s + Senal_de_salida_fija2).c_str());
strcpy(G_Espectro_cosenos[1], ("G_Espectro_cosenos_y_" + i_to_s + Senal_de_salida_fija2).c_str());
strcpy(G_Espectro_cosenos[2], ("G_Espectro_cosenos_z_" + i_to_s + Senal_de_salida_fija2).c_str());
strcpy(G_Espectro_senos[0], ("G_Espectro_senos_x_" + i_to_s + Senal_de_salida_fija2).c_str());
strcpy(G_Espectro_senos[1], ("G_Espectro_senos_y_" + i_to_s + Senal_de_salida_fija2).c_str());
strcpy(G_Espectro_senos[2], ("G_Espectro_senos_z_" + i_to_s + Senal_de_salida_fija2).c_str());
}

//for(int contador=0; contador<=todos_los_ejes*2; contador++){

//file.open(Datos_de_entrada);
file2x.open(coeficientes[0]);                   //ACTIVAR EL MODO DE ABRIR SI SOLO EL ARCHIVO EXISTE PARA EVITAR CREAR ARCHIVOS VACIOS
file2y.open(coeficientes[1]);                   //ACTIVAR EL MODO DE ABRIR SI SOLO EL ARCHIVO EXISTE PARA EVITAR CREAR ARCHIVOS VACIOS
//file3.open(G_Datos[eje-1]);
file4.open(G_Espectro_senos[0]);
file5.open(G_Espectro_cosenos[0]);

int N = N_de_lineasC(1);

file_1x.open(coeficientes[0]);
file_1y.open(coeficientes[1]);
Leer_amplitudes();

      salida[0][0][0] = amplitudes_CSxyzf[C][0][0];
      salida[0][0][1] = amplitudes_CSxyzf[C][0][1];
      salida[0][0][2] = amplitudes_CSxyzf[C][0][2];

      salida[1][0][0] = amplitudes_CSxyzf[S][1][0];
      salida[1][0][1] = amplitudes_CSxyzf[S][1][1];
      salida[1][0][2] = amplitudes_CSxyzf[S][1][2];

         for(int n=0; n<=1; n++){

            for(int k=1; k<=num_capas-2; k++){                    //Se comienza desde la segunda capa ya que la primera es de las entradas.

               for(int i=0; i<=neuronas_por_capa[k]-1; i++){
               a_k_i(n,k,i);
               salida[n][k][i]=sigmoide(a_ki[n][k][i]);
               }
            }
 
            for(int k=num_capas-1; k==num_capas-1; k++){                    

               for(int i=0; i<=neuronas_por_capa[k]-1; i++){
               a_k_i(n,k,i);
               salida[n][k][i]=sigmoide(a_ki[n][k][i]);
               }
            } 
         }

         if(salida[0][num_capas-1][0]>0.7 and salida[0][num_capas-1][1]<0.3 and salida[0][num_capas-1][2]<0.3 ){
         color_evento_C=2;
         }
         else if(salida[0][num_capas-1][0]<0.3 and salida[0][num_capas-1][1]>0.7 and salida[0][num_capas-1][2]<0.3 ){
         color_evento_C=1;
         }
         else if(salida[0][num_capas-1][0]<0.3 and salida[0][num_capas-1][1]<0.3 and salida[0][num_capas-1][2]>0.7 ){
         color_evento_C=3;
         }
         else if(salida[0][num_capas-1][0]<0.3 and salida[0][num_capas-1][1]<0.3 and salida[0][num_capas-1][2]<0.3 ){
         color_evento_C=0;
         }
         else{
         color_evento_C=4;
         }

         if(salida[1][num_capas-1][0]>0.7 and salida[1][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]<0.3){
         color_evento_S=2;
         }
         else if(salida[1][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]>0.7 and salida[1][num_capas-1][2]<0.3 ){
         color_evento_S=1;
         }
         else if(salida[1][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]>0.7 ){
         color_evento_S=3;
         }
         else if(salida[1][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]<0.3 ){
         color_evento_S=0;
         }
         else{
         color_evento_S=4;
         }

      file_1x.close();
      file_1y.close();

file5 << "set title \"Espectro de frecuencias. " << eventos[evento] << "eje " << xyz[0] << " (Cosenos)\"" << endl;
file5 << "set xlabel \'Frecuencia (Hz)\'" << endl;
file5 << "set ylabel \'Aceleraci\\363n (valor absoluto)\'" << endl;
file5 << intervalo;
file4 << "set title \"Espectro de frecuencias. " << eventos[evento] << "eje " << xyz[0] << " (Senos)\"" << endl;
file4 << "set xlabel \'Frecuencia (Hz)\'" << endl;
file4 << "set ylabel \'Aceleraci\\363n (valor absoluto)\'" << endl;
file4 << intervalo;

file2x.getline(a, 100, '(');                //Contribución de la frecuencia más alta.
file2x.getline(a, 100, '(');
file2x.getline(a, 100, ',');
frecmax = atof(a);
file2x.getline(a, 100);
file2x.close();
file2x.open(coeficientes[0]);   

for(int i=0; i<=N-1; i++){
escribir_CSx(a);
if(i==1 or i==2/* or i==4*/){
file5 << "\"<echo \'" << 1.*i/(2*N*0.01) << " " << abs(f) << "\'\" w i lc " << color_evento[color_evento_C] << " t \"\", \\" << endl;            //Espectro en valor absoluto
file4 << "\"<echo \'" << 1.*i/(2*N*0.01) << " " << abs(-f2) << "\'\" w i lc " << color_evento[color_evento_S] << " t \"\", \\" << endl;            //Espectro en valor absoluto
}
else{
file5 << "\"<echo \'" << 1.*i/(2*N*0.01) << " " << abs(f) << "\'\" w i lc 5 t \"\", \\" << endl;            //Espectro en valor absoluto
file4 << "\"<echo \'" << 1.*i/(2*N*0.01) << " " << abs(-f2) << "\'\" w i lc 5 t \"\", \\" << endl;            //Espectro en valor absoluto
}
}
file5 << "\"<echo \'" << 0.5/0.01 << " " << abs(frecmax) << "\'\" w i lc 5 t \"\", \\" << endl;            //Espectro en valor absoluto
file4 << "\"<echo \'" << 0.5/0.01 << " " << 0 << "\'\" w i lc 5 t \"\", \\" << endl;            //Espectro en valor absoluto

file2x.close();
file4.close();
file5.close();

//Lo mismo para el eje y.

file2y.open(coeficientes[1]);
file4.open(G_Espectro_senos[1]);
file5.open(G_Espectro_cosenos[1]);

file5 << "set title \"Espectro de frecuencias. " << eventos[evento] << "eje " << xyz[1] << " (Cosenos)\"" << endl;
file5 << "set xlabel \'Frecuencia (Hz)\'" << endl;
file5 << "set ylabel \'Aceleraci\\363n (valor absoluto)\'" << endl;
file5 << intervalo;
file4 << "set title \"Espectro de frecuencias. " << eventos[evento] << "eje " << xyz[1] << " (Senos)\"" << endl;
file4 << "set xlabel \'Frecuencia (Hz)\'" << endl;
file4 << "set ylabel \'Aceleraci\\363n (valor absoluto)\'" << endl;
file4 << intervalo;

file2y.getline(a, 100, '(');                //Contribución de la frecuencia más alta.
file2y.getline(a, 100, '(');
file2y.getline(a, 100, ',');
frecmax = atof(a);
file2y.getline(a, 100);
file2y.close();
file2y.open(coeficientes[0]);   

for(int i=0; i<=N-1; i++){
escribir_CSy(a);
if(/*i==1 or i==2 or */i==4){
file5 << "\"<echo \'" << 1.*i/(2*N*0.01) << " " << abs(f) << "\'\" w i lc " << color_evento[color_evento_C] << " t \"\", \\" << endl;            //Espectro en valor absoluto
file4 << "\"<echo \'" << 1.*i/(2*N*0.01) << " " << abs(-f2) << "\'\" w i lc " << color_evento[color_evento_C] << " t \"\", \\" << endl;            //Espectro en valor absoluto
}
else{
file5 << "\"<echo \'" << 1.*i/(2*N*0.01) << " " << abs(f) << "\'\" w i lc 5 t \"\", \\" << endl;            //Espectro en valor absoluto
file4 << "\"<echo \'" << 1.*i/(2*N*0.01) << " " << abs(-f2) << "\'\" w i lc 5 t \"\", \\" << endl;            //Espectro en valor absoluto
}
}
file5 << "\"<echo \'" << 0.5/0.01 << " " << abs(frecmax) << "\'\" w i lc 5 t \"\", \\" << endl;            //Espectro en valor absoluto
file4 << "\"<echo \'" << 0.5/0.01 << " " << 0 << "\'\" w i lc 5 t \"\", \\" << endl;            //Espectro en valor absoluto


/*
if(eje == 1){
file.getline(a, 32);
for(int i=1; i<=n; i++){
escribir_columna_1(a);
}
}

if(eje == 2){
file.getline(a, 32);
for(int i=1; i<=n; i++){
escribir_columna_2(a);
}
}

if(eje == 3){
file.getline(a, 32);
for(int i=1; i<=n; i++){
escribir_columna_3(a);
}
}
*/

file.close();
file2y.close();
file3.close();
file4.close();
file5.close();

eje++;

//}   //contador

}

return 0;

}








