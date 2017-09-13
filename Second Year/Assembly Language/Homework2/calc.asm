; decomment according to platform (Linux or Windows)
;%include "include/io.lin.inc"
%include "include/io.win.inc"

extern _malloc

section .data

    len1: dd 0
    len2: dd 0
    operation: db 0
    carryf: db 0
    sign_of_number: db 0
    counter: dd 0
    remember: dd 0
    
section .text

global do_operation

; TODO dissasemble the main.o file. Be sure not to overwrite registers used
; by main.o that he does not save himself.
; If you see your program going nuts, consider looking in the main.o disassembly
; for the causes mentioned earlier.

and_bits:
    
    ; salvam in cele 2 variabile len1 si len2 lungimile celor 2 numere
    ; ebx si edx vor contine adresele celor doua numere a si b
    
    mov ebx, dword [ebp + 8]
    mov eax, dword [ebx + 4]
    mov [len1], eax
    
    mov edx, dword [ebp + 12]
    mov eax, dword [edx + 4]
    mov [len2], eax
          
    ; initializam ecx cu 0, acesta fiind counter-ul cu care parcurgem numerele
    
    mov ecx, 0
    
    ; vedem ce numar este mai lung dintre cele 2
    
    mov eax, [len1]
    cmp eax, [len2]
    jl second_is_longer
    
    ; daca primul e mai lung atunci actualizam lungimea primului numar cu lungimea
    ; celui de-al doilea pentru ca ne intereseaza doar octetii comuni ai celor doua
    ; numere restul dand la operatia AND 0
    
    mov eax, [len2]
    mov [ebx + 4], eax
    
first_is_longer:
    
    ; cat timp nu am ajuns la finalul primilor len2 octeti
    
    cmp ecx, [len2]
    jge addapt_length_and

    ; luam cate un octet din fiecare numar
    
    mov al, byte [ebx + 8 + ecx]
    mov ah, byte [edx + 8 + ecx]
    
    ; aplicam operatia and
    
    AND al, ah

    ; punem in a rezultatul si incrementam counter-ul
    
    mov [ebx + 8 + ecx], al
    inc ecx
    
    ; repetam procedura
    
    jmp first_is_longer
    
second_is_longer: 
 
    ; daca al doilea e mai lung, atunci lungimea nu trebuie actualizata
    ; parcurgem primii len1 octeti din fiecare numar
    
    cmp ecx,[len1]
    jge addapt_length_and
    
    ; luam cate un octet din fiecare numar
    
    mov al, byte [ebx + 8 + ecx]
    mov ah, byte [edx + 8 + ecx]
    
    ; aplicam operatia and
    
    AND al, ah
    
    ; punem rezultatul obyinut in a si incrementam conter-ul
    
    mov [ebx + 8 + ecx] ,al
    inc ecx
    
    ; repetam procedura
    
    jmp second_is_longer
  
addapt_length_and:
    
    ; trebuie sa vedem daca nu cumva trebuie actualizata lungimea
    dec ecx
    
    ; incepand cu primul octet verificam daca nu cumva e 0
    
    mov al, byte [ebx + ecx + 8]
    
    ; daca nu e 0 atunci nu mai avem nimic de modificat
    
    cmp al, 0
    jne exit
    
    ; modificam lungimea si verificam daca nu cumva am ajuns la inceputul numarului
    
    inc ecx
    
    mov [ebx + 4], ecx
    
    dec ecx
    
    cmp ecx, 0
    jg addapt_length_and
    
exit: 
   
    ret
    

or_bits:
    
    ; salvam in cele 2 variabile len1 si len2 lungimile celor 2 numere
    ; ebx si edx vor contine adresele celor doua numere a si b
        
    mov ebx, dword [ebp + 8]
    mov eax, dword [ebx + 4]
    mov [len1], eax
    
    mov edx, dword [ebp + 12]
    mov eax, dword [edx + 4]
    mov [len2], eax
    
    ; initializam counter-ul cu care vom parcurge cele 2 numere cu 0
    
    mov ecx,0
    
    ; vedem ce numar este mai lung 
    
    mov eax, [len1]
    cmp eax, [len2]
    jl addapt_length

