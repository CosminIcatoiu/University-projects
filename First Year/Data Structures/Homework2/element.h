#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef Elem
#define Elem

typedef struct celula{
	void * info;
	struct celula * urm;
}TCelula, * TLG;

typedef struct{
	int id;
	char * denumire;
	char *ipv4;
	char *func;
}TSwitch;

//functie care compara doua switch-uri dupa id

int cmpid( void *a, void *b)
{
	return ((TSwitch*)a)->id-((TSwitch*)b)->id;
}

//functie care primeste 2 numere x si y ca parametru si intoarce x la puterea y

int putere( int x, int y)
{	
	if(y==0)
		return 1;
	return x*putere(x,y-1);
}

//functie care elibereaza un switch

void elibel( void * ae)
{
	free( ((TSwitch *)ae)->denumire);
	free( ((TSwitch *)ae)->func);
	free( ((TSwitch *)ae)->ipv4);
}

//functie care scrie intr-un fisier informatia dintr-un switch

void Afiel( void * ae,FILE *dfp)
{
	TSwitch * x= (TSwitch *)ae;

	//se scriu id-ul,ip-ul si denumirea

	fprintf(dfp,"%d %s %s\n",x->id,x->ipv4,x->denumire);
}

//functie care aloca memorie pentru un switch

TLG AlocCel( void * ae)
{
	TLG aux;

	aux=malloc(sizeof(TCelula));

	// daca nu s-a reusit alocarea celulei tratam eroarea

	if(!aux)
	{
		printf("Nu s-a reusit alocarea unei celule");
		return NULL;
	}
	
	//alocam informatia din switch si daca nu s-a reusit eliberam memoria alocata
	aux->info=malloc(sizeof(TSwitch));
	if(!aux->info)
	{
		free(aux);
		return NULL;
	}
	
	//copiem in noua celula informatia din switch-ul transmis ca parametru
	
	((TSwitch *)(aux->info))->denumire=strdup( ((TSwitch *)ae)->denumire);
	((TSwitch *)(aux->info))->ipv4=strdup( ((TSwitch *)ae)->ipv4);
	((TSwitch *)(aux->info))->func=strdup( ((TSwitch *)ae)->func);
	((TSwitch *)(aux->info))->id= ((TSwitch *)ae)->id;

	//initializam urmatorul cu NULL

	aux->urm=NULL;
	return aux;
}

//functie care converteste un ip din char in intreg

long int conversie( char * s)
{
	char *p;
	char * q;
	long int z=0,x=0,t=24,i;

	// copiem ip-ul intr-un auxiliar pentru a nu il distruge cand apelam strtok

	q=strdup(s);
	
	//cautam punctul care delimiteaza grupele de numere

	p=strtok(q,".");

	while(p!=NULL)
	{
		//transformam sirul de caractere in numarul respectiv

		for(i=0;i<strlen(p);i++)
		{
			z=z+(p[i]-'0')*putere(10,strlen(p)-i-1);
		}

		//il adaugam la numarul total, inmultit fiind cu 2 la puterea corespunzatoare

		x=x+z*putere(2,t);
		t=t-8;
		
		//reapelam pentru urmatorul grup de cifre pana cand nu mai exista

		p=strtok(NULL,".");
		
		z=0;
	}

	// eliberam memoria alocata si returnam numarul

	free(q);

	return x;
}
#endif
