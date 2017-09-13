function x = SST( A, b )

[n n]=size(A);
 
x=zeros(1,n);

%Folosind formulele din laborator se rezolva sistemul

for i=n:-1:1
    s=0;

    s=sum(A(i,i+1:n).*x(i+1:n));

	x(i)=(b(i)-s)/A(i,i);
endfor

endfunction