first_is_longer_or:

    ; daca primul numar este mai mare ne intereseaza doar primii len2 octeti
    ; restul ramanand neschimbati la operatia OR
        
    cmp ecx, [len2]
    jge out

    ; luam cate un octet din fiecare numar
    mov al, byte [ebx + 8 + ecx]
    mov ah, byte [edx + 8 + ecx]
    
    ; aplicam operatia or
    
    OR al, ah
    
    ; punem rezultatul inapoi in a
    
    mov [ebx + 8 + ecx], al
    
    ; crestem counter-ul si repetam procedura
    inc ecx
    
    jmp first_is_longer_or
    
addapt_length:
    
    ; daca al doilea numar este mai lung, atunci lungimea rezultatului va fi 
    ; lungimea celui de-al doilea numar  
    
    mov eax, [len2]
    mov [ebx+4], eax 
        
second_is_longer_or: 
    
    ; pentru primii len1 octeti din fiecare numar 
    
    cmp ecx,[len1]
    jge complete
    
    ; luam cate un octet din fiecare numar
    
    mov al, byte [ebx + 8 + ecx]
    mov ah, byte [edx + 8 + ecx]
    
    ; aplicam operatia or
    
    OR al, ah
   
    ; punem rezultatul inapoi in a
    
    mov [ebx + 8 + ecx], al
    
    ; crestem counter-ul si repetam procedura
    
    inc ecx
    jmp second_is_longer_or
    
complete:  
  
    ; de la lungimea primului numar pana la lungimea celui de-al doilea
    ; copiem octetii din b in a 
    
    cmp ecx,[len2]
    jge out
    
    ; luam octetul din b si il punem in a
    
    mov al, byte [edx + 8 + ecx]
    mov [ebx + 8 + ecx], al
    
    ; repetam procedura dupa ce am incrementat counter ul
    
    inc ecx
    
    jmp complete
    
    
out:        
    
    ret
    
lshift_bits:

    ; salvam in cele 2 variabile len1 si len2 lungimea primului numar
    ; respectiv cel de-al doilea numar, astfel ebx il va contine pe a
      
    mov ebx, dword [ebp + 8]
    mov eax, dword [ebx + 4]
    mov [len1], eax
    
    mov edx, dword [ebp + 12]
    mov eax, dword [edx + 8]
    mov [len2], eax
    
repeat:

    ; pastram numarul de shiftari in len2
     
    mov ecx, [len2]
    
    ; vedem daca mai trebuie sa shiftam
    
    cmp ecx, 0
    jle end_lshift_bits
    
    ; decrementam numarul de shiftari si il salvam in len2
    
    dec ecx
    
    mov [len2], ecx
    
    ; punem in ecx 0 pentru a parcurge octetii numarului
    
    mov ecx, 0
    xor edx, edx
    
lshift_byte:

    ; cat timp nu am terminat octetii numarului
    
    cmp ecx, [len1]
    jge here    
    
    ; luam un octet din numar 
    
    mov al, byte[ebx +8 + ecx]
    
    ; il copiem in alt registru si pe acela il shiftam la stanga cu 7 pozitii
    ; astfel, salvam carry-ul de la octetul curent
    
    mov dl, al
    shr dl, 7
    
    ; shiftam la stanga octetul curent
    
    shl al, 1
    
    ; verificam daca aveam carry de la octetul precedent
    
    cmp dh, 1
    jne no_carry    
    
    ; daca aveam, il adunam
     
    add al, 1

no_carry:

    ; actualizam octetul din a
    
    mov byte[ebx + 8 + ecx], al
    
    ; punem in dh noul carry 
    
    mov dh, dl
    
    ; incrementam counter-ul si repetam procedura 
    
    inc ecx
    
    jmp lshift_byte
    
