function x = Householder( A, b)

%Implementarea folosita este cea prezentata la curs de domnul profesor
%avand o mica eficientizare prin vectorizari in interiorul for-ului mare

[n m]=size(A);

%Pentru eficienta vom pastra matricea R in interiorul lui A

for p=1:m
	
	%Pentru fiecare coloana calculam sigma si beta 

    sigma=norm(A(p:n,p));
    if A(p,p) < 0
        sigma= -sigma;
    endif
    beta=sigma*(sigma + A(p,p));
	
	%Calculam vectorul Householder

    u(1:p-1)=0;
    u(p)=sigma+A(p,p);
    u(p+1:n)=A(p+1:n,p);

	%Punem pe diagonala principala -sigma si sub ea 0
    
    A(p,p)=-sigma;
    A(p+1:n,p)=0;
    
	%Calculam ce se obtine deasupra diagonalei principale in matricea R

    ro(p+1:m)= u * A(:,p+1:m)/beta;
	B(:,p+1:m)=u'*ro(p+1:m);
    A(:,p+1:m)=A(:,p+1:m)-B(:,p+1:m);

    %Calculam modificarile asupra vectorului b

    ro=u*b/beta;
    b=b-ro*u';
endfor

R=A;

%Apelam functia ce rezolva sisteme superior triunghiluare

x=SST(R,b);

endfunction
