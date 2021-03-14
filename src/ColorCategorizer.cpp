#include "ColorCategorizer.hpp"


int ExtractNum(std::fstream *file, char delimiter) {
    int alphabet[256];
    char sym;
    int res = 0;
    unsigned int digit_b = static_cast<unsigned int>(file->tellg());

    do {
        file->read(&sym, 1);
    } while (sym != delimiter);

    int digit_e = static_cast<int>(file->tellg()) - 2;
    int j = 0;
    for (int d = '0'; d <= '9'; d++, j++) alphabet[d] = j;
    int c = 1;
    for (j = digit_e; j >= digit_b; j--, c *= 10) {
        file->seekg(j);
        file->read(&sym, 1);
        res += alphabet[sym] * c;
    }
    file->seekg(digit_e + 2);
    return res;
}

void BuildHistogram(std::fstream *file,
                    unsigned int *histogram,
                    unsigned int len,
                    int width,
                    int height) {
    char sym;
    for (unsigned int d = 0; d < len; ++d)histogram[d] = 0;
    file->seekg(static_cast<unsigned int>(file->tellg()) + 4);
    for (unsigned int d = 0; d < (width * height); ++d) {
        if (file->eof())break;
        file->read(&sym, 1);
        histogram[static_cast<unsigned char>(sym)] += 1;
    }
    std::cout << std::endl;
    for (int j = 0; j < 256; j++) {
        std::cout << "[" << j << "] ";
        for (unsigned int c = 0; c < histogram[j]; c++)
            std::cout << "|";
        std::cout << std::endl;
    }
}

void PrintHistogram(const unsigned int *histogram,
                    unsigned int len,
                    int width,
                    int height) {
    auto *out = new std::ofstream("histogram.txt");
    *out << "Building histogram for graphic file" << std::endl;
    *out << "Width: " << width << "\t Height: " << height << std::endl;
    for (unsigned int j = 0; j < len; j++) {
        *out << "[" << j << "] ";
        for (unsigned int c = 0; c < histogram[j]; c++)
            *out << "|";
        *out << std::endl;
    }
    *out << "End of file " << std::endl << std::endl;
    out->close();
    delete out;
}

void ProcessFile(std::fstream *file, unsigned int *histogram, unsigned int len) {
    int width, height;
    char PGM_hdr1[2];

    file->read(PGM_hdr1, 2);
    if ((PGM_hdr1[0] != 0x50) || (PGM_hdr1[1] != 0x35)) return;
    std::cout << "PGM header detected" << std::endl;

    file->seekg(static_cast<unsigned int>(file->tellg()) + 1);

    width = ExtractNum(file, 0x20);
    std::cout << "Width: " << width << std::endl;

    height = ExtractNum(file, 0x0A);
    std::cout << "Height: " << width << std::endl;

    BuildHistogram(file, histogram, len, width, height);

    PrintHistogram(histogram, len, width, height);
}

int main(int argc, char **args) {
    auto *f = new std::fstream();
    const unsigned int SIZE = 256;
    unsigned int histogram[SIZE];

    if (argc == 1) {
        std::cout << "Please specify input file(s)!" << std::endl;
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        f->open(args[i], std::ios::binary | std::ios::in);
        if (!f->is_open()) {
            std::cout << "File: " << args[i] << " is not accessible!" << std::endl;
            continue;
        }
        std::cout << "File " << args[i] << " opened" << std::endl;
        ProcessFile(f, histogram, SIZE);
        f->close();
    }
    delete f;
    return 0;
}
