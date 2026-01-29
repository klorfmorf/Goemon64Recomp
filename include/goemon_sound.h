#ifndef __GOEMON_SOUND_H__
#define __GOEMON_SOUND_H__

namespace goemon64 {
    void reset_sound_settings();
    void set_main_volume(int volume);
    int get_main_volume();
    void set_bgm_volume(int volume);
    void set_se_volume(int volume);
    int get_bgm_volume();
    int get_se_volume();
}

#endif
