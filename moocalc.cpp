// namen fuer produkte noch rein

#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream.h>
#include <time.h>
#include <malloc.h>
#include <math.h>


// Science Queue als eigenes Chromosom
//#define INHABITANTS 10
//#define ANDROIDS 11


unsigned short Mutations,Mut_Rate;

struct trans
{
	unsigned char time,used,wohin;
} Transport[MAX_TRANSPORT];


struct Ships
{
	unsigned char Type; //0: none, 1: Transporter, 2: Colony Ship, 3: Outpost, 3: Fighter, 4: Corvette, 5: Cruiser, 6: Battle Ship, 7: Titan, 8: Dead Star, 
	unsigned char Destination,Start,Progress;
};


class Planets
{
protected:
	unsigned char BQueue[10];
public:
	
	unsigned char Type; // 0: does not exist, 1: gas planet, 2: asteroids, 3: gaia, 4: terran, 5: ocean, 6: tundra, 7: swamp, 8: desert, 9: arid, 10: radiated, 11: barren, 12: toxic
	unsigned char Size; //=0 for non-habitable objects, 1: very small, 2: small, 3: medium, 4: large, 5: huge
	unsigned char Settlement; //0=empty, 1=outpost, 2=colony
	unsigned char Minerals; // 0=Ultra Poor, 1=Poor, 2=average, 3=rich, 4=ultra rich
	unsigned char Special; //0=none, 1=gold, 2=diamonds, 3: tech, 4: inhabitants, 5: splinter colony
	unsigned char Gravitation; // 0=Low-G, 1=1 G, 2=High-G


	short Industry,Food,Science,Money;
	unsigned char FoodDemand,IndustryDemand;
	unsigned char Farmers,Workers,Scientists;
	unsigned char maxPop;
	unsigned char Building[60];
	unsigned short progress; // Production that is in the actual project
	unsigned char system;
	signed short overpop;
	unsigned char Population;
	unsigned char checked;
	unsigned char bought;

	unsigned char Planets::CanBuild(unsigned char item);

	unsigned char Planets::BQ(unsigned char num)
	{
		if((num>=0)&&(num<=10)) return BQueue[num];
		else return 0;
	};
	unsigned char Planets::SQ(unsigned char num,unsigned char what)
	{
		if((num>=0)&&(num<=10)&&(what<MAX_BUILDINGS)) { BQueue[num]=what;return 1;}
		else return 0;
	};


