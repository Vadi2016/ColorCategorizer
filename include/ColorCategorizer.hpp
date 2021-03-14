#ifndef CATEGORIZER_HPP
#define CATEGORIZER_HPP

#include <iostream>
#include <fstream>

void ProcessFile(std::fstream *file, const unsigned int *histogram, unsigned int len);

int ExtractNum(std::fstream *file, char delimiter);

void BuildHistogram(std::fstream *file,
                    unsigned int *histogram,
                    unsigned int len,
                    int width,
                    int height);


void PrintHistogram(const unsigned int *histogram,
                    unsigned int len,
                    int width,
                    int height);

#endif
