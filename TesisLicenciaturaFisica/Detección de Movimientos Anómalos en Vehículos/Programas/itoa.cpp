#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

std::string i_to_s;
std::stringstream canal_string;

string c = "Hola";
string d = " ";
string e = "tu";

void itoa(int x){
//std::stringstream canal_string;
canal_string << x;
i_to_s = canal_string.str();
canal_string.flush();
}



int main(){


itoa(12321);

cout << i_to_s << endl;
cout << c+d+e+i_to_s << endl;
//cout << "co"+"oc" << endl; //Error
canal_string.clear();
itoa(76849);

cout << i_to_s << endl;
cout << c+d+e+i_to_s << endl;

//IMPORTANTE: Documentar caracteristicas del operador + para strings.

return 0;

}
