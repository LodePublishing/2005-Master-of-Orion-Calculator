#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream.h>
#include <time.h>
#include <malloc.h>

// Science Queue als eigenes Chromosom
//#define INHABITANTS 10
//#define ANDROIDS 11
#define MAX_SYSTEMS 25
#define MAX_PLANETS MAX_SYSTEMS*5
#define MAX_SHIPS 1000
#define MAX_X 20
#define MAX_Y 15 // tiny galaxy

struct trans
{
	unsigned char woher,wer,ok,time;
} Transport[10];

struct receiv
{
	unsigned char wohin,woher;
} Receive[10];

unsigned char TransportCounter,ReceiveCounter;

struct name
{
	char Name[35];
};

const name Orders[256]=
{
	{"Switch 1 Farmer to Industry"},
	{"Switch 1 Farmer to Science"},
	{"Switch 1 Worker to Farming"},
	{"Switch 1 Worker to Science"},
	{"Switch 1 Scientist to Farming"},
	{"Switch 1 Scientist to Industry"},
	{"Switch 3 Farmer to Industry"},
	{"Switch 3 Farmer to Science"},
	{"Switch 3 Worker to Farming"},
	{"Switch 3 Worker to Science"},
	{"Switch 3 Scientist to Farming"},
	{"Switch 3 Scientist to Industry"},
	{"Send 1 Farmer to ..."},
	{"Send 1 Worker to ..."},
	{"Send 1 Scientist to ..."},
	{"Send 3 Farmers to ..."},
	{"Send 3 Workers to ..."},
	{"Send 3 Scientists to ..."},
	{"Receive people from Queue 1"},
	{"Receive people from Queue 2"},
	{"Receive people from Queue 3"},
	{"Receive people from Queue 4"},
	{"Receive people from Queue 5"},
	{"Send ship 1 to ..."},
	{"Send ship 2 to ..."},
	{"Send ship 3 to ..."},
	{"Send ship 4 to ..."},
	{"Send ship 5 to ..."},
	{"Buy project ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Replace project with ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Queue Building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{"Sell building ..."},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""},
	{""}
};

const unsigned char mins[5]={1,2,3,5,8};
const unsigned char robominer[5]={5,8,10,15,20};
const unsigned char food[13]={0,0,0,3,2,2,1,2,1,1,0,0,0};
const unsigned char farming[4]={3,4,6,8};

const unsigned char growth[30][30]= //pop/size
{ 
	{0,  0,	0,	0,	0,	0,	0,	0,	0,	0,	0,   0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0   },
	{0,  34	,36	,38	,40	,40	,41	,41	,42	,42	,42	,42	,42	,43	,43	,43	,43	,43	,43	,43	,43	,43	,43	,43	,43	,43	,43	,43	,43	,43	},
	{0,  0	,36	,44	,48	,51	,53	,54	,55	,56	,57	,57	,58	,58	,58	,59	,59	,59	,60	,60	,60	,60	,60	,60	,60	,60	,60	,60	,60	,61	},
	{0,  0	,0	,38	,48	,54	,58	,61	,63	,64	,66	,67	,67	,68	,69	,69	,70	,70	,71	,71	,71	,71	,72	,72	,72	,72	,73	,73	,73	,73	},
	{0,  0	,0	,0	,40	,51	,58	,63	,66	,69	,71	,73	,74	,75	,76	,77	,78	,78	,79	,80	,80	,80	,81	,81	,82	,82	,82	,82	,83	,83	},
	{0,  0	,0	,0	,0	,40	,53	,61	,66	,70	,74	,76	,78	,80	,81	,82	,84	,84	,85	,86	,87	,87	,88	,88	,89	,89	,90	,90	,91	,91	},
	{0,  0	,0	,0	,0	,0	,41	,54	,63	,69	,74	,77	,80	,82	,84	,86	,88	,89	,90	,91	,92	,93	,94	,94	,95	,96	,97	,97	,97	,97	},
	{0,  0	,0	,0	,0	,0	,0	,41	,55	,64	,71	,76	,80	,83	,86	,88	,90	,92	,93	,95	,96	,97	,98	,99,100,101,102,102,102,103	},
	{0,  0	,0	,0	,0	,0	,0	,0	,42	,56	,66	,73	,78	,82	,86	,89	,92	,94	,95	,97	,99	,100,102,103,103,105,106,106,107,108},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,42	,57	,67	,74	,80	,84	,88	,92	,94	,97	,99	,101,103,104,106,107,108,109,110,111,112},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,42	,57	,67	,75	,81	,86	,90	,94	,97	,100,102,104,106,108,110,110,112,113,114,115},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,42	,58	,68	,76	,82	,88	,92	,95	,99	,102,104,107,109,111,112,113,115,116,118},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,42	,58	,69	,77	,84	,89	,93	,97	,101,104,107,109,112,113,115,117,118,120},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,58	,69	,78	,84	,90	,95	,99	,103,106,109,112,114,116,118,119,121},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,59	,70	,78	,85	,91	,96	,100,104,108,111,113,116,118,120,122},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,59	,70	,79	,86	,92	,97	,102,106,110,112,115,118,120,122},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,59	,71	,80	,87	,93	,98	,103,107,110,113,117,119,122},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,71	,80	,87	,94	,99	,103,108,112,115,118,121},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,71	,80	,88	,94	,100,105,109,113,116,120},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,71	,81	,88	,95	,101,106,110,114,118},
	{0,  0  ,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,72	,81	,89	,96	,102,106,111,115},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,72	,82	,89	,97	,102,107,112},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,72	,82	,90	,97,102	,108},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,72	,82	,90	,97,103},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,73	,82	,91	,97},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,73	,83	,91},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,73	,83},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,60	,73},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43	,61},
	{0,  0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,43}
};

unsigned char Area[8][15]; // Zeiger auf die einzelnen Areale

struct str
{
	unsigned char Field,Progress;
};

const str ScienceArea[200]=
{
	{0,0},{0,0},{0,0},
	{0,1},{0,1},{0,1},
	{0,2},{0,2},{0,2},
	{0,3},{0,3},{0,3},
	{0,4},{0,4},{0,4},
	{0,5},{0,5},{0,5},
	{0,6},{0,6},{0,6},
	{0,7},{0,7},{0,7},
	{0,8},{0,8},
	{0,9},{0,9},
	{0,10},{0,10},{0,10},
	{0,11},{0,11},

	{1,0},
	{1,1},
	{1,2},{1,2},{1,2},
	{1,3},{1,3},{1,3},
	{1,4},{1,4},{1,4},
	{1,5},{1,5},
	{1,6},{1,6},{1,6},
	{1,7},{1,7},{1,7},
	{1,8},{1,8},{1,8},

	{2,0},
	{2,1},{2,1},
	{2,2},{2,2},
	{2,3},{2,3},{2,3},
	{2,4},{2,4},{2,4},
	{2,5},{2,5},{2,5},
	{2,6},{2,6},

	{3,0},
	{3,1},{3,1},
	{3,2},
	{3,3},
	{3,4},{3,4},{3,4},{3,4},
	{3,5},
	
	{4,0},
	{4,1},{4,1},{4,1},
	{4,2},{4,2},{4,2},
	{4,3},{4,3},{4,3},
	{4,4},{4,4},{4,4},
	{4,5},{4,5},{4,5},
	{4,6},{4,6},{4,6},
	{4,7},{4,7},
	{4,8},{4,8},{4,8},

	
	{5,0},{5,0},
	{5,1},{5,1},{5,1},
	{5,2},{5,2},
	{5,3},{5,3},{5,3},
	{5,4},
	{5,5},{5,5},
	{5,6},{5,6},
	{5,7},{5,7},
	{5,8},{5,8},{5,8},

	{6,0},
	{6,1},{6,1},
	{6,2},{6,2},{6,2},
	{6,3},{6,3},
	{6,4},{6,4},{6,4},
	{6,5},{6,5},
	{6,6},{6,6},{6,6},
	{6,7},{6,7},{6,7},
	{6,8},{6,8},
	{6,9},{6,9},{6,9},
	{6,10},{6,10},{6,10}
};

#define T_PHYSICS 122

#define T_FUSION_BEAM 123
#define T_FUSION_RIFLE 124

#define T_TACHYON_COMMUNICATION 125
#define T_TACHYON_SCANNER 126
#define T_BATTLE_SCANNER 127

#define T_NEUTRON_BLASTER 128
#define T_NEUTRON_SCANNER 129

#define T_TRACTOR_BEAM 130
#define T_GRAVITON_BEAM 131
#define T_PLANETARY_GRAVITATION_GENERATION 132

#define T_SUBSPACE_COMMUNICATION 133
#define T_JUMP_GATE 134

#define T_PHASOR 135
#define T_PHASOR_RIFLE 136
#define T_MULTI_PHASE_SHIELD 137

#define T_PLASMA_CANNON 138
#define T_PLASMA_RIFLE 139
#define T_PLASMA_WEB 140

#define T_DISRUPTOR_CANNON 141
#define T_DIMENSION_PORTAL 142

#define T_HYPERSPACE_COMMUNICATION 143
#define T_SENSORS 144
#define T_MAULER_DEVICE 145

#define T_TIME_WARP_FACILITY 146
#define T_STELLAR_CONVERTER 147
#define T_STAR_GATE 148


