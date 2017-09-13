function [M N] = Citire(fisier)

%Functia Citire este o functie care va returna matricea M si numarul de site-uri
%N, ea fiind utila pentru ca acest lucru este necesar in fiecare functie

%Deschidem fisierul pentru a citi din el

fid=fopen(fisier,"r");

%Citim numarul de site-uri

N=fscanf(fid,'%d',1);

%Variabile pe care le vom folosi ulterior

A=zeros(N);
K=zeros(N);

%Citim site-ul numarul de link-uri si construim pe loc cele doua matrice

for i=1:N

	x=fscanf(fid,'%d',1);
	nr=fscanf(fid,'%d',1);
	y=fscanf(fid,'%d',[1,nr]);

	K(i,i)=nr;
	A(i,y)=1;

endfor

%Inchidem fisierul cand am terminat de citit

fclose(fid);

%Prelucram cele doua matrice pentru a le aduce la forma dorita

for i=1:N

	if( A(i,i)!= 0)

		K(i,i)=K(i,i)-1;

	endif

	K(i,i)=1/K(i,i);
	A(i,i)=0;

endfor

%Calculam M-ul

M=(K*A)';

endfunction
