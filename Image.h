#pragma once
#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//(1) Declare a Header struct
struct Header {
    //(2) Declare each Header element
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

//(3) Declare a Pixel struct
struct Pixel {
    //(4) Declare each Pixel element
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

//(5) Declare an Image class
class Image {

public:

    //(9) Declare a header for the Image
    Header header;

    //(10) Declare a vector of pixels
    vector<Pixel> pixels;

    //(11) Declare an Image constructor
    Image();



    //(12) Declare a read function
    void read(const string& inName);

    //(13) Declare a write function
    void write(const string& outName);

    Image multiply(Image& top, Image& last);
    Image subtract(Image& top, Image& last);
    Image screen(Image& top, Image& bottom);
    Image overlay(Image& top, Image& bottom);
    Image add_green(Image& top,int& g);
    Image add_red(Image& top,int& r);
    Image add_blue(Image& top,int& b);
    Image change(Image& top);
    Image redd(Image& top, Image& bottom);
    Image greenn(Image& top, Image& bottom);
    Image bluee(Image& top, Image& bottom);
    Image combine(Image& top, Image& middle, Image& bottom); // change color to combine
    Image upsidedown(Image& top);
    ////////// PART 2 ////////////////////////
    Image operation(string& command);
    Image scale_red(Image& top,int& scale);
    Image scale_blue(Image& top,int& scale);
    Image scale_green(Image& top,int& scale);










};