#define T_CLASS_I_SHIELD 149
#define T_MASS_DRIVER 150
#define T_ECM_JAMMER 151

#define T_ANTI_GRAV 152 
#define T_INERTIAL_STABILISATOR 153
#define T_GYRO_DESTABILISATOR 154

#define T_CLASS_III_SHIELD 155
#define T_PLANETARY_RADIATION_SHIELD 156
#define T_WARP_DISSIPATOR 157

#define T_STEALTH_FIELD 158
#define T_PERSONAL_SHIELD 159
#define T_STEALTH_SUIT 160

#define T_PULSAR 161
#define T_WARP_INTERDICTOR 162
#define T_LIGTHNING_FIELD 163

#define T_CLASS_V_SHIELD 164
#define T_MULTIWAVE_ECM_JAMMER 165
#define T_GAUSS_CANNON 166

#define T_CLOAKING_DEVICE 167
#define T_STASIS_FIELD 168
#define T_HARD_SHIELDS 169

#define T_CLASS_VII_SHIELD 170
#define T_PLANETARY_FLUX_SHIELD 171
#define T_WIDE_AREA_JAMMER 172

#define T_DISPLACEMENT 173//(?)
#define T_SUBSPACE_TELEPORTER 174
#define T_INERTIAL_NULLIFIER 175

#define T_CLASS_X_SHIELD 176
#define T_PLANETARY_BARRIER_SHIELD 177
#define T_PHASING_CLOAK 178




unsigned short ScienceCosts[8][15]=
{
	//Construction
	80,
	150,
	250,
	400,
	650,
	900,
	1150,
	1500,
	2000,
	3500,
	6000,
	7500,
	0,
	0,
	0,
	//Chemistry
	50,
	250,
	650,
	1150,
	2000,
	4500,
	10000,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	//Power
	50,
	80,
	250,
	900,
	2000,
	2750,
	3500,
	4500,
	10000,
	0,
	0,
	0,
	0,
	0,
	0,

	//Sociology
	150,
	650,
	1150,
	2000,
	4500,
	6000,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	//Computers
	50,
	150,
	400,
	900,
	1500,
	2750,
	3500,
	4500,
	6000,
	0,
	0,
	0,
	0,
	0,
	0,
	//Biology
	80,
	400,
	900,
	1150,
	1500,
	2750,
	4500,
	7500,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	//Physics
	50,
	150,
	250,
	900,
	1150,
	1500,
	2000,
	3500,
	4500,
	6000,
	15000,
	0,
	0,
	0,
	0,
	//Force Fields
	250,
	650,
	900,
	1500,
	2000,
	2750,
	3500,
	4500,
	7500,
	15000,
	0,
	0,
	0,
	0,
	0
};



#define T_ANTI_MISSILE_ROCKET 0
#define T_FIGHTER_BAYS 1
#define T_REINFORCED_HULL 2
#define T_AUTOMATED_FACTORIES 3
#define T_MISSILE_BASE 4
#define T_HEAVY_ARMOR 5
#define T_BATTLE_PODS 6
#define T_TROOP_PODS 7
#define T_SURVIVAL_PODS 8
#define T_SPACE_PORT 9
#define T_ARMOR_BARRACKS 10
#define T_FIGHTER_GARRISONS 11
#define T_ROBO_MINE_PLANT 12
#define T_BATTLE_STATION 13
#define T_POWERED_ARMOR 14
#define T_FAST_MISSILE_RACKS 15
#define T_ADVANCED_DAMAGE_CONTROLS 16
#define T_ASSAULT_SHUTTLES 17
#define T_TITAN_CONSTRUCTION 18
#define T_GROUND_BATTERIES 19
#define T_BATTLEOIDS 20
#define T_RECYCLOTRON 21
#define T_AUTOREPAIR_UNIT 22
#define T_ARTIFICIAL_PLANET_CONSTRUCTION 23
#define T_ROBOTIC_FACTORY 24
#define T_BOMBER_BAYS 25
#define T_DEEP_CORE_MINE 26
#define T_CORE_WASTE_DUMP 27
#define T_STAR_FORTRESS 28
#define T_ADVANCED_CITY_PLANNING 29
#define T_HEAVY_FIGHTERS 30
#define T_DOOM_STAR_CONSTRUCTION 31
#define T_ARTEMIS_SYSTEM_NET 32

#define T_NUCLEAR_FUSION 33
#define T_COLD_FUSION 34
#define T_FUSION_DRIVE 35
#define T_FUSION_BOMB 36
#define T_AUGMENTED_ENGINES 37
#define T_ION_DRIVE 38
#define T_IONPULSE_CANNON 39
#define T_SHIELD_CAPACITY 40
#define T_ANTI_MATTER_DRIVE 41
#define T_ANTI_MATTER_TORPEDO 42
#define T_ANTI_MATTER_BOMB 43
#define T_TRANSPORTERS 44
#define T_FOOD_REPLICATOR 45
#define T_HIGH_ENERGY_FOCUS 46
#define T_ENERGY_ABSORBER 47
#define T_MEGAFLUX 48
#define T_PROTON_TORPEDO 49
#define T_HYPER_DRIVE 50
#define T_HYPERX_CAPACITY 51
#define T_INTERPHASE_DRIVE 52
#define T_PLASMA_TORPEDO 53
#define T_NEUTRONIUM_BOMB 54

#define T_CHEMISTRY 55
#define T_DEUTERIUM_FUEL 56
#define T_TRITANIUM_ARMOR 57
#define T_MERCULITE_MISSILE 58
#define T_POLLUTION_PROCESSOR 59
#define T_PULSON_MISSILE 60
#define T_ATMOSPHERE_RENEWER 61
#define T_IRIDIUM_FUEL 62
#define T_NANO_DISASSEMBLER 63
#define T_MICROLITE_CONSTRUCTION 64
#define T_ZORTIUM_ARMOR 65
#define T_ZEON_MISSILE 66
#define T_NEUTRONIUM_ARMOR 67
#define T_URIDIUM_FUEL 68
#define T_THORIUM_FUEL 69
#define T_ADAMANTIUM_ARMOR 70

#define T_SPACE_ACADEMY 71
#define T_XENO_PSYCHOLOGY 72
#define T_ALIEN_CONTROL_CENTER 73
#define T_STOCK_EXCHANGE 74
#define T_ASTRO_UNIVERSITY 75
#define T_CONFEDERATION 76
#define T_IMPERIUM 77
#define T_FEDERATION 78
#define T_GALACTIC_UNIFICATION 79
#define T_GALACTIC_CURRENCY_EXCHANGE 80

#define T_ELECTRONIC_COMPUTER 81
#define T_RESEARCH_LAB 82
#define T_OPTRONIC_COMPUTER 83
#define T_GUIDIANCE_SYSTEM (?)
#define T_NEURAL_SCANNER 85
#define T_SCOUT_LAB 86
#define T_SECURITY_STATIONS 87
#define T_POSITRONIC_COMPUTER 88
#define T_PLANETARY_SUPERCOMPUTER 89
#define T_HOLO_SIMULATOR 90
#define T_EMISSION_GUIDIANCE_SYSTEM 91
#define T_RANGEMASTER 92
#define T_CYBER_SECURITY_LINK 93
#define T_CYBERTRONIC_COMPUTER 94
#define T_AUTOLAB 95
#define T_STRUCTURAL_ANALYZER 96
#define T_ANDROID_FARMERS 97
#define T_ANDROID_WORKERS 98
#define T_ANDROID_SCIENTISTS 99
#define T_VIRTUAL_REALITY_NETWORK 100
#define T_GALACTICAL_CYBERNETWORK 101
#define T_PLEASURE_DOME 102
#define T_MOLECULAR_COMPUTER 103
#define T_ACHILLES_TARGETING_SYSTEM 104

#define T_HYDROPONIC_FARM 105
#define T_BIOSPHERES 106
#define T_CLONING_CENTER 107
#define T_SOIL_ENRICHEMENT 108
#define T_DEATH_SPORES 109
#define T_TELEPATHIC_TRAINING 110
#define T_MICROBIOTICS 111
#define T_TERRAFORMING 112
#define T_SUBBTERRAN_FARMS 113
#define T_WEATHER_CONTROL_SYSTEM 114
#define T_PSIONICS 115
#define T_INTELLIGENCE_GROWTH 116
#define T_BIO_TERMINATOR 117
#define T_UNIVERSAL_ANTIDOTE 118
#define T_BIOMORPH_FUNGI 119
#define T_GAIA_TRANSFORMATION 120
#define T_EVOLUTIONARY_MUTATION 121

#define T_PHYSICS 122
#define T_FUSION_BEAM 123
#define T_FUSION_RIFLE 124
#define T_TACHYON_COMMUNICATION 125
#define T_TACHYON_SCANNER 126
#define T_BATTLE_SCANNER 127
#define T_NEUTRON_BLASTER 128
#define T_NEUTRON_SCANNER 129
#define T_TRACTOR_BEAM 130
#define T_GRAVITON_BEAM 131
#define T_PLANETARY_GRAVITATION_GENERATION 132
#define T_SUBSPACE_COMMUNICATION 133
#define T_JUMP_GATE 134
#define T_PHASOR 135
#define T_PHASOR_RIFLE 136
#define T_MULTI_PHASE_SHIELD 137
#define T_PLASMA_CANNON 138
#define T_PLASMA_RIFLE 139
#define T_PLASMA_WEB 140
#define T_DISRUPTOR_CANNON 141
#define T_DIMENSION_PORTAL 142
#define T_HYPERSPACE_COMMUNICATION 143
#define T_SENSORS 144
#define T_MAULER_DEVICE 145
#define T_TIME_WARP_FACILITY 146
#define T_STELLAR_CONVERTER 147
#define T_STAR_GATE 148

