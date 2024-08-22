#include "Image.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>


Image::Image()
{
}

void Image::read(const string& inName) {
    //(14) Read in the .tga file
    ifstream stream(inName, ios_base::binary);

    //(15) Check if the file is opening
    if (!stream.is_open()) {
        cout << "file is not open :(" << endl;
    }

    //(16) Read in each element of the .tga file
    stream.read(&header.idLength, sizeof(header.idLength));
    stream.read(&header.colorMapType, sizeof(header.colorMapType));
    stream.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    stream.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    stream.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    stream.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
    stream.read((char*)&header.xOrigin, sizeof(header.xOrigin));
    stream.read((char*)&header.yOrigin, sizeof(header.yOrigin));
    stream.read((char*)&header.width, sizeof(header.width));
    stream.read((char*)&header.height, sizeof(header.height));
    stream.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    stream.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

    //(17) Get the image size by multiplying the image height and width
    int imageSize = (int)(header.width * header.height);

    //(18) Create a for loop to read in all the pixels
    for (int i = 0; i < imageSize; i++) {
        Pixel pixel;

        stream.read((char*)&pixel.blue, sizeof(pixel.blue));
        stream.read((char*)&pixel.green, sizeof(pixel.green));
        stream.read((char*)&pixel.red, sizeof(pixel.red));

        pixels.push_back(pixel);
    }

    //(21) Push in each pixel to the pixel vector

}

void Image::write(const string& outName) {
    //(22) Create a .tga file
    ofstream stream(outName, ios_base::binary);

    //(23) Write out each .tga file header element
    stream.write(&header.idLength, sizeof(header.idLength));
    stream.write(&header.colorMapType, sizeof(header.colorMapType));
    stream.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
    stream.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    stream.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    stream.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
    stream.write((char*)&header.xOrigin, sizeof(header.xOrigin));
    stream.write((char*)&header.yOrigin, sizeof(header.yOrigin));
    stream.write((char*)&header.width, sizeof(header.width));
    stream.write((char*)&header.height, sizeof(header.height));
    stream.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    stream.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

    //(24) Create a for loop to write out each pixel
    for (int i = 0; i < pixels.size(); i++) {
        Pixel pixel = pixels[i];

        stream.write((char*)&pixel.blue, sizeof(pixel.blue));
        stream.write((char*)&pixel.green, sizeof(pixel.green));
        stream.write((char*)&pixel.red, sizeof(pixel.red));
    }

    //(25) Write out each image pixel

}











Image Image::multiply(Image& top, Image& last) {
    // Check if the header dimensions match
    if (top.header.width != last.header.width || top.header.height != last.header.height) {
        // Handle the case where the dimensions of the headers don't match
        // For example, you can return an empty image or add appropriate error handling
        top.header=last.header;
    }

    Image product = top; // Create a copy of the top image to store the result

    for (int i = 0; i < top.pixels.size(); i++) {
        // Perform pixel-wise multiplication
        product.pixels[i].blue = (top.pixels[i].blue * last.pixels[i].blue / 255.0f) + 0.5f;
        product.pixels[i].green = (top.pixels[i].green * last.pixels[i].green / 255.0f) + 0.5f;
        product.pixels[i].red = (top.pixels[i].red * last.pixels[i].red / 255.0f) + 0.5f;

        // Ensure that the result remains within the valid range [0, 255]
        product.pixels[i].blue = (product.pixels[i].blue < 0) ? 0 : (product.pixels[i].blue > 255) ? 255 : product.pixels[i].blue;
        product.pixels[i].green = (product.pixels[i].green < 0) ? 0 : (product.pixels[i].green > 255) ? 255 : product.pixels[i].green;
        product.pixels[i].red = (product.pixels[i].red < 0) ? 0 : (product.pixels[i].red > 255) ? 255 : product.pixels[i].red;
    }

    return product;
}

Image Image::subtract(Image& top, Image& last) {
    if (top.header.width != last.header.width || top.header.height != last.header.height) {
        // Handle the case where the dimensions of the headers don't match.
        // You may want to add appropriate error handling or return an empty image.
        top.header = last.header;
    }

    Image product = top;

    for (int i = 0; i < top.pixels.size(); i++) {
        int newBlue = top.pixels[i].blue - last.pixels[i].blue;
        int newGreen = top.pixels[i].green - last.pixels[i].green;
        int newRed = top.pixels[i].red - last.pixels[i].red;

        // Ensure the new values don't go below 0
        if(newBlue < 0)
        {
            newBlue =0;
        }

        if(newGreen < 0)
        {
            newGreen = 0;

        }
        if(newRed<0)
        {
            newRed = 0;
        }

        newBlue = std::max(0, newBlue);
        newGreen = std::max(0, newGreen);
        newRed = std::max(0, newRed);

        product.pixels[i].blue = newBlue;
        product.pixels[i].green = newGreen;
        product.pixels[i].red = newRed;
    }

    return product;
}


