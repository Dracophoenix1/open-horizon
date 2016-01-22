//
// open horizon -- undefined_darkness@outlook.com
//

#pragma once

#include "ui.h"

namespace gui
{
//------------------------------------------------------------

class hud
{
public:
    void load(const char *aircraft_name, const char *location_name);
    void draw(const render &r);
    void update(int dt);

    void set_location(const char *location_name);
    void set_hide(bool value) { m_hide = value; }
    void set_project_pos(const nya_math::vec3 &pos) { m_project_pos = pos; }
    void set_pos(const nya_math::vec3 &pos) { m_pos = pos; }
    void set_yaw(float yaw) { m_yaw = yaw; }
    void set_speed(int value) { m_speed = value; }
    void set_alt(int value) { m_alt = value; }
    void set_missiles(const char *id, int icon);
    void set_missile_reload(int idx, float value);
    void change_radar() { m_show_map = !m_show_map; }

    void clear_alerts() { m_alerts.clear(); }
    void add_alert(float v) { m_alerts.push_back(v); }

    enum target_type
    {
        target_air,
        target_air_lock,
        target_air_ally,
        target_missile
    };

    enum select_type
    {
        select_not,
        select_current,
        select_next
    };

    void clear_targets() { m_targets.clear(); }
    void add_target(const nya_math::vec3 &pos, float yaw, target_type target, select_type select);

    hud(): m_common_loaded(false), m_hide(false) {}

private:
    nya_math::vec3 m_project_pos;
    nya_math::vec3 m_pos;
    ivalue m_speed;
    fvalue m_yaw;
    ivalue m_alt;
    ivalue m_missiles_icon;
    ivalue m_missiles_cross;
    bvalue m_show_map;
    std::vector<float> m_alerts;

    struct target
    {
        nya_math::vec3 pos;
        float yaw;
        target_type t;
        select_type s;
    };

    std::vector<target> m_targets;

    ivalue m_anim_time;

private:
    bool m_common_loaded;
    bool m_hide;
    fonts m_fonts;
    tiles m_common;
    tiles m_aircraft;
    tiles m_location;
};

//------------------------------------------------------------
}