#define T_CLASS_I_SHIELD 149
#define T_MASS_DRIVER 150
#define T_ECM_JAMMER 151
#define T_ANTI_GRAV 152 //(?)
#define T_INERTIAL_STABILISATOR 153
#define T_GYRO_DESTABILISATOR 154
#define T_CLASS_III_SHIELD 155
#define T_PLANETARY_RADIATION_SHIELD 156
#define T_WARP_DISSIPATOR 157
#define T_STEALTH_FIELD 158
#define T_PERSONAL_SHIELD 159
#define T_STEALTH_SUIT 160
#define T_PULSAR 161
#define T_WARP_FIELD 162 //(?)
#define T_LIGTHNING_FIELD 163
#define T_CLASS_V_SHIELD 164
#define T_MULTIWAVE_ECM_JAMMER 165
#define T_GAUSS_CANNON 166
#define T_CLOAKING_DEVICE 167
#define T_STASIS_FIELD 168
#define T_HARD_SHIELDS 169
#define T_CLASS_VII_SHIELD 170
#define T_PLANETARY_FLUX_SHIELD 171//(?)
#define T_WIDE_AREA_JAMMER 172
#define T_DISPLACEMENT 173//(?)
#define T_SUBSPACE_TELEPORTER 174
#define T_INERTIAL_NULLIFIER 175
#define T_CLASS_X_SHIELD 176
#define T_PLANETARY_BARRIER_SHIELD 177
#define T_PHASING_CLOAK 178

unsigned char tbcs[3]=
{
	1,2,4
};


unsigned short prod[62]=
{
	200,
	400,
	60,
	60,
	120,
	80,
	150,
	150,
	150,
	600,
	200,
	200,
	800,
	200,
	250,
	200,
	2100,
	1000,
	500,
	50,
	100,
	100,
	200,
	80,
	150,
	100,
	60,
	150,
	200,
	60,
	150,
	120,
	200,
	50,
	50,
	50,
	250,
	250,
	60,
	60,
	100,
	120,
	250, //(!! +X*250)
	150,
	200,
	500,
	500,
	1000,
	200,
	80,
	300,
	200,
	500,
	120,
	100,
	200,
	0,
	0,
	0,
	0,
	0,
	0
};

unsigned char cost[62]=
{
	0,
	2,
	1,
	2,
	1,
	2,
	2,
	2,
	3,
	2,
	3,
	0,
	3,
	3,
	8,
	4,
	5,
	0,
	0,
	0,
	0,
	10,
	1,
	3,
	2,
	1,
	2,
	4,
	1,
	2,
	1,
	3,
	0,
	0,
	0,
	3,
	3,
	2,
	1,
	2,
	0,
	0,
	4,
	3,
	0,
	2,
	6,
	1,
	3,
	3,
	5,
	2,	
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};




#define B_TRADING_GOODS 0
#define B_COLONY_BASE 1
#define B_STAR_BASE 2
#define B_MARINE_BARRACKS 3
#define B_AUTOMATED_FACTORIES 4
#define B_MISSILE_BASE 5
#define B_SPACE_PORT 6
#define B_ARMOR_BARRACKS 7
#define B_FIGHTER_GARRISON 8
#define B_ROBO_MINE_PLANT 9
#define B_BATTLE_STATION 10
#define B_GROUND_BATTERIES 11
#define B_RECYCLOTRON 12
#define B_ARTIFICIAL_PLANET_CONSTRUCTION 13
#define B_ROBOTIC_FACTORY 14
#define B_DEEP_CORE_MINE 15
#define B_CORE_WASTE_DUMP 16
#define B_STAR_FORTRESS 17
#define B_ARTEMIS_SYSTEM_NETWORK 18

#define B_COLONY_SHIP 19
#define B_FREIGHTERS 20
#define B_OUTPOST_SHIP 21
#define B_TRANSPORT 22
#define B_FOOD_REPLICATOR 23
#define B_POLLUTION_PROCESSOR 24
#define B_ATOMOSPHERE_RENEWER 25

#define B_SPACE_ACADEMY 26
#define B_ALIEN_CONTROL_CENTER 27    
#define B_STOCK_EXCHANGE 28
#define B_ASTRO_UNIVERSITY 29

#define B_RESEARCH_LAB 30
#define B_PLANETARY_SUPERCOMPUTER 31
#define B_HOLO_SIMULATOR 32
#define B_AUTOLAB 33
#define B_ANDROID_FARMER 34
#define B_ANDROID_WORKER 35
#define B_ANDROID_SCIENTIST 36
#define B_GALACTIC_CYBERNETWORK 37
#define B_PLEASURE_DOME 38

#define B_HYDROPONIC_FARM 39
#define B_BIOSPHERES 40
#define B_CLONING_CENTER 41
#define B_SOIL_ENRICHMENT 42
#define B_TERRAFORMING 43
#define B_SUBTERRAN_FARMS 44
#define B_WEATHER_CONTROL_SYSTEM 45
#define B_GAIA_TRANSFORMATION 46

#define B_DIMENSION_PORTAL 47
#define B_STELLAR_CONVERTER 48
#define B_PLANETARY_RADIATION_SHIELD 49
#define B_WARP_FIELD_DISSIPATOR 50
#define B_PLANETARY_FLUX_SHIELD 51
#define B_PLANETARY_BARRIER_SHIELD 52

#define B_GRAVITY_GENERATOR 53

#define B_SPY 54
#define B_GOVERNMENT_CENTER 55
#define B_HOUSING 56

#define B_SHIP_1 57
#define B_SHIP_2 58
#define B_SHIP_3 59
#define B_SHIP_4 60
#define B_SHIP_5 61

#define MAX_BUILDINGS 62


#define P_FEUDALISM 0
#define P_DICTATORSHIP 1
#define P_DEMOCRACY 2
#define P_UNIFICATION 3
#define P_WARLORD 4

#define P_AQUATIC 5
#define P_SUBTERRAN 6
#define P_LOWG 7
#define P_HIGHG 8
#define P_LARGE_HOMEWORLD 9
#define P_RICH_HOMEWORLD 10
#define P_POOR_HOMEWORLD 11
#define P_ARTIFACTS_HOMEWORLD 12
#define P_CYBERNETIC 13
#define P_LITHOVORE 14
#define P_TOLERANT 15
#define P_LUCK 16
#define P_CHARM 17
#define P_TELEPATH 18
#define P_OMNISCIENT 19
#define P_FANTASTIC_TRADER 20
#define P_TRANS_DIMENSIONAL 21
#define P_05GROWTH 22
#define P_15GROWTH 23
#define P_20GROWTH 24
#define P_15FOOD 25
#define P_30FOOD 26
#define P_40FOOD 27
#define P_20INDUSTRY 28
#define P_40INDUSTRY 29
#define P_50INDUSTRY 30
#define P_20SCIENCE 31
#define P_40SCIENCE 32
#define P_50SCIENCE 33
#define P_05BCS 34
#define P_15BCS 35
#define P_20BCS 36
#define P_08ATTACK 37
#define P_12ATTACK 38
#define P_15ATTACK 39
#define P_08DEFENSE 40
#define P_12DEFENSE 41
#define P_15DEFENSE 42
#define P_09GROUND 43
#define P_11GROUND 44
#define P_12GROUND 45
#define P_09SPY 46
#define P_11SPY 47
#define P_12SPY 48
#define P_CREATIVE 49
#define P_UNCREATIVE 50
#define P_REPULSIVE 51

#define MAX_PICKS 52

signed char PickCosts[MAX_PICKS]=
{
	-4,0,7,6,4,5,6,-5,6,1,2,-1,3,4,10,10,3,3,6,3,4,5,-4,3,6,-3,4,7,-3,3,6,-3,3,6,-4,5,8,-2,2,4,-2,3,7,-2,2,4,-3,3,6,8,-4,-6
}


struct Ships
{
	unsigned char Type; //0: Outpost, 1: Transporter, 2: Colony Ship, 3: Fighter, 4: Corvette, 5: Cruiser, 6: Battle Ship, 7: Titan, 8: Dead Star
	unsigned char Destination,Start,Progress;
};


#define PL_NONE 0
#define PL_GAS_PLANET 1
#define PL_ASTEROIDS 2
#define PL_GAIA 3
#define PL_TERRAN 4
#define PL_OCEAN 5
#define PL_TUNDRA 6
#define PL_SWAMP 7
#define PL_DESERT 8
#define PL_ARID 9
#define PL_RADIATED 10
#define PL_BARREN 11
#define PL_TOXIC 12

class Planets
{
public:
	
