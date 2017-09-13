function [ r1 r2 r3] = PageRank(fisier,d,tol)

%Citim din fisier pentru a obtine valorile va1 si val2

fid=fopen(fisier,"r");

N=fscanf(fid,'%d',1);

for i=1:N

	x=fscanf(fid,'%d',1);
	nr=fscanf(fid,'%d',1);
	y=fscanf(fid,'%d',[1,nr]);

endfor

val1=fscanf(fid,'%f',1);
val2=fscanf(fid,'%f',1);

fclose(fid);

%Deschidem un nou fisier in care vom scrie rezultatele

fopen([fisier ".out"],"w");

%Scriem numarul de site-uri

fprintf(fid,'%d',N);
fprintf(fid,'\n\n');

%Calculam rezultatele returnate de cele 3 functii

r1=Iterative(fisier,d,tol);

r2=Algebraic(fisier,d,tol);

r3=Power(fisier,d,tol);

%Scriem rezultatele functiei Iterrative

for i=1:N

	fprintf(fid,'%f',r1(i,1));
	fprintf(fid,'\n');

endfor


fprintf(fid,'\n');

%Scriem rezultatele functiei Algebraic

for i=1:N

	fprintf(fid,'%f',r2(i,1));
	fprintf(fid,'\n');

endfor

fprintf(fid,'\n');

%Scriem rezultatele functiei Power

for i=1:N

	fprintf(fid,'%f',r3(i,1));
	fprintf(fid,'\n');

endfor

fprintf(fid,'\n');

pr=r2;
index(1:N,1)=[1:N];

%Sortam rezultatele functiei a 2-a in acelasi timp cu un vector de indici

for i=1:N
	for j=i+1:N
		if pr(i,1)<pr(j,1) - tol

			aux=pr(i,1);
			pr(i,1)=pr(j,1);
			pr(j,1)=aux;

			aux=index(i,1);
			index(i,1)=index(j,1);
			index(j,1)=aux;

		endif
	endfor
endfor

%Transformam rezultatele functiei a 2-a cu ajutorul functiei Apartenenta

for i=1:N
	pr(i,1)=Apartenenta(pr(i,1),val1,val2);
endfor

%Scriem in fisier rezultatele transformarii

for i=1:N
	fprintf(fid,'%d ',i)
	fprintf(fid,'%d ',index(i,1));
	fprintf(fid,'%f',pr(i,1));
	fprintf(fid,'\n');
endfor

fclose(fid);

endfunction
