
void transpuesta(array<array<int,2>,2> &matriz){

	int aux = matriz[0][1];
	matrizAux[0][1] = matriz[1][0]; 
	matrizAux[1][0] = aux;
}

void reflejar(array<array<int,2>,2> &matriz){
	
	int aux = matriz[0][0];
	matrizAux[0][0] = matriz[0][1]; 
	matrizAux[0][1] = aux;
	aux = matriz[1][1];
	matrizAux[1][1] = matriz[1][0];
	matrizAux[1][0] = aux; 
}


inline bool llenarAux1(int r, int c, array<array<int,2>,2> &mallaBase){

	if(malla[r-1][c-1] == mallaBase[0][0] and malla[r][c-1] == mallaBase[1][0]){
	
		malla[r-1][c] = mallaBase[0][1];
		malla[r][c] = mallaBase[1][1];
		return true;
	}
	return false;
}

inline bool llenarAux2(int r, int c, array<array<int,2>,2> &mallaBase){

	if(malla[r-1][c-1] == matrizAux[0][0] and malla[r][c-1] == matrizAux[1][0]){
	
		malla[r-1][c] = matrizAux[0][1];
		malla[r][c] = matrizAux[1][1];
		return true;
	}
	return false;
}

inline bool llenarAux3(int r, int c, array<array<int,2>,2> &mallaBase){

	if((malla[r-1][c-1] == mallaBase[0][0] and malla[r][c-1] == mallaBase[1][0]) and malla[r-1][c] == mallaBase[0][1]){

		malla[r][c] = mallaBase[1][1];
		return true;
	}
	return false;
}

inline bool llenarAux4(int r, int c, array<array<int,2>,2> &mallaBase){

	if((malla[r-1][c-1] == matrizAux[0][0] and malla[r][c-1] == matrizAux[1][0]) and malla[r-1][c] == matrizAux[0][1]){

		malla[r][c] = matrizAux[1][1];
		return true;
	}
	return false;
}

inline bool llenarAux5(int r, int c, array<array<int,2>,2> &mallaBase){

	if(malla[r-1][c-1] == mallaBase[0][0] and malla[r-1][c] == mallaBase[0][1]){
	
		malla[r][c-1] = mallaBase[1][0];
		malla[r][c] = mallaBase[1][1];
		return true;
	}
	return false;
}

inline bool llenarAux6(int r, int c, array<array<int,2>,2> &mallaBase){

	if(malla[r-1][c-1] == matrizAux[0][0] and malla[r-1][c] == matrizAux[0][1]){
	
		malla[r][c-1] = matrizAux[1][0];
		malla[r][c] = matrizAux[1][1];
		return true;
	}
	return false;
}


bool cambioLocal(int i, int j, int elemPuntoClave){

	int aux;

	if(malla[i-1][j-1] != elemPuntoClave){ aux = malla[i-1][j-1]; malla[i-1][j-1] = elemPuntoClave; 
	malla[i][j] = aux; return 1;}
	
	else if(malla[i-1][j] != elemPuntoClave){ aux = malla[i-1][j]; malla[i-1][j] = elemPuntoClave; 
	malla[i][j] = aux; return 1;}
	
	else if(j<m-1 and malla[i-1][j+1] != elemPuntoClave){ aux = malla[i-1][j+1]; malla[i-1][j+1] = elemPuntoClave; 
	malla[i][j] = aux; return 1;}
	
	else if(malla[i][j-1] != elemPuntoClave){ aux = malla[i][j-1]; malla[i][j-1] = elemPuntoClave; 
	malla[i][j] = aux; return 1;}
	
	else if(j<m-1 and malla[i][j+1] != elemPuntoClave){ aux = malla[i][j+1]; malla[i][j+1] = elemPuntoClave; 
	malla[i][j] = aux; return 1;}
	
	else if(i<n-1 and malla[i+1][j-1] != elemPuntoClave){ aux = malla[i+1][j-1]; malla[i+1][j-1] = elemPuntoClave; 
	malla[i][j] = aux; return 1;}
	
	else if(i<n-1 and malla[i+1][j] != elemPuntoClave){ aux = malla[i+1][j]; malla[i+1][j] = elemPuntoClave; 
	malla[i][j] = aux; return 1;}
	
	else if((i<n-1 and j<m-1) and malla[i+1][j+1] != elemPuntoClave){ aux = malla[i+1][j+1]; malla[i+1][j+1] = elemPuntoClave; 
	malla[i][j] = aux; return 1;}
	
	return 0;
}


