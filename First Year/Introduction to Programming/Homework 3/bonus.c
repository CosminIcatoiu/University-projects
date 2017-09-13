//Icatoiu Vlad-Cosmin 314CB

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma pack(1)

// structura fileheader-ului

typedef struct
{
    unsigned char  marker1; 
    unsigned char  marker2; 
    unsigned int   fsize; 
    unsigned short unused1;
    unsigned short unused2;
    unsigned int   offset; 
} fheader;

//structura infoheader-ului

typedef struct
{
    unsigned int   isize; 
    signed int     latime; 
    signed int     lungime; 
    unsigned short planes ;
    unsigned short bitPix ;
    unsigned int   biCompression ;
    unsigned int   imgsize; 
    int            biXPelsPerMeter ;
    int            biYPelsPerMeter ;
    unsigned int   biClrUsed ;
    unsigned int   biClrImportant ;
} iheader;

#pragma pack()

// functie care recunoaste numerele in functie de cati pixeli are matricea 5x5

int numere( char ** matrice, int l, int c) 
{
	int i,j,nr=0;

	char ** aux;

	aux=calloc( 5 , sizeof( char * ) );
	if( !aux )
		return -1;

	for( i=0; i<5; i++)
	{
		aux[i]=calloc( 5, sizeof( char ) );
		
		if( !aux[i] )
		{
			for( j=0 ; j<i; j++ )
			{
				free( aux[i] );
			}
			
			free(aux);
		}
	}

	//folosim un auxiliar in care salvam matricea 5x5 a cifrei respective

	for( i=0; i < 5 ; i++)
		for ( j=0 ; j< 5 ; j++ )
		{
			aux[i][j]=matrice[l+i][j+c];

			if( matrice[l+i][j+c]=='x')
			{
				// calculam cati pixeli colorati are cifra respectiva

				nr++;
				
				//stergem cifra din matrice pentru a nu ne mai lovi de ea

				matrice[l+i][j+c]='.';
			}
		}
	
	// in functie de valoarea contorului nr si de valorile anumitor pozitii din
	// aux, returnam cifra corespunzatoare si eliberam memoria inainte

	if( nr == 5 || nr==6 || nr == 4 ) 
	{
		for( i=0; i<5; i++ )
		{
			free(aux[i]);
		}

		free(aux);
		return 1;
	}

	if( nr == 9 || nr == 8 )
	{
		for( i=0; i<5; i++ )
		{
			free(aux[i]);
		}

		free(aux);
		return 7;
	}

	if( nr == 11 || nr == 12 )
	{
		for( i=0; i<5; i++ )
		{
			free(aux[i]);
		}

		free(aux);
		return 4;
	}

	if( nr == 10 )
	{
		if( aux[0][1]=='x' )
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 7;
		}

		else 
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 4;
		}
	}

	if( nr == 20 )
	{
		for( i=0; i<5; i++ )
		{
			free(aux[i]);
		}

		free(aux);
		return 8;
	}

	if( nr == 15 )
	{
		for( i=0; i<5; i++ )
		{
			free(aux[i]);
		}

		free(aux);
		return 0;
	}

	if( nr == 19 )
	{
		if( aux[3][4] == 'x' && aux[1][0] == 'x' )
		{
			for( i=0; i<5; i++ )
			{
			free(aux[i]);
			}

			free(aux);
			return 8;
		}
		
		else
		{
			if( aux[3][4] == '.' )
			{
				for( i=0; i<5; i++ )
				{
					free(aux[i]);
				}

				free(aux);
				return 9;
			}

			else 
			{
				for( i=0; i<5; i++ )
				{
					free(aux[i]);
				}

				free(aux);
				return 6;
			}
		}
	}	
	
	if( nr == 16)
	{
		if( aux[3][0] == 'x' && aux[3][4] == 'x')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 0;
		}

		else
		{
			if(aux[1][4] == '.' && aux[3][0]=='.')
			{
				for( i=0; i<5; i++ )
				{
					free(aux[i]);
				}

				free(aux);
				return 2;
			}

			else
			{
				if( aux[1][4] == 'x' )
				{
					for( i=0; i<5; i++ )
					{
						free(aux[i]);
					}

					free(aux);
					return 5;
				}

				else
				{
					for( i=0; i<5; i++ )
					{
						free(aux[i]);
					}

					free(aux);
					return 3;
				}
			}
		}
	}

	if( nr == 17 )
	{
		if( aux[1][0] == 'x' && aux[1][4] == 'x' && aux[3][4] == 'x' )
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 0;
		}
		
		if( aux[1][0] == 'x' && aux[3][0] == 'x' && aux[1][4] =='.' )
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}
	
			free(aux);
			return 3;
		}
	
		if( aux[1][0] == 'x' && aux[3][4] == 'x')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 2;
		}
		
		if( aux[1][0] == '.' && aux[3][4] == '.')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}
	
			free(aux);
			return 5;
		}

		if( aux[1][0] == 'x' && aux[3][4] == '.')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 9;
		}
		
		if( aux[1][0] == '.' && aux[3][4] == 'x')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 6;
		}
	}

	if( nr == 18 )
	{
		if( aux[1][0] == 'x' && aux[3][4]=='x')
		{
			if( aux[1][4] == 'x' && aux [3][0] == 'x' ) 
			{
				for( i=0; i<5; i++ )
				{
					free(aux[i]);
				}

				free(aux);
				return 8;
			}
		}
		
		if( aux[1][0] == '.' && aux[3][4] == 'x')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 6;
		}
		
		if( aux[1][0] == 'x' && aux[3][4] == '.' && aux[1][4]=='x')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 9;	 
		}

		if( aux[1][0] == 'x' && aux[3][4]=='x' )
		{
			if( aux[3][0] == '.' || aux[1][4] =='.' )
			{
				for( i=0; i<5; i++ )
				{
					free(aux[i]);
				}

				free(aux);
				return 2;
			}
		}
		
		if( aux[1][0] == 'x' && aux[3][4] == '.' && aux[1][4] =='.')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 3;
		}
		
		if( aux[1][0] == '.' && aux[3][4] =='.')
		{
			for( i=0; i<5; i++ )
			{
				free(aux[i]);
			}

			free(aux);
			return 5;
		}	
	}
	

	// in cazul in care nu s-a returnat nimic in if-urile precedente
	// e o eroare de gandire si deci, returnam o valoare aleatoare
	
	for( i=0; i<5; i++ )
	{
		free(aux[i]);
	}

	free(aux);
	return 100;
}	

