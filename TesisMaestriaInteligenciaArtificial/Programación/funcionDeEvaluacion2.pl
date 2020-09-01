:- use_module(library(clpfd)).
:- use_module(library(thread)).
%:- use_module(library(csv)).

:- set_prolog_flag(answer_write_options, [quoted(true), portray(true), spacing(next_argument)]).

%:- [matrix].

%:- dynamic malla/1.
%:- dynamic mallaAux/1.

%:- ["mallaVentana"].
%:- ["mallaRefuerzo"].
%:- [baseConocimientoMalla].
%:- [baseConocimientoMallasFiltradas1].
:- [baseConocimientoMallasFiltradas].

eij(MatrizIn, I, J, Clase) :- nth0(I,MatrizIn,Row), nth0(J,Row,Clase).

sujetable(MatrizIn, I, J) :- eij(MatrizIn,I,J,Elem), J2 is J-1, J3 is J+1, eij(MatrizIn,I,J2,L), eij(MatrizIn,I,J3,R), R<Elem, L<Elem.
sujetable(MatrizIn, I, J) :- eij(MatrizIn,I,J,Elem), I2 is I-1, I3 is I+1, eij(MatrizIn,I2,J,T), eij(MatrizIn,I3,J,B), B<Elem, T<Elem.

totalObjetos(Matriz, N) :- flatten(Matriz,L), contar(L, N).

contar(Lista, Ocurrencias) :- contarAux(Lista, 0, Ocurrencias).

contarAux([], Ocurrencias, Ocurrencias).
contarAux([Y|T], Aux, Ocurrencias) :- 

	(Y>0, Aux1 is Aux+1, contarAux(T, Aux1, Ocurrencias) ; 
	contarAux(T, Aux, Ocurrencias)), !.

contarClases(Matriz, N1, N2) :- flatten(Matriz,L), contarClasesAux(L, 0, 0, N1, N2).
contarClasesAux([X|T], N1aux, N2aux, N1, N2) :- X=1, N1aux2 is N1aux + 1, contarClasesAux(T, N1aux2, N2aux, N1, N2).
contarClasesAux([X|T], N1aux, N2aux, N1, N2) :- X=2, N2aux2 is N2aux + 1, contarClasesAux(T, N1aux, N2aux2, N1, N2).
contarClasesAux([X|T], N1aux, N2aux, N1, N2) :- X=0, contarClasesAux(T, N1aux, N2aux, N1, N2).
contarClasesAux([], N1, N2, N1, N2).
	
count(X, Lista, Ocurrencias) :- countAux(X, Lista, 0, Ocurrencias), !.

countAux(_, [], Ocurrencias, Ocurrencias).
countAux(X, [X|T], Aux, Ocurrencias) :- Aux1 is Aux+1, countAux(X, T, Aux1, Ocurrencias).
countAux(X, [_|T], Aux, Ocurrencias) :- countAux(X, T, Aux, Ocurrencias).

sum(List, Sum) :- sumAux(List, 0, Sum), !.

sumAux([], Sum, Sum).
sumAux([X|T], Acc, Sum) :- (number(X), Acc1 is Acc+X, sumAux(T,Acc1,Sum) ; sumAux(T, Acc, Sum)).

caminosPosibles(MatrizIn, I, J, Caminos) :- findall(Camino, caminoPosible(MatrizIn, I, J, [], Camino), Caminos).

caminoPosible(MatrizIn, I, J, CaminoAux, Camino) :- sujetable(MatrizIn,I,J), append(CaminoAux, [I/J], CaminoInv), reverse(CaminoInv, Camino), !.

%caminoPosible(MatrizIn, I, J, CaminoAux, Camino) :- eij(MatrizIn,I,J,Elem), Elem=0, Camino=CaminoAux.

