



bool verificarSimetricos(array<int, 4> &vecindad_1, array<int, 4> &vecindad_2){

	if(vecindad_1 == vecindad_2) return true;
	
	//Reflejar.
	else if((vecindad_2[0] == vecindad_1[0] and vecindad_2[2] == vecindad_1[2]) and
		(vecindad_2[3] == vecindad_1[1] and vecindad_2[1] == vecindad_1[3])) return true;

	//Rotar.
	else if((vecindad_2[0] == vecindad_1[1] and vecindad_2[1] == vecindad_1[2]) and
		(vecindad_2[2] == vecindad_1[3] and vecindad_2[3] == vecindad_1[0])) return true;
	
	//Reflejar.
	else if((vecindad_2[0] == vecindad_1[1] and vecindad_2[3] == vecindad_1[2]) and
		(vecindad_2[2] == vecindad_1[3] and vecindad_2[1] == vecindad_1[0])) return true;

	//Rotar.
	else if((vecindad_2[0] == vecindad_1[2] and vecindad_2[1] == vecindad_1[3]) and
		(vecindad_2[2] == vecindad_1[0] and vecindad_2[3] == vecindad_1[1])) return true;
	
	//Reflejar.
	else if((vecindad_2[0] == vecindad_1[2] and vecindad_2[3] == vecindad_1[3]) and
		(vecindad_2[2] == vecindad_1[0] and vecindad_2[1] == vecindad_1[1])) return true;

	//Rotar.
	else if((vecindad_2[0] == vecindad_1[3] and vecindad_2[1] == vecindad_1[0]) and
		(vecindad_2[2] == vecindad_1[1] and vecindad_2[3] == vecindad_1[2])) return true;
	
	//Reflejar.
	else if((vecindad_2[0] == vecindad_1[3] and vecindad_2[3] == vecindad_1[0]) and
		(vecindad_2[2] == vecindad_1[1] and vecindad_2[1] == vecindad_1[2])) return true;
		
	else return false;	
}


struct claveVecindad{
	array<int, numClases+1> clave;
	array<int, 4> vecindad;
};
claveVecindad clave_vecindad;
void generarClaveVecindad(int r, int c){
	
	fill(clave_vecindad.clave.begin(), clave_vecindad.clave.end(), 0);
	
	if(malla[r-1][c]!=0) clave_vecindad.clave[malla[r-1][c]-1]++;
	if(malla[r][c+1]!=0) clave_vecindad.clave[malla[r][c+1]-1]++;
	if(malla[r+1][c]!=0) clave_vecindad.clave[malla[r+1][c]-1]++;
	if(malla[r][c-1]!=0) clave_vecindad.clave[malla[r][c-1]-1]++;

	clave_vecindad.vecindad[0] = malla[r-1][c];
	clave_vecindad.vecindad[1] = malla[r][c+1];
	clave_vecindad.vecindad[2] = malla[r+1][c];
	clave_vecindad.vecindad[3] = malla[r][c-1];
}


double puntajeElemento(int r, int c){

	int sumaElemLocal;
	double f_prop = 1.0;
	generarClaveVecindad(r, c);
	
	if((r>1 and r<n) and (c>1 and c<m)){
	
		while(!verificarSimetricos(clave_vecindad.vecindad, dicVecindadesDentro.find(clave_vecindad.clave)->second)){
			clave_vecindad.clave[numClases]++;
		}
		
		sumaElemLocal = accumulate(clave_vecindad.clave.begin(), clave_vecindad.clave.end()-1, 0);
		for(int i=0; i<=numClases-1; i++) propL[i+1]=clave_vecindad.clave[i]/5.0; 
		propL[0] = (4-sumaElemLocal)/5.0;
		propL[malla[r][c]] += 1.0/5.0;
		
		for(int i=0; i<=numClases; i++) f_prop += (1.0 - abs(propL[i]-propG[i]));
		f_prop *= bonoMaxProp;
		
		return (f_prop + dicPuntajesDentro.find(clave_vecindad.clave)->second[malla[r][c]]);
	}
	
	else if(((r==1 or r==n) and (c>1 and c<m)) or ((c==1 or c==m) and (r>1 and r<n))){
	
		while(!verificarSimetricos(clave_vecindad.vecindad, dicVecindadesBordes.find(clave_vecindad.clave)->second)){
			clave_vecindad.clave[numClases]++;
		}
		
		sumaElemLocal = accumulate(clave_vecindad.clave.begin(), clave_vecindad.clave.end()-1, 0);
		for(int i=0; i<=numClases-1; i++) propL[i+1]=clave_vecindad.clave[i]/4.0; 
		propL[0] = (3-sumaElemLocal)/4.0;
		propL[malla[r][c]] += 1.0/4.0;
		
		for(int i=0; i<=numClases; i++) f_prop += (1.0 - abs(propL[i]-propG[i]));
		f_prop *= bonoMaxProp;
		
		return (f_prop + dicPuntajesDentro.find(clave_vecindad.clave)->second[malla[r][c]]);
	}
	
	else{
	
		while(!verificarSimetricos(clave_vecindad.vecindad, dicVecindadesEsquinas.find(clave_vecindad.clave)->second)){
			clave_vecindad.clave[numClases]++;
		}
		
		sumaElemLocal = accumulate(clave_vecindad.clave.begin(), clave_vecindad.clave.end()-1, 0);
		for(int i=0; i<=numClases-1; i++) propL[i+1]=clave_vecindad.clave[i]/3.0; 
		propL[0] = (2-sumaElemLocal)/3.0;
		propL[malla[r][c]] += 1.0/3.0;
		
		for(int i=0; i<=numClases; i++) f_prop += (1.0 - abs(propL[i]-propG[i]));
		f_prop *= bonoMaxProp;
		
		return (f_prop + dicPuntajesEsquinas.find(clave_vecindad.clave)->second[malla[r][c]]);
	}
}