Image Image::screen(Image& top ,Image& bottom)
{
    top.header = bottom.header;

    Image new_image;

   // new_image = top.multiply(top, lay);
    new_image = top;


    for (int i = 0; i < new_image.pixels.size(); i++)
    {
        float topBlue = new_image.pixels[i].blue / 255.0f;
        float topGreen = new_image.pixels[i].green / 255.0f;
        float topRed = new_image.pixels[i].red / 255.0f;

        float bottomBlue = bottom.pixels[i].blue / 255.0f;
        float bottomGreen = bottom.pixels[i].green / 255.0f;
        float bottomRed = bottom.pixels[i].red / 255.0f;

        new_image.pixels[i].blue = (1 - (((1.0f - topBlue) * (1.0f - bottomBlue)))) * 255. + 0.5f;
        new_image.pixels[i].green = (1 - (((1.0f - topGreen) * (1.0f - bottomGreen)))) * 255. + 0.5f;
        new_image.pixels[i].red = (1 - (((1.0f - topRed) * (1.0f - bottomRed)))) * 255. + 0.5f;

        if (new_image.pixels[i].blue < 0) {
            new_image.pixels[i].blue = 0;
        }
        else if (new_image.pixels[i].blue > 255) {
            new_image.pixels[i].blue = 255;
        }

        if (new_image.pixels[i].green < 0) {
            new_image.pixels[i].green = 0;
        }
        else if (new_image.pixels[i].green > 255) {
            new_image.pixels[i].green = 255;
        }

        if (new_image.pixels[i].red < 0) {
            new_image.pixels[i].red = 0;
        }
        else if (new_image.pixels[i].red > 255) {
            new_image.pixels[i].red = 255;
        }
    }


    return new_image;
}

Image Image::overlay(Image& top, Image& bottom) {
    Image result = top;


    if (top.pixels.size() != bottom.pixels.size()) {
        return result;
    }


    for (int i = 0; i < top.pixels.size(); i++) {
        float newBlue, newGreen, newRed;


        float topBlue = top.pixels[i].blue / 255.0f;
        float topGreen = top.pixels[i].green / 255.0f;
        float topRed = top.pixels[i].red / 255.0f;


        float bottomBlue = bottom.pixels[i].blue / 255.0f;
        float bottomGreen = bottom.pixels[i].green / 255.0f;
        float bottomRed = bottom.pixels[i].red / 255.0f;


        if (bottomBlue <= 0.5f) {
            newBlue = 2.0f * topBlue * bottomBlue;
        }
        else {
            newBlue = 1.0f - 2.0f * (1.0f - topBlue) * (1.0f - bottomBlue);
        }


        if (bottomGreen <= 0.5f) {
            newGreen = 2.0f * topGreen * bottomGreen;
        }
        else {
            newGreen = 1.0f - 2.0f * (1.0f - topGreen) * (1.0f - bottomGreen);
        }


        if (bottomRed <= 0.5f) {
            newRed = 2.0f * topRed * bottomRed;
        }
        else {
            newRed = 1.0f - 2.0f * (1.0f - topRed) * (1.0f - bottomRed);
        }


        if (newBlue < 0.0f) {
            newBlue = 0.0f;
        }
        else if (newBlue > 1.0f) {
            newBlue = 1.0f;
        }


        if (newGreen < 0.0f) {
            newGreen = 0.0f;
        }
        else if (newGreen > 1.0f) {
            newGreen = 1.0f;
        }


        if (newRed < 0.0f) {
            newRed = 0.0f;
        }
        else if (newRed > 1.0f) {
            newRed = 1.0f;
        }




        result.pixels[i].blue = static_cast<int>((newBlue * 255) + 0.5f);
        result.pixels[i].green = static_cast<int>((newGreen * 255) + 0.5f);
        result.pixels[i].red = static_cast<int>((newRed * 255) + 0.5f);
    }


    return result;
}
// /b .\examples\EXAMPLE_part2.tga .\'Project 2'\task2.tga



Image Image::add_green(Image& top,int& g)
{
    Image overlay_image = top;
    int newgreen;

    for (int i = 0; i < top.pixels.size(); i++)
    {

        newgreen = overlay_image.pixels[i].green + g;
        if (newgreen > 255)
        {
            newgreen = 255;
        }
        else if (newgreen < 0)
        {
            newgreen = 0;
        }
        overlay_image.pixels[i].green = newgreen;


    }
    return overlay_image;

}
Image Image::add_blue(Image& top, int& b) {
    Image overlay_image = top;

    for (int i = 0; i < overlay_image.pixels.size(); i++) {
        int newblue = overlay_image.pixels[i].blue + b;

        // Ensure the value stays within the valid range [0, 255]
        newblue = std::max(0, std::min(255, newblue));

        overlay_image.pixels[i].blue = newblue;
    }

    return overlay_image;
}

