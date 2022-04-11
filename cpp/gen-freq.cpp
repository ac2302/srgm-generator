#include <iostream>
#include <cmath>

constexpr uint32_t sample_rate = 44100; // CD quality

void sine_wave(float duration, float frequency, float amplitude)
{
    uint32_t num_samples = sample_rate * duration;   // total number of samples to generate
    float period = 1.0 / frequency;                  // time-period of each cycle in seconds
    float samples_per_period = sample_rate * period; // the number of samples per cycle

    for (uint32_t i = 0; i < num_samples; ++i)
    {
        constexpr int16_t max_sample = 0x7fff;
        float angle = fmodf(i, samples_per_period) / samples_per_period * 2 * M_PI; // [0..2PI]
        int16_t sample = sinf(angle) * max_sample * amplitude;

        sample = htobe16(sample);
        std::cout.write((char *)&sample, sizeof(sample)); // write out one sample
    }
}

void square_wave(float duration, float frequency, float amplitude)
{
    uint32_t num_samples = sample_rate * duration;   // total number of samples to generate
    float period = 1.0 / frequency;                  // time-period of each cycle in seconds
    float samples_per_period = sample_rate * period; // the number of samples per cycle

    for (uint32_t i = 0; i < num_samples; ++i)
    {
        constexpr int16_t max_sample = 0x7fff;
        float angle = fmodf(i, samples_per_period) / samples_per_period; // [0..1]
        int16_t sample = ((angle < .5) ? max_sample : -max_sample) * amplitude;

        sample = htobe16(sample);
        std::cout.write((char *)&sample, sizeof(sample)); // write out one sample
    }
}

int main(int argc, char **argv)
{
    square_wave(atof(argv[1]), atof(argv[2]), atof(argv[3]));
}