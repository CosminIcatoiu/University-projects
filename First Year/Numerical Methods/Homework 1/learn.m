function w = learn( X, t)

[n m]=size(X);

%Adaugam ultima coloana cu 1-uri

X(1:n,m+1)=1;

%Pentru a rezolva sistemul prezentat in task am considerat ca metoda
%Householder este eficienta, astfel am trecut X'*X in partea stanga
%a ecuatiei si am descompus-o cu Householder in matrice QR si apoi am rezolvat
% sistemul superior triunghilat

w=Householder(X'*X,X'*t');

endfunction
