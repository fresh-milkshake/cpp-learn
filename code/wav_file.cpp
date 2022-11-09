#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

// RIFF headers, that will be used by third
// party software to identificate wav file
// and its parameters
// More info: https://docs.fileformat.com/audio/wav/
struct RIFF_header
{
    const char *riff = "RIFF";
    char *file_size;
    const char *wave_fmt = "WAVEfmt ";
    const char *fmt_size = "16";
    const char *fmt_type = "1";
    char *channels;
    char *sample_rate;
    char *byte_rate;
    char *block_align;
    const char *bits_per_sample = "16";
    const char *data = "data";
    char *data_size;
};

// Class for operations with WAV files
class WavFile
{
private:
    const char *file_path;         // Path to file
    RIFF_header header;            // RIFF header
    std::vector<float> audio_data; // Audio data in float format (from -1 to 1)
    int sample_rate = 0;           // Sample rate of audio data in Hz (samples per second)
    int channels = 0;              // Number of channels in audio data (1 - mono, 2 - stereo)
    int bits_per_sample = 0;       // Number of bits per sample (8 or 16)

    // Function for writing wav headers to the
    // start of the current file
    void write_headers(std::ofstream &file)
    {
        file.write(header.riff, 4);            // "RIFF" header
        file.write(header.file_size, 4);       // file size
        file.write(header.wave_fmt, 8);        // "WAVEfmt " to indentify file as wav
        file.write(header.fmt_size, 4);        // size of the fmt chunk
        file.write(header.fmt_type, 2);        // format type
        file.write(header.channels, 2);        // number of channels
        file.write(header.sample_rate, 4);     // sample rate
        file.write(header.byte_rate, 4);       // byte rate
        file.write(header.block_align, 2);     // block align
        file.write(header.bits_per_sample, 2); // bits per sample
        file.write(header.data, 4);            // write "data" header, containing all audio data
        file.write(header.data_size, 4);       // write size of audio data
    }

public:
    // Constructor for creating new wav file
    WavFile(const char *file_path, int sample_rate, int channels, int bits_per_sample)
    {
        this->file_path = file_path;
        this->sample_rate = sample_rate;
        this->channels = channels;
        this->bits_per_sample = bits_per_sample;
    }

    // Sample new audio data
    void sample(float sample)
    {
        audio_data.push_back(sample);
    }

    // Generate sine wave with given frequency
    // and add it to audio data (for given time)
    void generate_sin(float frequency, float amplitude, float duration)
    {
        for (int i = 0; i < duration * sample_rate; i++)
        {
            float sample = amplitude * sin(2 * M_PI * frequency * i / sample_rate);
            audio_data.push_back(sample);
        }
    }

    // Show range of audio data in console
    // from start to end (in seconds)
    void show_range(int start, int end)
    {
        for (int i = start; i < end; i++)
        {
            std::cout << audio_data[i] << std::endl;
        }
    }

    // Save audio data to wav file with 
    // path from constructor
    void save()
    {
        std::cout << "Saving file: " << file_path << std::endl;

        // open file in binary mode
        std::ofstream file(file_path, std::ios::binary);
        // write headers to file
        header.data_size = (char *)audio_data.size();
        write_headers(file);
        // write audio data to file
        file.write((char *)audio_data.data(), audio_data.size() * sizeof(float));
    }
};

int main()
{
    const char *filename = "test.wav";
    // Create new wav file
    WavFile file(filename, 44100, 1, 16);
    // Add some audio data
    file.generate_sin(440, 0.5, 1);
    file.show_range(0, 10);
    // Save file
    file.save();
    return 0;
}