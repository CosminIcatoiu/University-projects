#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int min(int a, int b)
{
	if(a<=b)
	{
		return a;
	}
	
	return b;

}

void alocare(char **s ,int k)
{
	int i,j;

	for(i=0;i<k;i++)
	{
		s[i]=(char*)calloc(12000,sizeof(char));
		if(!s[i])
		{
			for(j=0;j<i;j++)
			{
				free(s[i]);
			}

			free(s);
		}
	}
}

void citire(char **s, int k)
{
	int i;
	
	for(i=0;i<k;i++)
	{
		fgets(s[i],12000,stdin);
	}

}

int lista( char **s, char**ls, int *ap, char *aux, int n)
{
	int i,j,k=0,t=0,a;
	char *p;

	for(i=0; i<n; i++)
	{
		p=strtok(s[i],aux);
		
		while(p!=NULL)
		{
			for(j=0; j<k; j++)
			{
				if(strcmp(p,ls[j])==0)
				{
					a=j;
					t=1;
				}
			}
	
			if( t == 0 )
			{
				strcpy(ls[k],p);
				ap[k]=1;
				k++;
			}

			else
			{
				ap[a]++;
			}

			t=0;
			p=strtok(NULL,aux);

		}
	}
	return k;
} 

void sortare( char **s, int *ap, int k)
{
	int ok, i, j=0;
	int tmp;
	char *ajutor;

	ajutor=(char *)calloc(12000,sizeof(char));
	if(!ajutor)
	{
		printf("Nu s-a alocat ajutorul");
	}
	
		for(i = 0; i < k - 1; i++) 
		{
			ok=i;

			for(j=i+1; j < k; j++)
			{
				
			
				if ( ap[ok] < ap[j] ) 
				{
					ok=j;
				}
			}
			
			if( ok!=i)
			{
				tmp = ap[i];

				ap[i] = ap[ok];

                ap[ok] = tmp;
				
				strcpy( ajutor, s[i] );

				strcpy( s[i], s[ok] );

				strcpy( s[ok], ajutor );
			}	
		}
		for(i = 0; i < k - 1; i++) 
		{
			ok=i;

			for(j=i+1; j < k; j++)
			{
				
			
				if ( ap[ok] == ap[j] ) 
				{
					if(strcmp(s[ok],s[j]) > 0)
						ok=j;
				}
			}
			
			if( ok!=i)
			{		
				strcpy( ajutor, s[i] );

				strcpy( s[i], s[ok] );

				strcpy( s[ok], ajutor );
			}	
		}
	free(ajutor);
}

int distanta( char *v1, char *v2)
{
	int i,l1,l2, dist=0;

	l1=strlen(v1);
	l2=strlen(v2);
		
	for(i=0;i<min(l1,l2);i++)
	{
		dist=dist+abs(v1[i]-v2[i]);
	}
	
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
	return dist;
}
	
	
int main()
{
	int n, m, i, k1, k2, d;
	char **s1, **s2, **cuv1, **cuv2;
	char *aux=" ,?!';.\"\n"; // alocare dinamica
	int * aparitii1, * aparitii2;
	
	scanf("%d",&n);
	getchar();
	
	s1=(char **)calloc(n,sizeof(char *));
	if(!s1)
	{
		return -1;
	}
		
	alocare(s1, n);
	citire( s1, n );

	scanf("%d",&m);
	getchar();
	
	s2=(char **)calloc(m,sizeof(char *));
	if(!s2)
	{
		return -1;
	}
	
	alocare(s2, m);
	citire( s2, m);
	
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

	aparitii1=(int *)calloc(12000,sizeof(int));
	aparitii2=(int *)calloc(12000,sizeof(int));

	k1=lista(s1,cuv1,aparitii1,aux,n);
	k2=lista(s2,cuv2,aparitii2,aux,m);
	
	sortare(cuv1,aparitii1,k1);
	sortare(cuv2,aparitii2,k2);
	
	d= 100*abs(k2-k1);
	for(i=0; i < min(k1,k2); i++)
	{
		d=d+(aparitii1[i]+aparitii2[i])*distanta(cuv1[i],cuv2[i]);
	}
	
	printf("%d\n",d);
	
	for(i=0;i<n;i++)
	{
		free(s1[i]);	
	}
	free(s1);
	
	for(i=0;i<m;i++)
	{
		free(s2[i]);	
	}
	free(s2);
	
	for(i=0;i<12000;i++)
	{
		free(cuv1[i]);
	}
	free(cuv1);

	for(i=0;i<12000;i++)
	{
		free(cuv2[i]);
	}
	free(cuv2);	

	free(aparitii1);
	free(aparitii2);

	return 0;
}