	unsigned char Type; // 0: does not exist, 1: gas planet, 2: asteroids, 3: gaia, 4: terran, 5: ocean, 6: tundra, 7: swamp, 8: desert, 9: arid, 10: radiated, 11: barren, 12: toxic
	unsigned char Size; //=0 for non-habitable objects, 1: very small, 2: small, 3: medium, 4: large, 5: huge
	unsigned char Settlement; //0=empty, 1=outpost, 2=colony
	unsigned char Minerals; // 0=Ultra Poor, 1=Poor, 2=average, 3=rich, 4=ultra rich
	unsigned char Special; //0=none, 1=gold, 2=diamonds, 3: tech, 4: inhabitants, 5: splinter colony
	unsigned char Gravitation; // 0=Low-G, 1=1 G, 2=High-G
	unsigned char BQueue[10];

	short Industry,Food,Science,Money;
	unsigned char FoodDemand,IndustryDemand;
	unsigned char Farmers,Workers,Scientists;
	unsigned char maxPop;
	unsigned char Building[60];
	unsigned short progress; // Production that is in the actual project
	unsigned char System;
	unsigned short overpop;
	unsigned char Population;
	unsigned char checked;
	unsigned char bought;

	void Planets::AddQueue(unsigned char item) // end
{
		unsigned char j;
	if(CanBuild(item)==1)
		for(j=0;j<10;j++)
			if(BQueue[j]==0)
			{
				BQueue[j]=item;
				j=10;
			}
}

	unsigned char Planets::CanBuild(unsigned char item)
{
/*	not already in queue
	tech availible
	not availible because of grav/race/already built in system?
	not already built*/
		return 1;
}

	void Planets::InsertinQueue(unsigned char item) // 1. place
{
	unsigned char j;

	if((CanBuild(item)==1)&&(bought==0))
	{
		for(j=10;j>1;j--)
			BQueue[j]=BQueue[j-1];
		BQueue[0]=item;
	}
}

	void Planets::SwitchPeople(unsigned char who)
{
	switch(who)
	{
		case 0:if(Farmers>0) { Farmers--;Workers++;};break;//F -> W
		case 1:if(Farmers>0) { Farmers--;Scientists++;};break;//F -> S
		case 2:if(Workers>0) { Workers--;Farmers++;};break;//W -> F
		case 3:if(Workers>0) { Workers--;Scientists++;};break;//W -> S
		case 4:if(Scientists>0) { Scientists--;Farmers++;};break;//S -> F
		case 5:if(Scientists>0) { Scientists--;Workers++;};break;//S -> W
			//evtl noch Farmen verbieten, wenn Produktion 0 betraegt.
	}
}

unsigned char Planets::TransportPeople(unsigned char who)
{
	switch(who)
	{
		case 0:if(Farmers>0) Farmers--;return 1;break;
		case 1:if(Workers>0) Scientists--;return 1;break;
		case 2:if(Scientists>0) Scientists--;return 1;break;
	}
	return 0;
}

///~!!!  Wichtig, fuer scc auch so ein receive und send benutzen und durch die locations einzeln durchwechseln
//wesentlich besser als chobomaessig rein
} planet[MAX_PLANETS];

struct systems
{
//	unsigned char Color;
	Planets* Object[5]; //evtl pointer auf Planeten drauf
	unsigned char x,y;
//	unsigned char Special;  //Monsters, Time-stops etc.
	char Name [20];
//	unsigned char planetcount;
} System[MAX_SYSTEMS];

	Planets* p;





class player
{
//Genes:
public:
	unsigned char picks[MAX_PICKS];
	unsigned char OQueue[1000];
	unsigned char SQueue[50];

//temp
	unsigned long bcs;
	unsigned char tech[200];
	unsigned short OC,SC,PC; //OrderCounter, ScienceQueueCounter, Planetcounter
	unsigned long science,Freighter;
	short AvailibleFood,AvailibleFreighters,Fitness;//,Commando;
	Ships Ship[MAX_SHIPS];

	unsigned char player::SearchNextPlanet()
	{
		unsigned char b;
		b=PC+1;
		while(b!=PC)
		{
			if(b>=MAX_PLANETS) b=0;
			if(planet[b].Settlement==2)
			{
				if(planet[b].checked==1)
					return 255;
				planet[b].checked=1;
				return b;
			}
			b++;
		}
	}

	unsigned char player::Order(unsigned char what)
	{
		p=&planet[PC];
		switch(what)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:PC=SearchNextPlanet();break;//NOP und Ende noch einfuegen
			case 5:p->SwitchPeople(0);break;
			case 6:p->SwitchPeople(1);break;
			case 7:p->SwitchPeople(2);break;
			case 8:p->SwitchPeople(3);break;
			case 9:p->SwitchPeople(4);break;
			case 10:p->SwitchPeople(5);break;
			case 11:p->SwitchPeople(0);p->SwitchPeople(0);p->SwitchPeople(0);break;
			case 12:p->SwitchPeople(1);p->SwitchPeople(1);p->SwitchPeople(1);break;
			case 13:p->SwitchPeople(2);p->SwitchPeople(2);p->SwitchPeople(2);break;
			case 14:p->SwitchPeople(3);p->SwitchPeople(3);p->SwitchPeople(3);break;
			case 15:p->SwitchPeople(4);p->SwitchPeople(4);p->SwitchPeople(4);break;
			case 16:p->SwitchPeople(5);p->SwitchPeople(5);p->SwitchPeople(5);break;
			case 17:
			case 18:
			case 19:if((AvailibleFreighters>4)&&(p->TransportPeople(what-17)&&(TransportCounter<10))==1)
					{
						Transport[TransportCounter].woher=PC;
						Transport[TransportCounter].wer=what-17;
						Transport[TransportCounter].ok=0;
						TransportCounter++;
					};break;
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
				if((p->Population<p->maxPop)&&(Transport[what-20].ok==0))
					{		
						Transport[what-20].ok=1;
						Receive[ReceiveCounter].wohin=PC;
						Receive[ReceiveCounter].woher=what-20;
						ReceiveCounter++;

						// Anders loesen... muessen ja mehr als 10x Leute erschickt werden koennen...
					}


//		case ... :if(prod[BQueue[0]]*4<bcs)
//				  {
//					  bcs-=prod[BQueue[0]]*4;
//					  progress=prod[BQueue[0]];
//					  // noch Building als 'gekauft' markieren, um Cheaten zu verhindern
//				  }
//		case 24x:science[sciencecounter]=SearchScienceProject(number,row); //in ne Zahl halt umwandeln und ueberpruefen ob noch erforschbar oder net

//		case 63x:buildingcounter++;for(i=1;i<buildingcounter;i++) BQueue[i]=BQueue[i-1];
//				BQueue[0]=63x;
//				break;
//		case 63x: if buildingcounter<10
//				 {
//					BQueue[buildingcounter]=63x;buildingcounter++;
//				 }
//			break;

//SellBuilding: if(building63x vorhanden)
//			  {
//				  bcs+=prod[63x]/4;
//				  building[63x]=0;
//			  }

	}
		if(PC==255) return 1;
		return 0;
}


/*genes: 10 Befehle pro Planet, dann wird weitergeschalten, wenn nix mehr da is, naechste Runde

6x - NOP/Complete
12x - Switch People (1..6 x 2 (1 oder 3 verschieben, damits weniger Befehle sind))
6x - Transport People (1, 3 transportieren, x 3 (scientists, Workers, Farmers))

5x - Receive People Nr. 1..5 in Queue (Befehl am Schluss Abarbeiten, sonst kann Nr. 1 von Nr. 6 nix empfangen)
5x - Send ship Nr. 1..5 in Orbit
5x - Receive Ship Nr. 1..5 in Queue

1x - buy project with bcs
63x - Replace (0..Max Buildings)
63x - Insert in Building Queue (0..Max Buildings) ~~~
63x - sell building (0..Max Building) ~~

~~~~~~~~ Evtl noch machen, dass die Planeten aufgerufen werden, sobald was fertig is...
Nur problematisch, wenn Scienc Projekt grad fertig wurde und z.B. Factories gebaut werden muessen
mmmh...

=> Da man auch Geld kriegt, Leute nachwachsen etc. jede Runde aufrufen.


-_-
=> Byte befehl*/



