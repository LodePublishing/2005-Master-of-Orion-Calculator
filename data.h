#ifndef DATA_H
#define DATA_H

#define MAX_SYSTEMS 19
#define MAX_PLANETS MAX_SYSTEMS*5
#define MAX_SHIPS 100
#define MAX_X 20
#define MAX_Y 15 // tiny galaxy

#define MAX_ORDERS 250
#define MAX_SCIENCE 50
#define MAX_TECH 30
#define MAX_TRANSPORT 10

#define MAX_BUILDINGS 24


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

	{"ScQ 0"},
	{"ScQ 1"},
	{"ScQ 2"},

	{"ScQ 3"},
	{"ScQ 4"},
	{"ScQ 5"},
	{"ScQ 6"},
	{"ScQ 7"},
	{"ScQ 8"},
	{"ScQ 9"},
	{"ScQ10"},
	{"ScQ11"},
	{"ScQ12"},

	{"ScQ13"},
	{"ScQ14"},
	{"ScQ15"},
	{"ScQ16"},
	{"ScQ17"},
	{"ScQ18"},
	{"ScQ19"},
	{"ScQ20"},
	{"ScQ21"},
	{"ScQ22"},
	{"ScQ23"},
	{"ScQ24"},
	{"ScQ25"},


	{"ScQ26"},
	{"ScQ27"},
	{"ScQ28"},
	{"ScQ29"},

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


const name TName[MAX_TECH]=
{
"REINF",
"AUTOM",
"BATTL",
"SPACE",
"ROBO_",
"NUCLE",
"COLD_",
"AUGME",
"CHEMI",
"DEUTE",
"POLLU",
"ATMOS",
"NANO_",
"SPACE",
"ELECT",
"RESEA",
"NEURA",
"PLANE",
"HYDRO",
"BIOSP",
"CLONI",
"SOIL_",
"MICRO",
"PHYSI",
"FUSIO",
"BATTL",
"NEUTR",
"PLANE",
"MASS_",
"INERT"
};

#define T_REINFORCED_HULL 0
#define T_AUTOMATED_FACTORIES 1
#define T_BATTLE_PODS 2
#define T_SPACE_PORT 3
#define T_ROBO_MINE_PLANT 4
#define T_NUCLEAR_FISSION 5
#define T_COLD_FUSION 6
#define T_AUGMENTED_ENGINES 7
#define T_CHEMISTRY 8
#define T_DEUTERIUM_FUEL 9
#define T_POLLUTION_PROCESSOR 10
#define T_ATMOSPHERE_RENEWER 11
#define T_NANO_DISASSEMBLER 12
#define T_SPACE_ACADEMY 13
#define T_ELECTRONIC_COMPUTER 14
#define T_RESEARCH_LAB 15
#define T_NEURAL_SCANNER 16
#define T_PLANETARY_SUPERCOMPUTER 17
#define T_HYDROPONIC_FARM 18
#define T_BIOSPHERES 19
#define T_CLONING_CENTER 20
#define T_SOIL_ENRICHMENT 21
#define T_MICROBIOTICS 22
#define T_PHYSICS 23
#define T_FUSION_RIFLE 24
#define T_BATTLE_SCANNER 25
#define T_NEUTRON_BLASTER 26
#define T_PLANETARY_GRAVITATION_GENERATION 27
#define T_MASS_DRIVER 28
#define T_INERTIAL_STABILISATOR 29



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
#define B_SPACE_PORT 5
#define B_ROBO_MINE_PLANT 6
#define B_COLONY_SHIP 7
#define B_FREIGHTERS 8
#define B_OUTPOST_SHIP 9
#define B_TRANSPORT 10
#define B_POLLUTION_PROCESSOR 11
#define B_ATMOSPHERE_RENEWER 12
#define B_RESEARCH_LAB 13
#define B_PLANETARY_SUPERCOMPUTER 14
#define B_HYDROPONIC_FARM 15
#define B_BIOSPHERES 16
#define B_CLONING_CENTER 17
#define B_SOIL_ENRICHMENT 18
#define B_GRAVITY_GENERATOR 19
#define B_SPY 20
#define B_GOVERNMENT_CENTER 21
#define B_HOUSING 22
#define B_SHIP 23


const name BName[MAX_BUILDINGS]=
{
"TRADI",
"ColBa",
"STAR_",
"MARIN",
"AUTOM",
"SPACE",
"ROBO_",
"ColSh",
"FREIG",
"OUTPO",
"TRANS",
"POLLU",
"ATMOS",
"RESEA",
"PLANE",
"HYDRO",
"BIOSP",
"CLONI",
"SOIL_",
"GRAVI",
"SPY  ",
"GOVER",
"HOUSI",
"SHIP "
};

#define MAX_PICKS 32


const name PName[MAX_PICKS]=
{
"FEUDA",
"DICTA",
"DEMOC",
"UNIFI",
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
"FANTA",
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
"REPUL"
};


#define P_FEUDALISM 0
#define P_DICTATORSHIP 1
#define P_DEMOCRACY 2
#define P_UNIFICATION 3
#define P_AQUATIC 4
#define P_SUBTERRAN 5
#define P_LOWG 6
#define P_HIGHG 7
#define P_LARGE_HOMEWORLD 8
#define P_RICH_HOMEWORLD 9
#define P_POOR_HOMEWORLD 10
#define P_ARTIFACTS_HOMEWORLD 11
#define P_CYBERNETIC 12
#define P_LITHOVORE 13
#define P_TOLERANT 14
#define P_FANTASTIC_TRADER 15
#define P_05GROWTH 16
#define P_15GROWTH 17
#define P_20GROWTH 18
#define P_15FOOD 19
#define P_30FOOD 20
#define P_40FOOD 21
#define P_20INDUSTRY 22
#define P_40INDUSTRY 23
#define P_50INDUSTRY 24
#define P_20SCIENCE 25
#define P_40SCIENCE 26
#define P_50SCIENCE 27
#define P_05BCS 28
#define P_15BCS 29
#define P_20BCS 30
#define P_REPULSIVE 31


signed char PickCosts[MAX_PICKS]=
{
	-4,0,7,6,5,6,-5,6,1,2,-1,3,4,10,10,4,-4,3,6,-3,4,7,-3,3,6,-3,3,6,-4,5,8,-6
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