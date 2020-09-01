

double puntuacionInteraccion(int elemCentral, int elemVecino){

	if(elemCentral==elemVecino) return 0;
	
	if(elemCentral==1 and elemVecino==0){ 
		return 2.0;
	}
	if(elemCentral==1 and elemVecino==2){
		return 1.0;
	}
	
	if(elemCentral==2 and elemVecino==0){
		return 1.0;
	}
	if(elemCentral==2 and elemVecino==1){
		return 2.0;
	}
	
	if(elemCentral==0 and elemVecino==1){
		return 2.0;
	}
	if(elemCentral==0 and elemVecino==2){
		return 1.0;
	}
}


double puntajeElemento(int (&malla)[n+2][m+2], int r, int c){

	bool imposibleQ = false;
	double puntuacion=0;
	double libre1=0;
	double libre2=0;
	
	// Puntuación de interacciones y libertad.

	if(malla[r+1][c]<malla[r][c] and malla[r-1][c]<malla[r][c]){
	
		libre1 += puntuacionInteraccion(malla[r][c], malla[r+1][c]) + puntuacionInteraccion(malla[r][c], malla[r-1][c]);
		// Bono libertad.
		libre1 += 4;
	}
	
	if(malla[r][c+1]<malla[r][c] and malla[r][c-1]<malla[r][c]){
	
		libre2 += puntuacionInteraccion(malla[r][c], malla[r][c+1]) + puntuacionInteraccion(malla[r][c], malla[r][c-1]);
		// Bono libertad.
		libre2 += 4;
	}
	
	if(libre1==0 and libre2==0){
	
		puntuacion += puntuacionInteraccion(malla[r][c], malla[r][c+1]) + puntuacionInteraccion(malla[r][c], malla[r][c-1]);
		puntuacion += puntuacionInteraccion(malla[r][c], malla[r+1][c]) + puntuacionInteraccion(malla[r][c], malla[r-1][c]);
	}
	else{
		puntuacion += (libre1>=libre2 ? libre1 : libre2);
	}
	
	// Puntuación negativa de cuadros imposibles. Si pertenece a 1 o más cuadros imposibles, restar la misma puntuación.
	
	if(!imposibleQ and ((malla[r][c]==malla[r][c-1] and malla[r][c]==malla[r-1][c-1]) and (malla[r][c]==malla[r-1][c] and malla[r][c]>0))){
		puntuacion -= 2.0; imposibleQ = true;}
	if(!imposibleQ and ((malla[r][c]==malla[r][c+1] and malla[r][c]==malla[r-1][c+1]) and (malla[r][c]==malla[r-1][c] and malla[r][c]>0))){
		puntuacion -= 2.0; imposibleQ = true;}
	if(!imposibleQ and ((malla[r][c]==malla[r][c+1] and malla[r][c]==malla[r+1][c+1]) and (malla[r][c]==malla[r+1][c] and malla[r][c]>0))){
		puntuacion -= 2.0; imposibleQ = true;}
	if(!imposibleQ and ((malla[r][c]==malla[r][c-1] and malla[r][c]==malla[r+1][c-1]) and (malla[r][c]==malla[r+1][c] and malla[r][c]>0))){
		puntuacion -= 2.0; imposibleQ = true;}
	
	return puntuacion;
}


double puntajeMalla(int (&malla)[n+2][m+2], double (&mallasPuntajes)[n+2][m+2]){

	double puntaje = 0.0;
	double puntajeAux;

	for(int i=1; i<=n; i++){
	
		for(int j=1; j<=m; j++){

			puntajeAux = puntajeElemento(malla, i, j);
			puntaje += puntajeAux;
			mallasPuntajes[i][j] = puntajeAux;
		}
	}
	
	return puntaje;
}


int rand_n1=0;
int rand_m1=0;
int rand_n2=0;
int rand_m2=0;
int elemAux;
void cambiosAleatorios(int cambios, int (&malla)[n+2][m+2]){

	for(int i=1; i<=cambios; i++){
	
		do{
			rand_n1 = 1+rand()%n;
			rand_m1 = 1+rand()%m;
			rand_n2 = 1+rand()%n;
			rand_m2 = 1+rand()%m;
		}
		while(malla[rand_n1][rand_m1] == malla[rand_n2][rand_m2]);
		
		elemAux = malla[rand_n1][rand_m1];
		malla[rand_n1][rand_m1] = malla[rand_n2][rand_m2];
		malla[rand_n2][rand_m2] = elemAux;
	}
}


