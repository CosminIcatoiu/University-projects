#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Structura ce defineste o tranzitie 

typedef struct{
	char *si,*sf;
	char *ci,*cf,*pos;
}tranzitie;

// functia ce ruleaza masina Turing 

void mt( char * banda, char * sinit, char **sfinale,tranzitie *t,int tr,int m,FILE * fp)
{

	int i=1,j,ok1=0,ok2=0;

	char *sactual;

	sactual=calloc(4,sizeof(char));
	if(!sactual)
		return ;

	//Pornim din starea initiala 

	strcpy(sactual,sinit);
	
	while(1)
	{
		// Verificam daca ne aflam intr-o stare finala, caz in care scriem banda
		// si iesim din while

		for(j=0;j<m;j++)
		{
			if(strcmp(sactual,sfinale[j]) == 0)
			{
				fprintf(fp,"%s\n",banda);
				ok1=1;
				break;
			}
		}
		if(ok1==1)
			break;

		//Daca nu ne aflam intr-o stare finala, cautam in vectorul de tranzitii
		//pe cea care corespunde cu caracterul citit de pe banda si cu starea
		// in care ne aflam
	
		for(j=0;j<tr;j++)
		{
			if(strcmp(sactual,t[j].si)==0 && banda[i]==t[j].ci[0])
			{
				ok2=1;
				//actualizam starea

				strcpy(sactual,t[j].sf);

				//scriem pe banda noul caracter

				banda[i]=t[j].cf[0];
				
				//mutam capul de citire si incetam cautarea

				if( t[j].pos[0]=='R')
					i++;
				if( t[j].pos[0]=='L')
					i--;
				break;
			}
		}
		
		//Daca nu am gasit nicio tranzitie care sa se potriveasca inseamna ca 
		// am ajuns intr-o stare nedefinita pentru caracterul nostru

		if(ok2==0)
		{
			fprintf(fp,"Se agata");
			break;
		}

		//Reactualizam verificatorul

		ok2=0;
	}
}
					 
int main()
{
	char **stari, **sfinale;
	int m,n,i,j,tr;
	char *banda,*sinit;

	FILE *fp;

	banda=calloc(1000,sizeof(char));
	if(!banda)
		return 0;

	sinit=calloc(4,sizeof(char));
	if(!sinit)
	{
		free(banda);
		return 0;
	}

	//Deschidem fisierul ce contine masina Turing 

	fp=fopen("tm.in","r");

	//Citim numarul de stari

	fscanf(fp,"%d",&n);

	stari=calloc(n,sizeof(char*));
	if(!stari)
		return 0;

	for(i=0;i<n;i++)
	{
		stari[i]=calloc(4,sizeof(char));
		if(!stari[i])
		{
			for(j=0;j<i;j++)
				free(stari[j]);
			free(stari);
			break;
		}
	}

	//Citim starile

	for(i=0;i<n;i++)
		fscanf(fp,"%s",stari[i]);

	//Citim numarul de stari finale

	fscanf(fp,"%d",&m);

	sfinale=calloc(m,sizeof(char*));
	if(!sfinale)
		return 0;

	for(i=0;i<m;i++)
	{
		sfinale[i]=calloc(4,sizeof(char));
		if(!sfinale[i])
		{
			for(j=0;j<i;j++)
				free(sfinale[j]);
			free(sfinale);
			break;
		}
	}

	//Citim starile finale

	for(i=0;i<m;i++)
		fscanf(fp,"%s",sfinale[i]);

	//Citim starea initiala si numarul de tranzitii

	fscanf(fp,"%s",sinit);
	fscanf(fp,"%d\n",&tr);

	//Definim un vector de tranzitii si il alocam

	tranzitie *t;

	t=calloc(tr,sizeof(tranzitie));
	if(!t)
		return 0;

	for(i=0;i<tr;i++)
	{
		t[i].si=calloc(4,sizeof(char));
		t[i].sf=calloc(4,sizeof(char));
		t[i].ci=calloc(2,sizeof(char));
		t[i].cf=calloc(2,sizeof(char));
		t[i].pos=calloc(2,sizeof(char));

		if(!(t[i].si && t[i].sf && t[i].ci && t[i].cf && t[i].pos))
		{
			for(j=0;j<i;j++)
			{
				free(t[j].ci);
				free(t[j].cf);
				free(t[j].pos);
				free(t[j].si);
				free(t[j].sf);
			}
			free(t);
			break;
		}
	}

	//Citim tranzitiile 

	for(i=0;i<tr;i++)
	{
		fscanf(fp,"%s%s%s%s%s",t[i].si,t[i].ci,t[i].sf,t[i].cf,t[i].pos);
	}

	fclose(fp);

	//Deschidem fisierul ce contine banda si o citim

	fp=fopen("tape.in","r");

	fscanf(fp,"%s",banda);

	fclose(fp);

	fp=fopen("tape.out","w");

	//Apelam functia ce simuleaza masina Turing

	mt(banda,sinit,sfinale,t,tr,m,fp);

	fclose(fp);

	return 0;
}


	


