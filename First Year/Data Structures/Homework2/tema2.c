//Icatoiu Vlad-Cosmin 314CB

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stiva.h"
#include "coada.h"

//functia care adauga un nou switch in retea

void add( TStiva **s, TCoada *c ,TSwitch x, int id_stiva, char * principal)
{
	TStiva * aux;
	TCoada *v;
	TSwitch y,z;

	// alocam 2 switch-uri auxiliare de care ne vom ajuta ulterior, o coada si
	// o stiva

	v=InitC();
	if(!v)
		return;

	aux=InitS();
	if(!aux)
	{
		free(v);
		return;
	}

	y.denumire=malloc(40);

	if(!y.denumire)
	{
		free(v);
		free(aux);
		return;
	}

	y.func=malloc(10);

	if(!y.func)
	{
		free(y.denumire);
		free(v);
		free(s);
		return;
	}

	y.ipv4=malloc(40);

	if(!y.ipv4)
	{
		free(y.denumire);
		free(v);
		free(s);
		free(y.func);
		return;
	}

	z.denumire=malloc(100);
	if(!z.denumire)
	{
		free(y.denumire);
		free(v);
		free(s);
		free(y.func);
		free(y.ipv4);
		return;	
	}

	z.func=malloc(20);
	
	if(!z.func)
	{
		free(y.denumire);
		free(v);
		free(s);
		free(y.func);
		free(y.ipv4);
		free(z.denumire);
		return;	
	}
	z.ipv4=malloc(40);
	
	if(!z.ipv4)
	{
		free(y.denumire);
		free(v);
		free(s);
		free(y.func);
		free(y.ipv4);
		free(z.denumire);
		free(z.func);
		return;	
	}

	//daca trebuie sa inseram in stiva

	if( strcmp(x.func,"STACK") == 0)
	{
		//daca stiva e nula pur si simplu inseram

		if(s[id_stiva]->vf==NULL)
		 Push(s[id_stiva],	&x);
		else
		{
			//altfel, daca switch-ul nu e principal

			if(strcmp(principal,"NON_BASE") == 0)
			{
				
					//extragem elementele din stiva intr-o stiva auxiliara
					//pana cand gasim unul cu id mai mare, oprindu ne inainte 
					// de cel principal

					while(s[id_stiva]->vf->urm!=NULL )
					{
						if( cmpid(s[id_stiva]->vf->info,&x)<0 )
						{
							Pop(s[id_stiva],&y);
							Push(aux,&y);
						}
						else break;
					}

					//inseram in locul potrivit si reintroducem elementele

					Push(s[id_stiva],&x);
					while(aux->vf!=NULL)
					{
						Pop(aux,&y);
						Push(s[id_stiva],&y);
					}
			}
			else
			{

				//extragem elementele intr-o noua stiva

				while(s[id_stiva]->vf->urm!=NULL)
				{
					Pop(s[id_stiva],&y);
					Push(aux,&y);
				}

				//salvam vechiul varf intr-un switch auxiliar pentru a-l
				//insera ordonat

				Pop(s[id_stiva],&z);

				//introducem noua baza

				Push(s[id_stiva],&x);

				//reintroducem elementele si avem grija sa inseram si vechea
				//baza in locul potrivit

				while( aux->vf !=NULL )
				{
					if( cmpid(&z,aux->vf->info) < 0 )
					{
						Pop(aux,&y);
						Push(s[id_stiva],&y);
					}
					else break;
				}
				Push(s[id_stiva],&z);
				while( aux->vf !=NULL)
				{
					Pop(aux,&y);
					Push(s[id_stiva],&y);
				}
			}
		}
	}
	else
	{
		// daca trebuie sa inseram in coada si aceasta e vida pur si simplu
		// inseram 

		if(c->vf==NULL)
			InsC(c,&x);
		else
		{
			//altfel extragem elemente din coada in una auxiliara pana cand
			// gasim locul unde trebuie sa inseram noul element

			while(c->vf != NULL)
			{
				
				if(conversie( ((TSwitch *)c->vf->info)->ipv4) < conversie(x.ipv4))
				{
					
					ExtrC(c,&y);
					InsC(v,&y);
				}
				else break;
			}

			//inseram noul switch in coada auxiliara si dupa aceea le concatenam

			InsC(v,&x);
			ConcatC(c,v);
			ConcatC(v,c);
		}
	}

	//eliberam memoria alocata

	elibel(&y);
	elibel(&z);
	DistrugereS(aux);
	DistrugereC(v);
}

//functia care elimina un switch din retea

