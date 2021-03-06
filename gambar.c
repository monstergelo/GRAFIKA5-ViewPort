// global_* dan GLOBAL_*
#include "framebuffer_init.h"

// deklarasi fungsi
#include "gambar.h"
#include <stdio.h>
#include <math.h>

warna cRed ={255,25,25,255};
warna cGreen = {25,255,25,255};
warna cBlue = {25,25,255,255};

titik setTitik(int x, int y){
    titik temp = {x, y};
    return temp;
}

//mengganti nilai pixel dengan posisi p pada buffer dengan warna c
void DrawDot(titik p, warna c){
    if((p.x < 1) || (p.x >= GLOBAL_LAYAR_X) || (p.y < 1) || (p.y >= GLOBAL_LAYAR_Y)){
		return ;
	}

    long int position = (p.x + global_vinfo.xoffset) * (global_vinfo.bits_per_pixel / 8) +
       (p.y + global_vinfo.yoffset) * global_finfo.line_length;

    if(global_vinfo.bits_per_pixel == 32){
        *(global_fbp + position) = c.b;
        *(global_fbp + position + 1) = c.g;
        *(global_fbp + position + 2) = c.r;
        *(global_fbp + position + 3) = c.a;
    }else{
        // assume 16 bit color
        int b = c.b;
        int g = c.g;
        int r = c.r;
        unsigned short int t = r<<11 | g << 5 | b;
        *((unsigned short int*)(global_fbp + position)) = t;
    }
}

void bufferDrawDot(titik p, warna c){
    if((p.x < 1) || (p.x >= GLOBAL_LAYAR_X) || (p.y < 1) || (p.y >= GLOBAL_LAYAR_Y)){
		return ;
	}

    buffer_b[p.x][p.y] = c.b;
    buffer_g[p.x][p.y] = c.g;
    buffer_r[p.x][p.y] = c.r;
    buffer_a[p.x][p.y] = c.a;
}

titik getMidPoint(titik *citra, int sisi) {
  titik ans;
  int i = 0, midx = 0, midy = 0;
  for (i = 0; i < sisi; i++) {
    midx += citra[i].x;
    midy += citra[i].y;
  }
  midx /= sisi; midy /= sisi;
  ans.x = midx; ans.y = midy;
  return ans;
}
//mengganti nilai seluruh pixel buffer menjadi background color untuk
void refreshBuffer(titik p0, titik p1){
    warna warna_default = {25, 25, 255, 255};

    //
    //       *1
    // *0
    //
    int i, j;
    if(p0.x < p1.x && p0.y < p1.y){
        for(i = p0.x; i < p1.x; i++)
            for(j = p0.y; j < p1.y; j++){
                buffer_r[i][j] = warna_default.r;
                buffer_g[i][j] = warna_default.g;
                buffer_b[i][j] = warna_default.b;
                buffer_a[i][j] = warna_default.a;
            }

        return;
    }


    //
    // *1
    //       *0
    //
    if(p0.x > p1.x && p0.y < p1.y){
        for(i = p1.x; i < p0.x; i++)
            for(j = p0.y; j < p1.y; j++){
                buffer_r[i][j] = warna_default.r;
                buffer_g[i][j] = warna_default.g;
                buffer_b[i][j] = warna_default.b;
                buffer_a[i][j] = warna_default.a;
            }

        return;
    }

    //
    //       *0
    // *1
    //
    if(p0.x > p1.x && p0.y > p1.y){
        for(i = p1.x; i < p0.x; i++)
            for(j = p1.y; j < p0.y; j++){
                buffer_r[i][j] = warna_default.r;
                buffer_g[i][j] = warna_default.g;
                buffer_b[i][j] = warna_default.b;
                buffer_a[i][j] = warna_default.a;
            }

        return;
    }

    //
    // *0
    //       *1
    //
    if(p0.x < p1.x && p0.y > p1.y){
        for(i = p0.x; i < p1.x; i++)
            for(j = p1.y; j < p0.y; j++){
                buffer_r[i][j] = warna_default.r;
                buffer_g[i][j] = warna_default.g;
                buffer_b[i][j] = warna_default.b;
                buffer_a[i][j] = warna_default.a;
            }

        return;
    }
}