void copiarMalla(int (&original)[n+2][m+2], int (&copia)[n+2][m+2]){

	for(int i=0; i<=n+1; i++) copy(original[i], original[i] + m+2, copia[i]);
}


bool ordenamiento(array<double, 2> &i, array<double, 2> &j){
	
	return i[0]>j[0];
}


void ordenarPoblacion(){

	sort(puntajesPoblacion.begin(), puntajesPoblacion.end(), ordenamiento);
	
	for(int i=0; i<=poblacion+descendencia-1; i++){
	
		copiarMalla(mallas[(int) puntajesPoblacion[i][1]], mallasAux[i]);
		puntajesPoblacion[i][1]=i;
	}
	
	for(int i=0; i<=poblacion+descendencia-1; i++){
	
		copiarMalla(mallasAux[i], mallas[i]);
	}
}


void crearIntervalos(){

	double suma = 0.0;
	intervalos[0] = 0.0;

	for(int i=1; i<=poblacion; i++){
		
		suma += 1.0*puntajesPoblacion[i-1][0]/(1.0*sumaPuntajes);
		intervalos[i] = suma;
	}
}


void escogerPadres(){

	crearIntervalos();
	
	for(int j=0; j<=parejas*2-1; j++){
	
		aleatorio = (double) rand()/(RAND_MAX);

		for(int i=1; i<=poblacion; i++){
	
			if(aleatorio >= intervalos[i-1] and aleatorio < intervalos[i]){
		
				indicesPadres[j] = i-1;
			}
		}
	}
}


