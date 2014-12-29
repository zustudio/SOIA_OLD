#pragma once

#include <cmath>

#include "MTypes.h"

//////////////////////////////////////////////////////////////////////////////////
// Definitions
/*	the worst and best possible similarity between two structures*/
#define SIM_Max				cIA_LinkContent
#define SIM_Min				(SIM_Max / 10)
/*	slope of **function, causes SIM_Min for n = n_children to be (1/Slope) */
#define SIM_Slope			SIM_Min
/*	multiplicator for n_child's*/
#define SIM_Demult			0.9
/*	math*/
#define logBASE(val, base)	(std::log(val) / std::log(base))


namespace IA
{
	class DataType2 : public DataType
	{
	public:
		DataType2(int newI) : DataType(newI) {}
		enumElement(LightLink, 3);
	};
	/*class LinkType2 : public LinkType
	{
	public:
		LinkType2(int newI) : LinkType(newI) {}
		enumElement(IncludeLightLinks, 4);
	};*/

	template<class Super>
	class MSimDec : public MTypes < Super >
	{
	public:
		///////////////////////////////////////////////
		// init
		template<typename... Args>
		MSimDec(DataType2 NewType, Args&&... args) : MTypes<Super>(NewType, args...) {}
		///////////////////////////////////////////////
		// light linking = pattern matching
		float llink(IData* te, int depth)
		{
			IData* me = this;

			IData* lnk = ((MSimDec<Super>*)me)->connect(te, DataType2::LightLink);

			if (depth <= 0)		//if chain has ended
				return *lnk;	//return default (value for no match)
			else
			{
				if (int(*me) == int(*te))	//if me == te
				{
					*lnk = SIM_Min;				//return value for best match
					return *lnk;
				}
				else						//else try to match the children
				{
					int nC_me = me->getConnectedNum();
					int nC_te = te->getConnectedNum();

					float SIM_child = 0;		// similarity of single child
					float n_child = 0;			// scalar value: (n=0 -> no match | n=1 -> perfect match) is calculated for each child
					float sum_n = 0;			// sum of single scalar values
					int n_children = std::fmin(nC_me, nC_te);		// total amount of combinations between children

					for (int pC_me = 0; pC_me < nC_me; pC_me++)
					{
					for (int pC_te = 0; pC_te < nC_te; pC_te++)
					{
						SIM_child = ((MSimDec<Super>*)(*me)[pC_me])->llink((*te)[pC_te], depth - 1);
						n_child = -logBASE((SIM_child / SIM_Max), SIM_Slope);
						sum_n += SIM_Demult * n_child;
					}
					}

					float sim = SIM_Max * std::pow(SIM_Slope, (- sum_n / n_children));

					*lnk = int(sim);
					return sim;
				}
			}
		}

		///////////////////////////////////////////////
		// overrides
		virtual void connect(IData* NewSub) override { connect(NewSub, DataType2::Link); }
		virtual IData* connect(IData* NewSub, DataType2 WantedLinkType)
		{
			switch (((MSimDec<Super>*)NewSub)->Type)
			{
				case DataType::Content:
				{
					MSimDec<Super>* link = new MSimDec<Super>(WantedLinkType, cIA_LinkContent);
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
