function y = Apartenenta(x, val1, val2)

%Initializam a-ul si b-ul astfel incat functia sa fie continua

a=1/(val2-val1);

b=(-val1)/(val2-val1);

%In functie de valoarea lui x returnam valoarea corespunzatoare

if x<= val1 && x>=0
	y=0;
else
	if x>=val2 && x<=1
		y=1;
	else
		y=a*x+b;
	endif
endif
