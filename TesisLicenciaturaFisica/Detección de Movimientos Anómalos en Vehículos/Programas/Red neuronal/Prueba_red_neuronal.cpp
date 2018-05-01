#include "Red_neuronal.h"



int main(){



#include "Pesos_red_neuronal.h"

cout << "¿Desea entradas originales o nuevas? (0->Originales, 1->nuevas, -1->salir)" << endl;
cin >> entrada_original_o_manual;

while(1==1){

if(entrada_original_o_manual==1){
cout << "Introduzca entradas:" << endl;
cout << "salida[0][0][0] = ";
cin >> salida[0][0][0];
cout << "salida[0][0][1] = ";
cin >> salida[0][0][1];
cout << "salida[0][0][2] = ";
cin >> salida[0][0][2];
}

for(int n=0; n<=num_entradas-1; n++){

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

int n;

while(entrada_original_o_manual==0){
cout << "Introduzca número de salida (-1 -> salir)." << endl;
cin >> n;
mostrar_salida(n,entrada_original_o_manual);
if(n==-1) break;
}

if(entrada_original_o_manual!=0){
mostrar_salida(n,entrada_original_o_manual);
}

cin >> entrada_original_o_manual;

if(entrada_original_o_manual==-1) break;

}

return 0;

}