//memasukkan nilai buffer ke driver
void loadBuffer(){
    int i, j;

    titik titik_sementara;
    warna warna_sementara;
    warna warna_kosong = {0, 0, 0, 0};
    for(i = 0; i < GLOBAL_LAYAR_X; i++)
        for(j = 0; j < GLOBAL_LAYAR_Y; j++){
            titik_sementara.x = i;
            titik_sementara.y = j;

            if(buffer_r[i][j] && buffer_g[i][j] &&
            buffer_b[i][j] && buffer_a[i][j]){
                warna_sementara.r = buffer_r[i][j];
                warna_sementara.g = buffer_g[i][j];
                warna_sementara.b = buffer_b[i][j];
                warna_sementara.a = buffer_a[i][j];
            }else{
                warna_sementara = warna_kosong;
            }

            DrawDot(titik_sementara, warna_sementara);
        }
}

void bufferDrawPlane(titik* p, warna c, int sisi){
	int i= 0;

	for (i = 0; i < sisi-1; i++) {
		bufferDrawLine(p[i], p[i+1], c);
	}


	bufferDrawLine(p[i], p[0], c);
}



void bufferDrawCircle(titik p, int radius, warna c){
    inline void bufferDrawHorizontalLine(int x1, int x2, int y, warna c)
    {
        int i; titik l;
        for (i = x1; i < x2 ; i++){
            l.x = i; l.y = y;
            bufferDrawDot(l, c);
        }
    }
    inline void plot4poin(titik p1, int x, int y, warna c)
    {
        /*
        //Lingkaran kosong
        int a = p1.x+ x;
        int b = p1.x- x;
        int d = p1.y +y;
        int e = p1.y -y;
        titik pa = {a,d};
        titik pb = {b,d};
        titik pc = {a,e};
        titik pd = {b,e};
        bufferDrawDot(pa,c);
        bufferDrawDot(pb,c);
        bufferDrawDot(pc,c);
        bufferDrawDot(pd,c); */

       // Lingkaran berisi
        bufferDrawHorizontalLine(p1.x - x, p1.x + x, p1.y + y,c);
        bufferDrawHorizontalLine(p1.x - x, p1.x + x, p1.y - y,c);
    }

    inline void plot8poin(titik p1, int x, int y, warna c)
    {
        plot4poin(p1, x, y, c);
        plot4poin(p1, y, x, c);
    }


    int error = -radius;
    int x = radius;
    int y = 0;

    while (x >= y)
    {
        plot8poin(p, x, y, c);

        error += y;
        y++;
        error += y;

        if (error >= 0)
        {
            error += -x;
            x--;
            error += -x;
        }
    }
}

int dotDistance(titik p1, titik p2){
    double hasil;
    hasil = sqrt(((p2.x-p1.x)*(p2.x-p1.x))+((p2.y-p1.y)*(p2.y-p1.y)));
    return hasil;
}

int is_color(titik p, warna c) {
  if ((p.x < 1) || (p.x >= GLOBAL_LAYAR_X) || (p.y < 1) || (p.y >= GLOBAL_LAYAR_Y)){
      return 1;
  }

	return buffer_r[p.x][p.y] == c.r && buffer_g[p.x][p.y] == c.g
	&& buffer_b[p.x][p.y] == c.b && buffer_a[p.x][p.y] == c.a;
}

void bufferDrawPlaneSolid(titik* p, warna c, warna bound_c, int sisi) {
	int i, x_mid = 0, y_mid = 0;
	titik flare_point;
	bufferDrawPlane(p, bound_c, sisi);
	for (i = 0; i < sisi; i++) {
		x_mid += p[i].x;
		y_mid += p[i].y;
	}
	flare_point.x = x_mid / sisi;
	flare_point.y = y_mid / sisi;
	fill(flare_point, c, bound_c);
}

void fill(titik p, warna c, warna bound_c) {
	if (!is_color(p, c) && !is_color(p, bound_c)) {
		bufferDrawDot(p, c);
		titik new_p = {p.x, p.y+1};
		fill(new_p, c, bound_c);
		new_p.x = p.x-1; new_p.y = p.y;
		fill(new_p, c, bound_c);
		new_p.x = p.x+1; new_p.y = p.y;
		fill(new_p, c, bound_c);
		new_p.x = p.x; new_p.y = p.y-1;
		fill(new_p, c, bound_c);
	}
}

