(*
Name:Yehoshua Lipsker
ID:204038533
Group:89310-04
UserName:lipskey
*)

(*part1*)

exception IllegalArgumentException;

fun rotate([],n) = if (n<0) then raise IllegalArgumentException else []
	|rotate(ls,0) = ls
	| rotate ((x::rest),n) = if (n<0) then raise IllegalArgumentException else rotate(rest@[x], n-1);
	
fun split [] = ([],[])
	| split [x] = ([x],[])
	| split (first::second::rest) =
		let
			val (splitted1, splitted2) = split rest
		in
			((first::splitted1),(second::splitted2))
		end;
		
fun merge ([]:int list,[]:int list) = []
	| merge (ls,[]) = ls
	| merge ([],ls) = ls
	| merge (x::restx,y::resty) = if(x < y) then x::merge(restx,y::resty) else y::merge(x::restx,resty);
	
fun sort ([]:int list) = []
	| sort([x]) = [x]
	| sort ls = 
		let
			val (splitted1, splitted2) = split ls
		in
			merge(sort(splitted1),sort(splitted2))
		end;
		
(*part2*)

fun map (f, ls) =
    if null ls then
        [ ]
    else
        f (hd ls) :: map(f, (tl ls)) ;
	
fun choose (k, []) = if (k<0) then raise IllegalArgumentException else []
	| choose (0, ls) = [[]]
	| choose (k, x::rest) = if (k<0) then raise IllegalArgumentException else if(k = List.length(x::rest))
								then [x::rest]
							else
								map(fn(inLs)=>x::inLs,choose(k-1,rest))@choose(k,rest);
							
fun isPolindrom(str : string) = str = implode(rev(explode(str)));

(*part3*)

datatype Arguments = IntPair of int * int
					| RealTriple of real * real * real
					| StringSingle of string;
datatype OutputArgs = IntNum of int | RealNum of real | Str of string;

fun multiFunc (IntPair(x,y)) = IntNum(x*y)
	| multiFunc (RealTriple(x, y, z)) = RealNum((x + y + z) / 3.0)
	| multiFunc (StringSingle(str)) = Str(implode(rev(explode(str))));
	
(*part4*)
	
datatype Square = Alive of int | Dead of int;

datatype GameStatus = Extinct | OnGoing;

type LifeState = Square list list * GameStatus;
									
fun createLifeGrid (0,lives) = []
	| createLifeGrid (n, lives) = 	let
										fun mem ([ ], x) = false
											| mem (h::t, x) = (h = x) orelse mem(t, x)
										fun createSquare(i,j) = if mem(lives,(i,j))
																	then (Alive 0)
																else
																	(Dead 0)
										fun createRow(_,0) = []
											| createRow(a,b) = createRow(a,b-1)@[createSquare(a-1,b-1)]
										fun loop(0,_) = []
											| loop(c,d) = loop(c-1,d)@[createRow(c,d)]
									in
										if (n<0) then raise IllegalArgumentException else loop(n,n)
									end;
									
fun determineStatusOf([]) = Extinct
	| determineStatusOf(firstRow::rest) = 	let
												fun determineStatusOfRow([]) = Extinct 
													| determineStatusOfRow(x::resOfRow) = 	case x
																								of Alive(_) => OnGoing
																								|  Dead(_) => determineStatusOfRow(resOfRow)
											in
												case determineStatusOfRow(firstRow)
													of OnGoing => OnGoing
													|  Extinct => determineStatusOf(rest)
											end;
											
fun nextGeneration([]) = []
	| nextGeneration(grid) = let
								val gridLength = List.length(grid)
								fun NbrValue(i,j) = if (i = []) then 0 else 
														if (j>=0 andalso j<List.length(i)) then case List.nth(i,j) of Alive(_) => 1 | Dead(_) => 0 else 0	
								fun numOfNbrs(i,j) = let
														val iMinus1 = if (i-1 < 0) then [] else List.nth(grid,i-1)
														val iCurrent = List.nth(grid,i)
														val iPlus1 = if (i+1 >= gridLength) then [] else List.nth(grid,i+1)
													in 
														NbrValue(iMinus1,j-1) + NbrValue(iMinus1,j) + NbrValue(iMinus1,j+1) +
														NbrValue(iCurrent,j-1) + NbrValue(iCurrent,j+1) +
														NbrValue(iPlus1,j-1) + NbrValue(iPlus1,j) + NbrValue(iPlus1,j+1)
													end;
								fun nextSquare(sqr,i,j) = 	let
																val num = numOfNbrs(i,j)
															in
																case sqr
																	of Alive(x) => (case num
																						of 0 => (Dead 0)
																						|  1 => (Dead 0)
																						|  _ => if num > 3
																									then (Dead 0)
																								else
																									(Alive (x+1)))
																	|  Dead(x) => (case num
																						of 3 => (Alive 0)
																						|  _ => (Dead (x+1)))
															end;
								fun createRow(_,0) = []
									| createRow(a,b) = createRow(a,b-1)@[nextSquare(List.nth(List.nth(grid,a-1),b-1),a-1,b-1)]
								fun loop(0,_) = []
									| loop(c,d) = loop(c-1,d)@[createRow(c,d)]
							in
								loop(gridLength,gridLength)
							end;

fun determineNState((grid, x):LifeState,0):LifeState = (grid,x)
	| determineNState((grid,Extinct),n) = if (n<0) then raise IllegalArgumentException else determineNState((grid,Extinct),n-1)
	| determineNState((grid,OnGoing),n) = 	let
												val nextGen = nextGeneration(grid)
											in
												if (n<0) then raise IllegalArgumentException else determineNState((nextGen,determineStatusOf(nextGen)),n-1)
											end;
	
(*part4*)
	
exception EmptyList;

datatype 'a Seq = Cons of 'a * (unit -> 'a Seq) | Nil;

fun head (Cons(x,_)) = x 
	| head Nil = raise EmptyList;
	
fun tail (Cons(_,t)) = t () 
	| tail Nil = raise EmptyList;

fun take (0, _) = [] 
	| take (n, Nil) = raise EmptyList 
	| take (n, Cons(h, t)) = h :: take(n-1, t());
											
fun upF (u, f) = Cons(u, fn () => upF (f u, f));

(use "test.sml")