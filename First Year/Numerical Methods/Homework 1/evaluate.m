function procent = evaluate(cale,w,tip,count_bins)

nr=0;

%Concatenam directorului de teste cele 2 subdirectoare

nume1= [cale 'cats/'];
nume2= [cale 'not_cats/'];

%In functie de tipul histogramei

if strcmp(tip,'RGB') == 1
	
	%Extragem fisierele din primul subdirector si sarim peste . si ..

    files = dir(nume1);
    files =files(3:length(files));

	%Pentru fiecare imagine calculam y si daca acesta are semnul corect
	%crestem numarul de teste corecte

    for i=1:length(files)

        x=rgbHistogram([nume1 files(i).name],(length(w) -1)/3);
        x(length(x)+1)=1;
        y=w*x';

        if y>0
            nr = nr+1;
        endif

    endfor

    l=length(files);

	%Extragem fisierele din al doilea subdirector

    files = dir(nume2);
    files =files(3:length(files));

	%Procedam analog ca mai sus

    for i=1:length(files)
        x=rgbHistogram([nume2 files(i).name],(length(w) -1)/3);
        x(length(x)+1)=1;
        y=w*x';

        if y<0
            nr = nr+1;
        endif
    endfor

    l=l+length(files);
 endif
 
 if strcmp(tip,'HSV') == 1

	%Procedam la fel ca pentru RGB

    files = dir(nume1);
    files =files(3:length(files));

    for i=1:length(files)
        x=hsvHistogram([nume1 files(i).name],(length(w) -1)/3);
        x(length(x)+1)=1;
        y=w*x';

        if y>0
            nr = nr+1;
        endif

    endfor
    
    l=length(files);
    files = dir(nume2);
    files =files(3:length(files));

    for i=1:length(files)
        x=hsvHistogram([nume2 files(i).name],(length(w) -1)/3);
        x(length(x)+1)=1;
        y=w*x';

        if y<0
            nr = nr+1;
        endif

    endfor
    l=l+length(files);
 endif

procent=nr*100/l;

endfunction
    
