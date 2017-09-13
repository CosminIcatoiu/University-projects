//Icatoiu Vlad-Cosmin 314Cb

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//functie care face minimul intre 2 numere

int min(int a, int b)
{
	if( a<=b )
	{
		return a;
	}
	
	return b;

}

//functie care aloca memorie pentru cele k linii ale unui text

void alocare(char **s ,int k)
{
	int i,j;

	for( i=0; i<k; i++ )
	{
		s[i]=(char*)calloc(12000,sizeof(char));
		if(!s[i])
		{
			for( j=0; j<i; j++ )
			{
				free(s[i]);
			}

			free(s);
		}
	}
}

//functie care citeste un text cu k linii

void citire(char **s, int k)
{
	int i;
	
	for(i=0;i<k;i++)
	{
		fgets(s[i],12000,stdin);
	}

}

//functie ce extrage cuvintele distincte dintr-un text si formeaza o lista cu acestea 
//precum si un vector cu numarul de aparitii al fiecarui cuvant si returneaza numarul de cuvinte din text

int lista( char **s, char**ls, int *ap, char *aux, int n)
{
	int i,j,k=0,t=0,a;
	char *p;
	
	// pentru fiecare linie a textului

	for(i=0; i<n; i++)
	{

		//cautam cuvintele cu ajutorul delimitatorilor

		p=strtok(s[i],aux);
		
		while(p!=NULL)//cat timp avem cuvinte
		{

			//verifcam daca q mai exista in lista noastra pana la pozitia k			

			for(j=0; j<k; j++)
			{
				if(strcmp(p,ls[j])==0)
				{

					//daca da retinem pozitia si il schimbam pe t					

					a=j;
					t=1;
				}
			}
	
			//daca e un cuvant nou il copiem in lista la pozitia k, facem numarul de aparitii 1 si marim k-ul

			if( t == 0 )
			{
				strcpy(ls[k],p);

				ap[k]=1;

				k++;
			}

			else//altfel marim numarul de aparitii
			{
				ap[a]++;
			}

			t=0;//reinitializam pentru a-l putea folosi si pentru urmatorul cuvant

			p=strtok(NULL,aux);//cautam urmatorul cuvant

		}
	}
	
	//returnam numarul de cuvinte

	return k;
} 

//functie ce sorteaza o lista de k cuvinte in acelasi timp cu un vector de aparitii

void sortare( char **s, int *ap, int k)
{
	int ok, i, j=0;
	int tmp;
	char *ajutor;

	//folosim un ajutor pentru a face interschimbarea sirurilor si tmp pentru interschimbarea aparitiilor

	ajutor=(char *)calloc(12000,sizeof(char));
	if(!ajutor)
	{
		printf("Nu s-a alocat ajutorul");
	}

	//sortam descrescator dupa numarul de aparitii	

	for(i = 0; i < k - 1; i++) 
	{

		//retinem pozitia initiala

		ok=i;

		for( j=i+1; j < k; j++ )
		{
			
			//cautam maximul aparitiilor incepand de la pozitia noastra si retinem pozitia maximului			
	
			if ( ap[ok] < ap[j] ) 
			{
				ok=j;
			}

		}
			
		if( ok!=i) // daca e diferita de pozitia initiala facem interschimbarile
		{
			tmp = ap[i];

			ap[i] = ap[ok];

			ap[ok] = tmp;
				
			strcpy( ajutor, s[i] );

			strcpy( s[i], s[ok] );

			strcpy( s[ok], ajutor );
		}	
	}

	//sortam crescator cuvintele cu acelasi numar de aparitii

	for(i = 0; i < k - 1; i++) 
	{
			
		//retinem pozitia initiala
	
		ok=i;

		for( j=i+1; j < k; j++ )
		{
				
			//cautam cel mai mic cuvant alfabetic intre cele cu acelasi numar de aparitii
			
			if ( ap[ok] == ap[j] ) 
			{
				if(strcmp(s[ok],s[j]) > 0)
				{
					ok=j;
				}
			
			}
		}

		//daca nu e pe pozitia initiala facem interschimbarea
			
		if( ok!=i )
		{		
			strcpy( ajutor, s[i] );

			strcpy( s[i], s[ok] );

			strcpy( s[ok], ajutor );
		}	
	}

	//eliberam memoria

	free(ajutor);
}

