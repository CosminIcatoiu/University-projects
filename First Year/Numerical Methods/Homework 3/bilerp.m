function value = bilerp(img, row, col)

[n m]=size(img);

%verificam ca linia sa fie in interiorul matricii pentru a fi posibila
%interpolarea, coloana fiind verificata la apelul functiei lerp

if row < n && row >= 1
    %daca row e chiar numar intreg facem lerp chiar pe pozitia aceea

    if row == floor(row)
        r1=lerp(img(row,:),col);
        r2=lerp(img(row,:),col); 

    else
    %altfel, interpolam liniar pe liniile vecine valorii row
    
        r1=lerp(img(floor(row),:),col);
        r2=lerp(img(floor(row)+1,:),col);
    end
else
    r1=0;
    r2=0;
end

% interpolam liniar intre cele 2 valori obtinute anterior

x=zeros(1,m);

if row >= 1 && row < n
    x( floor(row))=r1;
    x( floor(row) +1)=r2;
    value=lerp(x,row);
else
    value=0;
end

end