void del( TStiva **s, TCoada *c, int id, int nrstive)
{
	TCoada *v;
	TStiva *aux;
	int i;
	
	//initializam atat o coada si o stiva ajutatoare cat si un switch auxiliar

	v=InitC();
	if(!v)
		return;

	aux=InitS();
	if(!aux)
	{
		free(v);
		return;
	}

	TSwitch y;

	y.denumire=malloc(40);

	if(!y.denumire)
	{
		free(v);
		free(aux);
		return;
	}

	y.func=malloc(10);

	if(!y.func)
	{
		free(y.denumire);
		free(v);
		free(s);
		return;
	}

	y.ipv4=malloc(40);

	if(!y.ipv4)
	{
		free(y.denumire);
		free(v);
		free(s);
		free(y.func);
		return;
	}
	
	//cautam switch ul in coada si daca switch ul nu corespunde cu cel cautat
	//il inseram intr-o coada auxiliara

	while(c->vf!=NULL)
	{
		if( ((TSwitch*)c->vf->info)->id != id )
		{
			ExtrC(c,&y);
			InsC(v,&y);
		}
		else
			ExtrC(c,&y);
	}

	//reintroducem elementele in coada initiala fara cel sters

	while(v->vf!=NULL)
	{
		ExtrC(v,&y);
		InsC(c,&y);
	}
	
	//cautam switch-ul in vectorul de stive

	for( i=0; i<nrstive ; i++)
	{
		//extragem din stive in cea auxiliara cat timp avem switch uri diferite
		//de cel cautat

		while(s[i]->vf !=NULL)
		{
			if( ((TSwitch*)s[i]->vf->info)->id != id )
			{
				Pop(s[i],&y);
				Push(aux,&y);
			}
			else
				Pop(s[i],&y);
		}
		
		//reintroducem elementele in stiva initiala

		DistrugereS(s[i]);
		s[i]=RastoarnaS(aux);
	}
	
	//eliberam memoria alocata

	elibel(&y);
	DistrugereS(aux);
	DistrugereC(v);
	
}

//functie care intoarce cel mai mic ip din coada

unsigned long int ipmin(TCoada * c)
{
	//daca nu avem elemente in coada returnam 0, altfel convertim ip-ul

	if(c->vf==NULL)
		return 0;
	return conversie( ((TSwitch *)c->vf->info)->ipv4 );

}

//functie care afiseaza switch-urile din retea

void show( TStiva **s, TCoada *c, int nr,FILE *dfp)
{
	int i;

	//afisam informatia din coada conform cerintei

	if(c->vf!=NULL)
		AfiC(c,dfp);
	else
		fprintf(dfp,"{}\n");

	//pentru fiecare stiva din vector se afiseaza informatia conform cerintei

	for( i=0;i<nr;i++)
	{
		if(s[i]->vf!=NULL)
		{
			fprintf(dfp,"%d:\n",i);
			AfiS(s[i],dfp);
		}
		else 
		fprintf(dfp,"%d:\n",i);
	}
}

//functie care schimba modul de functionare a unui switch

