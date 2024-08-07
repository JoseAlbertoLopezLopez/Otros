bool ordenamiento(array<int, 2> &i, array<int, 2> &j){
	
	return i[1]>j[1];
}


bool ordenamiento2(array<int, 3> &i, array<int, 3> &j){
	
	return i[2]>j[2];
}


bool ordenamiento3(array<int, 5> &i, array<int, 5> &j){
	
	return i[4]>j[4];
}


void eliminarImposiblesPotenciales2(int r, int c, array<array<int, m-1>, n-1> &potencialesCuadrosImposibles, array<array<int, 2>, 2> &ventana){

	fill(minoriasEnVentana.begin(), minoriasEnVentana.end(), false);
	
	for(int i=1; i<=numClases; i++){
		if(ventana[0][1]==mayoresMenoresAux[i][0]) minoriasEnVentana[1] = true;
		if(ventana[1][0]==mayoresMenoresAux[i][0]) minoriasEnVentana[2] = true;
		if(ventana[1][1]==mayoresMenoresAux[i][0]) minoriasEnVentana[3] = true;
	}

	if(c<m and (minoriasEnVentana[1] or minoriasEnVentana[3])) potencialesCuadrosImposibles[r-2][c-1] = 0;
	if((c<m and r<n) and minoriasEnVentana[3]) potencialesCuadrosImposibles[r-1][c-1] = 0;
	if(r<n and (minoriasEnVentana[2] or minoriasEnVentana[3])) potencialesCuadrosImposibles[r-1][c-2] = 0;
	potencialesCuadrosImposibles[r-2][c-2] = 0;
}


void eliminarImposiblesPotenciales(int r, int c, array<array<int, m-1>, n-1> &potencialesCuadrosImposibles){

	potencialesCuadrosImposibles[r-1][c-1] = 0;
	potencialesCuadrosImposibles[r-1][c] = 0;
	potencialesCuadrosImposibles[r][c-1] = 0;
	potencialesCuadrosImposibles[r][c] = 0;
}


