#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000
#define MAXL 250
#define time 5000

int main(int argc, char** argv) {
    msg t;
	msg * y;
	
	int nr = 0;

    init(HOST, PORT);

	char seq = 0;

	char * data = calloc(MAXL,sizeof(char));

    char * buf ;

	unsigned short crc;
	
	int j;

	//Pregatesc trimiterea pachetului initial

	init_data DATA = initialize();

	data = create_initial_data(DATA);

	buf = create_payload('S',seq,data,strlen(data));

	memcpy(t.payload,buf,(unsigned char)buf[1]+2);

	crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);

	t.len = (unsigned char)buf[1]-1;

	t.payload[t.len + 1]=crc/256;
	t.payload[t.len] = crc - buf[t.len + 1]*256;

	//Trimit pachetul initial

	send_message(&t);

	//Astept un raspuns

	y = receive_message_timeout(time);

	//Cat timp nu am primit un raspuns sau am primit un NAK retrimit mesajul
	//cu sau fara numarul de secventa si crc-ul schimbat
	
	while( y == NULL || y->payload[3] == 'N'){
		
		nr++;

		if( nr == 3){
			printf("S-a intrerupt transmisia\n");
			return 0;
		}

		if(y != NULL){
						
			nr = 0;

			seq = (seq +2) % 64;

			t.payload[2] = seq;

			crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);

			t.payload[t.len + 1] = crc/256;
			t.payload[t.len] = crc - buf[t.len + 1]*256;
		}

		send_message(&t);

		y = receive_message_timeout(time);
	}

	//Dupa ce am primit ACK pentru setari pregatesc trimiterea fisierelor.Astfel,
	//pentru fiecare fisier pe care il primesc ca parametru

	for(j = 1; j < argc ; j++){

		//Pregatesc trimiterea numelui 

		seq=(seq + 2) % 64;

		buf = create_payload('F',seq,argv[j],strlen(argv[j]));

		memcpy(t.payload,buf,(unsigned char)buf[1]+2);

		crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);

		t.len = (unsigned char)buf[1]-1;

		t.payload[t.len + 1]=crc/256;
		t.payload[t.len] = crc - buf[t.len + 1]*256;

		//Il trimit si astept sa vad ce primesc

		send_message(&t);
	
		y = receive_message_timeout(time);

		//Daca nu primesc un mesaj sau primesc un NAK sau primesc un ACK anterior
		//retrimit pachetul precedent tinand cont de schimbarile ce trebuie facute

		while( y == NULL || y->payload[3] == 'N' || (y->payload[2]+1) % 64 == seq){
		
			if( y == NULL)
				nr++;
			
			if(nr == 3){
				printf("S-a intrerupt transmisia aici\n");
				return 0;
			}

			if( y != NULL && y->payload[3] == 'N'){
			
				nr = 0;
				
				if( (y->payload[2] +1) % 64 != seq )
					seq = (seq +2) %64;

				t.payload[2] = seq;

				crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);

				t.payload[t.len + 1] = crc/256;
				t.payload[t.len] = crc - buf[t.len + 1]*256;
			}

			send_message(&t);	

			y = receive_message_timeout(time);
		}

		//Dupa ce am trimis numele de fisier, deschid fisierul si incep trimiterea
		//datelor

		int fid = open(argv[j],O_RDONLY);

		while(1){

			//Pregatesc citirea din fisier

			nr = 0;

			memset(data,0,MAXL);

			int ok = read(fid,data,MAXL);

			//Daca am ajuns la sfarsitul fisierului

			if( ok <= 0){

				//Pregatesc pachetul ce semnifica sfarsitul de fisier si il trimit
				//pana cand primesc ACK-ul pentru el, moment in care ies din while
			
				seq = (seq +2) % 64;

				memset(buf,0,256);

				buf = create_payload('Z',seq,data,0);
			
				memcpy(t.payload,buf,(unsigned char)buf[1]+2);

				crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);
			
				t.len = (unsigned char)buf[1]-1;

				t.payload[t.len + 1]=crc/256;
				t.payload[t.len] = crc - buf[t.len + 1]*256;

				send_message(&t);

				y = receive_message_timeout(time);
	
				nr = 0;

				while( y == NULL || y->payload[3] == 'N' || (y->payload[2] +1) % 64 == seq ){
				
					if( y == NULL)
						nr++;
					if(nr == 3){
						printf("S-a intrerupt transmisia aici\n");
						return 0;
					}

					if(y != NULL && y->payload[3] == 'N'){
			
						nr = 0;

						if( (y->payload[2] +1) % 64 != seq )
							seq = (seq + 2) % 64;

						t.payload[2] = seq;

						crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);

						t.payload[t.len + 1] = crc/256;
						t.payload[t.len] = crc - buf[t.len + 1]*256;
					}
					send_message(&t);	

					y = receive_message_timeout(time);
				}
				break;
			}

			//Daca am reusit sa citesc din fisier pregatesc pachetul pentru trimitere
			
			seq = (seq +2) % 64;
		
			memset(buf,0,256);

			buf = create_payload('D',seq,data,ok);
	
			memcpy(t.payload,buf,(unsigned char)buf[1]+2);

			crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);

			t.len = (unsigned char)buf[1]-1;
			
			t.payload[t.len + 1]=crc/256;
			t.payload[t.len] = crc - buf[t.len + 1]*256;

			send_message(&t);

			y = receive_message_timeout(time);
	
			nr = 0;

			//Retrimit pachetul anterior pana cand primesc un ACK sau pana cand
			// am primit 3 time_out-uri la rand caz in care intrerup transmisia

			while( y == NULL || y->payload[3] == 'N' || (y->payload[2]+1) % 64 == seq ){
		
				if( y == NULL)
					nr++;
			
				if(nr == 3){
					printf("S-a intrerupt transmisia aici\n");
					return 0;
				}

				if( y != NULL && y->payload[3] == 'N'){
			
					nr = 0;
				
					if( (y->payload[2] +1) % 64 != seq )
						seq = (seq +2) %64;

					t.payload[2] = seq;

					crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);

					t.payload[t.len + 1] = crc/256;
					t.payload[t.len] = crc - buf[t.len + 1]*256;
				}

				send_message(&t);	

				y = receive_message_timeout(time);
			}
		}

		//Dupa fiecare fisier inchid fisierul respectiv

		close(fid);
	}
	
	//La finalul transmisiei trimit un pachet de tip B pana cand acesta ajunge
	//la receptor si dupa ce am primit un ACK inchid transmisiunea.

	seq = (seq +2) % 64;

	memset(buf,0,256);

	memset(data,0,MAXL);

	buf = create_payload('B',seq,data,0);
			
	memcpy(t.payload,buf,(unsigned char)buf[1]+2);

	crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);
			
	t.len = (unsigned char)buf[1]-1;

	t.payload[t.len + 1]=crc/256;
	t.payload[t.len] = crc - buf[t.len + 1]*256;

	send_message(&t);

	y = receive_message_timeout(time);
	
	nr = 0;

	while( y == NULL || y->payload[3] == 'N' || (y->payload[2] +1) % 64 == seq ){
				
		if( y == NULL)
			nr++;
		if(nr == 3){
			printf("S-a intrerupt transmisia aici\n");
			return 0;
		}

		if(y != NULL && y->payload[3] == 'N'){
			
			nr = 0;

			if( (y->payload[2] +1) % 64 != seq )
				seq = (seq + 2) % 64;

				t.payload[2] = seq;

				crc = crc16_ccitt(t.payload,(unsigned char)t.payload[1]-1);

				t.payload[t.len + 1] = crc/256;
				t.payload[t.len] = crc - buf[t.len + 1]*256;
		}
		send_message(&t);	

		y = receive_message_timeout(time);
	}

    return 0;
}
