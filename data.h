#ifndef DATA_H
#define DATA_H

#define MAX_SYSTEMS 19
#define MAX_PLANETS MAX_SYSTEMS*5
#define MAX_SHIPS 100
#define MAX_X 20
#define MAX_Y 15 // tiny galaxy

#define MAX_ORDERS 250
#define MAX_SCIENCE 50
#define MAX_TECH 179
#define MAX_TRANSPORT 10


#define ORDER_COUNT 190

struct name
{
	char Name[6];
};


const name Orders[ORDER_COUNT]=
{
	{"1F>Wo"},
	{"1F>Sc"},
	{"1W>Fa"},
	{"1W>Sc"},
	{"1S>Fa"},
	{"1S>Wo"},
	{"3F>Wo"},
	{"3F>Sc"},
	{"3W>Fa"},
	{"3W>Sc"},

	{"3S>Fa"},
	{"3S>Wo"},
	{"Snd 1"},
	{"Snd 2"},
	{"Snd 3"},
	{"Snd 4"},
	{"Snd 5"},
	{"Snd 6"},
	{"Snd 7"},
	{"Snd 8"},
	
	{"Snd 9"},
	{"Snd10"},
	{"Snd11"},
	{"Snd12"},
	{"Snd13"},
	{"Snd14"},
	{"Snd15"},
	{"Snd16"},
	{"Snd17"},
	{"Snd18"},

	{"Snd19"},
	{"SysS1"},
	{"SysS2"},
	{"SysS3"},
	{"SysS4"},
	{"SysS5"},
	{"BuyPr"},

	{"Rpl 0"},
	{"Rpl 1"},
	{"Rpl 2"},

	{"Rpl 3"},
	{"Rpl 4"},
	{"Rpl 5"},
	{"Rpl 6"},
	{"Rpl 7"},
	{"Rpl 8"},
	{"Rpl 9"},
	{"Rpl10"},
	{"Rpl11"},
	{"Rpl12"},

	{"Rpl13"},
	{"Rpl14"},
	{"Rpl15"},
	{"Rpl16"},
	{"Rpl17"},
	{"Rpl18"},
	{"Rpl19"},
	{"Rpl20"},
	{"Rpl21"},
	{"Rpl22"},

	{"Rpl23"},
	{"Rpl24"},
	{"Rpl25"},
	{"Rpl26"},
	{"Rpl27"},
	{"Rpl28"},
	{"Rpl29"},
	{"Rpl30"},
	{"Rpl31"},
	{"Rpl32"},
//59
	{"Rpl33"},
	{"Rpl34"},
	{"Rpl35"},
	{"Rpl36"},
	{"Rpl37"},
	{"Rpl38"},
	{"Rpl39"},
	{"Rpl40"},
	{"Rpl41"},
	{"Rpl42"},
//69
	{"Rpl43"},
	{"Rpl44"},
	{"Rpl45"},
	{"Rpl46"},
	{"Rpl47"},
	{"Rpl48"},
	{"Rpl49"},
	{"Rpl50"},
	{"Rpl51"},
	{"Rpl52"},
//79
	{"Rpl53"},
	{"Rpl54"},
	{"Rpl55"},
	{"Rpl56"},
	{"Rpl57"},
	{"Rpl58"},
	{"Rpl59"},
	{"Rpl60"},
	{"Rpl61"},
	{"Que 0"},
//89
	{"Que 1"},
	{"Que 2"},
	{"Que 3"},
	{"Que 4"},
	{"Que 5"},
	{"Que 6"},
	{"Que 7"},
	{"Que 8"},
	{"Que 9"},
	{"Que10"},
//99
	{"Que11"},
	{"Que12"},
	{"Que13"},
	{"Que14"},
	{"Que15"},
	{"Que16"},
	{"Que17"},
	{"Que18"},
	{"Que19"},
	{"Que20"},
//109
	{"Que21"},
	{"Que22"},
	{"Que23"},
	{"Que24"},
	{"Que25"},
	{"Que26"},
	{"Que27"},
	{"Que28"},
	{"Que29"},
	{"Que30"},

	{"Que31"},
	{"Que32"},
	{"Que33"},
	{"Que34"},
	{"Que35"},
	{"Que36"},
	{"Que37"},
	{"Que38"},
	{"Que39"},
	{"Que40"},

	{"Que41"},
	{"Que42"},
	{"Que43"},
	{"Que44"},
	{"Que45"},
	{"Que46"},
	{"Que47"},
	{"Que48"},
	{"Que49"},
	{"Que50"},

	{"Que51"},
	{"Que52"},
	{"Que53"},
	{"Que54"},
	{"Que55"},
	{"Que56"},
	{"Que57"},
	{"Que58"},
	{"Que59"},
	{"Que60"},

	{"Que61"},
	{"Snd 1"},
	{"Snd 2"},
	{"Snd 3"},
	{"Snd 4"},
	{"Snd 5"},
	{"Snd 6"},
	{"Snd 7"},
	{"Snd 8"},
	{"Snd 9"},

	{"Snd10"},
	{"Snd11"},
	{"Snd12"},
	{"Snd13"},
	{"Snd14"},
	{"Snd15"},
	{"Snd16"},
	{"Snd17"},
	{"Snd18"},
	{"Snd19"},

	{"NextP"},
	{"NextP"},
	{"NextP"},
	{"NextP"},
	{"NextP"},
	{"NextP"},
	{"NextP"},
	{"NextP"},
	{"NextP"},
	{"NextP"},
};