unsigned char player::CanResearch(unsigned char what)
{
	if(tech[what]==1) return 0;
	if(Area[ScienceArea[what].Field][ScienceArea[what].Progress]==1) return 0; //Feld schon erforscht
	switch(what)
	{
		case T_POLLUTION_PROCESSOR:
		case T_ATMOSPHERE_RENEWER:
		case T_NANO_DISASSEMBLER:
		case T_CORE_WASTE_DUMP:if(picks[P_TOLERANT]==1) return 0;break;
		case T_HYDROPONIC_FARM:
		case T_SOIL_ENRICHEMENT:
		case T_SUBBTERRAN_FARMS:
		case T_FOOD_REPLICATOR:if(picks[P_LITHOVORE]==1) return 0;break;
		case T_CONFEDERATION:if(picks[P_FEUDALISM]==0) return 0;break;
		case T_IMPERIUM:if(picks[P_DICTATORSHIP]==0) return 0;break;
		case T_FEDERATION:if(picks[P_DEMOCRACY]==0) return 0;break;
		case T_GALACTIC_UNIFICATION:if(picks[P_UNIFICATION]==0) return 0;break;
		case T_HOLO_SIMULATOR:
		case T_VIRTUAL_REALITY_NETWORK:
		case T_PLEASURE_DOME:if(picks[P_UNIFICATION]==1) return 0;break;
	};
	return 1;
}

	void player::BetweenTime()
{
	unsigned char i,j,k;
	float gravitation,moral;
//	race* r;

//for(i=0;i<MAX_PEOPLE;i++)
//	planet[people[i].planet].All++;
	//	for(i=0;i<250;i++)
//		planet[people[i].planet].population[people[i].race]++; //Volkszaehlung
//~~~~~~~~~~~~~~~~~~~~~~
//	for(i=0;i<MAX_PLANETS;i++)
//		for(j=0;j<10;j++)
//			planet[i].All+=planet[i].population[j];

//Daten noch resetten!

//maxpop noch rein
//	for(i=0;

	//100 Zuege durchlaufen lassen

	for(k=0;((k<100)&&(OC<1000));k++)
	{

	for(i=0;i<MAX_PLANETS;i++)
		if((planet[i].Type>0)&&(planet[i].Settlement==2))
		{
			p=&planet[i];

//	growth; //0:*0, 1: *0.5, 2: *1, 3: *1.5, 4: *2

//	growth
			gravitation=0;
			if(p->Building[B_GRAVITY_GENERATOR]==0)
			{
				gravitation+=(p->Gravitation==1)*picks[P_LOWG]*0.25;
				gravitation+=(p->Gravitation==0)*(picks[P_LOWG]==0)*0.25;
				gravitation+=(p->Gravitation==2)*(picks[P_HIGHG]==0)*0.5;
			}	
			p->Food=0;p->Industry=0;p->Science=0;
			if(picks[P_CYBERNETIC]==1)
			{
				p->FoodDemand=p->Population*0.5;
				p->IndustryDemand=p->Population*0.5;
			} else
			p->FoodDemand=p->Population;
				// else => Lithovore
			moral=
			-((p->Building[B_MARINE_BARRACKS]==0)*(p->Building[B_ARMOR_BARRACKS]==0)*(tech[T_IMPERIUM]==0)*picks[P_DICTATORSHIP]*0.2)
			-((p->Building[B_MARINE_BARRACKS]==0)*(p->Building[B_ARMOR_BARRACKS]==0)*picks[P_FEUDALISM]*0.2)
			+(p->Building[B_HOLO_SIMULATOR]*0.2)
			+(tech[T_VIRTUAL_REALITY_NETWORK]*0.2)
			+(p->Building[B_PLEASURE_DOME]*0.3)
			+(tech[T_PSIONICS]*picks[P_FEUDALISM]*+tech[T_PSIONICS]*picks[P_DICTATORSHIP])*0.1
			+(tech[T_IMPERIUM]*0.2);
			
			p->Money=(
				(p->Special==1)*5+(p->Special==2)*10
			+p->Population*tbcs[picks[P_BCS]])*

			(1+
							  p->Building[B_SPACE_PORT]*0.5
							 +p->Building[B_STOCK_EXCHANGE]
							 +picks[P_DEMOCRACY]*0.5
							 +tech[T_FEDERATION]*0.25
							 +tech[T_GALACTIC_CURRENCY_EXCHANGE]
							);

			p->Food=p->Farmers* (1
							 +picks[P_UNIFICATION]*0.5
							 +tech[T_GALACTIC_UNIFICATION]*0.5
							 -gravitation
							 +moral*(picks[P_UNIFICATION]==0)
							 )
							
							*(
							food[p->Type]+tech[T_BIOMORPH_FUNGI]
							+((food[p->Type]+tech[T_BIOMORPH_FUNGI])>0)*
							(p->Building[B_ASTRO_UNIVERSITY]
							+p->Building[B_SOIL_ENRICHMENT]
							+p->Building[B_WEATHER_CONTROL_SYSTEM]*2
							+farming[picks[P_FOOD]]/2
							)
							+p->Building[B_HYDROPONIC_FARM]*2
							+p->Building[B_SUBTERRAN_FARMS]*4
							);
				
			p->Industry+=p->Workers*
					(mins[p->Minerals]
						+tech[T_MICROLITE_CONSTRUCTION]
						+p->Building[B_ASTRO_UNIVERSITY]
						+p->Building[B_AUTOMATED_FACTORIES]
						+p->Building[B_ROBO_MINE_PLANT]*2
						+p->Building[B_DEEP_CORE_MINE]*3)
						*
						(1
						 +picks[P_UNIFICATION]*0.5
						 +tech[T_GALACTIC_UNIFICATION]*0.5
						 -gravitation
						 +moral*(picks[P_UNIFICATION]==0)
						);
			if( (p->Industry>2*p->Size*(tech[T_NANO_DISASSEMBLER]+1))&&(p->Building[B_CORE_WASTE_DUMP]==0))
				p->Industry-=
						0.5
						*(1-picks[P_TOLERANT])
						*(1-0.5*p->Building[B_POLLUTION_PROCESSOR])
						*(1-0.75*p->Building[B_ATOMOSPHERE_RENEWER])
						*( p->Industry -2*p->Size * (tech[T_NANO_DISASSEMBLER]+1));

			p->Industry+=p->Building[B_AUTOMATED_FACTORIES]*5
					+p->Building[B_ROBO_MINE_PLANT]*10
							+p->Building[B_DEEP_CORE_MINE]*15
							+p->Building[B_ROBOTIC_FACTORY]*robominer[p->Minerals]
							+p->Population*p->Building[B_RECYCLOTRON];


			p->Science+=p->Scientists*( (p->Special==3)*2+ 
						+p->Building[B_RESEARCH_LAB]
						+p->Building[B_PLANETARY_SUPERCOMPUTER]
						+p->Building[B_GALACTIC_CYBERNETWORK]
						+p->Building[B_ASTRO_UNIVERSITY]
						+tech[T_INTELLIGENCE_GROWTH])
						*
						(1
						 +picks[P_DEMOCRACY]*0.5
							 +tech[T_FEDERATION]*0.25
						 -picks[P_FEUDALISM]*0.5
						 -gravitation
						 +moral*(picks[P_UNIFICATION]==0)
					)
					+p->Building[B_RESEARCH_LAB]*5
						+p->Building[B_PLANETARY_SUPERCOMPUTER]*10
						+p->Building[B_GALACTIC_CYBERNETWORK]*15
						+p->Building[B_AUTOLAB]*30;

//				Alle Leute überprüfen wegen tolerant, aquatisch, subterran
//				Size, Typ

			p->Food-=p->FoodDemand;
			if(p->Food>0)
				AvailibleFood+=p->Food;
//			if(p->Industry>=p->IndustryDemand)
//			{
//			}
			// else hungern, keine Freighters!!
			p->Industry-=p->IndustryDemand;

			if(p->Industry>0)
				{
					if(p->BQueue[0]==B_TRADING_GOODS)
					{
						if(picks[P_FANTASTIC_TRADER]==1)
							bcs+=p->Industry;
						else bcs+=p->Industry/2;
					}
					else if(p->BQueue[0]==B_HOUSING)
					{
						p->overpop+=p->Industry*(growth[p->Population][p->maxPop] / (2.5*p->Population));
						//bonus
					}
					else
					{
						p->progress+=p->Industry;
						if(p->progress>=prod[p->BQueue[0]])
						{
							p->progress-=prod[p->BQueue[0]];
							p->Building[p->BQueue[0]]=1;
							for(j=0;j<9;j++)
								p->BQueue[i]=p->BQueue[i+1];
							if(p->BQueue[0]==0) 
							{
								if(p->Population>=p->maxPop)
									p->BQueue[0]=B_TRADING_GOODS;
								else
									p->BQueue[0]=B_HOUSING;
							}
						}
					}

				p->overpop+=(growth[p->Population][p->maxPop]*picks[P_GROWTH])/2;
				while(p->overpop>999)
				{
					p->overpop-=1000;
					p->Population++;
					p->Workers++;
				}


				}
				science+=p->Science;
			}

		if(science>ScienceCosts[ScienceArea[SQueue[SC]].Field][ScienceArea[SQueue[SC]].Progress])
		{
			science=0;//-=science[ScienceProjekt]; oder wird doch aufgespart?
			tech[SQueue[SC]]=1;
			while(CanResearch(SQueue[SC])==0) SC++;
			//~~~~~~~~~~ Abbruchbedingung rein
		}
			
			for(i=0;i<MAX_PLANETS;i++)
				if((planet[i].Type>0)&&(planet[i].Settlement==2))
				{
					p=&planet[i];
					if((p->Food<0)&&(AvailibleFood>0)&&(AvailibleFreighters>0))
					{
						if((AvailibleFood>=-p->Food)&&(AvailibleFreighters>=-p->Food))
						{
							p->Food=0;
							AvailibleFood-=p->Food;
							AvailibleFreighters-=p->Food;
						}
						else
						{
							if(AvailibleFood>AvailibleFreighters)
							{
								p->Food+=AvailibleFreighters;
								AvailibleFood-=AvailibleFreighters;
								AvailibleFreighters=0;								
							}
							else
							{
								p->Food+=AvailibleFood;
								AvailibleFreighters-=AvailibleFood;
								AvailibleFood=0;
							}
						}
					}
				}





			//Aktion

			while((Order(OQueue[OC])==0)&&(OC<1000)) OC++;




			}


			for(i=0;i<10;i++)
				if(Transport[Receive[i].woher].time>0)
				{
					Transport[Receive[i].woher].time--;
					if(Transport[Receive[i].woher].time==0)
					{
						AvailibleFreighters+=5;
						switch(Transport[Receive[i].woher].wer)
						{
							case 0:planet[Receive[i].wohin].Farmers++;break;
							case 1:planet[Receive[i].wohin].Workers++;break;
							case 2:planet[Receive[i].wohin].Scientists++;break;
						}
					}
				}
			

				//hungern noch rein
						
			
//			if(tech[T_IMPERIUM])
//				Commando*=1.5; //?? oder werden anführer mit einberechnet?
			
//			for(j=0;j<8;j++)
//				if(leader[j]>0)
//				{
//					bcs+=Leader[leader[j]].Wealth*10;
//					science+=Leader[leader[j]].Scientist;
//					Commando+=Leader[leader[j]].Commando;
//				}
//			for(j=0;j<MAX_SHIPS;j++)
//			{
//				if(Ship[j].Type<3)
//					Commando--;
//				else
//				if(Ship[j].Type<9)
//					Commando-=(Ship[j].Type-2);
//				if(Commando<0)
//					bcs+=Commando*10;

				//Weiterfliegen, System als gescoutet vermelden etc.

//			}

		for(i=0;i<MAX_PLANETS;i++)
			Fitness=p->Population*(p->Settlement==2);
}


