#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"

using namespace std;

class Triangle {
public:
    int t,l,b,r;
    Triangle (int,int,int,int,int,int);
}

Triangle::Triangle (int vax, int vay, int vbx, int vby, int vcx, int vcy) {
    r = max(max(vax, vbx), vcx);
    t = max(max(vay, vby), vcy);
    l = min(min(vax, vbx), vcx);
    b = min(min(vay, vby), vcy);
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
    Triangle t (argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
    
    // Calculate the bounding box
    for (int i = t.l; i <= t.r; i++) {
        for (int j = t.b; j <= t.t; j++) {
            image->setPixel(i, j, 200, 0, 200);
        }
    }

	// Write image to file
	image->writeToFile(filename);
	return 0;
}
