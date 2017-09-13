function[ r ]=Algebraic(fisier,d)

%Apelam functia pentru a obtine matricea M si numarul de site-uri

[M N]=Citire(fisier);

B=eye(N);

%Descompunem QR matricea A cu ajutorul algoritmului Gramm-Schmidt

A=(B-d*M);

[Q R]=GS(A);

%Pentru a afla inversa lui A rezolvam sistemul pentru fiecare coloana a matricei
%A^(-1), coloana termenilor liberi fiind coloana corespunzatoare ca indice din B

for i=1:N
	K(:,i)=SST(R,Q'*B(:,i));
endfor

%La final calculam r-ul

r=K*(1-d)/N*ones(N,1);

endfunction