int indice_1;
int indice_2;
void escogerPadres2(){

	for(int i=0; i<=parejas*2-1; i++){
	
		indice_1 = rand()%poblacion;
		indice_2 = rand()%poblacion;
		
		if(puntajesPoblacion[indice_1][0] < puntajesPoblacion[indice_2][0]){
		
			indicesPadres[i] = indice_2;
		}
		else{
		
			indicesPadres[i] = indice_1;
		}
	}
}
void imprimirVectorMatriz(int (&mat)[n+2][m+2], int n, int m){
	                            
	for(int i=0; i<=n+1; i++){

		for(int j=0; j<=m+1; j++){
   
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}   
	cout << endl;    
}

int indiceHijo;
void recombinacion_mutacion(){

	indiceHijo = 0;

	for(int i=1; i<=parejas; i++){
	
		for(int l=1; l<=hijosPorPareja; l++){
		
			sinColocarAux = sinColocar;
			noColocados.clear();
			
			if((double) rand()/(RAND_MAX) < 0.5){
	
			for(int j=1; j<=n; j++){
		
				for(int k=1; k<=m; k++){
			
					if(((double) rand()/(RAND_MAX)) < 1.0*puntajesMallas[2*i-2][j][k]/(1.0*(puntajesMallas[2*i-2][j][k]+puntajesMallas[2*i-1][j][k]))){ // 1.0*puntajesPoblacion[indicesPadres[2*i-2]][0]/(1.0*(puntajesPoblacion[indicesPadres[2*i-2]][0]+puntajesPoblacion[indicesPadres[2*i-1]][0]))
				
						if(sinColocarAux[mallas[indicesPadres[2*i-2]][j][k]] > 0){
							mallas[poblacion + indiceHijo][j][k] = mallas[indicesPadres[2*i-2]][j][k];
							sinColocarAux[mallas[indicesPadres[2*i-2]][j][k]]--;
						}
						else{ mallas[poblacion + indiceHijo][j][k] = -1; noColocados.push_back({j,k}); }
					}
					else{
					
						if(sinColocarAux[mallas[indicesPadres[2*i-1]][j][k]] > 0){
							mallas[poblacion + indiceHijo][j][k] = mallas[indicesPadres[2*i-1]][j][k];
							sinColocarAux[mallas[indicesPadres[2*i-1]][j][k]]--;
						}
						else{ mallas[poblacion + indiceHijo][j][k] = -1; noColocados.push_back({j,k}); }
					}
				}
			}
			}else{
			
			for(int j=n; j>=1; j--){
		
				for(int k=m; k>=1; k--){
			
					if(((double) rand()/(RAND_MAX)) < 1.0*puntajesMallas[2*i-2][j][k]/(1.0*(puntajesMallas[2*i-2][j][k]+puntajesMallas[2*i-1][j][k]))){
				
						if(sinColocarAux[mallas[indicesPadres[2*i-2]][j][k]] > 0){
							mallas[poblacion + indiceHijo][j][k] = mallas[indicesPadres[2*i-2]][j][k];
							sinColocarAux[mallas[indicesPadres[2*i-2]][j][k]]--;
						}
						else{ mallas[poblacion + indiceHijo][j][k] = -1; noColocados.push_back({j,k}); }
					}
					else{
					
						if(sinColocarAux[mallas[indicesPadres[2*i-1]][j][k]] > 0){
							mallas[poblacion + indiceHijo][j][k] = mallas[indicesPadres[2*i-1]][j][k];
							sinColocarAux[mallas[indicesPadres[2*i-1]][j][k]]--;
						}
						else{ mallas[poblacion + indiceHijo][j][k] = -1; noColocados.push_back({j,k}); }
					}
				}
			}
			}
			
			for(auto &coord:noColocados){

				for(int i=0; i<=numClases; i++){
					if(sinColocarAux[i]>0){
						mallas[poblacion + indiceHijo][coord[0]][coord[1]] = i; break;
					}
				}
			}
			
			// Mutación.
			
			if(((double) rand()/(RAND_MAX)) < probMutacion and generacionActual>0){
			
				aux3 = rand()%(poblacion+descendencia);
				for(int i=1; i<=cambiosMutacion; i++){
					do{
						rand_n1 = 1+rand()%n;
						rand_m1 = 1+rand()%m;
						rand_n2 = 1+rand()%n;
						rand_m2 = 1+rand()%m;
					}
					while(mallas[aux3][rand_n1][rand_m1] == mallas[aux3][rand_n2][rand_m2]);
			
					aux = mallas[aux3][rand_n1][rand_m1];
					mallas[aux3][rand_n1][rand_m1] = mallas[aux3][rand_n2][rand_m2];
					mallas[aux3][rand_n2][rand_m2] = aux;
				}
				
				puntajesPoblacion[aux3][0] = puntajeMalla(mallas[aux3], puntajesMallas[aux3]);
			}
			
			puntajesPoblacion[poblacion + indiceHijo][0] = puntajeMalla(mallas[poblacion + indiceHijo], puntajesMallas[poblacion + indiceHijo]);
			puntajesPoblacion[poblacion + indiceHijo][1] = poblacion + indiceHijo;
			
			indiceHijo++;
		}
	}
}


int pivote_n;
int pivote_m;
bool pivoteAlcanzado;
int indicePadre1;
int indicePadre2;
void recombinacion_mutacion2(){

	indiceHijo = 0;

	for(int i=1; i<=parejas; i++){
	
		for(int l=1; l<=hijosPorPareja; l++){
		
			sinColocarAux = sinColocar;
			noColocados.clear();
			
			pivote_n = 1+rand()%n;
			pivote_m = 1+rand()%m;
			
			if(l%2==0){ indicePadre1=2*i-2; indicePadre2=2*i-1; }
			else{ indicePadre1=2*i-1; indicePadre2=2*i-2; }
			
			if(((double) rand()/(RAND_MAX)) < 0.5){
			
			pivoteAlcanzado = false;
	
			for(int j=1; j<=n; j++){
		
				if(pivoteAlcanzado) break;
		
				for(int k=1; k<=m; k++){
			
					if(sinColocarAux[mallas[indicesPadres[indicePadre1]][j][k]] > 0){
						mallas[poblacion + indiceHijo][j][k] = mallas[indicesPadres[indicePadre1]][j][k];
						sinColocarAux[mallas[indicesPadres[indicePadre1]][j][k]]--;
					}
					else{ mallas[poblacion + indiceHijo][j][k] = -1; noColocados.push_back({j,k}); }
					
					if(j==pivote_n and k==pivote_m){ pivoteAlcanzado = true; break; }
				}
			}
			
			pivoteAlcanzado = false;
			
			for(int j=n; j>=1; j--){
				
				if(pivoteAlcanzado) break;
				
				for(int k=m; k>=1; k--){
				
					if(j==pivote_n and k==pivote_m){ pivoteAlcanzado = true; break; }
			
					if(sinColocarAux[mallas[indicesPadres[indicePadre2]][j][k]] > 0){
						mallas[poblacion + indiceHijo][j][k] = mallas[indicesPadres[indicePadre2]][j][k];
						sinColocarAux[mallas[indicesPadres[indicePadre2]][j][k]]--;
					}
					else{ mallas[poblacion + indiceHijo][j][k] = -1; noColocados.push_back({j,k}); }
				}
			}
			}else{
			
			pivoteAlcanzado = false;
			
			for(int j=n; j>=1; j--){
				
				if(pivoteAlcanzado) break;
				
				for(int k=m; k>=1; k--){
				
					if(j==pivote_n and k==pivote_m){ pivoteAlcanzado = true; break; }
			
					if(sinColocarAux[mallas[indicesPadres[indicePadre2]][j][k]] > 0){
						mallas[poblacion + indiceHijo][j][k] = mallas[indicesPadres[indicePadre2]][j][k];
						sinColocarAux[mallas[indicesPadres[indicePadre2]][j][k]]--;
					}
					else{ mallas[poblacion + indiceHijo][j][k] = -1; noColocados.push_back({j,k}); }
				}
			}
			
			pivoteAlcanzado = false;
	
			for(int j=1; j<=n; j++){
		
				if(pivoteAlcanzado) break;
		
				for(int k=1; k<=m; k++){
			
					if(sinColocarAux[mallas[indicesPadres[indicePadre1]][j][k]] > 0){
						mallas[poblacion + indiceHijo][j][k] = mallas[indicesPadres[indicePadre1]][j][k];
						sinColocarAux[mallas[indicesPadres[indicePadre1]][j][k]]--;
					}
					else{ mallas[poblacion + indiceHijo][j][k] = -1; noColocados.push_back({j,k}); }
					
					if(j==pivote_n and k==pivote_m){ pivoteAlcanzado = true; break; }
				}
			}
			}
			
			for(auto &coord:noColocados){
			
				for(int i=0; i<=numClases; i++){
					if(sinColocarAux[i]>0){
						mallas[poblacion + indiceHijo][coord[0]][coord[1]] = i; break;
					}
				}
			}
			
			// Mutación.
			
			if(((double) rand()/(RAND_MAX)) < probMutacion and generacionActual>0){
			
				aux3 = rand()%(poblacion+descendencia);
				for(int i=1; i<=cambiosMutacion; i++){
					do{
						rand_n1 = 1+rand()%n;
						rand_m1 = 1+rand()%m;
						rand_n2 = 1+rand()%n;
						rand_m2 = 1+rand()%m;
					}
					while(mallas[aux3][rand_n1][rand_m1] == mallas[aux3][rand_n2][rand_m2]);
			
					aux = mallas[aux3][rand_n1][rand_m1];
					mallas[aux3][rand_n1][rand_m1] = mallas[aux3][rand_n2][rand_m2];
					mallas[aux3][rand_n2][rand_m2] = aux;
				}
				
				puntajesPoblacion[aux3][0] = puntajeMalla(mallas[aux3], puntajesMallas[aux3]);
			}
			
			puntajesPoblacion[poblacion + indiceHijo][0] = puntajeMalla(mallas[poblacion + indiceHijo], puntajesMallas[poblacion + indiceHijo]);
			puntajesPoblacion[poblacion + indiceHijo][1] = poblacion + indiceHijo;
			
			indiceHijo++;
		}
	}
}



void seleccion(){

	// Ordenar población y descendencia según su puntuación.
	ordenarPoblacion();

	sumaPuntajes = 0.0;

	for(int i=0; i<=poblacion-1; i++) sumaPuntajes += puntajesPoblacion[i][0];
}


void imprimirVecindad(array<int, 4> &vecindad){

	cout << "  " << vecindad[0] << endl;
	cout << vecindad[3] << "   " << vecindad[1] << endl;
	cout << "  " << vecindad[2] << endl << endl;
}




void imprimirVectorMatriz2(double (&mat)[n][m], int n, int m){
	                            
	for(int i=0; i<=n-1; i++){

		for(int j=0; j<=m-1; j++){
   
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}   
	cout << endl;    
}
