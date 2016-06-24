//
// open horizon -- undefined_darkness@outlook.com
//

// acah base container

#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <stdint.h>

//------------------------------------------------------------

class qdf_archive
{
public:
    bool open(const char *name);
    void close();

    int get_files_count() const { return int(m_fis.size()); }
    const char *get_file_name(int idx) const;
    uint64_t get_file_size(int idx) const;
    uint64_t get_file_offset(int idx) const;
	uint64_t get_file_info_offset(int idx) const;
    int get_file_idx(const char *name) const;
    int find_file_idx(const char *name_part) const;

    bool read_file_data(int idx, void *data) const;
    bool read_file_data(int idx, void *data, uint64_t size, uint64_t offset = 0) const;

    uint64_t get_part_size() const { return m_part_size; }

    qdf_archive(): m_part_size(0) {}

private:
    struct qdf_file_info
    {
        std::string name;
        uint64_t offset;
        uint64_t size;

		uint64_t offset_to_info;
    };

    std::string m_arch_name;
    uint64_t m_part_size;
    std::vector<FILE *> m_rds;
    std::vector<qdf_file_info> m_fis;
};

//------------------------------------------------------------
