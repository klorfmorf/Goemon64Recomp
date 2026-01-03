__start = 0x80000000;

/* Dummy addresses that get recompiled into function calls */
recomp_update_inputs = 0x8F000000;
recomp_puts = 0x8F000004;
recomp_exit = 0x8F000008;
recomp_get_gyro_deltas = 0x8F00000C;
recomp_get_mouse_deltas = 0x8F000010;
recomp_powf = 0x8F000014;
recomp_get_target_framerate = 0x8F000018;
recomp_get_window_resolution = 0x8F00001C;
recomp_get_target_aspect_ratio = 0x8F000020;
recomp_get_targeting_mode = 0x8F000024;
recomp_get_bgm_volume = 0x8F000028;
recomp_get_low_health_beeps_enabled = 0x8F00002C;
recomp_time_us = 0x8F000030;
recomp_get_autosave_enabled = 0x8F000034;
recomp_load_overlays = 0x8F000038;
recomp_unload_overlays = 0x8F00003C;
recomp_high_precision_fb_enabled = 0x8F000040;
recomp_get_resolution_scale = 0x8F000044;
recomp_get_inverted_axes = 0x8F000048;
recomp_get_analog_inverted_axes = 0x8F00004C;
recomp_get_analog_cam_enabled = 0x8F000050;
recomp_get_camera_inputs = 0x8F000054;
recomp_set_right_analog_suppressed = 0x8F000058;
recomp_run_ui_callbacks = 0x8F00005C;