int contarImpPotSeparados(array<array<int, m-1>, n-1> &potencialesCuadrosImposibles){

	int numImposiblesSeparados = 0;
	bool imposibleQ;

	for(int r=1; r<=n-2; r++){
		for(int c=1; c<=m-2; c++){
		
			imposibleQ = false;
		
			if(c%2==1 and r%2==1){
			
				if(potencialesCuadrosImposibles[r-1][c-1]) imposibleQ = true;
				if(potencialesCuadrosImposibles[r-1][c]) imposibleQ = true;
				if(potencialesCuadrosImposibles[r][c-1]) imposibleQ = true;
				if(potencialesCuadrosImposibles[r][c]) imposibleQ = true;
			}
			else if(((r==n-2 and r%2==0) and c%2==1) or ((c==m-2 and c%2==0) and r%2==1)){
				
				if((c==m-2 and c%2==0) and r%2==1){
					if(potencialesCuadrosImposibles[r][c] or potencialesCuadrosImposibles[r-1][c]) imposibleQ = true;
				}
				else{
					if(potencialesCuadrosImposibles[r][c] or potencialesCuadrosImposibles[r][c-1]) imposibleQ = true; 
				}
			}
			else if((r==n-2 and r%2==0) and (c==m-2 and c%2==0)){
			
				if(potencialesCuadrosImposibles[r][c]) imposibleQ = true;
			}
			
			if(imposibleQ) numImposiblesSeparados++;
		}
	}
	
	return numImposiblesSeparados++;
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
	                            
	for(int i=0; i<=n+1; i++){

		for(int j=0; j<=m+1; j++){
   
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



// Funciones algoritmo basado en puntuaciones /////////////////////////////////////////////////////////////////////////////////



int puntuacionInteraccion(int elem1, int elem2){

	if(elem1==elem2) return 0;
	if((elem1==1 and elem2==0) or (elem2==1 and elem1==0)) return 2;
	if((elem1==1 and elem2==2) or (elem2==1 and elem1==2)) return 2;
	if((elem1==2 and elem2==0) or (elem2==2 and elem1==0)) return 1;
}


// Puntuaciones de los vecinos interiores de la ventana.
int puntuacionVentana(array<array<int, 2>, 2> &ventana){

	int puntuacion = 0;

	puntuacion += puntuacionInteraccion(ventana[0][0], ventana[0][1]);
	puntuacion += puntuacionInteraccion(ventana[0][0], ventana[1][0]);
	puntuacion += puntuacionInteraccion(ventana[1][1], ventana[0][1]);
	puntuacion += puntuacionInteraccion(ventana[1][1], ventana[1][0]);
	
	// Castigo 3 elementos iguales.
	for(int i=0; i<=numClases; i++){ if(elementosVentana[i]==3) puntuacion -= 2; }
	
	return puntuacion;
}


// Puntuaciones de los vecinos exteriores de la ventana, recibe como argumento las coordenadas de la esquina inferior derecha 
// de la ventana y a la ventana misma.
int puntuacionFrontera(int r, int c, array<array<int, 2>, 2> &ventana){

	int puntuacion = 0;

	if(malla[r-2][c-1]>=0 and !elementosLiberados[{r-2,c-1}]) puntuacion += puntuacionInteraccion(ventana[0][0], malla[r-2][c-1]);
	if(malla[r-1][c-2]>=0 and !elementosLiberados[{r-1,c-2}]) puntuacion += puntuacionInteraccion(ventana[0][0], malla[r-1][c-2]);
	
	if(malla[r-2][c]>=0 and !elementosLiberados[{r-2,c}]) puntuacion += puntuacionInteraccion(ventana[0][1], malla[r-2][c]);
	if(malla[r-1][c+1]>=0 and !elementosLiberados[{r-1,c+1}]) puntuacion += puntuacionInteraccion(ventana[0][1], malla[r-1][c+1]);
	
	if(malla[r][c-2]>=0 and !elementosLiberados[{r,c-2}]) puntuacion += puntuacionInteraccion(ventana[1][0], malla[r][c-2]);
	if(malla[r+1][c-1]>=0 and !elementosLiberados[{r+1,c-1}]) puntuacion += puntuacionInteraccion(ventana[1][0], malla[r+1][c-1]);
	
	if(malla[r+1][c]>=0 and !elementosLiberados[{r+1,c}]) puntuacion += puntuacionInteraccion(ventana[1][1], malla[r+1][c]);
	if(malla[r][c+1]>=0 and !elementosLiberados[{r,c+1}]) puntuacion += puntuacionInteraccion(ventana[1][1], malla[r][c+1]);
	
	return puntuacion;
}


int puntuacionPotencial_1(int r, int c, array<array<int, 2>, 2> &ventana){

	int puntuacionTotal = 0;
	int puntuacionAux;
	int frontera;
	int elem;
	int max = 0;
	
	mayoresMenoresAux2 = mayoresMenoresAux;
	
	if(c<m and r==2){
		elem = ventana[0][1];
		for(int i=0; i<=numClases; i++){
	
			if(mayoresMenoresAux2[indicesMM[i]][1]>0){ 

				puntuacionAux = puntuacionInteraccion(ventana[0][1], i);
				if(puntuacionAux > max){ max = puntuacionAux; elem = i; }
			}
		}
	
		puntuacionTotal += max;
		mayoresMenoresAux2[indicesMM[elem]][1]--;
		max = 0;
	}
	
	if(r<n){
		elem = ventana[1][0];
		for(int i=0; i<=numClases; i++){
	
			if(mayoresMenoresAux2[indicesMM[i]][1]>0){ 

				puntuacionAux = puntuacionInteraccion(ventana[1][0], i);
				if(puntuacionAux > max){ max = puntuacionAux; elem = i; }
			}
		}
	
		puntuacionTotal += max;
		mayoresMenoresAux2[indicesMM[elem]][1]--;
		max = 0;
	}
	
	frontera = (r<n ? (c<m ? 2 : 1) : (c<m ? 1 : 0));
	for(int j=1; j<=frontera; j++){
	
		elem = ventana[1][1];
		for(int i=0; i<=numClases; i++){
	
			if(mayoresMenoresAux2[indicesMM[i]][1]>0){ 

				puntuacionAux = puntuacionInteraccion(ventana[1][1], i);
				if(puntuacionAux > max){ max = puntuacionAux; elem = i; }
			}
		}
	
		puntuacionTotal += max;
		mayoresMenoresAux2[indicesMM[elem]][1]--;
		max = 0;
	}
	
	return puntuacionTotal;
}


inline bool encajanRenglon(int r, int c, array<array<int,2>,2> &mallaBase){

	if(malla[r-1][c-1] == mallaBase[0][0] and malla[r][c-1] == mallaBase[1][0]) return true;

	return false;
}


inline bool encajanColumna(int r, int c, array<array<int,2>,2> &mallaBase){

	if(malla[r-1][c-1] == mallaBase[0][0] and malla[r-1][c] == mallaBase[0][1]) return true;

	return false;
}


inline bool encajanCentro(int r, int c, array<array<int,2>,2> &mallaBase){

	if((malla[r-1][c-1] == mallaBase[0][0] and malla[r][c-1] == mallaBase[1][0]) and malla[r-1][c] == mallaBase[0][1]) return true;

	return false;
}


bool encajan(int r, int c, array<array<int,2>,2> &mallaBase){

	if(r>2 and c>2) return encajanCentro(r, c, mallaBase);
	if(c>2 and r==2) return encajanRenglon(r, c, mallaBase);
	if(r>2 and c==2) return encajanColumna(r, c, mallaBase);
	return true;
}


void anadirForma(array<array<int,2>,2> &ventana, int puntuacion){

	bool repetido = false;

	array<int,5> vec = {{ventana[0][0], ventana[0][1], ventana[1][0], ventana[1][1], puntuacion}};
	
	if(formasPosiblesPuntuacion.size()>0){
	
		for(int i=0; i<=formasPosiblesPuntuacion.size()-1; i++){

			if(formasPosiblesPuntuacion[i] == vec) repetido = true;
		}
	}
	
	if(!repetido) formasPosiblesPuntuacion.push_back(vec);
}


void llenadosPosibles(int r, int c){

	int puntuacion;
	bool siguiente = false;
	
	for(int i=0; i<=formasPosibles.size()-1; i++){
	
		// Hacer copia de lista con poblaciones de elementos.
		mayoresMenoresAux = mayoresMenores;
		
		// Verificar que los tipos de elementos ya presentes en la ventana no sean mayores a los que se quierentomar.
		for(int j=0; j<=numClases-1; j++){ if(tomarParaVentana[j] > formasPosibles[i][j]){ siguiente = true; break; } }
		if(siguiente){ siguiente=false; continue; }
	
		// Contar población de cada elemento en la ventana.
		for(int j=1; j<=numClases; j++) elementosVentana[j] = formasPosibles[i][j-1];
		elementosVentana[0] = 4 - accumulate(formasPosibles[i].begin(), formasPosibles[i].end(), 0);
		
		// Si hay los elementos deseados, quitar población de ventana a la población fuera de la malla.
		for(int j=0; j<=numClases; j++){
			
			if((mayoresMenoresAux[indicesMM[j]][1] - elementosVentana[j] + repetidos[j]) >= 0){
				mayoresMenoresAux[indicesMM[j]][1] -= (elementosVentana[j] - repetidos[j]);
			}
			else{ siguiente = true; break; }
		}
		if(siguiente){ siguiente=false; continue; }
		
		sort(mayoresMenoresAux.begin(), mayoresMenoresAux.end(), ordenamiento);
		
		// Calcular minoria resultante suponiendo que los elementos se colocarán en la malla.
		minoria = 0;
		for(int j=1; j<=mayoresMenoresAux.size()-1; j++) minoria += mayoresMenoresAux[j][1];
		
		// Si la minoria satisface la condición de minoria mínima para que no haya imposibles, calcular puntaje de la ventana 
		// y agregarlo a la lista.
		for(int j=0; j<=dicMallasBaseEsquinas[formasPosibles[i]].size()-1; j++){

			ventana = dicMallasBaseEsquinas[formasPosibles[i]][j];
			
			potencialesCuadrosImposiblesAux = potencialesCuadrosImposibles;
			eliminarImposiblesPotenciales2(r, c, potencialesCuadrosImposiblesAux, ventana);
				
			if(minoria >= contarImpPotSeparados(potencialesCuadrosImposiblesAux)){
				
				if(encajan(r, c, ventana)){
					puntuacion = puntuacionVentana(ventana) + puntuacionFrontera(r, c, ventana) + puntuacionPotencial_1(r, c, ventana);
					anadirForma(ventana, puntuacion);
				}
			}
				
			// Hacer lo mismo para las 7 ventanas equivalentes (rotaciones y reflexiones).
			for(int k=1; k<=7; k++){

				(k%2==1 ?  reflejar2(ventana) : transpuesta2(ventana));
				
				potencialesCuadrosImposiblesAux = potencialesCuadrosImposibles;
				eliminarImposiblesPotenciales2(r, c, potencialesCuadrosImposiblesAux, ventana);
				
				if(minoria >= contarImpPotSeparados(potencialesCuadrosImposiblesAux)){
				
					if(encajan(r, c, ventana)){
						puntuacion = puntuacionVentana(ventana) + puntuacionFrontera(r, c, ventana) + puntuacionPotencial_1(r, c, ventana);
						anadirForma(ventana, puntuacion);
					}
				}
			}
		}
	}
}


void colocarVentana(int r, int c, array<int, 5> &ventana){

	malla[r-1][c-1] = ventana[0];
	malla[r-1][c] = ventana[1];
	malla[r][c-1] = ventana[2];
	malla[r][c] = ventana[3];
	
	ventanaAux[0][0] = ventana[0];
	ventanaAux[0][1] = ventana[1];
	ventanaAux[1][0] = ventana[2];
	ventanaAux[1][1] = ventana[3];
}


void noColocarVentana(int r, int c){

	malla[r-1][c-1] = ventana[0][0];
	malla[r-1][c] = ventana[0][1];
	malla[r][c-1] = ventana[1][0];
	malla[r][c] = ventana[1][1];
}


void verificarLiberados(int r, int c){

	if((malla[r-1][c-1] > malla[r-1][c-2] and malla[r-1][c-1] > malla[r-1][c]) or 
	(malla[r-1][c-1] > malla[r][c-1] and malla[r-1][c-1] > malla[r-2][c-1])) 
	elementosLiberados.insert(pair<array<int, 2>, bool>({r-1,c-1}, true));
	
	if(malla[r-1][c] > malla[r-2][c] and malla[r-1][c] > malla[r][c]) 
	elementosLiberados.insert(pair<array<int, 2>, bool>({r-1,c}, true));
	
	if(malla[r][c-1] > malla[r][c-2] and malla[r][c-1] > malla[r][c]) 
	elementosLiberados.insert(pair<array<int, 2>, bool>({r,c-1}, true));
}







