#ifndef GLOBALS_H
#define GLOBALS_H

// This file is auto-generated by scripts/GenerateGlobalHeaderFromSymbols.py and data_symbols.syms
// using Jinja template globals.h.j2

#include "types.h"
#include "types_directx.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
    // Line 0: diDataFormat 0x0049e720 DIDATAFORMAT
    extern DIDATAFORMAT diDataFormat;
    
    // Line 2: A3dApi_GUID 0x004ae0e8 GUID
    extern GUID A3dApi_GUID;
    
    // Line 3: IID_Ia3d4_GUID 0x004ae128 GUID
    extern GUID IID_Ia3d4_GUID;
    
    // Line 4: IID_IA3dListener_GUID 0x004ae158 GUID
    extern GUID IID_IA3dListener_GUID;
    
    // Line 6: iDirectDraw4_GUID 0x004af1c8 GUID
    extern GUID iDirectDraw4_GUID;
    
    // Line 7: iDirect3D3_GUID 0x004af278 GUID
    extern GUID iDirect3D3_GUID;
    
    // Line 9: IID_IDirectPlay4_GUID 0x004af4a8 GUID
    extern GUID IID_IDirectPlay4_GUID;
    
    // Line 10: DirectPlay_GUID 0x004af4c8 GUID
    extern GUID DirectPlay_GUID;
    
    // Line 12: Window_UUID 0x004af9b0 uint32_t[4] = { 0xC95FB584, 0x11D2FA31, 0xAA009D90, 0xAD22A300 }
    extern uint32_t Window_UUID[4] ;
    
    // Line 14: rdMatrix34_identity 0x004af880 rdMatrix34 = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}}
    extern rdMatrix34  rdMatrix34_identity;
    
    // Line 16: joystick_enabled 0x004b2944 int = 1
    extern int  joystick_enabled;
    
    // Line 17: keyboard_enabled 0x004b2948 int = 1
    extern int  keyboard_enabled;
    
    // Line 18: joystick_detected 0x004b294c int = 1
    extern int  joystick_detected;
    
    // Line 20: Main_force_feedback 0x004b4938 int = 1
    extern int  Main_force_feedback;
    
    // Line 22: iDirectDraw4_error 0x004b4758 int
    extern int iDirectDraw4_error;
    
    // Line 24: swrUI_unk_ptr 0x004b5d74 swrUI_unk*
    extern swrUI_unk* swrUI_unk_ptr;
    
    // Line 26: Main_nut_delay_ms 0x004b6718 int = 32
    extern int  Main_nut_delay_ms;
    
    // Line 27: Main_hiRes_sound 0x004b6d14 int = 1
    extern int  Main_hiRes_sound;
    
    // Line 28: Main_doppler_sound 0x004b6d18 int = 0
    extern int  Main_doppler_sound;
    
    // Line 29: Main_sound 0x004b6d20 int = 1
    extern int  Main_sound;
    
    // Line 30: Main_sound_gain_adjust 0x004b6d24 float
    extern float Main_sound_gain_adjust;
    
    // Line 31: swrRace_voices_enabled 0x004b6d28 int = 1
    extern int  swrRace_voices_enabled;
    
    // Line 32: Main_sound_unk 0x004b6d2c int = 1
    extern int  Main_sound_unk;
    
    // Line 33: Main_fullscreen_unk 0x004b79f8 int = 1
    extern int  Main_fullscreen_unk;
    
    // Line 34: Main_display_intro_scene 0x004b7a00 int = 1
    extern int  Main_display_intro_scene;
    
    // Line 36: swrSound_criticalSection 0x004b7e7e CRITICAL_SECTION
    extern CRITICAL_SECTION swrSound_criticalSection;
    
    // Line 38: swrSprite_SpriteCount 0x004b91b8 int
    extern int swrSprite_SpriteCount;
    
    // Line 39: swrSprite_unk_x 0x004b91bc float = 16.0
    extern float  swrSprite_unk_x;
    
    // Line 40: swrSprite_unk_y 0x004b91c0 float = 155.0
    extern float  swrSprite_unk_y;
    
    // Line 42: rdVector_negZ 0x004c2598 rdVector3 = {0.0, 0.0, -1.0}
    extern rdVector3  rdVector_negZ;
    
    // Line 44: ai_antiskid 0x004c3114 float
    extern float ai_antiskid;
    
    // Line 45: ai_turn_response 0x004c3118 float
    extern float ai_turn_response;
    
    // Line 46: ai_max_turn_rate 0x004c311c float
    extern float ai_max_turn_rate;
    
    // Line 47: ai_acceleration 0x004c3120 float
    extern float ai_acceleration;
    
    // Line 48: ai_max_speed 0x004c3124 float
    extern float ai_max_speed;
    
    // Line 49: ai_air_brake_interval 0x004c3128 float
    extern float ai_air_brake_interval;
    
    // Line 50: ai_deceleration_interval 0x004c312c float
    extern float ai_deceleration_interval;
    
    // Line 51: ai_boost_thrust 0x004c3130 float
    extern float ai_boost_thrust;
    
    // Line 52: ai_heat_rate 0x004c3134 float
    extern float ai_heat_rate;
    
    // Line 53: ai_cool_rate 0x004c3138 float
    extern float ai_cool_rate;
    
    // Line 54: ai_hover_height 0x004c313c float
    extern float ai_hover_height;
    
    // Line 55: ai_repair_rate 0x004c3140 float
    extern float ai_repair_rate;
    
    // Line 56: ai_bump_mass 0x004c3144 float
    extern float ai_bump_mass;
    
    // Line 57: ai_damage_immunity 0x004c3148 float
    extern float ai_damage_immunity;
    
    // Line 58: ai_intersect_radius 0x004c314c float
    extern float ai_intersect_radius;
    
    // Line 60: rdMatrix_unk5 0x004c3c38 rdMatrix44 = {{-1.0 / 6.0, 0.5, -0.5, 1.0 / 6.0}, {0.5, -1.0, 0.5, 0.0}, {-0.5, 0.0, 0.5, 0.0}, {1.0 /6.0, 2.0 / 3.0, 1.0 / 6.0, 0.0}}
    extern rdMatrix44  rdMatrix_unk5;
    
    // Line 61: rdMatrix_unk3 0x004c3c78 rdMatrix44 = {{0.0, 0.0, 0.0, 0.0}, {-0.5, 1.5, -1.5, 0.5}, {1.0, -2.0, 1.0, 0.0}, {-0.5, 0.0, 0.5, 0.0}}
    extern rdMatrix44  rdMatrix_unk3;
    
    // Line 62: rdMatrix_unk1 0x004c3cb8 rdMatrix44 = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {-1.0, 3.0, -3.0, 1.0}, {1.0, -2.0, 1.0, 0.0}}
    extern rdMatrix44  rdMatrix_unk1;
    
    // Line 63: rdMatrix_unk6 0x004c3cf8 rdMatrix44 = {{-1.0, 3.0, -3.0, 1.0}, {3.0, -6.0, 3.0, 0.0}, {-3.0, 3.0, 0.0, 0.0}, {1.0, 0.0, 0.0, 0.0}}
    extern rdMatrix44  rdMatrix_unk6;
    
    // Line 64: rdMatrix_unk4 0x004c3d38 rdMatrix44 = {{0.0, 0.0, 0.0, 0.0}, {-3.0, 9.0, -9.0, 3.0}, {6.0, -12.0, 6.0, 0.0}, {-3.0, 3.0, 0.0, 0.0}}
    extern rdMatrix44  rdMatrix_unk4;
    
    // Line 65: rdMatrix_unk2 0x004c3d78 rdMatrix44 = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {-6.0, 18.0, -18.0, 6.0}, {6.0, -12.0, 6.0, 0.0}}
    extern rdMatrix44  rdMatrix_unk2;
    
    // Line 67: ai_level 0x004c707c float
    extern float ai_level;
    
    // Line 68: ai_spread 0x004c7080 float
    extern float ai_spread;
    
    // Line 70: Main_sound_3dimpact 0x004c7aa8 int = -1
    extern int  Main_sound_3dimpact;
    
    // Line 72: death_speedMin 0x004c7bb8 float
    extern float death_speedMin;
    
    // Line 73: death_speedDrop 0x004c7bbc float
    extern float death_speedDrop;
    
    // Line 75: Main_sound_gain_const 0x004c7d70 float = 0.8
    extern float  Main_sound_gain_const;
    
    // Line 76: Main_sound_doppler_scale 0x004c7d74 float = 1.0
    extern float  Main_sound_doppler_scale;
    
    // Line 77: Main_sound_rolloff 0x004c7d78 float = 0.15
    extern float  Main_sound_rolloff;
    
    // Line 78: Main_sound_gain 0x004c7d7c float = 1.0
    extern float  Main_sound_gain;
    
    // Line 80: rdMatrixStack34_modified 0x004c3c0c int
    extern int rdMatrixStack34_modified;
    
    // Line 82: swrRace_AILevel 0x004c707c int
    extern int swrRace_AILevel;
    
    // Line 84: swrRace_DeathSpeedMin 0x004c7bb8 float = 325.00
    extern float  swrRace_DeathSpeedMin;
    
    // Line 85: swrRace_DeathSpeedDrop 0x004c7bbc float = 140.0
    extern float  swrRace_DeathSpeedDrop;
    
    // Line 87: swrRace_FireTimer 0x004c7bc0 float = -1.0
    extern float  swrRace_FireTimer;
    
    // Line 89: d3d_FogEnabled 0x004c98b0 int = 1
    extern int  d3d_FogEnabled;
    
    // Line 90: d3d_CurrentScene 0x004c98b4 int = 1 
    extern int  d3d_CurrentScene;
    
    // Line 92: stdMath_SinTable 0x004c98e8 float[4096]
    extern float stdMath_SinTable[4096];
    
    // Line 93: stdMath_TanTable 0x004cd8e8 float[4096]
    extern float stdMath_TanTable[4096];
    
    // Line 95: wuRegistry_lpClass 0x004d55cc LPSTR
    extern LPSTR wuRegistry_lpClass;
    
    // Line 97: multiplayer_enabled 0x004d5e00 int
    extern int multiplayer_enabled;
    
    // Line 99: swrText_keyNameText 0x004d5f38 char[128]
    extern char swrText_keyNameText[128];
    
    // Line 101: rdLight_1 0x004d6b78 rdLight
    extern rdLight rdLight_1;
    
    // Line 102: rdLight_2 0x004d6ba8 rdLight
    extern rdLight rdLight_2;
    
    // Line 104: directDrawSurface4_ptr2 0x004d6be0 LPDIRECTDRAWSURFACE4
    extern LPDIRECTDRAWSURFACE4 directDrawSurface4_ptr2;
    
    // Line 105: ddSurfaceDesc_2 0x004d6be4 DDSURFACEDESC
    extern DDSURFACEDESC ddSurfaceDesc_2;
    
    // Line 107: swrSpriteTexItems 0x004d7c68 swrSpriteTexItem[149]
    extern swrSpriteTexItem swrSpriteTexItems[149];
    
    // Line 109: multiplayer_in_mp 0x004d87a0 int
    extern int multiplayer_in_mp;
    
    // Line 111: swrUI_unk_array 0x004d8110 swrUI_unk[20]
    extern swrUI_unk swrUI_unk_array[20];
    
    // Line 113: swrUI_unk_array_count 0x004d87a4 int
    extern int swrUI_unk_array_count;
    
    // Line 115: time_buffer 0x004e9f20 char[256]
    extern char time_buffer[256];
    
    // Line 117: multiplayer_sync_timer_ms 0x004eb230 int
    extern int multiplayer_sync_timer_ms;
    
    // Line 119: multiplayer_race_button_toggle 0x004eb238 int
    extern int multiplayer_race_button_toggle;
    
    // Line 121: multiplayer_track_change_permission 0x004eb388 int
    extern int multiplayer_track_change_permission;
    
    // Line 123: playerNumber 0x004eb3b4 int
    extern int playerNumber;
    
    // Line 125: swrText_racerTab_array 0x004eb3c4 char**
    extern char** swrText_racerTab_array;
    
    // Line 126: swrText_racerTab_buffer 0x004eb3c8 char*
    extern char* swrText_racerTab_buffer;
    
    // Line 128: swrText_nbLinesRacerTab 0x004eb3cc int
    extern int swrText_nbLinesRacerTab;
    
    // Line 130: ia3dSourceThreadId 0x004eb3f8 DWORD
    extern DWORD ia3dSourceThreadId;
    
    // Line 131: ia3dSourceEventHandle 0x004eb3fc HANDLE
    extern HANDLE ia3dSourceEventHandle;
    
    // Line 132: ia3dSourceEventHandle2 0x004eb400 HANDLE
    extern HANDLE ia3dSourceEventHandle2;
    
    // Line 134: iA3DSource_ptr 0x004eb414 IA3dSource*
    extern IA3dSource* iA3DSource_ptr;
    
    // Line 136: swrRace_music_enabled 0x004eb45c int
    extern int swrRace_music_enabled;
    
    // Line 138: ia3dSourceThreadHandle 0x004eb478 HANDLE
    extern HANDLE ia3dSourceThreadHandle;
    
    // Line 139: ia3d_thread_running 0x004eb47c int
    extern int ia3d_thread_running;
    
    // Line 141: iDirectDrawSurface_ptr3 0x004eb480 LPDIRECTDRAWSURFACE
    extern LPDIRECTDRAWSURFACE iDirectDrawSurface_ptr3;
    
    // Line 142: ddSurfaceDesc_3 0x004eb484 DDSURFACEDESC
    extern DDSURFACEDESC ddSurfaceDesc_3;
    
    // Line 144: swrMain_initialized 0x0050b5a0 int
    extern int swrMain_initialized;
    
    // Line 146: array_classes_unk_counter 0x0050b5ec int
    extern int array_classes_unk_counter;
    
    // Line 148: rdVector_sound_pos 0x0050b5f0 rdVector4
    extern rdVector4 rdVector_sound_pos;
    
    // Line 150: Main_settings_RegFullScreen 0x0050b560 int
    extern int Main_settings_RegFullScreen;
    
    // Line 151: Main_settings_RegFixFlicker 0x0050b564 int
    extern int Main_settings_RegFixFlicker;
    
    // Line 152: Main_settings_RegDevMode 0x0050b568 int
    extern int Main_settings_RegDevMode;
    
    // Line 153: Main_settings_RegUseFett 0x0050b56c int
    extern int Main_settings_RegUseFett;
    
    // Line 155: Main_hWnd 0x0050b59c HWND 
    extern HWND  Main_hWnd;
    
    // Line 157: Main_settings_menu_only 0x0050b5b0 int
    extern int Main_settings_menu_only;
    
    // Line 158: Main_settings_debug_hud 0x0050b5c0 int
    extern int Main_settings_debug_hud;
    
    // Line 160: swrSprite_unk1_r 0x0050b704 char
    extern char swrSprite_unk1_r;
    
    // Line 161: swrSprite_unk1_g 0x0050b705 char
    extern char swrSprite_unk1_g;
    
    // Line 162: swrSprite_unk1_b 0x0050b706 char
    extern char swrSprite_unk1_b;
    
    // Line 163: swrSprite_unk1_a 0x0050b707 char
    extern char swrSprite_unk1_a;
    
    // Line 164: swrSprite_unk2_r 0x0050b708 char
    extern char swrSprite_unk2_r;
    
    // Line 165: swrSprite_unk2_g 0x0050b709 char
    extern char swrSprite_unk2_g;
    
    // Line 166: swrSprite_unk2_b 0x0050b70a char
    extern char swrSprite_unk2_b;
    
    // Line 167: swrSprite_unk2_a 0x0050b70b char
    extern char swrSprite_unk2_a;
    
    // Line 169: swrRace_DebugLevel 0x0050c040 int
    extern int swrRace_DebugLevel;
    
    // Line 170: swrRace_DebugMenu 0x0050c044 int 
    extern int  swrRace_DebugMenu;
    
    // Line 171: swrRace_DebugFlag 0x0050c048 char 
    extern char  swrRace_DebugFlag;
    
    // Line 173: swrLoader_sprite_file 0x0050c08c FILE*
    extern FILE* swrLoader_sprite_file;
    
    // Line 174: swrLoader_spline_file 0x0050c090 FILE*
    extern FILE* swrLoader_spline_file;
    
    // Line 175: swrLoader_texture_file 0x0050c094 FILE*
    extern FILE* swrLoader_texture_file;
    
    // Line 176: swrLoader_model_file 0x0050c098 FILE*
    extern FILE* swrLoader_model_file;
    
    // Line 178: swrRace_SelectedRacer 0x0050c118 int
    extern int swrRace_SelectedRacer;
    
    // Line 180: alpha_unk 0x0050c2e8 float
    extern float alpha_unk;
    
    // Line 181: gamma_unk 0x0050c2ec float
    extern float gamma_unk;
    
    // Line 183: swrRace_TournamentTrugutGain 0x0050c53c int
    extern int swrRace_TournamentTrugutGain;
    
    // Line 185: nb_AI_racers 0x0050c558 int
    extern int nb_AI_racers;
    
    // Line 187: rdMatrixStack44_size 0x0050c5e8 int
    extern int rdMatrixStack44_size;
    
    // Line 189: swrSound_Orientation1 0x0050c648 rdVector4
    extern rdVector4 swrSound_Orientation1;
    
    // Line 190: swrSound_Orientation2 0x0050c658 rdVector4
    extern rdVector4 swrSound_Orientation2;
    
    // Line 191: swrSound_Position 0x0050c668 rdVector4
    extern rdVector4 swrSound_Position;
    
    // Line 193: swrSound_unk_init 0x0050c68c int
    extern int swrSound_unk_init;
    
    // Line 194: swrSound_Velocity 0x0050c690 rdVector3
    extern rdVector3 swrSound_Velocity;
    
    // Line 196: IA3dSource2_ptr 0x0050c6a0 IA3dSource*
    extern IA3dSource* IA3dSource2_ptr;
    
    // Line 197: IA3dSource3_ptr 0x0050c6a4 IA3dSource*
    extern IA3dSource* IA3dSource3_ptr;
    
    // Line 199: swr_unk1_ptr 0x0050c6b0 swr_unk1*
    extern swr_unk1* swr_unk1_ptr;
    
    // Line 201: rdVector_unk5 0x0050c6e8 rdVector3
    extern rdVector3 rdVector_unk5;
    
    // Line 203: rdMatrixStack34_size 0x0050c6f4 int
    extern int rdMatrixStack34_size;
    
    // Line 205: debug_showSurfaceFlags 0x0050c88c int
    extern int debug_showSurfaceFlags;
    
    // Line 207: debug_showSplineMarkers 0x0050ca24 int
    extern int debug_showSplineMarkers;
    
    // Line 208: swrRace_IsInvincible 0x0050ca28 int
    extern int swrRace_IsInvincible;
    
    // Line 210: swr_systemTimeMs 0x0050cb60 DWORD
    extern DWORD swr_systemTimeMs;
    
    // Line 212: swr_FastMode 0x0050cb68 int
    extern int swr_FastMode;
    
    // Line 214: debug_buffer 0x0050cd18 char[2048]
    extern char debug_buffer[2048];
    
    // Line 216: stdPlatform_hostServices_initialized 0x0050d518 int
    extern int stdPlatform_hostServices_initialized;
    
    // Line 218: a3dCaps_hardware 0x0050d520 A3DCAPS_HARDWARE
    extern A3DCAPS_HARDWARE a3dCaps_hardware;
    
    // Line 219: a3dOutputGain 0x0050d544 float
    extern float a3dOutputGain;
    
    // Line 220: IA3d4_ptr 0x0050d548 IA3d4*
    extern IA3d4* IA3d4_ptr;
    
    // Line 222: Sound_enabled_3d 0x0050d550 int
    extern int Sound_enabled_3d;
    
    // Line 224: IA3dListener_ptr 0x0050d560 IA3dListener*
    extern IA3dListener* IA3dListener_ptr;
    
    // Line 226: iDirectInputDeviceA_ptr 0x0050d89c LPDIRECTINPUTDEVICEA
    extern LPDIRECTINPUTDEVICEA iDirectInputDeviceA_ptr;
    
    // Line 228: DirectInput_initialized 0x0050fea8 int
    extern int DirectInput_initialized;
    
    // Line 230: iDirectInputA_ptr 0x0050feb8 LPDIRECTINPUTA
    extern LPDIRECTINPUTA iDirectInputA_ptr;
    
    // Line 232: iDirectPlay4_ptr 0x00510254 IDirectPlay4*
    extern IDirectPlay4* iDirectPlay4_ptr;
    
    // Line 234: swrConfig_filename 0x005138b8 char[0x80]
    extern char swrConfig_filename[0x80];
    
    // Line 236: swrConfig_buffer3 0x005143d8 char[0x80]
    extern char swrConfig_buffer3[0x80];
    
    // Line 238: swrConfig_buffer 0x00528500 char[0x1000]
    extern char swrConfig_buffer[0x1000];
    
    // Line 239: swrConfig_file2 0x00529504 FILE*
    extern FILE* swrConfig_file2;
    
    // Line 240: swrConfig_file 0x00529508 FILE*
    extern FILE* swrConfig_file;
    
    // Line 242: swrMain_fontHandle 0x00529510 HFONT
    extern HFONT swrMain_fontHandle;
    
    // Line 244: iDirectDrawSurface_ptr 0x00529578 LPDIRECTDRAWSURFACE
    extern LPDIRECTDRAWSURFACE iDirectDrawSurface_ptr;
    
    // Line 245: _ddSurfaceDesc 0x0052957c DDSURFACEDESC2
    extern DDSURFACEDESC2 _ddSurfaceDesc;
    
    // Line 247: iDirectDraw4 0x0052d454 LPDIRECTDRAW
    extern LPDIRECTDRAW iDirectDraw4;
    
    // Line 249: d3dDeviceDesc 0x0052d460 D3DDEVICEDESC
    extern D3DDEVICEDESC d3dDeviceDesc;
    
    // Line 251: swr3DDevices 0x0052d870 swr3DDevice[4]
    extern swr3DDevice swr3DDevices[4];
    
    // Line 252: d3dRenderState 0x0052e610 unsigned int
    extern unsigned int d3dRenderState;
    
    // Line 253: d3dMipFilter 0x0052e614 unsigned int
    extern unsigned int d3dMipFilter;
    
    // Line 255: d3dMaxVertices 0x0052d624 unsigned int
    extern unsigned int d3dMaxVertices;
    
    // Line 256: d3dCurrentTexture 0x0052e628 IDirect3DTexture2*
    extern IDirect3DTexture2* d3dCurrentTexture;
    
    // Line 258: iDirectDraw4_2 0x0052e638 LPDIRECTDRAW
    extern LPDIRECTDRAW iDirectDraw4_2;
    
    // Line 259: iDirectDrawPalette_ptr 0x0052e63c LPDIRECTDRAWPALETTE
    extern LPDIRECTDRAWPALETTE iDirectDrawPalette_ptr;
    
    // Line 260: iDirect3D3_ptr 0x0052e640 LPDIRECT3D3
    extern LPDIRECT3D3 iDirect3D3_ptr;
    
    // Line 261: iDirect3DDevice3_ptr 0x0052e644 LPDIRECT3DDEVICE3
    extern LPDIRECT3DDEVICE3 iDirect3DDevice3_ptr;
    
    // Line 262: iDirect3DViewport_ptr 0x0052e648 IDirect3DViewport3*
    extern IDirect3DViewport3* iDirect3DViewport_ptr;
    
    // Line 264: stdFilePrintf_buffer 0x0052e658 char[0x800]
    extern char stdFilePrintf_buffer[0x800];
    
    // Line 266: Window_GUID 0x0052ee60 GUID
    extern GUID Window_GUID;
    
    // Line 267: Window_hWnd 0x0052ee70 HWND
    extern HWND Window_hWnd;
    
    // Line 268: Window_hinstance 0x0052ee74 HINSTANCE
    extern HINSTANCE Window_hinstance;
    
    // Line 270: stdConsole_hConsoleOutput 0x0052ee78 HANDLE
    extern HANDLE stdConsole_hConsoleOutput;
    
    // Line 271: stdConsole_wAttributes 0x0052ee7c WORD
    extern WORD stdConsole_wAttributes;
    
    // Line 273: daAlloc_struct 0x0052ee98 void*
    extern void* daAlloc_struct;
    
    // Line 275: swr_RenderState2 0x005330c0 unsigned int
    extern unsigned int swr_RenderState2;
    
    // Line 277: swr_RenderState 0x006830c8 unsigned int
    extern unsigned int swr_RenderState;
    
    // Line 279: d3d_IndexBuffer 0x00af30e8 WORD[2] 
    extern WORD d3d_IndexBuffer[2] ;
    
    // Line 281: d3d_VertexBuffer 0x00b6b0e8 void* 
    extern void*  d3d_VertexBuffer;
    
    // Line 283: rdCamera_camRotation 0x00df7f20 rdVector3
    extern rdVector3 rdCamera_camRotation;
    
    // Line 284: rdCamera_pCurCamera 0x00df7f2c rdCamera*
    extern rdCamera* rdCamera_pCurCamera;
    
    // Line 285: bRDroidStartup 0x00df7f30 int
    extern int bRDroidStartup;
    
    // Line 287: g_hWnd 0x00dfaa28 HWND
    extern HWND g_hWnd;
    
    // Line 288: g_nCmdShow 0x00dfaa2c int
    extern int g_nCmdShow;
    
    // Line 289: g_WndProc 0x00dfaa30 Window_MSGHANDLER_ptr
    extern Window_MSGHANDLER_ptr g_WndProc;
    
    // Line 290: Window_width 0x00dfaa34 int
    extern int Window_width;
    
    // Line 291: Window_height 0x00dfaa38 int
    extern int Window_height;
    
    // Line 292: wuRegistry_bInitted 0x00dfaa3c int
    extern int wuRegistry_bInitted;
    
    // Line 293: wuRegistry_lpSubKey 0x00dfaa40 LPCSTR
    extern LPCSTR wuRegistry_lpSubKey;
    
    // Line 294: wuRegistry_hKey 0x00dfaa44 HKEY
    extern HKEY wuRegistry_hKey;
    
    // Line 296: translation_unk 0x00e996c0 rdVector3
    extern rdVector3 translation_unk;
    
    // Line 297: rotation_unk 0x00e996cc rdVector3
    extern rdVector3 rotation_unk;
    
    // Line 299: rdMatrix_unk7 0x00e9ba44 rdMatrix44
    extern rdMatrix44 rdMatrix_unk7;
    
    // Line 301: swrSprite_array 0x00e9ba60 swrSprite
    extern swrSprite swrSprite_array;
    
    // Line 303: swrModel_unk_array 0x00dfb040 swrModel_unk[4]
    extern swrModel_unk swrModel_unk_array[4];
    
    // Line 305: rdCamera_toggle 0x00dfb1b0 int
    extern int rdCamera_toggle;
    
    // Line 306: rdCamera_transform 0x00dfb1dc  rdMatrix44
    extern  rdMatrix44 rdCamera_transform;
    
    // Line 308: rdMatrix44_unk 0x00dfb21c rdMatrix44
    extern rdMatrix44 rdMatrix44_unk;
    
    // Line 310: swrRace_frameTime 0x00e22a40 float
    extern float swrRace_frameTime;
    
    // Line 311: swrRace_deltaTime 0x00e22a50 float
    extern float swrRace_deltaTime;
    
    // Line 313: rdMatrix44_00e25960 0x00e25960 rdMatrix44
    extern rdMatrix44 rdMatrix44_00e25960;
    
    // Line 315: swrRace_FireLocation 0x00e25e00 float
    extern float swrRace_FireLocation;
    
    // Line 317: swrRace_Transition 0x00e295a0 float
    extern float swrRace_Transition;
    
    // Line 319: swrRace_MenuMaxSelection 0x00e295cc int
    extern int swrRace_MenuMaxSelection;
    
    // Line 320: swrRace_MenuSelectedItem 0x00e295d0 int
    extern int swrRace_MenuSelectedItem;
    
    // Line 322: rdMatrix44_unk4 0x00e298c0 rdMatrix44
    extern rdMatrix44 rdMatrix44_unk4;
    
    // Line 324: rdVector3_unk1 0x00e29b90 rdVector3
    extern rdVector3 rdVector3_unk1;
    
    // Line 326: swrRace_antiskid 0x00e29bdc float
    extern float swrRace_antiskid;
    
    // Line 327: swrRace_turn_response 0x00e29be0 float
    extern float swrRace_turn_response;
    
    // Line 328: swrRace_max_turn_rate 0x00e29be4 float
    extern float swrRace_max_turn_rate;
    
    // Line 329: swrRace_acceleration 0x00e29be8 float
    extern float swrRace_acceleration;
    
    // Line 330: swrRace_top_speed 0x00e29bec float
    extern float swrRace_top_speed;
    
    // Line 331: swrRace_air_brake_interval 0x00e29bf0 float
    extern float swrRace_air_brake_interval;
    
    // Line 332: swrRace_deceleration_interval 0x00e29bf4 float
    extern float swrRace_deceleration_interval;
    
    // Line 333: swrRace_boost_thrust 0x00e29bf8 float
    extern float swrRace_boost_thrust;
    
    // Line 334: swrRace_heat_rate 0x00e29bfc float
    extern float swrRace_heat_rate;
    
    // Line 335: swrRace_cool_rate 0x00e29c00 float
    extern float swrRace_cool_rate;
    
    // Line 336: swrRace_hover_height 0x00e29c04 float
    extern float swrRace_hover_height;
    
    // Line 337: swrRace_repair_rate 0x00e29c08 float
    extern float swrRace_repair_rate;
    
    // Line 338: swrRace_bump_mass 0x00e29c0c float
    extern float swrRace_bump_mass;
    
    // Line 339: swrRace_damage_immunity 0x00e29c10 float
    extern float swrRace_damage_immunity;
    
    // Line 340: swrRace_intersect_radius 0x00e29c14 float
    extern float swrRace_intersect_radius;
    
    // Line 342: swrRace_results_P1_Position 0x00e29c1c int
    extern int swrRace_results_P1_Position;
    
    // Line 343: swrRace_results_P1_Lap1 0x00e29c20 float
    extern float swrRace_results_P1_Lap1;
    
    // Line 344: swrRace_results_P1_Lap2 0x00e29c24 float
    extern float swrRace_results_P1_Lap2;
    
    // Line 345: swrRace_results_P1_Lap3 0x00e29c28 float
    extern float swrRace_results_P1_Lap3;
    
    // Line 346: swrRace_results_P1_Lap4 0x00e29c2c float
    extern float swrRace_results_P1_Lap4;
    
    // Line 347: swrRace_results_P1_Lap5 0x00e29c30 float
    extern float swrRace_results_P1_Lap5;
    
    // Line 348: swrRace_results_P1_total_time 0x00e29c34 float
    extern float swrRace_results_P1_total_time;
    
    // Line 349: swrRace_results_P1_Lap 0x00e29c38 float
    extern float swrRace_results_P1_Lap;
    
    // Line 350: swrRace_lastRaceDamage 0x00e29c40 float
    extern float swrRace_lastRaceDamage;
    
    // Line 351: swrRace_P1_UI_writer_ptr 0x00e29c44 void*
    extern void* swrRace_P1_UI_writer_ptr;
    
    // Line 353: rdMatrix44_unk3 0x00e2ae80 rdMatrix44
    extern rdMatrix44 rdMatrix44_unk3;
    
    // Line 355: rdVector_unk4 0x00e2af90 rdVector3
    extern rdVector3 rdVector_unk4;
    
    // Line 357: rdVector3_unk2 0x00e2b470 rdVector3
    extern rdVector3 rdVector3_unk2;
    
    // Line 359: sound_music_volume 0x00e364a6 short
    extern short sound_music_volume;
    
    // Line 361: swrRace_UnlockDataBase 0x00e35a84 int
    extern int swrRace_UnlockDataBase;
    
    // Line 363: swrRace_truguts 0x00e35a98 int
    extern int swrRace_truguts;
    
    // Line 365: swrRace_nbPitDroids 0x00e35aa0 char
    extern char swrRace_nbPitDroids;
    
    // Line 366: swrRace_traction_upgrade_level 0x00e35aa1 char
    extern char swrRace_traction_upgrade_level;
    
    // Line 367: swrRace_turning_upgrade_level 0x00e35aa2 char
    extern char swrRace_turning_upgrade_level;
    
    // Line 368: swrRace_acceleration_upgrade_level 0x00e35aa3 char
    extern char swrRace_acceleration_upgrade_level;
    
    // Line 369: swrRace_topspeed_upgrade_level 0x00e35aa4 char
    extern char swrRace_topspeed_upgrade_level;
    
    // Line 370: swrRace_airbrake_upgrade_level 0x00e35aa5 char
    extern char swrRace_airbrake_upgrade_level;
    
    // Line 371: swrRace_cooling_upgrade_level 0x00e35aa6 char
    extern char swrRace_cooling_upgrade_level;
    
    // Line 372: swrRace_repair_upgrade_level 0x00e35aa7 char
    extern char swrRace_repair_upgrade_level;
    
    // Line 373: swrRace_traction_upgrade_health 0x00e35aa8 char
    extern char swrRace_traction_upgrade_health;
    
    // Line 374: swrRace_turning_upgrade_health 0x00e35aa9 char
    extern char swrRace_turning_upgrade_health;
    
    // Line 375: swrRace_acceleration_upgrade_health 0x00e35aaa char
    extern char swrRace_acceleration_upgrade_health;
    
    // Line 376: swrRace_topspeed_upgrade_health 0x00e35aab char
    extern char swrRace_topspeed_upgrade_health;
    
    // Line 377: swrRace_airbrake_upgrade_health 0x00e35aac char
    extern char swrRace_airbrake_upgrade_health;
    
    // Line 378: swrRace_cooling_upgrade_health 0x00e35aad char
    extern char swrRace_cooling_upgrade_health;
    
    // Line 379: swrRace_repair_upgrade_health 0x00e35aae char
    extern char swrRace_repair_upgrade_health;
    
    // Line 381: traction_upgrade_level 0x00e364f5 char
    extern char traction_upgrade_level;
    
    // Line 382: turning_upgrade_level 0x00e364f6 char
    extern char turning_upgrade_level;
    
    // Line 383: acceleration_upgrade_level 0x00e364f7 char
    extern char acceleration_upgrade_level;
    
    // Line 384: topspeed_upgrade_level 0x00e364f8 char
    extern char topspeed_upgrade_level;
    
    // Line 385: airbrake_upgrade_level 0x00e364f9 char
    extern char airbrake_upgrade_level;
    
    // Line 386: cooling_upgrade_level 0x00e364fa char
    extern char cooling_upgrade_level;
    
    // Line 387: repair_upgrade_level 0x00e364fb char
    extern char repair_upgrade_level;
    
    // Line 389: rdMatrix_unk8 0x00e37480 rdMatrix44
    extern rdMatrix44 rdMatrix_unk8;
    
    // Line 391: rdMatrix44_00e37580 0x00e37580 rdMatrix44
    extern rdMatrix44 rdMatrix44_00e37580;
    
    // Line 392: rdMatrixStack34 0x00e375c0 rdMatrix34[33]
    extern rdMatrix34 rdMatrixStack34[33];
    
    // Line 394: texture_buffer 0x00e93860 void*[1700] 
    extern void* texture_buffer[1700] ;
    
    // Line 396: texture_count 0x00e9823c unsigned int
    extern unsigned int texture_count;
    
    // Line 398: rdMatrix44_stack 0x00e985c0 rdMatrix44[32]
    extern rdMatrix44 rdMatrix44_stack[32];
    
    // Line 400: swrRace_SelectIndex 0x00e99240 int
    extern int swrRace_SelectIndex;
    
    // Line 402: swrRace_PodRotationAnimation 0x00e99384 float
    extern float swrRace_PodRotationAnimation;
    
    // Line 404: rdMatrix44_unk2 0x00e9b9e8 rdMatrix44
    extern rdMatrix44 rdMatrix44_unk2;
    
    // Line 406: sound_3d_gain_adjust 0x00e9e048 float
    extern float sound_3d_gain_adjust;
    
    // Line 408: array_classes_unk 0x00e9edc0 void*[300] 
    extern void* array_classes_unk[300] ;
    
    // Line 410: stdPlatform_hostServices 0x00e9f280 HostServices
    extern HostServices stdPlatform_hostServices;
    
    // Line 412: unicode_unk 0x00e9f3c4 wchar_t[32]
    extern wchar_t unicode_unk[32];
    
    // Line 414: unicode_unk2 0x00e9f380 wchar_t[32]
    extern wchar_t unicode_unk2[32];
    
    // Line 416: multiplayer_racer1_id 0x00ea0260 int
    extern int multiplayer_racer1_id;
    
    // Line 417: multiplayer_racer2_id 0x00ea0264 int
    extern int multiplayer_racer2_id;
    
    // Line 418: multiplayer_racer3_id 0x00ea0268 int
    extern int multiplayer_racer3_id;
    
    // Line 419: multiplayer_racer4_id 0x00ea026c int
    extern int multiplayer_racer4_id;
    
    // Line 420: multiplayer_racer5_id 0x00ea0270 int
    extern int multiplayer_racer5_id;
    
    // Line 421: multiplayer_racer6_id 0x00ea0274 int
    extern int multiplayer_racer6_id;
    
    // Line 422: multiplayer_racer7_id 0x00ea0278 int
    extern int multiplayer_racer7_id;
    
    // Line 423: multiplayer_racer8_id 0x00ea027c int
    extern int multiplayer_racer8_id;
    
    // Line 424: multiplayer_racer9_id 0x00ea0280 int
    extern int multiplayer_racer9_id;
    
    // Line 425: multiplayer_racer10_id 0x00ea0284 int
    extern int multiplayer_racer10_id;
    
    // Line 426: multiplayer_racer11_id 0x00ea0288 int
    extern int multiplayer_racer11_id;
    
    // Line 427: multiplayer_racer12_id 0x00ea028c int
    extern int multiplayer_racer12_id;
    
    // Line 428: multiplayer_racer13_id 0x00ea0290 int
    extern int multiplayer_racer13_id;
    
    // Line 429: multiplayer_racer14_id 0x00ea0294 int
    extern int multiplayer_racer14_id;
    
    // Line 430: multiplayer_racer15_id 0x00ea0298 int
    extern int multiplayer_racer15_id;
    
    // Line 431: multiplayer_racer16_id 0x00ea029c int
    extern int multiplayer_racer16_id;
    
    // Line 432: multiplayer_racer17_id 0x00ea02a0 int
    extern int multiplayer_racer17_id;
    
    // Line 433: multiplayer_racer18_id 0x00ea02a4 int
    extern int multiplayer_racer18_id;
    
    // Line 434: multiplayer_racer19_id 0x00ea02a8 int
    extern int multiplayer_racer19_id;
    
    // Line 435: multiplayer_racer20_id 0x00ea02ac int
    extern int multiplayer_racer20_id;
    
    // Line 436: multiplayer_track_select 0x00ea02b0 swrRace_TRACK
    extern swrRace_TRACK multiplayer_track_select;
    
    // Line 438: multiplayer_laps 0x00ea02b8 int
    extern int multiplayer_laps;
    
    // Line 440: swrConfig_FORCE_STRENGTH 0x00ec83e0 int
    extern int swrConfig_FORCE_STRENGTH;
    
    // Line 441: swrConfig_FORCE_AUTOCENTER 0x00ec83e4 int
    extern int swrConfig_FORCE_AUTOCENTER;
    
    // Line 442: swrConfig_FORCE_COLLISIONS 0x00ec83e8 int
    extern int swrConfig_FORCE_COLLISIONS;
    
    // Line 443: swrConfig_FORCE_DAMAGE 0x00ec83ec int
    extern int swrConfig_FORCE_DAMAGE;
    
    // Line 444: swrConfig_FORCE_TERRAIN 0x00ec83f0 int
    extern int swrConfig_FORCE_TERRAIN;
    
    // Line 445: swrConfig_FORCE_PODACTIONS 0x00ec83f4 int
    extern int swrConfig_FORCE_PODACTIONS;
    
    // Line 446: swrConfig_FORCE_GFORCES 0x00ec83f8 int
    extern int swrConfig_FORCE_GFORCES;
    
    // Line 447: swrConfig_FORCE_ENGINERUMBLE 0x00ec83fc int
    extern int swrConfig_FORCE_ENGINERUMBLE;
    
    // Line 449: rdCamera_mat 0x00ec8580 rdMatrix34
    extern rdMatrix34 rdCamera_mat;
    
    // Line 451: screen_height 0x00ec85e8 int
    extern int screen_height;
    
    // Line 452: rdCamera_main_ptr 0x00ec85ec rdCamera*
    extern rdCamera* rdCamera_main_ptr;
    
    // Line 454: swrConfig_VIDEO_REFLECTIONS 0x00ec86a0 int
    extern int swrConfig_VIDEO_REFLECTIONS;
    
    // Line 455: swrConfig_VIDEO_ZEFFECTS 0x00ec86a4 int
    extern int swrConfig_VIDEO_ZEFFECTS;
    
    // Line 456: swrConfig_VIDEO_DYNAMIC_LIGHTING 0x00ec86a8 int
    extern int swrConfig_VIDEO_DYNAMIC_LIGHTING;
    
    // Line 457: swrConfig_VIDEO_VSYNC 0x00ec86ac int
    extern int swrConfig_VIDEO_VSYNC;
    
    // Line 458: swrConfig_VIDEO_LENSFLARE 0x00ec86b0 int
    extern int swrConfig_VIDEO_LENSFLARE;
    
    // Line 459: swrConfig_VIDEO_ENGINEEXHAUST 0x00ec86b4 int
    extern int swrConfig_VIDEO_ENGINEEXHAUST;
    
    // Line 460: swrConfig_VIDEO_TEXTURE_RES 0x00ec86b8 int
    extern int swrConfig_VIDEO_TEXTURE_RES;
    
    // Line 461: swrConfig_VIDEO_MODEL_DETAIL 0x00ec86bc int
    extern int swrConfig_VIDEO_MODEL_DETAIL;
    
    // Line 462: swrConfig_VIDEO_DRAWDISTANCE 0x00ec86c0 int
    extern int swrConfig_VIDEO_DRAWDISTANCE;
    
    // Line 463: screen_width 0x00ec86c4 int
    extern int screen_width;
    
    // Line 465: tagRect 0x00ec86d0 tagRECT
    extern tagRECT tagRect;
    
    // Line 467: rdCanvas_main_ptr 0x00ec86e0 rdCanvas*
    extern rdCanvas* rdCanvas_main_ptr;
    
    // Line 469: g_mouse_x 0x00ec874c int
    extern int g_mouse_x;
    
    // Line 470: g_mouse_x2 0x00ec8750 int
    extern int g_mouse_x2;
    
    // Line 472: g_mouse_y 0x00ec8754 int
    extern int g_mouse_y;
    
    // Line 473: g_mouse_y2 0x00ec8754 int
    extern int g_mouse_y2;
    
    // Line 475: Deadzone 0x00ec876c float
    extern float Deadzone;
    
    // Line 477: flip_x_axis 0x00ec8790 int
    extern int flip_x_axis;
    
    // Line 478: flip_y_axis 0x00ec8794 int
    extern int flip_y_axis;
    
    // Line 479: flip_z_axis 0x00ec8798 int
    extern int flip_z_axis;
    
    // Line 481: swrRace_ThrottleInput 0x00ec8830 float
    extern float swrRace_ThrottleInput;
    
    // Line 483: swrRace_PitchInput 0x00ec883c float
    extern float swrRace_PitchInput;
    
    // Line 485: swrRace_ThrustInput 0x00ec884c float
    extern float swrRace_ThrustInput;
    
    // Line 486: swrRace_BoostInput 0x00ec8850 float
    extern float swrRace_BoostInput;
    
    // Line 488: stdPlatfom_FPU1 0x00ec8c80 unsigned short
    extern unsigned short stdPlatfom_FPU1;
    
    // Line 489: stdPlatfom_FPU2 0x00ec8c82 unsigned short
    extern unsigned short stdPlatfom_FPU2;
    
    // Line 490: stdPlatfom_FPU3 0x00ec8c84 unsigned int
    extern unsigned int stdPlatfom_FPU3;
    
    // Line 492: iDirectDrawSurface4_ptr 0x00ec8d00 LPDIRECTDRAWSURFACE4
    extern LPDIRECTDRAWSURFACE4 iDirectDrawSurface4_ptr;
    
    // Line 493: _ddSurfaceDesc2_2 0x00ec8d04 DDSURFACEDESC2
    extern DDSURFACEDESC2 _ddSurfaceDesc2_2;
    
    // Line 495: stdVBuffer_main 0x00ec8da0 stdVBuffer
    extern stdVBuffer stdVBuffer_main;
    
    // Line 500: swrConfig_buffer2 0x00ec9e84 char* 
    extern char*  swrConfig_buffer2;
    
    // Line 502: iDirectInputDeviceA_ptr2 0x00ecb484 LPDIRECTINPUTDEVICEA
    extern LPDIRECTINPUTDEVICEA iDirectInputDeviceA_ptr2;
    
    // Line 503: diDevCaps_ptr 0x00ecb488 LPDIDEVCAPS
    extern LPDIDEVCAPS diDevCaps_ptr;
    
    // Line 505: std_output_buffer 0x00ecbc20 char[0x800]
    extern char std_output_buffer[0x800];
    
    // Line 507: stdPlatform_hostServices_ptr 0x00ecc420 HostServices*
    extern HostServices* stdPlatform_hostServices_ptr;
    
    // Line 508: rdroid_hostServices_ptr 0x00ecc428 HostServices*
    extern HostServices* rdroid_hostServices_ptr;
    
    // Line 510: rdCamera_camMatrix 0x00ecc440 rdMatrix34
    extern rdMatrix34 rdCamera_camMatrix;
    
#ifdef __cplusplus
}
#endif

#endif // GLOBALS_H