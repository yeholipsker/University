%Name:Yehoshua Lipsker
%ID:204038533
%Group:89310-04
%UserName:lipskey

getElement([],_,undefined).
getElement([Head|_],0,Head):-!.
getElement([_|Rest],N,R):-N1 is N-1,getElement(Rest,N1,R).

mulList(L,R):-mulList(L,1,R).
mulList([],F,F).
mulList([H|T],F,R) :- F2 is F * H, mulList(T,F2,R).

pairs(L,R) :- pairs(L,[],R).
pairs([],F,F) :- !.
pairs([H|T],F,R) :- pairsHelper(H,T,F2), append(F,F2,F3),pairs(T,F3,R).

pairsHelper(_,[],[]) :- !.
pairsHelper(A,[H|T],[[A,H]|R]) :- pairsHelper(A,T,R).

mergeLists([], [], []).
mergeLists([], LS, LS) :- !.
mergeLists(LS, [], LS) :- !.
mergeLists([H|T], [X|Y], [H,X|Z]) :- mergeLists(T,Y,Z).

takeFirst([], []) :- !.
takeFirst([[H|_]|Tail], [H|Rest]) :- takeFirst(Tail,Rest).

dropFirst([], []) :- !.
dropFirst([[_|T]|Tail], [T|Rest]) :- dropFirst(Tail,Rest).

selectCol([],_,[]) :- !.
selectCol(LSS,1,Result) :- takeFirst(LSS,Result),!.
selectCol(LSS,N,Result) :- N1 is N-1, dropFirst(LSS,NewLSS), selectCol(NewLSS,N1,Result).

transpose([[]|_],[]) :- !.
transpose(LSS,[Col|Result]) :- selectCol(LSS,1,Col),dropFirst(LSS,NewLSS),transpose(NewLSS,Result).