here:
    
    ; verificam daca primul octet al numarului are si el carry
    ; daca nu are luam procedura de shiftare de la inceput
    
    cmp dh, 1
    jne repeat
    
    ; daca are carry incrementam lungimea numarului atat in memorie cat si
    ; in variabila len1
    
    mov eax, [len1]
    
    add eax, 1
    
    mov [ebx +4], eax
    
    mov [len1], eax
    
    ; si punem in octet carry-ul  
    
    mov byte [ebx + 8 + ecx], dh
    
    ; repetam procedura de shiftare
    
    jmp repeat
    
end_lshift_bits:

    ret
    
rshift_bits:

    ; salvam in cele 2 variabile len1 si len2 lungimea primului numar,
    ; respectiv cel de-al doilea numar, astfel ebx il va contine pe a
    
    mov ebx, dword [ebp + 8]
    mov eax, dword [ebx + 4]
    mov [len1], eax
    
    mov edx, dword [ebp + 12]
    mov eax, dword [edx + 8]
    mov [len2], eax

redo:
    
    mov ecx, [len2]
    
    ; verificam daca mai trebuie sa shiftam numarul
    
    cmp ecx, 0
    jle end_rshift_bits
    
    ; actualizam numarul de shiftari in len2
    
    dec ecx
    mov [len2], ecx          
    
    ; punem in ecx len1 pentru ca de aceasta data trebuie sa shiftam
    ; incepand cu primul octet 
    
    mov ecx, [len1]
    dec ecx
    
    ; facem edx-ul 0
    
    xor edx,edx
    
    ; verificam daca primul octet al numarului este egal cu 1, caz in care
    ; trebuie sa actualizam lungimea dupa shiftare 
    
    mov al, byte[ ebx + 8+ ecx]
    
    cmp al, 1
    jne rshift_byte
    
    ; actualizam lungimea atat in memorie cat si in variabila len1
    
    mov edx, [len1]
    dec edx
    
    mov [len1], edx
    mov [ebx +4], edx
    
    ; facem edx 0 din nou pentru a-i putea folosi subregistrele
    
    xor edx, edx
    
rshift_byte:
    
    ; cat timp mai avem octeti de shiftat
       
    cmp ecx,0
    jl redo  
    
    ; luam octetul curent din numar
    
    mov al, byte[ ebx +8 + ecx]
    
    ; vedem daca avem carry la octet-ul actual
    
    mov dl, 1
    and dl, al
    
    ; shiftam octetul curent
     
    shr al, 1
    
    ; daca aveam carry de la octet-ul precedent 
    
    cmp dh, 1
    jne no_rest    
    
    ; adunam carry-ul de la octet-ul precedent
    
    shl dh, 7
    add al, dh
    
no_rest:

    ; punem inapoi in a octetul actualizat 
    
    mov byte[ebx + 8 + ecx], al
    
    ; punem in dh carry-ul octetului curent
    
    mov dh,dl
    
    ; decrementam counter-ul si repetam procedura
    
    dec ecx
    jmp rshift_byte
    
end_rshift_bits:
    
    ret
    
add_bits:
    
    ; salvam in cele 2 variabile len1 si len2 lungimile celor 2 numere
    ; ebx si edx vor contine adresele celor doua numere a si b
        
    mov ebx, dword [ebp + 8]
    mov eax, dword [ebx + 4]
    mov [len1], eax
    
    mov edx, dword [ebp + 12]
    mov eax, dword [edx + 4]
    mov [len2], eax
    
    ; vedem daca cele doua numere au acelasi semn 
    
    mov eax, dword [edx]
    mov ecx, dword [ebx]
    
    cmp eax, ecx
    jne different_signs
    
    ; verificam care numar este mai lung 
    
    mov eax, [len1]
   
    cmp eax, [len2]
    jl same_sign_second_longer
    
    ; initializam counter-ul cu 0 si facem carry flag-ul 0
    
    mov ecx, 0
    clc
    
same_sign_first_longer:
    
    ; daca primul numar este mai lung luam cate un octet din fiecare numar
    
    mov al, byte [ebx + 8 + ecx]
    
    mov ah, byte [edx + 8 + ecx]
    
    ; adaugam carry-ul de la octetul precedent
    
    add al, [carryf]
    
    ; apoi facem carry-ul 0
    
    mov byte [carryf],0
    
    ; facem adunarea si vedem daca avem carry
    
    add al, ah
    jnc continue
    
    ; daca avem carry il salvam in variabila carryf
    
    mov byte [carryf], 1
    
