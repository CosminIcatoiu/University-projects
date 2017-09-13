function [ Q R ]= GS(A)

%Algoritmul Gramm-Schmidt modificat, implementat din laborator

[n n]=size(A);

R=zeros(n);

Q=zeros(n);

for i=1:n

	R(i,i)=norm(A(:,i));
	Q(:,i)=A(:,i)/R(i,i);

	for j= i+1:n

		R(i,j)=Q(:,i)'*A(:,j);
		A(:,j)=A(:,j)-Q(:,i)*R(i,j);

	endfor

endfor
	
