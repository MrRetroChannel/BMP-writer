#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
struct Color
{
    int r, g, b;
    Color(int a, int b, int c) : r(a), g(b), b(c)
    {}
};

class Image
{
    std::ofstream file;
    int height, width;

    public:
    Image()
    {}

    Image(int h, int w) : height(h), width(w)
    {}

    void write(const char* name)
    {
        file.open(name, std::ios::binary);
        unsigned char pad[3] = {0, 0, 0};
        int padcol = (4 - (width * 3) % 4) % 4;
        int filesize = padcol * height + 14 + 40 + width * height * 3;
        unsigned char fileheader[14];
        fileheader[0] = 'B';
        fileheader[1] = 'M';

        *(fileheader + 2) = filesize;

        fileheader[6] = 0; fileheader[7] = 0; fileheader[8] = 0; fileheader[9] = 0;
        fileheader[10] = 54;
        fileheader[11] = 0; fileheader[12] = 0; fileheader[13] = 0;

        unsigned char infoheader[40];

        infoheader[0] = 40;
        infoheader[1] = 0; infoheader[2] = 0; infoheader[3] = 0;

        infoheader[4] = width; 
        infoheader[5] = width >> 8; 
        infoheader[6] = width >> 16;
        infoheader[7] = width >> 24;

        infoheader[8] = height;
        infoheader[9] = height >> 8;
        infoheader[10] = height >> 16;
        infoheader[11] = height >> 24;

        infoheader[12] = 1;
        infoheader[13] = 0; 

        infoheader[14] = 24;
        infoheader[15] = 0;

        for (int i=16; i < 39; i++)
        infoheader[i] = 0;

        file.write((char*)fileheader, 14);
        file.write((char*)infoheader, 40);
        

        for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            unsigned char result[3] = {(x * y) % 250, x , y };
            
            file.write((char*)result, 3);
        }

        file.write((char*)pad, padcol);
    }

    ~Image()
    {
        file.close();
    }
};

int main()
{
    srand(time(0));
    Image img(500, 500);
    img.write("123.bmp");
}