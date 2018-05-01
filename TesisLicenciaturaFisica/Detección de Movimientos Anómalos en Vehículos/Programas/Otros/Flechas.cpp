/*Este programa sirve para graficar una serie de flechas y puntos con el programa Gnuplot mediante el archivo de 
salida que se genera*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;


ofstream file_0;

double long_flecha=5;
double long_linea=14;
double punto_inicio=15;
double punto_final=219;



int main(){



file_0.open("Flechas.gpl");

file_0 << "set arrow from 0,115 to 15,115 nohead lw 3 dt 3 front; set arrow from 15,115 to 15,142.5 nohead lw 3 dt 3 front; set arrow from 15,142.5 to 0,142.5 nohead lw 3 dt 3 front; set arrow from 0,142.5 to 0,115 nohead lw 3 dt 3 front;" << endl;
file_0 << "set arrow from 219,115 to 234,115 nohead lw 3 front; set arrow from 234,115 to 234,142.5 nohead lw 3 front; set arrow from 234,142.5 to 219,142.5 nohead lw 3 front; set arrow from 219,142.5 to 219,115 nohead lw 3 front;" << endl;

for(int i=punto_inicio; i<=punto_final; i+=long_flecha+long_linea){
file_0 << "set arrow from " << i << ",142.5 to " << i+long_flecha << ",142.5 lw 2 filled;" << endl;
file_0 << "set arrow from " << i+long_flecha << ",142.5 to " << i+long_flecha+long_linea << ",142.5 lw 2 dt 2 nohead;" << endl;

//file_0 << "set arrow from " << i << ",128.75 to " << i+long_flecha << ",128.75 lw 2 filled;" << endl;
//file_0 << "set arrow from " << i+long_flecha << ",128.75 to " << i+long_flecha+long_linea << ",128.75 lw 2 dt 2 nohead;" << endl;

file_0 << "set arrow from " << i << ",115 to " << i+long_flecha << ",115 lw 2 filled;" << endl;
file_0 << "set arrow from " << i+long_flecha << ",115 to " << i+long_flecha+long_linea << ",115 lw 2 dt 2 nohead;" << endl;


}

return 0;

}



