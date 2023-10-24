#include "globals.h"

#include "types.h"
#include "types_directx.h"

// This file is auto-generated by scripts/GenerateGlobalHeaderFromSymbols.py and data_symbols.syms
// using Jinja template globals.h.j2

// Line 0: diDataFormat 0x0049e720 DIDATAFORMAT
DIDATAFORMAT diDataFormat ;

// Line 2: A3dApi_GUID 0x004ae0e8 GUID
GUID A3dApi_GUID ;

// Line 3: IID_Ia3d4_GUID 0x004ae128 GUID
GUID IID_Ia3d4_GUID ;

// Line 4: IID_IA3dListener_GUID 0x004ae158 GUID
GUID IID_IA3dListener_GUID ;

// Line 6: iDirectDraw4_GUID 0x004af1c8 GUID
GUID iDirectDraw4_GUID ;

// Line 7: iDirect3D3_GUID 0x004af278 GUID
GUID iDirect3D3_GUID ;

// Line 9: IID_IDirectPlay4_GUID 0x004af4a8 GUID
GUID IID_IDirectPlay4_GUID ;

// Line 10: DirectPlay_GUID 0x004af4c8 GUID
GUID DirectPlay_GUID ;

// Line 12: Window_UUID 0x004af9b0 uint32_t[4] = { 0xC95FB584, 0x11D2FA31, 0xAA009D90, 0xAD22A300 }
uint32_t Window_UUID[4]   = { 0xC95FB584, 0x11D2FA31, 0xAA009D90, 0xAD22A300 };

// Line 14: rdMatrix34_identity 0x004af880 rdMatrix34 = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}}
rdMatrix34  rdMatrix34_identity  = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}};

// Line 16: swrConfig_joystick_enabled 0x004b2944 int = 1
int  swrConfig_joystick_enabled  = 1;

// Line 17: swrConfig_keyboard_enabled 0x004b2948 int = 1
int  swrConfig_keyboard_enabled  = 1;

// Line 18: joystick_detected 0x004b294c int = 1
int  joystick_detected  = 1;

// Line 20: direct3d_LensFlareCompatible 0x004b431c int
int direct3d_LensFlareCompatible ;

// Line 22: swrConfig_defaultVideoConfig 0x004b4330 int[9] = { 0, 0, 0, 0, 0, 0, 1, 3, 2};
int swrConfig_defaultVideoConfig[9]   = { 0, 0, 0, 0, 0, 0, 1, 3, 2};;

// Line 24: Main_force_feedback 0x004b4938 int = 1
int  Main_force_feedback  = 1;

// Line 26: iDirectDraw4_error 0x004b4758 int
int iDirectDraw4_error ;

// Line 28: swrUI_unk_ptr 0x004b5d74 swrUI_unk*
swrUI_unk* swrUI_unk_ptr ;

// Line 30: Main_nut_delay_ms 0x004b6718 int = 32
int  Main_nut_delay_ms  = 32;

// Line 31: Main_hiRes_sound 0x004b6d14 int = 1
int  Main_hiRes_sound  = 1;

// Line 32: Main_doppler_sound 0x004b6d18 int = 0
int  Main_doppler_sound  = 0;

// Line 33: Main_sound 0x004b6d20 int = 1
int  Main_sound  = 1;

// Line 34: Main_sound_gain_adjust 0x004b6d24 float
float Main_sound_gain_adjust ;

// Line 35: swrRace_voices_enabled 0x004b6d28 int = 1
int  swrRace_voices_enabled  = 1;

// Line 36: Main_sound_unk 0x004b6d2c int = 1
int  Main_sound_unk  = 1;

// Line 37: Main_fullscreen_unk 0x004b79f8 int = 1
int  Main_fullscreen_unk  = 1;

// Line 38: Main_display_intro_scene 0x004b7a00 int = 1
int  Main_display_intro_scene  = 1;

// Line 40: swrSound_criticalSection 0x004b7e7e CRITICAL_SECTION
CRITICAL_SECTION swrSound_criticalSection ;

// Line 42: swrSprite_SpriteCount 0x004b91b8 int
int swrSprite_SpriteCount ;

// Line 43: swrSprite_unk_x 0x004b91bc float = 16.0
float  swrSprite_unk_x  = 16.0;

// Line 44: swrSprite_unk_y 0x004b91c0 float = 155.0
float  swrSprite_unk_y  = 155.0;

// Line 46: rdVector_negZ 0x004c2598 rdVector3 = {0.0, 0.0, -1.0}
rdVector3  rdVector_negZ  = {0.0, 0.0, -1.0};

// Line 48: ai_antiskid 0x004c3114 float
float ai_antiskid ;

// Line 49: ai_turn_response 0x004c3118 float
float ai_turn_response ;

// Line 50: ai_max_turn_rate 0x004c311c float
float ai_max_turn_rate ;

// Line 51: ai_acceleration 0x004c3120 float
float ai_acceleration ;

// Line 52: ai_max_speed 0x004c3124 float
float ai_max_speed ;

// Line 53: ai_air_brake_interval 0x004c3128 float
float ai_air_brake_interval ;

// Line 54: ai_deceleration_interval 0x004c312c float
float ai_deceleration_interval ;

// Line 55: ai_boost_thrust 0x004c3130 float
float ai_boost_thrust ;

// Line 56: ai_heat_rate 0x004c3134 float
float ai_heat_rate ;

// Line 57: ai_cool_rate 0x004c3138 float
float ai_cool_rate ;

// Line 58: ai_hover_height 0x004c313c float
float ai_hover_height ;

// Line 59: ai_repair_rate 0x004c3140 float
float ai_repair_rate ;

// Line 60: ai_bump_mass 0x004c3144 float
float ai_bump_mass ;

// Line 61: ai_damage_immunity 0x004c3148 float
float ai_damage_immunity ;

// Line 62: ai_intersect_radius 0x004c314c float
float ai_intersect_radius ;

// Line 65: rdMatrixStack34_modified 0x004c3c0c int
int rdMatrixStack34_modified ;