const unsigned char mins[5]={1,2,3,5,8};
const unsigned char robominer[5]={5,8,10,15,20};
const unsigned char food[13]={0,0,0,3,2,2,1,2,1,1,0,0,0};

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

const str ScienceArea[MAX_TECH]=
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

	
	{5,0},
	{5,1},{5,1},
	{5,2},{5,2},{5,2},
	{5,3},{5,3},
	{5,4},{5,4},{5,4},
	{5,5},{5,5},
	{5,6},{5,6},
	{5,7},{5,7},
	{5,8},{5,8},
	{5,9},{5,9},{5,9},

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
	50000,
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
#define T_ARTEMIS_SYSTEM_NETWORK 32

#define T_NUCLEAR_FISSION 33
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
#define T_GUIDIANCE_SYSTEM 84
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
#define T_GALACTIC_CYBERNETWORK 101
#define T_PLEASURE_DOME 102
#define T_MOLECULAR_COMPUTER 103
#define T_ACHILLES_TARGETING_SYSTEM 104

#define T_HYDROPONIC_FARM 105
#define T_BIOSPHERES 106
#define T_CLONING_CENTER 107
#define T_SOIL_ENRICHMENT 108
#define T_DEATH_SPORES 109
#define T_TELEPATHIC_TRAINING 110
#define T_MICROBIOTICS 111
#define T_TERRAFORMING 112
#define T_SUBTERRAN_FARMS 113
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
#define T_ANTI_GRAV_HARNESS 152
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
#define T_DISPLACEMENT_DEVICE 173
#define T_SUBSPACE_TELEPORTER 174
#define T_INERTIAL_NULLIFIER 175
#define T_CLASS_X_SHIELD 176
#define T_PLANETARY_BARRIER_SHIELD 177
#define T_PHASING_CLOAK 178

#define T_NONE 179


const name TName[MAX_TECH]=
{
"ANTI_",
"FIGHT",
"REINF",
"AUTOM",
"MISSI",
"HEAVY",
"BATTL",
"TROOP",
"SURVI",
"SPACE",
"ARMOR",
"FIGHT",
"ROBO_",
"BATTL",
"POWER",
"FAST_",
"ADVAN",
"ASSAU",
"TITAN",
"GROUN",
"BATTL",
"RECYC",
"AUTOR",
"ARTIF",
"ROBOT",
"BOMBE",
"DEEP_",
"CORE_",
"STAR_",
"ADVAN",
"HEAVY",
"DOOM_",
"ARTEM",
"NUCLE",
"COLD_",
"FUSIO",
"FUSIO",
"AUGME",
"ION_D",
"IONPU",
"SHIEL",
"ANTI_",
"ANTI_",
"ANTI_",
"TRANS",
"FOOD_",
"HIGH_",
"ENERG",
"MEGAF",
"PROTO",
"HYPER",
"HYPER",
"INTER",
"PLASM",
"NEUTR",
"CHEMI",
"DEUTE",
"TRITA",
"MERCU",
"POLLU",
"PULSO",
"ATMOS",
"IRIDI",
"NANO_",
"MICRO",
"ZORTI",
"ZEON_",
"NEUTR",
"URIDI",
"THORI",
"ADAMA",
"SPACE",
"XENO_",
"ALIEN",
"STOCK",
"ASTRO",
"CONFE",
"IMPER",
"FEDER",
"GALAC",
"GALAC",
"ELECT",
"RESEA",
"OPTRO",
"GUIDI",
"NEURA",
"SCOUT",
"SECUR",
"POSIT",
"PLANE",
"HOLO_",
"EMISS",
"RANGE",
"CYBER",
"CYBER",
"AUTOL",
"STRUC",
"ANDRO",
"ANDRO",
"ANDRO",
"VIRTU",
"GALAC",
"PLEAS",
"MOLEC",
"ACHIL",
"HYDRO",
"BIOSP",
"CLONI",
"SOIL_",
"DEATH",
"TELEP",
"MICRO",
"TERRA",
"SUBTE",
"WEATH",
"PSION",
"INTEL",
"BIO_T",
"UNIVE",
"BIOMO",
"GAIA_",
"EVOLU",
"PHYSI",
"FUSIO",
"FUSIO",
"TACHY",
"TACHY",
"BATTL",
"NEUTR",
"NEUTR",
"TRACT",
"GRAVI",
"PLANE",
"SUBSP",
"JUMP_",
"PHASO",
"PHASO",
"MULTI",
"PLASM",
"PLASM",
"PLASM",
"DISRU",
"DIMEN",
"HYPER",
"SENSO",
"MAULE",
"TIME_",
"STELL",
"STAR_",
"CLASS",
"MASS_",
"ECM_J",
"ANTI_",
"INERT",
"GYRO_",
"CLASS",
"PLANE",
"WARP_",
"STEAL",
"PERSO",
"STEAL",
"PULSA",
"WARP_",
"LIGTH",
"CLASS",
"MULTI",
"GAUSS",
"CLOAK",
"STASI",
"HARD_",
"CLASS",
"PLANE",
"WIDE_",
"DISPL",
"SUBSP",
"INERT",
"CLASS",
"PLANE",
"PHASI"
};


