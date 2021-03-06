#ifndef GAMBAR_H
#define GAMBAR_H


// variabel statik global buffer_*
// tipe data titik, warna
#include "glob_var_type.h"


unsigned char buffer_r[4000][4000];
unsigned char buffer_g[4000][4000];
unsigned char buffer_b[4000][4000];
unsigned char buffer_a[4000][4000];

unsigned char viewport_r[4000][4000];
unsigned char viewport_g[4000][4000];
unsigned char viewport_b[4000][4000];
unsigned char viewport_a[4000][4000];

unsigned char window_r[4000][4000];
unsigned char window_g[4000][4000];
unsigned char window_b[4000][4000];
unsigned char window_a[4000][4000];


line worldLines[100];
int lastLine;

selectedBuffer view;
selectedBuffer window;


//mengembalikan titik dengan nilai x dan y sesuai argumen
titik setTitik(int x, int y);

// Melakukan assign warna c pada
// posisi c pada matriks framebuffer
void bufferDrawDot(titik p, warna c);

//memasukka warna pixel pada driver
void DrawDot(titik p, warna c);

// Melakukan assign warna default ke matriks
// buffer (bukan matriks framebuffer) berupa
// segi empat yang dibentuk oleh dua titik p0 dan p1
void refreshBuffer(titik p0, titik p1);

// Memuat/assign nilai dari matriks buffer
// ke matriks framebuffer.
void loadBuffer();

void bufferDrawPlaneSolid(titik* p, warna c, warna bound_c, int sisi);	//membuat bidang yang menyambungkan titik p[0] ke p[1], p[1] ke p[2], ...., p[n] ke p[0]
	                                                					//dengan warna solid

void bufferDrawPlaneSolidCitra(titik* citra, titik origin, warna fill, warna bound, int sisi); //membuat gambar dengan origin sebagai posisi

void fill(titik p, warna c, warna bound_c);	//melakukan pewarnaan flood denganp sebagai titik api


//================================================
void bufferDrawLine(titik p0, titik p1, warna c);	//mmengganti nilai pixel sehingga tergambar garis dari p0 ke p1
void bufferDrawPlane(titik* p, warna c, int sisi);			//membuat bidang yang menyambungkan titik p[0] ke p[1], p[1] ke p[2], ...., p[n] ke p[0]
//================================================
void bufferDrawCircle(titik p, int radius, warna c);	//membuat lingkaran dengan p sebagai pusat
int  dotDistance(titik p1, titik p2);		//mengembalikan jarak antara p1 dan p2
//================================================

void saveLine(titik p0, titik p1, warna c); //menambahkan garis ke worldLine

// membuat pesawat dengan xof sebagai ofside kiri, yof sebagai ofset atas
void drawPlane(int xof, int yof);

// membuat tank dengan xof sebagai ofside kiri, yof sebagai ofset atas
void drawTank(int xof, int yof);

titik getMidPoint(titik *citra, int sisi);

//view-stuff====================================================================

//inisialisasi atribut view
void init_view(titik p, int length_x, int length_y);

//menetralkan warna view
void refreshView();

//mengkopi buffer ke view sesuai atribut view dan window
void prepareView();

//me-load view ke layar
void loadView();

double getViewScaling(int wHeight, int wWidth, int vHeight, int vWidth);

double getViewScalingX(int wWidth, int vWidth);

double getViewScalingY(int wHeight, int vHeight);

//window-stuff==================================================================

//inisialisasi atribut window
void init_window(titik p, int length_x, int length_y);

//menggeser titik origin window
void shift_window(int x, int y);

//mengubah ukuran window
void stretch_window(int x, int y);
//worldLines-stuff==============================================================

//print WorldLine 0 - i
void printLines(int i);

//scale garis di WorldLines sebesar s
void resizeLines(titik p0, float s);
void resizeLinesX(titik p0, float s);
void resizeLinesY(titik p0, float s);

//drawLinebuffer seluruh WorldLines
void redrawLines();

//menjauhkan jarak p0 dan setiap p1 dengan menggeser 
//setiap p1 sehingga jarak membesar sebanyak skala
titik scaleDot(titik p0, titik p1, float s); 

titik scaleYDot(titik p0, titik p1, float s);

titik scaleXDot(titik p0, titik p1, float s);

//menjauhkan jarak p0 dan setiap p1 dengan menggeser 
//setiap p1 sehingga jarak membesar sebanyak skala
void scaleBanyakDot(titik p0, titik *p1, float s, int banyaktitik); 

#endif //GAMBAR_H
