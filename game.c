#include "gambar.h"
#include "skala.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

void drawObjects();		//menggambar tembakan dan objekTabrak ke buffer
void *preUpdate();		//(1)cek inputuser
void updatePosisi();	//(1)ubah posisi. (2)spawnObjek, (3)drawBuffer
void postUpdate();	 	//(1)cek kolisi, (2)loadbuffer ke layar

titik pl0 = {0,0};
titik pl1 = {1366,700};
pthread_t thread0; 		//thread input capture
int fd; 				//something-something keylogger
struct input_event ev;	//something-something keylogger
ssize_t n;
int user_input = -99;
int keypress = 0;
titik p0 = {100,350};
titik p1 = {600,650};
titik p2 = {300,650};
titik p3 = {500,650};
titik p4 = {600, 650};
titik p5 = {0,0};
titik p6 = {760,2};
titik p7 = {0,600};
titik p8 = {1000,700};
titik pv = {1366/2, 700/2};

int main(){
//**setup-pendengar-keyboard********************************************************************
	// Input keyboard device file
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    const char *dev = "/dev/input/event3";
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    // Open device for reference
    fd = open(dev, O_RDONLY);

    // Check if device is opened
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

//**setup-objek-game****************************************************************************
	init_fb();
	init_view(pv, 400, 400);
	init_window(pl0, 400, 400);
	warna c = {255,255,255,255};
	warna c0 = {255,255,255,255};
	c0.r += 30;
    c0.g += 30;
    c0.b += 30;

	titik pt[3];
	pt[0] = pl0;
	pt[1] = p0;
	pt[2] = p1;

	for(int in=0; in<10; in++)
	{

	}

	refreshBuffer(pl0,pl1);
	bufferDrawLine(p1, p2, c);
	bufferDrawLine(p5, p4, c);
	bufferDrawLine(p8, p3, c);
	bufferDrawLine(p6, p4, c);
	bufferDrawLine(p2, p5, c);
	bufferDrawLine(p1, p6, c);
	bufferDrawLine(p6, p7, c);
	bufferDrawLine(p2, p5, c);
	bufferDrawLine(p5, p7, c);
	bufferDrawLine(p1, p8, c);
	loadBuffer();
	prepareView();
	usleep(1500000);
	loadView();

	printf("wawawa\n");
	usleep(3000000);
	printf("wiwiwi\n");

	titik bidang[8];
	bidang[0] = p1;
	bidang[1] = p2;
	bidang[2] = p3;
	bidang[3] = p4;
	bidang[4] = p5;
	bidang[5] = p6;
	bidang[6] = p7;
	bidang[7] = p8;
	
	titik tengah = {1366/2, 700/2};
	scaleBanyakDot(tengah, bidang, 1.5, 8);

	refreshBuffer(pl0,pl1);
	bufferDrawLine(bidang[0], bidang[1], c);
	bufferDrawLine(bidang[4], bidang[3], c);
	bufferDrawLine(bidang[7], bidang[2], c);
	bufferDrawLine(bidang[5], bidang[3], c);
	bufferDrawLine(bidang[1], bidang[4], c);
	bufferDrawLine(bidang[0], bidang[5], c);
	bufferDrawLine(bidang[5], bidang[6], c);
	bufferDrawLine(bidang[1], bidang[4], c);
	bufferDrawLine(bidang[4], bidang[6], c);
	bufferDrawLine(bidang[0], bidang[7], c);
	loadBuffer();
	prepareView();
	usleep(1500000);
	loadView();


//**game-loop***********************************************************************************
	pthread_create(&thread0, NULL, preUpdate, NULL);
	while(1)
	{

	}

//**garbaging***********************************************************************************
	//pthread_join(thread0, NULL);
	garbage_fb();
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
	return 0;
}



void *preUpdate(){
	
}

void updatePosisi(){
	
}

void postUpdate(){
	
}