void drawPlane(int xof, int yof) {
    titik ekorPesawatAtas[] = {{xof,yof+25}, {xof,yof+50}, {xof+25,yof+45}, {xof+15,yof+25}};
    titik ekorPesawatBawah[] = {{xof,yof+50}, {xof+15,yof+70}, {xof+90,yof+70}, {xof+90,yof+45}, {xof+25,yof+45}};
    titik badanPesawat[] = {{xof+90,yof+45}, {xof+190,yof+45}, {xof+190,yof+70}, {xof+90, yof+70}};
    titik sayapAtas[] = {{xof+70,yof}, {xof+85,yof}, {xof+105, yof+45}, {xof+80,yof+45}};
    titik sayapBawah[] = {{xof+70,yof+70}, {xof+95,yof+70}, {xof+80, yof+120}, {xof+55, yof+120}};
    titik kepalaPesawat[] = {{xof+190,yof+45}, {xof+220,yof+50}, {xof+225, yof+70}, {xof+190, yof+70}};
    titik pMulutPesawat = {xof+225, yof+62};
    bufferDrawPlaneSolid(ekorPesawatAtas, cRed, cRed, 4);
    bufferDrawPlaneSolid(ekorPesawatBawah, cRed, cRed, 5);
    bufferDrawPlaneSolid(badanPesawat, cRed, cRed, 4);
    bufferDrawPlaneSolid(sayapAtas, cRed, cRed, 4);
    bufferDrawPlaneSolid(kepalaPesawat, cRed, cRed, 4);
    bufferDrawCircle(pMulutPesawat, 9, cRed);
}

void drawTank(int xof, int yof) {
    titik badanTank[] = {{xof+20,yof+90}, {xof+120,yof+90}, {xof+140,yof+60}, {xof,yof+60}};
    titik pShutterCircle = {xof+70,yof+60};
    titik tankGun[] = {{xof+63,yof+40}, {xof+77,yof+40}, {xof+77,yof}, {xof+64,yof}};
    bufferDrawPlaneSolid(badanTank, cRed, cRed, 4);
    bufferDrawCircle(pShutterCircle, 20, cRed);
    bufferDrawPlaneSolid(tankGun, cRed, cRed, 4);
}


void bufferDrawLine(titik p0, titik p1, warna c) {
    int x0 = p0.x; int x1 = p1.x; int y0 = p0.y; int y1 = p1.y;
    int dx = abs(x1-x0), wx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;){
      titik temp = {x0, y0};
      bufferDrawDot(temp, c);
      if (x0==x1 && y0==y1) break;
      e2 = err;
      if (e2 >-dx) { err -= dy; x0 += wx; }
      if (e2 < dy) { err += dx; y0 += sy; }
    }

    saveLine(p0, p1, c);
}

void saveLine(titik p0, titik p1, warna c)
{
    for(int i; i<lastLine; i++)
    {
        if((worldLines[i].p0.x == p0.x) && (worldLines[i].p0.y == p0.y) && 
           (worldLines[i].p1.x == p1.x) && (worldLines[i].p1.y == p1.y))
        {
            return;
        }
    }

    worldLines[lastLine].p0 = p0;
    worldLines[lastLine].p1 = p1;
    worldLines[lastLine].c = c;
    lastLine++;
}

void bufferDrawPlaneSolidCitra(titik *citra, titik pivot, warna c, warna bound_c, int sisi) {
  int i;
  titik* posAbs = (titik*) malloc(8 * sizeof(titik));
  for (i = 0; i < sisi; i++) {
    posAbs[i].x = citra[i].x + pivot.x;
    posAbs[i].y = citra[i].y + pivot.y;
  }
  bufferDrawPlaneSolid(posAbs, c, bound_c, sisi);
}

titik scaleDot(titik p0, titik p1, float s){
    titik output;
    output.x = p1.x;
    output.y = p1.y;
    int jarakx = abs(p1.x - p0.x);
    int jaraky = abs(p1.y - p0.y);
    if (p1.x < p0.x){
        output.x = ((int)(((float)p0.x) - ((float)jarakx * s)));
    }
    else {
        output.x = ((int)(((float)p0.x) + ((float)jarakx * s)));
    }
    if (p1.y < p0.y){
        output.y = ((int)(((float)p0.y) - ((float)jaraky * s)));
    }
    else {
        output.y = ((int)(((float)p0.y) + ((float)jaraky * s)));
    }
    
    
    
    return output;
}

