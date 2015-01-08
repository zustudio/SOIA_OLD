#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "MTypes.h"
#include "Random.h"

//////////////////////////////////////////////////////////////////////////////////
// Definitions
//---- Values ----
/*	the worst and best possible similarity between two structures*/
#define SIM_Val_Max				cIA_LinkContent
#define SIM_Val_Min				(SIM_Val_Max / 10)
/*	value that causes data to be in "superposition", postponing its evaluation to the next (int)(*X) call*/
#define SIM_Val_X 987654
//---- LinkContentFunction Variables ----
/*	slope of **function, causes SIM_Val_Min for n = n_children to be (1/Slope) */
#define SIM_Slope			SIM_Val_Min
/*	multiplicator for n_child's*/
#define SIM_Demult			0.9
//---- math ----
#define logBASE(val, base)	(std::log(val) / std::log(base))


namespace IA
{
	template<class Super>
	class MSimDec : public MTypes < Super >
	{
	public:
		///////////////////////////////////////////////
		// vars
		bool bLLinked;
		///////////////////////////////////////////////
		// init
		template<typename... Args>
		MSimDec(DataType NewType, Args&&... args) : MTypes<Super>(NewType, args...) { bLLinked = false; }
		///////////////////////////////////////////////
		// light linking = pattern matching
		float llink(IData* te, int depth)
		{
			if (((MSimDec<Super>*)te)->bLLinked || bLLinked)
				return SIM_Val_Max;

			IData* me = this;

			IData* lnk = ((MSimDec<Super>*)me)->connect(te, DataType::LightLink);
			bLLinked = true;

			if (depth > 0)		// else: if chain has ended, return default (value for no match)
			{
				if (int(*me) == int(*te))	//if me == te
				{
					*lnk = SIM_Val_Min;				//return value for best match
				}
				else						//else try to match the children
				{
					int nC_me = me->getConnectedNum();
					int nC_te = te->getConnectedNum();

					float SIM_child = 0;		// similarity of single child
					float n_child = 0;			// scalar value: (n=0 -> no match | n=1 -> perfect match) is calculated for each child
					float sum_n = 0;			// sum of single scalar values
					int n_children = std::fmax(nC_me, nC_te);		// total amount of combinations between children

					for (int pC_me = 0; pC_me < nC_me; pC_me++)		// iterate over every comibination
					{												//
					for (int pC_te = 0; pC_te < nC_te; pC_te++)		//
					{
						SIM_child = ((MSimDec<Super>*)(*me)[pC_me])->llink((*te)[pC_te], depth - 1);
						n_child = -logBASE((SIM_child / SIM_Val_Max), SIM_Slope);
						sum_n += SIM_Demult * n_child;
					}
					}

					float sim = SIM_Val_Max * std::pow(SIM_Slope, (- sum_n / n_children));
					*lnk = int(sim);
				}
			}

			return *lnk;
		}

		///////////////////////////////////////////////
		// overrides
		//------------------------ content  -----------------------
		virtual int get() override
		{
			int realValue = Super::get();
			if (realValue != SIM_Val_X)
			{
				return realValue;
			}
			else
			{
				std::vector<float> Values;
				int n = Super::getConnectedNum();
				for (int i = 0; i < n; i++)
				{
					MSimDec<Super>* lnk = (MSimDec<Super>*) Super::getConnected(i);
					if (isChild(lnk, DataType::LightLink, LinkType::NoLink))
					{
						Values.push_back((float)(lnk->Super::get()));
					}
				}

				int i_Value = ZABS::Math::Random::InfluencedRand(Values);
				int value = Values[i_Value];
#if cSO_DebugData > 0
				std::cout << "[MSimDec]: found " << Values.size() << " connected lightlinks" << std::endl;
				for (int i_AllVals = 0; i_AllVals < Values.size(); i_AllVals++)
				{
					std::cout << "[MSimDec]:  - [" << i_AllVals << "] " << Values[i_AllVals] << std::endl;
				}
				std::cout << "[MSimDec]: chosen option => [" << i_Value << "]" << std::endl;
#endif
				set(value);
				return value;
			}
		}
		//------------------------ children -----------------------
		virtual void connect(IData* NewSub) override { connect(NewSub, DataType::Link); }
		virtual IData* connect(IData* NewSub, DataType WantedLinkType)
		{
			switch (((MSimDec<Super>*)NewSub)->Type)
			{
				case DataType::Content:
				{
					MSimDec<Super>* link = new MSimDec<Super>(WantedLinkType, "", cIA_LinkContent);
					this->Super::connect(link);
					link->Super::connect(NewSub);
					return link;
				} break;
				default:/*case DataType::Link:*/
				{
					Super::connect(NewSub);
					return nullptr;
				} break;
			}
		}
	};
}
