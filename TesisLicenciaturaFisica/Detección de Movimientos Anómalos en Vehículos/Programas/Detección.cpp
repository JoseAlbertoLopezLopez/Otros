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
int todos_los_ejes = 1;             // 0: Desactivado, 1: Activado.
int N_de_senales = 439;               // 1: Desactivado, >1: Activado

char archivo_de_salida[50] = "Deteccion.txt";
char archivo_de_salida2[50] = "Deteccion.txt";

string salida_fija1 = "Deteccion_";
string salida_fija2 = ".gpl";

string entrada_fija1 = "coeficientes_";
string entrada_fija2 = ".txt";

string evento="Detecci{\\363}n rebase";
string intervalo="plot[][-1:4] ";

char coeficientes[3][100]={"coeficientes_x.txt", "coeficientes_y.txt", "coeficientes_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica

string eventos[5]={" ", " ", " ", " ", ""};  //"Regular", "Rebase", "Frenado", "Zig-zag", ""

int num_evento[5]={0,1,2,3,0};   //Valor de cada evento en el contradominio.

int ls=11;   //Estilo de línea (Gnuplot).

//###############################################################################################################

int num[15];

string xyz[3]={"x","y","z"};
char CS[2]={'C','S'};

const int C = 0;
const int S = 1;
const int CxS = 2;
const int x = 0;
const int y = 1;
const int z = 2;

double amplitudes_CSxyzf[2][3][3];

char a[100];

char archivo_de_entrada[50];

ifstream file_1x; 
ifstream file_1y; 
ofstream file_C;
ofstream file_S;
ofstream file_CxS;
ofstream file_C_f;
ofstream file_S_f;
ofstream file_C_r;
ofstream file_S_r;
ofstream file_C_z;
ofstream file_S_z;
ofstream file_SxC_f;
ofstream file_SxC_r;
ofstream file_SxC_z;

std::string i_to_s;                        //Variables para pasar de un entero a un string.
std::stringstream canal_string;

int N_de_lineas(){                                     //Función para leer el número de datos.
ifstream arch(archivo_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}

string imprimir_cadena(int c, int d){
if(num[c]==0 and d==C){
num[c]=1;
return eventos[c];
}
else if(num[c+5]==0 and d==S){
num[c+5]=1;
return eventos[c];
}
else if(num[c+10]==0 and d==CxS){
num[c+10]=1;
return eventos[c];
}
else{
return "";
}
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

//for(int c3=0; c3<=2; c3++){

strcpy(archivo_de_salida, (salida_fija1 + "C" + salida_fija2).c_str());
file_C.open(archivo_de_salida);

strcpy(archivo_de_salida2, (salida_fija1 + "S" + salida_fija2).c_str());
file_S.open(archivo_de_salida2);

strcpy(archivo_de_salida2, (salida_fija1 + "CxS" + salida_fija2).c_str());
file_CxS.open(archivo_de_salida2);

/*file_C << "set title \"" << evento << " " << "(Cosenos)" <<  "\"" << endl;
file_S << "set title \"" << evento << " " << "(Senos)" <<  "\"" << endl;
file_C << "set xlabel \'Tiempo (s)\'" << endl;
file_S << "set xlabel \'Tiempo (s)\'" << endl;
file_C << "set ylabel \'Evento\'" << endl;
file_S << "set ylabel \'Evento\'" << endl;*/

file_C << intervalo;
file_S << intervalo;
file_CxS << intervalo;

file_C_f.open("Salida_C_f.txt");
file_S_f.open("Salida_S_f.txt");
file_C_r.open("Salida_C_r.txt");
file_S_r.open("Salida_S_r.txt");
file_C_z.open("Salida_C_z.txt");
file_S_z.open("Salida_S_z.txt");
file_SxC_f.open("Salida_SxC_f.txt");
file_SxC_r.open("Salida_SxC_r.txt");
file_SxC_z.open("Salida_SxC_z.txt");

for(int i=0; i<=9; i++){num[i]=0;}

for(int c2=1; c2 <= N_de_senales; c2++){

if(N_de_senales>1){                                
eje=eje*(!todos_los_ejes)+todos_los_ejes;          //Reiniciar la variable de los ejes cada vez que se cambie de archivo de datos
itoa((c2-1)*5);
strcpy(coeficientes[0], ("coeficientes_x_" + i_to_s + entrada_fija2).c_str());
strcpy(coeficientes[1], ("coeficientes_y_" + i_to_s + entrada_fija2).c_str());
strcpy(coeficientes[2], ("coeficientes_z_" + i_to_s + entrada_fija2).c_str());
}

file_1x.open(coeficientes[0]);                   //ACTIVAR EL MODO DE ABRIR SI SOLO EL ARCHIVO EXISTE PARA EVITAR CREAR ARCHIVOS VACIOS
file_1y.open(coeficientes[1]);
Leer_amplitudes();

      salida[0][0][0] = amplitudes_CSxyzf[C][0][0];
      salida[0][0][1] = amplitudes_CSxyzf[C][0][1];
      salida[0][0][2] = amplitudes_CSxyzf[C][0][2];

      salida[1][0][0] = amplitudes_CSxyzf[S][1][0];
      salida[1][0][1] = amplitudes_CSxyzf[S][1][1];
      salida[1][0][2] = amplitudes_CSxyzf[S][1][2];
/*
      cout << amplitudes_CSxyzf[C][c3][0] << endl;
      cout << amplitudes_CSxyzf[C][c3][1]<< endl;
      cout << amplitudes_CSxyzf[C][c3][2]<< endl;

      cout << amplitudes_CSxyzf[S][c3][0]<< endl;
      cout << amplitudes_CSxyzf[S][c3][1]<< endl;
      cout << amplitudes_CSxyzf[S][c3][2]<< endl;

      cout << endl;*/

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

         file_SxC_f << 15+(c2-1)*0.5 << ' ' << salida[1][num_capas-1][0]*salida[0][num_capas-1][0] << endl;
         file_SxC_r << 15+(c2-1)*0.5 << ' ' << salida[1][num_capas-1][1]*salida[0][num_capas-1][1] << endl;
         file_SxC_z << 15+(c2-1)*0.5 << ' ' << salida[1][num_capas-1][2]*salida[0][num_capas-1][2] << endl;

         file_C_f << 15+(c2-1)*0.5 << ' ' << salida[0][num_capas-1][0] << endl;
         file_S_f << 15+(c2-1)*0.5 << ' ' << salida[1][num_capas-1][0] << endl;
         file_C_r << 15+(c2-1)*0.5 << ' ' << salida[0][num_capas-1][1] << endl;
         file_S_r << 15+(c2-1)*0.5 << ' ' << salida[1][num_capas-1][1] << endl;
         file_C_z << 15+(c2-1)*0.5 << ' ' << salida[0][num_capas-1][2] << endl;
         file_S_z << 15+(c2-1)*0.5 << ' ' << salida[1][num_capas-1][2] << endl;

         if(salida[0][num_capas-1][0]>0.7 and salida[0][num_capas-1][1]<0.3 and salida[0][num_capas-1][2]<0.3 ){
         file_C << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[2] << "\'\" w p ls " << ls << " lc 7 t \"" << imprimir_cadena(num_evento[2],C) << "\", \\" << endl;
         }
         else if(salida[0][num_capas-1][0]<0.3 and salida[0][num_capas-1][1]>0.7 and salida[0][num_capas-1][2]<0.3 ){
         file_C << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[1] << "\'\" w p ls " << ls << " lc 2 t \"" << imprimir_cadena(num_evento[1],C) << "\", \\" << endl;
         }
         else if(salida[0][num_capas-1][0]<0.3 and salida[0][num_capas-1][1]<0.3 and salida[0][num_capas-1][2]>0.7 ){
         file_C << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[3] << "\'\" w p ls " << ls << " lc 1 t \"" << imprimir_cadena(num_evento[3],C) << "\", \\" << endl;
         }
         else if(salida[0][num_capas-1][0]<0.3 and salida[0][num_capas-1][1]<0.3 and salida[0][num_capas-1][2]<0.3 ){
         file_C << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[0] << "\'\" w p ls " << ls << " lc 6 t \"" << imprimir_cadena(num_evento[0],C) << "\", \\" << endl;
         }
         else{
         file_C << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[4] << "\'\" w p ls " << ls << " lc 6 t \"" << imprimir_cadena(num_evento[4],C) << "\", \\" << endl;
         }

         if(salida[1][num_capas-1][0]>0.7 and salida[1][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]<0.3){
         file_S << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[2] << "\'\" w p ls " << ls << " lc 7 t \"" << imprimir_cadena(num_evento[2],S) << "\", \\" << endl;
         }
         else if(salida[1][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]>0.7 and salida[1][num_capas-1][2]<0.3 ){
         file_S << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[1] << "\'\" w p ls " << ls << " lc 2 t \"" << imprimir_cadena(num_evento[1],S) << "\", \\" << endl;
         }
         else if(salida[1][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]>0.7 ){
         file_S << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[3] << "\'\" w p ls " << ls << " lc 1 t \"" << imprimir_cadena(num_evento[3],S) << "\", \\" << endl;
         }
         else if(salida[1][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]<0.3 ){
         file_S << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[0] << "\'\" w p ls " << ls << " lc 6 t \"" << imprimir_cadena(num_evento[0],S) << "\", \\" << endl;
         }
         else{
         file_S << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[4] << "\'\" w p ls " << ls << " lc 6 t \"" << imprimir_cadena(num_evento[4],S) << "\", \\" << endl;
         }

         if(salida[1][num_capas-1][0]*salida[0][num_capas-1][0]>0.7 and salida[1][num_capas-1][1]*salida[0][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]*salida[0][num_capas-1][2]<0.3 ){
         file_CxS << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[2] << "\'\" w p ls " << ls << " lc 7 t \"" << imprimir_cadena(num_evento[2],CxS) << "\", \\" << endl;
         }
         else if(salida[1][num_capas-1][0]*salida[0][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]*salida[0][num_capas-1][1]>0.7 and salida[1][num_capas-1][2]*salida[0][num_capas-1][2]<0.3 ){
         file_CxS << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[1] << "\'\" w p ls " << ls << " lc 2 t \"" << imprimir_cadena(num_evento[1],CxS) << "\", \\" << endl;
         }
         else if(salida[1][num_capas-1][0]*salida[0][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]*salida[0][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]*salida[0][num_capas-1][2]>0.7 ){
         file_CxS << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[3] << "\'\" w p ls " << ls << " lc 1 t \"" << imprimir_cadena(num_evento[3],CxS) << "\", \\" << endl;
         }
         else if(salida[1][num_capas-1][0]*salida[0][num_capas-1][0]<0.3 and salida[1][num_capas-1][1]*salida[0][num_capas-1][1]<0.3 and salida[1][num_capas-1][2]*salida[0][num_capas-1][2]<0.3 ){
         file_CxS << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[0] << "\'\" w p ls " << ls << " lc 6 t \"" << imprimir_cadena(num_evento[0],CxS) << "\", \\" << endl;
         }
         else{
         file_CxS << "\"<echo '" << 15+(c2-1)*0.5 << ' ' << num_evento[4] << "\'\" w p ls " << ls << " lc 6 t \"" << imprimir_cadena(num_evento[4],CxS) << "\", \\" << endl;
         }

      file_1x.close();
      file_1y.close();
}

file_C_f.close();
file_S_f.close();
file_C_r.close();
file_S_r.close();
file_C_z.close();
file_S_z.close();
file_SxC_f.close();
file_SxC_r.close();
file_SxC_z.close();

file_C.close();
file_S.close();

//   }   //Eje (c3)

return 0;

}









