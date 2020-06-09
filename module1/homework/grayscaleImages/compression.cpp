#include "compression.hpp"
#include <iostream>


void printBitmap(Bitmap bitmap) {
    std::cout << "BITMAP!" << "\n";
    for(const auto & line : bitmap)
    {
        for(const auto & pixel : line)
        {
            std::cout << static_cast<int>(pixel) << " ";
        }
        std::cout << "\n";
    }
}

CompressedBitmap compressLine(const std::array<uint8_t,width>& line)
{
    CompressedBitmap result;
    std::pair<uint8_t, uint8_t> buffer{line[0], 0};

        for (const auto& pixel : line)
        {
            if (buffer.first == pixel)
            {
                buffer.second++;
                buffer.first = pixel;
            }
            else
            {
                result.push_back(buffer);
                buffer.first = pixel;
                buffer.second = 1;
            }
        }
        result.push_back(buffer);
    return result;
}



CompressedBitmap compressGrayscale(Bitmap bitmap)
{
    CompressedBitmap result;
    CompressedBitmap tmp;

    //printBitmap(bitmap);

    for (const auto& line : bitmap)
    {
        tmp = compressLine(line);
        result.insert(std::end(result), std::begin(tmp), std::end(tmp));

    }
    return result;
}

Bitmap decompressGrayscale(CompressedBitmap compressedBitmap)
{
    Bitmap result;
    return result;
}