// Line 67: rdMatrix_unk5 0x004c3c38 rdMatrix44 = {{-1.0 / 6.0, 0.5, -0.5, 1.0 / 6.0}, {0.5, -1.0, 0.5, 0.0}, {-0.5, 0.0, 0.5, 0.0}, {1.0 /6.0, 2.0 / 3.0, 1.0 / 6.0, 0.0}}
rdMatrix44  rdMatrix_unk5  = {{-1.0 / 6.0, 0.5, -0.5, 1.0 / 6.0}, {0.5, -1.0, 0.5, 0.0}, {-0.5, 0.0, 0.5, 0.0}, {1.0 /6.0, 2.0 / 3.0, 1.0 / 6.0, 0.0}};

// Line 68: rdMatrix_unk3 0x004c3c78 rdMatrix44 = {{0.0, 0.0, 0.0, 0.0}, {-0.5, 1.5, -1.5, 0.5}, {1.0, -2.0, 1.0, 0.0}, {-0.5, 0.0, 0.5, 0.0}}
rdMatrix44  rdMatrix_unk3  = {{0.0, 0.0, 0.0, 0.0}, {-0.5, 1.5, -1.5, 0.5}, {1.0, -2.0, 1.0, 0.0}, {-0.5, 0.0, 0.5, 0.0}};

// Line 69: rdMatrix_unk1 0x004c3cb8 rdMatrix44 = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {-1.0, 3.0, -3.0, 1.0}, {1.0, -2.0, 1.0, 0.0}}
rdMatrix44  rdMatrix_unk1  = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {-1.0, 3.0, -3.0, 1.0}, {1.0, -2.0, 1.0, 0.0}};

// Line 70: rdMatrix_unk6 0x004c3cf8 rdMatrix44 = {{-1.0, 3.0, -3.0, 1.0}, {3.0, -6.0, 3.0, 0.0}, {-3.0, 3.0, 0.0, 0.0}, {1.0, 0.0, 0.0, 0.0}}
rdMatrix44  rdMatrix_unk6  = {{-1.0, 3.0, -3.0, 1.0}, {3.0, -6.0, 3.0, 0.0}, {-3.0, 3.0, 0.0, 0.0}, {1.0, 0.0, 0.0, 0.0}};

// Line 71: rdMatrix_unk4 0x004c3d38 rdMatrix44 = {{0.0, 0.0, 0.0, 0.0}, {-3.0, 9.0, -9.0, 3.0}, {6.0, -12.0, 6.0, 0.0}, {-3.0, 3.0, 0.0, 0.0}}
rdMatrix44  rdMatrix_unk4  = {{0.0, 0.0, 0.0, 0.0}, {-3.0, 9.0, -9.0, 3.0}, {6.0, -12.0, 6.0, 0.0}, {-3.0, 3.0, 0.0, 0.0}};

// Line 72: rdMatrix_unk2 0x004c3d78 rdMatrix44 = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {-6.0, 18.0, -18.0, 6.0}, {6.0, -12.0, 6.0, 0.0}}
rdMatrix44  rdMatrix_unk2  = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {-6.0, 18.0, -18.0, 6.0}, {6.0, -12.0, 6.0, 0.0}};

// Line 74: ai_level 0x004c707c float
float ai_level ;

// Line 75: ai_spread 0x004c7080 float
float ai_spread ;

// Line 77: Main_sound_3dimpact 0x004c7aa8 int = -1
int  Main_sound_3dimpact  = -1;

// Line 79: death_speedMin 0x004c7bb8 float
float death_speedMin ;

// Line 80: death_speedDrop 0x004c7bbc float
float death_speedDrop ;

// Line 82: Main_sound_gain_const 0x004c7d70 float = 0.8
float  Main_sound_gain_const  = 0.8;

// Line 83: Main_sound_doppler_scale 0x004c7d74 float = 1.0
float  Main_sound_doppler_scale  = 1.0;

// Line 84: Main_sound_rolloff 0x004c7d78 float = 0.15
float  Main_sound_rolloff  = 0.15;

// Line 85: Main_sound_gain 0x004c7d7c float = 1.0
float  Main_sound_gain  = 1.0;

// Line 87: swrRace_AILevel 0x004c707c int
int swrRace_AILevel ;

// Line 89: swrRace_DeathSpeedMin 0x004c7bb8 float = 325.00
float  swrRace_DeathSpeedMin  = 325.00;

// Line 90: swrRace_DeathSpeedDrop 0x004c7bbc float = 140.0
float  swrRace_DeathSpeedDrop  = 140.0;

// Line 92: swrRace_FireTimer 0x004c7bc0 float = -1.0
float  swrRace_FireTimer  = -1.0;

// Line 94: DirectDraw_CooperativeLevel 0x004c86bc int
int DirectDraw_CooperativeLevel ;

// Line 95: directDraw_BltFillColor 0x004c86c0 int
int directDraw_BltFillColor ;

// Line 97: d3d_FogEnabled 0x004c98b0 int = 1
int  d3d_FogEnabled  = 1;

// Line 98: d3d_CurrentScene 0x004c98b4 int = 1 
int  d3d_CurrentScene  = 1 ;

// Line 100: stdMath_SinTable 0x004c98e8 float[4096]
float stdMath_SinTable[4096] ;

// Line 101: stdMath_TanTable 0x004cd8e8 float[4096]
float stdMath_TanTable[4096] ;

// Line 103: wuRegistry_lpClass 0x004d55cc LPSTR
LPSTR wuRegistry_lpClass ;

// Line 105: multiplayer_enabled 0x004d5e00 int
int multiplayer_enabled ;

// Line 107: swrText_keyNameText 0x004d5f38 char[128]
char swrText_keyNameText[128] ;

// Line 109: swrConfig_mouse_enabled 0x004d6b38 int
int swrConfig_mouse_enabled ;

// Line 111: rdLight_1 0x004d6b78 rdLight
rdLight rdLight_1 ;

// Line 112: rdLight_2 0x004d6ba8 rdLight
rdLight rdLight_2 ;

// Line 114: directDrawSurface4_ptr2 0x004d6be0 LPDIRECTDRAWSURFACE4
LPDIRECTDRAWSURFACE4 directDrawSurface4_ptr2 ;

