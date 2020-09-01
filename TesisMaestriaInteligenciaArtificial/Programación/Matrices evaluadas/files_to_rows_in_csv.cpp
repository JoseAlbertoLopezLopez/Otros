#include <iostream>
#include <string.h>
#include <dirent.h>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

string directorio = "/home/j6/Desktop/Tesis/Programación/Matrices evaluadas/";
vector<string> listaArchivos;

vector<string> nombresArchivos(string path = ".") {

    DIR* dir;
    dirent* pdir;
    std::vector<std::string> files;
    int n = 1;
    dir = opendir(path.c_str());

    cout << "Obteniendo nombres de los archivos." << endl;
    while (pdir = readdir(dir)) {
        if (pdir->d_type != DT_DIR) {
            if (n % 10000 == 0) cout << n << endl;
            files.push_back(pdir->d_name);
            n++;
        }
    }

    return files;
}

string first_number_string(string const & str) {
    char const* digits = "0123456789";
    size_t const n = str.find_first_of(digits);

    if (n != string::npos) {
        size_t const m = str.find_first_not_of(digits, n);
        return str.substr(n, m != string::npos ? m-n : m);
    }

    return string();
}


int main(int argc, char const *argv[]) {

    listaArchivos = nombresArchivos(directorio);

    ofstream base_de_datos;
    base_de_datos.open("matrices_evaluadas.csv", ios::app);

    time_t t1;
	time_t t2;
	time(&t1);

    int n = 4125265;
    string archivo;
    cout << "Construyendo base de datos." << endl;
    //base_de_datos << "Archivo,Datos" << endl;
    for (int i = 4125265; i < listaArchivos.size(); i++) {
        archivo = listaArchivos[i];
        
        if (n % 10000 == 0) {
            time(&t2);
            double t = double(t2 - t1);
            cout << n;
            cout << "  Tiempo transcurrido: " << t << "s." << endl;
            time(&t1);
        }
        ifstream archivo_txt(directorio + archivo, ios::in);
        char linea[64];

        base_de_datos << first_number_string(archivo) + ",\"";

        while (archivo_txt.good()) {
            archivo_txt.getline(linea, 64);
            base_de_datos << linea << 'n';
        }

        base_de_datos << "\"\n";
        archivo_txt.close();
        n++;
    }

    base_de_datos.close();

    return 0;
}