continue:
   
    ; facem ah-ul 0
    
    sub ah, byte[edx + 8 + ecx]
    
    ; actualizam octetul in a cu rezultatul adunarii
    
    mov byte[ebx + 8 +ecx], al
    
    ; crestem counter-ul si verificam daca am ajuns la finalul
    ; celui de-al doilea numar
    
    inc ecx
    
    cmp ecx, [len2]
    jge carry
    
    ; daca nu am ajuns repetam procedura 
    
    jmp same_sign_first_longer
   
carry:

    ; daca am ajuns la final verificam daca avem carry de la 
    ; adunarea precedenta 
    
    mov ah, [carryf]
    
    ; daca nu avem carry nu mai trebuie facuta nicio schimbare
     
    cmp ah, 1
    jne end_add_bits
     
    ; daca am depasit lungimea primului numar
    
    cmp ecx,[len1]
    jl no_change
    
    ; actualizam lungimea atat in memorie cat si in variabila len1
     
    inc ecx
    
    mov [len1], ecx
    mov [ebx+4], ecx
    
    dec ecx
     
no_change:

    ; luam un octet din a 
    
    mov al, byte [ebx + 8 + ecx]
    
    ; il adunam cu carry-ul 
    
    add al, ah
     
    ; il actualizam in memorie si verificam daca mai avem carry
    
    mov byte[ebx + 8 + ecx], al
    jnc end_add_bits
    
    ; daca avem carry il punem in variabila carryf, incrementam
    ; counter-ul si si repetam procedura
    
    mov byte [carryf], 1
    
    inc ecx
    jmp carry
        
same_sign_second_longer:

    ; luam un octet din fiecare numar 
     
    mov al, byte [ebx + 8 + ecx]
    
    mov ah, byte [edx + 8 + ecx]
    
    ; adaugam carry-ul de la adunarea precedenta 
    
    add al, [carryf]
    
    ; facem carry-ul 0 pentru a nu-l folosi gresit la urmatoarea adunare
    
    mov byte [carryf], 0
    
    ; facem adunarea si verificam daca avem sau nu carry
    
    add al, ah
    jnc continue_second
    
    ; daca avem carry il punem in variabila carryf
    
    mov byte [carryf],1
    
continue_second:
    
    ; punem in a octet-ul actualizat 
    
    mov byte[ebx + 8 +ecx], al
    inc ecx
    
    ; daca am ajuns la finalul numarului mai mare mergem 
    ; mai departe daca nu repetam procedura 
    
    cmp ecx, [len2]
    jge move
    
    jmp same_sign_second_longer
    
move:

    ; punem in ah carry-ul de la ultima adunare
    
    mov ah, [carryf]
    
    ; actualizam lungimea primului numar cu cea celui de-al doilea
    
    mov [len1], ecx
    mov [ebx+4] ,ecx
    
    ; vedem daca ah e diferit de 0 
       
    cmp ah, 1
    jne end_add_bits
    
    ; actualizam iar lungimea 
    
    inc ecx
    
    mov [len1], ecx
    mov [ebx+4] ,ecx
    
    dec ecx
    
    ; punem 1 in octetul curent, acesta fiind ultimul din rezultat
    
    mov al, 0
    
    add al, ah
     
    mov byte[ebx + 8 + ecx], al
    
    ; terminam adunarea 
    
    jmp end_add_bits
    

different_signs:
    
    ; initializam counter-ul cu care vom parcurge numerele
    
    mov ecx,0
    
    ; vedem ce numar este mai lung
    
    mov eax, [len1]
    
    ; vedem ce numar este mai lung 
    
    cmp eax, [len2]
    jle different_signs_second_longer
    
    ; initializam carry-ul cu 1 pentru a construi complementul
    ; fata de 2
    
    mov byte [carryf], 1
    