// Line 115: ddSurfaceDesc_2 0x004d6be4 DDSURFACEDESC
DDSURFACEDESC ddSurfaceDesc_2 ;

// Line 117: swrSpriteTexItems 0x004d7c68 swrSpriteTexItem[149]
swrSpriteTexItem swrSpriteTexItems[149] ;

// Line 119: multiplayer_in_mp 0x004d87a0 int
int multiplayer_in_mp ;

// Line 121: swrUI_unk_array 0x004d8110 swrUI_unk[20]
swrUI_unk swrUI_unk_array[20] ;

// Line 123: swrUI_unk_array_count 0x004d87a4 int
int swrUI_unk_array_count ;

// Line 125: time_buffer 0x004e9f20 char[256]
char time_buffer[256] ;

// Line 127: multiplayer_sync_timer_ms 0x004eb230 int
int multiplayer_sync_timer_ms ;

// Line 129: multiplayer_race_button_toggle 0x004eb238 int
int multiplayer_race_button_toggle ;

// Line 131: multiplayer_track_change_permission 0x004eb388 int
int multiplayer_track_change_permission ;

// Line 133: playerNumber 0x004eb3b4 int
int playerNumber ;

// Line 135: swrText_racerTab_array 0x004eb3c4 char**
char** swrText_racerTab_array ;

// Line 136: swrText_racerTab_buffer 0x004eb3c8 char*
char* swrText_racerTab_buffer ;

// Line 138: swrText_nbLinesRacerTab 0x004eb3cc int
int swrText_nbLinesRacerTab ;

// Line 140: ia3dSourceThreadId 0x004eb3f8 DWORD
DWORD ia3dSourceThreadId ;

// Line 141: ia3dSourceEventHandle 0x004eb3fc HANDLE
HANDLE ia3dSourceEventHandle ;

// Line 142: ia3dSourceEventHandle2 0x004eb400 HANDLE
HANDLE ia3dSourceEventHandle2 ;

// Line 144: iA3DSource_ptr 0x004eb414 IA3dSource*
IA3dSource* iA3DSource_ptr ;

// Line 146: swrRace_music_enabled 0x004eb45c int
int swrRace_music_enabled ;

// Line 148: ia3dSourceThreadHandle 0x004eb478 HANDLE
HANDLE ia3dSourceThreadHandle ;

// Line 149: ia3d_thread_running 0x004eb47c int
int ia3d_thread_running ;

// Line 151: iDirectDrawSurface_ptr3 0x004eb480 LPDIRECTDRAWSURFACE
LPDIRECTDRAWSURFACE iDirectDrawSurface_ptr3 ;

// Line 152: ddSurfaceDesc_3 0x004eb484 DDSURFACEDESC
DDSURFACEDESC ddSurfaceDesc_3 ;

// Line 154: swrMain_initialized 0x0050b5a0 int
int swrMain_initialized ;

// Line 156: array_classes_unk_counter 0x0050b5ec int
int array_classes_unk_counter ;

// Line 158: rdVector_sound_pos 0x0050b5f0 rdVector4
rdVector4 rdVector_sound_pos ;

// Line 160: Main_settings_RegFullScreen 0x0050b560 int
int Main_settings_RegFullScreen ;

// Line 161: Main_settings_RegFixFlicker 0x0050b564 int
int Main_settings_RegFixFlicker ;

// Line 162: Main_settings_RegDevMode 0x0050b568 int
int Main_settings_RegDevMode ;

// Line 163: Main_settings_RegUseFett 0x0050b56c int
int Main_settings_RegUseFett ;

// Line 165: Main_hWnd 0x0050b59c HWND 
HWND  Main_hWnd ;

// Line 167: Main_settings_menu_only 0x0050b5b0 int
int Main_settings_menu_only ;

// Line 168: Main_settings_debug_hud 0x0050b5c0 int
int Main_settings_debug_hud ;

// Line 170: swrSprite_unk1_r 0x0050b704 char
char swrSprite_unk1_r ;

// Line 171: swrSprite_unk1_g 0x0050b705 char
char swrSprite_unk1_g ;

// Line 172: swrSprite_unk1_b 0x0050b706 char
char swrSprite_unk1_b ;

// Line 173: swrSprite_unk1_a 0x0050b707 char
char swrSprite_unk1_a ;

// Line 174: swrSprite_unk2_r 0x0050b708 char
char swrSprite_unk2_r ;

// Line 175: swrSprite_unk2_g 0x0050b709 char
char swrSprite_unk2_g ;

// Line 176: swrSprite_unk2_b 0x0050b70a char
char swrSprite_unk2_b ;

// Line 177: swrSprite_unk2_a 0x0050b70b char
char swrSprite_unk2_a ;

// Line 179: swrRace_DebugLevel 0x0050c040 int
int swrRace_DebugLevel ;

// Line 180: swrRace_DebugMenu 0x0050c044 int 
int  swrRace_DebugMenu ;

// Line 181: swrRace_DebugFlag 0x0050c048 char 
char  swrRace_DebugFlag ;

// Line 183: swrLoader_sprite_file 0x0050c08c FILE*
FILE* swrLoader_sprite_file ;

// Line 184: swrLoader_spline_file 0x0050c090 FILE*
FILE* swrLoader_spline_file ;

// Line 185: swrLoader_texture_file 0x0050c094 FILE*
FILE* swrLoader_texture_file ;

// Line 186: swrLoader_model_file 0x0050c098 FILE*
FILE* swrLoader_model_file ;

// Line 188: swrRace_SelectedRacer 0x0050c118 int
int swrRace_SelectedRacer ;

// Line 190: alpha_unk 0x0050c2e8 float
float alpha_unk ;

// Line 191: gamma_unk 0x0050c2ec float
float gamma_unk ;

// Line 193: swrRace_TournamentTrugutGain 0x0050c53c int
int swrRace_TournamentTrugutGain ;

// Line 195: nb_AI_racers 0x0050c558 int
int nb_AI_racers ;

// Line 197: rdMatrixStack44_size 0x0050c5e8 int
int rdMatrixStack44_size ;

// Line 199: swrSound_Orientation1 0x0050c648 rdVector4
rdVector4 swrSound_Orientation1 ;

