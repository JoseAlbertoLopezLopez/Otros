#include "libreria.h"



int main(){  



cout << "¿Desea restar las frecuencias a la señal original? (y:sí, n:no)" << endl;
cin >> opcion;

if(todos_los_ejes==1){
eje=1;
cout << endl;
cout << "ALERTA: Se trabajará con todos los ejes" << endl;
cout << endl;
}

for(int c2=1; c2 <= N_de_senales; c2++){

if(N_de_senales>1){                                
eje=eje*(!todos_los_ejes)+todos_los_ejes;          //Reiniciar la variable de los ejes cada vez que se cambie de archivo de datos

itoa((c2-1)*5);

strcpy(Senal_de_entrada, (Senal_de_entrada_fija1 + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(coeficientes[0], ("coeficientes_x_" + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(coeficientes[1], ("coeficientes_y_" + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(coeficientes[2], ("coeficientes_z_" + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(datos_sin_ruido[0], ("datos_sin_ruido_x_" + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(datos_sin_ruido[1], ("datos_sin_ruido_y_" + i_to_s + Senal_de_entrada_fija2).c_str());
strcpy(datos_sin_ruido[2], ("datos_sin_ruido_z_" + i_to_s + Senal_de_entrada_fija2).c_str());

discretizacion = N_de_lineas()-1;
w = complex<double>(0.,(-2.*M_PI)/discretizacion);      //Argumento de la exponencial compleja de la fórmula
e = exp(w);
N = N_de_lineas() - 1;                                 //Número de datos
cout << c2 << endl;
}

file2.open("datos2.txt",ios::out | ios::trunc);        

espejo();

for(int contador=0; contador<=todos_los_ejes*2; contador++){

file2.open("datos2.txt");
file3.open(coeficientes[eje-1]);
file3.setf(ios::fixed);                   // VERIFICAR.           

for (k=0; k<=(discretizacion/2)-1; k++){              //Para cada k hay un par de coeficientes Ckx & Ckx_ (su simétrico)

//file2.getline(a, 32);                  //Saltar la línea de título

Ckx = complex<double>(0.,0.);
Ckx_ = complex<double>(0.,0.);

Aceleraciones(a);                                             
Cix = xyzt[eje-1];
Aceleraciones(a);                                             
Cpx = xyzt[eje-1]; 

    for(int i=N/2; i>1; i--){           //Bucle que calcula la sumatoria de cada dato multiplicada por su correspondiente exponencial.

    Aceleraciones(a);                                             
    Cix *= m*m;
    Cix += xyzt[eje-1];
   
    Aceleraciones(a);                                             
    Cpx *= m*m;
    Cpx += xyzt[eje-1];  
    }

Ckx = Cpx + m*Cix;                                        //Coeficientes pares e impares sumados
Ckx_ = Cpx - m*Cix;                                       //En el primer cálculo si calcula el correspondiente a N/2 (frec. max.)

if (abs(real((1./N)*Ckx)) < filtro_amplitud) real(Ckx) = 0.;       //Si el valor absoluto es muy pequeño volverlo 0
if (abs(imag((1./N)*Ckx)) < filtro_amplitud) imag(Ckx) = 0.;
if (abs(real((1./N)*Ckx_)) < filtro_amplitud) real(Ckx_) = 0.;
if (abs(imag((1./N)*Ckx_)) < filtro_amplitud) imag(Ckx_) = 0.;

file3 << (1./N)*Ckx << "," << (1./N)*Ckx_ << endl;        //Escribe  los coeficientes en un archivo 
m *= e;
file2.seekp(0, ios::beg);                                 //Volver a colocar lector al inicio del archivo
};

file2.close();
file3.close();



//Empieza código para resta de frecuencias ######################################################################



if(opcion == 'y'){
file5.open(Senal_de_entrada);
file6.open(coeficientes[eje-1]);
file7.open(coeficientes[eje-1]);
file4.open(datos_sin_ruido[eje-1]);
//file4.setf(ios::fixed);  
int d = N_de_lineasC();

file4 << "time" << "," << 'x' << "," << 'y' << "," << 'z' << endl;
file5.getline(a, 99); 

for(int j=0; j<=N-1; j++){                 //Bucle que recorre todos los puntos de la gráfica

Aceleraciones2(a);

file6.getline(a, 99); 
file7.getline(a, 99); 
   
   for(int k=1; k <= d - 1; k++){        //Bucle que resta todas las frecuencias a un punto de la gráfica
   Leer_amplitudes_s(a);
   Leer_amplitudes_c(a);
//   if(abs(ASx)>0.000145887 or abs(ACx)>0.000145887){      //Filtro (si la amplitud es mayor a un número arbitrario)
   x2 += 2.*(-ASx*sin(2.*M_PI*(1.*k*j/(2.*d))) + ACx*cos(2.*M_PI*(1.*k*j/(2.*d)))); 
   }
//   }

file7.seekp(0, ios::beg);            //Sumar contribución de frecuencia con k=0
file7.getline(a, 100, '(');
file7.getline(a, 100, ',');
ACx = 1.*atof(a);
//if(abs(ACx)>0.002){               //Filtro (si la amplitud es mayor a un número arbitrario)
x2 += 1.*ACx;
//}


file7.seekp(0, ios::beg);            //Sumar contribución de frecuencia con k=N/2
file7.getline(a, 100, '(');
file7.getline(a, 100, '(');
file7.getline(a, 100, ',');
ACx = 1.*atof(a);
//if(abs(ACx)>0.000145887){           //Filtro (si la amplitud es mayor a un número arbitrario)    
x2 += ACx*cos(M_PI*1.*j);
//}

if(abs(xyzt[eje-1] - x2)<1e-4){               //Si la resta es muy pequeña hacerla 0
file4 << a2 << " " << 0 << endl;
}

else {
file4 << a2 << " " << xyzt[eje-1] - x2 << endl;
}

x2 = 0.0;
file6.seekp(0, ios::beg);           //Volver al inicio del archivo
file7.seekp(0, ios::beg);

}

file6.close();
file7.close();
file5.close();
file4.close();

}

m = complex<double>(1.,0.); 
eje++;

}

}

/* Si el numero de frecuencias que se tienen es menor que el número maximo, al hacer la resta no quedará 0 a 
menos que la señal se componga de multiplos enteros de la frecuencia maxima.*/

/*Declarar los ficheros siempre sin argumentos, luego usar la función .open() con el nombre que se deseé, 
cerrarlo al final con .close(), y si se desea abrir otro volver a usar .open() con el nuevo argumento.*/

return 0;

}










