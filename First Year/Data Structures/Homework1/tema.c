//Icatoiu Vlad Cosmin 314CB

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Structura ce defineste o celula din lista

typedef struct celulag
{ 
	void* info;           
	struct celulag *urm,*prev;   
} TCelulaG, *TLG, **ALG; 

// Structura pentru functia hash

typedef int (*TFHash)(void*,int);

// Structura ce defineste tabela hash

typedef struct
{
	int M;
	TFHash fh;
	TLG *v;
} TH;

// Structura ce definieste informatia dintr-o  celula

typedef struct 
{
	char *key, *value;
	int freq;
}LRU;

//Functia hash dupa care se sorteaza elementele in tabela

int keyhash( void * a, int M)
{
	char * x =((LRU *)a)->key;
	int i,s=0;
	
	for( i=0; i<strlen(x); i++)
	{
		s=s+(int)x[i];
	}
	return s%M;
}

//Functie ce compara partea key din informatia unei celule

int cmp(void *p1,void*p2)
{
	return strcmp( ((LRU*)p1)->key,((LRU*)p2)->key );
}

//Functie care calculeaza lungimea unei liste

int lungl( TLG l )
{
	int nr=0;

	//Salvam in p primul element al listei

	TLG p=l;

	//Daca lista e vida atunci lungimea e 0;
	if( l == NULL )
		return 0;

	l=l->urm;
	
	//Daca "al doilea" element e chiar primul atunci lista are un singur element
	if( l == p)
		return 1;
	nr=1;

	//Cat timp nu am ajuns la inceputul listei crestem contorul 
	while( l!=p)
	{
		l=l->urm;
		nr++;
	}

	return nr;
}

	//Functie ce elibereaza campurile din informatie

void elibel(void * p)
{
	free( ((LRU*)p)->key);
	free( ((LRU*)p)->value);
}

	//Functie ce elibereaza o lista

void eliblista( ALG al)
{
	TLG p=*al,aux;
	
	//Salvam lungimea intr-o variabila pentru a parcurge toata lista

	int i,l=lungl(*al);

	//Pentru fiecare celula din lista

	for(i=0;i<l;i++)
	{
		//Salvam celula curenta in auxiliar si apoi incrementam p-ul

		aux=p;
		p=p->urm;

		//Eliberam campurile din informatie, informatia propriu-zisa si apoi celula

		elibel(aux->info);
		free(aux->info);
		free(aux);
		
	}

	//Facem lista sa puncteze catre null

	(*al)=NULL;
}

	//Functie ce distruge o tabela hash

void DistrTH(TH ** a)
{
	int i;

	// Pentru fiecare lista din tabela

	for(i=0;i<(*a)->M;i++)
	{
		//eliberam memoria alocata listei

		eliblista(&(*a)->v[i]);
	}

	//eliberam vectorul de liste

	free((*a)->v);
}

	//Functie ce insereaza un element ae dupa un element ref dat ca parametru

int insdupa(ALG al, void* ae, void* ref, size_t d)
{

	TLG aux = malloc(sizeof(TCelulaG));

	if(!aux)
		return 0;

	TLG p= *al;
	
	//Cautam elementul ref in lista 

	while( cmp(ref,p->info)!=0)
		p=p->urm;
	
	aux->info=malloc(d);

	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	
	//Copiem in campul aux->info informatiile din elementul ae

	((LRU *)(aux->info))->key=strdup(((LRU *)ae)->key);
	((LRU *)(aux->info))->value=strdup(((LRU *)ae)->value);
	((LRU *)(aux->info))->freq=((LRU *)ae)->freq;

	//Legam noul element la lista 

	aux->urm=p->urm;
	aux->prev=p;
	p->urm=aux;
	aux->urm->prev=aux;

	return 1;
}

	//Functie ce insereaza la inceputul listei elementul ae

