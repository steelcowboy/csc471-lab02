#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"

using namespace std;

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
    int vax = atoi(argv[4]);
    int vay = atoi(argv[5]);

    int vbx = atoi(argv[6]);
    int vby = atoi(argv[7]);

    int vcx = atoi(argv[8]);
    int vcy = atoi(argv[9]);

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
    
    // Calculate the bounding box
    int maxx = max(max(vax, vbx), vcx);
    int maxy = max(max(vay, vby), vcy);
    int minx = min(min(vax, vbx), vcx);
    int miny = min(min(vay, vby), vcy);

    for (int i = minx; i <= maxx; i++) {
        for (int j = miny; j <= maxy; j++) {
            image->setPixel(i, j, 200, 0, 200);
        }
    }

    image->setPixel(vax, vay, 0, 200, 200);
    image->setPixel(vbx, vby, 0, 200, 200);
    image->setPixel(vcx, vcy, 0, 200, 200);

    
	// Write image to file
	image->writeToFile(filename);
	return 0;
}
