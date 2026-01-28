#include "patches.h"
#include "sound_funcs.h"

typedef struct SOUND_W {
    u32 sequence_id;
    s8 priority;
    s8 initial_delay_counter;
    u8 flags;
    u8 unknown_4;
    u8 *sequence_data_needle;
    u8 bank;
    u8 sound;
    u8 voice_active;
    u8 voice_killed;
    s8 dry_wet_mix;
    s8 pad1;
    s8 pad2;
    s8 pad3;
    ALWaveTable* wave_table; // ALWaveTable changed!
    u16 tempo;
    u16 tempo_counter;
    u8 tempo_change_target;
    u8 tempo_change_duration;
    s16 tempo_change_amount;
    u8 previous_note_duration;
    u8 note_duration;
    u8 note_hold_ratio;
    u8 previous_note_hold_ratio;
    s8 note_hold_duration;
    u8 note_pitch;
    u8 unknown_22;
    u8 unknown_23;
    u32 pitch;
    s16 sound_transpose_detune;
    s16 effect_transpose;
    s16 effect_detune;
    s16 marker_transpose;
    s16 nested_marker_transpose;
    s16 vibrato_pitch;
    s16 random_pitch;
    u16 volume;
    u8 unknown_33;
    u8 unknown_34;
    u8 unknown_35;
    u8 unknown_36;
    s16 marker_volume;
    s16 nested_marker_volume;
    s16 volume_change_amount;
    u8 volume_change_target;
    u8 volume_change_duration;
    u8 note_velocity;
    u8 envelope_phase;
    u16 envelope_volume_target;
    u16 envelope_phase_duration;
    u16 envelope_attack_duration;
    u16 envelope_decay_duration;
    u16 envelope_sustain_duration;
    s16 envelope_decay_volume;
    u16 envelope_release_duration;
    u16 pan;
    u8 pan_change_target;
    u8 pan_change_duration;
    s16 pan_change_amount;
    s8 marker_loop_counter;
    u8 unknown_56;
    u8 *marker_needle;
    s8 nested_marker_loop_counter;
    u8 unknown_59;
    u8 unknown_60;
    u8 unknown_61;
    u8 *nested_marker_needle;
    u8 *master_marker_needle;
    s8 conditional_marker_flag;
    u8 unknown_65;
    u8 unknown_66;
    u8 unknown_67;
    u8 *conditional_marker_needle_1;
    u8 *conditional_marker_needle_2;
    s8 pitch_change_delay_duration;
    u8 pitch_change_duration;
    u8 unknown_72;
    u8 unknown_73;
    u32 pitch_change_target;
    s32 pitch_change_amount;
    u8 pitch_change_next_note_delay_duration;
    u8 pitch_change_next_note_duration;
    s16 pitch_change_next_note_parameter;
    u8 pitch_change_type;
    u8 random_index;
    u16 random_pitch_mask;
    u16 random_counter;
    u8 random_rate;
    u8 vibrato_intended_delay_duration;
    s8 vibrato_delay_duration;
    u8 vibrato_rate;
    u16 vibrato_counter;
    u8 vibrato_oscillation;
    u8 vibrato_oscillation_step_size;
    u16 vibrato_depth_target;
    u16 vibrato_depth;
    u8 vibrato_intended_start_duration;
    s8 vibrato_start_duration;
    u16 vibrato_depth_change_amount;
    u8 unknown_95;
    u8 unknown_96;
    f32 previous_pitch;
    s16 previous_volume;
    u16 previous_envelope_phase_duration;
    u8 disable;
    u8 unk_ad;
    u16 unk_ae;
} SOUND_W;

extern SOUND_W* D_801C1728_1C2328;

extern ALGlobals* D_8007A230_7AE30;      // alGlobals
extern ALVoice    D_801C0A68_1C1668[16];

extern unsigned char D_801C09CC_1C15CC;

extern unsigned char D_801C09D6_1C15D6;

extern unsigned char D_801C09D3_1C15D3;

extern unsigned char D_801C09DC_1C15DC;

extern unsigned char D_801C09CF_1C15CF;

extern u16 D_801C09E8_1C15E8[];

extern u8 D_801C09E0_1C15E0[];

#define CALLBACK_TIME 5000

#define VOLUME_IS_CHANGING (1 << 0)
#define PITCH_IS_CHANGING (1 << 1)
#define IS_DRUM (1 << 2)

RECOMP_PATCH void func_8003AFB0_3BBB0() // player_set_volume
{
    s32 intended_volume;
    s32 clamped_volume;
    s32 enveloped_volume;
    s32 final_volume;

    s32 var_v0;
    u16 *var_v1;
    u32 temp_t4;
    var_v1 = &D_801C09E8_1C15E8;

    D_801C1728_1C2328->flags &= ~VOLUME_IS_CHANGING;

    intended_volume = (D_801C1728_1C2328->note_velocity + D_801C1728_1C2328->marker_volume + D_801C1728_1C2328->nested_marker_volume) * D_801C1728_1C2328->volume;

    if (intended_volume >= 0x800000) {
        clamped_volume = 0x7FFF;
    } else if (intended_volume < 0) {
        clamped_volume = 0;
    } else {
        clamped_volume = intended_volume >> 8;
    }

    enveloped_volume = (D_801C1728_1C2328->envelope_volume_target * clamped_volume) >> 8;

    final_volume = enveloped_volume;

    if (D_801C1728_1C2328->unk_ae != 0) {
        final_volume = (D_801C1728_1C2328->unk_ae * enveloped_volume) >> 8;
    }

    if (D_801C09D6_1C15D6 != 0) {
        final_volume = (D_801C09D6_1C15D6 * final_volume) >> 8;
    }
    
    temp_t4 = D_801C1728_1C2328->sequence_id & 0x7FFF;
    if (temp_t4 < 0x100) {
        if (D_801C09D3_1C15D3 != 0) {
            final_volume = (D_801C09D3_1C15D3 * final_volume) >> 8;
        }

        if (D_801C09DC_1C15DC != 0) {
            final_volume = (D_801C09DC_1C15DC * final_volume) >> 8;
        }

        // @recomp Allow user to change the volume of the background music.
        final_volume = (recomp_get_bgm_volume() * (float) final_volume);
    }

    if (D_801C09CF_1C15CF != 0) {
        final_volume = (D_801C09CF_1C15CF * final_volume) >> 8;
    }

    for (var_v0 = 0; var_v0 < 4; var_v0++) {
        if (temp_t4 == var_v1[var_v0]) {
            final_volume = (D_801C09E0_1C15E0[var_v0] * final_volume) >> 8;
            break;
        }
    }

    if ((final_volume != D_801C1728_1C2328->previous_volume) || (D_801C1728_1C2328->envelope_phase_duration != D_801C1728_1C2328->previous_envelope_phase_duration)) {
        D_801C1728_1C2328->previous_volume = (s16) final_volume;
        D_801C1728_1C2328->previous_envelope_phase_duration = (u16) D_801C1728_1C2328->envelope_phase_duration;
        alSynSetVol(&D_8007A230_7AE30->drvr, &D_801C0A68_1C1668[D_801C09CC_1C15CC], final_volume, D_801C1728_1C2328->envelope_phase_duration * CALLBACK_TIME);
    }
}