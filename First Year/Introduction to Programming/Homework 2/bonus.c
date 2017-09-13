//Icatoiu Vlad-Cosmin 314CB

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//functie ce verifica daca un cuvant s face match sau nu cu o expresie cuv

int cuvant( char *s, char *cuv)
{
	int j=0, i, count1=0, count2=0, ok=0, k;
	
	char *q,*aux;

	//alocam memorie unui auxiliar pe care il folosim ulterior	

	aux=calloc(12000,sizeof(char));
	if(!aux)
	{
		printf("Nu s-a putut aloca aux");
	}

	//calculam numarul de caractere alfanumerice ok, numarul de * count1 si numarul de . count2

	for(i=0; i<strlen(cuv)-1 ; i++)
	{
		
		if(cuv[i]!='*' && cuv[i]!='.')
			ok++;

		if(cuv[i]=='*')
			count1++;

		if(cuv[i]=='.')
			count2++;

	}

	//daca nu avem caractere alfanumerice

	if(ok==0)
	{

		if(count1==0)// si nu avem nici *
		{

			//verificam daca lungimea lui s e egala cu numarul de puncte

			if(strlen(s)==count2)
			{
				free(aux);
				return 1;//daca da rezulta ca face match
			}

			else// daca nu inseamna ca nu face match
			{
				free(aux);
				return 0;
			}
		}

		else// daca avem si *
		{

			//verificam daca lungimea lui s e mai mare decat numarul de puncte

			if(strlen(s)>=count2)//daca da rezulta ca face match
			{
				free(aux);
				return 1;
			}

			else// daca nu inseamna ca nu face match
			{
				free(aux);
				return 0;
			}
		}
	
	}	
	
	//daca lungimea lui s e mai mica decat numarul caracterelor diferite de * din expresie

	if( strlen(s) < ok+count2 )
	{
		free(aux);
		return 0;//expresia nu face match
	}

	//parcurgem simultan expresia, cu ajutorul lui i, si cuvantul cu ajutorul lui j 
			
	for(i=0; i<strlen(cuv)-1 ;i++)
	{

		//daca nu pe o pozitie din expresie nu avem nici punct nici * si nu e acelasi
		//caracter cu cel din cuvant rezulta ca nu face match

		if(cuv[i]!='.' && cuv[i]!='*' && cuv[i]!=s[j])
		{	
			free(aux);
			return 0;
		}

		//punem conditia ca . sa nu faca match cu '\0'

		if(cuv[i]=='.' && s[j]=='\0')
		{
			free(aux);
			return 0;
		}

		//tratam cazul cand pe pozitia i avem *

		if(cuv[i]=='*')
		{
			
			strcpy(aux,cuv); // copiem in auxiliar cuvantul

			//daca si pe pozitia i+1 avem tot * eliminam atat in auxiliar cat si in cuvant
			// steluta respectiva pentru ca ** sunt echivalente cu 1

			if(cuv[i+1]=='*')
			{

				for(k=i;k<strlen(aux);k++)
					{
						aux[k]=aux[k+1];
						cuv[k]=cuv[k+1];
					}
			}

			//daca pe pozitia i+1 avem . construim recursiv expresiile ce au cel putin o 
			//steluta egala cu nul si verificam daca macar unul face match cu cuvantul nostru
			//daca da, atunci si expresia face match(ex a*.*. formeaza a.*., a.., a*..)


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

			//pentru a scapa de cazuri verificam daca ultima litera a expresiei e . sau * sau 
			//e egala cu ultima litera cuvantului; daca nu se intampla macar una inseamna ca nu fac match
	
			if(cuv[strlen(cuv)-2]!=s[strlen(s)-1] && cuv[strlen(cuv)-2]!='*' && cuv[strlen(cuv)-2]!='.')
			{
				free(aux);
				return 0;
			}

			//daca am ajuns pe ultima pozitie din expresie, ea fiind * rezulta ca se face match

			if( i+1 == strlen(cuv) - 1 )
			{
				free(aux);
				return 1;
			}

			//daca avem . dupa * mutam j-ul cu atatea pozitii inainte de finalul cuvantului
			//cu cate pozitii mai sunt pana la finalul expresiei, cu conditia ca aceasta pozitie
			// sa fie dupa cea actuala
			
			if(cuv[i+1]=='.' && j <= strlen(s)-strlen(cuv+i+1) )
			{
					j=strlen(s)-strlen(cuv+i+1);
			}
			
			//daca urmatorul caracter dupa * este un caracter alfanumeric

			if( cuv[i+1] != '.' )
			{

				//la fel ca mai sus cream recursiv toate cuvintele care au cel putin o * nula si
				//verificam daca macar unul face match, caz in care si expresia noastra face match			

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

					//daca j-ul a ajuns la finalul cuvantului inseamna ca nu se mai poate face match
					//pentru ca nu exista corespondent pentru careacterul alfanumeric i+11

					if( j+1 >= strlen(s) )
					{
						free(aux);
						return 0;
					}

					else
					{

						//cautam in cuvant prima aparitie a caracterului de pe pozitia i+1						

						q=strchr(s+j+1,cuv[i+1]);

						//daca nu exista atunci nu se face match

						if(q==NULL)
						{
							free(aux);
							return 0;
						}
						
						//cat timp exista o alta aparitie caracterului in s care sa fie cel putin
						//la fel de apropiata de finalul cuvantului il mutam pe q acolo si verificam
						//daca face match cu ce a ramas pana la finalul expresiei noastre

						while(strlen(q) > strlen(cuv)-j-2 && strchr(q+1,cuv[i+1])!=NULL )
							{

								if(cuvant(q,cuv+i+1)==1)
								{
									free(aux);
									return 1;
								}

								q=strchr(q+1,cuv[i+1]);
							}

						//daca nu s-a facut match se muta j-ul corespunzator 

						j=q-s-1;
						
					}
				}	
			}
		}
		
		//se incrementeaza j-ul la finalul parcurgerii pentru a muta pozitia in cuvant

		j++;
	}
	
	//verificam daca strlen(s)=j pentru a corecta cazurile de genul abcde si abcd unde 
	//fiecare litera din expresie gaseste corespondent dar cuvintele nu fac match

	if( strlen(s)!=j )
	{
		free(aux);
		return 0;
	}

	//daca nu a fost oprit pana aici inseamna ca expresia face match peste cuvant
	// de mentionat ca de fiecare data inainte sa returnam eliberam memoria

	free(aux);
	return 1;
}

