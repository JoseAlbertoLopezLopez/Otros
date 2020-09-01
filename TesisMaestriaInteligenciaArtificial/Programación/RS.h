

double puntuacionInteraccion(int elemCentral, int elemVecino){

	if(elemCentral==elemVecino) return 0;
	
	if(elemCentral==1 and elemVecino==0){ 
		return 3.0;
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
		libre1 += 3;
	}
	
	if(malla[r][c+1]<malla[r][c] and malla[r][c-1]<malla[r][c]){
	
		libre2 += puntuacionInteraccion(malla[r][c], malla[r][c+1]) + puntuacionInteraccion(malla[r][c], malla[r][c-1]);
		// Bono libertad.
		libre2 += 3;
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



double puntajeMalla(int (&malla)[n+2][m+2]){

	double puntaje = 0.0;

	for(int i=1; i<=n; i++){
	
		for(int j=1; j<=m; j++){

			puntaje += puntajeElemento(malla, i, j);
		}
	}
	
	return puntaje;
}


int rand_n1=0;
int rand_m1=0;
int rand_n2=0;
int rand_m2=0;
int elemAux;
void cambiosAleatorios(int cambios){

	for(int i=1; i<=cambios; i++){
	
		do{
			rand_n1 = 1+rand()%n;
			rand_m1 = 1+rand()%m;
			rand_n2 = 1+rand()%n;
			rand_m2 = 1+rand()%m;
		}
		while(mallaNew[rand_n1][rand_m1] == mallaNew[rand_n2][rand_m2]);
		
		//cout << rand_n1 << " " << rand_m1 << ", " << rand_n2 << " " << rand_m2 << endl;
		
		elemAux = mallaNew[rand_n1][rand_m1];
		mallaNew[rand_n1][rand_m1] = mallaNew[rand_n2][rand_m2];
		mallaNew[rand_n2][rand_m2] = elemAux;
	}
}


void copiarMalla(int (&original)[n+2][m+2], int (&copia)[n+2][m+2]){

	for(int i=0; i<=n+1; i++) copy(original[i], original[i] + m+2, copia[i]);
}


void imprimirVecindad(array<int, 4> &vecindad){

	cout << "  " << vecindad[0] << endl;
	cout << vecindad[3] << "   " << vecindad[1] << endl;
	cout << "  " << vecindad[2] << endl << endl;
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

void imprimirVectorMatriz2(double (&mat)[n][m], int n, int m){
	                            
	for(int i=0; i<=n-1; i++){

		for(int j=0; j<=m-1; j++){
   
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}   
	cout << endl;    
}