// Line 200: swrSound_Orientation2 0x0050c658 rdVector4
rdVector4 swrSound_Orientation2 ;

// Line 201: swrSound_Position 0x0050c668 rdVector4
rdVector4 swrSound_Position ;

// Line 203: swrSound_unk_init 0x0050c68c int
int swrSound_unk_init ;

// Line 204: swrSound_Velocity 0x0050c690 rdVector3
rdVector3 swrSound_Velocity ;

// Line 206: IA3dSource2_ptr 0x0050c6a0 IA3dSource*
IA3dSource* IA3dSource2_ptr ;

// Line 207: IA3dSource3_ptr 0x0050c6a4 IA3dSource*
IA3dSource* IA3dSource3_ptr ;

// Line 209: swr_unk1_ptr 0x0050c6b0 swr_unk1*
swr_unk1* swr_unk1_ptr ;

// Line 211: rdVector_unk5 0x0050c6e8 rdVector3
rdVector3 rdVector_unk5 ;

// Line 213: rdMatrixStack34_size 0x0050c6f4 int
int rdMatrixStack34_size ;

// Line 215: debug_showSurfaceFlags 0x0050c88c int
int debug_showSurfaceFlags ;

// Line 217: debug_showSplineMarkers 0x0050ca24 int
int debug_showSplineMarkers ;

// Line 218: swrRace_IsInvincible 0x0050ca28 int
int swrRace_IsInvincible ;

// Line 220: swr_systemTimeMs 0x0050cb60 DWORD
DWORD swr_systemTimeMs ;

// Line 222: swr_FastMode 0x0050cb68 int
int swr_FastMode ;

// Line 224: debug_buffer 0x0050cd18 char[2048]
char debug_buffer[2048] ;

// Line 226: stdPlatform_hostServices_initialized 0x0050d518 int
int stdPlatform_hostServices_initialized ;

// Line 228: a3dCaps_hardware 0x0050d520 A3DCAPS_HARDWARE
A3DCAPS_HARDWARE a3dCaps_hardware ;

// Line 229: a3dOutputGain 0x0050d544 float
float a3dOutputGain ;

// Line 230: IA3d4_ptr 0x0050d548 IA3d4*
IA3d4* IA3d4_ptr ;

// Line 232: Sound_enabled_3d 0x0050d550 int
int Sound_enabled_3d ;

// Line 234: IA3dListener_ptr 0x0050d560 IA3dListener*
IA3dListener* IA3dListener_ptr ;

// Line 236: DirectInputKeyboards 0x0050d658 void*
void* DirectInputKeyboards ;

// Line 238: iDirectInputDeviceA_ptr 0x0050d89c LPDIRECTINPUTDEVICEA
LPDIRECTINPUTDEVICEA iDirectInputDeviceA_ptr ;

// Line 240: DirectInput_initialized 0x0050fea8 int
int DirectInput_initialized ;

// Line 242: iDirectInputA_ptr 0x0050feb8 LPDIRECTINPUTA
LPDIRECTINPUTA iDirectInputA_ptr ;

// Line 243: DirectInputNbKeyboard 0x00febc int 
int  DirectInputNbKeyboard ;

// Line 245: DirectInputNbMouses 0x0050fec0 int 
int  DirectInputNbMouses ;

// Line 247: DirectInputNbJoysticks 0x0050fec8 int 
int  DirectInputNbJoysticks ;

// Line 248: DirectInputTimeMs 0x0050fecc int
int DirectInputTimeMs ;

// Line 249: DirectInputPreviousTimeMs 0x0050fed0 int
int DirectInputPreviousTimeMs ;

// Line 251: DirectInputDeltaTimeMs 0x0050fed8 int
int DirectInputDeltaTimeMs ;

// Line 253: iDirectPlay4_ptr 0x00510254 IDirectPlay4*
IDirectPlay4* iDirectPlay4_ptr ;

// Line 255: swrConfig_filename 0x005138b8 char[0x80]
char swrConfig_filename[0x80] ;

// Line 257: swrConfig_buffer3 0x005143d8 char[0x80]
char swrConfig_buffer3[0x80] ;

// Line 259: swrConfig_buffer 0x00528500 char[0x1000]
char swrConfig_buffer[0x1000] ;

// Line 261: swrConfig_file_ready 0x00529500 int
int swrConfig_file_ready ;

// Line 263: swrConfig_file2 0x00529504 FILE*
FILE* swrConfig_file2 ;

// Line 264: swrConfig_file 0x00529508 FILE*
FILE* swrConfig_file ;

// Line 266: swrMain_fontHandle 0x00529510 HFONT
HFONT swrMain_fontHandle ;

// Line 267: directDrawSelectedDevice 0x00529514 int
int directDrawSelectedDevice ;

// Line 269: directDraw_FontWidth 0x0052951c int
int directDraw_FontWidth ;

// Line 270: directDraw_FontHeight_unused 0x00529520 int
int directDraw_FontHeight_unused ;

// Line 272: iDirectDrawSurface_ptr 0x00529578 LPDIRECTDRAWSURFACE
LPDIRECTDRAWSURFACE iDirectDrawSurface_ptr ;

// Line 273: _ddSurfaceDesc 0x0052957c DDSURFACEDESC2
DDSURFACEDESC2 _ddSurfaceDesc ;

// Line 274: swrDisplayModes 0x005295f8 swrDisplayMode[32]
swrDisplayMode swrDisplayModes[32] ;

// Line 276: swrDrawDevicesArray 0x0052a9f8 swrDrawDevice[16]
swrDrawDevice swrDrawDevicesArray[16] ;

// Line 278: directDrawInitialized 0x0052d438 int
int directDrawInitialized ;

// Line 279: directDrawDisplayModesReady 0x0052d43c int
int directDrawDisplayModesReady ;

// Line 281: directDrawSurfacesInitialized 0x0052d440 int
int directDrawSurfacesInitialized ;

// Line 282: directDrawNbDevices 0x0052d444 int
int directDrawNbDevices ;

// Line 284: directDrawNbDisplayModes 0x0052d44c int
int directDrawNbDisplayModes ;