//functie ce calculeaza distanta intre 2 cuvinte

int distanta( char *v1, char *v2)
{
	int i,l1,l2, dist=0;

	l1=strlen(v1);
	l2=strlen(v2);

	//parcurgem cuvintele pana la minimul lungimilor si adunam diferenta dintre litere la contorul dist
		
	for(i=0;i<min(l1,l2);i++)
	{
		dist=dist+abs(v1[i]-v2[i]);
	}
	
	//parcurgem cuvantul mai mare de la minimul lungimilor pana la max 
	// si adunam la contor diferenta intre literele lui si '\0'

	for(i=min(l1,l2);i<l1+l2-min(l1,l2) ;i++)
	{
		if( l2 > l1 )
		{
			dist=dist+abs(v2[i]-'\0');
		}

		else
		{
			dist=dist+abs(v1[i]-'\0');
		}
	
	}

	//returnam distanta

	return dist;
}
	
	
int main()
{
	int n, m, i, k1, k2, d;

	char **s1, **s2, **cuv1, **cuv2;

	char *aux=" ,?!';.\"\n"; 

	int * aparitii1, * aparitii2;
	
	scanf("%d",&n);//citim numarul de linii al primului text
	getchar();
	
	//alocam si citim primul text

	s1=(char **)calloc(n,sizeof(char *));
	if(!s1)
	{
		return -1;
	}
		
	alocare(s1, n);
	citire( s1, n );

	scanf("%d",&m);//citim numarul de linii al celui de-al doilea text
	getchar();
	
	//alocam memorie si citim al doilea text

	s2=(char **)calloc(m,sizeof(char *));
	if(!s2)
	{
		return -1;
	}
	
	alocare(s2, m);
	citire( s2, m);

	//alocam listele de cuvinte pentru fiecare text
	
	cuv1=(char **)calloc(12000,sizeof(char *));
	if(!cuv1)
	{
		return -1;
	}
	
	cuv2=(char **)calloc(12000,sizeof(char *));
	if(!cuv2)
	{
		return -1;
	}
	
	alocare(cuv1,12000);
	alocare(cuv2,12000);

	//alocam vectorii de aparitii

	aparitii1=(int *)calloc(12000,sizeof(int));
	aparitii2=(int *)calloc(12000,sizeof(int));

	//scoatem cuvintele din fiecare text impreuna cu numarul de aparitii al fiecaruia si numarul total de cuvinte

	k1=lista(s1,cuv1,aparitii1,aux,n);
	k2=lista(s2,cuv2,aparitii2,aux,m);

	//sortam listele si vectorii de aparitii
	
	sortare(cuv1,aparitii1,k1);
	sortare(cuv2,aparitii2,k2);
	
	//calculam gradul de similitudine conform formulei

	d= 100*abs(k2-k1);

	for( i=0; i < min(k1,k2); i++ )
	{
		d=d+(aparitii1[i]+aparitii2[i])*distanta(cuv1[i],cuv2[i]);
	}
	
	printf("%d\n",d);

	//eliberam memoria
	
	for( i=0; i<n; i++ )
	{
		free(s1[i]);	
	}
	free(s1);
	
	for( i=0; i<m; i++ )
	{
		free(s2[i]);	
	}
	free(s2);
	
	for( i=0; i<12000; i++ )
	{
		free(cuv1[i]);
	}
	free(cuv1);

	for( i=0; i<12000; i++ )
	{
		free(cuv2[i]);
	}
	free(cuv2);	

	free(aparitii1);
	free(aparitii2);

	return 0;
}