int insinc(ALG al , void * ae, size_t d)
{
	TLG aux= malloc(sizeof(TCelulaG));
	
	//Daca lista e nula 

	if(*al == NULL)
	{

		aux->info=malloc(d);
		if(!aux->info)
		{
			free(aux);
			return 0;
		}
		
		//Copiem in auxiliar informatiile din elementul ae
		((LRU *)(aux->info))->freq=((LRU *)ae)->freq;
		((LRU *)(aux->info))->key=strdup(((LRU *)ae)->key);
		((LRU *)(aux->info))->value=strdup(((LRU *)ae)->value);

		//Facem legaturile corespunzatoare

		*al=aux;
		aux->urm=aux;
		aux->prev=aux;
	}
	else
	{
		//Daca lista nu e nula

		aux->info=malloc(d);
		if(!aux->info)
		{
			free(aux);
			return 0;
		}

		((LRU *)(aux->info))->key=strdup(((LRU *)ae)->key);
		((LRU *)(aux->info))->value=strdup(((LRU *)ae)->value);
		((LRU *)(aux->info))->freq=((LRU *)ae)->freq;

		//Singura diferenta e la legaturi

		aux->urm=*al;
		aux->prev=(*al)->prev;
		(*al)->prev->urm=aux;
		(*al)->prev=aux;
		*al=aux;
	}
	
	return 1;
}

	//Functie care scrie campul Value intr-un fisier deschis dat ca parametru

void afiel(void * ae,FILE * dfp)
{
	LRU *p = (LRU*)ae;	
	fprintf(dfp,"(%s)", p->value);
}

	//Functie care scrie elementele unei liste intr-un fisier dat ca parametru

void afisare(TLG l, FILE * dfp)
{ 
	int i;
	
	for(i=1; i<=lungl(l); i++)
	{
		//Parcurgem lista si afisam fiecare element

		fprintf(dfp," ");		
		afiel(l->info,dfp);
		l=l->urm;
	}
	
	fprintf(dfp,"\n");
}
		
	//Functie care sterge un element din lista

void stergere( ALG al, char * s)
{
	int i;
	TLG q=*al,aux;

	//Daca lista are un element si acesta e chiar cel ce trebuie sters

	if(lungl(*al)==1 &&  strcmp( ((LRU *)(q->info))->key, s) == 0)
	{
		//Eliberam celula si facem lista sa puncteze catre NULL

		elibel((*al)->info);
		free((*al)->info);
		free(*al);
		*al=NULL;

		return ;
	}
	
	//Daca lista e nula nu avem ce sterge

	if( *al == NULL)
		return ;

	for(i=1;i<=lungl(*al);i++)
	{
		
		//Daca gasim elementul ce trebuie sters din lista

		if( strcmp( ((LRU *)(q->info))->key, s) == 0)
		{

			// si acesta e primul

			if(i==1)
			{
				// pastram elementul in auxiliar

				aux=*al;
				
				// refacem legaturile si actualizam inceputul de lista
				*al=aux->urm;
				(*al)->prev=aux->prev;
				aux->prev->urm=*al;

				//eliberam memoria
	
				elibel(aux->info);
				free(aux->info);
				free(aux);
			}
			else
			{
				// procedam asemanator doar ca nu actualizam inceputul de lista

				aux=q;

				q->prev->urm=q->urm;
				q->urm->prev=q->prev;

				elibel(aux->info);
				free(aux->info);
				free(aux);

			}

			//daca am gasit elementul nu mai are rost sa cautam in continuare
			break;
		}

		//daca nu l-am gasit avansam in lista

		q=q->urm;
	}
}

	//Functie ce insereaza ordonat un element in lista 