% Camino para liberar horizontalmente.
caminoPosible(MatrizIn, I, J, CaminoAux, Camino) :- 

	eij(MatrizIn,I,J,Elem), Elem \= 0,
	\+ member(I/J,CaminoAux), 
	append(CaminoAux,[I/J],CaminoAux2), 
	J2 is J-1, J3 is J+1, 
	eij(MatrizIn,I,J2,Oizq), eij(MatrizIn,I,J3,Oder), 
	(
		Oizq<Elem,
		caminoPosible(MatrizIn,I,J3,CaminoAux2,Camino) ; 
		(
			Oder<Elem,
			caminoPosible(MatrizIn,I,J2,CaminoAux2,Camino) ; 
			Oder>=Elem,
			Oizq>=Elem,
			caminoPosible(MatrizIn,I,J2,CaminoAux2,CaminoInv), 
			reverse(CaminoInv, CaminoAux3),
			caminoPosible(MatrizIn,I,J3,CaminoAux3,Camino)
		)
	).

% Camino para liberar verticalmente.
caminoPosible(MatrizIn, I, J, CaminoAux, Camino) :-

	eij(MatrizIn,I,J,Elem), Elem \= 0,
	\+ member(I/J,CaminoAux), 
	append(CaminoAux,[I/J],CaminoAux2), 
	I2 is I-1, I3 is I+1, 
	eij(MatrizIn,I2,J,Oarriba), eij(MatrizIn,I3,J,Oabajo), 
	(
		Oarriba<Elem,
		caminoPosible(MatrizIn,I3,J,CaminoAux2,Camino) ; 
		(
			Oabajo<Elem,
			caminoPosible(MatrizIn,I2,J,CaminoAux2,Camino) ; 
			Oarriba>=Elem,
			Oabajo>=Elem,
			caminoPosible(MatrizIn,I2,J,CaminoAux2,CaminoInv), 
			reverse(CaminoInv, CaminoAux3),
			caminoPosible(MatrizIn,I3,J,CaminoAux3,Camino)
		)
	).

caminoMasCorto(MatrizIn, I, J, Camino) :- 

	caminosPosibles(MatrizIn, I, J, Caminos), 
	maplist(length, Caminos, LongitudesCaminos), 
	min_member(Min, LongitudesCaminos),
	nth0(Indice,LongitudesCaminos,Min),
	nth0(Indice,Caminos,Camino), !.

pasos(MatrizIn,I,J,Pasos) :- 

	(eij(MatrizIn,I,J,Elem), Elem == 0, Pasos = 0 ; 
	(caminoMasCorto(MatrizIn,I,J,Camino), length(Camino,Pasos) ; Pasos = -1)), !.

pasosElementos(MatrizIn, Pasos) :-

	length(MatrizIn,I1), I2 is I1-1,
	nth0(0,MatrizIn,Row),
	length(Row,J1), J2 is J1-1,
	I in 0..I2, J in 0..J2,
	indomain(I), indomain(J),
	pasos(MatrizIn,I,J,Pasos).

funcionDeEvaluacion(MatrizIn, SumaPasos, PromedioPasos, MinPasos, MaxPasos, MatrizOut) :-

	findall(Pasos, pasosElementos(MatrizIn,Pasos), MatrizOut), 
	(\+ member(-1, MatrizOut),
	delete(MatrizOut, 0, MatrizOutAux),
	sum(MatrizOutAux, SumaPasos), totalObjetos(MatrizIn, N),
	PromedioPasos is SumaPasos/N, min_member(MinPasos, MatrizOutAux), max_member(MaxPasos, MatrizOutAux) ; 
	SumaPasos = -1, PromedioPasos = -1, MinPasos = -1, MaxPasos = -1), !.

evaluar :- 

%	open("EvaluacionMallas.txt", write, Stream), 
	findall(N1N2SumaPasos, evaluarAux(N1N2SumaPasos), L), 
%	close(Stream),
	
	open("LimitesPasos.txt", write, Stream3), 
	findall(LimitesPasos, limitesPasosArregloFijo(L,LimitesPasos,Stream3), ListaLimitesPasos),
	close(Stream3),
	
	writeln(ListaLimitesPasos), nl.
	
evaluarAux(N1/N2/SumaPasos) :- 

	malla(MatrizIn),
	funcionDeEvaluacion(MatrizIn, SumaPasos, _, _, _, _),
	flatten(MatrizIn,MatrizIn2),
	count(1, MatrizIn2, N1), count(2, MatrizIn2, N2).	% Quitar punto.
%	escribirResultado(MatrizIn2, MatrizOut, SumaPasos, PromedioPasos, MinPasos, MaxPasos, Stream, N1, N2).
	
