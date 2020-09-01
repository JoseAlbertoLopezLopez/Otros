bool ordenamiento(array<int, 2> &i, array<int, 2> &j){
	
	return i[1]>j[1];
}


bool ordenamiento2(array<int, 3> &i, array<int, 3> &j){
	
	return i[2]>j[2];
}


void eliminarImposiblesPotenciales2(int r, int c, array<array<int, m-1>, n-1> &potencialesCuadrosImposibles){

	if(c-1<m-2) potencialesCuadrosImposibles[(r-1)][(c-1)+1] = 0;
	if(c-1<m-2 and r-1<n-1) potencialesCuadrosImposibles[(r-1)+1][(c-1)+1] = 0;
	if(r-1<n-2) potencialesCuadrosImposibles[(r-1)+1][(c-1)] = 0;
	potencialesCuadrosImposibles[(r-1)][(c-1)] = 0;
}


void eliminarImposiblesPotenciales(int r, int c, array<array<int, m-1>, n-1> &potencialesCuadrosImposibles){

	potencialesCuadrosImposibles[r-1][c-1] = 0;
	potencialesCuadrosImposibles[r-1][c] = 0;
	potencialesCuadrosImposibles[r][c-1] = 0;
	potencialesCuadrosImposibles[r][c] = 0;
}


bool noAgregar = false;
bool contarImposiblesPotenciales(array<array<int, m-1>, n-1> &potencialesCuadrosImposibles){
	
	//Contar imposibles potenciales por ventana.
	for(int r=1; r<=n-2; r++){
		for(int c=1; c<=m-2; c++){

			noAgregar = false;
			array<int, 3> listaPotImpAux;
			listaPotImpAux[2] = 0;
			
			if(potencialesCuadrosImposibles[r-1][c-1]) listaPotImpAux[2]++;
			if(potencialesCuadrosImposibles[r-1][c]) listaPotImpAux[2]++;
			if(potencialesCuadrosImposibles[r][c-1]) listaPotImpAux[2]++;
			if(potencialesCuadrosImposibles[r][c]) listaPotImpAux[2]++;
			
			listaPotImpAux[0] = r; 
			listaPotImpAux[1] = c; 
			
			if(listaPotencialesImposibles.size()>0){
			
				for(int i=0; i<=listaPotencialesImposibles.size()-1; i++){
			
					if(listaPotencialesImposibles[i][2] == listaPotImpAux[2]) noAgregar = true; 
				}
				
				if(!noAgregar) listaPotencialesImposibles.push_back(listaPotImpAux);
			}
			else listaPotencialesImposibles.push_back(listaPotImpAux);
		}
	}
	
	sort(listaPotencialesImposibles.begin(), listaPotencialesImposibles.end(), ordenamiento2);
	
	if(listaPotencialesImposibles[0][2]) return true;
	else return false;
}


int minoriaNecesaria(){

	int minoriaNec = 0;
	int indice = 0;
	int r;
	int c;
	
	potencialesCuadrosImposiblesAux = potencialesCuadrosImposibles;

	contarImposiblesPotenciales(potencialesCuadrosImposiblesAux);
		
	while(listaPotencialesImposibles[indice][2]>0){
		
		r=listaPotencialesImposibles[indice][0];
		c=listaPotencialesImposibles[indice][1];
		
		eliminarImposiblesPotenciales(r, c, potencialesCuadrosImposiblesAux);
		minoriaNec++;
		contarImposiblesPotenciales(potencialesCuadrosImposiblesAux);
	}
	
	return minoriaNec;
}


int indicePreferencia(int r, int c){

	//Si la ventana se encuentra en un borde o esquina prefiere los 1's y 0's.
	if((r==1 or r==n-1) or (c==1 or c==m-1)){
	
		//Si hay 1's, y la cantidad de 0's/1's es >=1/9 prefiere los 0's, si no, prefiere los 1's.
		if((mayoresMenores[indicesMM[1]][1]>0 and 1.0*mayoresMenores[indicesMM[0]][1]/(1.0*mayoresMenores[indicesMM[1]][1]) >= 1.0/9.0) and (tomarParaVentana[1]!=2 or tomarParaVentana[0]!=0)){
		
			for(int i=1; i<=mayoresMenores.size()-1; i++){ if(mayoresMenores[i][0]==0 and mayoresMenores[i][1]>0) return i; }
		}
		else{
	
			for(int i=1; i<=mayoresMenores.size()-1; i++){ if(mayoresMenores[i][0]==1 and mayoresMenores[i][1]>0) return i; }
		}
	}
	else{
		for(int i=1; i<=mayoresMenores.size()-1; i++){ if(mayoresMenores[i][0]==2 and mayoresMenores[i][1]>0) return i; }
	}
	
	return -1;
}


void llenar_indicesMM(){

	for(int i=0; i<=numClases; i++){
	
		indicesMM[mayoresMenores[i][0]] = i;
	}
}


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


void transpuesta2(array<array<int,2>,2> &matriz){

	int aux = matriz[0][1];
	matriz[0][1] = matriz[1][0]; 
	matriz[1][0] = aux;
}

void reflejar2(array<array<int,2>,2> &matriz){
	
	int aux = matriz[0][0];
	matriz[0][0] = matriz[0][1]; 
	matriz[0][1] = aux;
	aux = matriz[1][1];
	matriz[1][1] = matriz[1][0];
	matriz[1][0] = aux; 
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


void imprimirMalla(){
	                            
	for(int i=0; i<=n-1; i++){

		for(int j=0; j<=m-1; j++){
   
			cout << malla[i][j] << " ";
		}
		cout << endl;
	}   
	cout << endl;    
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


void imprimirMatriz2(array<array<int,n-1>,m-1> &matriz){
	                            
	for(int i=0; i<=n-2; i++){

		for(int j=0; j<=m-2; j++){
   
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}   
	cout << endl;    
}
