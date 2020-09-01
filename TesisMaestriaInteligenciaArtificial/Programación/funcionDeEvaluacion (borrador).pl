eliminarSimilaresAux2(Stream2) :- 

	(mallaAux(MatrizIn),
	retract(mallaAux(MatrizIn)),
	% No se usa "assert" porque si se hace más de 2 veces se agregaran repetidos.
	write(Stream2,malla(MatrizIn)), writeln(Stream2,.), eliminarSimilaresAux2(Stream2) ; true), !.



cambiarElementoMatriz(MatrizIn, I, J, Valor, MatrizOut) :- 
	nth0(I,MatrizIn,Row), 
	length(Row,N1), 
	Naux1 is N1-1, rango(0, Naux1, Indices1),
	maplist(cambiar(Valor,J), Row, Indices1, L2),
	length(MatrizIn,N2), 
	Naux2 is N2-1, rango(0, Naux2, Indices2),
	maplist(cambiar(L2,I), MatrizIn, Indices2, MatrizOut).

cambiar(Valor,Indice,X,Y,Z) :- (Y\=Indice, Z=X ; Y==Indice, Z=Valor), !.



test(Cont,N) :- Cont > N, !.
test(Cont,N) :- Cont =< N, malla(M), cambiarElementoMatriz(M, 2, 2, 11, MatrizOut), Cont2 is Cont +1, test(Cont2,N), !.



sujetable(I, J, Formas) :-
	eij(I,J,Elem),
	FormasAux=[],
	I2 is I-1, I3 is I+1, J2 is J-1, J3 is J+1, 
	eij(I2,J,T), eij(I3,J,B), eij(I,J2,L), eij(I,J3,R),
	(B<Elem, T<Elem, append(FormasAux, [v], FormasAux2) ; FormasAux2=[])
	(R<Elem, L<Elem, append(FormasAux2, [h], Formas) ; true).
	
	
	
sujetable(I, J, Formas) :- findall(X, sujetableAux(I,J,X), Formas), length(Formas,N), N>0.

sujetableAux(I, J, Forma) :- eij(I,J,Elem), J2 is J-1, J3 is J+1, eij(I,J2,L), eij(I,J3,R), R<Elem, L<Elem, Forma=h.
sujetableAux(I, J, Forma) :- eij(I,J,Elem), I2 is I-1, I3 is I+1, eij(I2,J,T), eij(I3,J,B), B<Elem, T<Elem, Forma=v.




caminoPosible(I, J, CaminosAux, Caminos) :- sujetable(I, J, _), append(CaminosAux, [I/J], CaminosInv), reverse(CaminosInv, Caminos).

caminoPosible(I, J, CaminosAux, Caminos) :- 

	\+ sujetable(I, J, _), 
	\+ member(I/J, CaminosAux), 
	append(CaminosAux, [I/J], CaminosAux2), 
	I2 is I-1, I3 is I+1, 
	eij(I2, J, O), O==0, 
	caminoPosible(I3, J, CaminosAux2, Caminos).
	
caminoPosible(I, J, CaminosAux, Caminos) :- 

	\+ sujetable(I, J, _), 
	\+ member(I/J, CaminosAux), 
	append(CaminosAux, [I/J], CaminosAux2), 
	I2 is I-1, I3 is I+1, 
	eij(I3, J, O), O==0, 
	caminoPosible(I2, J, CaminosAux2, Caminos).
	
caminoPosible(I, J, CaminosAux, Caminos) :- 

	\+ sujetable(I, J, _), 
	\+ member(I/J, CaminosAux), 
	append(CaminosAux, [I/J], CaminosAux2), 
	J2 is J-1, J3 is J+1, 
	eij(I, J2, O), O==0, 
	caminoPosible(I, J3, CaminosAux2, Caminos).
	
caminoPosible(I, J, CaminosAux, Caminos) :- 

	\+ sujetable(I, J, _), 
	\+ member(I/J, CaminosAux), 
	append(CaminosAux, [I/J], CaminosAux2), 
	J2 is J-1, J3 is J+1, 
	eij(I, J3, O), O==0, 
	caminoPosible(I, J2, CaminosAux2, Caminos).

caminoPosible(I, J, CaminosAux, Caminos) :- 

	\+ sujetable(I, J, _), 
	\+ member(I/J, CaminosAux), 
	append(CaminosAux, [I/J], CaminosAux2), 
	I2 is I-1, I3 is I+1,
	eij(I2, J, O1), O1\=0, 
	eij(I3, J, O2), O2\=0, 
	caminoPosible(I2, J, CaminosAux2, CaminosInv), 
	reverse(CaminosInv, CaminosAux3),
	caminoPosible(I3, J, CaminosAux3, Caminos).

caminoPosible(I, J, CaminosAux, Caminos) :- 

	\+ sujetable(I, J, _), 
	\+ member(I/J, CaminosAux), 
	append(CaminosAux, [I/J], CaminosAux2), 
	J2 is J-1, J3 is J+1,
	eij(I,J2,O1), O1\=0, 
	eij(I,J3,O2), O2\=0, 
	caminoPosible(I, J2, CaminosAux2, CaminosInv), 
	reverse(CaminosInv, CaminosAux3),
	caminoPosible(I, J3, CaminosAux3, Caminos).

boost::variant<int, double, std::string> foo() {
    if (something) 
        //set type to int
    else if (something else)
        //set type to double
    else
        //set type to std::string
}



#include <iomanip>
#include <iostream>

int main()
{
    std::cout << std::setfill('0') << std::setw(5) << 25;
}


Naux = accumulate(NsAux, NsAux+numClases, 0);







//ORDENAR UN VECTOR CON BASE EN EL ORDENAMIENTO DE OTRO.
array<array<int, 2>, 4> vec = {{{5, 0}, {3, 1}, {7, 2}, {1, 3}}};


bool myfunc(array<int, 2> &i, array<int, 2> &j){
	
	return i[0]>j[0];
}


int main(){

sort(vec.begin(), vec.end(), myfunc);

for(auto elem:vec) cout << elem[0] << " ";
cout << endl;
for(auto elem:vec) cout << elem[1] << " ";
cout << endl;



