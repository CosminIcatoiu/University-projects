#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <map>
#include <netdb.h>
#define BUFLEN 15000

using namespace std;

// Comparatorul pentru url-urile introduse in mapa
struct cmp_str
{
   bool operator()(char const *a, char const *b)
   {
      return strcmp(a, b) < 0;
   }
};

// Mapa ce va face o legatura intre url-uri si fisierele lor de pe disk
map<char *,char *,cmp_str> files;

//Functie ce primeste un host ca parametru si intoarce adresa lui IP subforma
//de string
char * by_name(char* name) {
    struct hostent* host = gethostbyname(name);
   
    if (host == NULL) {
        printf("Adresa url invalida\n");
        return NULL;
    }

    struct in_addr **adr = (struct in_addr**) host->h_addr_list;

    return(inet_ntoa(*adr[0]));
}

//Functie ce parseaza input-ul si obtine url-ul paginii pentru ca
//acesta sa fie introdus in mapa
char * get_url(char * buf){

	char *p, * q;
	char * copy = (char *)calloc(15000,sizeof(char));
	char * url = (char *)calloc(1500,sizeof(char));
	char * line = (char *)calloc(15000,sizeof(char));

	strcpy(copy,buf);

	//Pe prima linie 
	p = strtok(copy,"\n");

	strcpy(line,p);

	//Ne uitam daca avem hostname-ul acolo
	q=strtok(line," ");
	q=strtok(NULL," ");

	//Daca este pe prima linie
	if(q[0] !='/' && q[0] != 'H'){

		// Il copiem si il returnam
		strcpy(url,q);

		return url;
	} else {
		
		//Altfel, ne uitam pe a doua linie si il returnam
		strcpy(copy,buf);
		p = strtok(copy,"\n");
		p = strtok(NULL,"\n");

		q = strtok(line," ");
		q = strtok(NULL," ");

		strcpy(url,q);

		return url;
	}
}

//O functie ce parseaza input-ul si intoarce hostname-ul si portul
pair<char *, int> parse(char * buf) {

	char * p, * q;
	char * copy = (char *)calloc(15000,sizeof(char));
	char * line = (char *)calloc(15000,sizeof(char));
	char * host = (char *)calloc(1000,sizeof(char));
	char * port = (char *)calloc(100,sizeof(char));
	int po;

	//Verificam pe prima linie
	strcpy(copy,buf);
	p = strtok(copy,"\n");
	strcpy(line,p);

	//URL-ul ar trebui sa fie dupa primul spatiu
	q = strtok(line," ");
	q = strtok(NULL," ");
	
	//Daca se afla pe prima linie
	if(q[0] != '/' && q[0] != 'H') {
		strcpy(host,q);

		unsigned int i = 0;
		int ok = 0;
		
		//Eliminam calea si pastram doar hostname-ul

		while(i < strlen(host)) {
			if(host[i] == '/' && ok == 1)
				break;
			if(host[i] == '.')
				ok = 1;
			i++;
		}

		host[i]='\0';

		i = 0;

		ok = 0;

		//Verificam daca este dat portul
		while(i < strlen(host)) {
			if(host[i] == ':' && ok == 1)
				break;
			if(host[i] == '.')
				ok = 1;
			i++;
		}
		
		//Daca este dat il convertim si apoi il stergem din host

		if(i != strlen(host)){
			strcpy(port,host+i+1);
			po = atoi(port);
			host[i]='\0';
		} else {
			po = 80;
		}

		//Returnam perechea obtinuta
		return make_pair(host,po);

	} else {
		
		//Ne uitam pe a doua linie, unde trebuie sa fie campul Host:
		strcpy(copy,buf);
		p = strtok(copy,"\n");
		p = strtok(NULL,"\n");

		strcpy(line,p);

		//URL-ul este sigur dupa primul spatiu
		q = strtok(line," ");
		q = strtok(NULL," ");

		strcpy(host,q);
		unsigned int i = 0;

		int ok = 0;

		//Eliminam calea si pastram doar hostname-ul

		while(i < strlen(host)) {
			if(host[i] == '/' && ok == 1)
				break;
			if(host[i] == '.')
				ok = 1;
			i++;
		}

		host[i]='\0';

		i = 0;

		ok = 0;

		//Verificam daca am primit si portul

		while(i < strlen(host)) {
			if(host[i] == ':' && ok == 1)
				break;
			if(host[i] == '.')
				ok = 1;
			i++;
		}
		
		//Daca da, il convertim si il stergem din host

		if(i != strlen(host)){
			strcpy(port,host+i+1);
			po = atoi(port);
			host[i] = '\0';
		} else {
			po = 80;
		}

		//Returnam perechea obtinuta
		return make_pair(host,po);
	}
}


