
#include "Draw_2D.h"

using namespace IA::MeaningStream;

#define DebugLog(string) std::cout << string << std::endl;

void Draw_2D::Draw(CCanvas* Canvas, std::deque<ExGroup*>* Groups)
{
	//---- check dimension of the extend of my groups ----
	int dim_Extend = 0;
	for (ExGroup* group : *Groups)
	{
		VectorND<float>* extend = group->GetExtend();
		dim_Extend = std::fmax(extend->dim(), dim_Extend);
	}

	std::cout << "[MS::Draw_2D]: Info: Maximal Dimension of groups is " + std::to_string(dim_Extend) + '\n';

	if (dim_Extend > 2)
	{
		std::cout << "[MeaningStream::Draw_2D]: Error: Dimension of extend of drawn groups out of bounds\n";
		return;
	}

	//---- set integer location of data according to child groups ----
	for (ExGroup* group : *Groups)
	{
		int n_data = group->GetOccupants()->size();
		for (int i_data = 0; i_data < n_data; i_data++)
		{
			std::deque<ExGroup*>* childGroups = group->GetChildGroups();
			ExData* data = (*group->GetOccupants())[i_data];
			if (i_data >= childGroups->size())
			{
				data->InterpProps.IntExtend = 1;
			}
			else
			{
				ExGroup* childGroup = (*childGroups)[i_data];
				data->InterpProps.IntExtend = *childGroup->GetExtend();
			}
			std::cout << "[MS::Draw_2D]: Info: Found data '" + *data->getText() + "' with extend of " + std::to_string(data->InterpProps.IntExtend.dim()) << std::endl;
		}
	}

	//TEST
	return;
	//ENDTEST

	//---- drawing the data ----
	Canvas->Clear();

	for (ExGroup* group : *Groups)
	{
		for (ExData* data : *group->GetOccupants())
		{
			fPoint Loc = fPoint(data->Location.X - 0.5* data->Extend.X, data->Location.Y);
			Canvas->DrawRect(Loc, data->Extend);

			std::string *text = data->getText();
			Canvas->CDrawText(data->Location, text);
		}
	}
}