double puntajeMallaInicial(){

	double puntaje = 0.0;

	for(int i=1; i<=n; i++){
	
		for(int j=1; j<=m; j++){
		
			puntajesMalla[i-1][j-1] = puntajeElemento(i, j);
			puntaje += puntajesMalla[i-1][j-1];
		}
	}
	
	return puntaje;
}


double puntajesRepetidos(int i1,int j1, int i2, int j2){

	double suma = 0.0;

	if(i2==i1+1 and abs(j1-j2)<2) suma = puntajesMalla[i1][j1-1] + puntajesMalla[i2-2][j2-1];
	else if(i2==i1-1 and abs(j1-j2)<2) suma = puntajesMalla[i1-2][j1-1] + puntajesMalla[i2][j2-1];
	else if(i2==i1 and j2==j1+1) suma = puntajesMalla[i1-1][j1] + puntajesMalla[i2-1][j2-2];
	else if(i2==i1 and j2==j1-1) suma = puntajesMalla[i1-1][j1-2] + puntajesMalla[i2-1][j2];
	
	else if(j2==j1 and i2==i1+2) suma = puntajesMalla[i2-2][j2-1];
	else if(j2==j1 and i2==i1-2) suma = puntajesMalla[i2][j2-1];
	else if(i2==i1 and j2==j1+2) suma = puntajesMalla[i2-1][j2-2];
	else if(i2==i1 and j2==j1-2) suma = puntajesMalla[i2-1][j2];

	return suma;
}


int soloInteracciones(int &elem1, int &elem2){

	if(elem1 != 0 and elem1 == elem2) return 0;
	else if(elem1 == 0 and elem2 == 0) return 1;
	else if((elem1 == 0 and elem2==2) or (elem1 == 2 and elem2 == 0)) return 2;
	else if((elem1 == 0 and elem2==1) or (elem1 == 1 and elem2 == 0)) return 3;
	else if((elem1 == 1 and elem2==2) or (elem1 == 2 and elem2 == 1)) return 3;
}


int puntajeMallaInicial2(){

	int puntaje = 0;

	for(int i=1; i<=n; i++){
	
		for(int j=1; j<=m; j++){
		
			if(i>1 and j>1){
		
				puntaje += soloInteracciones(malla[i][j], malla[i][j+1]);
				puntaje += soloInteracciones(malla[i][j], malla[i+1][j]);
			}
			else if(i==1 and j>1){
			
				puntaje += soloInteracciones(malla[i][j], malla[i-1][j]);
				puntaje += soloInteracciones(malla[i][j], malla[i][j+1]);
				puntaje += soloInteracciones(malla[i][j], malla[i+1][j]);
			}
			else if(i>1 and j==1){

				puntaje += soloInteracciones(malla[i][j], malla[i][j+1]);
				puntaje += soloInteracciones(malla[i][j], malla[i+1][j]);
				puntaje += soloInteracciones(malla[i][j], malla[i][j-1]);
			}
			else{

				puntaje += soloInteracciones(malla[i][j], malla[i-1][j]);
				puntaje += soloInteracciones(malla[i][j], malla[i][j+1]);
				puntaje += soloInteracciones(malla[i][j], malla[i+1][j]);
				puntaje += soloInteracciones(malla[i][j], malla[i][j-1]);
			}
		}
	}
	
	return puntaje;
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
