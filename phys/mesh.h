//
// open horizon -- undefined_darkness@outlook.com
//

#pragma once

#include "math/frustum.h"
#include "util/simd.h"
#include "memory/align_alloc.h"
#include <vector>

namespace phys
{
//------------------------------------------------------------

struct mesh
{
    nya_math::aabb bbox;

public:
    bool load(const void *data, size_t size);

    bool trace(const nya_math::vec3 &from, const nya_math::vec3 &to) const;
    bool trace(const nya_math::vec3 &from, const nya_math::vec3 &to, float &result) const;

private:
    struct pl { vec3_float4 p, lv, rv, v; };
    struct shape { std::vector<pl, nya_memory::aligned_allocator<pl,16> > pls; };
    std::vector<shape> m_shapes;
};

//------------------------------------------------------------
};
