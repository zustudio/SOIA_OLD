#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "SDL.h"
#include "MTypes.h"
#include "MDebug.h"
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
#define SIM_MapFunctionArgs	{100, 1, 0.0001F}	//{SIM_Val_Max, SIM_Slope}
#define mapfunction(x)		SIM_MapFunctionType::get_f((x), SIM_MapFunctionArgs)
#define rev_mapfunction(f)	SIM_MapFunctionType::get_reverse_x((f), SIM_MapFunctionArgs)


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

			float lnk = mapfunction(0);
			bLLinked = true;

			if (depth > 0)		// else: if chain has ended, return default (value for no match)
			{
				if (int(*me) == int(*te))	//if me == te
				{
					lnk = mapfunction(1);				//return value for best match
				}
				else if (depth > 1)						//else try to match the children
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
					}
					}

					if (depth == 2)
					{
						std::string meData = "[";
						std::string teData = "[";

						for (int xData = 0; xData < nC_me; xData++)
						{
							meData += std::to_string((*me)[xData]->get());
							meData += " |";
						}
						meData += "]";
						
						for (int yData = 0; yData < nC_te; yData++)
						{
							teData += std::to_string((*te)[yData]->get());
							teData += " |";
						}
						teData += "]";
						

						DataLog("Linking x to y:");
						DataLog(meData);
						DataLog(linkResults.to_string());
						DataLog(teData);
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
					std::deque<float> sortedLostValues = { 1000000 };	// (from lowest to highest)
					std::deque<std::pair<float, Vector2D<int> > > sortedLinkGains = { std::make_pair(1000000, Vector2D<int>()) };
					std::deque<float> sortedLinkGains_Display = { 1000000 };

					for (int x = 0; x < n_children; x++)
					{
						for (int y = 0; y < n_children; y++)
						{
							float lostValue = ColumnSums[x] + RowSums[x] - 3 * (*linkResults.get(x, y));

							// III - Try to minimize value lost (thus maximizing the perfectness of match) via finding lowest lostValues
							//         Sort value into already sorted values.
							for (int i = 0; i < sortedLostValues.size(); i++)
							{
								if (lostValue <= sortedLostValues[i])
								{
									sortedLostValues.insert(sortedLostValues.begin() + i, lostValue);
									float linkResult = *linkResults.get(x, y);
									auto pair = std::make_pair(linkResult, Vector2D<int>(x, y));
									sortedLinkGains.insert(sortedLinkGains.begin() + i, pair);
									sortedLinkGains_Display.insert(sortedLinkGains_Display.begin() + i, pair.first);
									break;
								}
							}
						}
					}
					if (depth == 2)
					{
						DataLog("Sorted Values are: " + (std::string)VectorND<float>(sortedLostValues));
						DataLog("Corresponding link results: " + std::string(VectorND<float>(sortedLinkGains_Display)));
					}
					

					//  IV - calculate the total match perfectness, via finding linkresults corresponding to lowest lostValues,
					//       ignore values, if their row or column is already used
					std::vector<int> usedColumns;
					std::vector<int> usedRows;

		
					std::string chosenLinks_text;
					int found = 0;
					for (int i = 0; found < n_children; i++)
					{
						auto pair = sortedLinkGains[i];
						if (std::find(usedColumns.begin(), usedColumns.end(), pair.second.X) == usedColumns.end()
							&& std::find(usedRows.begin(), usedRows.end(), pair.second.Y) == usedRows.end())
						{
							sum_n += pair.first;
							usedColumns.push_back(pair.second.X);
							usedRows.push_back(pair.second.Y);
							chosenLinks_text += std::string("(") + std::to_string(pair.second.X) + " | " + std::to_string(pair.second.Y) + "); ";
							found++;
						}
					}
					DataLog("Chosen links are: " + chosenLinks_text);

					if (depth == 2)
						DataLog("Counting first " + std::to_string(n_children) + " elements. Equal to " + std::to_string(sum_n));
					
					float sim = mapfunction(sum_n / n_children);

					lnk = sim;
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
			DataLog("Found " + std::to_string(Values.size()) + " connected lightlinks");
			for (int i_AllVals = 0; i_AllVals < Values.size(); i_AllVals++)
			{
				DataLog(" - [" + std::to_string(i_AllVals) + "] " + std::to_string(Values[i_AllVals]));
			}
			DataLog("chosen option => [" + std::to_string(i_Value) + "]");
			Super::set(value);

			//delete llinks again:
			for (IData* temp : llinks)
			{
				temp->Destroy();
				delete temp;
			}

			return value;
		}

		//------------------------ children -----------------------
		virtual void connect(IData* NewSub) override { connect(NewSub, DataType::Link); }
		virtual IData* connect(IData* NewSub, DataType WantedLinkType)
		{
			switch (((MSimDec<Super>*)NewSub)->Type)
			{
				case DataType::Content:
				{
					MSimDec<Super>* link = new MSimDec<Super>(WantedLinkType, nullptr, "", cIA_LinkContent);
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