limitesPasosArregloFijo(L, LimitesPasos, Stream) :- 

	LimitesPasosAux = [],
	findall(A/B, member(A/B/_, L), Combinaciones_NsAux),
	eliminarDuplicados(Combinaciones_NsAux,Combinaciones_Ns),
	member(N1/N2,Combinaciones_Ns),
	append(LimitesPasosAux, [N1/N2], LimitesPasosAux2),
	findall(Elem, member(N1/N2/Elem, L), L2),
	delete(L2, -1, L3),
	(min_member(Min,L3),
	max_member(Max,L3),
	%writeln(Stream, Min), 
	write(Stream, N1/N2), write(Stream, ","), writeln(Stream, Min/Max), 
	append(LimitesPasosAux2, [Min/Max], LimitesPasos) ;
	\+ min_member(_,L3), Min = -1,
	\+ max_member(_,L3), Max = -1,
	%writeln(Stream, Min), 
	write(Stream, N1/N2), write(Stream, ","), writeln(Stream, Min/Max), 
	append(LimitesPasosAux2, [Min/Max], LimitesPasos)).
	
eliminarDuplicados(ListaIn, ListaOut) :- eliminarDuplicadosAux(ListaIn, [], ListaOut).

eliminarDuplicadosAux([X|T], ListaAux, ListaOut) :- 

	(member(X, ListaAux), eliminarDuplicadosAux(T, ListaAux, ListaOut) ; 
	append(ListaAux, [X], ListaAux2), eliminarDuplicadosAux(T, ListaAux2, ListaOut)), !.

eliminarDuplicadosAux([], ListaOut, ListaOut).

escribirResultado(MatrizIn, MatrizOut, SumaPasos, PromedioPasos, MinPasos, MaxPasos, Stream, N1, N2) :-

	length(MatrizIn,R1), R is R1-2,
	nth0(0,MatrizIn,Row),
	length(Row,C1), C is C1-2,
	write(Stream, R), write(Stream, "x"), write(Stream, C), write(Stream, ","), write(Stream, N1), write(Stream, ","), write(Stream, N2), nl(Stream),
	escribirLista(Stream, MatrizIn),
	escribirLista(Stream, MatrizOut),
	write(Stream, SumaPasos), write(Stream, ","), write(Stream, PromedioPasos), write(Stream, ","), write(Stream, MinPasos), write(Stream, ","), write(Stream, MaxPasos), nl(Stream), nl(Stream).

escribirLista(_, []).
escribirLista(Stream, [X]) :- writeln(Stream,X), !.
escribirLista(Stream, [X|T]) :- write(Stream,X), write(Stream,","), escribirLista(Stream, T), !.

cambiarElementoMatriz(MatrizIn, I, J, Valor, MatrizOut) :- 
	nth0(I,MatrizIn,Row), 
	length(Row,N1), 
	length(L1,N1), 
	nth0(J, L1, Valor), 
	maplist(cambiar(Valor), Row, L1, L2),
	length(MatrizIn,N2), 
	length(L3,N2), 
	nth0(I, L3, L2), 
	maplist(cambiar(L2), MatrizIn, L3, MatrizOut).

cambiar(Valor,X,Y,Z) :- (var(Y), Z=X ; \+ var(Y), Z=Valor), !.

rango(Min, Max, Lista) :- Aux in Min..Max, findall(Aux, indomain(Aux), Lista).

crearMatriz(N,M,Valor,Matriz) :- length(Row,M), maplist(=(Valor),Row), length(Matriz,N), maplist(=(Row),Matriz).

inicializarLista(N,Valor,Lista) :- length(Lista,N), maplist(=(Valor),Lista).

writeMatrix([]) :- nl.
writeMatrix([X|T]) :- writeln(X), writeMatrix(T).

transpuesta(MatrizIn, MatrizOut) :- nth0(0,MatrizIn,Row), length(Row,N), transpuestaAux(MatrizIn, 0, N, [], MatrizOut).

