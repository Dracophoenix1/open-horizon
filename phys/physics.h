//
// open horizon -- undefined_darkness@outlook.com
//

#pragma once

#include "plane_params.h"
#include "math/quaternion.h"
#include "math/quadtree.h"
#include "mesh.h"
#include <functional>
#include <vector>
#include <memory>

namespace phys
{
//------------------------------------------------------------

typedef nya_math::vec3 vec3;
typedef nya_math::quat quat;
typedef params::fvalue fvalue;
typedef params::value<int> ivalue;
typedef params::value<bool> bvalue;

//------------------------------------------------------------

template <typename t> using ptr = std::shared_ptr<t>;

//------------------------------------------------------------

struct object
{
    vec3 pos;
    quat rot;
    vec3 vel;
};

typedef ptr<object> object_ptr;

typedef std::function<void(const object_ptr &a, const object_ptr &b)> hit_hunction;

//------------------------------------------------------------

struct plane_controls
{
    vec3 rot;
    fvalue throttle;
    fvalue brake;
};

//------------------------------------------------------------

struct plane: public object
{
    fvalue thrust_time;
    vec3 rot_speed;

    plane_controls controls;
    plane_params params;
    //col_mesh mesh;

    void reset_state();
    void update(int dt);
};

typedef ptr<plane> plane_ptr;

//------------------------------------------------------------

struct missile: public object
{
    ivalue no_accel_time;
    fvalue gravity;
    fvalue accel;
    fvalue speed_init;
    fvalue max_speed;
    bvalue accel_started;

    fvalue rot_max;
    fvalue rot_max_low;
    fvalue rot_max_hi;

    vec3 target_dir;

    void update(int dt);
};

typedef ptr<missile> missile_ptr;

//------------------------------------------------------------

struct bullet
{
    nya_math::vec3 pos;
    nya_math::vec3 vel;
    int time;
};

//------------------------------------------------------------

class world
{
public:
    void set_location(const char *name);

    plane_ptr add_plane(const char *name, bool add_to_world);
    missile_ptr add_missile(const char *name);

    void spawn_bullet(const char *type, const nya_math::vec3 &pos, const nya_math::vec3 &dir);

    void update_planes(int dt, hit_hunction on_hit);
    void update_missiles(int dt, hit_hunction on_hit);
    void update_bullets(int dt, hit_hunction on_hit);

    const std::vector<bullet> &get_bullets() const { return m_bullets; }

    float get_height(float x, float z) const;

private:
    std::vector<plane_ptr> m_planes;
    std::vector<missile_ptr> m_missiles;
    std::vector<bullet> m_bullets;

    const static unsigned int location_size = 16;
    unsigned char m_height_patches[location_size * location_size];
    std::vector<float> m_heights;

    std::vector<mesh> m_meshes;

    struct instance
    {
        int mesh_idx = -1;
        nya_math::vec3 pos;
        float yaw_s, yaw_c = 0.0f;
        nya_math::aabb bbox;

    public:
        nya_math::vec3 transform(const nya_math::vec3 &v) const;
        nya_math::vec3 transform_inv(const nya_math::vec3 &v) const;
    };

    std::vector<instance> m_instances;
    nya_math::quadtree m_qtree;
};

//------------------------------------------------------------
}
