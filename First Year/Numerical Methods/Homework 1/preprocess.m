function [ X t ]= preprocess( cale, tip, count_bins )

%Concatenam caii catre director cele 2 subdirectoare

nume1= [cale '/cats/'];
nume2= [cale '/not_cats/'];

%In functie de tipul histogramei

if strcmp(tip,'RGB') == 1
	%Extragem fisierele din primul director si eliminam . si ..

    files = dir(nume1);
    files =files(3:length(files));

	%Pentru fiecare imagine calculam histograma si o introducem in matrice

    for i= 1:length(files)
        X(i,:)=rgbHistogram([nume1 files(i).name],count_bins);
    endfor

	% calculam etichetele pentru primul director

	t(1:length(files))=1;
    l=length(files);
	%Extragem fisierele din al doilea director si eliminam . si ..

    files= dir(nume2);
    files= files(3:length(files));
    
	%Pentru fiecare imagine din al doilea subdirector calculam histograma
	%si o introducem in matrice pe pozitia corespunzatoare

    for i= 1:length(files)
	    X(l+i,:)=rgbHistogram([nume2 files(i).name ],count_bins);
    endfor
	
	%calculam etichetele pentru al doilea subdirector

	t(l+1:l+length(files))=-1;
endif

if strcmp(tip,'HSV') == 1
	
	%Procedam la fel ca pentru RGB, apeland de aceasta data functia pentru HSV

    files = dir(nume1);
    files =files(3:length(files));
    
    for i= 1:length(files)
        X(i,:)=hsvHistogram([nume1 files(i).name ],count_bins);
    endfor

	t(1:length(files))=1;
    l=length(files);

    files= dir(nume2);
    files= files(3:length(files));
    
    for i= 1:length(files)
	    X(l+i,:)=hsvHistogram([nume2 files(i).name ],count_bins);
    endfor

	t(l+1:l+length(files))=-1;
endif

endfunction 