Image Image::add_red(Image& top, int& r)
{
    Image overlay_image = top;
    int newred;

    for (int i = 0; i < top.pixels.size(); i++)
    {

        newred = overlay_image.pixels[i].red + r;
        if (newred > 255)
        {
            newred = 255;
        }
        else if (newred < 0)
        {
            newred = 0;
        }
        overlay_image.pixels[i].red = newred;


    }
    return overlay_image;

}

Image Image ::change(Image& top) /// scaling which mean just multiplying
{
    float newgreen = 0;
    float newblue = 0;
    Image overlay_image = top;

    for (int i = 0; i < top.pixels.size(); i++)
    {
        float topRed = top.pixels[i].red *4;
        float topBlue = top.pixels[i].blue * 0;

        if (topRed > 255)
        {
            topRed = 255;
        }
        else if (topRed < 0)
        {
            topRed = 0;
        }
        if (topBlue > 255)
        {
            topBlue = 255;
        }
        else if (topBlue < 0)
        {
            topBlue = 0;
        }

        overlay_image.pixels[i].blue = topBlue;

        overlay_image.pixels[i].red = topRed;


    }
    return overlay_image;

}

Image Image::redd(Image& top, Image& bottom) {
    top.header = bottom.header;

    Image overlay_image = top;
    Image image = bottom;

    for (int i = 0; i < overlay_image.pixels.size(); i++) {
        int redValue = image.pixels[i].red;

        overlay_image.pixels[i].red = redValue;
        overlay_image.pixels[i].green = redValue;
        overlay_image.pixels[i].blue = redValue;
    }

    return overlay_image;
}



Image Image::greenn(Image& top, Image& bottom)
{
    top.header = bottom.header;

    Image overlay_image = top;
    Image image = bottom;



    for (int i = 0; i < overlay_image.pixels.size(); i++)
    {
        overlay_image.pixels[i].green = image.pixels[i].green;
        overlay_image.pixels[i].blue = image.pixels[i].green;
        overlay_image.pixels[i].red = image.pixels[i].green;

    }


    return overlay_image;
}


Image Image::bluee(Image& top, Image& bottom)
{
    top.header = bottom.header;
    Image overlay_image = top;
    Image image = bottom;



    for (int i = 0; i < overlay_image.pixels.size(); i++)
    {
        overlay_image.pixels[i].green = image.pixels[i].blue;
        overlay_image.pixels[i].blue = image.pixels[i].blue;
        overlay_image.pixels[i].red = image.pixels[i].blue;

    }


    return overlay_image;
}
Image Image::combine(Image &top, Image &middle, Image &bottom)
{
    Image lR = top; //tracking image
    Image lG = middle;
    Image lB = bottom;
    Image image; //tracking image

    if (lR.header.width != lG.header.width || lR.header.width != lB.header.width ||
        lR.header.height != lG.header.height || lR.header.height != lB.header.height) {

    }

    image.header = lR.header;

    for (int i = 0; i < lB.pixels.size(); i++) {
        Pixel pixs;
        pixs.blue = lB.pixels[i].blue;
        pixs.green = lG.pixels[i].green;
        pixs.red = lR.pixels[i].red;
        image.pixels.push_back(pixs);
    }
    return image;
}



Image Image::upsidedown(Image& top)
{
    Image uPside;
    uPside.header = top.header;


    for (int i = top.pixels.size()-1; i >= 0; i--)
    {
        Pixel pixs = top.pixels[i];
        uPside.pixels.push_back(pixs);
    }
    return uPside;

}



////////// part2//////////
Image Image:: scale_red(Image& top,int& scale)
{
Image overlay_image = top;

for (int i = 0; i < top.pixels.size(); i++)
{
float topRed = top.pixels[i].red *scale;

if (topRed > 255)
{
topRed = 255;
}
else if (topRed < 0)
{
topRed = 0;
}

overlay_image.pixels[i].red = topRed;

}
return overlay_image;

}

Image Image :: scale_blue(Image& top,int& scale)
{
    Image overlay_image = top;

    for (int i = 0; i < top.pixels.size(); i++) {
        float topBlue = top.pixels[i].blue * scale;

        if (topBlue > 255) {
            topBlue = 255;
        } else if (topBlue < 0) {
            topBlue = 0;
        }

        overlay_image.pixels[i].blue = topBlue;
    }
    return overlay_image;

}

    Image Image::scale_green(Image& top, int& scale)
    {
        Image overlay_image = top;

        for (int i = 0; i < top.pixels.size(); i++) {
            float topGreen = top.pixels[i].green * scale;

            if (topGreen > 255) {
                topGreen = 255;
            } else if (topGreen < 0) {
                topGreen = 0;
            }

            overlay_image.pixels[i].green = topGreen;
        }
        return overlay_image;

    }










//
// Created by LookO on 10/19/2023.
//