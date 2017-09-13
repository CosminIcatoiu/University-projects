#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "element.h"

#ifndef Coada
#define Coada

typedef struct{
	TLG vf,bs;
}TCoada;


//functie ce initializeaza o coada

TCoada* InitC()
{
	TCoada *c;

	// se aloca o coada noua

	c=malloc(sizeof(TCoada));

	// daca nu s-a reusit se prelucreaza eroarea
	
	if(!c)
	{
		printf("Nu s-a reusit alocarea cozii");
		return NULL;
	}

	// se initializeaza varful si baza cozii cu NULL si se returneaza coada
	
	c->vf=NULL;
	c->bs=NULL;

	return c;
}

// functie ce insereaza intr-o coada un nou element

void InsC(TCoada *c, void *x)
{
	TLG aux;
	
	//se aloca o noua celula ce va contine informatia data ca parametru

	aux=AlocCel(x);
	if(!aux)
		return;

	//daca nu avem nimic in coada actualizam varful si baza cu noua celula

	if(c->vf==NULL)
	{
		c->vf=aux;
		c->bs=aux;
	}
	else
	{
		//altfel actualizam baza si legam fosta baza de cea noua

		c->bs->urm=aux;
		c->bs=aux;
	}
}

//functie ce extrage un element dintr-o coada

void ExtrC(TCoada *c, void * ae)
{
	TLG aux;
	aux=c->vf;

	//daca nu e nimic in coada nu avem ce extrage

	if( c->vf==NULL)
		return;


	//se copiaza informatia din varf in ae

	strcpy(((TSwitch *)ae)->denumire, ((TSwitch *)(aux->info))->denumire);
	strcpy(((TSwitch *)ae)->ipv4, ((TSwitch *)(aux->info))->ipv4);
	strcpy(((TSwitch *)ae)->func, ((TSwitch *)(aux->info))->func);
	((TSwitch *)ae)->id= ((TSwitch *)(aux->info))->id;

	//actualizam noul varf si il eliberam pe precedentul

	c->vf=c->vf->urm;

	elibel(aux->info);
	free(aux->info);
	free(aux);
}

//functie ce distruge o coada

void DistrugereC(TCoada *c)
{
	TLG aux;

	//daca nu avem nimic in coada eliberam memoria pentru aceasta

	if(c->vf==NULL)
	{
		free(c);
		return ;
	}

	
	while(c->vf!=NULL)
	{
		// procedam la fel ca la ExtrC retinem vechiul varf si il actualizam

		aux=c->vf;
		c->vf=c->vf->urm;

		//eliberam memoria din vechiul varf

		elibel(aux->info);
		free(aux->info);
		free(aux);
	}

	//eliberam coada

	free(c);
}

//functie de scriere a informatiei dintr-o coada intr-un fisier

void AfiC(TCoada *c,FILE *dfp)
{

	TCoada *v;

	//initializam o noua coada in care vom transfera elementele

	v=InitC();

	TSwitch x;
	x.denumire=malloc(100);
	x.func=malloc(20);
	x.ipv4=malloc(40);

	fprintf(dfp,"{");

	while(c->vf!=NULL)
	{
		//cat timp avem elemente in coada le extragem afisam id-ul si le
		//inseram in coada auxiliara

		ExtrC(c,&x);
		fprintf(dfp,"%d ",x.id);
		InsC(v,&x);
	}

	fprintf(dfp,"}\n");

	while(v->vf!=NULL)
	{
		//transferam elementele inapoi

		ExtrC(v,&x);
		InsC(c,&x);
	}

	//eliberam memoria folosita
	
	DistrugereC(v);	
	elibel(&x);	
}	


//functie ce concateneaza doua cozi

void ConcatC(TCoada *c, TCoada *v)
{
	TSwitch x;
	x.denumire=malloc(100);
	x.func=malloc(20);
	x.ipv4=malloc(40);

	//cat timp avem elemente in prima le transferam in a doua
	
	while(c->vf!=NULL)
	{
		ExtrC(c,&x);
		InsC(v,&x);
	}

	//eliberam memoria folosita

	elibel(&x);

	//nu eliberam si coada c pentru ca in program va fi folosita ulterior
}

#endif
