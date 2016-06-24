//
// open horizon -- undefined_darkness@outlook.com
//

#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <string.h>

namespace sound
{
//------------------------------------------------------------

class hsa_bit_stream;

//------------------------------------------------------------

class file
{
public:
    bool load(const void *data, size_t size);

    void limit_channels(int count);

    unsigned int get_length() const;
    unsigned int get_loop_start() const;
    unsigned int get_freq() const;
    bool is_stereo() const;

    //stream
public:
    size_t get_buf_size() const;
    size_t cache_buf(void *data, unsigned int buf_idx, bool loop) const; //returns actually cached size

    //cache into audio system
public:
    typedef std::function<unsigned int(const void *data, size_t size)> as_create_buf;
    typedef std::function<void(unsigned int)> as_free_buf;

    bool cache(const as_create_buf &c, const as_free_buf &f);
    unsigned int get_cached_id() const;

private:
    bool load_hca(const void *data, size_t size);

    struct hca_data
    {
        uint16_t version = 0;
        uint32_t samples_per_second = 0;
        uint32_t block_count = 0;
        uint16_t block_size = 0;
        uint16_t loop_fine = 0;
        uint32_t loop_start = 0, loop_end = 0;
        std::vector<char> raw_data;

        int limit_channels = 2;

        void decode(hsa_bit_stream &data);

        struct channel
        {
            float block[0x80];
            float base[0x80];
            char value[0x80];
            char scale[0x80];
            char value2[8];
            int count;

            float sample1[0x80];
            float sample2[0x80];
            float sample3[0x80];
            float samples[8][0x80];

            void decode1(hsa_bit_stream &data, int t);
            void decode2(hsa_bit_stream &data);
            void decode5(int index);

            channel() { memset(this, 0, sizeof(channel)); }
        };

        std::vector<channel> channels;
    };

    std::shared_ptr<hca_data> m_hca_data;

    struct cached
    {
        unsigned int id = 0;
        unsigned int length = 0;
        unsigned int loop_start = 0;
        unsigned int channels = 0;
        unsigned int freq = 0;

        as_free_buf on_free;

        ~cached() { if (id && on_free) on_free(id); }
    };

    std::shared_ptr<cached> m_cached;
};

//------------------------------------------------------------
}
