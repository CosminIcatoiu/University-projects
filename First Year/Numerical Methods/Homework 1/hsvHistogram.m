function [ hsv ] = hsvHistogram ( img , count_bins ) 

A=imread(img);

[h w q]=size(A);

%Extragem in vectori de dimensiune h*w matricile pentru R,G,B

R(1:h*w)=A(:,:,1);
G(1:h*w)=A(:,:,2);
B(1:h*w)=A(:,:,3);

%Convertim matricele la double pentru a putea face impartirile
R=double(R);
G=double(G);
B=double(B);

R=R/255;
G=G/255;
B=B/255;


%Vectorii cmax si cmin contin valorile maxime respectiv minime pe
%fiecare pozitie din cei 3 vectori R,G,B iar delta diferenta acestora 2

cmax=max(R,max(G,B));
cmin=min(R,min(G,B));
d=cmax-cmin;

%Pentru a nu irosi memorie am incercat sa folosesc G si B pe post de S si V

%Daca delta este 0 atunci H si G(echivalentul lui S) sunt 0
H(d==0)=0;
G(d==0)=0;

%Urmatoarele formule vectorizate calculeaza pe pozitiile pe care delta e diferit
%de 0, in functie de  valoarea lui cmax, valoarea lui H

H(cmax==R & d!=0)=60*mod((G(cmax==R & d!=0)-B(cmax==R & d!=0))./d(cmax==R & d!=0),6);
H(cmax==G & d!=0)=60*( (B(cmax==G & d!=0)-R(cmax==G & d!=0) )./d(cmax==G & d!=0) +2);
H(cmax==B & d!=0)=60*( (R(cmax==B & d!=0)-G(cmax==B & d!=0) )./d(cmax==B & d!=0) +4);

%B(echivalentul lui V) este cmax pentru orice valoare a lui delta, iar
%G este d/cmax pentru d diferit de 0

B=cmax;
G(d!=0)=double(d(d!=0)./cmax(d!=0));

%Aducem toti vectorii in intervalul [0;100)

H=H*100/360;
G=G*100;
B=B*100;

%Aducem valorile din matrice in intervalul [0;count_bins)

k=101/count_bins;

H=idivide(H,k)+1 ;
G=idivide(G,k)+1 ;
B=idivide(B,k)+1 ;

%Cu ajutorul functiei accumarray calculam numarul de aparitii din fiecare vector
% si le introducem in vectorul mare care calculeaza histograma

hsv=zeros(1,3*count_bins);
u=accumarray(H(:),1);
hsv(1:length(u))=u;

u=accumarray(G(:),1);
hsv(count_bins+1:count_bins+length(u))=u;

u=accumarray(B(:),1);
hsv(2*count_bins+1:2*count_bins + length(u))=u;

endfunction
        
