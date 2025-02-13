#ifndef __GOEMON_CONFIG_H__
#define __GOEMON_CONFIG_H__

#include <filesystem>
#include <string_view>
#include "ultramodern/config.hpp"
#include "recomp_input.h"

namespace goemon64 {
    constexpr std::u8string_view program_id = u8"Goemon64Recompiled";
    constexpr std::string_view program_name = "Goemon 64: Recompiled";

    // TODO: Move loading configs to the runtime once we have a way to allow per-project customization.
    void load_config();
    void save_config();
    
    void reset_input_bindings();
    void reset_cont_input_bindings();
    void reset_kb_input_bindings();
    void reset_single_input_binding(recomp::InputDevice device, recomp::GameInput input);

    std::filesystem::path get_app_folder_path();
    
    bool get_debug_mode_enabled();
    void set_debug_mode_enabled(bool enabled);
    
    enum class AutosaveMode {
        On,
        Off,
        OptionCount
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(goemon64::AutosaveMode, {
        {goemon64::AutosaveMode::On, "On"},
        {goemon64::AutosaveMode::Off, "Off"}
    });

    enum class TargetingMode {
        Switch,
        Hold,
        OptionCount
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(goemon64::TargetingMode, {
        {goemon64::TargetingMode::Switch, "Switch"},
        {goemon64::TargetingMode::Hold, "Hold"}
    });

    TargetingMode get_targeting_mode();
    void set_targeting_mode(TargetingMode mode);

    enum class CameraInvertMode {
        InvertNone,
        InvertX,
        InvertY,
        InvertBoth,
        OptionCount
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(goemon64::CameraInvertMode, {
        {goemon64::CameraInvertMode::InvertNone, "InvertNone"},
        {goemon64::CameraInvertMode::InvertX, "InvertX"},
        {goemon64::CameraInvertMode::InvertY, "InvertY"},
        {goemon64::CameraInvertMode::InvertBoth, "InvertBoth"}
    });

    CameraInvertMode get_camera_invert_mode();
    void set_camera_invert_mode(CameraInvertMode mode);

    CameraInvertMode get_analog_camera_invert_mode();
    void set_analog_camera_invert_mode(CameraInvertMode mode);

    enum class AnalogCamMode {
        On,
        Off,
		OptionCount
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(goemon64::AnalogCamMode, {
        {goemon64::AnalogCamMode::On, "On"},
        {goemon64::AnalogCamMode::Off, "Off"}
    });

    AutosaveMode get_autosave_mode();
    void set_autosave_mode(AutosaveMode mode);

    AnalogCamMode get_analog_cam_mode();
    void set_analog_cam_mode(AnalogCamMode mode);

    void open_quit_game_prompt();
};

#endif
