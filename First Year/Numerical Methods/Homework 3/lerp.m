function value = lerp(v, x)

%daca x-ul e in afara vectorului nu putem face interpolare
if x < 1 || x > length(v)
    value =0;
else
    if x == floor(x)

    %daca x-ul e chiar un numar intreg din vector atunci intoarcem valoarea
    %de pe pozitia x

        value=v(x);
    else

    %aflam coeficientii a si b ai functiei liniare si apoi returnam valoarea
    %functiei in punctul x dat ca parametru

        a=double(v(floor(x)+1))-double(v(floor(x)));           
        b=double(v(floor(x)))-double(a*floor(x));
        value=a*x+b;
    end
end
