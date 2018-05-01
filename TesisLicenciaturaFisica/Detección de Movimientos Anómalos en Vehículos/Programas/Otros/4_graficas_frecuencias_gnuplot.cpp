#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

bool SoC=0;

int todos_los_ejes = 1;
int eje = 0;
int vec = 0;
int vec2 = 0;
int lim = 3;

double maxi[4];
double x;

char S_C[2][10]={"senos","cosenos"};
char ejes[3]={'x','y','z'};
char a[100];
char Senal_de_entrada[93][50]={
"G_Espectro_senos_x_1.txt",
"G_Espectro_senos_x_10.txt",
"G_Espectro_senos_x_20.txt",
"G_Espectro_senos_x_30.txt",
"G_Espectro_senos_x_40.txt",
"G_Espectro_senos_x_50.txt",
"G_Espectro_senos_x_60.txt",
"G_Espectro_senos_x_70.txt",
"G_Espectro_senos_x_80.txt",
"G_Espectro_senos_x_90.txt",
"G_Espectro_senos_x_100.txt",
"G_Espectro_senos_x_110.txt",
"G_Espectro_senos_x_120.txt",
"G_Espectro_senos_x_130.txt",
"G_Espectro_senos_x_140.txt",
"G_Espectro_senos_x_150.txt",
"G_Espectro_senos_x_160.txt",
"G_Espectro_senos_x_170.txt",
"G_Espectro_senos_x_180.txt",
"G_Espectro_senos_x_190.txt",
"G_Espectro_senos_x_200.txt",
"G_Espectro_senos_x_210.txt",
"G_Espectro_senos_x_220.txt",
"G_Espectro_senos_x_230.txt",
"G_Espectro_senos_x_240.txt",
"G_Espectro_senos_x_250.txt",
"G_Espectro_senos_x_260.txt",
"G_Espectro_senos_x_270.txt",
"G_Espectro_senos_x_280.txt",
"G_Espectro_senos_x_290.txt",
"G_Espectro_senos_x_300.txt",
"G_Espectro_senos_y_1.txt",
"G_Espectro_senos_y_10.txt",
"G_Espectro_senos_y_20.txt",
"G_Espectro_senos_y_30.txt",
"G_Espectro_senos_y_40.txt",
"G_Espectro_senos_y_50.txt",
"G_Espectro_senos_y_60.txt",
"G_Espectro_senos_y_70.txt",
"G_Espectro_senos_y_80.txt",
"G_Espectro_senos_y_90.txt",
"G_Espectro_senos_y_100.txt",
"G_Espectro_senos_y_110.txt",
"G_Espectro_senos_y_120.txt",
"G_Espectro_senos_y_130.txt",
"G_Espectro_senos_y_140.txt",
"G_Espectro_senos_y_150.txt",
"G_Espectro_senos_y_160.txt",
"G_Espectro_senos_y_170.txt",
"G_Espectro_senos_y_180.txt",
"G_Espectro_senos_y_190.txt",
"G_Espectro_senos_y_200.txt",
"G_Espectro_senos_y_210.txt",
"G_Espectro_senos_y_220.txt",
"G_Espectro_senos_y_230.txt",
"G_Espectro_senos_y_240.txt",
"G_Espectro_senos_y_250.txt",
"G_Espectro_senos_y_260.txt",
"G_Espectro_senos_y_270.txt",
"G_Espectro_senos_y_280.txt",
"G_Espectro_senos_y_290.txt",
"G_Espectro_senos_y_300.txt",
"G_Espectro_senos_z_1.txt",
"G_Espectro_senos_z_10.txt",
"G_Espectro_senos_z_20.txt",
"G_Espectro_senos_z_30.txt",
"G_Espectro_senos_z_40.txt",
"G_Espectro_senos_z_50.txt",
"G_Espectro_senos_z_60.txt",
"G_Espectro_senos_z_70.txt",
"G_Espectro_senos_z_80.txt",
"G_Espectro_senos_z_90.txt",
"G_Espectro_senos_z_100.txt",
"G_Espectro_senos_z_110.txt",
"G_Espectro_senos_z_120.txt",
"G_Espectro_senos_z_130.txt",
"G_Espectro_senos_z_140.txt",
"G_Espectro_senos_z_150.txt",
"G_Espectro_senos_z_160.txt",
"G_Espectro_senos_z_170.txt",
"G_Espectro_senos_z_180.txt",
"G_Espectro_senos_z_190.txt",
"G_Espectro_senos_z_200.txt",
"G_Espectro_senos_z_210.txt",
"G_Espectro_senos_z_220.txt",
"G_Espectro_senos_z_230.txt",
"G_Espectro_senos_z_240.txt",
"G_Espectro_senos_z_250.txt",
"G_Espectro_senos_z_260.txt",
"G_Espectro_senos_z_270.txt",
"G_Espectro_senos_z_280.txt",
"G_Espectro_senos_z_290.txt",
"G_Espectro_senos_z_300.txt"};


