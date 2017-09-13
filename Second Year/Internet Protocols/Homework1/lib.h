#ifndef LIB
#define LIB

#define MAXL 250
#define time 5000

typedef struct {
    int len;
    char payload[1400];
} msg;

typedef struct {

	char soh;
	unsigned char len;
	char seq;
	char type;
	char * data;
	short check;
	char mark;
} frame;

typedef struct {
	unsigned char maxl;
	unsigned char TIME;
	unsigned char npad;
	unsigned char padc;
	unsigned char eol;
	unsigned char qctl;
	unsigned char chkt;
	unsigned char rept;
	unsigned char capa;
	unsigned char r; 
} init_data;

init_data initialize(){

	init_data DATA;
	DATA.maxl=250;
	DATA.TIME=5;
	DATA.npad=0x00;
	DATA.padc=0x00;
	DATA.eol=0x0D;
	DATA.qctl=0x00;
	DATA.chkt=0x00;
	DATA.rept=0x00;
	DATA.capa=0x00;
	DATA.r=0x00;
	return DATA;
}

char * create_initial_data(init_data DATA){

	char * buf = calloc(sizeof(init_data),1);

	memcpy(buf,&DATA.maxl,1);
	
	memcpy(buf + 1, &DATA.TIME,1);
	
	memcpy(buf + 2, &DATA.npad,1);

	memcpy(buf + 3, &DATA.padc,1);
	
	memcpy(buf + 4, &DATA.eol,1);

	memcpy(buf + 5, &DATA.qctl,1);

	memcpy(buf + 6, &DATA.chkt,1);

	memcpy(buf + 7, &DATA.rept,1);

	memcpy(buf + 8, &DATA.capa,1);

	memcpy(buf + 9, &DATA.r,1);
	
	return buf;
}

frame create_frame(char type, char seq, char * data, int len){

	frame Frame;

	Frame.soh=0x01;

	Frame.mark=0x0D;

	Frame.type=type;

	Frame.seq=seq;

	Frame.len= len+5; 
	
	Frame.data = calloc(MAXL,sizeof(char));
	
	if( len != 0)
		memcpy(Frame.data,data,len);

	Frame.check=0x00;

	return Frame;
}

char * create_payload(char type, char seq, char * data, int len){

	frame Frame = create_frame(type,seq,data,len);
	
	char * payload = calloc(256,sizeof(char));

	memcpy(payload,&Frame.soh,1);

	memcpy(payload + 1, &Frame.len,1);
	
	memcpy(payload + 2, &Frame.seq,1);
	
	memcpy(payload + 3, &Frame.type,1);

	if( len != 0 )
		memcpy(payload + 4, Frame.data,len);

	memcpy(payload + 4 + len,&Frame.check,2);
	
	memcpy(payload + 6 + len,&Frame.mark,1);

	return payload;
}	

void init(char* remote, int remote_port);
void set_local_port(int port);
void set_remote(char* ip, int port);
int send_message(const msg* m);
int recv_message(msg* r);
msg* receive_message_timeout(int timeout); //timeout in milliseconds
unsigned short crc16_ccitt(const void *buf, int len);

#endif

