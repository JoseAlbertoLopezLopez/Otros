#include <iostream>     // cout
#include <fstream> 
#include <string.h>
#include <sstream>

using namespace std;


ifstream leerCaso;
ofstream archivoFinal;





int main(){





archivoFinal.open("EvaluacionMallas.txt", ios::binary);


leerCaso.open("EvaluacionMallas1.txt", ios::binary);
archivoFinal << leerCaso.rdbuf();
leerCaso.close();

leerCaso.open("EvaluacionMallas2.txt", ios::binary);
archivoFinal << leerCaso.rdbuf();
leerCaso.close();

leerCaso.open("EvaluacionMallas3.txt", ios::binary);
archivoFinal << leerCaso.rdbuf();
leerCaso.close();

leerCaso.open("EvaluacionMallas4.txt", ios::binary);
archivoFinal << leerCaso.rdbuf();
leerCaso.close();


archivoFinal.close();


return 0;
}