different_signs_first_longer:
    
    ; vedem daca am ajuns la finalul numarului mai mic
    
    cmp ecx,[len2]
    jge addapt_nr1
    
    ; luam cate un octet din fiecare numar
    
    mov al, byte[ebx + 8 + ecx]
    
    mov ah, byte[edx + 8 + ecx]
    
    ; vedem care numar este negativ 
    
    cmp dword[ebx], 0
    jne change_first1

    ; il negam pentru a obtine numarul negativ 
    
    not ah
    jmp add_c

change_first1:

    not al
    
add_c:

    ; adunam carry-ul de la adunarea precedenta si pentru primul
    ; octet adunam 1 ca sa formam complementul fata de 2 
    
    add al, [carryf]
    
    ; facem carry-ul 0 
    
    mov byte [carryf], 0
    
    ; facem adunarea si verificam daca avem carry
    
    add al, ah
    jnc no_other_carry
    
    ; daca avem facem carryf-ul 1
    
    mov byte [carryf], 1
    
no_other_carry:

    ; verificam semnul primului numar pentru ca acest va si
    ; semnul numarului ca total 
    
    cmp dword [ebx], 0
    je positive
    
    ;in functie de acesta, transformam sau nu rezultatul
    
    not al
    
    cmp ecx,0
    jne positive
    
    ; daca e primul octet, trebuie transformat in complement fata de
    ; 2, asa ca trebuie adunat 1
    
    add al,1
    
positive:

    ; actualizam octetul, crestem counter-ul si repetam procedura
    
    mov byte [ebx + ecx + 8], al
    inc ecx
    
    jmp different_signs_first_longer
    
addapt_nr1:

    ; daca dupa terminarea celui de-al doilea numar nu avem carry
    ; nu mai avem ce modifica decat eventual lungimea
     
    cmp byte[carryf], 1
    jne addapt_length1
   
    ; daca avem carry punem in al octetul 
    
    mov al, byte[ebx + ecx + 8]
    
    ; in functie de semn punem in ah 00 sau ff si negam sau nu al-ul
    
    mov ah, 0x00
    cmp dword [ebx], 0
    jne neg
   
    mov ah, 0xff
    jmp add_carry
   
neg:

    not al

add_carry:  

    ; adunam carry-ul, ah-ul
    add al, [carryf]
    mov byte [carryf], 0
   
    add al,ah
    jnc no_more_carry_first
    
    ; actualizam numarul 
    
    mov byte [ebx + 8 + ecx], al
    
    ;actualizam carry-ul
    
    mov byte [carryf], 1
    
    ; incrementam ecx-ul si repetam procedura 
    
    inc ecx
    jmp addapt_nr1
    
no_more_carry_first:

    ; daca nu mai avem carry actualizam octetul si verificam daca
    ; trebuie sa adaptam lungimea
    
    mov byte [ebx + 8 + ecx], al 

addapt_length1:

    ; verificam daca primul octet din rezultat este cumva 0
    
    mov ecx, [len1]
    
    dec ecx
    
    mov al, byte [ebx + ecx + 8]
    
    ; daca nu este 0, nu trebuie sa adaptam lungimea
    
    cmp al, 0
    jne end_add_bits
    
    ; daca este 0 actualizam lungimea atat in memorie cat si in variabila len1
    
    mov [ebx + 4], ecx
    mov [len1], ecx

    ; repetam procedura
        
    jmp addapt_length1

 
different_signs_second_longer:

    ; daca al doilea numar este mai mare sau egal
    ; initializam carry-ul si counter-ul
    
    mov ecx, 0
    mov byte [carryf], 1
    
different_signs_sec:
    
    ; verificam daca am ajuns la finalul numarului mai mic
    
    cmp ecx, [len1]
    jge complete_first
    
    ; facem semnul 0 , pentru a vedea la lungimi egale ce semn are 
    ; rezultatul 
    
    mov byte [sign_of_number], 0
    
    ; luam un octet din fiecare numar
    
    mov al, byte [ebx + ecx + 8]
    
    mov ah, byte [edx + ecx + 8] 

    ; verificam pentru semn care octet este mai mare
    
    cmp al, ah
    jnb lower
    
    mov byte [sign_of_number],1
    