int main()
{
	fheader f;
	iheader i;
	unsigned char * imagine;

	char *s, ** matrice;

	FILE *fp;

	int pad=0,j,k,l=0,size,c=0, * vect, e;

	// alocam memorie pentru vectori si matrice 

	s = calloc(100, sizeof( char) );
	if(!s)
	{
		printf("Nu s-a reusit alocarea lui s");
	}

	vect = calloc(100, sizeof(int));
	if(!vect)
	{
		printf("Nu s-a reusit alocarea lui v");
	}

	// din fisierul input citim numele fisierului folosit la bonus

	fp=fopen("input.txt","r");

	fscanf(fp,"%s",s);

	while( fscanf(fp,"%d",&e) == 1)
	{
		e++;
	}

	fscanf(fp,"%s",s);
	
	fclose(fp);

	// citim imaginea 
	
	fp=fopen(s, "rb");

	fread(&f,sizeof(fheader),1,fp);

	fread(&i,sizeof(iheader),1,fp);
	
	// calculam padding-ul 

	while( (i.latime*3 +pad) %4 != 0)
	{
		pad++;
	}
	
	// calculam dimensiunea imaginii tinand cont si de padding

	size=i.lungime*(i.latime*3+pad);
	
	// alocam memorie vectorului in care tinem minte pixelii 

	imagine=calloc(size+1, sizeof( unsigned char ) ) ;
	
	if(!imagine)
	{
		return -1;
	}

	//alocam memorie pentru matricea auxiliara

	matrice=calloc(i.lungime,sizeof (char *));
	if(! matrice)
		printf("Nu s-a reusit alocarea");

	for(j=0; j< i.lungime; j++)
	{
		matrice[j]=calloc(i.latime,sizeof(char));
		if(! matrice[j])
		{
			for(k=0 ; k<j; k++)
			{
				free(matrice[k]);
			}
			free(matrice);
		}
	}
	
	// citim matricea de pixeli

	fread(imagine,size,1,fp);
	
	fclose(fp);

	// punem in matricea auxiliara x unde avem pixel colorat si . daca pixelul e alb
	// retinem in matrice imaginea de la dreapta la stanga

	for(j=i.lungime -1 ; j >= 0; j--)
	{
		for(k=i.latime-1; k >= 0; k--)
		{
			if( (l-c)% (3*i.latime)==0 && l!=0)
			{
				// sarim peste padding
	
				l=l+pad;
				c=c+pad;
			}

			if(imagine[l] == 255 && imagine[l+1] == 255 && imagine[l+2] == 255 )
			{
				matrice[j][k]='.';
			}
			else
			{
				matrice[j][k]='x';
			}			
			l=l+3;
		}
	}

	l=0;

	// parcurgem matricea auxiliara pe coloane
	// si scriem cifrele recunoscute in vectorul auxiliar

	for(j=0;j<i.latime;j++)
	{
		for(k=0; k < i.lungime-4;k++)
		{
			
			// daca am gasit un pixel colorat inseamna ca am gasit o cifra 
			// si cu ajutorul functiei numere o recunoastem si punem in locul cifrei pixeli albi
		
			if( matrice[k][j] == 'x' )
			{
				vect[l]=numere(matrice,k,j) ;
				l++;
				
			}

			// in cazul in care avem o cifra careia ii lipseste coltul din dreapta sus, 
			//cifra diferita de 1, 4 

			if( matrice[k][j+1] == 'x' ) 
			{	
				if (matrice[k+1][j]=='x' ) 
				{
					vect[l]=numere(matrice,k,j) ;
					l++;
				}
			
				if( matrice[k][j+4]=='x' && matrice[k][j+5]=='.' && matrice[k+2][j]=='x' )
				{
					vect[l]=numere(matrice,k,j) ;
					l++;
				}
			}
			
			// in cazul in care avem un 1 sau un 4 caruia ii lipseste coltul din dreapta sus

			if ( matrice[k+1][j] == 'x' )
			{
				if( (k+5) == i.lungime )
				{
					vect[l]=numere(matrice,k,j);
					l++;
				}

				else
				{
					if( matrice[k+5][j]=='.' && matrice[k+4][j]=='x' && matrice[k+1][j+2]=='.' )
					{
						vect[l]=numere(matrice,k,j);
						l++;
					}
				}	
			}
		}
	}
	
	// cream noul fisier 

	s[ strlen(s) -4] ='\0';
	strcat(s,"_bonus.txt");
	
	fp=fopen(s,"w");

	for(j=l-1;j>=0;j--)
	{
		// scriem in el numerele recunoscute, salvate in vector in ordine inversa
		
		fprintf(fp,"%d",vect[j]);
	}

	free(imagine);

	free(s);

	free(vect);

	for( j=0; j < i.lungime; j++)
	{
		free( matrice[j] );
	}
	free(matrice);

	return 0;
}


