#ifndef TYPES_ENUMS_H
#define TYPES_ENUMS_H

typedef enum rdCameraProjectType
{
    rdCameraProjectType_Ortho = 0,
    rdCameraProjectType_Perspective = 1,
    rdCameraProjectType_PerspMVP = 2
} rdCameraProjectType;

typedef enum swrLoader_TYPE
{
    swrLoader_TYPE_MODEL_BLOCK = 0,
    swrLoader_TYPE_SPRITE_BLOCK = 1,
    swrLoader_TYPE_SPLINE_BLOCK = 2,
    swrLoader_TYPE_TEXTURE_BLOCK = 3
} swrLoader_TYPE;

typedef enum swrObjHang_STATE
{
    // swrObjHang_STATE_ERROR = -1 == ~swrObjHang_STATE_LEGAL,
    swrObjHang_STATE_LEGAL = 0,
    swrObjHang_STATE_SPLASH = 1,
    swrObjHang_STATE_ENTER_NAME = 2,
    swrObjHang_STATE_MAIN_MENU = 3,
    swrObjHang_STATE_JUNKYARD = 4,
    swrObjHang_STATE_POST_RACE_INFO = 5,
    swrObjHang_STATE_UNKNOWN = 6,
    swrObjHang_STATE_WATTO = 7,
    swrObjHang_STATE_LOOK_AT_VEHICLE = 8,
    swrObjHang_STATE_SELECT_VEHICLE = 9,
    swrObjHang_STATE_SELECT_PLANET = 12,
    swrObjHang_STATE_SELECT_TRACK = 13,
    // more here to 18, but which ones ?
} swrObjHang_STATE;

// char sized enum the good old way
#define swrObjHang_TrackTier_AMATEUR (0)
#define swrObjHang_TrackTier_SEMIPRO (1)
#define swrObjHang_TrackTier_GALACTIC (2)
#define swrObjHang_TrackTier_INVITATIONAL (3)

typedef enum swrRace_TRACK
{
    swrRace_TRACK_BOONTA_TRAINING_COURSE = 0,
    swrRace_TRACK_BOONTA_CLASSIC = 1,
    swrRace_TRACK_BEEDOS_WILD_RIDE = 2,
    swrRace_TRACK_HOWLER_GORGE = 3,
    swrRace_TRACK_ANDOBI_MOUNTAIN_RUN = 4,
    swrRace_TRACK_ANDOBI_PRIME_CENTRUM = 5,
    swrRace_TRACK_AQUILARIS_CLASSIC = 6,
    swrRace_TRACK_SUNKEN_CITY = 7,
    swrRace_TRACK_BUMBYS_BREAKERS = 8,
    swrRace_TRACK_SCRAPPERS_RUN = 9,
    swrRace_TRACK_DETHROS_REVENGE = 10,
    swrRace_TRACK_ABYSS = 11,
    swrRace_TRACK_BAROO_COAST = 12,
    swrRace_TRACK_GRABVINE_GATEWAY = 13,
    swrRace_TRACK_FIRE_MOUNTAIN_RALLY = 14,
    swrRace_TRACK_INFERNO = 15,
    swrRace_TRACK_MON_GAZZA_SPEEDWAY = 16,
    swrRace_TRACK_SPICE_MINE_RUN = 17,
    swrRace_TRACK_ZUGGA_CHALLENGE = 18,
    swrRace_TRACK_VENGEANCE = 19,
    swrRace_TRACK_EXECUTIONER = 20,
    swrRace_TRACK_THE_GAUNTLET = 21,
    swrRace_TRACK_MALASTARE_100 = 22,
    swrRace_TRACK_DUG_DERBY = 23,
    swrRace_TRACK_SEBULBAS_LEGACY = 24
} swrRace_TRACK;