// Line 286: iDirectDraw4 0x0052d454 LPDIRECTDRAW
LPDIRECTDRAW iDirectDraw4 ;

// Line 288: directDrawSpecialDeviceId 0x0052d45c int
int directDrawSpecialDeviceId ;

// Line 290: d3dDeviceDesc 0x0052d460 D3DDEVICEDESC
D3DDEVICEDESC d3dDeviceDesc ;

// Line 292: swrNb3DDevices 0x0052d56c int
int swrNb3DDevices ;

// Line 293: swr3DTextureFormats 0x0052d570 swr3DTextureFormat[8]
swr3DTextureFormat swr3DTextureFormats[8] ;

// Line 295: swr3DDevices 0x0052d870 swr3DDevice[4]
swr3DDevice swr3DDevices[4] ;

// Line 296: d3dRenderState 0x0052e610 unsigned int
unsigned int d3dRenderState ;

// Line 297: d3dMipFilter 0x0052e614 unsigned int
unsigned int d3dMipFilter ;

// Line 299: Direct3D_NbTextureFormats 0x0052e61c int
int Direct3D_NbTextureFormats ;

// Line 301: Direct3DFoundValidTextureFormat 0x0052e620 int
int Direct3DFoundValidTextureFormat ;

// Line 302: d3dMaxVertices 0x0052d624 unsigned int
unsigned int d3dMaxVertices ;

// Line 303: d3dCurrentTexture 0x0052e628 IDirect3DTexture2*
IDirect3DTexture2* d3dCurrentTexture ;

// Line 305: iDirectDraw4_2 0x0052e638 LPDIRECTDRAW
LPDIRECTDRAW iDirectDraw4_2 ;

// Line 306: iDirectDrawPalette_ptr 0x0052e63c LPDIRECTDRAWPALETTE
LPDIRECTDRAWPALETTE iDirectDrawPalette_ptr ;

// Line 307: iDirect3D3_ptr 0x0052e640 LPDIRECT3D3
LPDIRECT3D3 iDirect3D3_ptr ;

// Line 308: iDirect3DDevice3_ptr 0x0052e644 LPDIRECT3DDEVICE3
LPDIRECT3DDEVICE3 iDirect3DDevice3_ptr ;

// Line 309: iDirect3DViewport_ptr 0x0052e648 IDirect3DViewport3*
IDirect3DViewport3* iDirect3DViewport_ptr ;

// Line 310: direct3DInterfaceInitialized 0x0052e64c int 
int  direct3DInterfaceInitialized ;

// Line 312: stdFilePrintf_buffer 0x0052e658 char[0x800]
char stdFilePrintf_buffer[0x800] ;

// Line 314: Window_GUID 0x0052ee60 GUID
GUID Window_GUID ;

// Line 315: Window_hWnd 0x0052ee70 HWND
HWND Window_hWnd ;

// Line 316: Window_hinstance 0x0052ee74 HINSTANCE
HINSTANCE Window_hinstance ;

// Line 318: stdConsole_hConsoleOutput 0x0052ee78 HANDLE
HANDLE stdConsole_hConsoleOutput ;

// Line 319: stdConsole_wAttributes 0x0052ee7c WORD
WORD stdConsole_wAttributes ;

// Line 321: daAlloc_struct 0x0052ee98 void*
void* daAlloc_struct ;

// Line 323: swrRenders 0x005330c0 swrRenderUnk[1024]
swrRenderUnk swrRenders[1024] ;

// Line 325: swr_RenderState 0x006830c8 unsigned int
unsigned int swr_RenderState ;

// Line 327: swrNbRenders 0x00af30d8 int 
int  swrNbRenders ;

// Line 329: d3d_IndexBuffer 0x00af30e8 WORD[2] 
WORD d3d_IndexBuffer[2]  ;

// Line 331: d3d_VertexBuffer 0x00b6b0e8 void* 
void*  d3d_VertexBuffer ;

// Line 333: rdCamera_camRotation 0x00df7f20 rdVector3
rdVector3 rdCamera_camRotation ;

// Line 334: rdCamera_pCurCamera 0x00df7f2c rdCamera*
rdCamera* rdCamera_pCurCamera ;

// Line 335: bRDroidStartup 0x00df7f30 int
int bRDroidStartup ;

// Line 337: g_hWnd 0x00dfaa28 HWND
HWND g_hWnd ;

// Line 338: g_nCmdShow 0x00dfaa2c int
int g_nCmdShow ;

// Line 339: g_WndProc 0x00dfaa30 Window_MSGHANDLER_ptr
Window_MSGHANDLER_ptr g_WndProc ;

// Line 340: Window_width 0x00dfaa34 int
int Window_width ;

// Line 341: Window_height 0x00dfaa38 int
int Window_height ;

// Line 342: wuRegistry_bInitted 0x00dfaa3c int
int wuRegistry_bInitted ;

// Line 343: wuRegistry_lpSubKey 0x00dfaa40 LPCSTR
LPCSTR wuRegistry_lpSubKey ;

// Line 344: wuRegistry_hKey 0x00dfaa44 HKEY
HKEY wuRegistry_hKey ;

// Line 346: translation_unk 0x00e996c0 rdVector3
rdVector3 translation_unk ;

// Line 347: rotation_unk 0x00e996cc rdVector3
rdVector3 rotation_unk ;

// Line 349: rdMatrix_unk7 0x00e9ba44 rdMatrix44
rdMatrix44 rdMatrix_unk7 ;

// Line 351: swrSprite_array 0x00e9ba60 swrSprite
swrSprite swrSprite_array ;

// Line 353: swrModel_unk_array 0x00dfb040 swrModel_unk[4]
swrModel_unk swrModel_unk_array[4] ;

// Line 355: rdCamera_toggle 0x00dfb1b0 int
int rdCamera_toggle ;

// Line 356: rdCamera_transform 0x00dfb1dc  rdMatrix44
 rdMatrix44 rdCamera_transform ;

// Line 358: rdMatrix44_unk 0x00dfb21c rdMatrix44
rdMatrix44 rdMatrix44_unk ;

// Line 360: cameraFOV 0x00dfb2e0 float
float cameraFOV ;

