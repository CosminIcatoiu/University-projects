function stack =image_stack(img, num_levels)

%Citim imaginea
A=imread(img);

%Initializam factorul de blurare cu valoarea din enunt

K=ones(3);
K=1/9*K;

[m n]=size(A);

%Initializam matricea 3D

stack=zeros(m,n,num_levels);

%Punem pe primul nivel matricea initiala
stack(:,:,1)=A;

for i=2:num_levels

    %Apoi pentru fiecare nivel bluram nivelul anterior cu factorul dat,avand
    %grija sa pastram dimensiunile imaginii
    
    stack(:,:,i)=conv2(stack(:,:,i-1),K,'same');
end

end