void cambioGlobal(int i, int j, int elemPuntoClave){

	int r3;
	int c3;
	int r3aux;
	int c3aux;
	bool exit=false;

	for(int i2=0; i2<=puntosClaveR-1; i2++){
	
		for(int j2=0; j2<=puntosClaveC-1; j2++){
		
			r3 = 2*i2+1;
			c3 = 2*j2+1;
			
			if(r3!=i or c3!=j){
			
				int aux;

				if(malla[r3-1][c3-1] != elemPuntoClave){ aux = malla[r3-1][c3-1]; malla[r3-1][c3-1] = elemPuntoClave; 
				malla[i][j] = aux; exit=true; r3aux=r3-1; c3aux=c3-1;}
	
				else if(malla[r3-1][c3] != elemPuntoClave){ aux = malla[r3-1][c3]; malla[r3-1][c3] = elemPuntoClave; 
				malla[i][j] = aux; exit=true; r3aux=r3-1; c3aux=c3;}

				else if(c3<m-1 and malla[r3-1][c3+1] != elemPuntoClave){ aux = malla[r3-1][c3+1]; malla[r3-1][c3+1] = elemPuntoClave; 
				malla[i][j] = aux; exit=true; r3aux=r3-1; c3aux=c3+1;}
		
				else if(malla[r3][c3-1] != elemPuntoClave){ aux = malla[r3][c3-1]; malla[r3][c3-1] = elemPuntoClave; 
				malla[i][j] = aux; exit=true; r3aux=r3; c3aux=c3-1;}
				
				else if(c3<m-1 and malla[r3][c3+1] != elemPuntoClave){ aux = malla[r3][c3+1]; malla[r3][c3+1] = elemPuntoClave; 
				malla[i][j] = aux; exit=true; r3aux=r3; c3aux=c3+1;}
	
				else if(r3<n-1 and  malla[r3+1][c3-1] != elemPuntoClave){ aux = malla[r3+1][c3-1]; malla[r3+1][c3-1] = elemPuntoClave; 
				malla[i][j] = aux; exit=true; r3aux=r3+1; c3aux=c3-1;}
	
				else if(r3<n-1 and malla[r3+1][c3] != elemPuntoClave){ aux = malla[r3+1][c3]; malla[r3+1][c3] = elemPuntoClave; 
				malla[i][j] = aux; exit=true; r3aux=r3+1; c3aux=c3;}
	
				else if((r3<n-1 and c3<m-1) and malla[r3+1][c3+1] != elemPuntoClave){ aux = malla[r3+1][c3+1]; malla[r3+1][c3+1] = elemPuntoClave; 
				malla[i][j] = aux; exit=true; r3aux=r3+1; c3aux=c3+1;}
				
				if(exit){
				
					if(malla[r3][c3]==aux){
					
						if(r3aux==r3-1){
						
							if(c3aux==c3-1) if(malla[r3-1][c3]==aux and malla[r3][c3-1]==aux){ 
								cuadrosImposibles[i2][j2]--;}
								
							else if(c3aux==c3){ 
								if(malla[r3-1][c3-1]==aux and malla[r3][c3-1]==aux){ 
									cuadrosImposibles[i2][j2]--;}
								if(malla[r3-1][c3+1]==aux and malla[r3][c3+1]==aux){ 
									cuadrosImposibles[i2][j2]--;}
							}
							
							else if(c3aux==c3+1) if(malla[r3-1][c3]==aux and malla[r3][c3+1]==aux){
								cuadrosImposibles[i2][j2]--;}
						}
						
						else if(r3aux==r3){
						
							if(c3aux==c3-1){
								if(malla[r3-1][c3-1]==aux and malla[r3-1][c3]==aux){
									cuadrosImposibles[i2][j2]--;}
								if(malla[r3+1][c3-1]==aux and malla[r3+1][c3]==aux){
									cuadrosImposibles[i2][j2]--;}
							}
							else if(c3aux==c3+1){
								if(malla[r3-1][c3]==aux and malla[r3-1][c3+1]==aux){
									cuadrosImposibles[i2][j2]--;}
								if(malla[r3+1][c3]==aux and malla[r3+1][c3+1]==aux){
									cuadrosImposibles[i2][j2]--;}
							}
						}
						
						else if(r3aux==r3+1){
						
							if(c3aux==c3-1) if(malla[r3][c3-1]==aux and malla[r3+1][c3]==aux){ 
								cuadrosImposibles[i2][j2]--;}
								
							else if(c3aux==c3){ 
								if(malla[r3+1][c3-1]==aux and malla[r3][c3-1]==aux){ 
									cuadrosImposibles[i2][j2]--;}
								if(malla[r3+1][c3+1]==aux and malla[r3][c3+1]==aux){
									cuadrosImposibles[i2][j2]--;}
							}
							
							else if(c3aux==c3+1) if(malla[r3][c3+1]==aux and malla[r3+1][c3]==aux){ 
								cuadrosImposibles[i2][j2]--;}
						}
					}
					else{
					
						int aux2 = malla[r3][c3];
					
						if(r3aux==r3-1){
						
							if(c3aux==c3-1){
								if((malla[r3-1][c3]==aux2 and malla[r3][c3-1]==aux2) and aux2==elemPuntoClave){
									cuadrosImposibles[i2][j2]++;}
							}
								
							else if(c3aux==c3){ 
								if((malla[r3-1][c3-1]==aux2 and malla[r3][c3-1]==aux2) and aux2==elemPuntoClave){ 
									cuadrosImposibles[i2][j2]++;}
								if((malla[r3-1][c3+1]==aux2 and malla[r3][c3+1]==aux2) and aux2==elemPuntoClave){
									cuadrosImposibles[i2][j2]++;}
							}
							
							else if(c3aux==c3+1){
								if((malla[r3-1][c3]==aux2 and malla[r3][c3+1]==aux2) and aux2==elemPuntoClave){
									cuadrosImposibles[i2][j2]++;}
							}
						}
						
						else if(r3aux==r3){
						
							if(c3aux==c3-1){ 
								if((malla[r3-1][c3-1]==aux2 and malla[r3-1][c3]==aux2) and aux2==elemPuntoClave){ 
									if(r3==5 and c3==1) cout << "cuadrosImposibles[2][0] = " << cuadrosImposibles[2][0] << endl; 
									cuadrosImposibles[i2][j2]++;
									if(r3==5 and c3==1) cout << "cuadrosImposibles[2][0] = " << cuadrosImposibles[2][0] << endl; }
								if((malla[r3+1][c3-1]==aux2 and malla[r3+1][c3]==aux2) and aux2==elemPuntoClave){
									if(r3==5 and c3==1) cout << "Hola" << endl; 
									cuadrosImposibles[i2][j2]++;}
							}
							else if(c3aux==c3+1){ 
								if((malla[r3-1][c3]==aux2 and malla[r3-1][c3+1]==aux2) and aux2==elemPuntoClave){
									if(r3==5 and c3==1) cout << "Hola" << endl; 
									cuadrosImposibles[i2][j2]++;}
								if((malla[r3+1][c3]==aux2 and malla[r3+1][c3+1]==aux2) and aux2==elemPuntoClave){
									if(r3==5 and c3==1) cout << "Hola" << endl; 
									cuadrosImposibles[i2][j2]++;}
							}
						}
						
						else if(r3aux==r3+1){
						
							if(c3aux==c3-1){
								if((malla[r3][c3-1]==aux2 and malla[r3+1][c3]==aux2) and aux2==elemPuntoClave){ 
									cuadrosImposibles[i2][j2]++;}
							}
								
							else if(c3aux==c3){ 
								if((malla[r3+1][c3-1]==aux2 and malla[r3][c3-1]==aux2) and aux2==elemPuntoClave){ 
									cuadrosImposibles[i2][j2]++;}
								if((malla[r3+1][c3+1]==aux2 and malla[r3][c3+1]==aux2) and aux2==elemPuntoClave){ 
									cuadrosImposibles[i2][j2]++;}
							}
							
							else if(c3aux==c3+1){
								if((malla[r3][c3+1]==aux2 and malla[r3+1][c3]==aux2) and aux2==elemPuntoClave){
									cuadrosImposibles[i2][j2]++;}
							}
						}
					}
				}
			}
			
			if(exit) break;
		}
		
		if(exit) break;
	}
}


