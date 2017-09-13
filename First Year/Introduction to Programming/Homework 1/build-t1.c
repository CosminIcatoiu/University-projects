#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int aparitii( char *s1, char *s2, char *aux )
{
	int ok=0;
	char *p, *copie1;
	
	copie1=strdup(s1);
	p=strtok(copie1,aux);
	
	while(p!=NULL)
	{
		if( strcmp( p, s2 ) == 0 ) 
		{
			ok++;
		}
		p=strtok(NULL,aux);
	}
	free(copie1);
	return ok;
}

char *strdel( char*s ,int pos, int n)
{
	char*p=s+pos-1;
	
	while(*p!='\0')
	{
		*p=*(p+n);
		p++;
	}

	return s;
}

char *strins( char*s, int pos, char*s1)
{
	int l=strlen(s1),i,l1=strlen(s);
	
	for(i=l1-1;i>=pos-1;i--)
	{
		s[i+l]=s[i];
	}
	
	for(i=0;i<l;i++)
	{
		s[i+pos-1]=s1[i];
	}

	return s;
}

void realocare( char **s, int n)
{
	char *p;
	p=realloc( *s, n);
	if(!p)
		printf("Nu pot realoca");
	else *s=p;
}

char *inlocuire( char *s, char*s1, char*s2, char *aux)
{
	int ct,i=0;
	char *q, *copie ;
	
	copie=strdup(s);	

	q=strtok(copie,aux);
	
	while(q!=NULL)
	{
		if(strcmp(q,s1)==0 && strchr(aux,q[strlen(s1)])!=NULL)
		{
			ct=q-copie+1+i*(strlen(s2)-strlen(s1));
			
			if(strlen(s2)>strlen(s1))
			{
				realocare(&s, 20*(strlen(s) + strlen(s2)-strlen(s1) )  );
			}
			strcpy(s,strdel(s, ct ,strlen(s1)));
			strcpy(s,strins(s, ct ,s2));
			i++;
		}
		q=strtok(NULL,aux);
		
	}	
	free(copie);
	return s;
}

char * deplasare( char *s, int k)
{
	int i,j;
	char c;
	for(j=1;j<=k%strlen(s);j++)
	{
		c=s[strlen(s)-1];
		for(i=strlen(s)-1;i>0;i--)
			s[i]=s[i-1];
		s[0]=c;}
	return s;
}
	
char* mutare( char *s, char *aux,int k)
{
	char *p,*copie;
	int l;

	copie=strdup(s);

	p=strtok(copie,aux);
	while(p!=NULL)
	{
		l=p-copie+1;
		strdel(s,l,strlen(p));
		strins(s,l,deplasare(p,k));
		p=strtok(NULL,aux);
	}
	return s;
	free(copie);
}

int main()
{
	char **v;
	char *s, *s1;
	int i, j, n, m, nr=0, op, k;
	char *aux=" ,?!';.\"\n";// alocare dinamica
	
	scanf("%d",&n);
	getchar();	
	
	s1=(char*)calloc(12000,sizeof(char));
	if(!s1)
		return -1;

	s=(char*)calloc(12000,sizeof(char));
	if(!s)
		return -1;

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
	for(i=0;i<n;i++)
	{
		fgets(v[i],12000,stdin);
	}

	scanf("%d",&m);
	getchar();
	
	for(j=1;j<=m;j++)
	{
		scanf("%d",&op);
		getchar();
		if(op==1)
		{
			scanf("%s",s);
			
			for(i=0;i<n;i++)
			{
				nr=nr+aparitii(v[i],s,aux);
			}
			
			printf("%d\n",nr);
			nr=0;
		}
		
		if(op==2)
		{
			scanf("%s%s",s,s1);
			
			for(i=0;i<n;i++)
			{
				v[i]=inlocuire(v[i],s,s1,aux);
				printf("%s",v[i]);
			}
		}
		
		if(op==3)
		{
			scanf("%d",&k);

			for(i=0;i<n;i++)
			{
				printf("%s",mutare(v[i],aux,k));
			}
		}
	}
	
	free(s);
	free(s1);
	
	for(i=0;i<n;i++)
	{
		free(v[i]);
	}
	free(v);
	return 0;
}
