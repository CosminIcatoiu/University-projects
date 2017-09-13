function img_out = transform_image(img_in, k)

%Cream stack-ul de imagini

stack=image_stack(img_in,floor(k)+1);

[m n p]=size(stack);

%Initializam noua imagine
img_out=zeros(m,n);

for i=1:m
    for j=1:n

        %Aflam valoarea de pe fiecare pozitie apeland functia trilerp cu 
        %pozitia respectiva(i,j) si cu parametrul k al functiei

        img_out(i,j)=trilerp(stack,i,j,k);
    endfor
endfor

%La final scriem noua imagine

imwrite(mat2gray(img_out),'file.png');
end