lower:

    ; in functie de semn negam unul din octeti
    
    cmp dword [ebx], 0
    jne change_first
    
    ; daca al doilea e negtiv atunci il negam pe al doilea
    
    not ah
    add ah, [carryf]
    jmp sum1
        
change_first:

    ; daca primul e negativ il negam pe el
    
    not al
    add al, [carryf]
sum1:
    
    ; punem in carryf 0
    
    mov byte [carryf], 0
    
    ; facem adunarea si verificam daca avem carry sau nu
    
    add al, ah
    jnc no_set_carry
    
    ; daca avem carryf punem in variabila valoarea 1
    
    mov byte [carryf], 1
    
no_set_carry:

    ; in functie de semnul celui de-al doilea numar il schimbam sau nu
    ; pentru a acoperi cazul in care al doilea e strict mai mare 
    
    cmp byte [ebx], 0
    jne change_byte
    
    ; daca primul numar e pozitiv, al doilea e negativ deci trebuie
    ; sa schimbam numarul
    
    not al
    
    ; daca suntem la primul octet trebuie sa schimbam in complement fata
    ; de 2, deci, sa adunam 1
    
    cmp ecx, 0
    jne change_byte
    
    add al,1
    
change_byte:

    ; actualizam octetul in memorie 
    
    mov byte[ebx + ecx + 8], al
    
    ; crestem counter-ul si apoi repetam procedura
    
    inc ecx
    jmp different_signs_sec
    
complete_first:

    ; completam primul numar 

    ; verificam daca am ajuns la finalul celui de-al doilea numar 
    cmp ecx, [len2]
    jge adjust_all
    
    ; luam un octet din al doilea numar
    
    mov al, byte [ edx + ecx + 8]
    
    ; luam ah de semn opus pentru a face adunarea bine 
    
    mov ah, 0x00
    
    cmp dword [edx], 0
    jne sign_chosen
   
    mov ah, 0xff
    
sign_chosen:

    ; adunam carry-ul precedent
    
    add al, byte[carryf]
    
    ; il facem 0
    mov byte [carryf], 0
    
    ; verificam daca mai avem carry 
    
    add al,ah
    jnc continue_copy

    ; daca avem facem variabila carryf 1
    
    mov byte [carryf], 1

continue_copy:

    ; copiem octetul in primul numar 
    
    mov byte [ebx + ecx + 8], al
    
    ; incrementam counter-ul si repetam procedura
    
    inc ecx
    
    jmp complete_first
      
adjust_all:

    ; lungimea rezultatului va fi cel mult lungimea celui de-al
    ; doilea numar
    
    mov eax, [len2]
    mov [ebx+4],eax

    ; daca al doilea numar este pozitiv 

    cmp dword [edx],0
    je check
    
    ; semnul este negativ la sfarsitul primului numar
    
    cmp byte [sign_of_number],0
    jne change_sign
    
    ; si au lungimi egale 
    
    cmp eax, [len1]
    jg end_add_bits
    
    ; trebuie sa negam tot numarul pentru ca noi l-am format dupa
    ; semnul celui de-al doilea numar
    
    dec ecx
    
change_number:

    ; dupa ce am schimbat fiecare octet trebuie sa vedem daca nu
    ; cumva trebuie sa actualizam lungimea
    
    cmp ecx, 0
    jl length_set
    
    ; luam octet cu octet il negam si tinem cont ca la ultimul octet
    ; trebuie sa adunam 1 pentru a transforma corect in complement
    ; fata de 2
    
    mov al, byte[ebx + ecx + 8]
    not al
    cmp ecx, 0
    jne update
    
    add al, 1
update:

    ; actualizam octetul in memorie si decrementam counterul
    
    mov byte[ebx + ecx + 8], al
    dec ecx
    
    ; repetam procedura 
    jmp change_number
