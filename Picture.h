#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#pragma pack(push, 1)
struct BMP {
    int8_t id[2];// ������ �� ����� 'B' � 'M'
    int32_t filesize;        // ����� ����� � ������!!!!!!!!!!!!!!!!!!!!!!
    int32_t reserved;     // 0, 0
    int32_t headersize;      // 54L ��� 24-����� ���������
    int32_t infoSize;        // 40L ��� 24-����� ���������
    int32_t width;           // ������ ���������� � �������!!!!!!!!!!!!!!!!!!!!!!
    int32_t depth;           // ������ ���������� � �������!!!!!!!!!!!!!!!!!!!!!!)))
    int16_t biPlanes;        // 1 (��� 24-����� ���������)
    int16_t bits;            // 24 (��� 24-����� ���������)
    int32_t biCompression;   // 0L
    int32_t biSizeImage;     // ����� ��������� � 0L ��� ��������� ��� �������� (��� ������)
    int32_t biXPelsPerMeter; // ������������� ������� ������ �� ����, ����� 0L
    int32_t biYPelsPerMeter; // �� ����, �� �����
    int32_t biClrUsed;       // ��� ������������ ���������, ����� ��������� 0L
    int32_t biClrImportant;  // �� ����
    BMP() {
        id[0] = 'B';
        id[1] = 'M';
        reserved = 0;
        infoSize = 40;
        biPlanes = 1;
        bits = 24;
        biCompression = 0;
        biYPelsPerMeter = 2834;
        biClrUsed = 0;
        biClrImportant = 0;
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PIXEL {
    unsigned char B = 255;
    unsigned char G = 255;
    unsigned char R = 255;
    PIXEL() {
        B = 255;
        G = 255;
        R = 255;
    }
    PIXEL(unsigned char r, unsigned char g, unsigned char b) {
        R = r;
        B = b;
        G = g;
    }
};
#pragma pack(pop)

void printToPicture(vector<vector<double>>& matrix) {
    int width = matrix[0].size(), depth = matrix.size();
    BMP header;

    ofstream out("out.bmp", ios::binary);

    char str[10] = {};
    int padding = (4 - width * sizeof(PIXEL) % 4) % 4;
    out.seekp(0, ios_base::beg);

    header.filesize = sizeof(BMP) + sizeof(PIXEL) * header.width * header.depth + padding * header.depth;
    header.width = width;
    header.depth = depth;
    header.headersize = sizeof(BMP);

    out.write((char*)&header, sizeof(BMP));

    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < width; j++) {
            PIXEL pixel;

            if (matrix[i][j] == -5) {
                //���
                pixel.R = 255;
                pixel.G = 255;
                pixel.B = 255;
            }
            else if (matrix[i][j] < 0.14) {
                pixel.R = (unsigned char)255;
                pixel.G = (unsigned char)0;
                pixel.B = (unsigned char)0;
            }
            else if (matrix[i][j] < 0.28) {
                pixel = { (unsigned char)255, (unsigned char)87, (unsigned char)15 };
            }
            else if (matrix[i][j] < 0.42) {
                pixel = { (unsigned char)255, (unsigned char)220, (unsigned char)0 };
            }
            else if (matrix[i][j] < 0.55) {
                pixel = { (unsigned char)30, (unsigned char)255, (unsigned char)40 };
            }
            else if (matrix[i][j] < 0.70) {
                pixel = { (unsigned char)45, (unsigned char)255, (unsigned char)255 };
            }
            else if (matrix[i][j] < 0.84) {
                pixel = { (unsigned char)30, (unsigned char)40, (unsigned char)255 };
            }
            else if (matrix[i][j] <= 1) {
                pixel = { (unsigned char)255, (unsigned char)40, (unsigned char)255 };
            }

            out.write((char*)&(pixel), sizeof(PIXEL));
        }
        out.write(str, padding);
    }
    out.close();
}
/*
0 - ������� (255, 0, 0)
1 - ��������� (255, 87, 15)
2 - ����� (255, 220, 0)
3 - ������ (30, 255, 40)
4 - ������� (45, 255, 255)
5 - ����� (30, 40, 255)
6 - ���������� (255, 40, 255)
*/

/*
0.0-0.3 - �����
0.3-0.5 - �������
0.5-0.7 - �������
0.7-1 - mix
*/


/*
                //y = |x-a|
                pixel.R = int(fabs(double(matrix[i][j]-0.5)) * double(255));//128 - int(double(matrix[i][j]-0.5) * double(128));
                pixel.G = 0.75 * int(double(matrix[i][j]) * double(255));
                pixel.B = 0.5 * int(double(matrix[i][j]) * double(255));

*/