void scaleBanyakDot(titik p0, titik *p1, float s, int banyaktitik){
    for (int i = 0; i < banyaktitik;i++){
        p1[i] = scaleDot(p0, p1[i], s);
    }
}

//view-stuff====================================================================

void init_view(titik p, int length_x, int length_y)
{
    view.origin.x = p.x;view.origin.y = p.y;
    view.length_x = length_x;
    view.length_y = length_y;
}

void refreshView()
{
    titik p0 = {0,0};
    titik p1 = {4000,4000};

    warna warna_default = {25, 25, 255, 255};

    //
    //       *1
    // *0
    //
    int i, j;
    if(p0.x < p1.x && p0.y < p1.y){
        for(i = p0.x; i < p1.x; i++)
            for(j = p0.y; j < p1.y; j++){
                viewport_r[i][j] = warna_default.r;
                viewport_g[i][j] = warna_default.g;
                viewport_b[i][j] = warna_default.b;
                viewport_a[i][j] = warna_default.a;
            }

        return;
    }


    //
    // *1
    //       *0
    //
    if(p0.x > p1.x && p0.y < p1.y){
        for(i = p1.x; i < p0.x; i++)
            for(j = p0.y; j < p1.y; j++){
                viewport_r[i][j] = warna_default.r;
                viewport_g[i][j] = warna_default.g;
                viewport_b[i][j] = warna_default.b;
                viewport_a[i][j] = warna_default.a;
            }

        return;
    }

    //
    //       *0
    // *1
    //
    if(p0.x > p1.x && p0.y > p1.y){
        for(i = p1.x; i < p0.x; i++)
            for(j = p1.y; j < p0.y; j++){
                viewport_r[i][j] = warna_default.r;
                viewport_g[i][j] = warna_default.g;
                viewport_b[i][j] = warna_default.b;
                viewport_a[i][j] = warna_default.a;
            }

        return;
    }

    //
    // *0
    //       *1
    //
    if(p0.x < p1.x && p0.y > p1.y){
        for(i = p0.x; i < p1.x; i++)
            for(j = p1.y; j < p0.y; j++){
                viewport_r[i][j] = warna_default.r;
                viewport_g[i][j] = warna_default.g;
                viewport_b[i][j] = warna_default.b;
                viewport_a[i][j] = warna_default.a;
            }

        return;
    }
}

void prepareView()
{
    for(int j=0; j<4000; j++)
    {
        for(int i=0; i<4000; i++)
        {
            window_r[i][j] = buffer_r[i][j];
            window_g[i][j] = buffer_g[i][j];
            window_b[i][j] = buffer_b[i][j];
            window_a[i][j] = buffer_a[i][j];
        }
    }

    refreshView();
    //resize view
    float scalex = getViewScalingX(window.length_x, view.length_x);
    float scaley = getViewScalingY(window.length_y, view.length_y);
    titik p0 = {0,0};
    // titik p1 = {1366,700};

    printf("a\n");
    // resizeLines(p0, 2);
    // printf("scale %f, %f\n", scalex, scaley);
    resizeLinesX(p0, scalex);
    resizeLinesY(p0, scaley);

    redrawLines();
    // printf("awawaw\n");

    //pindahin semua pixel yang ada di window ke view
    int wx = window.origin.x * scalex; //koordinat x kiri-atas window
    int wy = window.origin.y * scaley; //koordinat x kiri-atas window

    int vx = view.origin.x;
    int vy = view.origin.y;


    for(int j=0; j<(view.length_y); j++)
    {
        for(int i=0; i<(view.length_x); i++)
        {
            viewport_r[vx+i][vy+j] = buffer_r[wx+i][wy+j];
            viewport_g[vx+i][vy+j] = buffer_g[wx+i][wy+j];
            viewport_b[vx+i][vy+j] = buffer_b[wx+i][wy+j];
            viewport_a[vx+i][vy+j] = buffer_a[wx+i][wy+j];
        }
    }


    //kembalikan buffer
    resizeLinesX(p0, 1/scalex);
    resizeLinesY(p0, 1/scaley);

    for(int j=0; j<4000; j++)
    {
        for(int i=0; i<4000; i++)
        {
            buffer_r[i][j] = window_r[i][j];
            buffer_g[i][j] = window_g[i][j];
            buffer_b[i][j] = window_b[i][j];
            buffer_a[i][j] = window_a[i][j];
        }
    }
}