// Line 361: cameraAspectRatio 0x00dfb2e4 float
float cameraAspectRatio ;

// Line 363: swrRace_frameTime 0x00e22a40 float
float swrRace_frameTime ;

// Line 364: swrRace_deltaTime 0x00e22a50 float
float swrRace_deltaTime ;

// Line 366: rdMatrix44_00e25960 0x00e25960 rdMatrix44
rdMatrix44 rdMatrix44_00e25960 ;

// Line 368: swrRace_FireLocation 0x00e25e00 float
float swrRace_FireLocation ;

// Line 370: swrRace_Transition 0x00e295a0 float
float swrRace_Transition ;

// Line 372: swrRace_MenuMaxSelection 0x00e295cc int
int swrRace_MenuMaxSelection ;

// Line 373: swrRace_MenuSelectedItem 0x00e295d0 int
int swrRace_MenuSelectedItem ;

// Line 375: rdMatrix44_unk4 0x00e298c0 rdMatrix44
rdMatrix44 rdMatrix44_unk4 ;

// Line 377: rdVector3_unk1 0x00e29b90 rdVector3
rdVector3 rdVector3_unk1 ;

// Line 379: swrRace_antiskid 0x00e29bdc float
float swrRace_antiskid ;

// Line 380: swrRace_turn_response 0x00e29be0 float
float swrRace_turn_response ;

// Line 381: swrRace_max_turn_rate 0x00e29be4 float
float swrRace_max_turn_rate ;

// Line 382: swrRace_acceleration 0x00e29be8 float
float swrRace_acceleration ;

// Line 383: swrRace_top_speed 0x00e29bec float
float swrRace_top_speed ;

// Line 384: swrRace_air_brake_interval 0x00e29bf0 float
float swrRace_air_brake_interval ;

// Line 385: swrRace_deceleration_interval 0x00e29bf4 float
float swrRace_deceleration_interval ;

// Line 386: swrRace_boost_thrust 0x00e29bf8 float
float swrRace_boost_thrust ;

// Line 387: swrRace_heat_rate 0x00e29bfc float
float swrRace_heat_rate ;

// Line 388: swrRace_cool_rate 0x00e29c00 float
float swrRace_cool_rate ;

// Line 389: swrRace_hover_height 0x00e29c04 float
float swrRace_hover_height ;

// Line 390: swrRace_repair_rate 0x00e29c08 float
float swrRace_repair_rate ;

// Line 391: swrRace_bump_mass 0x00e29c0c float
float swrRace_bump_mass ;

// Line 392: swrRace_damage_immunity 0x00e29c10 float
float swrRace_damage_immunity ;

// Line 393: swrRace_intersect_radius 0x00e29c14 float
float swrRace_intersect_radius ;

// Line 395: swrRace_results_P1_Position 0x00e29c1c int
int swrRace_results_P1_Position ;

// Line 396: swrRace_results_P1_Lap1 0x00e29c20 float
float swrRace_results_P1_Lap1 ;

// Line 397: swrRace_results_P1_Lap2 0x00e29c24 float
float swrRace_results_P1_Lap2 ;

// Line 398: swrRace_results_P1_Lap3 0x00e29c28 float
float swrRace_results_P1_Lap3 ;

// Line 399: swrRace_results_P1_Lap4 0x00e29c2c float
float swrRace_results_P1_Lap4 ;

// Line 400: swrRace_results_P1_Lap5 0x00e29c30 float
float swrRace_results_P1_Lap5 ;

// Line 401: swrRace_results_P1_total_time 0x00e29c34 float
float swrRace_results_P1_total_time ;

// Line 402: swrRace_results_P1_Lap 0x00e29c38 float
float swrRace_results_P1_Lap ;

// Line 403: swrRace_lastRaceDamage 0x00e29c40 float
float swrRace_lastRaceDamage ;

// Line 404: swrRace_P1_UI_writer_ptr 0x00e29c44 void*
void* swrRace_P1_UI_writer_ptr ;

// Line 406: rdMatrix44_unk3 0x00e2ae80 rdMatrix44
rdMatrix44 rdMatrix44_unk3 ;

// Line 408: rdVector_unk4 0x00e2af90 rdVector3
rdVector3 rdVector_unk4 ;

// Line 410: rdVector3_unk2 0x00e2b470 rdVector3
rdVector3 rdVector3_unk2 ;

// Line 412: sound_music_volume 0x00e364a6 short
short sound_music_volume ;

// Line 414: swrRace_UnlockDataBase 0x00e35a84 int
int swrRace_UnlockDataBase ;

// Line 416: swrRace_truguts 0x00e35a98 int
int swrRace_truguts ;

// Line 418: swrRace_nbPitDroids 0x00e35aa0 char
char swrRace_nbPitDroids ;

// Line 419: swrRace_traction_upgrade_level 0x00e35aa1 char
char swrRace_traction_upgrade_level ;

// Line 420: swrRace_turning_upgrade_level 0x00e35aa2 char
char swrRace_turning_upgrade_level ;

// Line 421: swrRace_acceleration_upgrade_level 0x00e35aa3 char
char swrRace_acceleration_upgrade_level ;

// Line 422: swrRace_topspeed_upgrade_level 0x00e35aa4 char
char swrRace_topspeed_upgrade_level ;

// Line 423: swrRace_airbrake_upgrade_level 0x00e35aa5 char
char swrRace_airbrake_upgrade_level ;

// Line 424: swrRace_cooling_upgrade_level 0x00e35aa6 char
char swrRace_cooling_upgrade_level ;

// Line 425: swrRace_repair_upgrade_level 0x00e35aa7 char
char swrRace_repair_upgrade_level ;

// Line 426: swrRace_traction_upgrade_health 0x00e35aa8 char
char swrRace_traction_upgrade_health ;

// Line 427: swrRace_turning_upgrade_health 0x00e35aa9 char
char swrRace_turning_upgrade_health ;

// Line 428: swrRace_acceleration_upgrade_health 0x00e35aaa char
char swrRace_acceleration_upgrade_health ;

// Line 429: swrRace_topspeed_upgrade_health 0x00e35aab char
char swrRace_topspeed_upgrade_health ;

