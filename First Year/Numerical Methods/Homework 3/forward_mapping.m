function img_out = forward_mapping(img_in, T)

A=imread(img_in);
[m n]=size(A);

% Cu ajutorul dimensiunilor imaginii initiale si a matriciei de transformare
% aflam noile dimensiuni, formula fiind una obtinuta manual (geometric)

a=n*abs(T(2,1))+m*abs(T(1,1));
b=n*abs(T(1,1))+m*abs(T(2,1));

%avem grija ca dimensiunile sa fie intregi si sa nu avem borduri negre la noua
%imagine

a=round(a)-1;
b=round(b)-1;

%initializam noua imagine

img_out=zeros(a,b);

%in functie de operatia pe care trebuie sa o efectuam( scalare sau rotire)
if( T(1,2) ==0 && T(1,1) > 0)
    
    %La scalare
    %cream un vector x care va contine toate perechile de indici din prima 
    %imagine sub forma x(1,i) si x(2,i)
    
    k=0;
    y(1:n)=[1:n];
    for i=1:m
        x(1,k*n+1:(k+1)*n)=i;
        x(2,k*n+1:(k+1)*n)=y;
        k=k+1;
    endfor
    
    %aplicam transformarea indicilor

    y=T*x;
    y=round(y);
    y=y+1;

    %aflam intensitatea imaginii in fiecare punct si scriem imaginea
    
    for i=1:m*n
        img_out(y(1,i),y(2,i))=A(x(1,i),x(2,i));
    end
    imwrite(mat2gray(img_out),'file.png');
else
    
    %La rotire
    %cream acelasi vector ca la scalare
    k=0;
    y(1:n)=[1:n];
    for i=1:m
        x(1,k*n+1:(k+1)*n)=i;
        x(2,k*n+1:(k+1)*n)=y;
        k=k+1;
    endfor
    
    %Deoarece indicii dupa aplicarea transformarii pot fi si negativi trebuie
    %sa vedem care va fi minimul, fiind evident ca minimul se atinge indiferent
    %de unghi pentru unul din colturi
    
    aux=T*[1 n;1 1;m 1;m n]';
    aux1=min(aux(1,:));
    aux2=min(aux(2,:));

    y=T*x;

    %Daca exista indici negativi adunam minimul obtinut anterior pentru a aduce
    % toti indicii in 1:a respectiv 1:b

    if(aux1 < 0)
        y(1,:)=y(1,:)+abs(aux1)+1;
    end
    if(aux2 < 0)
        y(2,:)=y(2,:)+abs(aux2)+1;
    end
    y=round(y);

    %Calculam intensitatea in fiecare punct si apoi scriem imaginea
    
    for i=1:m*n
        img_out(y(1,i),y(2,i))=A(x(1,i),x(2,i));
    end
    imwrite(mat2gray(img_out),'file.png');
end
