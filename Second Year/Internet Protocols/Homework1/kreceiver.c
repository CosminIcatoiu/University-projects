#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001
#define MAXL 250
#define time 5000

int main(int argc, char** argv) {

    msg t;
	msg * y;
	
	int nr = 0;

	int seq = -1; 

	unsigned short crc;

	char * buf = calloc(500,sizeof(char));

	char * data = calloc(MAXL,sizeof(char));

	int i = 0;
	
	init(HOST, PORT);

	//Astept primirea setarilor initiale pana cand primesc un pachet

	y = receive_message_timeout(time);

	while( y == NULL ){

		nr++;
		if( nr == 3 ){
			printf("Receiver-ul a intrerupt transmisia\n");
			return 0;
		}
		
		y=receive_message_timeout(time);
	}
	
	nr = 0;

	//Calculez crc-ul pentru pachetul curent

	crc = crc16_ccitt(y->payload,y->len);

	//Cat timp nu am primit un pachet corect sau am primit timeout trimit un 
	// nou NAK sau retrimit NAK-ul anterior . E posibil ca dupa un NAK sa primesc
	//un nou time_out si de aceea apare si conditia y == NULL in while

	while( y == NULL || crc != (unsigned char)y->payload[y->len+1] * 256 + (unsigned char)y->payload[y->len] ){

		nr ++;

		if( nr == 3){
			printf("S-a intrerupt transmisia de la receiver");
			return 0;
		}

		if(	y != NULL) {
			
			seq = (seq + 2)% 64;

			nr = 0;
			
			buf = create_payload('N',seq,data,0);
			
			memcpy(t.payload,buf,buf[1] + 2);
		}
			
		send_message(&t);

		y = receive_message_timeout(time);
		
		if( y != NULL )
			crc = crc16_ccitt(y->payload,y->len);

	}

	//Dupa ce am primit un pachet corect construiesc un pachet ACK si il trimit

	seq = seq +2;

	init_data DATA = initialize();

	data = create_initial_data(DATA);

	buf = create_payload('Y',seq,data,strlen(data));

	memcpy(t.payload,buf,buf[1] + 2);

	send_message(&t);

	//Incep primirea fisierelor

	while(1){

		//Astept un mesaj 

		y = receive_message_timeout(time);

		//Daca acesta nu a ajuns sau daca primesc mesajul anterior pentru ca 
		//ACK-ul trimis nu a ajuns, il retrimit

		while( y == NULL || (y->payload[2] + 1) % 64 == seq ){
		
			nr ++;
			if ( nr == 3 ){
				printf("Nu am putut trimite ACK\n");
				return 0;
			}
			send_message(&t);
			y = receive_message_timeout(time);
		}

		//Cand am primit un pachet cu numarul de secventa corect verific daca el a 
		// venit fara erori sau daca nu cumva am primit iar un time_out caz in
		//care trimit un nou NAK sau NAK-ul anterior

		while( y == NULL || crc != (unsigned char)y->payload[y->len+1] * 256 + (unsigned char)y->payload[y->len] ){

			nr ++;

			if( nr == 3){
				printf("S-a intrerupt transmisia de la receiver,%d\n",i);
				return 0;
			}

			if(	y != NULL) {
			
				seq = (seq + 2) % 64;

				nr = 0;
			
				buf = create_payload('N',seq,data,0);
			
				memcpy(t.payload,buf,buf[1] + 2);
			}
			
			send_message(&t);

			y = receive_message_timeout(time);
		
			if( y != NULL )
				crc = crc16_ccitt(y->payload,y->len);

		}

		//Daca am primit un pachet de tip B inseamna ca nu mai trebuie sa primesc
		// niciun fisier, trimit ACK si inchei transmisia

		if( y -> payload[3] == 'B'){

			seq = (seq + 2) % 64;
		
			buf = create_payload('Y',seq,data,0);

			memcpy(t.payload,buf,buf[1] + 2);

			send_message(&t);

			break;			
		}

		//Daca am primit un nume de fisier deschid noul fisier si trimit ACK-ul
		//pentru numele de fisier

		char * file = calloc(250,sizeof(char));

		strcat(file,"recv_");

		char * aux = calloc(250,sizeof(char));

		memcpy(aux, y->payload +4,y->len -4);

		strcat(file,aux);

		int fid = open(file,O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);

		seq = (seq + 2) % 64;

		nr = 0;
	
		memset(buf,0,256);

		buf = create_payload('Y',seq,data,0);

		memcpy(t.payload,buf,buf[1] + 2);

		send_message(&t);

		//Primesc fisierul

		while(1){
	
			i++;
			nr = 0;
			
			//Astept datele din fisier
			y = receive_message_timeout(time);

			//Daca nu primesc nimic sau daca primesc pachetul anterior retrimit
			//ACK-ul anterior pentru ca sender-ul sa stie ca am primit pachetul
			//anterior

			while( y == NULL || (y->payload[2] + 1) % 64 == seq ){
		
				nr ++;
				if ( nr == 3 ){
					printf("Nu am putut trimite ACK\n");
					return 0;
				}
				send_message(&t);
				y = receive_message_timeout(time);
			}
		
			crc = crc16_ccitt(y->payload,y->len);

			nr = 0;

			//Cand am primit un pachet cu numar de secventa corect , verific
			//din nou corectitudinea acestuia

			while( y == NULL || crc != (unsigned char)y->payload[y->len+1] * 256 + (unsigned char)y->payload[y->len] ){

				nr ++;

				if( nr == 3){
					printf("S-a intrerupt transmisia de la receiver,%d\n",i);
					return 0;
				}

				if(	y != NULL) {
			
					seq = (seq + 2) % 64;

					nr = 0;
			
					buf = create_payload('N',seq,data,0);
			
					memcpy(t.payload,buf,buf[1] + 2);
				}
			
				send_message(&t);

				y = receive_message_timeout(time);
		
				if( y != NULL )
					crc = crc16_ccitt(y->payload,y->len);

			} 

			//Dupa ce am primit un mesaj corect verific daca nu cumva am primit
			//mesajul de sfarsit de fisier, caz in care trimit un ACK si ies
			// din while

			if( y -> payload[3] == 'Z'){

				seq = (seq + 2) % 64;
		
				buf = create_payload('Y',seq,data,0);

				memcpy(t.payload,buf,buf[1] + 2);

				send_message(&t);

				break;			
			}

			//Daca am primit un pachet de tip data scriu in fisier ce trebuie
			//si apoi trimit un ACK
		
			memset(data,0,MAXL);

			memcpy(data, y->payload +4,y->len -4);

			write(fid,data,y->len-4);

			seq = (seq + 2 ) % 64;

			nr = 0;

			buf = create_payload('Y',seq,data,0);

			memcpy(t.payload,buf,buf[1] + 2);

			send_message(&t);
		}

		//La finalul transmisiei unui fisier, inchid fisierul deschis

		close(fid);
	}
	return 0;
}
