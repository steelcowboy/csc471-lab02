#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"

using namespace std;

class Triangle {
public:
    float area;
    int vax, vay, vbx, vby, vcx, vcy;
    int t,l,b,r;
    Triangle (int,int,int,int,int,int);
    float get_area_b (int, int); 
    float get_area_c (int, int); 
};

Triangle::Triangle (int ax, int ay, int bx, int by, int cx, int cy) {
    vax = ax; vay = ay;
    vbx = bx; vby = by;
    vcx = cx; vcy = cy;

    r = max(max(vax, vbx), vcx);
    t = max(max(vay, vby), vcy);
    l = min(min(vax, vbx), vcx);
    b = min(min(vay, vby), vcy);

    area = 1/2.0 * ((vbx - vax)*(vcy - vay) - (vcx - vax)*(vby - vay));
    cout << "Triangle area: " << area << endl;
}

float Triangle::get_area_b (int px, int py) {
    return 1/2.0 * ((vax - vcx)*(py - vcy) - (px - vcx)*(vay - vcy));
}

float Triangle::get_area_c (int px, int py) {
    return 1/2.0 * ((vbx - vax)*(py - vay) - (px - vax)*(vby - vay));
}

int main(int argc, char **argv)
{
	if(argc < 19) {
        //                                  1        2     3     4  5  6  7 8   9 10 11 12 13 14 15 16 17 18
		cout << "Usage: " << argv[0] << " filename width height x0 y0 r0 g0 b0 x1 y1 r1 g1 b1 x2 y2 r2 g2 b2" << endl;
		return 0;
	}
	// Output filename
	string filename(argv[1]);
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[3]);

    // Triangle bounds
    Triangle t (atoi(argv[4]), atoi(argv[5]), 
            atoi(argv[9]), atoi(argv[10]), 
            atoi(argv[14]), atoi(argv[15]));

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);

    float a, b, g;
    int re, bl, gr;
    
    // Calculate the bounding box
    for (int i = t.l; i <= t.r; i++) {
        for (int j = t.b; j <= t.t; j++) {
            b = t.get_area_b(i, j) / t.area;
            g = t.get_area_c(i, j) / t.area;
            a = 1 - b - g;
            //cout << "alpha: " << a << "\nbeta: " << b << "\ngamma: " << g << endl;

            if (a < 0 || b < 0 || g < 0)
                continue;

            re = a * atoi(argv[6]) + b * atoi(argv[10]) + g * atoi(argv[16]);
            bl = a * atoi(argv[7]) + b * atoi(argv[11]) + g * atoi(argv[17]);
            gr = a * atoi(argv[8]) + b * atoi(argv[12]) + g * atoi(argv[18]);
            image->setPixel(i, j, re, bl, gr);
        }
    }

	// Write image to file
	image->writeToFile(filename);
	return 0;
}