change_sign:

    ; schimbam semnul daca este nevoie si apoi verificam daca
    ; trebuie sa actualizam lungimea
    
    mov dword [ebx], 0xffffffff
    jmp length_set

check:

    ; daca numarul al doilea e pozitiv si are lungimea mai mare
    ; schimbam doar semnul
    
    cmp eax, [len1]
    jg strictly_greater
    
    ; daca sunt egale ca lungime si semnul rezultatului e negativ 
    ; trebuie sa modificam numarul pentru ca noi l-am construit in functie
    ; de semnul numarului al doilea
    
    cmp byte [sign_of_number], 0
    jne change_number
    
strictly_greater:

    ; schimbam semnul daca e cazul
    
    mov dword [ebx], 0x00000000
    
length_set:

    ; verificam daca nu cumva lungimea e mai mica decat len2
    
    mov ecx, [len2]
    
length_update:

    ; cat timp nu am terminat numarul
    
    dec ecx
    cmp ecx,0
    je end_add_bits

    ; luam octetul curent si verificam daca e 0, caz in care 
    ; scadem lungimea 
    
    mov al, [ebx + ecx + 8]

    cmp al, 0 
    jne end_add_bits
    
    ; actualizam lungimea si repetam procedura 
     
    mov [ebx + 4], ecx
    jmp length_update
    
end_add_bits:

    ret

multiply_bits:
    
    ; salvam in cele 2 variabile len1 si len2 lungimile celor 2 numere
    ; ebx si edx vor contine adresele celor doua numere a si b

    mov ebx, dword [ebp + 8]
    mov eax, dword [ebx + 4]
    mov [len1], eax
    
    mov edx, dword [ebp + 12]
    mov eax, dword [edx + 4]
    mov [len2], eax
    
    ; alocam spatiu suficient cat sa putem pune rezultatul inmultirii
    
    mov eax, [len1]
    add eax, [len2]
    add eax,1
    
    push eax
    call _malloc
    add esp,4    
    
    ; salvam in edi adresa acestei zone de memorie
    
    mov edi, eax
    
    ; repunem in ebx si edx cele doua numere
    
    mov edx, dword [ebp + 12]
    mov ebx, dword [ebp + 8]
    
    ; intializam counter-ul pentru primul numar cu 0
   
    mov dword[counter], 0

    ; initializam zona de memorie cu 0
    
    mov ecx,[len1]
    add ecx,[len2]
    add ecx,1
    
initializare:

    cmp ecx, -1
    je first
    
    mov byte [edi + ecx], 0
    
    dec ecx
    jmp initializare
    
first:

    ; vom parcurge primul numar cu ajutorul variabile counter
    
    mov ecx, [counter]
    
    cmp ecx, [len1]
    je copy
    
    ; luam un octet din primul numar
     
    mov al, byte [ebx + ecx + 8]
    
    ; crestem counter-ul
    
    inc ecx
    
    mov [counter], ecx
    
    ; initializam ecx-ul pe care il vom folosi drept counter pentru
    ; al doilea numar
    
    mov ecx, 0
    
second:

    ; cat timp nu am parcurs toti octetii din al doilea numar
    
    cmp ecx, [len2]
    je first
    
    ; luam unul
    
    mov ah, byte [edx + ecx + 8]

    ; facem inmultirea
    
    mul ah

    ; rezultatul inmultirii a 2 octeti trebuie pus in rezultatul mare
    ; la index-ul egal cu counter + ecx 
    
    add ecx, [counter]
    
    dec ecx

    ; retinem intr-o variabila valoarea counter-ului pentru al doilea
    ; numar
    
    mov dword [remember], ecx
    
    ; adunam la rezultat octet-ul inferior al inmultirii si verificam
    ; daca avem sau nu carry
    
    add byte [edi +ecx], al
    jnc no_c
    
    
propaga:

    ; daca avem carry il adunam si repetam acest procedeu de adunare a 
    ; carry-ului pana nu o sa mai fie carry
    
    add byte [edi + ecx + 1], 1
    jnc no_c
    
    inc ecx 
    jmp propaga  
      
