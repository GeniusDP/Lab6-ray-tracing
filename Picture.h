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
    unsigned char B=0;
    unsigned char G=0;
    unsigned char R=0;
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
            pixel.R = int(double(matrix[i][j]) * double(255));
            pixel.G = int(double(matrix[i][j]) * double(255));
            pixel.B = int(double(matrix[i][j]) * double(255));
            out.write((char*)&(pixel), sizeof(PIXEL));
        }
        out.write(str, padding);
    }
    out.close();
}
