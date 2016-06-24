//
// open horizon -- undefined_darkness@outlook.com
//

// ac > 6 base container

#pragma once

#include "resources/resources.h"
#include "fhm.h"
#include <vector>
#include <stdint.h>

//------------------------------------------------------------

class dpl_file
{
public:
    bool open(const char *name);
    void close();

    int get_files_count() const { return (int)m_infos.size(); }
    uint32_t get_file_size(int idx) const;
    bool read_file_data(int idx, void *data) const;

    dpl_file(): m_data(0), m_archieved(false), m_byte_order(false) {}

private:
    struct info
    {
        fhm_file::fhm_header header;
        uint64_t offset;
        uint32_t size;
        uint32_t unpacked_size;
        unsigned char key;
    };

    std::vector<info> m_infos;
    nya_resources::resource_data *m_data;
    bool m_archieved;
    bool m_byte_order;
};

//------------------------------------------------------------