void imprimirMalla(){
	                            
	for(int i=0; i<=n-1; i++){

		for(int j=0; j<=m-1; j++){
   
			cout << malla[i][j] << " ";
		}
		cout << endl;
	}   
	cout << endl;    
}


void corregirImposibles(){

	int elemPuntoClave;
	int r2;
	int c2;

	for(int i=0; i<=puntosClaveR-1; i++){
	
		for(int j=0; j<=puntosClaveC-1; j++){
		
			if(cuadrosImposibles[i][j]==4){
			
				r2 = 2*i+1;
				c2 = 2*j+1;
				elemPuntoClave = malla[r2][c2];
				
				for(auto &row:cuadrosImposibles) {for(auto &elem:row) cout << elem << " "; cout << endl;} cout << endl;
				imprimirMalla();
				cambioGlobal(r2, c2, elemPuntoClave);
			}
		
			else if(cuadrosImposibles[i][j]>0){

				r2 = 2*i+1;
				c2 = 2*j+1;
				elemPuntoClave = malla[r2][c2];
				
				for(auto &row:cuadrosImposibles) {for(auto &elem:row) cout << elem << " "; cout << endl;} cout << endl;
				imprimirMalla();
				if(!cambioLocal(r2, c2, elemPuntoClave)) cambioGlobal(r2, c2, elemPuntoClave);
			}
			
			cuadrosImposibles[i][j] = 0;
		}
	}
}


void imprimirMatriz(array<array<int,2>,2> &matriz){
	                            
	for(int i=0; i<=1; i++){

		for(int j=0; j<=1; j++){
   
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}   
	cout << endl;    
}
