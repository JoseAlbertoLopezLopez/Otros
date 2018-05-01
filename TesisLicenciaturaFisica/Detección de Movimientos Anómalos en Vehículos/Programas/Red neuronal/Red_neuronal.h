#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
#include <cstdlib>
using namespace std;

const int num_entradas = 24;
const int num_capas=3;
const int max_n_capa = 4;
int neuronas_por_capa[num_capas]={3,4,3};

//Prueba_red_neuronal////////////////////////////////////////////////////////////////////////////////////////////

double alpha = 10.0;                        //Momentum

char archivo_salida[50] = "Pesos_red_neuronal.h";

int imprimir_salida_n=-1;                   // 0 <= n <= num_entradas -1, -1: Desactivado.
int iteraciones = 1000000;

double entrada[num_entradas][3]={{0.523602,2.398338,0.022881},
                                 {1.937878,1.136229,0.029787},
                                 {1.229727,1.587049,0.046849},
                                 {3.052422,0.694677,0.018856},
                                 {2.969470,1.661595,0.020685},
                                 {3.439653,0.940884,0.029936},
                                 {0.317252,0.559695,0.177542}, 
                                 {0.993314,0.322509,0.014052},
                                 {0.424887,0.647418,0.115961},
                                 {1.032852,0.262589,0.314044},
                                 {1.653561,0.014462,0.043891},
                                 {1.105726,0.018746,0.168486},
                                 {0.155248,0.072942,0.855960},
                                 {0.104593,0.013917,2.107660},
                                 {0.025101,0.124063,0.576754},
                                 {0.154532,0.019824,3.659537},
                                 {0.046990,0.076746,2.559510},
                                 {0.020204,0.069771,4.159607},
                                 {0.123390,0.048497,0.097252},
                                 {0.032765,0.053693,0.008537},
                                 {0.517879,0.082361,0.030586},
                                 {0.085696,0.090114,0.085132},
                                 {0.066895,0.068510,0.024082},
                                 {0.163739,0.102261,0.006494}};   

double salida_deseada[4][3]={{1.0,0.0,0.0},
                             {0.0,1.0,0.0},
                             {0.0,0.0,1.0},
                             {0.0,0.0,0.0}}; 

double valor_inicial_bki(){
return (rand()%100)/100.0;
}

double valor_inicial_wkij(){
return (rand()%100)/100.0;
}


//Red_neuronal###################################################################################################

double beta = 0.2;                         //Tasa de aprendizaje
double ecmo = 0.00001;                     //Error cuadrático medio objetivo.     
double salida[num_entradas][num_capas][max_n_capa];                //Salida para cada neurona ([capa][neurona]), la capa 0 son las entradas.
double dError_dwkji[num_capas][max_n_capa][max_n_capa]={0};                 //Delta del error para cada peso.
double dError_dbki[num_capas][max_n_capa]={0};
double delta_ki[num_entradas][num_capas][max_n_capa]={0};              //Error delta para cada neurona.
//1
double pesos[num_capas][max_n_capa][max_n_capa];                      //Pesos para cada neurona, los pesos de la primera capa no se utilizan ya que son de las entradas.
//2
double bias[num_capas][max_n_capa];                          //bias para el nodo i en la capa k.   
//3
double a_ki[num_entradas][num_capas][max_n_capa];

int m;                  //Variable para iteraciones.
int porcentaje = 0;

ofstream file1;
//4
double sigmoide(double a){
//if(a<-500) return 0.0;
return 1.0/(1.0+exp(-a));
}

double dsigmoide_daki(double a){
if(a<-500) return 0.0;
return exp(-a)/((1.0+exp(-a))*(1.0+exp(-a)));
}
//5
double a_k_i(int n, int k, int i){                      //Producto vectorial + bias para la neurona i de la capa k.

a_ki[n][k][i]=0;

   for(int j=0; j<=neuronas_por_capa[k-1]-1; j++){
   a_ki[n][k][i]+=pesos[k][j][i]*salida[n][k-1][j];
   }

a_ki[n][k][i]+=bias[k][i];
return a_ki[n][k][i];
}

void dError1_dwkji(int n,int k, int j, int i){  //Esta función encuentra dError/dwkji solo para 1 neurona de la capa final.
dError_dwkji[k][j][i]=0.0;  
dError_dbki[k][i]=0.0;  
double sum1=0;

delta_ki[n][k][i]=(sigmoide(a_ki[n][k][i])-salida_deseada[int(n/6)][i])*dsigmoide_daki(a_ki[n][k][i]);    //6?
//cin.ignore().get();
sum1+=delta_ki[n][k][i];
dError_dwkji[k][j][i]+=(1.0/num_entradas)*(salida[n][k-1][j])*sum1;  
dError_dbki[k][i]+=(1.0/num_entradas)*sum1;                             //Aportación del bias.
}

void dError2_dwkji(int n, int k, int j, int i){              //Esta función encuentra dError/dwkji solo para 1 neurona.
dError_dwkji[k][j][i]=0.0;  
dError_dbki[k][i]=0.0;  
double sum2=0;

delta_ki[n][k][i]=0.0;

   for(int c1=0; c1<=neuronas_por_capa[k+1]-1; c1++){
   delta_ki[n][k][i]+=delta_ki[n][k+1][c1]*dsigmoide_daki(a_ki[n][k][i])*pesos[k+1][i][c1];
   }

sum2+=delta_ki[n][k][i];                     //MEJORAR
dError_dwkji[k][j][i]+=(1.0/num_entradas)*(salida[n][k-1][j])*sum2;  
dError_dbki[k][i]+=(1.0/num_entradas)*sum2;                             //Aportación del bias.
}

void imprimir_salidas(int imprimir_salida_n){
if(m%100==0 and imprimir_salida_n>-1){
cout << dError_dwkji[num_capas-1][0][0] << ',' << dError_dbki[num_capas-1][0] << endl;
cout << salida[imprimir_salida_n][num_capas-1][0] << endl; 
cout << salida[imprimir_salida_n][num_capas-1][1] << endl;
cout << salida[imprimir_salida_n][num_capas-1][2] << endl;
cout << "" << endl;
}
}

//Prueba_red_neuronal

int entrada_original_o_manual;

int mostrar_salida(int n, int entrada_original_o_manual){
if(n==-1)goto exit;
if(entrada_original_o_manual==0){
cout << salida[n][num_capas-1][0] << endl;
cout << salida[n][num_capas-1][1] << endl;
cout << salida[n][num_capas-1][2] << endl;
cout << endl;
}
else{
cout << salida[0][num_capas-1][0] << endl;
cout << salida[0][num_capas-1][1] << endl;
cout << salida[0][num_capas-1][2] << endl;
cout << endl;
}
exit:;
}

//1,2,3,4,5













