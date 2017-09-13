function [ h ] = rgbHistogram ( img, count_bins )

%Calculam lungimea intervalelor si citim imaginea

k=256/count_bins;

A=imread(img);

%Aducem valorile din matrice in intervalul [0;count_bins)

A=idivide(A,k);

% Pentru count_bins diferit de 256
if k!=1

	%extragem matricea cu valorile pentru R 
    B=A(:,:,1);

	%initializare are sens pentru ca daca valorile in R sunt de la 
	%0 la 30 functia accumarray nu va pune pe pozitia 31 valoarea 0	
    red=zeros(1,count_bins);

  	u=accumarray(B(:)+1,1);
    red(1:length(u))=u;
	%calculam cu ajutorul functiei accumarray numarul de aparitii al fiecarui rest
	

	%Procedam analog ca mai sus pentru vectorii G si B
    B=A(:,:,2);

    green=zeros(1,count_bins);
	u=accumarray(B(:)+1,1);
    green(1:length(u))=u;

    B=A(:,:,3);

    blue=zeros(1,count_bins);
	u=accumarray(B(:)+1,1);
    blue(1:length(u))=u;
	
	%Cream histograma petru imaginea data
    h=[red green blue];

endif

%Pentru count_bins=256 este un caz special pentru ca atunci cand aduni
%matricei de pixeli 1 valoarea 255 nu devine 256
if k==1

    B=A(:,:,1);

	%Procedeul este absolut asemanator singura diferenta este ca pentru
	%fiecare vector calculam "manual" valoarea de pe ultimele 2 pozitii

    red=zeros(1,count_bins);

    red(256)=length(B(B == 255));%calculam valoarea de pe ultima pozitie
    
	u=accumarray(B(:)+1,1);
    red(1:length(u))=u;
    red(255) =red(255)-red(256);%calculam valoarea de pe penultima pozitie

	%Procedam analog ca mai sus

    B=A(:,:,2);

    green=zeros(1,count_bins);
    
	green(256)=length(B(B == 255));

	u=accumarray(B(:)+1,1);
    green(1:length(u))=u;
    green(255) =green(255)-green(256);

    B=A(:,:,3);

    blue=zeros(1,count_bins);

    blue(256)=length(B(B == 255));

	u=accumarray(B(:)+1,1);
    blue(1:length(u))=u;
    blue(255) =blue(255)-blue(256);

    h=[red green blue];

endif

endfunction
