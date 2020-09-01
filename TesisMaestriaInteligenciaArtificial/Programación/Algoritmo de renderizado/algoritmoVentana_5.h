bool ordenamiento(array<int, 2> &i, array<int, 2> &j){
	
	return i[1]>j[1];
}


void transpuesta(array<array<int,2>,2> &matriz){

	int aux = matriz[0][1];
	matriz[0][1] = matriz[1][0]; 
	matriz[1][0] = aux;
}

void reflejar(array<array<int,2>,2> &matriz){
	
	int aux = matriz[0][0];
	matriz[0][0] = matriz[0][1]; 
	matriz[0][1] = aux;
	aux = matriz[1][1];
	matriz[1][1] = matriz[1][0];
	matriz[1][0] = aux; 
}


void ventanasSeparadas(){

	int numVentanas = floor(n/2.0)*floor(m/2.0);
	int minorias = Nx[1][1] + Nx[2][1];
	int ventanasPorColocar = numVentanas;
	int elemPorColocar = 4;
	array<int, 2> ventana = {{0,0}};
	
	while(ventanasPorColocar > 0){
	
		elemPorColocar = 4;
		ventana = {{0,0}};
	
		while(elemPorColocar > 0){
		
			for(int i=1; i<=numClases; i++){
		
				if(minorias > ventanasPorColocar-1 and elemPorColocar > 2){
				
					if(Nx[i][1]>0){
					
						Nx[i][1]--; elemPorColocar--; minorias--; 
						if(Nx[i][0]>0) ventana[Nx[i][0]-1]++;
					}
				}
			}
		
			Nx[0][1]--; elemPorColocar--; 
			if(Nx[0][0]>0) ventana[Nx[0][0]-1]++;
			sort(Nx.begin(), Nx.end(), ordenamiento);
			minorias = Nx[1][1] + Nx[2][1];
		}
		
		for(int i=0; i<=12; i++) if(ventanasSeparadas2[i]==ventana) ventanasSeparadas1[i]++;
		cout << ventana[0] << " " << ventana[1] << endl;
		ventanasPorColocar--;
	}
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




