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

int main() {
    sine_wave(10.0, 443, 1.0);
}