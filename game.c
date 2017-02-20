#include "gambar.h"
#include "skala.h"
#include "framebuffer_init.h"
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

titik pl0 = {VIEW_X_START, VIEW_Y_START};
titik pl1 = {VIEW_X_END, VIEW_Y_END};
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

  printf("JUST CREATED A THREAD\n");
  pthread_create(&thread0, NULL, preUpdate, NULL);

  while (1) {

  }

//**garbaging***********************************************************************************
	//pthread_join(thread0, NULL);
	garbage_fb();
  fflush(stdout);
  fprintf(stderr, "%s.\n", strerror(errno));
	return 0;
}

void *preUpdate() {
    titik midPoint = {1366/2, 700/2};
    while(1) {
    // get stored value on keyboard device reference file
      n = read(fd, &ev, sizeof ev);
      // check if no stored value on device file
      if (n == (ssize_t)-1) {

      }

      // if keystroke is stored on keyboard device reference file
      if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
          if(ev.value == 1) { // when it pressed, 0 is released
              switch(ev.code) {
                  case 44: // Z
                      resizeLines(midPoint, 1.2);
                      break;
                  case 45: // X
                      resizeLines(midPoint, 0.8);
                      break;
                  case 105: // left
                      moveLines(-20, 0);
                      break;
                  case 106: // right
                      moveLines(20, 0);
                      break;
                  case 103: // up
                      moveLines(0, -20);
                      break;
                  case 108: // down
                      moveLines(0, 20);
                      break;
                  default:
                      break;

              }
              printf("%d\n", ev.code);
              if (ev.code == 44 || ev.code == 45 || ev.code == 103 || ev.code == 105 || ev.code == 106 || ev.code == 108) {
                refreshBuffer(pl0, pl1);
                redrawLines();
                loadBuffer();
              }
              keypress = 1;
          }

          if(ev.value == 0){
            keypress = 0;
          }
      }
    }
}

void updatePosisi(){

}

void postUpdate(){

}
