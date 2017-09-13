#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cuvant( char *s, char *cuv)
{
	int j=0, i, count1=0, count2=0, ok=0, k;
	
	char *q,*aux;	

	aux=calloc(12000,sizeof(char));
	if(!aux)
	{
		printf("Nu s-a putut aloca aux");
	}

	for(i=0; i<strlen(cuv)-1 ; i++)
	{
		
		if(cuv[i]!='*' && cuv[i]!='.')
			ok++;

		if(cuv[i]=='*')
			count1++;

		if(cuv[i]=='.')
			count2++;

	}

	if(ok==0)
	{

		if(count1==0)
		{

			if(strlen(s)==count2)
			{
				free(aux);
				return 1;
			}

			else
			{
				free(aux);
				return 0;
			}
		}

		else
		{

			if(strlen(s)>=count2)
			{
				free(aux);
				return 1;
			}

			else
			{
				free(aux);
				return 0;
			}
		}
	
	}	
	
	if(strlen(s)<ok+count2)
	{
		free(aux);
		return 0;
	}
			
	for(i=0; i<strlen(cuv)-1 ;i++)
	{
		if(cuv[i]!='.' && cuv[i]!='*' && cuv[i]!=s[j])
		{	
			free(aux);
			return 0;
		}

		if(cuv[i]=='.' && s[j]=='\0')
		{
			free(aux);
			return 0;
		}

		if(cuv[i]=='*')
		{
			
			strcpy(aux,cuv);

			if(cuv[i+1]=='*')
			{

				for(k=i;k<strlen(aux);k++)
					{
						aux[k]=aux[k+1];
						cuv[k]=cuv[k+1];
					}
			}

			if(cuv[i+1]=='.')
			{
								
				for(k=i;k<strlen(aux);k++)
				{
					aux[k]=aux[k+1];
				}

				if(cuvant(s,aux) == 1)
				{
					free(aux);
					return 1;
				}
			}
	
			if(cuv[strlen(cuv)-2]!=s[strlen(s)-1] && cuv[strlen(cuv)-2]!='*' && cuv[strlen(cuv)-2]!='.')
			{
				free(aux);
				return 0;
			}

			if( i+1 == strlen(cuv) - 1 )
			{
				free(aux);
				return 1;
			}

			if(cuv[i+1]=='*')
			{
				j--;
			}
			
			if(cuv[i+1]=='.' && j <= strlen(s)-strlen(cuv)+i+1)
			{
					j=strlen(s)-strlen(cuv)+i+1;
			}

			if(cuv[i+1]!='*' && cuv[i+1]!='.' && i+1 < strlen(cuv) -1)
			{
				strcpy(aux,cuv);
				aux[i]='\0';	
				strcat(aux,cuv+i+1);
				
				if(cuvant(s,aux)==1)
				{
					free(aux);
					return 1;
				}
				else
				{

					if( j+1 >= strlen(s) )
					{
						free(aux);
						return 0;
					}

					else
					{
						q=strchr(s+j+1,cuv[i+1]);

						if(q==NULL)
						{
							free(aux);
							return 0;
						}

						while(strlen(q) > strlen(cuv)-j-2 && strchr(q+1,cuv[i+1])!=NULL )
							{

								if(cuvant(q,cuv)==1)
								{
									free(aux);
									return 1;
								}

								q=strchr(q+1,cuv[i+1]);
							} 

						j=q-s-1;
						
					}
				}	
			}
		}
		
		j++;
	}
	
	if(strlen(s)!=j && cuv[strlen(cuv)-2]!='*')
	{
		free(aux);
		return 0;
	}
	free(aux);
	return 1;
}


int numara( char **s, char *expr, int n)
{
	char *copie, *p;

	int nr=0,i;
	
	char *aux=" ,.;?!\n\"'";

	for(i=0;i<n;i++)
	{
		copie=strdup(s[i]);
		p=strtok(copie,aux);
		while(p!=NULL)
		{
	
			if(cuvant(p,expr)==1)
				nr++;
			p=strtok(NULL,aux);

		}

	}
	free(copie);
	return nr;
}

int main()
{
	char **s, **v;
	int n,m,i,j=0;

	scanf("%d",&n);
	getchar();
	
	s=(char **)calloc(n,sizeof(char*));
	if(!s)
	{
		return -1;
	}

	for(i=0;i<n;i++)
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

	for(i=0;i<n;i++)
	{
		fgets(s[i],12000,stdin);
	}

	scanf("%d",&m);
	getchar();
	
	v=calloc(m,sizeof(char*));
	if(!v)
	{
		return -1;
	}
	
	for(i=0;i<m;i++)
	{
		v[i]=calloc(12000,sizeof(char*));
	
		if(!v[i])
		{
			for(j=0;j<i;j++)
			{
				free(v[i]);
			}
			free(v);
		}
	}

	for(i=0;i<m;i++)
	{
		fgets(v[i],12000,stdin);
	}
	
	for(j=0;j<m;j++)
	{
		printf("%d\n",numara(s,v[j],n));
	}
	
	for(i=0;i<m;i++)
	{
		free(v[i]);
	}
	free(v);
	
	for(i=0;i<n;i++)
	{
		free(s[i]);
	}
	free(s);
	
	return 0;
}