ofstream file;
ifstream file2;

int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch(Senal_de_entrada[vec], ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}



int main(){



if(todos_los_ejes==1){
eje=0;
cout << endl;
cout << "ALERTA: Se trabajará con todos los ejes" << endl;
cout << endl;
}

file.open("Instrucciones.gpl");

file << "set terminal pdf fontscale .4" << endl;

for(int contador=0; contador<=todos_los_ejes*2; contador++){

for(int i=1; i<=8; i++){

maxi[0]=0;
maxi[1]=0;
maxi[2]=0;
maxi[3]=0;

file << "set output \"4_espectros_" << S_C[SoC] << '_' << ejes[eje] << '_' << i << ".pdf\"" << endl;
file << "set multiplot" << endl;
file << "set size .5,.5" << endl;
file << "set origin 0,.5" << endl;

if(i==8) lim=2;
else lim=3;

for(int k=0; k<=lim; k++){

//Senal_de_entrada="G_Espectro_senos_x_240"; // Modo autovariable
file2.open(Senal_de_entrada[vec]);
file2.getline(a,100);

   for(int j=1; j<=N_de_lineas(); j++){
   
   file2.getline(a,20,' ');
   file2.getline(a,20);
   x=atof(a);
   if(x>maxi[k]) maxi[k]=x;
   }

file2.close();
vec++;
}

if(i==8){

file << "p[-0.1:3.2][0:" << maxi[0] + .1*maxi[0] << "] " << "'" << Senal_de_entrada[vec2] << "' " << "w i t '" << "Zig-zag " << S_C[SoC] << ' ' << ejes[eje] << ' ' << !(vec2-31*contador)+(vec2-31*contador)*10 << "'" << endl;
file << "set origin .5,.5" << endl;
vec2++;
file << "p[-0.1:3.2][0:" << maxi[1] + .1*maxi[1] << "] " << "'" << Senal_de_entrada[vec2] << "' " << "w i t '" << "Zig-zag " << S_C[SoC] << ' ' << ejes[eje] << ' ' << !(vec2-31*contador)+(vec2-31*contador)*10 << "'" << endl;
file << "set origin 0,0"  << endl;
vec2++;
file << "p[-0.1:3.2][0:" << maxi[2] + .1*maxi[2] << "] " << "'" << Senal_de_entrada[vec2] << "' " << "w i t '" << "Zig-zag " << S_C[SoC] << ' ' << ejes[eje] << ' ' << !(vec2-31*contador)+(vec2-31*contador)*10 << "'" << endl;
file << "set origin .5,0" << endl;
vec2++;
file << "unset multiplot" << endl;
file << "unset output" << endl;

}

else{

file << "p[-0.1:3.2][0:" << maxi[0] + .1*maxi[0] << "] " << "'" << Senal_de_entrada[vec2] << "' " << "w i t '" << "Zig-zag " << S_C[SoC] << ' ' << ejes[eje] << ' ' << !(vec2-31*contador)+(vec2-31*contador)*10 << "'" << endl;
file << "set origin .5,.5" << endl;
vec2++;
file << "p[-0.1:3.2][0:" << maxi[1] + .1*maxi[1] << "] " << "'" << Senal_de_entrada[vec2] << "' " << "w i t '" << "Zig-zag " << S_C[SoC] << ' ' << ejes[eje] << ' ' << !(vec2-31*contador)+(vec2-31*contador)*10 << "'" << endl;
file << "set origin 0,0"  << endl;
vec2++;
file << "p[-0.1:3.2][0:" << maxi[2] + .1*maxi[2] << "] " << "'" << Senal_de_entrada[vec2] << "' " << "w i t '" << "Zig-zag " << S_C[SoC] << ' ' << ejes[eje] << ' ' << !(vec2-31*contador)+(vec2-31*contador)*10 << "'" << endl;
file << "set origin .5,0" << endl;
vec2++;
file << "p[-0.1:3.2][0:" << maxi[3] + .1*maxi[3] << "] " << "'" << Senal_de_entrada[vec2] << "' " << "w i t '" << "Zig-zag " << S_C[SoC] << ' ' << ejes[eje] << ' ' << !(vec2-31*contador)+(vec2-31*contador)*10 << "'" << endl;
file << "unset multiplot" << endl;
file << "unset output" << endl;
vec2++;

}

}

eje++;

}

file.close();
return 0;

}




   
