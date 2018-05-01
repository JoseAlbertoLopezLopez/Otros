#include "Red_neuronal.h"



int main(){



//Fijar valores iniciales a los pesos y bias.

for(int k=0; k<=num_capas-1; k++){                  //Desde k=1 ya que los pesos de la primera capa no se usan.

   for(int i=0; i<=neuronas_por_capa[k]-1; i++){

      for(int j=0; j<=neuronas_por_capa[k-1]-1; j++){

      pesos[k][j][i]=valor_inicial_wkij();
      cout << pesos[k][j][i] << endl;
      }

   bias[k][i]=valor_inicial_bki();
   cout << bias[k][i] << endl;
   }
}

//Fijar las entradas como la primera capa de salidas.

for(int n=0; n<=num_entradas-1; n++){

   for (int i=0; i<=neuronas_por_capa[0]-1; i++){
   salida[n][0][i]=entrada[n][i];                             //El primer vector de salida son las entradas.
   }
}

//Cálculo de las salidas de capas intermedias para cada una de las entradas:  

int n=0; m=num_entradas;
while(m<=iteraciones+num_entradas){

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

//Cálculo de las derivadas de la función error con respecto a los pesos para la última capa:  
 
   for(int k=num_capas-1;k==num_capas-1;k++){

      for(int j=0; j<=neuronas_por_capa[k-1]-1; j++){

         for(int i=0; i<=neuronas_por_capa[k]-1; i++){

         dError1_dwkji(n,k,j,i);

         }
      }
   }

//Cálculo de las derivadas de la función error con respecto a los pesos y a los bias para las capas intermedias.  

   for(int k=num_capas-2; k>=1; k--){                  //Hasta k>=1 ya que los pesos de la primera capa no se usan.

      for(int j=0; j<=neuronas_por_capa[k-1]-1; j++){

         for(int i=0; i<=neuronas_por_capa[k]-1; i++){

         dError2_dwkji(n,k,j,i);

         }
      }
   }

//Actualización de los pesos y bias:

   for(int k=1; k<=num_capas-1; k++){                  //Desde k=1 ya que los pesos de la primera capa no se usan.

      for(int i=0; i<=neuronas_por_capa[k]-1; i++){

         for(int j=0; j<=neuronas_por_capa[k-1]-1; j++){

         pesos[k][j][i]=pesos[k][j][i]-alpha*dError_dwkji[k][j][i];
     
         }

      bias[k][i]=bias[k][i]-alpha*dError_dbki[k][i];

      }
   }

imprimir_salidas(imprimir_salida_n);

m++; n=int(m%num_entradas/4)+(num_entradas/4)*(m%4);  //MEJORAR 4

if(int(100*m/(iteraciones+num_entradas))>porcentaje){       //Imprime el prgreso de los cálculos del programa.
porcentaje=int(100*m/(iteraciones+num_entradas));
cout << int(100*m/(iteraciones+num_entradas)) << "%" << endl;
}

}


//Prueba de funcionamiento.

file1.open(archivo_salida);
file1.setf(ios::fixed);

for(int k=0; k<=num_capas-1; k++){                  //Hasta k>=1 ya que los pesos de la primera capa no se usan.

   for(int i=0; i<=neuronas_por_capa[k]-1; i++){

      for(int j=0; j<=neuronas_por_capa[k-1]-1; j++){

      if(k==0){
      file1 << "pesos[" << k << "][" << j << "][" << i << "]=" << 0 << ';' << endl;
      }
      else{
      file1 << "pesos[" << k << "][" << j << "][" << i << "]=" << pesos[k][j][i] << ';' << endl;
      }

      }
   file1 << "bias[" << k << "][" << i << "]=" << bias[k][i] << ';' << endl;
   }
}

for(int n=0; n<=num_entradas-1; n++){
   for(int i=0; i<=neuronas_por_capa[0]-1; i++){
   file1 << "salida[" << n << "][0][" << i << "]=" << salida[n][0][i] << ';' << endl;
   }
}

file1.close();

return 0;

}