void player::Init()
{
	unsigned short i;
	PC=0;//...
	for(i=0;i<50;i++)
		picks[i]=0;
	bcs=50;
	OC=0;SC=0;PC=0;
	science=0;Freighter=0;
	AvailibleFood=0;AvailibleFreighters=0;
	for(i=0;i<200;i++)
		tech[i]=0;
//	for(i=0;i<MAX_SHIPS;i++)
//		Ship[i]. ....;
	
//		...

//	1 Colony Ship
//	Starbase
//	Infantery
//	...
//	fitness=0;

//		Planeten resetten?
};

void player::RestartGalaxy() // aufruf pro durchgang ~~~~~~~~
{
		int rcounter,pcounter,counter,i,j,t,s,k;//,temp;
		counter=0; // Für Leute
		rcounter=0;
		unsigned short Home_System;
//		temp=0;

		//Alles resetten, auf unerforscht stellen

				//Galaxie erstellen
		for(i=0;i<MAX_SYSTEMS;i++)
		{
			System[i].x=rand()%MAX_X;
			System[i].y=rand()%MAX_Y;
			for(j=0;j<5;j++)
			{
				p=System[i].Object[j];
				p->Type=rand()%13; // noch anpassen, gaia unwahrscheinlicher etc.
				
				
				if(p->Type>2)
				{
					if(picks[P_AQUATIC])
					{
						if((p->Type==PL_OCEAN)||(p->Type==PL_TERRAN))
							p->Type=PL_GAIA;
						else if((p->Type==PL_TUNDRA)||(p->Type==PL_SWAMP))
							p->Type=PL_TERRAN;
					}
					t=p->Type;
				
					p->Size=rand()%5+1;
					if(rand()%20==0)
					{
						p->Special=rand()%4+1; //Splinter mal weglassen
					} else p->Special=0;	
					s=p->Size;
					t=p->Type;

					p->maxPop+=(picks[P_SUBTERRAN]*2*s);
					if(picks[P_TOLERANT])
					{
						switch(t)
						{
							
							case PL_GAIA:
							case PL_TERRAN:p->maxPop+=5*s;break;
							case PL_ARID:if(s>1) p->maxPop+=4*s+1; else p->maxPop+=4;break;
							case PL_SWAMP:if(s>1) p->maxPop+=4*s+1; else p->maxPop+=4;break;
							default:
								switch(s)
								{
									case 1:
									case 2:p->maxPop+=2+s;break;
									case 3:
									case 4:p->maxPop+=2*s;break;
									case 5:p->maxPop+=1+2*s;break;
								};break;
						}
					}
					else
					{
						switch(t)
						{
							case PL_GAIA:p->maxPop+=5*s;break;
							case PL_TERRAN:p->maxPop+=4*s;break;
							case PL_ARID:p->maxPop+=3*s;break;
							case PL_SWAMP:p->maxPop+=2*s;break;
							default:if(s==1) p->maxPop++;
								else p->maxPop+=s+1;
								break;
						}
					}
				}

				else
					{
						p->Size=0;
						p->Special=0;
						p->maxPop=0;							
					}

				for(k=0;k<10;j++)
					p->BQueue[k]=0;
				for(k=0;k<MAX_BUILDINGS;k++)
					p->Building[k]=0;
				p->Farmers=0;
				p->Scientists=0;
				p->Workers=0;
				p->Food=0;
				p->Industry=0;
				p->Science=0;
				p->Money=0;
				p->IndustryDemand=0;
				p->FoodDemand=0;
				p->Gravitation=rand()%3;
				p->Minerals=rand()%5;
				p->Settlement=0;
				p->progress=0;
				p->System=i;
				p->overpop=0;
				p->Population=0;
				//planet[i].Gravitation=size, minerals
				//huge 50%, large 25%, normal 10%, small 5%
				//tiny 50%, small 25%, normal 10%, large 5%
				//urich -20%, 
		}
		//Heimatwelt erstellen*/
		Home_System=rand()%MAX_SYSTEMS;
		p=System[Home_System].Object[rand()%5];
		p->Building[B_GOVERNMENT_CENTER]=1;
		p->Building[B_MARINE_BARRACKS]=1;
		p->Building[B_STAR_BASE]=1;
		bcs=50;
//		if(Game_Avg_Tech)
			{
				tech[T_NUCLEAR_FUSION]=1;
				tech[T_COLD_FUSION]=1;
				tech[T_CHEMISTRY]=1;
				tech[T_ELECTRONIC_COMPUTER]=1;
				tech[T_PHYSICS]=1;
				//Schiffe!
			}
			// kein Advanced Tech... bringt nix
//				if(picks[P_OMNISCIENT])
//					for(j=0;j<MAX_SYSTEMS];j++)
//						System[j].Scouted[?]=1;

		if(picks[P_LARGE_HOMEWORLD])
			p->Size=4;
		else p->Size=3;
	
		if(picks[P_RICH_HOMEWORLD])
			p->Minerals=3;
		else
		if(picks[P_POOR_HOMEWORLD])
			p->Minerals=1;
		else
			p->Minerals=2;

		if(picks[P_ARTIFACTS_HOMEWORLD])
			p->Special=3;

		if(picks[P_HIGHG])
			p->Gravitation=2;
		else
		if(picks[P_LOWG])
			p->Gravitation=0;
		else p->Gravitation=1;

		if(picks[P_AQUATIC])
			p->Type=5;
		else
			p->Type=4;

			
			}




};


