#ifndef GLOB_VAR_TYPE_H
#define GLOB_VAR_TYPE_H

#define GLOBAL_LAYAR_X 1366
#define GLOBAL_LAYAR_Y 700

typedef struct{
    int r,g,b,a;
} warna;

typedef struct{
	int x;
	int y;
} titik;

typedef struct{
	titik p0;
	titik p1;
	warna c;
} line;

typedef struct{
	titik origin;
	int length_x;
	int length_y;
} selectedBuffer;

extern selectedBuffer view;
extern selectedBuffer window;

extern line worldLines[100];

extern unsigned char buffer_r[4000][4000];
extern unsigned char buffer_g[4000][4000];
extern unsigned char buffer_b[4000][4000];
extern unsigned char buffer_a[4000][4000];

extern unsigned char viewport_r[4000][4000];
extern unsigned char viewport_g[4000][4000];
extern unsigned char viewport_b[4000][4000];
extern unsigned char viewport_a[4000][4000];

extern unsigned char window_r[4000][4000];
extern unsigned char window_g[4000][4000];
extern unsigned char window_b[4000][4000];
extern unsigned char window_a[4000][4000];

#endif //GLOB_VAR_TYPE_H