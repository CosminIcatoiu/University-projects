%include "io.inc"

section .data
    %include "input.inc"
    
    ; Salvam in figures un sir cu toate "cifrele" posibile
    ; in toate bazele si in err mesajul de eroare
    
    figures dd "0123456789abcdef", 0
    
    err dd "Baza incorecta", 0

section .text
global CMAIN
CMAIN:

    mov ebp, esp
    
    ; Numarul este dd deci el incape in eax, deci, punem in edx 0
    
    mov eax, [numar]
    mov edx, 0
    mov ebx, [baza]
    
    ;Verificam daca avem una din bazele specificate in enunt
    
    cmp ebx, 1
    jle error
    
    cmp ebx, 16
    jg error
    
    ;Vom retine in ecx numarul de resturi obtinute
    
    mov ecx, 0
    
remainders:
    
    ;Facem impartirea
    
    div ebx
    
    ;Punem pe stiva resturile pentru a le putea lua ulterior
    ;in ordinea corecta
    
    push edx
    
    ;Punem 0 in edx pentru ca din nou numarul ce trebuie impartit
    ;incape in eax si este chiar catul obtinut anterior
    
    mov edx, 0
    
    ;Crestem numarul de resturi
     
    inc ecx
    
    ;Daca am obtinut catul 0 inseamna ca am terminat de impartit
    ;si mergem la afisare, altfel, repetam procedura
    
    cmp eax, 0
    je print
    
    jmp remainders
    
print:

    ;Extragem in edx resturile in ordinea corecta si cu ajutorul
    ;sirului figures afisam simbolul corespunzator restului
    
    xor edx,edx
    
    pop edx
    
    PRINT_CHAR [figures+ edx]
    
    ;Scadem ecx, iar in cazul in care am extras toate resurile 
    ; mergem la finalul programului, altfel, repetam procedura
    
    dec ecx
    
    cmp ecx, 0
    je final
    
    jmp print
    
error:

    ;Afisam mesajul de eroare
    
    PRINT_STRING err
    
final:

    ret