void player::Create()
{
	unsigned short i,p,m,t;
	picks
	unsigned char OQueue[1000];
	unsigned char SQueue[50];
	
	
	muss mit add remove gemacht werden
		und halt dann immer chekcen obs passt

	while(
	{
		t=rand()%MAX_PICKS;

#define P_05GROWTH 22
#define P_15GROWTH 23
#define P_20GROWTH 24
#define P_15FOOD 25
#define P_30FOOD 26
#define P_40FOOD 27
#define P_20INDUSTRY 28
#define P_40INDUSTRY 29
#define P_50INDUSTRY 30
#define P_20SCIENCE 31
#define P_40SCIENCE 32
#define P_50SCIENCE 33
#define P_05BCS 34
#define P_15BCS 35
#define P_20BCS 36
#define P_08ATTACK 37
#define P_12ATTACK 38
#define P_15ATTACK 39
#define P_08DEFENSE 40
#define P_12DEFENSE 41
#define P_15DEFENSE 42
#define P_09GROUND 43
#define P_11GROUND 44
#define P_12GROUND 45
#define P_09SPY 46
#define P_11SPY 47
#define P_12SPY 48
#define P_CREATIVE 49
#define P_UNCREATIVE 50
#define P_REPULSIVE 51

			switch(t)
			{

			case P_FEUDALISM:
				if((Picks[P_FEUDALISM]==0)&&(m<=6))
				{
					m+=4;
					Picks[P_FEUDALISM]=1;

					if(Picks[P_DICTATORSHIP]==1)
						Picks[P_DICTATORSHIP]=0;
					else
					if(Picks[P_DEMOCRACY]==1)
					{
						Picks[P_DEMOCRACY]=0;
						p-=7;
					}
					else
					if(Picks[P_UNIFICATION]==1)
					{
						Picks[P_UNIFICATION]=0;
						p-=6;
					}
				};break;
			case P_DICTATORSHIP:
				if(Picks[P_DICTATORSHIP]==0)
				{
					Picks[P_DICTATORSHIP]=1;
					if(Picks[P_FEUDALISM]==1)
					{
						m-=4;
						Picks[P_FEUDALISM]=0;
					}
					else 
					if(Picks[P_DEMOCRACY]==1)
					{
						p-=7;
						Picks[P_DEMOCRACY]=0;
					}					
					if(Picks[P_UNIFICATION]==1)
					{
						p-=6;
						Picks[P_UNIFICATION]=0;
					}
				};break;
			case P_DEMOCRACY:
				if((Picks[P_DEMOCRACY]==0)&&(p+(-6*Picks[P_UNIFICATION])<=3+m+(-4*Picks[P_FEUDALISM]))
				{
					p+=7;
					Picks[P_DEMOCRACY]=1;
					if(Picks[P_FEUDALISM]==1)
					{
						m-=4;
						Picks[P_FEUDALISM]=0;
					}
					else 
					if(Picks[P_DICTATORSHIP]==1)
						Picks[P_DICTATORSHIP]=0;
					if(Picks[P_UNIFICATION]==1)
					{
						p-=6;
						Picks[P_UNIFICATION]=0;
					}
				};break;
			case P_UNIFICATION:
				if((Picks[P_UNIFICATION]==0)&&(p+(-7*Picks[P_DEMOCRACY])<=4+m+(-4*Picks[P_FEUDALISM]))
				{
					p+=6;
					Picks[P_UNIFICATION]=1;
					if(Picks[P_FEUDALISM]==1)
					{
						m-=4;
						Picks[P_FEUDALISM]=0;
					}
					else 
					if(Picks[P_DICTATORSHIP]==1)
						Picks[P_DICTATORSHIP]=0;
					if(Picks[P_DEMOCRACY]==1)
					{
						p-=7;
						Picks[P_DEMOCRACY]=0;
					}
				};break;						  

			case P_WARLORD:
			case P_AQUATIC:
			case P_SUBTERRAN:
			case P_LARGE_HOMEWORLD:
			case P_ARTIFACTS_HOMEWORLD:
			case P_TOLERANT:
			case P_LUCK:
			case P_CHARM:
			case P_TELEPATH:
			case P_OMNISCIENT:
			case P_FANTASTIC_TRADER:
			case P_TRANS_DIMENSIONAL:
				if(Picks[t]==1)
				{
					p-=PickCosts[t];
					Picks[t]=0;
				}
				else
				if(p<=10-PickCosts[t]+m)
				{
					p+=PickCosts[t];
					Picks[t]=1;
				};break;

			case P_LOWG:
				if(Picks[P_LOWG]==1)
				{
					m+=PickCosts[P_LOWG];
					Picks[P_LOWG]=0;
				}
				else
				if((Picks[P_HIGHG]==1)&&(m<=5)
				{
					p-=PickCosts[P_HIGHG];
					m-=PickCosts[P_LOWG];
					Picks[P_HIGHG]=0;
					Picks[P_LOWG]=1;
				}
				else
				if(m<=5)
				{
					m-=PickCosts[P_LOWG];
					Picks[P_LOWG]=1;
				};break;
			case P_HIGHG:
				if(Picks[P_HIGHG]==1)
				{
					p-=PickCosts[P_HIGHG];
					Picks[P_HIGHG]=0;
				}
				else
				if((Picks[P_LOWG]==1)&&(p+1<=m)
				{
					p+=PickCosts[P_HIGHG];
					m+=PickCosts[P_LOWG];
					Picks[P_HIGHG]=1;
					Picks[P_LOWG]=0;
				}
				else
				if(p<=4+m)
				{
					p+=PickCosts[P_HIGHG];
					Picks[P_HIGHG]=1;
				};break;

			case P_RICH_HOMEWORLD:
				if(Picks[P_RICH_HOMEWORLD]==1)
				{
					p-=PickCosts[P_RICH_HOMEWORLD];
					Picks[P_RICH_HOMEWORLD]=0;
				}
				else
				if((Picks[P_POOR_HOMEWORLD]==1)&&(p<=7+m)
				{
					p+=PickCosts[P_RICH_HOMEWORLD];
					m+=PickCosts[P_POOR_HOMEWORLD];
					Picks[P_RICH_HOMEWORLD]=1;
					Picks[P_POOR_HOMEWORLD]=0;
				}
				else
				if(p<=8+m)
				{
					p+=PickCosts[P_RICH_HOMEWORLD];
					Picks[P_RICH_HOMEWORLD]=1;
				};break;
			case P_POOR_HOMEWORLD:
				if(Picks[P_POOR_HOMEWORLD]==1)
				{
					m+=PickCosts[P_POOR_HOMEWORLD];
					Picks[P_POOR_HOMEWORLD]=0;
				}
				else
				if((Picks[P_RICH_HOMEWORLD]==1)&&(m<=9)
				{
					p-=PickCosts[P_RICH_HOMEWORLD];
					m-=PickCosts[P_POOR_HOMEWORLD];
					Picks[P_RICH_HOMEWORLD]=0;
					Picks[P_POOR_HOMEWORLD]=0;
				}
				else
				if(m<=9)
				{
					m-=PickCosts[P_POOR_HOMEWORLD];
					Picks[P_POOR_HOMEWORLD]=1;
				};break;

			case P_CYBERNETIC:
				if(Picks[P_CYBERNETIC]==1)
				{
					p-=PickCosts[P_CYBERNETIC];
					Picks[P_CYBERNETIC]=0;
				}
				else
				if(Picks[P_LITHOVORE]==1)
				{
					p+=6;
					Picks[P_CYBERNETIC]=1;
					Picks[P_LITHOVORE]=0;
				}
				else
				if(p<=6+m)
				{
					p+=PickCosts[P_CYBERNETIC];
					Picks[P_CYBERNETIC]=1;
				};break;
			case P_LITHOVORE:
				if(Picks[P_LITHOVORE]==1)
				{
					p+=PickCosts[P_LITHOVORE];
					Picks[P_LITHOVORE]=0;
				}
				else
				{
					if(Picks[P_CYBERNETIC]==1)
					{
						if((Picks[P_15FOOD]==1)&&(p<=m-9))
						{
							m+=PickCosts[P_15FOOD];
							p-=PickCosts[P_CYBERNETIC];
							p+=PickCosts[P_LITHOVORE];
							Picks[P_15FOOD]=0;
							Picks[P_CYBERNETIC]=0;
							Picks[P_LITHOVORE]=1;
						}
						else 
						if((Picks[P_30FOOD]==1)&&(p<=m-2))
						{
							p-=PickCosts[P_30FOOD];
							p-=PickCosts[P_CYBERNETIC];
							p+=PickCosts[P_LITHOVORE];
							Picks[P_30FOOD]=0;
							Picks[P_CYBERNETIC]=0;
							Picks[P_LITHOVORE]=1;
						}
						else 
						if((Picks[P_40FOOD]==1)&&(p<=m+1))
						{
							p-=PickCosts[P_40FOOD];
							p-=PickCosts[P_CYBERNETIC];
							p+=PickCosts[P_LITHOVORE];
							Picks[P_40FOOD]=0;
							Picks[P_CYBERNETIC]=0;
							Picks[P_LITHOVORE]=1;
						}
						else if(p<=m-6)
						{
							p-=PickCosts[P_CYBERNETIC];
							p+=PickCosts[P_LITHOVORE];
							Picks[P_CYBERNETIC]=0;
							Picks[P_LITHOVORE]=1;
						}
					}
					else
					{
						if((Picks[P_15FOOD]==1)&&(p<=m-3))
						{
							m+=PickCosts[P_15FOOD];
							p+=PickCosts[P_LITHOVORE];
							Picks[P_15FOOD]=0;
							Picks[P_LITHOVORE]=1;
						}
						else 
						if((Picks[P_30FOOD]==1)&&(p<=m+4))
						{
							p-=PickCosts[P_30FOOD];
							p+=PickCosts[P_LITHOVORE];
							Picks[P_30FOOD]=0;
							Picks[P_LITHOVORE]=1;
						}
						else 
						if((Picks[P_40FOOD]==1)&&(p<=m+7))
						{
							p-=PickCosts[P_40FOOD];
							p+=PickCosts[P_LITHOVORE];
							Picks[P_40FOOD]=0;
							Picks[P_LITHOVORE]=1;
						}
						else if(p<=m)
						{
							p+=PickCosts[P_LITHOVORE];
							Picks[P_LITHOVORE]=1;
						}
					}
				};break;




	P.OQueue
	P.SQueue
}


};

player P;



void main()
{
	unsigned short run,old,oldl,i,j;
	unsigned char l,race,counter;//,Detailed_Info;

//	char I[11],O[9];
	unsigned short n,pos;
	unsigned char * buffer;
	char line[100];
	long size;
	signed char error;

	srand(time(NULL));
	for(i=0;i<1000;i++)
		j=rand()%2;
	j=0;


	for(i=0;i<MAX_SYSTEMS;i++)
		for(j=0;j<5;j++)
			System[i].Object[j]=&planet[i*5+j];

P.Init();
P.Create();
P.Restart();



	Max_Generations=0;
	Mutations=0;
	Mut_Rate=0;

	run=0;

	error=0;

	Player Save[RUNNINGS];
	Player tempp;

	for(l=0;l<RUNNINGS;l++)
		Save[l].Init();
	tempp.Init();

	while( (kbhit()==0) && (run<RUNNINGS))
	{
		x=0;
		while(generation<Max_Generations)
		{
			player->Init();
			for(i=0;i<MAX_LENGTH;i++)
				player->program[i].order=Save[run]->program[i].order;
			player->Mutate();

			player->Calculate();
			if(player->fitness>Save[run]->fitness)
			{
				for(i=0;i<MAX_LENGTH;i++)
				{
					Save[run]->program[i].order=player->program[i].order;
					Save[run]->program[i].mins=player->program[i].mins;
					Save[run]->program[i].gas=player->program[i].gas;
				}

				//location?
				Save[run]->fitness=player->fitness;
				Save[run]->timer=player->timer;
				Save[run]->harvested_mins=player->harvested_mins;
				Save[run]->harvested_gas=player->harvested_gas;
				Save[run]->mins=player->mins;
				Save[run]->gas=player->gas;
				Save[run]->length=player->length;
				for(i=0;i<building_types;i++)
					for(j=0;j<LOCATIONS;j++)
						Save[run]->force[i][j]=player->force[i][j];
				generation=0;
			}
			generation++;
			//printf("%i.",Save[run]->fitness);
		}
		run++;
		generation=0;

		player->Restart();
		printf("%i:%i ",RUNNINGS-run,Save[run-1]->timer);

	} // end while...

	//Output

	y=RUNNINGS;
	if(run>0)
	{
		afit=0;
		for(x=0;x<RUNNINGS;x++)
			if((Save[x]->fitness>afit)&&(Save[x]->timer<Max_Time))
			{
				afit=Save[x]->fitness;
				y=x;
			}
	}

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P
	printf("Calculating completed.\n\n");
	if(y==RUNNINGS)
	{
		printf("  NO SOLUTION FOUND!\n");
		printf("The program scanned the %s at the beginning but didn't find any errors.\n",I);
		printf("(like too many goals, impossible combinations etc.)\n\n");
		printf(" Possible solutions (you can change the values in %s):\n",I);
		if(Max_Time<2700) 
			printf("- Try to increase Max Time.\n  Currently it is set to %i, while the maximum is 45.\n",Max_Time);
		if(Max_Generations<200)
			printf("- Try to increase Max Generations.\n  Currently it is set to %i, while a good value is about 250.\n",Max_Generations);
		if(Mutations<20)
			printf("- Try to increase Mutations.\n  Currently it is set to %i, while a good value is about 25.\n",Mutations);
		if(Mutations>40)
			printf("- Try to decrease Mutations.\n  Currently it is set to %i, while a good value is about 25.\n",Mutations);
		if(Mut_Rate<25)
			printf("- Try to increase Mutation Rate.\n  Currently it is set to %i, while a good value is about 50.\n",Mut_Rate);
		if(Mut_Rate>75)
			printf("- Try to decrease Mutation Rate.\n  Currently it is set to %i, while a good value is about 50.\n",Mut_Rate);
		printf("- If even a rerun does not bring any result I would be happy if you send me the %s to scc@clawsoftware.de!\n",I);
		printf("- Maybe other users already reported this, so it would be wise to check www.clawsoftware.de for an update\n");
		l=getch();
		return 1;
	}

	printf(" The build order was saved in the file ""%s"".\n\n",O);
	printf(" Brought to you by clawsoftware.de\n");
	printf("\n\n\n\n\n\n\n\n\n\n");	

	out_file<<"StarCraft Evolution Chamber by ClawSoftware.de\n";
	out_file<<"--------------------------------------------------\n\n";
	out_file<<"Fastest build order:\n";
	sprintf(line,"Time used: [%2i:%02i]\n",Save[y]->timer/60,Save[y]->timer%60);
	out_file<<line;

	old=200;oldl=200;
	counter=1;
	for(i=0;i<=Save[y]->length;i++)
	{
		if(Detailed_Info==0)
		{
			while(((Save[y]->program[i].time>=Save[y]->timer-stats[race][Build_Av[Save[y]->program[i].order]].BT)||(Build_Av[Save[y]->program[i].order]>=building_types-1))&&(i<MAX_LENGTH-1))
				i++;
			if((old==Build_Av[Save[y]->program[i].order])&&(oldl==Save[y]->program[i].location)) counter++;
			else if((old<200)&&(oldl<200))
			{
				sprintf(line,"%2i %s (%s)\n",counter,stats[race][old].name,location[Save[y]->program[i].location].name);
				out_file<<line;
				counter=1;
				old=Build_Av[Save[y]->program[i].order];
				oldl=Save[y]->program[i].location;
			}
			else
			{
				old=Build_Av[Save[y]->program[i].order];
				oldl=Save[y]->program[i].location;
			}
		}
		else
			//TODO buildingtypes-1 schreiben... damit wait net in der dings drinsteht... oder bissl aendern... sieht etwas verwirrend aus...
		if((Save[y]->program[i].time<Save[y]->timer-stats[race][Build_Av[Save[y]->program[i].order]].BT)&&(Build_Av[Save[y]->program[i].order]<building_types)&&((i==0)||(Save[y]->program[i].time>0)))
		{
			sprintf(line,"[%3i/%3i] [%5iM|%5iG] [%2i:%02i] -> [%2i:%02i] %s (%s)\n",(Save[y]->program[i].UsedSupply+0),(Save[y]->program[i].Supply+0),Save[y]->program[i].mins,Save[y]->program[i].gas,(Save[y]->program[i].time+0)/60,(Save[y]->program[i].time+0)%60,(Save[y]->program[i].time+stats[race][Build_Av[Save[y]->program[i].order]].BT)/60,(Save[y]->program[i].time+stats[race][Build_Av[Save[y]->program[i].order]].BT)%60,stats[race][Build_Av[Save[y]->program[i].order]].name,location[Save[y]->program[i].location].name);
			out_file<<line;
		}
	}

	for(j=0;j<LOCATIONS;j++)
	for(i=0;i<building_types;i++)
		if(Save[y]->force[i][j]>0)
		{
			sprintf(line,"%2ix %s (%s)\n",Save[y]->force[i][j],stats[race][i].name,location[j].name);
			out_file<<line;
		}
	
	out_file<<"Harvested Minerals: "<<(unsigned short)(Save[y]->harvested_mins+0)<<"\n";
	out_file<<"Harvested Gas: "<<(unsigned short)(Save[y]->harvested_gas+0)<<"\n";		
	out_file<<"Minerals after completing last task: "<<(unsigned short)(Save[y]->mins+0)<<"\n";
	out_file<<"Gas after completing last task: "<<(unsigned short)(Save[y]->gas+0)<<"\n";
	
	if(run>0)
	{
		out_file<<"\n";
		out_file<<"Other possible solutions: \n";
		for(x=0;x<run;x++)
			if((Save[x]->timer<Max_Time)&&(y!=x)&&(Save[x]->timer!=Save[y]->timer))			
			{
				out_file<<"\n";
				out_file<<"\n----------------------------------------------------------\n\n";
				sprintf(line,"Time used: [%2i:%02i]\n",Save[x]->timer/60,Save[x]->timer%60);
				out_file<<line;
				old=200;oldl=200;
				counter=1;
				for(i=0;i<=Save[x]->length;i++)
				{
					if(Detailed_Info==0)
					{
						while(((Save[x]->program[i].time>=Save[x]->timer-stats[race][Build_Av[Save[x]->program[i].order]].BT)||(Build_Av[Save[x]->program[i].order]>=building_types))&&(i<MAX_LENGTH-1))
							i++;
						if((old==Build_Av[Save[x]->program[i].order])&&(oldl==Save[x]->program[i].location)) counter++;
						else if((old<200)&&(oldl<200))
						{
							sprintf(line,"%2i %s (%s)\n",counter,stats[race][old].name,location[Save[x]->program[i].location].name);
							out_file<<line;
							counter=1;
							old=Build_Av[Save[x]->program[i].order];
							oldl=Save[x]->program[i].location;
						}
						else
						{
							old=Build_Av[Save[x]->program[i].order];
							oldl=Save[x]->program[i].location;
						}
					}
					else
					if((Save[x]->program[i].time<Save[x]->timer-stats[race][Build_Av[Save[x]->program[i].order]].BT)&&(Build_Av[Save[x]->program[i].order]<building_types)&&((i==0)||(Save[x]->program[i].time>0)))
					{
						sprintf(line,"[%3i/%3i] [%5iM|%5iG] [%2i:%02i] -> [%2i:%02i] %s (%s)\n",(Save[x]->program[i].UsedSupply+0),(Save[x]->program[i].Supply+0),Save[x]->program[i].mins,Save[x]->program[i].gas,(Save[x]->program[i].time+0)/60,(Save[x]->program[i].time+0)%60,(Save[x]->program[i].time+stats[race][Build_Av[Save[x]->program[i].order]].BT)/60,(Save[x]->program[i].time+stats[race][Build_Av[Save[x]->program[i].order]].BT)%60,stats[race][Build_Av[Save[x]->program[i].order]].name,location[Save[x]->program[i].location].name);
						out_file<<line;
					}
				}
					
				for(j=0;j<LOCATIONS;j++)
				for(i=0;i<building_types;i++)
					if(Save[x]->force[i][j]>0)
					{
						sprintf(line,"%2ix %s (%s)\n",Save[x]->force[i][j],stats[race][i].name,location[j].name);
						out_file<<line;
					}						

				out_file<<"Harvested Minerals: "<<(unsigned short)(Save[x]->harvested_mins+0)<<"\n";
				out_file<<"Harvested Gas: "<<(unsigned short)(Save[x]->harvested_gas+0)<<"\n";	
				out_file<<"Minerals after completing last task: "<<(unsigned short)(Save[x]->mins+0)<<"\n";
				out_file<<"Gas after completing last task: "<<(unsigned short)(Save[x]->gas+0)<<"\n";
			}
	}

	out_file.close();

	player=NULL;
	for(l=0;l<RUNNINGS;l++)
		Save[l]=NULL;
	tempp=NULL;

	x=getch();
	return 0;
}


// In output noch larven?





}