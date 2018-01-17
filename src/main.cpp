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
	if(argc < 10) {
		cout << "Usage: " << argv[0] << " filename width height vax vay vbx vby vcx vcy" << endl;
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
            atoi(argv[6]), atoi(argv[7]), 
            atoi(argv[8]), atoi(argv[9]));

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);

    float a, b, g;
    
    // Calculate the bounding box
    for (int i = t.l; i <= t.r; i++) {
        for (int j = t.b; j <= t.t; j++) {
            b = t.get_area_b(i, j) / t.area;
            g = t.get_area_c(i, j) / t.area;
            a = 1 - b - g;
            //cout << "alpha: " << a << "\nbeta: " << b << "\ngamma: " << g << endl;

            if (a < 0 || b < 0 || g < 0)
                continue;

            image->setPixel(i, j, 255, 0, 0);
        }
    }

	// Write image to file
	image->writeToFile(filename);
	return 0;
}
