function img_out = inverse_mapping(img_in, T)

A=imread(img_in);
[m n]=size(A);

% Cu ajutorul dimensiunilor imaginii initiale si a matriciei de transformare
% aflam noile dimensiuni, formula fiind una obtinuta manual (geometric)

a=n*abs(T(2,1))+m*abs(T(1,1));
b=n*abs(T(1,1))+m*abs(T(2,1));

%Avem grija ca dimensiunile sa fie intregi si sa nu avem borduri negre la noua
%imagine ( de aceea scad -1)

a=round(a)-1;
b=round(b)-1;

%initializam noua imagine
img_out=zeros(a,b);

%in functie de operatia pe care trebuie sa o efectuam

if( T(1,2) ==0 && T(1,1) > 0)

    %La scalare
    %cream un vector x care va contine toate perechile de indici din noua 
    %imagine sub forma x(1,i) si x(2,i)
    
    k=0;
    y(1:b)=[1:b];
    for i=1:a
        x(1,k*b+1:(k+1)*b)=i;
        x(2,k*b+1:(k+1)*b)=y;
        k=k+1;
    endfor
    
    %aflam inversa lui T si aplicam transformarea pentru a afla pozitiile in
    %imaginea initiala
    
    T=1/(T(1,1)*T(2,2)-T(1,2)*T(2,1))*[T(2,2) -T(1,2); -T(2,1) T(1,1) ];
    y=T*x;

    %Cu ajutorul functiei bilerp aflam intensitatea in fiecare punct din noua
    %imagine si apoi scriem imaginea
    
    for i=1:a*b
        img_out(x(1,i),x(2,i))=round(bilerp(A,y(1,i),y(2,i)));
    end
    imwrite(mat2gray(img_out),'file.png');
else

    %La rotire
    %cream acelasi vector ca mai sus
    
    k=0;
    y(1:b)=[1:b];
    for i=1:a
        x(1,k*b+1:(k+1)*b)=i;
        x(2,k*b+1:(k+1)*b)=y;
        k=k+1;
    endfor
    
    %Trebuie sa procedam invers fata de forward_mapping, pentru ca daca vom
    %aplica transformarea pe indicii normali atunci vom obtine multi indici 
    %peste numarul de linii/coloane din matricea intiala
    
    %Aflam minimul indicilor daca am transforma matricea initiala
    
    aux=T*[1 n;1 1;m 1;m n]';
    aux1=min(aux(1,:));
    aux2=min(aux(2,:));

    %Aflam inversa lui T
    
    T=1/(T(1,1)*T(2,2)-T(1,2)*T(2,1))*[T(2,2) -T(1,2); -T(2,1) T(1,1) ];

    %Daca minimele obtinute anterior sunt negative inseamna ca trebuie sa 
    %mutam indicii din matricea finala, scazand din ei abs(aux1), respectiv,
    %abs(aux2) pentru a obtine indici corect la ulterioara transformare
    
    if aux1 < 0
        x(1,:)=x(1,:)-abs(aux1);
    end
    if aux2 < 0
        x(2,:)=x(2,:)-abs(aux2);
    end
    
    %Aplicam transformarea
    y=T*x;
    
    %Aducem indicii din matricea finala la loc
    if aux1<0
        x(1,:)=x(1,:)+abs(aux1);
    end
    if aux2<0
        x(2,:)=x(2,:)+abs(aux2);
    end
    
    %Aflam cu ajutorul functiei bilerp intensitatea in fiecare punct din noua
    %imagine si apoi scriem imaginea
    
    for i=1:a*b
        img_out(x(1,i),x(2,i))=bilerp(A,y(1,i),y(2,i));
    end
    imwrite(mat2gray(img_out),'file.png');
end