//unsigned char tbcs[3]=
//{
//	1,2,4
//};


unsigned short prod[62]=
{
	999,
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
	80,
	300,
	200,
	500,
	120,
	100,
	200,
	50,//erstmal nur colony ships
	100,
	200,
	400,
	800,
	1600
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
#define B_ATMOSPHERE_RENEWER 25

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

const name BName[MAX_BUILDINGS]=
{
"TRADI",
"COLON",
"STARB",
"MARIN",
"AUTOM",
"MISSI",
"SPACE",
"ARMOR",
"FIGHT",
"ROBOM",
"BATTL",
"GROUN",
"RECYC",
"ARTIF",
"ROBOT",
"DEEPC",
"CORED",
"STARF",
"ARTEM",
"COLON",
"FREIG",
"OUTPO",
"TRANS",
"FOODR",
"POLLU",
"ATMOS",
"SPACE",
"ALIEN",
"STOCK",
"ASTRO",
"RESEA",
"PLANE",
"HOLOS",
"AUTOL",
"ANDRO",
"ANDRO",
"ANDRO",
"GALAC",
"PLEAS",
"HYDRO",
"BIOSP",
"CLONI",
"SOILE",
"TERRA",
"SUBTE",
"WEATH",
"GAIAT",
"DIMEN",
"STELL",
"PLANE",
"WARPD",
"PLANE",
"PLANE",
"GRAVI",
"SPY  ",
"GOVER",
"HOUSI",
"SHIP1",
"SHIP2",
"SHIP3",
"SHIP4",
"SHIP5"
};

#define MAX_PICKS 52


const name PName[MAX_PICKS]=
{
"FEUDA",
"DICTA",
"DEMOC",
"UNIFI",
"WARLO",
"AQUAT",
"SUBTE",
"LOWG ",
"HIGHG",
"LARGE",
"RICH_",
"POOR_",
"ARTIF",
"CYBER",
"LITHO",
"TOLER",
"LUCK ",
"CHARM",
"TELEP",
"OMNIS",
"FANTA",
"TRANS",
"05GRO",
"15GRO",
"20GRO",
"15FOO",
"30FOO",
"40FOO",
"20IND",
"40IND",
"50IND",
"20SCI",
"40SCI",
"50SCI",
"05BCS",
"15BCS",
"20BCS",
"08ATT",
"12ATT",
"15ATT",
"08DEF",
"12DEF",
"15DEF",
"09GRO",
"11GRO",
"12GRO",
"09SPY",
"11SPY",
"12SPY",
"CREAT",
"UNCRE",
"REPUL"
};


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


signed char PickCosts[MAX_PICKS]=
{
	-4,0,7,6,4,5,6,-5,6,1,2,-1,3,4,10,10,3,3,6,3,4,5,-4,3,6,-3,4,7,-3,3,6,-3,3,6,-4,5,8,-2,2,4,-2,3,7,-2,2,4,-3,3,6,8,-4,-6
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

#endif