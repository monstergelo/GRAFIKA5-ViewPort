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
	init_view(pl0, 1000, 700);
	init_window(pl0, 1000, 700);
	warna c = {255,255,255,255};

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
	usleep(10000);
	//refreshBuffer(pl0, pl1);

	// refreshBuffer(pl0, pl1);
	// prepareView();
	// loadView();
	// return 0;

	for(int ii=0; ii<5; ii++)
	{
		refreshBuffer(pl0, pl1);
		stretch_window(-120, -60);
		prepareView();
		loadView();
		usleep(10000);
	}


	//init_view(pl0, 400, 500);
	prepareView();
	loadView();
	usleep(200000);

//**game-loop***********************************************************************************
	// pthread_create(&thread0, NULL, preUpdate, NULL);
	for(int ii=0; ii<5; ii++)
	{
		shift_window(10, 0);
		prepareView();
		loadView();
		usleep(1000000);
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