// Line 430: swrRace_airbrake_upgrade_health 0x00e35aac char
char swrRace_airbrake_upgrade_health ;

// Line 431: swrRace_cooling_upgrade_health 0x00e35aad char
char swrRace_cooling_upgrade_health ;

// Line 432: swrRace_repair_upgrade_health 0x00e35aae char
char swrRace_repair_upgrade_health ;

// Line 434: traction_upgrade_level 0x00e364f5 char
char traction_upgrade_level ;

// Line 435: turning_upgrade_level 0x00e364f6 char
char turning_upgrade_level ;

// Line 436: acceleration_upgrade_level 0x00e364f7 char
char acceleration_upgrade_level ;

// Line 437: topspeed_upgrade_level 0x00e364f8 char
char topspeed_upgrade_level ;

// Line 438: airbrake_upgrade_level 0x00e364f9 char
char airbrake_upgrade_level ;

// Line 439: cooling_upgrade_level 0x00e364fa char
char cooling_upgrade_level ;

// Line 440: repair_upgrade_level 0x00e364fb char
char repair_upgrade_level ;

// Line 442: rdMatrix_unk8 0x00e37480 rdMatrix44
rdMatrix44 rdMatrix_unk8 ;

// Line 444: rdMatrix44_00e37580 0x00e37580 rdMatrix44
rdMatrix44 rdMatrix44_00e37580 ;

// Line 445: rdMatrixStack34 0x00e375c0 rdMatrix34[33]
rdMatrix34 rdMatrixStack34[33] ;

// Line 447: texture_buffer 0x00e93860 void*[1700] 
void* texture_buffer[1700]  ;

// Line 449: texture_count 0x00e9823c unsigned int
unsigned int texture_count ;

// Line 451: rdMatrix44_stack 0x00e985c0 rdMatrix44[32]
rdMatrix44 rdMatrix44_stack[32] ;

// Line 453: swrRace_SelectIndex 0x00e99240 int
int swrRace_SelectIndex ;

// Line 455: swrRace_PodRotationAnimation 0x00e99384 float
float swrRace_PodRotationAnimation ;

// Line 457: rdMatrix44_unk2 0x00e9b9e8 rdMatrix44
rdMatrix44 rdMatrix44_unk2 ;

// Line 459: sound_3d_gain_adjust 0x00e9e048 float
float sound_3d_gain_adjust ;

// Line 461: array_classes_unk 0x00e9edc0 void*[300] 
void* array_classes_unk[300]  ;

// Line 463: stdPlatform_hostServices 0x00e9f280 HostServices
HostServices stdPlatform_hostServices ;

// Line 465: unicode_unk 0x00e9f3c4 wchar_t[32]
wchar_t unicode_unk[32] ;

// Line 467: unicode_unk2 0x00e9f380 wchar_t[32]
wchar_t unicode_unk2[32] ;

// Line 469: multiplayer_racer1_id 0x00ea0260 int
int multiplayer_racer1_id ;

// Line 470: multiplayer_racer2_id 0x00ea0264 int
int multiplayer_racer2_id ;

// Line 471: multiplayer_racer3_id 0x00ea0268 int
int multiplayer_racer3_id ;

// Line 472: multiplayer_racer4_id 0x00ea026c int
int multiplayer_racer4_id ;

// Line 473: multiplayer_racer5_id 0x00ea0270 int
int multiplayer_racer5_id ;

// Line 474: multiplayer_racer6_id 0x00ea0274 int
int multiplayer_racer6_id ;

// Line 475: multiplayer_racer7_id 0x00ea0278 int
int multiplayer_racer7_id ;

// Line 476: multiplayer_racer8_id 0x00ea027c int
int multiplayer_racer8_id ;

// Line 477: multiplayer_racer9_id 0x00ea0280 int
int multiplayer_racer9_id ;

// Line 478: multiplayer_racer10_id 0x00ea0284 int
int multiplayer_racer10_id ;

// Line 479: multiplayer_racer11_id 0x00ea0288 int
int multiplayer_racer11_id ;

// Line 480: multiplayer_racer12_id 0x00ea028c int
int multiplayer_racer12_id ;

// Line 481: multiplayer_racer13_id 0x00ea0290 int
int multiplayer_racer13_id ;

// Line 482: multiplayer_racer14_id 0x00ea0294 int
int multiplayer_racer14_id ;

// Line 483: multiplayer_racer15_id 0x00ea0298 int
int multiplayer_racer15_id ;

// Line 484: multiplayer_racer16_id 0x00ea029c int
int multiplayer_racer16_id ;

// Line 485: multiplayer_racer17_id 0x00ea02a0 int
int multiplayer_racer17_id ;

// Line 486: multiplayer_racer18_id 0x00ea02a4 int
int multiplayer_racer18_id ;

// Line 487: multiplayer_racer19_id 0x00ea02a8 int
int multiplayer_racer19_id ;

// Line 488: multiplayer_racer20_id 0x00ea02ac int
int multiplayer_racer20_id ;

// Line 489: multiplayer_track_select 0x00ea02b0 swrRace_TRACK
swrRace_TRACK multiplayer_track_select ;

// Line 491: multiplayer_laps 0x00ea02b8 int
int multiplayer_laps ;

// Line 493: swrConfig_FORCE_STRENGTH 0x00ec83e0 int
int swrConfig_FORCE_STRENGTH ;

// Line 494: swrConfig_FORCE_AUTOCENTER 0x00ec83e4 int
int swrConfig_FORCE_AUTOCENTER ;

// Line 495: swrConfig_FORCE_COLLISIONS 0x00ec83e8 int
int swrConfig_FORCE_COLLISIONS ;

// Line 496: swrConfig_FORCE_DAMAGE 0x00ec83ec int
int swrConfig_FORCE_DAMAGE ;

// Line 497: swrConfig_FORCE_TERRAIN 0x00ec83f0 int
int swrConfig_FORCE_TERRAIN ;

// Line 498: swrConfig_FORCE_PODACTIONS 0x00ec83f4 int
int swrConfig_FORCE_PODACTIONS ;

// Line 499: swrConfig_FORCE_GFORCES 0x00ec83f8 int
int swrConfig_FORCE_GFORCES ;