//functie care numara cate cuvinte dintr-un text de n linii fac match cu o expresie

int numara( char **s, char *expr, int n)
{
	char *copie, *p;

	int nr=0,i;
	
	char *aux=" ,.;?!\n\"'";

	//folosim o copie pentru a nu strica sirul

	for( i=0; i<n; i++ )//pentru fiecare linie a textului
	{
		copie=strdup(s[i]);

		p=strtok(copie,aux);//cautam primul cuvant

		while( p!=NULL )//cat timp avem cuvinte
		{
	
			if(cuvant(p,expr)==1)//daca p face match cu expresia atunci crestem contorul
			{
				nr++;
			}

			p=strtok(NULL,aux);//apelam pentru urmatorul cuvant

		}

	}

	//eliberam memoria si returnam numarul de cuvinte

	free(copie);
	return nr;
}

int main()
{
	char **s, **v;

	int n,m,i,j=0;

	//citim numarul de linii ale textului

	scanf("%d",&n);
	getchar();

	//alocam memorie pentru text si pentru fiecare linie
	
	s=(char **)calloc(n,sizeof(char*));
	if(!s)
	{
		return -1;
	}

	for( i=0; i<n; i++ )
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

	//citim textul

	for( i=0; i<n; i++ )
	{
		fgets(s[i],12000,stdin);
	}

	scanf("%d",&m);//citim numarul de expresii
	getchar();
	
	//alocam vectorul de expresii

	v=calloc(m,sizeof(char*));
	if(!v)
	{
		return -1;
	}
	
	for( i=0; i<m; i++ )
	{
		v[i]=calloc(12000,sizeof(char*));
	
		if(!v[i])
		{
			for( j=0; j<i; j++ )
			{
				free(v[i]);
			}
			free(v);
		}
	}

	//citim expresiile

	for( i=0; i<m; i++ )
	{
		fgets(v[i],12000,stdin);
	}
	
	//pentru fiecare din cele m expresii afisam cate cuvinte fac match

	for( j=0; j<m; j++ )
	{
		printf("%d\n",numara(s,v[j],n));
	}
	
	//eliberam memoria

	for( i=0; i<m; i++ )
	{
		free(v[i]);
	}
	free(v);
	
	for( i=0; i<n; i++ )
	{
		free(s[i]);
	}

	free(s);
	
	return 0;
}
