#include "ColorCategorizer.hpp"
#define HISTOGRAM_SIZE 256
#define ALPHABET_SIZE 256

using namespace std;


unsigned int histogram[HISTOGRAM_SIZE];
int alphabet[ALPHABET_SIZE];

int main(int argc, char** args) 
{
    fstream f;
    ofstream out("histogram.txt");
    int width = 0;
    int height = 0;
    char PGM_hdr1[2];
    cout << "Program started" << endl;
    if (argc == 1) {
        cout << "Please specify input file(s)!" << endl;
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        f.open(args[i], ios::binary|ios::in);
        if (!f.is_open())
        {
            cout << "File: " << args[i] << " is not accesible!" << endl;
            continue;
        }
        cout << "Opened " << args[i] << " file" << endl;
        f.read(PGM_hdr1, 2);
        if ((PGM_hdr1[0] != 0x50)||(PGM_hdr1[1] != 0x35)) continue;
        cout << "PGM header detected" << endl;
        f.seekg(static_cast<unsigned int>(f.tellg()) + 1);
        unsigned int digit_b = static_cast<unsigned int>(f.tellg());
        char sym;
        do
        {
           f.read(&sym, 1);
        }while(sym != 0x20);
        unsigned int digit_e = static_cast<unsigned int>(f.tellg()) - 2;
        int j = 0;
        for (int d = '0'; d <= '9'; d++, j++) alphabet[d] = j;
        int c = 1;
        for(j = digit_e; j >= digit_b; j--, c *= 10)
        {
            f.seekg(j);
            f.read(&sym, 1);
            width += alphabet[sym] * c;
        }
        cout << "Width: " << width << endl;
        digit_b = digit_e + 2;
        c = 1;
        do
        {
            f.read(&sym, 1);
        }while(sym != 0x0A);
        digit_e = static_cast<unsigned int>(f.tellg()) - 2;
        for (j = digit_e; j >= digit_b; j--, c *= 10)
        {
            f.seekg(j);
            f.read(&sym, 1);
            height += alphabet[sym] * c;
        }
        cout << "Height: " << height << endl;
        for (int d = 0; d < 256; ++d) histogram[d] = 0;
        f.seekg(digit_e + 6);
        for (int d = 0; d < (width * height); ++d)
        {
            if (f.eof()) break;
            f.read(&sym, 1);
            histogram[static_cast<unsigned char>(sym)] += 1;
        }
        cout << endl;
        for (j = 0; j < 256; j++)
        {
            cout << "[" << j << "] ";
            for (c = 0; c < histogram[j]; c++) cout << "|";
            cout << endl;
        }
        f.close();

        out << "File: " << args[i] << endl;
        out << "Width: " << width << "\tHeight: " << height << endl;
        for (j = 0; j < 256; j++)
        {
            out << "[" << j << "] ";
            for (c = 0; c < histogram[j]; c++) out << "|";
            out << endl;
        }
        out << "End of file" << args[i] << endl << endl;
        out.close();
    }
    cout << "Program ended" << endl;
	return 0;
}
