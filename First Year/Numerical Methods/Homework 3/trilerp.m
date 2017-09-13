function value = trilerp(stack, row, col, level)

[m n p]=size(stack);

%Daca vreuna din valorile date ca parametru depasesc dimensiunile imaginii
%sau sunt mai mici decat 1 atunci returnam 0

if level > p || row > m || col > n 
    value=0;
    return
else
    if level < 1 || row < 1 || col <1
        value=0;
        return
    else

    	%Altfel, apelam functia bilerp pentru cele 2 matrici de pe nivelele
        %vecine valorii level

		if level == floor(level)
	        r1=bilerp( stack(:,:,level),row,col);
        	r2=bilerp( stack(:,:,level),row,col);
        else        
        	r1=bilerp( stack(:,:,floor(level)),row,col );
        	r2=bilerp( stack(:,:,floor(level) +1),row,col);
        end
        %Dupa care interpolam liniar intre cele 2 valori obtinute anterior
        
        x=zeros(1,p);

        x(floor(level))=r1;
        x(floor(level)+1)=r2;

        value=lerp(x,level);
    end
end
end