typedef enum swrSprite_NAME
{
    swrSprite_NAME_ALDARBEEDO = 0,
    swrSprite_NAME_BENQUADINAROS = 1,
    swrSprite_NAME_2 = 2,
    swrSprite_NAME_3 = 3,
    swrSprite_NAME_BULLSEYENAVIOR = 4,
    swrSprite_NAME_5 = 5,
    swrSprite_NAME_6 = 6,
    swrSprite_NAME_7 = 7,
    swrSprite_NAME_8 = 8,
    swrSprite_NAME_9 = 9,
    swrSprite_NAME_10 = 10,
    swrSprite_NAME_MARSGUO = 11,
    swrSprite_NAME_12 = 12,
    swrSprite_NAME_13 = 13,
    swrSprite_NAME_14 = 14,
    swrSprite_NAME_RATTSTYREL = 15,
    swrSprite_NAME_16 = 16,
    swrSprite_NAME_17 = 17,
    swrSprite_NAME_18 = 18,
    swrSprite_NAME_STARTINGGRIDONE = 19,
    swrSprite_NAME_STARTINGGRIDTWO = 20,
    swrSprite_NAME_STARTINGGRIDTHREE = 21,
    swrSprite_NAME_N64CONTROLLER = 22,
    swrSprite_NAME_CURSOR = 23,
    swrSprite_NAME_NOISE = 24,
    swrSprite_NAME_SPLINES = 25,
    swrSprite_NAME_26 = 26,
    swrSprite_NAME_SPLASHSCREEN = 27,
    swrSprite_NAME_28 = 28,
    swrSprite_NAME_29 = 29,
    swrSprite_NAME_30 = 30,
    swrSprite_NAME_31 = 31,
    swrSprite_NAME_32 = 32,
    swrSprite_NAME_FLARE1 = 33,
    swrSprite_NAME_FLARE2 = 34,
    swrSprite_NAME_35 = 35,
    swrSprite_NAME_ANAKINSKYWALKER = 36,
    swrSprite_NAME_GASGANO = 37,
    swrSprite_NAME_SEBULBA = 38,
    swrSprite_NAME_39 = 39,
    swrSprite_NAME_UIMETAL1 = 40,
    swrSprite_NAME_UIMETAL2 = 41,
    swrSprite_NAME_UIMETAL3 = 42,
    swrSprite_NAME_COLORRAMP = 43,
    swrSprite_NAME_RACERFLAGALDARBEEDO = 44,
    swrSprite_NAME_45 = 45,
    swrSprite_NAME_ENGINEPART1 = 46,
    swrSprite_NAME_ENGINEPART2 = 47,
    swrSprite_NAME_ENGINEPART3 = 48,
    swrSprite_NAME_ENGINEOUTLINE = 49,
    swrSprite_NAME_RACERFLAGANAKIN = 50,
    swrSprite_NAME_RACERFLAGBEN = 51,
    swrSprite_NAME_RACERFLAGBOLES = 52,
    swrSprite_NAME_RACERFLAGBOZZIE = 53,
    swrSprite_NAME_RACERFLAGBULLSEYE = 54,
    swrSprite_NAME_RACERFLAGARKBUMPY = 55,
    swrSprite_NAME_RACERFLAGCLEGG = 56,
    swrSprite_NAME_RACERFLAGDUD = 57,
    swrSprite_NAME_RACERFLAGEBE = 58,
    swrSprite_NAME_RACERFLAGELAN = 59,
    swrSprite_NAME_RACERFLAGFUD = 60,
    swrSprite_NAME_RACERFLAGGASGANO = 61,
    swrSprite_NAME_RACERFLAGMARS = 62,
    swrSprite_NAME_RACERFLAGMAWHONIC = 63,
    swrSprite_NAME_RACERFLAGNEVA = 64,
    swrSprite_NAME_RACERFLAGODY = 65,
    swrSprite_NAME_RACERFLAGRATTS = 66,
    swrSprite_NAME_RACERFLAGSEBULBA = 67,
    swrSprite_NAME_RACERFLAGSLIDE = 68,
    swrSprite_NAME_RACERFLAGTEEMTO = 69,
    swrSprite_NAME_RACERFLAGTOY = 70,
    swrSprite_NAME_RACERFLAGWAN = 71,
    swrSprite_NAME_72 = 72,
    swrSprite_NAME_73 = 73,
    swrSprite_NAME_74 = 74,
    swrSprite_NAME_75 = 75,
    swrSprite_NAME_76 = 76,
    swrSprite_NAME_77 = 77,
    swrSprite_NAME_78 = 78,
    swrSprite_NAME_79 = 79,
    swrSprite_NAME_80 = 80,
    swrSprite_NAME_STICK = 81,
    swrSprite_NAME_SETTINGSARROWRIGHT = 82,
    swrSprite_NAME_SETTINGSARROWRIGHTLIGHT = 83,
    swrSprite_NAME_84 = 84,
    swrSprite_NAME_85 = 85,
    swrSprite_NAME_86 = 86,
    swrSprite_NAME_N64 = 87,
    swrSprite_NAME_SETTINGSARROWUP = 88,
    swrSprite_NAME_SETTINGSARROWUPLIGHT = 89,
    swrSprite_NAME_90 = 90,
    swrSprite_NAME_91 = 91,
    swrSprite_NAME_FLAGFIRSTPLACE = 92,
    swrSprite_NAME_FLAGSECONDPLACE = 93,
    swrSprite_NAME_FLAGTHIRDPLACE = 94,
    swrSprite_NAME_95 = 95,
    swrSprite_NAME_ENGINEBORDER3 = 96,
    swrSprite_NAME_ENGINEBORDER4 = 97,
    swrSprite_NAME_98 = 98,
    swrSprite_NAME_SPEEDOMETERRAMP = 99,
    swrSprite_NAME_100 = 100,
    swrSprite_NAME_101 = 101,
    swrSprite_NAME_102 = 102,
    swrSprite_NAME_103 = 103,
    swrSprite_NAME_SPEEDOMETER = 104,
    swrSprite_NAME_105 = 105,
    swrSprite_NAME_106 = 106,
    swrSprite_NAME_107 = 107,
    swrSprite_NAME_108 = 108,
    swrSprite_NAME_109 = 109,
    swrSprite_NAME_110 = 110,
    swrSprite_NAME_111 = 111,
    swrSprite_NAME_112 = 112,
    swrSprite_NAME_113 = 113,
    swrSprite_NAME_114 = 114,
    swrSprite_NAME_115 = 115,
    swrSprite_NAME_116 = 116,
    swrSprite_NAME_117 = 117,
    swrSprite_NAME_118 = 118,
    swrSprite_NAME_119 = 119,
    swrSprite_NAME_120 = 120,
    swrSprite_NAME_121 = 121,
    swrSprite_NAME_122 = 122,
    swrSprite_NAME_123 = 123,
    swrSprite_NAME_124 = 124,
    swrSprite_NAME_125 = 125,
    swrSprite_NAME_126 = 126,
    swrSprite_NAME_FLARE3 = 127,
    swrSprite_NAME_FLARE4 = 128,
    swrSprite_NAME_129 = 129,
    swrSprite_NAME_ARTWORK_ANDOPRIME = 130,
    swrSprite_NAME_ARTWORK_AQUILARIS = 131,
    swrSprite_NAME_ARTWORK_ORDIBANNA = 132,
    swrSprite_NAME_ARTWORK_BAROONDA = 133,
    swrSprite_NAME_ARTWORK_MONGAZZA = 134,
    swrSprite_NAME_ARTWORK_OOVOIV = 135,
    swrSprite_NAME_ARTWORK_MALASTARE = 136,
    swrSprite_NAME_ARTWORK_TATOOINE = 137,
    swrSprite_NAME_ENGINEHALFGRADIENT = 138,
    swrSprite_NAME_ENGINEGRADIENT = 139,
    swrSprite_NAME_ENGINEBORDER1 = 140,
    swrSprite_NAME_ENGINEBORDER2 = 141,
    swrSprite_NAME_142 = 142,
    swrSprite_NAME_143 = 143,
    swrSprite_NAME_144 = 144,
    swrSprite_NAME_UI1 = 145,
    swrSprite_NAME_146 = 146,
    swrSprite_NAME_147 = 147,
    swrSprite_NAME_148 = 148,
    swrSprite_NAME_149 = 149,
    swrSprite_NAME_150 = 150,
    swrSprite_NAME_151 = 151,
    swrSprite_NAME_152 = 152,
    swrSprite_NAME_153 = 153,
    swrSprite_NAME_UI2 = 154,
    swrSprite_NAME_155 = 155,
    swrSprite_NAME_156 = 156,
    swrSprite_NAME_157 = 157,
    swrSprite_NAME_UI3 = 158,
    swrSprite_NAME_159 = 159,
    swrSprite_NAME_SPLASHSCREENWIDE = 160,
    swrSprite_NAME_EPISODE1 = 161,
    swrSprite_NAME_RACER = 162,
    swrSprite_NAME_STARWARS = 163,
    swrSprite_NAME_STAR = 164,
    swrSprite_NAME_WARS = 165,
    swrSprite_NAME_SPEEDOMETERRAMPBORDER = 166,
    swrSprite_NAME_LUCASARTS = 167,
    swrSprite_NAME_LUCASARTSGLOW = 168,
    swrSprite_NAME_FLARE5 = 169,
    swrSprite_NAME_THETEAM = 170,
    swrSprite_NAME_171 = 171,
    swrSprite_NAME_172 = 172,
    swrSprite_NAME_UI4 = 173,
    swrSprite_NAME_174 = 174,
    swrSprite_NAME_UI5 = 175,
    swrSprite_NAME_EXPANSIONPACK = 176,
    swrSprite_NAME_BUTTONZ = 177
} swrSprite_NAME;

