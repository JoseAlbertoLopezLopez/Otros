/* Este programa genera un archivo llamado "datos.txt" con datos de una función matemática en x, y & z 
en función del tiempo.*/


#include "libreria.h"


x = 2.23*cos(2.*M_PI*(6.*n/240))+2.*cos(2.*M_PI*(120.*n/240))+8.444444444*cos(2.*M_PI*(0.*n/240))+4.5*sin(2.*M_PI*(70.5*n/240));
y = 0.0;
z = 0.0;



int main(){



//Formato de aplicación de celular

ofstream file("datos.txt");

file << "time" << "," << 'x' << "," << 'y' << "," << 'z' << endl;

for(int n=0; n<=N-1; n++){
file << n << "," << x << "," << y << "," << z << endl;
}

/*
//Formato de gráfica de Gnuplot

ofstream file("datos.txt");

for(int n=0; n<=N-1; n++){
file << n << " " << x << " " << y << " " << z << endl;
}
*/

return 0;

}