no_c:

    ; daca avem sau nu carry, recuperam valoarea counter-ului
    
    mov ecx,[remember]
    
    ; adaugam octet-ul superior la urmatorul octet din rezultat
    ; si verificam din nou daca avem sau nu carry
    
    add byte [edi + ecx + 1], ah
    jnc no_c2
    
    
propaga2:

    ; daca avem carry il adunam si repetam procedura pana 
    ; ramanem fara carry
    
    add byte [edi + ecx + 2], 1
    jnc no_c2
    
    inc ecx
    jmp propaga2
        
no_c2:

    ; trebuie sa recuperam in al octetul din primul numar
    ; punem in ecx counter-ul din primul numar si scadem 1 pentru ca
    ; il incrementasem
    
    mov ecx, [counter]
    dec ecx
    
    ; punem in al octetul din primul numar
    
    mov al, byte [ebx + ecx + 8]
    
    ; facem ah 0 ca sa nu folosim ceva gresit ulterior
    xor ah, ah
    
    ; recuperam counter-ul si apoi scadem din el valoarea primului
    ; counter pentru a reveni unde trebuie in al doilea numar
    
    mov ecx, [remember]
    
    sub ecx, [counter]
    add ecx, 1
    
    ; incrementam counter-ul si dupa repetam procedura
    
    inc ecx
    
    jmp second
    
copy:

    ; dupa ce am terminat inmultirea trebuie sa mutam rezultatul in a
    
    ; lungimea poate fi maxim len1+len2+1
    
    mov ecx, [len1]
    add ecx, [len2]
    add ecx, 1
    
    ; actualizam lungimea primului numar
    
    mov dword[ebx + 4], ecx
    
repeat_copy:
    
    ; luam un octet din rezultat si il punem in a
    
    mov al, byte [edi +ecx]
    mov byte [ebx + ecx + 8], al
    
    ; decrementam counter-ul si repetam procedura
    
    dec ecx
    
    cmp ecx,-1
    je addapt_length_mul
    
    jmp repeat_copy
    
addapt_length_mul:

    ; la final trebuie sa vedem daca nu cumva inmultirea a generat un
    ; rezultat cu o lungime mai mica 
    
    mov ecx, [len1]
    add ecx, [len2]
    add ecx, 1
    
real_addapt:

    ; incepand cu primul octet verificam daca acesta este 0 
    
    mov al, byte [ebx + ecx + 8]

    cmp al,0
    jne addapt_sign
    
    ; daca acesta este 0 decrementam lungimea numarului in memorie
    
    mov dword [ebx + 4], ecx
    dec ecx
    
    ; repetam procedura pana gasim un octet diferit de 0
    
    jmp real_addapt
    
addapt_sign: 

    ; trebuie sa adaptam semnul
    
    ; daca numerele au acelasi semn facem semnul pozitiv
    
    mov eax, [ebx]
    
    cmp eax, [edx]
    je change_positive
    
    ; altfel, facem semnul negativ 
    mov dword [ebx], 0xffffffff
    
    jmp end_multiply_bits
    
change_positive:

    mov dword [ebx], 0x00000000 
    
end_multiply_bits:

    ret
      
do_operation:

    push ebp
    mov ebp,esp
          
    ; luam de pe stiva operatia
    
    mov ebx, dword [ebp+ 16] 
    
    ; ne intereseaza primul octet al acesteia
     
    mov al, byte [ebx]    
    
    ; in functie de operatie 
    
    cmp al, '&'
    je and
    
    cmp al, '|'
    je or
    
    cmp al, '<'
    je lshift
    
    cmp al, '>'
    je rshift
    
    cmp al, '+'
    je add
    
    cmp al, '*'
    je multiply
    
    ; apelam functia corespunzatoare 
    ; si apoi sarim la final
           
and:
    
    call and_bits
    jmp finish
     
or:

    call or_bits
    jmp finish
    
lshift:

    call lshift_bits
    jmp finish
    
rshift:
    
    call rshift_bits
    jmp finish
   
add:

   call add_bits
   jmp finish

multiply:
   
   call multiply_bits
  
finish:
    leave
    ret