TLG ins(ALG al,void *p)
{
	int succes,j;

	TLG ant, q;
	q=*al;
	ant=NULL;
	
	//Daca lista e nula atunci inseram la inceput

	if( q == NULL )
	{
		succes=insinc(al,p,sizeof(LRU));
		if(!succes)
			return (*al);
	}
	else
	{
		// altfel parcurgem lista 

		for(j=1;j<=lungl(*al);j++)
		{
			//daca gasim un element cu frecventa mai mica decat elementul
			// pe care trebuie sa il inseram dam break pentru a retine acel element

			if( ((LRU *)(q->info))->freq < ((LRU *)p)->freq)
				break;

			//procedam asemanator daca gasim un element cu aceeasi frecventa
			//dar mai mare alfabetic 

			if( cmp(q->info,p) >= 0 && ((LRU *)(q->info))->freq == ((LRU *)p)->freq)
				break;

			// salvam elementul anterior dupa care vom face inserarea

			ant=q;
			q=q->urm;
		}

		//inseram elementul doar daca nu are acelasi key

		if(cmp(q->info,p) !=0)
		{
			//daca anteriorul e null atunci trebuie sa inseram la inceput
	
			if(ant == NULL )
			{
				succes=insinc(al,p,sizeof(LRU));
				if(!succes)
					return (*al);
			}
			else
			{
				//altfel trebuie sa inseram dupa elementul salvat in anterior
	
				succes=insdupa(al,p,ant->info,sizeof(LRU));
				if(!succes)
					return (*al);
			}
		}
	}
	return (*al);
}

	//functie ce intoarce prin referentiere prin referentiere valoarea value
	//a unui element cu cheia s si apoi o reintroduce in lista cu frecventa
	// crescuta cu unu

void mutare( ALG al, char *s, char **d)
{
	int i;
	TLG q=*al;
	LRU aux;

	//cautam elementul in lista
	
	for(i=1;i<=lungl(*al);i++)
	{
		//daca il gasim

		if( strcmp( ((LRU *)(q->info))->key, s) == 0)
		{
			//salvam intr-un auxiliar informatia din acea celula
			
			aux.key=strdup(((LRU *)(q->info))->key);
			aux.value=strdup(((LRU *)(q->info))->value);
			aux.freq=((LRU *)(q->info))->freq+1;
			
			//o stergem din lista
			stergere(al,((LRU *)(q->info))->key);
			
			// o inseram cu noua frecventa

			ins(al,&aux);
			
			//eliberam memoria alocata si salvam in d valoare value

			free(aux.key);
			strcpy((*d),aux.value);
			free(aux.value);

			return;
		}
		q=q->urm;
	}

	//daca nu il gasim eliberam memoria alocata pentru d
	// si intoarcem null

	free((*d));
	(*d)=NULL;
}				

	//functie ce initializeaza o tabela hash 

TH* IniTH(int M, TFHash fh)
{
	//Se aloca memorie pentru tabela

	TH*h=(TH*)calloc(sizeof(TH),1);
	if (!h) 
	{	
		printf("eroare alocare hash\n");
		return NULL;
	}

	//Se aloca memorie pentru vectorul de liste

	h->v=(TLG*)calloc(M, sizeof(TLG));
	if(!h->v)
	{
		printf("eroare alocare vector de pointeri TLG in hash\n");
		free(h);
		return NULL;
	}

	//Se salveaza functia hash pentru tabela si marimea M

	h->M=M;
	h->fh=fh;

	return h;
}

	//Functia ce insereaza in tabela hash un element

void set( TH * a, char *key, char * value)
{
	int i,s=0,j,cod;
	TLG *x;

	//Se calculeaza numarul de elemente din tabela hash
	
	for(i=0;i<a->M;i++)
	{
		s=s+lungl(a->v[i]);
	}

	//Daca acesta este mai mare decat 2*M

	if(s>2*a->M)
	{
		//Se aloca memorie pentru un vector de liste mai mare

		x=calloc(2*a->M,sizeof(TLG));
		
		//Se copiaza in noul vector elementele din vechiul vector apelandu-se
		// functia hash pentru noua dimensiune

		for(i=0;i<a->M;i++)
		{
			for(j=1;j<=lungl(a->v[i]);j++)
			{
				cod=a->fh(a->v[i]->info,2*a->M);
				ins(&x[cod],a->v[i]->info);
				a->v[i]=a->v[i]->urm;
			}
			
			//se elibereaza fiecare lista din tabela hash

			eliblista(&a->v[i]);
		}
		
		// se elibereaza vectorul de liste 

		free(a->v);

		// se actualizeaza datele din tabela hash

		a->M=2*a->M;
		a->v=x;
	}
		
	//salvam in auxiliar informatiile ce trebuie introduse in tabela

	LRU aux;
	aux.key=strdup(key);
	aux.value=strdup(value);
	aux.freq=0;

	//Se determina lista in care trebuie introdus elementul

	cod=a->fh(&aux,a->M);

	//Daca lista are mai mult de M elemente se sterge ultimul element

	if(lungl(a->v[cod])==a->M)
	{
		stergere(&a->v[cod],((LRU *)(a->v[cod]->prev->info))->key);
	}

	// Se insereaza elementul in lista si se elibereaza memoria din aux
	ins(&a->v[cod],&aux);

	free(aux.key);
	free(aux.value);
}

	//Functia ce scrie in fisier valoarea value a unui element cu cheia key si
	// incrementeaza frecventa 

