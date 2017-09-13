function[ r ]=Power(fisier, d, tol)

%Aflam cu ajutorul functiei citire matricea M si numarul de site-uri

[M N]=Citire(fisier);

aux=zeros(N,1);
r(1:N,1)=1/N;

%Calculam matricea P a carei vector propriu principal este r

K=ones(N);
P=d*M+(1-d)/N*K;

%Calculam cu ajutorul algoritmului MPD r-ul 

while norm(r-aux)> tol

	aux=r;
	z=P*r;
	r=z/norm(z);

endwhile

%La final normam vectorul

r=r/norm(r,1);

endfunction
