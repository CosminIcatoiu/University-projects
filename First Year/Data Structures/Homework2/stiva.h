#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "element.h"

#ifndef Stiva
#define Stiva

typedef struct{
	TLG vf;
}TStiva;

//functie ce initializeaza o stiva noua

TStiva* InitS()
{
	TStiva *s;
	
	//se aloca memoria pentru o stiva

	s=malloc(sizeof(TStiva));

	//in caz ca nu s-a reusit se trateaza eroarea

	if(!s)
	{
		printf("Nu s-a reusit alocarea stivei");
		return NULL;
	}

	//se initializeaza varful cu NULL si se returneaza stiva

	s->vf=NULL;

	return s;
}

//functie care insereaza un element in stiva

void Push(TStiva *s, void * x)
{
	TLG aux;
	
	//se aloca o noua celula ce contine informatia data ca parametru 

	aux=AlocCel(x);

	// daca nu se reuseste alocarea nu mai inseram

	if(!aux)
		return;

	//daca stiva e vida introducem noul varf

	if(!s->vf)
	{
		s->vf=aux;
	}
	else
	{
		//altfel legam noua celula la vechiul varf si actualizam varful

		aux->urm=s->vf;
		s->vf=aux;
	}
}


//functie ce extrage un element din stiva si salveaza informatia in ae

void Pop(TStiva *s, void *ae)
{
	TLG aux;
	aux=s->vf;

	// daca stiva e vida nu avem ce extrage

	if( s->vf==NULL)
		return;

	// copiem informatia din varf in ae

	strcpy(((TSwitch *)ae)->denumire, ((TSwitch *)(aux->info))->denumire);
	strcpy(((TSwitch *)ae)->ipv4, ((TSwitch *)(aux->info))->ipv4);
	strcpy(((TSwitch *)ae)->func, ((TSwitch *)(aux->info))->func);
	((TSwitch *)ae)->id= ((TSwitch *)(aux->info))->id;

	//actualizam varful si eliberam memoria pentru vechiul varf

	s->vf=s->vf->urm;

	elibel(aux->info);
	free(aux->info);
	free(aux);
}

//functie ce distruge o stiva

void DistrugereS(TStiva *s)
{
	TLG aux;

	//daca stiva e vida eliberam doar memoria alocata pentru ea

	if(s->vf==NULL)
	{
		free(s);
		return ;
	}

	// altfel plecam din varf

	while(s->vf!=NULL)
	{
		//extragem varful intr-un auxiliar

		aux=s->vf;

		//actualizam noul varf (la fel ca la pop)		

		s->vf=s->vf->urm;

		//eliberam informatia din vechiul varf
	
		elibel(aux->info);
		free(aux->info);
		free(aux);
	}

	//eliberam stiva

	free(s);
}

//functie ce rastoarna o stiva

TStiva* RastoarnaS(TStiva *s)
{
	TStiva *v;

	//initializam stiva in care urmeaza sa rasturnam
	
	v=InitS();

	TSwitch x;
	x.denumire=malloc(100);
	x.func=malloc(20);
	x.ipv4=malloc(40);

	//extragem elementele din stiva initiala in cea noua

	while(s->vf!=NULL)
	{
		Pop(s,&x);
		Push(v,&x);
	}

	//eliberam switch-ul ajutator

	elibel(&x);

	//nu eliberam si stiva pentru ca in program ulterior o vom refolosi

	return v;
}


//functie ce scrie informatia dintr-o stiva in fisier

void AfiS(TStiva *s,FILE *dfp)
{

	TStiva *v;
	v=InitS();
	TSwitch x;
	
	x.denumire=malloc(100);
	x.func=malloc(100);
	x.ipv4=malloc(100);

	//cat timp avem elemente in stiva

	while(s->vf!=NULL)
	{
		//le extragem, le afisam si le introducem intr-o stiva auxiliara

		Pop(s,&x);
		Afiel(&x,dfp);
		Push(v,&x);
	}
	
	while(v->vf!=NULL)
	{
		//transferam elementele inapoi

		Pop(v,&x);
		Push(s,&x);
	}
	
	//eliberam memoria folosita

	elibel(&x);
	DistrugereS(v);

}

#endif