	unsigned char Planets::SwitchPeople(unsigned char who)
	{
		switch(who)
		{
			case 0:if(Farmers>0) { Farmers--;Workers++;return 1;};break;//F -> W
			case 1:if(Farmers>0) { Farmers--;Scientists++;return 1;};break;//F -> S
			case 2:if(Workers>0) { Workers--;Farmers++;return 1;};break;//W -> F
			case 3:if(Workers>0) { Workers--;Scientists++;return 1;};break;//W -> S
			case 4:if(Scientists>0) { Scientists--;Farmers++;return 1;};break;//S -> F
			case 5:if(Scientists>0) { Scientists--;Workers++;return 1;};break;//S -> W
				//evtl noch Farmen verbieten, wenn Produktion 0 betraegt.
		}
		return 0;
	}

unsigned char Planets::TransportPeople(unsigned char who)
{
	switch(who)
	{
		case 0:if(Farmers>0) { Farmers--;return 1;}break;
		case 1:if(Workers>0) { Scientists--;return 1;}break;
		case 2:if(Scientists>0) { Scientists--;return 1;}break;
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
} System[MAX_SYSTEMS];



Planets* p;
Planets* h;



class player
{
//Genes:
public:
	unsigned char picks[MAX_PICKS];
	unsigned char OQueue[MAX_ORDERS];
	unsigned char SQueue[MAX_SCIENCE];

	unsigned short time,orders; //wieviel zeit/wieviele Befehle wurden benoetigt?

//temp
	unsigned long bcs;
	unsigned char pl,mi;

	unsigned char tech[MAX_TECH],temp;
	unsigned short OC,SC,PC; //OrderCounter, ScienceQueueCounter, Planetcounter
	unsigned long science,Freighter;
	short AvailibleFood,AvailibleFreighters,Fitness;//,Commando;
	Ships Ship[MAX_SHIPS];

	unsigned char SelectResearch(unsigned char what)  //1-24
	{
		unsigned char i,j,area;
		j=0;area=0;
		while(j<=what-SCount[area][progress[area]])		 //1,2,3
		{
			j+=SCount[area][progress[area]];
			area++;
		}

		//Problem: Tolerante, Lithovoren koennen net alles erforschen... mmmh

		j=what-j;
		for(i=0;i<progress[area];i++)
			j+=SCount[area][i];

		switch(area)
		{
			case 0:break;
			case 1:j+=33;break;
			case 2:j+=55;break;
			case 3:j+=71;break;
			case 4:j+=81;break;
			case 5:j+=105;break;
			case 6:j+=122;break;
			case 7:j+=149;break;
		}
		return j;
	}


		
	unsigned char player::SearchNextPlanet()
	{
		unsigned char b;
		if(PC+1>=MAX_PLANETS)
			b=0;
		else			
			b=PC+1;
		while(true)
		{
			if(planet[b].Settlement==2)
			{
				if(planet[b].checked==1)
					return 255;
				planet[b].checked=1;
				return b;
			}
			b++;
			if(b>=MAX_PLANETS) b=0;
		}
	}

	unsigned char player::Order(unsigned char what)
	{
		unsigned short i,ok;
		unsigned char a,b,c;
		ok=0;
		c=0;
		
		p=&planet[PC];
		if(what<6) ok=p->SwitchPeople(what);
		else if(what<12) { 
							ok|=p->SwitchPeople(what-6);
							ok|=p->SwitchPeople(what-6);
							ok|=p->SwitchPeople(what-6); 
						}//~~~~~~
		else if(what<31)
		{
			if(p->Workers>0)
			{
				if(what-12==p->system)	
				{
					for(a=0;a<MAX_TRANSPORT;a++)
						if(Transport[a].used==0)
						{
							for(b=0;b<5;b++)
							{
								if((System[p->system].Object[b]->Settlement==2)&&(System[p->system].Object[b]->Population<System[p->system].Object[b]->maxPop)&&(p->Population>0)&&(p->Workers>0))
								{
									Transport[a].used=1;
									Transport[a].wohin=(5*what-12)+b;
									p->Workers--;
									p->Population--;
									Transport[a].time=0;
									a=20;
									ok=1;
									b=5;
								}
							}							
						}
				}
				else
				if(AvailibleFreighters>4)
					{		
						for(a=0;a<MAX_TRANSPORT;a++)
							if(Transport[a].used==0)
							{
								for(b=0;b<5;b++)
								{
									if((System[p->system].Object[b]->Settlement==2)&&(System[p->system].Object[b]->Population<System[p->system].Object[b]->maxPop)&&(p->Population>0)&&(p->Workers>0))
									{
										Transport[a].used=1;
										Transport[a].wohin=(5*what-12)+b;
										p->Workers--;
										p->Population--;
										AvailibleFreighters-=5;
										Transport[a].time=
										sqrt(
											(System[p->system].x-System[planet[what-12].system].x)*(System[p->system].x-System[planet[what-12].system].x)+
											(System[p->system].y-System[planet[what-12].system].y)*(System[p->system].y-System[planet[what-12].system].y)
											);
										a=20;
										ok=1;
									}
								}
							}

						// Anders loesen... muessen ja mehr als 10x Leute erschickt werden koennen...
//						vor allem innerhalb eines Systems...
//						vielleicht extra Befehl fuer sub-system transport
					}
			}
		}

		else if(what<36)
		{
			if((p->Population>0)&&(p->Settlement==2)&&(p->Workers>0)&&(System[p->system].Object[what-31]->Settlement==2)&&(System[p->system].Object[what-31]->Population<System[p->system].Object[what-31]->maxPop)&&(System[p->system].Object[what-31]->Population>0)&&(System[p->system].Object[what-31]->Settlement==2))
			{
				p->Workers--;
				p->Population--;
				System[p->system].Object[what-31]->Workers++;
				System[p->system].Object[what-31]->Population++;
				ok=1;
			}
		}
		else if(what==36)
		{
			if(prod[p->BQ(0)]*4<bcs)
				  {
					  ok=1;
					  bcs-=prod[p->BQ(0)]*4;
					  p->progress=prod[p->BQ(0)];
					  // noch Building als 'gekauft' markieren, um Cheaten zu verhindern
				  }
		}

		else if(what<99)
		{
			if(p->CanBuild(what-37)==1)
			{
				for(a=1;a<10;a++) 
					p->SQ(a,p->BQ(a-1)); //kein ok=..., weil is ja schon ueberprueft
				ok=p->SQ(0,what-37);
			}
		}
		
		else if(what<161)
		{
			if(p->CanBuild(what-99)==1)
			{
				for(a=1;a<10;a++)
					if(p->BQ(a)==0)
					{				
						ok=p->SQ(a,what-99);
						a=10;
					}
			}
		}
		else
		if(what<180)
		{
			for(i=0;i<MAX_SHIPS;i++) //evtl noch im System Pointer auf Schiffe
				if((Ship[i].Type>0)&&(Ship[i].Start==p->system)&&(Ship[i].Start==Ship[i].Destination)&&(p->system!=what-161)&&(Ship[i].Progress==0))
				{
					Ship[i].Destination=what-161;
					Ship[i].Progress=
						sqrt(
							(System[Ship[i].Start].x-System[Ship[i].Destination].x)*(System[Ship[i].Start].x-System[Ship[i].Destination].x)+
							(System[Ship[i].Start].y-System[Ship[i].Destination].y)*(System[Ship[i].Start].y-System[Ship[i].Destination].y)
							);
					i=MAX_SHIPS;
					ok=1;
					//fehlt: Checken ob in Reichweite
				}
		}
		else 
		{
			ok=1;
			c=SearchNextPlanet();
		}

		if(ok==0)
			return 2;
			//rausloeschen!
		else
		if(c==255) 
			return 1;
		else
		{
			PC=c;
			return 0;
		}
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
//	if(progress[ScienceArea[what].Field]>=ScienceArea[what].Progress) return 0; //Feld schon erforscht
//	if(ScienceArea[what].Progress>0)
//		if(progress[ScienceArea[what].Field]>=ScienceArea[what].Progress
//		if(Area[][ScienceArea[what].Progress-1]==0) return 0; //Vorgaenger-Feld noch nicht erforscht?
//		wenn der andere code funzt, sollte des unnoetig sein
	switch(what)
	{
		case T_POLLUTION_PROCESSOR:
		case T_ATMOSPHERE_RENEWER:
		case T_NANO_DISASSEMBLER:
		case T_CORE_WASTE_DUMP:if(picks[P_TOLERANT]==1) return 0;break;
		case T_HYDROPONIC_FARM:
		case T_SOIL_ENRICHMENT:
		case T_SUBTERRAN_FARMS:
		case T_FOOD_REPLICATOR:if(picks[P_LITHOVORE]==1) return 0;break;
//		case T_CONFEDERATION:if(picks[P_FEUDALISM]==0) return 0;break;
//		case T_IMPERIUM:if(picks[P_DICTATORSHIP]==0) return 0;break;
//		case T_FEDERATION:if(picks[P_DEMOCRACY]==0) return 0;break;
//		case T_GALACTIC_UNIFICATION:if(picks[P_UNIFICATION]==0) return 0;break;
		case T_HOLO_SIMULATOR:
		case T_VIRTUAL_REALITY_NETWORK:
		case T_PLEASURE_DOME:if(picks[P_UNIFICATION]==1) return 0;break;
	};
	return 1;
}

void player::BetweenTime()
{
	unsigned short i,j,k,points;
	float gravitation,moral;
	unsigned char temp,a,t,s,u,t2,t3;

	//100 Zuege durchlaufen lassen

	for(k=0;((k<MAX_TURNS)&&(OC<MAX_ORDERS));k++)
	{
			for(i=0;i<MAX_PLANETS;i++)
				planet[i].checked=0;

	for(i=0;i<MAX_PLANETS;i++)
		if((planet[i].Type>0)&&(planet[i].Settlement==2))
		{
			p=&planet[i];
			p->bought=0;

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
			+p->Population* (1-picks[P_05BCS]*0.5+picks[P_15BCS]*0.5+picks[P_20BCS]) )*

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
							+(picks[P_15FOOD]*1.5+picks[P_30FOOD]*3+picks[P_40FOOD]*4)
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
						*(1-0.75*p->Building[B_ATMOSPHERE_RENEWER])
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
						+tech[T_INTELLIGENCE_GROWTH]
						+3
						-picks[P_20SCIENCE]
						+picks[P_40SCIENCE]
						+2*picks[P_50SCIENCE]
						)
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
			if(p->Food>=p->FoodDemand)
			{
				p->Food-=p->FoodDemand;
				AvailibleFood+=p->Food;
			}
			else
			{
				p->FoodDemand-=p->Food;
				p->Food=0;
			};
			if(p->Industry>=p->IndustryDemand)
				p->Industry-=p->IndustryDemand;
			else
			{
				p->IndustryDemand-=p->Industry;
				p->Industry=0;
			}

			// else hungern, keine Freighters!!

			if(p->Industry>0)
				{
					if(p->BQ(0)==B_TRADING_GOODS)
					{

						if(picks[P_FANTASTIC_TRADER]==1)
							bcs+=p->Industry;
						else bcs+=p->Industry/2;
					}
					else if(p->BQ(0)==B_HOUSING)
						p->overpop+=p->Industry*(growth[p->Population][p->maxPop-1] / (2.5*p->Population));
					else
					{
						p->progress+=p->Industry;
						
				
					if(p->progress>=prod[p->BQ(0)])
						{
							p->progress-=prod[p->BQ(0)];
//							printf("%s, ",BName[p->BQ(0)].Name);
							
							if((p->BQ(0)>=B_SHIP_1)&&(p->BQ(0)<=B_SHIP_5))
							{
								for(j=0;j<MAX_SHIPS;j++)
									if(Ship[j].Type==0)
									{
										Ship[j].Start=p->system;
										Ship[j].Progress=0;
										Ship[j].Destination=p->system;
										Ship[j].Type=p->BQ(0)-B_SHIP_1+4;
										j=MAX_SHIPS;
									}
							}
							else 
								if(p->BQ(0)==B_COLONY_BASE)
							{
								for(j=0;j<5;j++)

									if((System[p->system].Object[j]->Type>2)&&(System[p->system].Object[j]->Settlement<2))
									{
//										printf("ColonyBase");
										System[p->system].Object[j]->Population=1;
										if(System[p->system].Object[j]->Settlement==1)
											System[p->system].Object[j]->Building[B_MARINE_BARRACKS]=1;
										System[p->system].Object[j]->Settlement=2;
										System[p->system].Object[j]->Farmers=1;
										j=6;
									}
								if(j==5)
									bcs+=100;//verschrotten;

							}


							else
								if(p->BQ(0)==B_FREIGHTERS)
								{
									AvailibleFreighters+=5;
									Freighter+=5;
								}
							else
								p->Building[p->BQ(0)]=1;

							for(a=0;a<9;a++)
								p->SQ(a,p->BQ(a+1));
							p->SQ(9,0);
							if(p->BQ(0)==0) 
							{
								if(p->Population>=p->maxPop)
									p->SQ(0,B_TRADING_GOODS);
								else
									p->SQ(0,B_HOUSING);
							}
						}
					}
			}

				p->overpop+=(growth[p->Population][p->maxPop-1]*(1-picks[P_05GROWTH]*0.5+picks[P_15GROWTH]*0.5+picks[P_20GROWTH]));
				p->overpop-=(p->FoodDemand+p->IndustryDemand)*50;
				while(p->overpop>999)
				{
					p->overpop-=1000;
					p->Population++;
					p->Workers++;
				}
				while(p->overpop<0)
				{
					p->overpop+=1000;
					p->Population--;
					if(p->Scientists>0)
						p->Scientists--;
					else if(p->Workers>0)
						p->Workers--;
					else if(p->Farmers>0)
						p->Farmers--;
				}


				science+=p->Science;
			}

			SQueue[SC]=SQueue[SC]%SLMax;

			t=ScienceList[SQueue[SC]];
			t2=ScienceList[SQueue[SC]+1];
			t3=ScienceList[SQueue[SC]+2];

		if(science>ScienceCosts[ScienceArea[t].Field][ScienceArea[t].Progress])
		{

			science=0;//-=science[ScienceProjekt]; oder wird doch aufgespart?
			tech[t]=1;
			
		s=SCount[ScienceArea[t].Field][ScienceArea[t].Progress];
		u=0;

			switch(s)
			{
				case 1:u=0;break;
				case 2:if(t+1==t2) u=0; else u=1;break;
				case 3:if(
						  (t+1==t2)
						&&(t+2==t3)
						)
						u=0;
					else
						if(t+1==t2)
							u=1;
						else u=2;break;
			}
			
			if(SCount[ScienceArea[t].Field][ScienceArea[t].Progress+1]>SCount[ScienceArea[t].Field][ScienceArea[t].Progress])
			{
				for(i=24;i>=SQueue[SC]-u;i++)
					ScienceList[i+SCount[ScienceArea[t].Field][ScienceArea[t].Progress+1] ]=ScienceList[i+SCount[ScienceArea[t].Field][ScienceArea[t].Progress]];
			}
			else
			if(SCount[ScienceArea[t].Field][ScienceArea[t].Progress+1]<SCount[ScienceArea[t].Field][ScienceArea[t].Progress])
			{
				for(i=SQueue[SC]-u;i<=25;i++)
					ScienceList[i+SCount[ScienceArea[t].Field][ScienceArea[t].Progress+1]]=ScienceList[i+SCount[ScienceArea[t].Field][ScienceArea[t].Progress]];
			}

			t+=SCount[ScienceArea[t].Field][ScienceArea[t].Progress];

			for(i=0;i<SCount[ScienceArea[t].Field][ScienceArea[t].Progress+1];i++)
				ScienceList[i+SQueue[SC]-u]=t+i;
			SLMax+=SCount[ScienceArea[t].Field][ScienceArea[t].Progress+1]-SCount[ScienceArea[t].Field][ScienceArea[t].Progress];
		}
			
			for(i=0;i<MAX_PLANETS;i++)
				if((planet[i].Type>0)&&(planet[i].Settlement==2))
				{
					p=&planet[i];
					if((p->FoodDemand>0)&&(AvailibleFood>0)&&(AvailibleFreighters>0))
					{
						if((AvailibleFood>=p->FoodDemand)&&(AvailibleFreighters>=p->FoodDemand))
						{
							AvailibleFood-=p->FoodDemand;
							AvailibleFreighters-=p->FoodDemand;
							p->FoodDemand=0;
						}
						else
						{
							if(AvailibleFood>AvailibleFreighters)
							{
								p->FoodDemand-=AvailibleFreighters;
								AvailibleFood-=AvailibleFreighters;
								AvailibleFreighters=0;								
							}
							else
							{
								p->FoodDemand-=AvailibleFood;
								AvailibleFreighters-=AvailibleFood;
								AvailibleFood=0;
							}
						}
					}
				}





			//Aktion
			temp=0;
			while((OC<MAX_ORDERS)&&(temp==0))
			{
				temp=Order(OQueue[OC]);
//				if((OQueue[OC]>155)&&(OQueue[OC]<174)&&(temp!=2))
//				{
//					printf("winke");
//				}
				if(temp==2)
				{
					for(i=OC;i<MAX_ORDERS-1;i++) OQueue[i]=OQueue[i+1];
					OQueue[MAX_ORDERS-1]=ORDER_COUNT-1;
					temp=0;
				}
				else
					OC++;
			};









			for(i=0;i<MAX_TRANSPORT;i++)
				if(Transport[i].used==1)
				{
					if(Transport[i].time>0)
						Transport[i].time--;
					else
					{
						Transport[i].used=0;
						Transport[i].time=0;
						AvailibleFreighters+=5;
						if(planet[Transport[i].wohin].Population<planet[Transport[i].wohin].maxPop)
						{
							planet[Transport[i].wohin].Population++;
							planet[Transport[i].wohin].Workers++;
						}
						Transport[i].wohin=0;
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
				for(i=0;i<MAX_SHIPS;i++)
					if((Ship[i].Type>0)&&(Ship[i].Destination!=Ship[i].Start)&&(Ship[i].Progress>0))
					{
						Ship[i].Progress--; //Antrieb? Transdimensional?
						if(Ship[i].Progress==0)
						{
							Ship[i].Start=Ship[i].Destination;
							if(Ship[i].Type==2)
							{
								for(j=0;j<5;j++)
									if((System[Ship[i].Start].Object[j]->Type>2)&&(System[Ship[i].Start].Object[j]->Settlement<2))
									{
										System[Ship[i].Start].Object[j]->Settlement=2;
										System[Ship[i].Start].Object[j]->Population=1;
										System[Ship[i].Start].Object[j]->Farmers=1;
										Ship[i].Type=0;
										Ship[i].Destination=0;
										Ship[i].Start=0;
										Ship[i].Progress=0;
										j=5;
									}
							} else if(Ship[i].Type==3)
								for(j=0;j<5;j++)
									if((System[Ship[i].Start].Object[j]->Type>0)&&(System[Ship[i].Start].Object[j]->Settlement==0))
									{
										System[Ship[i].Start].Object[j]->Settlement=1;
										Ship[i].Type=0;
										Ship[i].Destination=0;
										Ship[i].Start=0;
										Ship[i].Progress=0;
										j=5;
									}

						}
					}

			}

//			time speichern! ALso wieviel befehle gebraucht wurden


//				evtl noch mehr NUL Befehle rein, sonst is ja immer nur nextp...
orders=OC;
time=k;
points=0;
//Fitness=AvailibleFreighters/5;
		for(i=0;i<MAX_PLANETS;i++)
		{
			Fitness+=planet[i].Population*(planet[i].Settlement==2)*10;
//			for(j=0;j<MAX_BUILDINGS;j++)
//				Fitness+=planet[i].Building[j]==1;
//			Fitness+=bcs;
		}
//		for(i=0;i<MAX_ORDERS;i++)
//			if(OQueue[i]<155) points++;
//		Fitness+=MAX_ORDERS-points;
}


void player::Init()
{
	unsigned short i;
	PC=0;//...
	for(i=0;i<50;i++)
		picks[i]=0;
	bcs=50;
	OC=0;SC=0;PC=0;
	science=0;Freighter=0;Fitness=0;
	AvailibleFood=0;AvailibleFreighters=0;
	for(i=0;i<MAX_TECH;i++)
		tech[i]=0;
	for(i=0;i<MAX_SHIPS;i++)
	{
		Ship[i].Destination=0;
		Ship[i].Progress=0;
		Ship[i].Start=0;
		Ship[i].Type=0;
	};
	
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
		unsigned short i,j,t,s,k;
		unsigned short Home_System;
		unsigned char a;

		for(i=0;i<MAX_PLANETS;i++)
		{
			planet[i].bought=0;
			planet[i].Type=0;
			planet[i].Gravitation=0;
			planet[i].Settlement=0;
			planet[i].Special=0;
			planet[i].maxPop=0;
			planet[i].Size=0;
		}
		

		Home_System=5;
		h=System[Home_System].Object[0];

		for(i=0;i<MAX_SYSTEMS;i++)
			for(j=0;j<5;j++)
				System[i].Object[j]=&planet[i*5+j];

		//Alles resetten, auf unerforscht stellen
				//Galaxie erstellen
		// keine Random Galaxie... mmmh oder doch? NEIN
		//tjo, da muss eine hin... -_- doch


		System[0].x=1;System[0].y=12;sprintf(System[0].Name,"Draconis");System[0].Object[0]->Gravitation=1;System[0].Object[0]->Minerals=2;System[0].Object[0]->Type=4;System[0].Object[0]->Size=3;System[0].Object[0]->system=0;
															   System[0].Object[1]->Gravitation=1;System[0].Object[1]->Minerals=1;System[0].Object[1]->Type=6;System[0].Object[1]->Size=3;System[0].Object[1]->system=0;

		System[1].x=1;System[1].y=5;sprintf(System[1].Name,"Leng"); System[1].Object[0]->Gravitation=1;System[1].Object[0]->Minerals=3;System[1].Object[0]->Type=8;System[1].Object[0]->Size=2;System[1].Object[0]->system=1;
														   System[1].Object[1]->Gravitation=1;System[1].Object[1]->Minerals=2;System[1].Object[1]->Type=11;System[1].Object[1]->Size=4;System[1].Object[1]->system=1;
														   System[1].Object[2]->Gravitation=1;System[1].Object[2]->Minerals=2;System[1].Object[2]->Type=4;System[1].Object[2]->Size=4;System[1].Object[2]->system=1;
														   System[1].Object[3]->Gravitation=1;System[1].Object[3]->Minerals=2;System[1].Object[3]->Type=1;System[1].Object[3]->Size=0;System[1].Object[3]->system=1;

		System[2].x=2;System[2].y=3;sprintf(System[2].Name,"Bier"); System[2].Object[0]->Gravitation=1;System[2].Object[0]->Minerals=3;System[2].Object[0]->Type=10;System[2].Object[0]->Size=3;System[2].Object[0]->system=2;
														   System[2].Object[1]->Gravitation=0;System[2].Object[1]->Minerals=0;System[2].Object[1]->Type=9;System[2].Object[1]->Size=3;System[2].Object[1]->system=2;
														   System[2].Object[2]->Gravitation=1;System[2].Object[2]->Minerals=1;System[2].Object[2]->Type=11;System[2].Object[2]->Size=4;System[2].Object[2]->system=2;
														   System[2].Object[3]->Gravitation=1;System[2].Object[3]->Minerals=2;System[2].Object[3]->Type=1;System[2].Object[3]->Size=0;System[2].Object[3]->system=2;

		System[3].x=1;System[3].y=12;sprintf(System[3].Name,"Kif");System[3].Object[0]->Gravitation=0;System[3].Object[0]->Minerals=1;System[3].Object[0]->Type=6;System[3].Object[0]->Size=2;System[3].Object[0]->system=3;
														  System[3].Object[1]->Gravitation=1;System[3].Object[1]->Minerals=0;System[3].Object[1]->Type=7;System[3].Object[1]->Size=5;System[3].Object[1]->system=3;

		System[4].x=5;System[4].y=3;sprintf(System[4].Name,"Sonans");System[4].Object[3]->Gravitation=1;System[4].Object[3]->Minerals=2;System[4].Object[3]->Type=1;System[4].Object[3]->Size=0;System[4].Object[3]->system=4;

		System[5].x=6;System[5].y=1;sprintf(System[5].Name,"Kholdan");System[5].Object[0]->Gravitation=1;System[5].Object[0]->Minerals=2;System[5].Object[0]->Type=5;System[5].Object[0]->Size=4;System[5].Object[0]->system=5;
														   System[5].Object[1]->Gravitation=0;System[5].Object[1]->Minerals=1;System[5].Object[1]->Type=6;System[5].Object[1]->Size=2;System[5].Object[1]->system=5;
														   System[5].Object[2]->Gravitation=1;System[5].Object[2]->Minerals=2;System[5].Object[2]->Type=1;System[5].Object[2]->Size=0;System[5].Object[2]->system=5;
														   System[5].Object[3]->Gravitation=1;System[5].Object[3]->Minerals=2;System[5].Object[3]->Type=1;System[5].Object[3]->Size=0;System[5].Object[3]->system=5;
		
		System[6].x=5;System[6].y=10;sprintf(System[6].Name,"Katab");System[6].Object[0]->Gravitation=1;System[6].Object[0]->Minerals=3;System[6].Object[0]->Type=8;System[6].Object[0]->Size=2;System[6].Object[0]->system=6;
															   System[6].Object[1]->Gravitation=1;System[6].Object[1]->Minerals=3;System[6].Object[1]->Type=10;System[6].Object[1]->Size=4;System[6].Object[1]->system=6;

	System[7].x=7;System[7].y=8;sprintf(System[7].Name,"Zothique");System[7].Object[0]->Gravitation=1;System[7].Object[0]->Minerals=1;System[7].Object[0]->Type=10;System[7].Object[0]->Size=4;System[7].Object[0]->system=7;
														   System[7].Object[1]->Gravitation=1;System[7].Object[1]->Minerals=1;System[7].Object[1]->Type=8;System[7].Object[1]->Size=5;System[7].Object[1]->system=7;
														   System[7].Object[2]->Gravitation=1;System[7].Object[2]->Minerals=2;System[7].Object[2]->Type=6;System[7].Object[2]->Size=2;System[7].Object[2]->system=7;
														   System[7].Object[3]->Gravitation=1;System[7].Object[3]->Minerals=2;System[7].Object[3]->Type=1;System[7].Object[3]->Size=0;System[7].Object[3]->system=7;

	System[8].x=10;System[8].y=9;sprintf(System[8].Name,"Ras");System[8].Object[0]->Gravitation=2;System[8].Object[0]->Minerals=4;System[8].Object[0]->Type=10;System[8].Object[0]->Size=3;System[8].Object[0]->system=8;

	System[9].x=10;System[9].y=7;sprintf(System[9].Name,"Kakari");System[9].Object[0]->Gravitation=1;System[9].Object[0]->Minerals=3;System[9].Object[0]->Type=10;System[9].Object[0]->Size=2;System[9].Object[0]->system=9;
													   System[9].Object[1]->Gravitation=0;System[9].Object[1]->Minerals=1;System[9].Object[1]->Type=11;System[9].Object[1]->Size=2;System[9].Object[1]->system=9;

	System[10].x=8;System[10].y=6;sprintf(System[10].Name,"Sssla");System[10].Object[0]->Gravitation=1;System[10].Object[0]->Minerals=2;System[10].Object[0]->Type=4;System[10].Object[0]->Size=2;System[10].Object[0]->system=10;
													        System[10].Object[1]->Gravitation=1;System[10].Object[1]->Minerals=2;System[10].Object[1]->Type=10;System[10].Object[1]->Size=2;System[10].Object[1]->system=10;

	System[11].x=8;System[11].y=2;sprintf(System[11].Name,"Schwan");System[11].Object[0]->Gravitation=1;System[11].Object[0]->Minerals=2;System[11].Object[0]->Type=6;System[11].Object[0]->Size=4;System[11].Object[0]->system=11;
														System[11].Object[1]->Gravitation=1;System[11].Object[1]->Minerals=2;System[11].Object[1]->Type=5;System[11].Object[1]->Size=3;System[11].Object[1]->system=11;
														System[11].Object[2]->Gravitation=2;System[11].Object[2]->Minerals=2;System[11].Object[2]->Type=6;System[11].Object[2]->Size=5;System[11].Object[2]->system=11;
														System[11].Object[3]->Gravitation=1;System[11].Object[3]->Minerals=2;System[11].Object[3]->Type=1;System[11].Object[3]->Size=0;System[11].Object[3]->system=11;

	System[12].x=9;System[12].y=4;sprintf(System[12].Name,"Lyae");System[12].Object[0]->Gravitation=2;System[12].Object[0]->Minerals=4;System[12].Object[0]->Type=8;System[12].Object[0]->Size=2;System[12].Object[0]->system=12;
													        System[12].Object[1]->Gravitation=1;System[12].Object[1]->Minerals=3;System[12].Object[1]->Type=4;System[12].Object[1]->Size=2;System[12].Object[1]->system=12;

	System[13].x=12;System[13].y=4;sprintf(System[13].Name,"Suji");System[13].Object[0]->Gravitation=1;System[13].Object[0]->Minerals=1;System[13].Object[0]->Type=8;System[13].Object[0]->Size=4;System[13].Object[0]->system=13;
													        System[13].Object[1]->Gravitation=1;System[13].Object[1]->Minerals=1;System[13].Object[1]->Type=4;System[13].Object[1]->Size=3;System[13].Object[1]->system=13;
													        System[13].Object[2]->Gravitation=1;System[13].Object[2]->Minerals=2;System[13].Object[2]->Type=1;System[13].Object[2]->Size=2;System[13].Object[2]->system=13;

	System[14].x=13;System[14].y=8;sprintf(System[14].Name,"Orion");System[14].Object[0]->Gravitation=1;System[14].Object[0]->Minerals=4;System[14].Object[0]->Type=3;System[14].Object[0]->Size=5;System[14].Object[0]->system=14;


	System[15].x=14;System[15].y=11;sprintf(System[15].Name,"Thiba");System[15].Object[0]->Gravitation=1;System[15].Object[0]->Minerals=2;System[15].Object[0]->Type=8;System[15].Object[0]->Size=2;System[15].Object[0]->system=15;
														System[15].Object[1]->Gravitation=1;System[15].Object[1]->Minerals=2;System[15].Object[1]->Type=8;System[15].Object[1]->Size=2;System[15].Object[1]->system=15;

	System[16].x=14;System[16].y=9;sprintf(System[16].Name,"Nazin");System[16].Object[0]->Gravitation=1;System[16].Object[0]->Minerals=2;System[16].Object[0]->Type=4;System[16].Object[0]->Size=3;System[16].Object[0]->system=16;
													        System[16].Object[1]->Gravitation=1;System[16].Object[1]->Minerals=1;System[16].Object[1]->Type=1;System[16].Object[1]->Size=0;System[16].Object[1]->system=16;
													        System[16].Object[2]->Gravitation=2;System[16].Object[2]->Minerals=4;System[16].Object[2]->Type=7;System[16].Object[2]->Size=4;System[16].Object[2]->system=16;

	System[17].x=15;System[17].y=6;sprintf(System[17].Name,"Yian");System[17].Object[0]->Gravitation=1;System[17].Object[0]->Minerals=2;System[17].Object[0]->Type=11;System[17].Object[0]->Size=3;System[17].Object[0]->system=17;
														System[17].Object[1]->Gravitation=0;System[17].Object[1]->Minerals=2;System[17].Object[1]->Type=7;System[17].Object[1]->Size=1;System[17].Object[1]->system=17;
														System[17].Object[2]->Gravitation=1;System[17].Object[2]->Minerals=2;System[17].Object[2]->Type=1;System[17].Object[2]->Size=0;System[17].Object[2]->system=17;
														System[17].Object[3]->Gravitation=1;System[17].Object[3]->Minerals=2;System[17].Object[3]->Type=1;System[17].Object[3]->Size=0;System[17].Object[3]->system=17;

	System[18].x=12;System[18].y=6;sprintf(System[18].Name,"Xanthus");System[18].Object[0]->Gravitation=1;System[18].Object[0]->Minerals=2;System[18].Object[0]->Type=8;System[18].Object[0]->Size=2;System[18].Object[0]->system=18;
															System[18].Object[1]->Gravitation=1;System[18].Object[1]->Minerals=1;System[18].Object[1]->Type=5;System[18].Object[1]->Size=3;System[18].Object[1]->system=18;



//Special noch rein


		for(i=0;i<MAX_SYSTEMS;i++)
		{
//			System[i].x=rand()%MAX_X;
//			System[i].y=rand()%MAX_Y;
			for(j=0;j<5;j++)
			{
				p=System[i].Object[j];
				if(h==p)
					p->Type=PL_TERRAN;
//				else
//				p->Type=rand()%13; // noch anpassen, gaia unwahrscheinlicher etc.
				
				
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
				
					if(h==p)
					{
						if(picks[P_LARGE_HOMEWORLD]==1)
							p->Size=4;
						else p->Size=3;
					}
//					else
//					{
//						p->Size=rand()%5+1;
//						if(rand()%20==0)
//						{
//							p->Special=rand()%4+1; //Splinter mal weglassen
//						} else p->Special=0;	
//					}
					p->Special=0;
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

				for(a=0;a<10;a++)
					p->SQ(a,0);
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

//				p->Gravitation=rand()%3;
//				p->Minerals=rand()%5;
				p->bought=0;
				p->checked=0;
				p->Settlement=0;
				p->progress=0;
				p->system=i;
				p->overpop=0;
				p->Population=0;
				//planet[i].Gravitation=size, minerals
				//huge 50%, large 25%, normal 10%, small 5%
				//tiny 50%, small 25%, normal 10%, large 5%
				//urich -20%, 
			}
		}
		//Heimatwelt erstellen*/
		h->Building[B_GOVERNMENT_CENTER]=1;
		h->Building[B_MARINE_BARRACKS]=1;
		h->Building[B_STAR_BASE]=1;
		h->Settlement=2;
		h->bought=0;
		h->Population=8;
		h->Farmers=8;
		h->Workers=0;
		h->Scientists=0;
		bcs=50;
//		if(Game_Avg_Tech)
/*			{
				tech[T_NUCLEAR_FISSION]=1;
				tech[T_COLD_FUSION]=1;

				progress[ScienceArea[T_NUCLEAR_FISSION].Field]=ScienceArea[T_NUCLEAR_FISSION].Progress;

				Area[ScienceArea[T_COLD_FUSION].Field][ScienceArea[T_COLD_FUSION].Progress]=1;
				tech[T_CHEMISTRY]=1;
				Area[ScienceArea[T_CHEMISTRY].Field][ScienceArea[T_CHEMISTRY].Progress]=1;
				tech[T_ELECTRONIC_COMPUTER]=1;
				Area[ScienceArea[T_ELECTRONIC_COMPUTER].Field][ScienceArea[T_ELECTRONIC_COMPUTER].Progress]=1;
				tech[T_PHYSICS]=1;
				Area[ScienceArea[T_PHYSICS].Field][ScienceArea[T_PHYSICS].Progress]=1;
				//Schiffe!
			}*/
			// kein Advanced Tech... bringt nix
//				if(picks[P_OMNISCIENT])
//					for(j=0;j<MAX_SYSTEMS];j++)
//						System[j].Scouted[?]=1;

		if(picks[P_LARGE_HOMEWORLD])
			h->Size=4;
		else h->Size=3;
	
		if(picks[P_RICH_HOMEWORLD])
			h->Minerals=3;
		else
		if(picks[P_POOR_HOMEWORLD])
			h->Minerals=1;
		else
			h->Minerals=2;

		if(picks[P_ARTIFACTS_HOMEWORLD])
			h->Special=3;
		else h->Special=0;
		
		if(picks[P_HIGHG])
			h->Gravitation=2;
		else
		if(picks[P_LOWG])
			h->Gravitation=0;
		else h->Gravitation=1;

		if(picks[P_AQUATIC])
			h->Type=5;
		else
			h->Type=4;
		Ship[0].Destination=h->system;
		Ship[0].Progress=0;
		Ship[0].Start=h->system;
		Ship[0].Type=3;

};


void player::TryPick(unsigned short t)
{
	switch(t)
		{

			case P_FEUDALISM:
				if((picks[P_FEUDALISM]==0)&&(mi<=6))
				{
					mi+=4;
					picks[P_FEUDALISM]=1;

					if(picks[P_DICTATORSHIP]==1)
						picks[P_DICTATORSHIP]=0;
					else
					if(picks[P_DEMOCRACY]==1)
					{
						picks[P_DEMOCRACY]=0;
						pl-=7;
					}
					else
					if(picks[P_UNIFICATION]==1)
					{
						picks[P_UNIFICATION]=0;
						pl-=6;
					}
				};break;
			case P_DICTATORSHIP:
				if(picks[P_DICTATORSHIP]==0)
				{
					picks[P_DICTATORSHIP]=1;
					if(picks[P_FEUDALISM]==1)
					{
						mi-=4;
						picks[P_FEUDALISM]=0;
					}
					else 
					if(picks[P_DEMOCRACY]==1)
					{
						p-=7;
						picks[P_DEMOCRACY]=0;
					}					
					if(picks[P_UNIFICATION]==1)
					{
						pl-=6;
						picks[P_UNIFICATION]=0;
					}
				};break;
			case P_DEMOCRACY:
				if((picks[P_DEMOCRACY]==0)&&(pl+(-6*picks[P_UNIFICATION])<=3+mi+(-4*picks[P_FEUDALISM])))
				{
					pl+=7;
					picks[P_DEMOCRACY]=1;
					if(picks[P_FEUDALISM]==1)
					{
						mi-=4;
						picks[P_FEUDALISM]=0;
					}
					else 
					if(picks[P_DICTATORSHIP]==1)
						picks[P_DICTATORSHIP]=0;
					if(picks[P_UNIFICATION]==1)
					{
						pl-=6;
						picks[P_UNIFICATION]=0;
					}
				};break;
			case P_UNIFICATION:
				if((picks[P_UNIFICATION]==0)&&(pl+(-7*picks[P_DEMOCRACY])<=4+mi+(-4*picks[P_FEUDALISM])))
				{
					pl+=6;
					picks[P_UNIFICATION]=1;
					if(picks[P_FEUDALISM]==1)
					{
						mi-=4;
						picks[P_FEUDALISM]=0;
					}
					else 
					if(picks[P_DICTATORSHIP]==1)
						picks[P_DICTATORSHIP]=0;
					if(picks[P_DEMOCRACY]==1)
					{
						pl-=7;
						picks[P_DEMOCRACY]=0;
					}
				};break;						  

			case P_WARLORD:
			case P_AQUATIC:
			case P_SUBTERRAN:
			case P_LARGE_HOMEWORLD:
			case P_ARTIFACTS_HOMEWORLD:
			case P_TOLERANT:
			case P_LUCK:
			case P_TELEPATH:
			case P_OMNISCIENT:
			case P_FANTASTIC_TRADER:
			case P_TRANS_DIMENSIONAL:
				if(picks[t]==1)
				{
					pl-=PickCosts[t];
					picks[t]=0;
				}
				else
				if(pl<=10-PickCosts[t]+mi)
				{
					pl+=PickCosts[t];
					picks[t]=1;
				};break;

			case P_LOWG:
				if(picks[P_LOWG]==1)
				{
					mi+=PickCosts[P_LOWG];
					picks[P_LOWG]=0;
				}
				else
				if((picks[P_HIGHG]==1)&&(mi<=5))
				{
					pl-=PickCosts[P_HIGHG];
					mi-=PickCosts[P_LOWG];
					picks[P_HIGHG]=0;
					picks[P_LOWG]=1;
				}
				else
				if(mi<=5)
				{
					mi-=PickCosts[P_LOWG];
					picks[P_LOWG]=1;
				};break;
			case P_HIGHG:
				if(picks[P_HIGHG]==1)
				{
					pl-=PickCosts[P_HIGHG];
					picks[P_HIGHG]=0;
				}
				else
				if((picks[P_LOWG]==1)&&(pl+1<=mi))
				{
					pl+=PickCosts[P_HIGHG];
					mi+=PickCosts[P_LOWG];
					picks[P_HIGHG]=1;
					picks[P_LOWG]=0;
				}
				else
				if(pl<=4+mi)
				{
					pl+=PickCosts[P_HIGHG];
					picks[P_HIGHG]=1;
				};break;

			case P_RICH_HOMEWORLD:
				if(picks[P_RICH_HOMEWORLD]==1)
				{
					pl-=PickCosts[P_RICH_HOMEWORLD];
					picks[P_RICH_HOMEWORLD]=0;
				}
				else
				if((picks[P_POOR_HOMEWORLD]==1)&&(pl<=7+mi))
				{
					pl+=PickCosts[P_RICH_HOMEWORLD];
					mi+=PickCosts[P_POOR_HOMEWORLD];
					picks[P_RICH_HOMEWORLD]=1;
					picks[P_POOR_HOMEWORLD]=0;
				}
				else
				if(pl<=8+mi)
				{
					pl+=PickCosts[P_RICH_HOMEWORLD];
					picks[P_RICH_HOMEWORLD]=1;
				};break;
			case P_POOR_HOMEWORLD:
				if(picks[P_POOR_HOMEWORLD]==1)
				{
					mi+=PickCosts[P_POOR_HOMEWORLD];
					picks[P_POOR_HOMEWORLD]=0;
				}
				else
				if((picks[P_RICH_HOMEWORLD]==1)&&(mi<=9))
				{
					pl-=PickCosts[P_RICH_HOMEWORLD];
					mi-=PickCosts[P_POOR_HOMEWORLD];
					picks[P_RICH_HOMEWORLD]=0;
					picks[P_POOR_HOMEWORLD]=0;
				}
				else
				if(mi<=9)
				{
					mi-=PickCosts[P_POOR_HOMEWORLD];
					picks[P_POOR_HOMEWORLD]=1;
				};break;

			case P_CYBERNETIC:
				if(picks[P_CYBERNETIC]==1)
				{
					pl-=PickCosts[P_CYBERNETIC];
					picks[P_CYBERNETIC]=0;
				}
				else
				if(picks[P_LITHOVORE]==1)
				{
					pl+=6;
					picks[P_CYBERNETIC]=1;
					picks[P_LITHOVORE]=0;
				}
				else
				if(pl<=6+mi)
				{
					pl+=PickCosts[P_CYBERNETIC];
					picks[P_CYBERNETIC]=1;
				};break;
			case P_LITHOVORE:
				if(picks[P_LITHOVORE]==1)
				{
					pl+=PickCosts[P_LITHOVORE];
					picks[P_LITHOVORE]=0;
				}
				else
				{
					if(picks[P_CYBERNETIC]==1)
					{
						if((picks[P_15FOOD]==1)&&(pl<=mi-9))
						{
							mi+=PickCosts[P_15FOOD];
							pl-=PickCosts[P_CYBERNETIC];
							pl+=PickCosts[P_LITHOVORE];
							picks[P_15FOOD]=0;
							picks[P_CYBERNETIC]=0;
							picks[P_LITHOVORE]=1;
						}
						else 
						if((picks[P_30FOOD]==1)&&(pl<=mi-2))
						{
							pl-=PickCosts[P_30FOOD];
							pl-=PickCosts[P_CYBERNETIC];
							pl+=PickCosts[P_LITHOVORE];
							picks[P_30FOOD]=0;
							picks[P_CYBERNETIC]=0;
							picks[P_LITHOVORE]=1;
						}
						else 
						if((picks[P_40FOOD]==1)&&(pl<=mi+1))
						{
							pl-=PickCosts[P_40FOOD];
							pl-=PickCosts[P_CYBERNETIC];
							pl+=PickCosts[P_LITHOVORE];
							picks[P_40FOOD]=0;
							picks[P_CYBERNETIC]=0;
							picks[P_LITHOVORE]=1;
						}
						else if(pl<=mi-6)
						{
							pl-=PickCosts[P_CYBERNETIC];
							pl+=PickCosts[P_LITHOVORE];
							picks[P_CYBERNETIC]=0;
							picks[P_LITHOVORE]=1;
						}
					}
					else
					{
						if((picks[P_15FOOD]==1)&&(pl<=mi-3))
						{
							mi+=PickCosts[P_15FOOD];
							pl+=PickCosts[P_LITHOVORE];
							picks[P_15FOOD]=0;
							picks[P_LITHOVORE]=1;
						}
						else 
						if((picks[P_30FOOD]==1)&&(pl<=mi+4))
						{
							pl-=PickCosts[P_30FOOD];
							pl+=PickCosts[P_LITHOVORE];
							picks[P_30FOOD]=0;
							picks[P_LITHOVORE]=1;
						}
						else 
						if((picks[P_40FOOD]==1)&&(pl<=mi+7))
						{
							pl-=PickCosts[P_40FOOD];
							pl+=PickCosts[P_LITHOVORE];
							picks[P_40FOOD]=0;
							picks[P_LITHOVORE]=1;
						}
						else if(pl<=mi)
						{
							pl+=PickCosts[P_LITHOVORE];
							picks[P_LITHOVORE]=1;
						}
					}
				};break;

			case P_CREATIVE:
				if((picks[P_UNCREATIVE]==1)&&(pl<=mi-2))
				{
					mi+=PickCosts[P_UNCREATIVE];
					pl+=PickCosts[P_CREATIVE];
					picks[P_UNCREATIVE]=0;
					picks[P_CREATIVE]=1;
				}
				else if(pl<=mi+2)
				{
					pl+=PickCosts[P_CREATIVE];
					picks[P_CREATIVE]=1;
				};break;

			case P_UNCREATIVE:
				if((picks[P_CREATIVE]==1)&&(mi<=6))
				{
					mi-=PickCosts[P_UNCREATIVE];
					pl-=PickCosts[P_CREATIVE];
					picks[P_CREATIVE]=0;
					picks[P_UNCREATIVE]=1;
				}
				else if(mi<=6)
				{
					mi-=PickCosts[P_UNCREATIVE];
					picks[P_UNCREATIVE]=1;
				};break;

			case P_CHARM:
				if((picks[P_REPULSIVE]==1)&&(pl<=mi+1))
				{
					mi+=PickCosts[P_REPULSIVE];
					pl+=PickCosts[P_CHARM];
					picks[P_REPULSIVE]=0;
					picks[P_CHARM]=1;
				}
				else if(pl<=mi+7)
				{
					pl+=PickCosts[P_CHARM];
					picks[P_CHARM]=1;
				};break;

			case P_REPULSIVE:
				if((picks[P_CHARM]==1)&&(mi<=4))
				{
					mi-=PickCosts[P_REPULSIVE];
					pl-=PickCosts[P_CHARM];
					picks[P_CHARM]=0;
					picks[P_REPULSIVE]=1;
				}
				else if(mi<=4)
				{
					mi-=PickCosts[P_REPULSIVE];
					picks[P_REPULSIVE]=1;
				};break;

			case P_05GROWTH:
				if(picks[P_05GROWTH]==1)
				{
					mi+=PickCosts[P_05GROWTH];
					picks[P_05GROWTH]=0;
				}
				else
				if(mi<=7)
				{
					mi-=PickCosts[P_05GROWTH];
					picks[P_05GROWTH]=1;
					if(picks[P_15GROWTH]==1)
					{
						pl-=PickCosts[P_15GROWTH];
						picks[P_15GROWTH]=0;
					}
					else 
					if(picks[P_20GROWTH]==1)
					{
						pl-=PickCosts[P_20GROWTH];
						picks[P_20GROWTH]=0;
					}
				};break;
			case P_15GROWTH:
				if(picks[P_15GROWTH]==1)
				{
					pl-=PickCosts[P_15GROWTH];
					picks[P_15GROWTH]=0;
				}
				else
				if((picks[P_05GROWTH]==1)&&(pl<=mi+4))
				{
					mi+=PickCosts[P_05GROWTH];
					pl+=PickCosts[P_15GROWTH];
					picks[P_15GROWTH]=1;
					picks[P_05GROWTH]=0;
				}
				else
				if(picks[P_20GROWTH]==1)
				{
					pl+=PickCosts[P_15GROWTH];
					pl-=PickCosts[P_20GROWTH];
					picks[P_15GROWTH]=1;
					picks[P_20GROWTH]=0;
				}
				else 
				if(pl<=mi+7)
				{
					pl+=PickCosts[P_15GROWTH];
					picks[P_15GROWTH]=1;
				};break;
			case P_20GROWTH:
				if(picks[P_20GROWTH]==1)
				{
					pl-=PickCosts[P_20GROWTH];
					picks[P_20GROWTH]=0;
				}
				else
				if((picks[P_05GROWTH]==1)&&(pl<=mi+1))
				{
					mi+=PickCosts[P_05GROWTH];
					pl+=PickCosts[P_20GROWTH];
					picks[P_20GROWTH]=1;
					picks[P_05GROWTH]=0;
				}
				else
				if((picks[P_15GROWTH]==1)&&(pl<=mi+7))
				{
					pl+=PickCosts[P_20GROWTH];
					pl-=PickCosts[P_15GROWTH];
					picks[P_20GROWTH]=1;
					picks[P_15GROWTH]=0;
				}
				else 
				if(pl<=mi+4)
				{
					pl+=PickCosts[P_20GROWTH];
					picks[P_20GROWTH]=1;
				};break;

			case P_20INDUSTRY:
				if(picks[P_20INDUSTRY]==1)
				{
					mi+=PickCosts[P_20INDUSTRY];
					picks[P_20INDUSTRY]=0;
				}
				else
				if(mi<=7)
				{
					mi-=PickCosts[P_20INDUSTRY];
					picks[P_20INDUSTRY]=1;
					if(picks[P_40INDUSTRY]==1)
					{
						pl-=PickCosts[P_40INDUSTRY];
						picks[P_40INDUSTRY]=0;
					}
					else 
					if(picks[P_50INDUSTRY]==1)
					{
						pl-=PickCosts[P_50INDUSTRY];
						picks[P_50INDUSTRY]=0;
					}
				};break;
			case P_40INDUSTRY:
				if(picks[P_40INDUSTRY]==1)
				{
					pl-=PickCosts[P_40INDUSTRY];
					picks[P_40INDUSTRY]=0;
				}
				else
				if((picks[P_20INDUSTRY]==1)&&(pl<=mi+4))
				{
					mi+=PickCosts[P_20INDUSTRY];
					pl+=PickCosts[P_40INDUSTRY];
					picks[P_40INDUSTRY]=1;
					picks[P_20INDUSTRY]=0;
				}
				else
				if(picks[P_50INDUSTRY]==1)
				{
					pl+=PickCosts[P_40INDUSTRY];
					pl-=PickCosts[P_50INDUSTRY];
					picks[P_40INDUSTRY]=1;
					picks[P_50INDUSTRY]=0;
				}
				else 
				if(pl<=mi+7)
				{
					pl+=PickCosts[P_40INDUSTRY];
					picks[P_40INDUSTRY]=1;
				};break;
			case P_50INDUSTRY:
				if(picks[P_50INDUSTRY]==1)
				{
					pl-=PickCosts[P_50INDUSTRY];
					picks[P_50INDUSTRY]=0;
				}
				else
				if((picks[P_20INDUSTRY]==1)&&(pl<=mi+1))
				{
					mi+=PickCosts[P_20INDUSTRY];
					pl+=PickCosts[P_50INDUSTRY];
					picks[P_50INDUSTRY]=1;
					picks[P_20INDUSTRY]=0;
				}
				else
				if((picks[P_40INDUSTRY]==1)&&(pl<=mi+7))
				{
					pl+=PickCosts[P_50INDUSTRY];
					pl-=PickCosts[P_40INDUSTRY];
					picks[P_50INDUSTRY]=1;
					picks[P_40INDUSTRY]=0;
				}
				else 
				if(pl<=mi+4)

				{
					pl+=PickCosts[P_50INDUSTRY];
					picks[P_50INDUSTRY]=1;
				};break;


			case P_20SCIENCE:
				if(picks[P_20SCIENCE]==1)
				{
					mi+=PickCosts[P_20SCIENCE];
					picks[P_20SCIENCE]=0;
				}
				else
				if(mi<=7)
				{
					mi-=PickCosts[P_20SCIENCE];
					picks[P_20SCIENCE]=1;
					if(picks[P_40SCIENCE]==1)
					{
						pl-=PickCosts[P_40SCIENCE];
						picks[P_40SCIENCE]=0;
					}
					else 
					if(picks[P_50SCIENCE]==1)
					{
						pl-=PickCosts[P_50SCIENCE];
						picks[P_50SCIENCE]=0;
					}
				};break;
			case P_40SCIENCE:
				if(picks[P_40SCIENCE]==1)
				{
					pl-=PickCosts[P_40SCIENCE];
					picks[P_40SCIENCE]=0;
				}
				else
				if((picks[P_20SCIENCE]==1)&&(pl<=mi+4))
				{
					mi+=PickCosts[P_20SCIENCE];
					pl+=PickCosts[P_40SCIENCE];
					picks[P_40SCIENCE]=1;
					picks[P_20SCIENCE]=0;
				}
				else
				if(picks[P_50SCIENCE]==1)
				{
					pl+=PickCosts[P_40SCIENCE];
					pl-=PickCosts[P_50SCIENCE];
					picks[P_40SCIENCE]=1;
					picks[P_50SCIENCE]=0;
				}
				else 
				if(pl<=mi+7)
				{
					pl+=PickCosts[P_40SCIENCE];
					picks[P_40SCIENCE]=1;
				};break;
			case P_50SCIENCE:
				if(picks[P_50SCIENCE]==1)
				{
					pl-=PickCosts[P_50SCIENCE];
					picks[P_50SCIENCE]=0;
				}
				else
				if((picks[P_20SCIENCE]==1)&&(pl<=mi+1))
				{
					mi+=PickCosts[P_20SCIENCE];
					pl+=PickCosts[P_50SCIENCE];
					picks[P_50SCIENCE]=1;
					picks[P_20SCIENCE]=0;
				}
				else
				if((picks[P_40SCIENCE]==1)&&(pl<=mi+7))
				{
					pl+=PickCosts[P_50SCIENCE];
					pl-=PickCosts[P_40SCIENCE];
					picks[P_50SCIENCE]=1;
					picks[P_40SCIENCE]=0;
				}
				else 
				if(pl<=mi+4)
				{
					pl+=PickCosts[P_50SCIENCE];
					picks[P_50SCIENCE]=1;
				};break;


			case P_09SPY:
				if(picks[P_09SPY]==1)
				{
					mi+=PickCosts[P_09SPY];
					picks[P_09SPY]=0;
				}
				else
				if(mi<=7)
				{
					mi-=PickCosts[P_09SPY];
					picks[P_09SPY]=1;
					if(picks[P_11SPY]==1)
					{
						pl-=PickCosts[P_11SPY];
						picks[P_11SPY]=0;
					}
					else 
					if(picks[P_12SPY]==1)
					{
						pl-=PickCosts[P_12SPY];
						picks[P_12SPY]=0;
					}
				};break;
			case P_11SPY:
				if(picks[P_11SPY]==1)
				{
					pl-=PickCosts[P_11SPY];
					picks[P_11SPY]=0;
				}
				else
				if((picks[P_09SPY]==1)&&(pl<=mi+4))
				{
					mi+=PickCosts[P_09SPY];
					pl+=PickCosts[P_11SPY];
					picks[P_11SPY]=1;
					picks[P_09SPY]=0;
				}
				else
				if(picks[P_12SPY]==1)
				{
					pl+=PickCosts[P_11SPY];
					pl-=PickCosts[P_12SPY];
					picks[P_11SPY]=1;
					picks[P_12SPY]=0;
				}
				else 
				if(pl<=mi+7)
				{
					pl+=PickCosts[P_11SPY];
					picks[P_11SPY]=1;
				};break;
			case P_12SPY:
				if(picks[P_12SPY]==1)
				{
					pl-=PickCosts[P_12SPY];
					picks[P_12SPY]=0;
				}
				else
				if((picks[P_09SPY]==1)&&(pl<=mi+1))
				{
					mi+=PickCosts[P_09SPY];
					pl+=PickCosts[P_12SPY];
					picks[P_12SPY]=1;
					picks[P_09SPY]=0;
				}
				else
				if((picks[P_11SPY]==1)&&(pl<=mi+7))
				{
					pl+=PickCosts[P_12SPY];
					pl-=PickCosts[P_11SPY];
					picks[P_12SPY]=1;
					picks[P_11SPY]=0;
				}
				else 
				if(pl<=mi+4)
				{
					pl+=PickCosts[P_12SPY];
					picks[P_12SPY]=1;
				};break;

			case P_05BCS:
				if(picks[P_05BCS]==1)
				{
					mi+=PickCosts[P_05BCS];
					picks[P_05BCS]=0;
				}
				else
				if(mi<=6)
				{
					mi-=PickCosts[P_05BCS];
					picks[P_05BCS]=1;
					if(picks[P_15BCS]==1)
					{
						pl-=PickCosts[P_15BCS];
						picks[P_15BCS]=0;
					}
					else 
					if(picks[P_20BCS]==1)
					{
						pl-=PickCosts[P_20BCS];
						picks[P_20BCS]=0;
					}
				};break;
			case P_15BCS:
				if(picks[P_15BCS]==1)
				{
					pl-=PickCosts[P_15BCS];
					picks[P_15BCS]=0;
				}
				else
				if((picks[P_05BCS]==1)&&(pl<=mi+1))
				{
					mi+=PickCosts[P_05BCS];
					pl+=PickCosts[P_15BCS];
					picks[P_15BCS]=1;
					picks[P_05BCS]=0;
				}
				else
				if(picks[P_20BCS]==1)
				{
					pl+=PickCosts[P_15BCS];
					pl-=PickCosts[P_20BCS];
					picks[P_15BCS]=1;
					picks[P_20BCS]=0;
				}
				else 
				if(pl<=mi+5)
				{
					pl+=PickCosts[P_15BCS];
					picks[P_15BCS]=1;
				};break;
			case P_20BCS:
				if(picks[P_20BCS]==1)
				{
					pl-=PickCosts[P_20BCS];
					picks[P_20BCS]=0;
				}
				else
				if((picks[P_05BCS]==1)&&(pl<=mi-2))
				{
					mi+=PickCosts[P_05BCS];
					pl+=PickCosts[P_20BCS];
					picks[P_20BCS]=1;
					picks[P_05BCS]=0;
				}
				else
				if((picks[P_15BCS]==1)&&(pl<=mi+7))
				{
					pl+=PickCosts[P_20BCS];
					pl-=PickCosts[P_15BCS];
					picks[P_20BCS]=1;
					picks[P_15BCS]=0;
				}
				else 
				if(pl<=mi+2)
				{
					pl+=PickCosts[P_20BCS];
					picks[P_20BCS]=1;
				};break;

			case P_08ATTACK:
				if(picks[P_08ATTACK]==1)
				{
					mi+=PickCosts[P_08ATTACK];
					picks[P_08ATTACK]=0;
				}
				else
				if(mi<=8)
				{
					mi-=PickCosts[P_08ATTACK];
					picks[P_08ATTACK]=1;
					if(picks[P_12ATTACK]==1)
					{
						pl-=PickCosts[P_12ATTACK];
						picks[P_12ATTACK]=0;
					}
					else 
					if(picks[P_15ATTACK]==1)
					{
						pl-=PickCosts[P_15ATTACK];
						picks[P_15ATTACK]=0;
					}
				};break;
			case P_12ATTACK:
				if(picks[P_12ATTACK]==1)
				{
					pl-=PickCosts[P_12ATTACK];
					picks[P_12ATTACK]=0;
				}
				else
				if((picks[P_08ATTACK]==1)&&(pl<=mi+6))
				{
					mi+=PickCosts[P_08ATTACK];
					pl+=PickCosts[P_12ATTACK];
					picks[P_12ATTACK]=1;
					picks[P_08ATTACK]=0;
				}
				else
				if(picks[P_15ATTACK]==1)
				{
					pl+=PickCosts[P_12ATTACK];
					pl-=PickCosts[P_15ATTACK];
					picks[P_12ATTACK]=1;
					picks[P_15ATTACK]=0;
				}
				else 
				if(pl<=mi+8)
				{
					pl+=PickCosts[P_12ATTACK];
					picks[P_12ATTACK]=1;
				};break;
			case P_15ATTACK:
				if(picks[P_15ATTACK]==1)
				{
					pl-=PickCosts[P_15ATTACK];
					picks[P_15ATTACK]=0;
				}
				else
				if((picks[P_08ATTACK]==1)&&(pl<=mi+4))
				{
					mi+=PickCosts[P_08ATTACK];
					pl+=PickCosts[P_15ATTACK];
					picks[P_15ATTACK]=1;
					picks[P_08ATTACK]=0;
				}
				else
				if((picks[P_12ATTACK]==1)&&(pl<=mi+8))
				{
					pl+=PickCosts[P_15ATTACK];
					pl-=PickCosts[P_12ATTACK];
					picks[P_15ATTACK]=1;
					picks[P_12ATTACK]=0;
				}
				else 
				if(pl<=mi+6)
				{
					pl+=PickCosts[P_15ATTACK];
					picks[P_15ATTACK]=1;
				};break;


			case P_08DEFENSE:
				if(picks[P_08DEFENSE]==1)
				{
					mi+=PickCosts[P_08DEFENSE];
					picks[P_08DEFENSE]=0;
				}
				else
				if(mi<=8)
				{
					mi-=PickCosts[P_08DEFENSE];
					picks[P_08DEFENSE]=1;
					if(picks[P_12DEFENSE]==1)
					{
						pl-=PickCosts[P_12DEFENSE];
						picks[P_12DEFENSE]=0;
					}
					else 
					if(picks[P_15DEFENSE]==1)
					{
						pl-=PickCosts[P_15DEFENSE];
						picks[P_15DEFENSE]=0;
					}
				};break;
			case P_12DEFENSE:
				if(picks[P_12DEFENSE]==1)
				{
					pl-=PickCosts[P_12DEFENSE];
					picks[P_12DEFENSE]=0;
				}
				else
				if((picks[P_08DEFENSE]==1)&&(pl<=mi+5))
				{
					mi+=PickCosts[P_08DEFENSE];
					pl+=PickCosts[P_12DEFENSE];
					picks[P_12DEFENSE]=1;
					picks[P_08DEFENSE]=0;
				}
				else
				if(picks[P_15DEFENSE]==1)
				{
					pl+=PickCosts[P_12DEFENSE];
					pl-=PickCosts[P_15DEFENSE];
					picks[P_12DEFENSE]=1;
					picks[P_15DEFENSE]=0;
				}
				else 
				if(pl<=mi+7)
				{
					pl+=PickCosts[P_12DEFENSE];
					picks[P_12DEFENSE]=1;
				};break;
			case P_15DEFENSE:
				if(picks[P_15DEFENSE]==1)
				{
					pl-=PickCosts[P_15DEFENSE];
					picks[P_15DEFENSE]=0;
				}
				else
				if((picks[P_08DEFENSE]==1)&&(pl<=mi+1))
				{
					mi+=PickCosts[P_08DEFENSE];
					pl+=PickCosts[P_15DEFENSE];
					picks[P_15DEFENSE]=1;
					picks[P_08DEFENSE]=0;
				}
				else
				if((picks[P_12DEFENSE]==1)&&(pl<=mi+6))
				{
					pl+=PickCosts[P_15DEFENSE];
					pl-=PickCosts[P_12DEFENSE];
					picks[P_15DEFENSE]=1;
					picks[P_12DEFENSE]=0;
				}
				else 
				if(pl<=mi+3)
				{
					pl+=PickCosts[P_15DEFENSE];
					picks[P_15DEFENSE]=1;
				};break;


			case P_09GROUND:
				if(picks[P_09GROUND]==1)
				{
					mi+=PickCosts[P_09GROUND];
					picks[P_09GROUND]=0;
				}
				else
				if(mi<=8)
				{
					mi-=PickCosts[P_09GROUND];
					picks[P_09GROUND]=1;
					if(picks[P_11GROUND]==1)
					{
						pl-=PickCosts[P_11GROUND];
						picks[P_11GROUND]=0;
					}
					else 
					if(picks[P_12GROUND]==1)
					{
						pl-=PickCosts[P_12GROUND];
						picks[P_12GROUND]=0;
					}
				};break;
			case P_11GROUND:
				if(picks[P_11GROUND]==1)
				{
					pl-=PickCosts[P_11GROUND];
					picks[P_11GROUND]=0;
				}
				else
				if((picks[P_09GROUND]==1)&&(pl<=mi+6))
				{
					mi+=PickCosts[P_09GROUND];
					pl+=PickCosts[P_11GROUND];
					picks[P_11GROUND]=1;
					picks[P_09GROUND]=0;
				}
				else
				if(picks[P_12GROUND]==1)
				{
					pl+=PickCosts[P_11GROUND];
					pl-=PickCosts[P_12GROUND];
					picks[P_11GROUND]=1;
					picks[P_12GROUND]=0;
				}
				else 
				if(pl<=mi+8)
				{
					pl+=PickCosts[P_11GROUND];
					picks[P_11GROUND]=1;
				};break;
			case P_12GROUND:
				if(picks[P_12GROUND]==1)
				{
					pl-=PickCosts[P_12GROUND];
					picks[P_12GROUND]=0;
				}
				else
				if((picks[P_09GROUND]==1)&&(pl<=mi+4))
				{
					mi+=PickCosts[P_09GROUND];
					pl+=PickCosts[P_12GROUND];
					picks[P_12GROUND]=1;
					picks[P_09GROUND]=0;
				}
				else
				if((picks[P_11GROUND]==1)&&(pl<=mi+8))
				{
					pl+=PickCosts[P_12GROUND];
					pl-=PickCosts[P_11GROUND];
					picks[P_12GROUND]=1;
					picks[P_11GROUND]=0;
				}
				else 
				if(pl<=mi+6)
				{
					pl+=PickCosts[P_12GROUND];
					picks[P_12GROUND]=1;
				};break;


			case P_15FOOD:
				if(picks[P_LITHOVORE]==1)
				{
					picks[P_LITHOVORE]=0;
					pl-=PickCosts[P_LITHOVORE];
				}
				if(picks[P_15FOOD]==1)
				{
					mi+=PickCosts[P_15FOOD];
					picks[P_15FOOD]=0;
				}
				else
				if(mi<=7)
				{
					mi-=PickCosts[P_15FOOD];
					picks[P_15FOOD]=1;
					if(picks[P_30FOOD]==1)
					{
						pl-=PickCosts[P_30FOOD];
						picks[P_30FOOD]=0;
					}
					else 
					if(picks[P_40FOOD]==1)
					{
						pl-=PickCosts[P_40FOOD];
						picks[P_40FOOD]=0;
					}
				};break;
			case P_30FOOD:
				if(picks[P_LITHOVORE]==1)
				{
					picks[P_LITHOVORE]=0;
					pl-=PickCosts[P_LITHOVORE];
				}
				if(picks[P_30FOOD]==1)
				{
					pl-=PickCosts[P_30FOOD];
					picks[P_30FOOD]=0;
				}
				else
				if((picks[P_15FOOD]==1)&&(pl<=mi+3))
				{
					mi+=PickCosts[P_15FOOD];
					pl+=PickCosts[P_30FOOD];
					picks[P_30FOOD]=1;
					picks[P_15FOOD]=0;
				}
				else
				if(picks[P_40FOOD]==1)
				{
					pl+=PickCosts[P_30FOOD];
					pl-=PickCosts[P_40FOOD];
					picks[P_30FOOD]=1;
					picks[P_40FOOD]=0;
				}
				else 
				if(pl<=mi+6)
				{
					pl+=PickCosts[P_30FOOD];
					picks[P_30FOOD]=1;
				};break;
			case P_40FOOD:
				if(picks[P_LITHOVORE]==1)
				{
					picks[P_LITHOVORE]=0;
					pl-=PickCosts[P_LITHOVORE];
				}
				if(picks[P_40FOOD]==1)
				{
					pl-=PickCosts[P_40FOOD];
					picks[P_40FOOD]=0;
				}
				else
				if((picks[P_15FOOD]==1)&&(pl<=mi))
				{
					mi+=PickCosts[P_15FOOD];
					pl+=PickCosts[P_40FOOD];
					picks[P_40FOOD]=1;
					picks[P_15FOOD]=0;
				}
				else
				if((picks[P_30FOOD]==1)&&(pl<=mi+7))
				{
					pl+=PickCosts[P_40FOOD];
					pl-=PickCosts[P_30FOOD];
					picks[P_40FOOD]=1;
					picks[P_30FOOD]=0;
				}
				else 
				if(pl<=mi+3)
				{
					pl+=PickCosts[P_40FOOD];
					picks[P_40FOOD]=1;
				};break;
			}
		};

void player::Create()
{
	unsigned short i,j,k;

	pl=0;mi=0;

	for(i=0;i<MAX_PICKS;i++);
		TryPick(rand()%MAX_PICKS);
	while(pl<mi+8)
		TryPick(rand()%MAX_PICKS);
		
		for(i=0;i<MAX_ORDERS;i++)
			OQueue[i]=rand()%ORDER_COUNT;
		for(i=0;i<MAX_SCIENCE;i++)
			SQueue[i]=0;
		for(i=0;i<8;i++)
				progress[i]=0;

		for(i=0;i<MAX_SCIENCE;i++)
			SQueue[i]=rand()%100;
/*		{
			t=SelectResearch(rand()%25);
			while(CanResearch(t)==0) t=SelectResearch(rand()%25);
			SQueue[i]=t;
			tech[t]=1;
			Area[ScienceArea[t].Field][ScienceArea[t].Progress]=1;
		}*/

		
		ScienceList[0]=0;
		ScienceList[1]=1;
		ScienceList[2]=2;
		ScienceList[3]=33;
		ScienceList[4]=55;
		ScienceList[5]=71;
		ScienceList[6]=78;
		ScienceList[7]=102;
		ScienceList[8]=103;
		ScienceList[9]=119;
		ScienceList[10]=146;

		SLMax=11;
/*


SQueue[0]=T_ELECTRONIC_COMPUTER;
SQueue[1]=T_RESEARCH_LAB;
SQueue[2]=T_REINFORCED_HULL;
SQueue[3]=T_AUTOMATED_FACTORIES;
SQueue[4]=T_BIOSPHERES;

  SQueue[5]=T_CLONING_CENTER;
SQueue[6]=T_NEURAL_SCANNER;
SQueue[7]=T_PLANETARY_SUPERCOMPUTER;
SQueue[8]=T_CHEMISTRY;
SQueue[9]=T_TRITANIUM_ARMOR;
SQueue[10]=T_POLLUTION_PROCESSOR;
SQueue[11]=T_BATTLE_PODS;
SQueue[12]=T_SPACE_PORT;
SQueue[13]=T_ROBO_MINE_PLANT;
SQueue[14]=T_PHYSICS;
SQueue[15]=T_FUSION_RIFLE;
SQueue[16]=T_BATTLE_SCANNER;
SQueue[17]=T_ATMOSPHERE_RENEWER;
SQueue[18]=T_ZORTIUM_ARMOR;
SQueue[19]=T_NUCLEAR_FISSION;
SQueue[20]=T_COLD_FUSION;
SQueue[21]=T_AUGMENTED_ENGINES;*/
	}

	void player::Mutate()
	{
		unsigned char ttt,ta,tb;
		unsigned short x,y,i,k;

	//loeschen, einfuegen, veraendern
		for(k=0;k<Mutations;k++)
		{

			// Locations rein!!!!
			if(rand()%Mutations==0)
			{
				x=rand()%MAX_ORDERS;
				for(y=x;y<MAX_ORDERS-1;y++)
					OQueue[y]=OQueue[y+1];
			}
			if(rand()%Mut_Rate==0)
			{
				x=rand()%MAX_ORDERS;
				for(y=MAX_ORDERS-1;y>x;y--)
					OQueue[y]=OQueue[y-1];
				OQueue[x]=rand()%MAX_ORDERS;
			}		
			if(rand()%Mut_Rate==0)
			{
				x=rand()%MAX_ORDERS;
				OQueue[x]=rand()%MAX_ORDERS;
			}
			if(rand()%Mut_Rate==0)
			{
				ta=rand()%MAX_ORDERS;
				tb=rand()%MAX_ORDERS;
				ttt=OQueue[ta];
				OQueue[ta]=OQueue[tb];
				OQueue[tb]=ttt;
			}
			if(rand()%(Mut_Rate/2)==0)
			{
				ta=rand()%MAX_ORDERS;
				tb=rand()%MAX_ORDERS;
				if(ta>tb)
				{
					ttt=OQueue[ta];
					for(i=ta;i<tb;i++)
						OQueue[i]=OQueue[i+1];
					OQueue[tb]=ttt;
				}
			}
			if(rand()%Mut_Rate==0)
				TryPick(rand()%MAX_PICKS);
		}
	}


};

player P,S;

/*Mutation, Weitergabe, Save

Schiffe!!
Besiedelungsfunktion
etc.etc.
aber sieht schon gut aus :)*/





unsigned char Planets::CanBuild(unsigned char item)
{
	unsigned char a,b;
	if(Building[item]==1) return 0;
	for(a=0;a<10;a++)
		if(BQueue[a]==item) return 0;
	switch(item)
	{
		case B_COLONY_BASE:b=1;for(a=0;a<5;a++) b&=((System[system].Object[a]->Settlement>0)||(System[system].Object[a]->Type<3));if(b==1) return 0;break;
		case B_AUTOMATED_FACTORIES:if(P.tech[T_AUTOMATED_FACTORIES]==0) return 0;break;
		case B_MISSILE_BASE:if(P.tech[T_MISSILE_BASE]==0) return 0;break;
		case B_SPACE_PORT:if(P.tech[T_SPACE_PORT]==0) return 0;break;
		case B_ARMOR_BARRACKS:if(P.tech[T_ARMOR_BARRACKS]==0) return 0;break;
		case B_FIGHTER_GARRISON:if(P.tech[T_FIGHTER_GARRISONS]==0) return 0;break;
		case B_ROBO_MINE_PLANT:if(P.tech[T_ROBO_MINE_PLANT]==0) return 0;break;
		case B_BATTLE_STATION:if(P.tech[T_BATTLE_STATION]==0) return 0;break;
		case B_GROUND_BATTERIES:if(P.tech[T_GROUND_BATTERIES]==0) return 0;break;
		case B_RECYCLOTRON:if(P.tech[T_RECYCLOTRON]==0) return 0;break;
		case B_ARTIFICIAL_PLANET_CONSTRUCTION:if(P.tech[T_ARTIFICIAL_PLANET_CONSTRUCTION]==0) return 0;break;// nur wenn gas/asteroid da is
		case B_ROBOTIC_FACTORY:if(P.tech[T_ROBOTIC_FACTORY]==0) return 0;break;
		case B_DEEP_CORE_MINE:if(P.tech[T_DEEP_CORE_MINE]==0) return 0;break;
		case B_CORE_WASTE_DUMP:if(P.tech[T_CORE_WASTE_DUMP]==0) return 0;break;
		case B_STAR_FORTRESS:if(P.tech[T_STAR_FORTRESS]==0) return 0;break;
		case B_ARTEMIS_SYSTEM_NETWORK:if(P.tech[T_ARTEMIS_SYSTEM_NETWORK]==0) return 0;break; // nur eins im system

		case B_SHIP_1:
		case B_SHIP_2:
		case B_SHIP_3:
		case B_SHIP_4:
		case B_SHIP_5:
		case B_OUTPOST_SHIP:
		case B_TRANSPORT:
		case B_COLONY_SHIP:if((P.tech[T_COLD_FUSION]==0)||(P.tech[T_CHEMISTRY]==0)) return 0;break;
		case B_FREIGHTERS:if(P.tech[T_NUCLEAR_FISSION]==0) return 0;break;
		case B_FOOD_REPLICATOR:if(P.tech[T_FOOD_REPLICATOR]==0) return 0;break;
		case B_POLLUTION_PROCESSOR:if(P.tech[T_POLLUTION_PROCESSOR]==0) return 0;break;
		case B_ATMOSPHERE_RENEWER:if(P.tech[T_ATMOSPHERE_RENEWER]==0) return 0;break;
		case B_SPACE_ACADEMY:if(P.tech[T_SPACE_ACADEMY]==0) return 0;break;
		case B_ALIEN_CONTROL_CENTER:if(P.tech[T_ALIEN_CONTROL_CENTER]==0) return 0;break;
		case B_STOCK_EXCHANGE:if(P.tech[T_STOCK_EXCHANGE]==0) return 0;break;
		case B_ASTRO_UNIVERSITY:if(P.tech[T_ASTRO_UNIVERSITY]==0) return 0;break;
		case B_RESEARCH_LAB:if(P.tech[T_RESEARCH_LAB]==0) return 0;break;
		case B_PLANETARY_SUPERCOMPUTER:if(P.tech[T_PLANETARY_SUPERCOMPUTER]==0) return 0;break;
		case B_HOLO_SIMULATOR:if(P.tech[T_HOLO_SIMULATOR]==0) return 0;break;
		case B_AUTOLAB:if(P.tech[T_AUTOLAB]==0) return 0;break;
		case B_ANDROID_FARMER:if(P.tech[T_ANDROID_FARMERS]==0) return 0;break;
		case B_ANDROID_WORKER:if(P.tech[T_ANDROID_WORKERS]==0) return 0;break;
		case B_ANDROID_SCIENTIST:if(P.tech[T_ANDROID_SCIENTISTS]==0) return 0;break;
		case B_GALACTIC_CYBERNETWORK:if(P.tech[T_GALACTIC_CYBERNETWORK]==0) return 0;break;
		case B_PLEASURE_DOME:if(P.tech[T_PLEASURE_DOME]==0) return 0;break; //? unific?
		case B_HYDROPONIC_FARM:if(P.tech[T_HYDROPONIC_FARM]==0) return 0;break;
		case B_BIOSPHERES:if(P.tech[T_BIOSPHERES]==0) return 0;break;
		case B_CLONING_CENTER:if(P.tech[T_CLONING_CENTER]==0) return 0;break;
		case B_SOIL_ENRICHMENT:if(P.tech[T_SOIL_ENRICHMENT]==0) return 0;break; //?
		case B_TERRAFORMING:if(P.tech[T_TERRAFORMING]==0) return 0;break; //?
		case B_SUBTERRAN_FARMS:if(P.tech[T_SUBTERRAN_FARMS]==0) return 0;break; //?
		case B_WEATHER_CONTROL_SYSTEM:if(P.tech[T_WEATHER_CONTROL_SYSTEM]==0) return 0;break; //?
		case B_GAIA_TRANSFORMATION:if(P.tech[T_GAIA_TRANSFORMATION]==0) return 0;break; //?
		case B_DIMENSION_PORTAL:if(P.tech[T_DIMENSION_PORTAL]==0) return 0;break; //?
		case B_STELLAR_CONVERTER:if(P.tech[T_STELLAR_CONVERTER]==0) return 0;break;
		case B_PLANETARY_RADIATION_SHIELD:if(P.tech[T_PLANETARY_RADIATION_SHIELD]==0) return 0;break; //?
		case B_WARP_FIELD_DISSIPATOR:if(P.tech[T_WARP_DISSIPATOR]==0) return 0;break; //?
		case B_PLANETARY_FLUX_SHIELD:if(P.tech[T_PLANETARY_FLUX_SHIELD]==0) return 0;break; //?
		case B_PLANETARY_BARRIER_SHIELD:if(P.tech[T_PLANETARY_BARRIER_SHIELD]==0) return 0;break; //?
		case B_GRAVITY_GENERATOR:if((P.tech[T_PLANETARY_GRAVITATION_GENERATION]==0)|| ( (Gravitation==0)&&(P.picks[P_LOWG]==1) ) || ( (Gravitation==1) && ( P.picks[P_LOWG]==0) ) || ((Gravitation==2)&&(P.picks[P_HIGHG]==1))) return 0;break;
//		case B_GOVERNMENT_CENTER:if(P.NoGoverment==0) return 0;break;
	};

		


/*	not already in queue
	tech availible
	not availible because of grav/race/already built in system?
	not already built*/
		return 1;
};














void main()
{
	unsigned short i,j,oldf;
	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord={0,0};
	ofstream out_file("bo.txt");


	srand(time(NULL));
	for(i=0;i<1000;i++)
		j=rand()%2;
	j=0;
Mutations=MAX_ORDERS;
Mut_Rate=50;
oldf=0;

for(i=0;i<MAX_SYSTEMS;i++)
	for(j=0;j<5;j++)
		System[i].Object[j]=&planet[i*5+j];

for(i=0;i<MAX_ORDERS;i++)
	S.OQueue[i]=P.OQueue[i];
for(i=0;i<MAX_TECH;i++)
	S.SQueue[i]=P.SQueue[i];
for(i=0;i<MAX_PICKS;i++)
	S.picks[i]=P.picks[i];
		S.time=P.time;
		S.orders=P.orders;
P.Init();
P.Create();


while(kbhit()==0)
{
	P.Init();
//	if(rand()%20==0) P.Create();

	P.RestartGalaxy();
	P.BetweenTime();
//	printf(".");

	if(P.Fitness>oldf)
	{
		//		SetConsoleCursorPosition(hStdOut,coord);
		oldf=P.Fitness;
	//	for(i=0;i<MAX_BUILDINGS;i++)
		printf("(%i) ",P.Fitness);
			for(j=0;j<MAX_PLANETS;j++)
				if(planet[j].Settlement>0)
					printf("%i: %i/%i, ",planet[j].Settlement,planet[j].Population,planet[j].maxPop);

	//			if(planet[j].Building[i]==1) 
	//				printf("%s",BName[i].Name);
//			if(P.OQueue[i]<161) printf(" %s |",Orders[P.OQueue[i]].Name);
	printf("-(T: %i)  (O: %i)-\n",P.time,P.orders);
	
		for(i=0;i<MAX_ORDERS;i++)
			S.OQueue[i]=P.OQueue[i];
		for(i=0;i<MAX_TECH;i++)
			S.SQueue[i]=P.SQueue[i];
		for(i=0;i<MAX_PICKS;i++)
			S.picks[i]=P.picks[i];
		S.time=P.time;
		S.orders=P.orders;
	}
	else
	{
		for(i=0;i<MAX_ORDERS;i++)
			P.OQueue[i]=S.OQueue[i];
		for(i=0;i<MAX_TECH;i++)
			P.SQueue[i]=S.SQueue[i];
		for(i=0;i<MAX_PICKS;i++)
			P.picks[i]=S.picks[i];
	}
	P.Mutate();
}
	out_file<<"Time: "<<S.time;
	out_file<<"Orders: "<<S.orders;


	out_file<<"Orders:\n";
	for(i=0;i<MAX_ORDERS;i++)
	{
		if(S.OQueue[i]<180) out_file<<Orders[S.OQueue[i]].Name;
		if((S.OQueue[i]>36)&&(S.OQueue[i]<99))
			out_file<<"  "<<BName[S.OQueue[i]-37].Name;
		else if((S.OQueue[i]>98)&&(S.OQueue[i]<161))
			out_file<<"  "<<BName[S.OQueue[i]-99].Name;
		
		if(S.OQueue[i]>179) out_file<<">>\n"; else out_file<<" | ";
	}

	out_file<<"Science:\n";
	for(i=0;i<MAX_TECH;i++)
		out_file<<TName[S.SQueue[i]].Name<<"\n";

	out_file<<"Picks:\n";
	for(i=0;i<MAX_PICKS;i++)
		if(S.picks[i]==1)
			out_file<<PName[i].Name<<"\n";

	out_file.close();
};


// In output noch larven?





// Verbesserungen: evtl doch cross over und multiple viecher
// 