void loadView()
{
    int i, j;

    titik titik_sementara;
    warna warna_sementara;
    warna warna_kosong = {0, 0, 0, 0};
    for(i = 0; i < GLOBAL_LAYAR_X; i++){
        for(j = 0; j < GLOBAL_LAYAR_Y; j++){
            titik_sementara.x = i;
            titik_sementara.y = j;

            if(viewport_r[i][j] && viewport_g[i][j] &&
            viewport_b[i][j] && viewport_a[i][j]){
                warna_sementara.r = viewport_r[i][j];
                warna_sementara.g = viewport_g[i][j];
                warna_sementara.b = viewport_b[i][j];
                warna_sementara.a = viewport_a[i][j];
            }else{
                warna_sementara = warna_kosong;
            }

            DrawDot(titik_sementara, warna_sementara);
        }
    }
}

//window-stuff==================================================================

void init_window(titik p, int length_x, int length_y)
{
    window.origin.x = p.x;window.origin.y = p.y;
    window.length_x = length_x;
    window.length_y = length_y;
}

void shift_window(int x, int y)
{
    window.origin.x += x;
    window.origin.y += y;
}

void stretch_window(int x, int y)
{
    window.length_x += x;
    window.length_y += y;
}
//lines-stuff===================================================================
void printLines(int i)
{
    for(int ii = 0; ii<i; ii++)
    {
        printf("Line %d: [%d,%d] [%d,%d]\n", 
            ii, worldLines[ii].p0.x, worldLines[ii].p0.y, 
                worldLines[ii].p1.x, worldLines[ii].p1.y);
    }
}

void resizeLines(titik p0, float s)
{
    for(int i=0; i<lastLine; i++)
    {
        worldLines[i].p0 = scaleDot(p0, worldLines[i].p0, s);
        worldLines[i].p1 = scaleDot(p0, worldLines[i].p1, s);
    }
}

void resizeLinesX(titik p0, float s)
{
    for(int i=0; i<lastLine; i++)
    {
        worldLines[i].p0 = scaleXDot(p0, worldLines[i].p0, s);
        worldLines[i].p1 = scaleXDot(p0, worldLines[i].p1, s);
    }
}

void resizeLinesY(titik p0, float s)
{
    for(int i=0; i<lastLine; i++)
    {
        worldLines[i].p0 = scaleYDot(p0, worldLines[i].p0, s);
        worldLines[i].p1 = scaleYDot(p0, worldLines[i].p1, s);
    }
}

void redrawLines()
{
    for(int i=0; i<lastLine; i++)
    {
        bufferDrawLine(worldLines[i].p0, worldLines[i].p1, worldLines[i].c);
    }
}

double getViewScaling(int wHeight, int wWidth, int vHeight, int vWidth)
{
    int factor = vHeight < vWidth ? vHeight : vWidth;
    if (factor == vHeight) {
                return (double) wHeight / vHeight;
    } else {
            return (double) wWidth / vWidth;
    }
}

double getViewScalingX(int wWidth, int vWidth)
{
    return (double) vWidth / wWidth;
}

double getViewScalingY(int wHeight, int vHeight)
{
    return (double) vHeight / wHeight;
}

titik scaleXDot(titik p0, titik p1, float s){
    titik output;
    output.x = p1.x;
    output.y = p1.y;
    int jarakx = abs(p1.x - p0.x);
    if (p1.x < p0.x){
        output.x = ((int)(((float)p0.x) - ((float)jarakx * s)));
    }
    else {
        output.x = ((int)(((float)p0.x) + ((float)jarakx * s)));
    }

    
    
    
    return output;
}

titik scaleYDot(titik p0, titik p1, float s){
    titik output;
    output.x = p1.x;
    output.y = p1.y;
    int jaraky = abs(p1.y - p0.y);
    if (p1.y < p0.y){
        output.y = ((int)(((float)p0.y) - ((float)jaraky * s)));
    }
    else {
        output.y = ((int)(((float)p0.y) + ((float)jaraky * s)));
    }
    
    
    
    return output;
}