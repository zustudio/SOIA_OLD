#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "MTypes.h"
#include "Matrix2D.h"
#include "Random.h"
#include "ExponentialFunction.h"
#include "ReversedExponentialFunction.h"
#include "LinearFunction.h"

using namespace ZABS::Math;

//////////////////////////////////////////////////////////////////////////////////
// Definitions
//---- Values ----
/*	the worst and best possible similarity between two structures*/
#define SIM_Val_Max				cIA_LinkContent
#define SIM_Val_Min				(SIM_Val_Max / 20)
/*	value that causes data to be in "superposition", postponing its evaluation to the next (int)(*X) call*/
#define SIM_Val_X 987654
//---- LinkContentFunction Variables ----
/*	slope of **function, causes SIM_Val_Min for n = n_children to be (1/Slope) */
#define SIM_Slope			SIM_Val_Min
/*	multiplicator for n_child's*/
#define SIM_Demult			1
//---- functions ----
#define SIM_MapFunctionType	ReversedExponentialFunction
#define SIM_MapFunctionArgs	{100, 1, 0.01F}	//{SIM_Val_Max, SIM_Slope}
#define mapfunction(x)		SIM_MapFunctionType::get_f((x), SIM_MapFunctionArgs)
#define rev_mapfunction(f)	SIM_MapFunctionType::get_reverse_x((f), SIM_MapFunctionArgs)
//---- math ----
//#define logBASE(val, base)	(std::log(val) / std::log(base))


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
		virtual ~MSimDec() {}
		///////////////////////////////////////////////
		// light linking = pattern matching
		float llink(IData* te, int depth)
		{
			IData* lnk = this->connect(te, DataType::LightLink);
			lnk->set(exe_llink(te, depth));
			return *lnk;
		}
		float exe_llink(IData* te, int depth)
		{
			IData* me = this;

			int lnk = mapfunction(0);
			bLLinked = true;

			if (depth > 0)		// else: if chain has ended, return default (value for no match)
			{
				if (int(*me) == int(*te))	//if me == te
				{
					lnk = mapfunction(1);				//return value for best match
				}
				else						//else try to match the children
				{
					int nC_me = me->getConnectedNum();
					int nC_te = te->getConnectedNum();

					float SIM_child = 0;		// similarity of single child
					float n_child = 0;			// scalar value: (n=0 -> no match | n=1 -> perfect match) is calculated for each child
					float sum_n = 0;			// sum of single scalar values
					int n_children = std::fmax(nC_me, nC_te);		// total amount of combinations between children
					Matrix2D<float> linkResults = Matrix2D<float>(n_children, n_children, 0);

					for (int pC_me = 0; pC_me < nC_me; pC_me++)		// iterate over every comibination
					{												//
					for (int pC_te = 0; pC_te < nC_te; pC_te++)		//
					{
						SIM_child = ((MSimDec<Super>*)(*me)[pC_me])->exe_llink((*te)[pC_te], depth - 1);
						n_child = rev_mapfunction(SIM_child);

						// save results into a matrix for calculation
						linkResults.set(pC_me, pC_te, n_child);

						//sum_n += SIM_Demult * n_child;
					}
					}

					// calculate value of best match:
					std::vector<float> ColumnSums;
					std::vector<float> RowSums;

					//   I - calculate sums of individual columns and rows
					for (int x = 0; x < n_children; x++)
					{
						ColumnSums.push_back(linkResults.GetColumn(x).Sum());
					}

					for (int y = 0; y < n_children; y++)
					{
						RowSums.push_back(linkResults.GetRow(y).Sum());
					}

					//  II - calculate for each linkResult the value of connections, which would be lost, if this linkResult
					//		 would be taken as matching path, thus disallowing all value of corresponding rows and columns
					Matrix2D<float> lostValues = Matrix<float>(n_children, n_children, 0);

					for (int x = 0; x < n_children; x++)
					{
						for (int y = 0; y < n_children; y++)
						{
							lostValues.set(x, y, ColumnSums[x] + RowSums[x] - 2 * (*linkResults.get(x, y)));
						}
					}

					// III - try to minimize value lost (thus maximizing the perfectness of match) via finding lowest lostValues

					//  IV - calculate the total match perfectness, via finding linkresults corresponding to lowest lostValues





					float sim = mapfunction(sum_n / n_children);

					lnk = int(sim);
				}
			}

			return lnk;
		}

		///////////////////////////////////////////////
		// overrides
		//------------------------ content  -----------------------
		virtual int CollapseOpenLLinks()
		{
			std::vector<float> Values;
			std::vector<IData*> datas;
			std::vector<IData*> llinks;
			int n = Super::getConnectedNum();
			for (int i = 0; i < n; i++)
			{
				MSimDec<Super>* lnk = (MSimDec<Super>*) Super::getConnected(i);
				if (MTypes<Super>::isChild(lnk, DataType::LightLink, LinkType::NoLink))
				{
					llinks.push_back(lnk);
					Values.push_back((float)(lnk->Super::get()));

					IData* content = lnk->Super::getConnected(0) == this ? lnk->Super::getConnected(1) : lnk->Super::getConnected(0);

					datas.push_back(content);
				}
			}

			n = Values.size();
			for (int i = 0; i < n; i++)
			{
				Values[i] = SIM_Val_Max - Values[i];
			}

			int i_Value = ZABS::Math::Random::InfluencedRand(Values);
			int value = *(datas[i_Value]);
#if cSO_DebugData > 0
			std::cout << "[MSimDec]: found " << Values.size() << " connected lightlinks" << std::endl;
			for (int i_AllVals = 0; i_AllVals < Values.size(); i_AllVals++)
			{
				std::cout << "[MSimDec]:  - [" << i_AllVals << "] " << Values[i_AllVals] << std::endl;
			}
			std::cout << "[MSimDec]: chosen option => [" << i_Value << "]" << std::endl;
#endif
			Super::set(value);

			//delete llinks again:
			for (IData* temp : llinks)
			{
				temp->Destroy();
				delete temp;
			}

			return value;
		}

		/*virtual int get() override
		{
			int realValue = Super::get();
			if (realValue != SIM_Val_X)
			{
				return realValue;
			}
		}*/
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