void set( TStiva **s, TCoada *c , TSwitch y, char *p ,int id_stiva, int nr)
{
	int ok=0,i;
	TStiva * aux;
	TCoada * v;
	TSwitch z;

	//initializam o coada, o stiva si un switch auxiliar

	v=InitC();
	if(!v)
		return;

	aux=InitS();
	if(!aux)
	{
		free(v);
		return;
	}

	z.denumire=malloc(40);
	if(!z.denumire)
	{
		free(v);
		free(s);
		return;	
	}

	z.func=malloc(10);
	
	if(!z.func)
	{
		free(v);
		free(s);
		free(z.denumire);
		return;	
	}
	z.ipv4=malloc(40);
	
	if(!z.ipv4)
	{
		free(v);
		free(s);
		free(z.denumire);
		free(z.func);
		return;	
	}

	//daca trebuie sa il introducem in stiva

	if(strcmp(y.func,"STACK")== 0)
	{
		//cautam in coada switch-ul trecand elementele in coada auxiliara

		while(c->vf!=NULL)
		{
			if( cmpid(c->vf->info,&y) == 0)
			{
				strcpy(y.denumire,((TSwitch *)c->vf->info)->denumire);
				strcpy(y.ipv4,((TSwitch *)c->vf->info)->ipv4);
				ok=1;
				break;
			}
			ExtrC(c,&z);
			InsC(v,&z);
		}

		//reintroducem elementele in coada

		ConcatC(c,v);
		ConcatC(v,c);

		//daca s-a gasit in coada switch-ul respectiv il stergem si apoi il
		//introducem cu noua functionare
	
		if(ok == 1)
		{
			del(s,c,y.id,nr);
			add(s,c,y,id_stiva,p);
		}
		else 
		{

			//daca nu e in coada il cautam in vectorul de stive 

			for(i=0;i<nr;i++)
			{
				//extragem elementele din stiva pana cand il gasim pe cel cautat

				while(s[i]->vf !=NULL)
				{
					if( cmpid(s[i]->vf->info,&y) == 0 )
					{
						strcpy(y.denumire,((TSwitch *)s[i]->vf->info)->denumire);
						strcpy(y.ipv4,((TSwitch *)s[i]->vf->info)->ipv4);
						ok=1;
						break;
					}
				Pop(s[i],&z);
				Push(aux,&z);
				}

				//reintroducem elementele in stiva initiala

				while(aux->vf!=NULL)
				{
					Pop(aux,&z);
					Push(s[i],&z);
				}

				//daca a fost gasit elementul il stergem si il introducem cu 
				//noua functionare si oprim cautarea

				if(ok==1)
				{
					del(s,c,y.id,nr);
					add(s,c,y,id_stiva,p);
					break;
				}	
			}
		}
	}
	else
	{

		//daca trebuie sa il introducem in coada
		//procedam ca mai sus, cautandu-l in vectorul de stive si, in momentul
		//in care l-am gasit il stergem, il introducem cu noua functionalitate
		//si oprim cautarea

		for(i=0;i<nr;i++)
		{
			while(s[i]->vf !=NULL)
			{
				if( cmpid(s[i]->vf->info,&y) == 0 )
				{
					strcpy(y.denumire,((TSwitch *)s[i]->vf->info)->denumire);
					strcpy(y.ipv4,((TSwitch *)s[i]->vf->info)->ipv4);
					ok=1;
					break;
				}
				Pop(s[i],&z);
				Push(aux,&z);
			}
			while(aux->vf!=NULL)
			{
				Pop(aux,&z);
				Push(s[i],&z);
			}
			if(ok==1)
			{
				del(s,c,y.id,nr);
				add(s,c,y,id_stiva,p);
				break;
			}	
		}
	}

	//eliberam memoria alocata

	elibel(&z);
	DistrugereS(aux);
	DistrugereC(v);
}
		
int main(int argc , char * argv[])
{
	TStiva **s;
	TCoada *c;
	int i,nr,id_stiva;
	TSwitch x;
	FILE * fp,*dfp;
	c=InitC();

	//auxiliare in care citim din fisier

	char *op=malloc(100),*p=malloc(100);

	//deschidem fisierele din care citim,respectiv, in care scriem
	
	fp=fopen(argv[1],"r");
	dfp=fopen(argv[2],"w");

	//citim numarul de stive

	fscanf(fp,"%d",&nr);
	
	//alocam vectorul de stive

	s=malloc(nr*sizeof(TStiva));
	for(i=0;i<nr;i++)
		s[i]=InitS();
	
	//alocam un auxiliar in care sa citim informatiile switch-urilor

	x.denumire=malloc(100);
	x.func=malloc(20);
	x.ipv4=malloc(40);


	//in functie de operatie, citim parametrii corespunzatori si apelam
	//functia corespunzatoare

	while(fscanf(fp,"%s",op) == 1)
	{
		if(strcmp(op,"add")== 0)
		{
			fscanf(fp,"%d%s%s%s",&x.id,x.denumire,x.ipv4,x.func);

			if( strcmp(x.func,"STACK") == 0)
			{
				fscanf(fp,"%d%s",&id_stiva,p);
				add(s,c,x,id_stiva,p);
			}

			else
				add(s,c,x,0,"a");
		}

		if( strcmp(op,"del") == 0)
		{
			fscanf(fp,"%d",&x.id);
			del(s,c,x.id,nr);
		}

		if( strcmp(op,"set") == 0)
		{
			fscanf(fp,"%d%s",&x.id,x.func);

			if( strcmp(x.func,"STACK") == 0)
			{
				fscanf(fp,"%d%s",&id_stiva,p);
				set(s,c,x,p,id_stiva,nr);
			}

			else
				set(s,c,x,"a",0,nr);
		}

		if( strcmp(op,"ipmin") == 0)
			fprintf(dfp,"ipmin=%lu\n",ipmin(c));

		if( strcmp(op,"show") == 0)
		{
			show(s,c,nr,dfp);
			fprintf(dfp,"\n");
		}

	}

	//inchidem fisierele

	fclose(fp);
	fclose(dfp);


	//eliberam memoria alocata pentru vectorul de stive, pentru coada si pentru
	// auxiliari
	
	elibel(&x);
	for(i=0;i<nr;i++)
		DistrugereS(s[i]);
	free(s);
	DistrugereC(c);
	free(p);
	free(op);
	
	return 0;
}

