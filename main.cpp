#include<iostream>
using namespace std;

int main() {
    //image
    
    const int image_width = 256;
    const int image_height = 256;
    
    //render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int i = image_height-1; i>=0; i--) {
        clog << "\rScanliness remaining: " << (image_height - i) << flush;
        for(int j=0; j<image_width; j++) {
            auto r = double(i) / (image_height - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int> (255.999 * r);
            int ig = static_cast<int> (255.990 * g);
            int ib = static_cast<int> (255.999 * b);
        
            cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    cerr << "\nDone.\n";
}

//just goofing around and testing irfanView for multiplle values of width and height