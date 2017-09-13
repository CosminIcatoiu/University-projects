function[ r ]= Iterative( fisier, d, tol)

%Apelam functia de citire si obtinem matricea M si numarul de site-uri

[M N]=Citire(fisier);

%Initializam r-ul asa cum se specifica in enunt 

aux=zeros(N,1);
r(1:N,1)=1/N;

%Calculam vectorul r cu ajutorul relatiei de recurenta 

while( norm(r-aux) > tol )

	aux=r;
	r=d*M*r +((1-d)/N)*ones(N,1);

endwhile

endfunction
	