transpuestaAux(MatrizIn, Cont, N, MatrizOutAux, MatrizOut) :- (Cont<N, findall(Elem, eij(MatrizIn, _, Cont, Elem), Row), Cont2 is Cont+1, append(MatrizOutAux, [Row], MatrizOutAux2), transpuestaAux(MatrizIn, Cont2, N, MatrizOutAux2, MatrizOut) ; MatrizOut = MatrizOutAux), !.

rotar90(MatrizIn, MatrizOut) :- transpuesta(MatrizIn, MatrizOutAux), maplist(reverse, MatrizOutAux, MatrizOut).

reflejarHorizontal(MatrizIn, MatrizOut) :- maplist(reverse, MatrizIn, MatrizOut).
%reflejar(MatrizReflexion, MatrizIn, MatrizOut) :- matrix_multiply(MatrizReflexion,MatrizIn,MatrizOut).

eliminarSimilares :- open("baseConocimientoMallasFiltradas.pl", write, Stream2), eliminarSimilaresAux(Stream2,0), close(Stream2).

eliminarSimilaresAux(Stream2, Cont) :- 

	(mallaAux(MatrizIn),	
	
	rotar90(MatrizIn, MatrizOut1), 
	rotar90(MatrizOut1, MatrizOut2), 
	rotar90(MatrizOut2, MatrizOut3), 
	
	reflejarHorizontal(MatrizIn, MatrizOut4),
	reflejarHorizontal(MatrizOut1, MatrizOut5), 
	reflejarHorizontal(MatrizOut2, MatrizOut6), 
	reflejarHorizontal(MatrizOut3, MatrizOut7), 
	
	retract(mallaAux(MatrizIn)),

	(mallaAux(MatrizOut1), 
	retract(mallaAux(MatrizOut1)) ; true),

	(mallaAux(MatrizOut2), 
	retract(mallaAux(MatrizOut2)) ; true),
	
	(mallaAux(MatrizOut3), 
	retract(mallaAux(MatrizOut3)) ; true),
	
	(mallaAux(MatrizOut4), 
	retract(mallaAux(MatrizOut4)) ; true),

	(mallaAux(MatrizOut5), 
	retract(mallaAux(MatrizOut5)) ; true),
	
	(mallaAux(MatrizOut6), 
	retract(mallaAux(MatrizOut6)) ; true),
	
	(mallaAux(MatrizOut7), 
	retract(mallaAux(MatrizOut7)) ; true),
	
	Cont2 is Cont+1,
	writeln(Cont2),
	
	% No se usa "assert" porque si se hace más de 2 veces se agregaran repetidos.
	write(Stream2,malla(MatrizIn)), writeln(Stream2,.), eliminarSimilaresAux(Stream2,Cont2) ; true), !.
	
% [SumaPasos,N1,N2]	
resultadosVentana(ListaSumas) :- findall(SumaPasos, (mallaV(MatrizIn), contarClases(MatrizIn, N1, N2), funcionDeEvaluacion(MatrizIn, SumaPasos, _, _, _, _)), ListaSumas).
resultadosRefuerzo(ListaSumas) :- findall([SumaPasos,N1,N2], (mallaR(MatrizIn), contarClases(MatrizIn, N1, N2), funcionDeEvaluacion(MatrizIn, SumaPasos, _, _, _, _)), ListaSumas).

escribirSumas :- open("comparacionAlgoritmos.txt", write, Stream), 
	resultadosVentana(ListaSumas1), resultadosRefuerzo(ListaSumas2),
	escribirSumasAux(Stream, ListaSumas1, ListaSumas2),
	close(Stream).
escribirSumasAux(Stream, [X1|T1], [X2|T2]) :- 
	nth0(0,X1,S1), nth0(0,X2,S2), 
	nth0(1,X1,C1), nth0(2,X1,C2), 
	write(Stream,S1), write(Stream," "), write(Stream,S2), write(Stream," "), write(Stream,C1), write(Stream,","), writeln(Stream,C2),
	escribirSumasAux(Stream, T1, T2), !.
escribirSumasAux(_, [], []).




test(MatrizIn, N, Cont, MatrizOut) :- Cont<N, reflejar2(MatrizIn, MatrizOut), Cont2 is Cont+1, test(MatrizIn, N, Cont2, MatrizOut).
suma(X,Y) :- Y is X+1.