int main(int argc,char ** argv) {

	int sd_tcp,sd_aux,new_sd,fisier = 0,fdmax,i,rw,sent;
	struct sockaddr_in addr_tcp, new_addr,addr_cli;
	fd_set read_fs,temp_fs;
	char buf[BUFLEN];
	char * nume_fisier = (char *)calloc(1500,sizeof(char));

	//Deschidem un socket tcp pe care vom astepta conexiuni cu browsere

	sd_tcp = socket(PF_INET,SOCK_STREAM,0);

	//Cream legatura TCP

	addr_tcp.sin_family = AF_INET;
	addr_tcp.sin_addr.s_addr = INADDR_ANY;
	addr_tcp.sin_port = htons(atoi(argv[1]));

	//Facem bind pe canalul TCP

	if (bind(sd_tcp, (struct sockaddr *) &addr_tcp, sizeof(addr_tcp)) < 0) {
        printf("Eroare la apel bind\n");
		return 0;
	}

	//Facem socket-ul TCP sa astepte conexiuni 

	listen(sd_tcp,100);

	//Initializam seturile de descriptori cu socket-ul tcp 

	FD_ZERO(&read_fs);
	FD_ZERO(&temp_fs);
	FD_SET(0,&read_fs);
	FD_SET(sd_tcp,&read_fs);

	fdmax = sd_tcp;

	while(1) {
		temp_fs = read_fs;
		
		if(select(fdmax+1,&temp_fs,NULL,NULL,NULL) == -1) {
			printf("Eroare la apel select\n");
		}

		for(i = 0; i <= fdmax; i++) {

			//Pentru fiecare numar posibil al unui socket, daca este in setul de socketi

			if(FD_ISSET(i,&temp_fs)) {
				
				//Daca este chiar socket-ul tcp acceptam un nou client si il introducem
				//in set-ul de socketi.

				if( i == sd_tcp ) {
					socklen_t len = sizeof(addr_cli);
					new_sd = accept(sd_tcp, (struct sockaddr *)&addr_cli, &len);

					if(new_sd == -1) {
						printf("Eroare la apel accept\n");
					} else {
						FD_SET(new_sd,&read_fs);

						//Updatam numarul maxim al unui socket

						if( new_sd > fdmax ) {
							fdmax = new_sd;
						}
					}
				
					break;

				} else {

					//Daca am primit un request de la un browser

					memset(buf,0,BUFLEN);
					
					rw = recv(i, buf, BUFLEN, 0);

					//Parsam request-ul pentru a obtine hostname-ul, portul si url-ul
					pair<char *,int> aux = parse(buf);

					char * url = (char *)calloc(1500,sizeof(char));

					url = get_url(buf);

					//Verificam daca am mai avut vreo cerere pentru acest url

					if(files.find(url) == files.end()) {
					
						//Daca nu am mai avut, cream un nou socket
						sd_aux = socket(PF_INET,SOCK_STREAM,0);

						//Aflam ip-ul corespunzator hosname-ului

						char * ip = (char *)calloc(1500,sizeof(char));

						if(strstr(aux.first,"http://") == NULL)
							ip = by_name(aux.first);
						else
							ip = by_name(aux.first+7);

						//Si cream noua conexiune TCP cu serverul de la care vom primi pagina

						new_addr.sin_family = AF_INET;
						new_addr.sin_port = htons(aux.second);
						inet_aton(ip, &new_addr.sin_addr);

						//Ne conectam la acel server
						if(connect(sd_aux,(struct sockaddr *) &new_addr, sizeof(new_addr)) < 0) {
							printf("Eroare la apel connect\n");
						}

						//Si ii trimitem cererea primita
						sent = send(sd_aux, buf, rw, 0);
						
						if(sent < 0){
							cout << "Eroare la functia send" << endl;
						}

						//Verificam daca trebuie sau nu sa salvam cererea in cache

						if(strstr(buf,"no-cache") != NULL || strstr(buf,"private") != NULL || strstr(buf,"POST") != NULL){

							//Daca nu trebuie, pur si simplu trimitem inapoi la client ce primim de la server

							while(1){
								memset(buf,0,BUFLEN);

								rw = recv(sd_aux, buf, BUFLEN, 0);
								if(rw <= 0)
									break;
								sent = send(i,buf,rw,0);

								if(sent < 0){
									cout << "Eroare la functia send" << endl;
								}
							}
						} else {

							//Altfel, cream numele unui nou fisier

							memset(nume_fisier,0,1500);
							
							strcat(nume_fisier,"fisier");
							
							char * index = (char *)calloc(1500,sizeof(char));
							
							sprintf(index,"%d",fisier);
							
							strcat(nume_fisier,index);
							
							fisier ++;

							//Inseram noua pereche url-fisier in mapa
							files.insert(make_pair(url,nume_fisier));

							//Si deschidem fisierul pentru a scrie in el
							int id = open(nume_fisier,O_WRONLY | O_CREAT, 0640);

							//Procedam ca mai sus, doar ca acum scriem si in fisier raspunsul de la server
							while(1){
								memset(buf,0,BUFLEN);

								rw = recv(sd_aux, buf, BUFLEN, 0);
								if(rw <= 0)
									break;
								write(id,buf,rw);
								sent = send(i,buf,rw,0);

								if(sent < 0){
									cout << "Eroare la functia send" << endl;
								}
							}

							//Inchidem fisierul

							close(id);
						}

						//Inchidem socketul catre serverul de la care am primit pagina
						close(sd_aux);
					} else {

						//Deschidem fisierul corespunzator acelui URL

						int f = open((*files.find(url)).second,O_RDONLY);
						memset(buf,0,BUFLEN);

						//Citim din el si trimitem inapoi browserului pagina pana cand am trimis-o pe toata
						while((rw = read(f,buf,sizeof(buf))) > 0){
							sent = send(i,buf,rw,0);
							if(sent < 0){
								cout << "Eroare la functia send" << endl;
							}
							
							memset(buf,0,BUFLEN);
						}

						//Inchidem fisierul
						close(f);

					}

					//La final inchidem socket-ul si il stergem din setul de descriptori
					FD_CLR(i,&read_fs);
					close(i);
				}
			}
		}
	}

	return 0;
}