void get( TH *a, char * key,FILE * dfp)
{

	LRU aux;
	aux.key=strdup(key);
	aux.value=malloc(1000);
	aux.freq=0;

	//Cautam lista in care trebuie sa cautam elementul

	int cod=a->fh(&aux,a->M);

	//Apelam functia ce returneaza referential valoarea value

	mutare(&a->v[cod],aux.key,&aux.value);

	//Scriem informatia din aux.value in fisier
	if(!aux.value)
		fprintf(dfp,"NULL\n");
	else
		fprintf(dfp,"%s\n",aux.value);

	//elibiram memoria 

	free(aux.key);
	free(aux.value);


}

	//Functie ce sterge din tabela hash un element

void stergereTH( TH *a , char *key)
{
	LRU aux;
	
	//Salvam intr-un auxiliar cheia pentru a o daca parametru functiei hash

	aux.key=strdup(key);
	aux.value=NULL;
	aux.freq=0;

	//Se determina lista din care trebuie sters elementul	

	int cod=a->fh(&aux,a->M);

	free(aux.key);

	//Apelam functia de stergere a unui element dintr-o lista

	stergere(&a->v[cod],key);
}

	//Functie ce scrie informatiile dintr-o lista intr-un fisier
	
void print_list( TH *a, int i, FILE * dfp)
{

	if(i>=0 && i<a->M && a->v[i]==NULL)
	{	
		fprintf(dfp,"%d: VIDA\n",i);
	}
	if(i>=0 && i<a->M && a->v[i]!=NULL)
	{
		fprintf(dfp,"%d:",i);
		afisare(a->v[i],dfp);
	}

}

	//Functie ce scrie informatiile dintr-o tabela hash intr-un fisier

void print( TH *a, FILE * dfp)
{
	int i;

	//Parcurgem lista si apelam funcita de afisare a unei liste numai in cazul
	//in care lista nu este vida

	for(i=0;i<a->M;i++)
	{
		if(a->v[i]!=NULL)
		{
			fprintf(dfp,"%d:",i);
			afisare(a->v[i],dfp);
		}
	}
}


int main(int argc, char * argv[])
{ 
	TH *a=NULL;
	int index;
	FILE *fp,*dfp;

	//Variabile in care sa citim informatiile din fisier

	char *key,*value,*operatie;

	key=malloc(1000);
	value=malloc(1000);
	operatie=malloc(1000);


	//Initializam tabela hash si deschidem cele 2 fisiere
	
	a=IniTH(atoi(argv[1]),keyhash);
	
	fp=fopen(argv[2],"r");
	dfp=fopen(argv[3],"w");

	//Cat timp avem ce citi din fisier apelam functia corespunzatoare
	
	while(fscanf(fp,"%s",operatie) == 1)
	{
		if(strcmp(operatie,"set")==0)
		{
			fscanf(fp,"%s%s",key,value);
			set(a,key,value);
		}

		if(strcmp(operatie,"get")==0)
		{
			fscanf(fp,"%s",key);
			get(a,key,dfp);
		}

		if(strcmp(operatie,"remove")==0)
		{
			fscanf(fp,"%s",key);
			stergereTH(a,key);
		}

		if(strcmp(operatie,"print")==0)
			print(a,dfp);
		
		if(strcmp(operatie,"print_list")==0)
		{
			fscanf(fp,"%d",&index);
			print_list(a,index,dfp);
		}
	}
	
	//Inchidem fisierele

	fclose(dfp);
	fclose(fp);

	//Eliberam memoria alocata tabelei hash	

	DistrTH(&a);
	free(a);
	free(key);
	free(operatie);
	free(value);	
	return 0;
}


