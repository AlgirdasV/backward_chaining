Pseudokodas:

backward_chaining(goal, lygis)
1: if tikslas yra tarp faktų
2:   then exit;
3: if tikslas nėra jau ieškotas
4:   then for visos taisykles
5:     if taisykle nepanaudota
6: 		   then if taisykle veda į tikslą
7:         then begin
8:				   reikalingos taisyklės += taisyklė
9:					 rasta produkcija = true
10:				 end
11:   end
12: 	if neradome į tikslą vedančių taisyklų
13: 	  then pasiekėme aklavietę
14: else ciklas
15: for reikalingos taisyklės
16:	  for taisyklės sąlygos
17:		  if sąlygos nėra tarp faktų
18:			  then backward_chaining(sąlyga, lygis+1)
19:		end
20:		if taisyklės sąlygos yra patenkintos
21:		  then return rastų taisyklių sąrašas
22:	end
23:	return tuščias vektorius