typedef enum swrConfig_DEVICE
{
    swrConfig_DEVICE_JOYSTICK = 0,
    swrConfig_DEVICE_MOUSE = 1,
    swrConfig_DEVICE_KEYBOARD = 2,
} swrConfig_DEVICE;

typedef enum swr3DTextureFormatFLAGS
{
    swr3DTextureFormatFLAGS_UNINITIALIZED = 0,
    swr3DTextureFormatFLAGS_NOALPHAPIXELS = 1,
    swr3DTextureFormatFLAGS_ALPHAPIXELS = 2,
} swr3DTextureFormatFLAGS;

typedef enum rdCanvas_CLIP
{
    rdCanvas_CLIP_XUNDER = 1,
    rdCanvas_CLIP_XOVER = 0x10,
    rdCanvas_CLIP_YOVER = 0x100,
    rdCanvas_CLIP_YUNDER = 0x1000,
} rdCanvas_CLIP;

typedef enum swrModel_NAME
{
    swrModel_NAME_Anakin_Skywalker_MAlt = 0,
    swrModel_NAME_The_Boonta_Classic_Trak = 1,
    swrModel_NAME_Anakin_Skywalker_Podd = 2,
    swrModel_NAME_Teemto_Pagalies_MAlt = 3,
    swrModel_NAME_Teemto_Pagalies_Podd = 4,
    swrModel_NAME_Sebulba_MAlt = 5,
    swrModel_NAME_Sebulba_Podd = 6,
    swrModel_NAME_Ratts_Tyerell_MAlt = 7,
    swrModel_NAME_Ratts_Tyerell_Podd = 8,
    swrModel_NAME_Aldar_Beedo_Podd = 9,
    swrModel_NAME_Aldar_Beedo_MAlt = 10,
    swrModel_NAME_Mawhonic_MAlt = 11,
    swrModel_NAME_Mawhonic_Podd = 12,
    swrModel_NAME_Ark_Bumpy_Roose_Podd = 13,
    swrModel_NAME_Ark_Bumpy_Roose_MAlt = 14,
    swrModel_NAME_Wan_Sandage_Podd = 15,
    swrModel_NAME_Mars_Guo_Podd = 16,
    swrModel_NAME_Wan_Sandage_Podd2 = 17,
    swrModel_NAME_Mars_Guo_MAlt = 18,
    swrModel_NAME_Ebe_Endocott_MAlt = 19,
    swrModel_NAME_Ebe_Endocott_Podd = 20,
    swrModel_NAME_Dud_Bolt_MAlt = 21,
    swrModel_NAME_Dud_Bolt_Podd = 22,
    swrModel_NAME_Gasgano_MAlt = 23,
    swrModel_NAME_Gasgano_Podd = 24,
    swrModel_NAME_Clegg_Holdfast_MAlt = 25,
    swrModel_NAME_Clegg_Holdfast_Podd = 26,
    swrModel_NAME_Elan_Mak_MAlt = 27,
    swrModel_NAME_Elan_Mak_Podd = 28,
    swrModel_NAME_Neva_Kee_MAlt = 29,
    swrModel_NAME_Neva_Kee_Podd = 30,
    swrModel_NAME_Bozzie_Baranta_MAlt = 31,
    swrModel_NAME_Bozzie_Baranta_Podd = 32,
    swrModel_NAME_Boles_Roor_MAlt = 33,
    swrModel_NAME_Boles_Roor_Podd = 34,
    swrModel_NAME_Ody_Mandrell_MAlt = 35,
    swrModel_NAME_Ody_Mandrell_Podd = 36,
    swrModel_NAME_Fud_Sang_MAlt = 37,
    swrModel_NAME_Fud_Sang_Podd = 38,
    swrModel_NAME_Ben_Quadinaros_MAlt = 39,
    swrModel_NAME_Ben_Quadinaros_Podd = 40,
    swrModel_NAME_Slide_Paramita_MAlt = 41,
    swrModel_NAME_Slide_Paramita_Podd = 42,
    swrModel_NAME_Toy_Dampner_MAlt = 43,
    swrModel_NAME_Toy_Dampner_Podd = 44,
    swrModel_NAME_Bullseye_Navior_MAlt = 45,
    swrModel_NAME_Bullseye_Navior_Podd = 46,
    swrModel_NAME_Aquilaris_Vehicle_Part = 47,
    swrModel_NAME_Vehicle_Select_Flag_Part = 48,
    swrModel_NAME_AnakinPod_LightningBolt_Part = 49,
    swrModel_NAME_Control_Linkage_Part = 50,
    swrModel_NAME_Control_Shift_Plate_Part = 51,
    swrModel_NAME_Control_Vectro_Jet_Part = 52,
    swrModel_NAME_Control_Coupling_Part = 53,
    swrModel_NAME_Control_Nozzle_Part = 54,
    swrModel_NAME_Upgrade_Part_0 = 55,
    swrModel_NAME_Upgrade_Part_1 = 56,
    swrModel_NAME_Upgrade_Part_2 = 57,
    swrModel_NAME_Upgrade_Part_3 = 58,
    swrModel_NAME_Upgrade_Part_4 = 59,
    swrModel_NAME_Coffer_Part = 60,
    swrModel_NAME_Upgrade_Part_5 = 61,
    swrModel_NAME_Upgrade_Part_6 = 62,
    swrModel_NAME_Upgrade_Part_7 = 63,
    swrModel_NAME_Control_Stabilizer_Part = 64,
    swrModel_NAME_Upgrade_Part_8 = 65,
    swrModel_NAME_Upgrade_Part_9 = 66,
    swrModel_NAME_Upgrade_Part_10 = 67,
    swrModel_NAME_Double_Coffer_Part = 68,
    swrModel_NAME_Quad_Coffer_Part = 69,
    swrModel_NAME_Pit_Droid_Hover_Platform_Part = 70,
    swrModel_NAME_Guide_Arrow_Part = 71,
    swrModel_NAME_planet_Part_0 = 72,
    swrModel_NAME_planet_Part_1 = 73,
    swrModel_NAME_planet_Part_2 = 74,
    swrModel_NAME_planet_Part_3 = 75,
    swrModel_NAME_PlanetA_Part = 76,
    swrModel_NAME_PlanetB_Part = 77,
    swrModel_NAME_PlanetC_Part = 78,
    swrModel_NAME_Tatooine_Part = 79,
    swrModel_NAME_Baroonda_Part = 80,
    swrModel_NAME_Moon_Part = 81,
    swrModel_NAME_Ovoo_IV_Asteroid_Part = 82,
    swrModel_NAME_Hangar_Part = 83,
    swrModel_NAME_Wattos_Shop_Part = 84,
    swrModel_NAME_Wattos_Junkyard_Part = 85,
    swrModel_NAME_Teemto_Pagalies_Pupp = 86,
    swrModel_NAME_Anakin_Skywalker_Pupp = 87,
    swrModel_NAME_Gasgano_Pupp = 88,
    swrModel_NAME_Mawhonic_Pupp = 89,
    swrModel_NAME_Ody_Mandrell_Pupp = 90,
    swrModel_NAME_Sebulba_Pupp = 91,
    swrModel_NAME_Mars_Guo_Pupp = 92,
    swrModel_NAME_Ratts_Tyerell_Pupp = 93,
    swrModel_NAME_Ben_Quadinaros_Pupp = 94,
    swrModel_NAME_Ebe_Endocott_Pupp = 95,
    swrModel_NAME_Ark_Bumpy_Roose_Pupp = 96,
    swrModel_NAME_Clegg_Holdfast_Pupp = 97,
    swrModel_NAME_Dud_Bolt_Pupp = 98,
    swrModel_NAME_Wan_Sandage_Pupp = 99,
    swrModel_NAME_Elan_Mak_Pupp = 100,
    swrModel_NAME_Toy_Dampner_Pupp = 101,
    swrModel_NAME_Fud_Sang_Pupp = 102,
    swrModel_NAME_Neva_Kee_Pupp = 103,
    swrModel_NAME_Slide_Paramita_Pupp = 104,
    swrModel_NAME_Aldar_Beedo_Pupp = 105,
    swrModel_NAME_Bozzie_Baranta_Pupp = 106,
    swrModel_NAME_Boles_Roor_Pupp = 107,
    swrModel_NAME_Bullseye_Navior_Pupp = 108,
    swrModel_NAME_Pit_Droid_Pupp = 109,
    swrModel_NAME_Watto_Pupp = 110,
    swrModel_NAME_Dewback_Pupp = 111,
    swrModel_NAME_Ronto_Pupp = 112,
    swrModel_NAME_Jabba_Pupp = 113,
    swrModel_NAME_unk_Modl1 = 114,
    swrModel_NAME_Boonta_Training_Course_Trak = 115,
    swrModel_NAME_Mon_Gazza_Part = 116,
    swrModel_NAME_Ando_Prime_Part = 117,
    swrModel_NAME_Aquilaris_Part = 118,
    swrModel_NAME_Baroonda_Part2 = 119,
    swrModel_NAME_Trugut_Part = 120,
    swrModel_NAME_Malastare_Part = 121,
    swrModel_NAME_Ando_Prime_Centrum_Part = 122,
    swrModel_NAME_Flag_First_Blue_Part = 123,
    swrModel_NAME_Winners_Platform_Part = 124,
    swrModel_NAME_Flag_Second_Red_Part = 125,
    swrModel_NAME_Flag_Third_White_Part = 126,
    swrModel_NAME_StartOfTatooine_Part = 127,
    swrModel_NAME_Ando_Prime_Centrum_Trak = 128,
    swrModel_NAME_Inferno_Trak = 129,
    swrModel_NAME_Beedos_Wild_Ride_Trak = 130,
    swrModel_NAME_Howler_Gorge_Trak = 131,
    swrModel_NAME_Andobi_Mountain_Run_Trak = 132,
    swrModel_NAME_Aquilaris_Classic_Trak = 133,
    swrModel_NAME_Sunken_City_Trak = 134,
    swrModel_NAME_Bumpys_Breakers_Trak = 135,
    swrModel_NAME_Scrappers_Run_Trak = 136,
    swrModel_NAME_Dethros_Revenge_Trak = 137,
    swrModel_NAME_Abyss_Trak = 138,
    swrModel_NAME_Baroo_Coast_Trak = 139,
    swrModel_NAME_Grabvine_Gateway_Trak = 140,
    swrModel_NAME_Fire_Mountain_Rally_Trak = 141,
    swrModel_NAME_Mon_Gazza_Speedway_Trak = 142,
    swrModel_NAME_Spice_Mine_Run_Trak = 143,
    swrModel_NAME_Zugga_Challenge_Trak = 144,
    swrModel_NAME_Vengeance_Trak = 145,
    swrModel_NAME_AnakinPod_LB_2plane_Modl = 146,
    swrModel_NAME_Ball_For_Explosion_Part = 147,
    swrModel_NAME_Executioner_Trak = 148,
    swrModel_NAME_Jabbas_Spectator_Booth_Scen = 149,
    swrModel_NAME_Sebulba_Scen = 150,
    swrModel_NAME_texturedCircle_Modl = 151,
    swrModel_NAME_Jabbas_place_racers_Scen = 152,
    swrModel_NAME_Anakin_Skywalker_Scen = 153,
    swrModel_NAME_Cantina_Part = 154,
    swrModel_NAME_Opee_Sea_Killer_Pupp = 155,
    swrModel_NAME_Pods_Scen = 156,
    swrModel_NAME_Mark_II_Air_Brake_Part = 157,
    swrModel_NAME_Mark_III_Air_Brake_Part = 158,
    swrModel_NAME_Mark_IV_Air_Brake_Part = 159,
    swrModel_NAME_Mark_V_Air_Brake_Part = 160,
    swrModel_NAME_Tri_Jet_Air_Brake_Part = 161,
    swrModel_NAME_Quadrijet_Air_Brake_Part = 162,
    swrModel_NAME_Coolant_Radiator_Part = 163,
    swrModel_NAME_Stack_Radiator_Part_0 = 164,
    swrModel_NAME_Stack_Radiator_Part_1 = 165,
    swrModel_NAME_Rod_Coolant_Pump_Part = 166,
    swrModel_NAME_Dual_Coolant_Pump_Part = 167,
    swrModel_NAME_Turbo_Coolant_Pump_Part = 168,
    swrModel_NAME_Plug2_Thrust_Coil_Part = 169,
    swrModel_NAME_Plug3_Thrust_Coil_Part = 170,
    swrModel_NAME_Plug5_Thrust_Coil_Part = 171,
    swrModel_NAME_Plug8_Thrust_Coil_Part = 172,
    swrModel_NAME_Block5_Thrust_Coil_Part = 173,
    swrModel_NAME_Block6_Thrust_Coil_Part = 174,
    swrModel_NAME_HoloTable_Pupp = 175,
    swrModel_NAME_AndoPrime_IceStub_Modl = 176,
    swrModel_NAME_Beedos_Wild_Ride_Part = 177,
    swrModel_NAME_Howler_Gorge_Part = 178,
    swrModel_NAME_Andobi_Mountain_Run_Part = 179,
    swrModel_NAME_Aquilaris_Classic_Part = 180,
    swrModel_NAME_Sunken_City_Part = 181,
    swrModel_NAME_Malastare_100_Part = 182,
    swrModel_NAME_Dug_Derby_Part = 183,
    swrModel_NAME_Sebulbas_Legacy_Part = 184,
    swrModel_NAME_Bumpys_Breakers_Part = 185,
    swrModel_NAME_Scrappers_Run_Part = 186,
    swrModel_NAME_Dethros_Revenge_Part = 187,
    swrModel_NAME_Abyss_Part = 188,
    swrModel_NAME_Mon_Gazza_Speedway_Part = 189,
    swrModel_NAME_Spice_Mine_Run_Part = 190,
    swrModel_NAME_Inferno_Part = 191,
    swrModel_NAME_Zugga_Challenge_Part = 192,
    swrModel_NAME_Vengeance_Part = 193,
    swrModel_NAME_Executioner_Part = 194,
    swrModel_NAME_The_Gauntlet_Part = 195,
    swrModel_NAME_marker_flag_Part = 196,
    swrModel_NAME_marker_flag_Modl = 197,
    swrModel_NAME_Dual_20_PCX_Injector_Part = 198,
    swrModel_NAME_44_PCX_Injector_Part = 199,
    swrModel_NAME_Dual_32_PCX_Injector_Part = 200,
    swrModel_NAME_Quad_32_PCX_Injector_Part = 201,
    swrModel_NAME_Quad_44_Injector_Part = 202,
    swrModel_NAME_Mag_6_Injector_Part = 203,
    swrModel_NAME_R_20_Repulsorgirp_Part = 204,
    swrModel_NAME_R_60_Repulsorgirp_Part = 205,
    swrModel_NAME_R_80_Repulsorgirp_Part = 206,
    swrModel_NAME_Aldar_Beedo_Part = 207,
    swrModel_NAME_Anakin_Skywalker_Part = 208,
    swrModel_NAME_Ben_Quadinaros_Part = 209,
    swrModel_NAME_Boles_Roor_Part = 210,
    swrModel_NAME_Bozzie_Baranta_Part = 211,
    swrModel_NAME_Bullseye_Navior_Part = 212,
    swrModel_NAME_Ark_Bumpy_Roose_Part = 213,
    swrModel_NAME_Clegg_Holdfast_Part = 214,
    swrModel_NAME_Dud_Bolt_Part = 215,
    swrModel_NAME_Ebe_Endocott_Part = 216,
    swrModel_NAME_Elan_Mak_Part = 217,
    swrModel_NAME_Fud_Sang_Part = 218,
    swrModel_NAME_Gasgano_Part = 219,
    swrModel_NAME_Ratts_Tyerell_Part = 220,
    swrModel_NAME_Mars_Guo_Part = 221,
    swrModel_NAME_Mawhonic_Part = 222,
    swrModel_NAME_Neva_Kee_Part = 223,
    swrModel_NAME_Ody_Mandrell_Part = 224,
    swrModel_NAME_Sebulba_Part = 225,
    swrModel_NAME_Slide_Paramita_Part = 226,
    swrModel_NAME_Teemto_Pagalies_Part = 227,
    swrModel_NAME_Toy_Dampner_Part = 228,
    swrModel_NAME_Wan_Sandage_Part = 229,
    swrModel_NAME_R_100_Repulsorgirp_Part = 230,
    swrModel_NAME_The_Gauntlet_Trak = 231,
    swrModel_NAME_Malastare_100_Trak = 232,
    swrModel_NAME_Dug_Derby_Trak = 233,
    swrModel_NAME_Single_Power_Cell_Part = 234,
    swrModel_NAME_Dual_Power_Cell_Part = 235,
    swrModel_NAME_Baroo_Coast_Part = 236,
    swrModel_NAME_Quad_Power_Cell_Part = 237,
    swrModel_NAME_Cluster_Power_Plug_Part = 238,
    swrModel_NAME_Rotary_Power_Plug_Part = 239,
    swrModel_NAME_Control_Stabilizer_Part2 = 240,
    swrModel_NAME_R_300_Repulsorgirp_Part = 241,
    swrModel_NAME_R_600_Repulsorgirp_Part = 242,
    swrModel_NAME_Cluster_2_Power_Plug_Part = 243,
    swrModel_NAME_Hammerhead_Pupp = 244,
    swrModel_NAME_Anakin_Pupp = 245,
    swrModel_NAME_Jar_Jar_Binks_Pupp = 246,
    swrModel_NAME_Jawa_Pupp = 247,
    swrModel_NAME_R2D2_Pupp = 248,
    swrModel_NAME_Grabvine_Gateway_Part = 249,
    swrModel_NAME_Fire_Mountain_Rally_Part = 250,
    swrModel_NAME_Big_Rock_Explosion_Part = 251,
    swrModel_NAME_Small_Rock_Explosion_Part = 252,
    swrModel_NAME_Ord_Ibanna_Part = 253,
    swrModel_NAME_Ice_Explosion_Part = 254,
    swrModel_NAME_Sebulba_Part2 = 255,
    swrModel_NAME_Anakin_Skywalker_Part2 = 256,
    swrModel_NAME_Teemto_Pagalies_Part2 = 257,
    swrModel_NAME_Ratts_Tyerell_Part2 = 258,
    swrModel_NAME_Aldar_Beedo_Part2 = 259,
    swrModel_NAME_Mawhonic_Part2 = 260,
    swrModel_NAME_Ark_Bumpy_Roose_Part2 = 261,
    swrModel_NAME_Wan_Sandage_Part2 = 262,
    swrModel_NAME_Mars_Guo_Part2 = 263,
    swrModel_NAME_Ebe_Endocott_Part2 = 264,
    swrModel_NAME_Dud_Bolt_Part2 = 265,
    swrModel_NAME_Gasgano_Part2 = 266,
    swrModel_NAME_Clegg_Holdfast_Part2 = 267,
    swrModel_NAME_Elan_Mak_Part2 = 268,
    swrModel_NAME_Neva_Kee_Part2 = 269,
    swrModel_NAME_Bozzie_Baranta_Part2 = 270,
    swrModel_NAME_Boles_Roor_Part2 = 271,
    swrModel_NAME_Ody_Mandrell_Part2 = 272,
    swrModel_NAME_Fud_Sang_Part2 = 273,
    swrModel_NAME_Ben_Quadinaros_Part2 = 274,
    swrModel_NAME_Slide_Paramita_Part2 = 275,
    swrModel_NAME_Toy_Dampner_Part2 = 276,
    swrModel_NAME_Bullseye_Navior_Part2 = 277,
    swrModel_NAME_Tatooine_Starting_Line_Bridge_Part = 278,
    swrModel_NAME_Boonta_Training_Course_Part = 279,
    swrModel_NAME_Boonta_Classic_Part = 280,
    swrModel_NAME_AquilarisStadium_Scen = 281,
    swrModel_NAME_StartOfOrdIbanna_Scen = 282,
    swrModel_NAME_StartOfBaronda_Scen = 283,
    swrModel_NAME_StartofMonGazza_Scen = 284,
    swrModel_NAME_Part_Of_Oovo_Iv_ForVideo_Scen = 285,
    swrModel_NAME_Jabbas_Observation_Booth_Scen = 286,
    swrModel_NAME_Logo_LucasArt_Scen = 287,
    swrModel_NAME_Pods_Character_Scen_0 = 288,
    swrModel_NAME_Pods_Character_Scen_1 = 289,
    swrModel_NAME_Pods_Character_Scen_2 = 290,
    swrModel_NAME_Pods_Character_Scen_3 = 291,
    swrModel_NAME_Pods_Character_Scen_4 = 292,
    swrModel_NAME_Anakin_Skywalker_Scen2 = 293,
    swrModel_NAME_flames_Modl = 294,
    swrModel_NAME_for_explosion_unk_Part = 295,
    swrModel_NAME_Baroonda_Branch_Explosion_Part = 296,
    swrModel_NAME_Baroondas_Beach_Animatedsea_Modl = 297,
    swrModel_NAME_Jinn_Reeso_MAlt = 298,
    swrModel_NAME_Jinn_Reeso_Podd = 299,
    swrModel_NAME_Cy_Yunga_MAlt = 300,
    swrModel_NAME_Cy_Yunga_Podd = 301,
    swrModel_NAME_Jinn_Reeso_Part = 302,
    swrModel_NAME_Cy_Yunga_Part = 303,
    swrModel_NAME_Jinn_Reeso_Pupp = 304,
    swrModel_NAME_Cy_Yunga_Pupp = 305,
    swrModel_NAME_Rock_Explosion_Part = 306,
    swrModel_NAME_for_explosion_unk2_Part = 307,
    swrModel_NAME_Tatooine_Balloon_Part = 308,
    swrModel_NAME_methane_gass_effect_Part = 309,
    swrModel_NAME_Starting_Line_Object_Part = 310,
    swrModel_NAME_magma_explosion_Part = 311,
    swrModel_NAME_Mon_Gazza_Dozer_Part = 312,
    swrModel_NAME_unk_Part = 313,
    swrModel_NAME_unk_Modl = 314,
    swrModel_NAME_Sebulbas_Legacy_Trak = 315,
    swrModel_NAME_AnakinPod_LightningBolt_Modl = 316,
    swrModel_NAME_flames_Part = 317,
    swrModel_NAME_AnakinPod_Explosion_Part = 318,
    swrModel_NAME_Qui_Gon_Jinn_Pupp = 319,
    swrModel_NAME_Textured_Circle_Part = 320,
    swrModel_NAME_unk_Part1 = 321,
    swrModel_NAME_N64_Memory_Expansion_Pak_Part = 322,
} swrModel_NAME;

#endif // TYPES_ENUMS_H
