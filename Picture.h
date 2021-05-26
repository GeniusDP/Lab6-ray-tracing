#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#pragma pack(push, 1)
struct BMP {
    int8_t id[2];// Çàâæäè äâ³ ë³òåðè 'B' ³ 'M'
    int32_t filesize;        // Ðîçì³ð ôàéëà â áàéòàõ!!!!!!!!!!!!!!!!!!!!!!
    int32_t reserved;     // 0, 0
    int32_t headersize;      // 54L äëÿ 24-á³òíèõ çîáðàæåíü
    int32_t infoSize;        // 40L äëÿ 24-á³òíèõ çîáðàæåíü
    int32_t width;           // øèðèíà çîáðàæåííÿ â ï³êñåëÿõ!!!!!!!!!!!!!!!!!!!!!!
    int32_t depth;           // âèñîòà çîáðàæåííÿ â ï³êñåëÿõ!!!!!!!!!!!!!!!!!!!!!!)))
    int16_t biPlanes;        // 1 (äëÿ 24-á³òíèõ çîáðàæåíü)
    int16_t bits;            // 24 (äëÿ 24-á³òíèõ çîáðàæåíü)
    int32_t biCompression;   // 0L
    int32_t biSizeImage;     // Ìîæíà ïîñòàâèòè â 0L äëÿ çîáðàæåíü áåç êîìïðåññ³¿ (íàø âàð³àíò)
    int32_t biXPelsPerMeter; // Ðåêîìåíäîâàíà ê³ëüê³ñòü ï³êñåë³â íà ìåòð, ìîæíà 0L
    int32_t biYPelsPerMeter; // Òå ñàìå, ïî âèñîò³
    int32_t biClrUsed;       // Äëÿ ³íäåêñîâàíèõ çîáðàæåíü, ìîæíà ïîñòàâèòè 0L
    int32_t biClrImportant;  // Òå ñàìå
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
    unsigned char B;
    unsigned char G;
    unsigned char R;
};
#pragma pack(pop)

void printToPicture(vector<vector<char>>& matrix) {
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