// Line 500: swrConfig_FORCE_ENGINERUMBLE 0x00ec83fc int
int swrConfig_FORCE_ENGINERUMBLE ;

// Line 502: rdCamera_mat 0x00ec8580 rdMatrix34
rdMatrix34 rdCamera_mat ;

// Line 504: screen_height 0x00ec85e8 int
int screen_height ;

// Line 505: rdCamera_main_ptr 0x00ec85ec rdCamera*
rdCamera* rdCamera_main_ptr ;

// Line 507: swrConfig_VIDEO_REFLECTIONS 0x00ec86a0 int
int swrConfig_VIDEO_REFLECTIONS ;

// Line 508: swrConfig_VIDEO_ZEFFECTS 0x00ec86a4 int
int swrConfig_VIDEO_ZEFFECTS ;

// Line 509: swrConfig_VIDEO_DYNAMIC_LIGHTING 0x00ec86a8 int
int swrConfig_VIDEO_DYNAMIC_LIGHTING ;

// Line 510: swrConfig_VIDEO_VSYNC 0x00ec86ac int
int swrConfig_VIDEO_VSYNC ;

// Line 511: swrConfig_VIDEO_LENSFLARE 0x00ec86b0 int
int swrConfig_VIDEO_LENSFLARE ;

// Line 512: swrConfig_VIDEO_ENGINEEXHAUST 0x00ec86b4 int
int swrConfig_VIDEO_ENGINEEXHAUST ;

// Line 513: swrConfig_VIDEO_TEXTURE_RES 0x00ec86b8 int
int swrConfig_VIDEO_TEXTURE_RES ;

// Line 514: swrConfig_VIDEO_MODEL_DETAIL 0x00ec86bc int
int swrConfig_VIDEO_MODEL_DETAIL ;

// Line 515: swrConfig_VIDEO_DRAWDISTANCE 0x00ec86c0 int
int swrConfig_VIDEO_DRAWDISTANCE ;

// Line 516: screen_width 0x00ec86c4 int
int screen_width ;

// Line 518: tagRect 0x00ec86d0 tagRECT
tagRECT tagRect ;

// Line 520: rdCanvas_main_ptr 0x00ec86e0 rdCanvas*
rdCanvas* rdCanvas_main_ptr ;

// Line 522: g_mouse_x 0x00ec874c int
int g_mouse_x ;

// Line 523: g_mouse_x2 0x00ec8750 int
int g_mouse_x2 ;

// Line 525: g_mouse_y 0x00ec8754 int
int g_mouse_y ;

// Line 526: g_mouse_y2 0x00ec8754 int
int g_mouse_y2 ;

// Line 528: Deadzone 0x00ec876c float
float Deadzone ;

// Line 530: flip_x_axis 0x00ec8790 int
int flip_x_axis ;

// Line 531: flip_y_axis 0x00ec8794 int
int flip_y_axis ;

// Line 532: flip_z_axis 0x00ec8798 int
int flip_z_axis ;

// Line 534: swrRace_ThrottleInput 0x00ec8830 float
float swrRace_ThrottleInput ;

// Line 536: swrRace_PitchInput 0x00ec883c float
float swrRace_PitchInput ;

// Line 538: swrRace_ThrustInput 0x00ec884c float
float swrRace_ThrustInput ;

// Line 539: swrRace_BoostInput 0x00ec8850 float
float swrRace_BoostInput ;

// Line 541: stdPlatfom_FPU1 0x00ec8c80 unsigned short
unsigned short stdPlatfom_FPU1 ;

// Line 542: stdPlatfom_FPU2 0x00ec8c82 unsigned short
unsigned short stdPlatfom_FPU2 ;

// Line 543: stdPlatfom_FPU3 0x00ec8c84 unsigned int
unsigned int stdPlatfom_FPU3 ;

// Line 545: iDirectDrawSurface4_ptr 0x00ec8d00 LPDIRECTDRAWSURFACE4
LPDIRECTDRAWSURFACE4 iDirectDrawSurface4_ptr ;

// Line 546: _ddSurfaceDesc2_2 0x00ec8d04 DDSURFACEDESC2
DDSURFACEDESC2 _ddSurfaceDesc2_2 ;

// Line 548: directDrawVidMemTotal 0x00ec8d80 int;
int; directDrawVidMemTotal ;

// Line 550: stdVBuffer_main 0x00ec8da0 stdVBuffer
stdVBuffer stdVBuffer_main ;

// Line 555: swrConfig_buffer2 0x00ec9e84 char* 
char*  swrConfig_buffer2 ;

// Line 557: DirectInputMouses 0x00ecb240 void*
void* DirectInputMouses ;

// Line 559: DirectInputJoysticks 0x00ec9ea0 void*
void* DirectInputJoysticks ;

// Line 561: iDirectInputDeviceA_ptr2 0x00ecb484 LPDIRECTINPUTDEVICEA
LPDIRECTINPUTDEVICEA iDirectInputDeviceA_ptr2 ;

// Line 562: diDevCaps_ptr 0x00ecb488 LPDIDEVCAPS
LPDIDEVCAPS diDevCaps_ptr ;

// Line 564: std_output_buffer 0x00ecbc20 char[0x800]
char std_output_buffer[0x800] ;

// Line 566: stdPlatform_hostServices_ptr 0x00ecc420 HostServices*
HostServices* stdPlatform_hostServices_ptr ;

// Line 567: rdroid_hostServices_ptr 0x00ecc428 HostServices*
HostServices* rdroid_hostServices_ptr ;

// Line 568: rdCamera_screen_width 0x00ecc42c float
float rdCamera_screen_width ;

// Line 570: rdCamera_camMatrix 0x00ecc440 rdMatrix34
rdMatrix34 rdCamera_camMatrix ;

// Line 572: nbVertexBuffer1 0x00ecc480
 
 nbVertexBuffer1 ;

// Line 574: VertexBuffer1 0x00ecc48c rdVector3*
rdVector3* VertexBuffer1 ;

// Line 576: VertexBuffer1_projected 0x00ecc49c rdVector3*
rdVector3* VertexBuffer1_projected ;
