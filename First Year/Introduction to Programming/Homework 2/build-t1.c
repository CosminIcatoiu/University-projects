//Icatoiu Vlad-Cosmin 314CB

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//functie care numara aparitiile unui cuvant intr-un sir

int aparitii( char *s1, char *s2, char *aux )
{
	int ok=0;
	char *p, *copie1;
	
	// luam o copie pentru a nu strica sirul din cauza lui strtok

	copie1=strdup(s1);
	
	//cautam cu ajutorul delimitatorilor cuvintele din ea

	p=strtok( copie1, aux );
	
	while( p!=NULL )
	{
	
		//verificam daca cuvantul din text e acelasi cu cel cautat de noi

		if( strcmp( p, s2 ) == 0 ) 
		{
			ok++; // daca da marim contor-ul ok
		}

		//reapelam pentru urmatorul cuvant

		p=strtok(NULL,aux);
	}

	//eliberam memoria si returnam numarul de aparitii

	free(copie1);
	return ok;
}

//functie care sterge intr-un sir de pe pozitia pos, n elemente

char *strdel( char*s ,int pos, int n)
{
	char*p=s+pos-1;

	//pornim de la pozitia pos si pana la '\0'
	
	while( *p!='\0' )
	{

	//suprascriem elementul continut la *p cu elementul de la *(p+n)

		*p=*(p+n);

	// dupa care marim p-ul pentru a schimba pozitia

		p++;
	}
	
	//returnam noul sir

	return s;
}

//functie care insereaza intr-un sir pe pozitia pos sirul s1

char *strins( char*s, int pos, char*s1)
{

	int l=strlen(s1),i,l1=strlen(s);

	//pornind de la finalul sirului si pana la pozitia pos
	//mutam la dreapta cu strlen(s1) toate elementele
	
	for( i=l1-1; i>=pos-1 ; i-- )
	{
		s[i+l]=s[i];
	}
	
	//pornind de la pozitia pos pana la pos +l suprascriem elementele lui s cu cele ale lui s1

	for( i=0 ; i<l; i++ )
	{
		s[i+pos-1]=s1[i];
	}

	//returnam noul sir

	return s;
}

// functie care realoca un sir

void realocare( char **s, int n)
{
	char *p;
	p=realloc( *s, n);
	if(!p)
		printf("Nu pot realoca");
	else *s=p;
}

//functie care inlocuieste in s un cuvant s1 cu un cuvant s2

char *inlocuire( char *s, char*s1, char*s2, char *aux)
{
	int ct,i=0;
	char *q, *copie ;
	
	//folosim o copie pentru a nu strica sirul

	copie=strdup(s);	

	//si cautam in ea cuvintele cu ajutorul delimitatorilor

	q=strtok(copie,aux);
	
	while( q!=NULL )//cat timp avem cuvinte
	{

		//daca q e chiar cuvantul cautat

		if( strcmp(q,s1)==0 )
		{

			// retinem cu ajutorul lui ct pozitia din sirul initial s

			ct=q-copie+1+i*(strlen(s2)-strlen(s1));
			
			//daca inlocuitorul e mai mare realocam dimensiunea sirului

			if(strlen(s2)>strlen(s1))
			{
				realocare(&s,  2 * ( strlen(s) + strlen(s2)-strlen(s1) ) );
			}

			//stergem sirul s1 si inseram sirul s2

			strdel(s, ct ,strlen(s1));

			strins(s, ct ,s2);

			//contorizam numarul de aparitii

			i++;
		}
		q=strtok(NULL,aux); // reapelam pentru un nou cuvant
		
	}	

	//eliberam memoria si returnam sirul

	free(copie);
	return s;
}

//functie care deplaseaza la dreapta literele unui cuvant cu k pozitii

char * deplasare( char *s, int k)
{

	int i,j;
	char c;
		

	for( j=1; j<=k%strlen(s); j++)//pentru eficientizare mergem pana la k modulo strlen(s)
	{

	//retinem intr-un auxiliar ultima litera

		c=s[strlen(s)-1];
	
	//incepand cu ultima litera pana la prima suprascriem litera de pe pozitia i cu cea de pe pozitia i-1

		for( i=strlen(s)-1; i>0; i-- )
			s[i]=s[i-1];

	//punem pe prima pozitie ultima litera

		s[0]=c;
	}
	
	//returnam noul sir

	return s;
}

//functie care face deplasarea pentru fiecare cuvant al unui sir
	
char* mutare( char *s, char *aux,int k)
{
	char *p,*copie;
	int l;

	//folosim o copie pentru a nu strica sirul si cautam cu ajutorul delimitatorilor cuvintele

	copie=strdup(s);

	p=strtok(copie,aux);

	while( p!=NULL )
	{
		l=p-copie+1;

		//retinem pozitia la care trebuie facuta inlocuirea

		strdel(s,l,strlen(p));

		strins(s,l,deplasare(p,k));

		//stergem cuvantul si il inlocuim cu cuvantul deplasat de k ori

		p=strtok(NULL,aux); // reapelam pentru un nou cuvant
	}

	// returnam s si dam free la memorie

	free(copie);

	return s;
	
}

int main()
{
	char **v;

	char *s, *s1;

	int i, j, n, m, nr=0, op, k;

	char *aux=" ,?!';.\"\n";

	// citim numarul de linii ale textului
	
	scanf("%d",&n);
	getchar();	
	
	//alocam memorie pentru cele 2 cuvinte

	s1=(char*)calloc(12000,sizeof(char));
	if(!s1)
		return -1;

	s=(char*)calloc(12000,sizeof(char));
	if(!s)
		return -1;

	//alocam memorie pentru text si pentru fiecare linie

	v=(char **)calloc(n,sizeof(char*));
	if(!v)
		return -1;

	for(i=0;i<n;i++)
	{
		v[i]=(char*)calloc(12000,sizeof(char));
		if(!v[i])
		{
			for(j=0;j<i;j++)
			{
				free(v[i]);
			}
			free(v);
		}
	}

	//citim textul

	for(i=0;i<n;i++)
	{
		fgets(v[i],12000,stdin);
	}

	//citim numarul de operatii

	scanf("%d",&m);
	getchar();
	
	for(j=1;j<=m;j++)
	{
		scanf("%d",&op);//citim operatia
		getchar();

		if( op==1 )
		{
			scanf("%s",s);
			
			//citim cuvantul ce trebuie cautat

			for( i=0; i<n; i++ )
			{
				nr=nr+aparitii(v[i],s,aux);
			}
			
			printf("%d\n",nr);
			nr=0;
		}
		
		if(op==2)
		{
			scanf("%s%s",s,s1);//citim cele 2 cuvinte
			
			for( i=0; i<n; i++ )
			{
				v[i]=inlocuire(v[i],s,s1,aux);
				printf("%s",v[i]);
			}
		}
		
		if(op==3)
		{
			scanf("%d",&k);//citim numarul de rotiri

			for(i=0;i<n;i++)
			{
				printf("%s",mutare(v[i],aux,k));
			}
		}
	}
	
	//eliberam memoria

	free(s);
	free(s1);
	
	for( i=0; i<n; i++ )
	{
		free(v[i]);
	}
	free(v);

	return 0;
}
