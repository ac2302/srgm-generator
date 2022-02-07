#include <iostream>

constexpr uint32_t sample_rate = 44100; // CD quality

int main()
{
    // send the following values in big-endian format
    uint32_t magic = htobe32(0x2e736e64);     // ".snd"
    uint32_t data_offset = htobe32(24);       // minimal header
    uint32_t data_size = htobe32(0xffffffff); // length unknown
    uint32_t encoding = htobe32(3);           // 16-bit linear PCM
    uint32_t rate = htobe32(sample_rate);     // samples/sec, 44100 = CD quality
    uint32_t channels = htobe32(1);           // 1 channel = mono

    std::cout.write((char *)&magic, sizeof(magic));
    std::cout.write((char *)&data_offset, sizeof(data_offset));
    std::cout.write((char *)&data_size, sizeof(data_size));
    std::cout.write((char *)&encoding, sizeof(encoding));
    std::cout.write((char *)&rate, sizeof(rate));
    std::cout.write((char *)&channels, sizeof(channels));
}