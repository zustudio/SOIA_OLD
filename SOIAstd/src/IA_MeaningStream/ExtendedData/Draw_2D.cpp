
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
		for (ExData* data : *group->GetOccupants())
		{
			std::vector<float> extend = std::vector<float>();
			extend.push_back(1);
			extend.push_back(1);
			data->InterpProps.IntExtend = VectorND<float>(extend);
		}
	}
	for (ExGroup* group : *Groups)
	{
		ExData* data = group->GetBaseData();
		if (data)
			data->InterpProps.IntExtend = *group->GetExtend();

		std::cout << "[MS::Draw_2D]: Info: Found data '" + *data->getText() + "' with extend of " + (std::string)data->InterpProps.IntExtend << std::endl;
	}


	VectorND<float> start = VectorND<float>(2);
	exe_SetLocation((*Groups)[0], start);


	//---------------- find the max int demensions of locations ------------------

	VectorND<float> maxLoc = VectorND<float>(dim_Extend);
	
	for (ExGroup* group : *Groups)
	{
		for (ExData* data : *group->GetOccupants())
		{
			VectorND<float> loc = data->InterpProps.IntLocation;
			int n = loc.dim();
			for (int i = 0; i < n; i++)
			{
				maxLoc[i] = std::fmax(maxLoc[i], loc[i]);
			}
		}
	}
	std::vector<float> add = std::vector<float>();
	add.push_back(1);
	add.push_back(1);
	maxLoc += VectorND<float>(add);

	//----------------- rescale all int locs & extends into float ones ---------------
	for (ExGroup* group : *Groups)
	{
		for (ExData* data : *group->GetOccupants())
		{
			for (int i = 0; i < dim_Extend; i++)
			{
				data->InterpProps.FloatExtend[i] = (1 / maxLoc[i]) * data->InterpProps.IntExtend[i] * 0.5F;
				data->InterpProps.FloatLocation[i] = (1 / maxLoc[i]) * (data->InterpProps.IntLocation[i] + 0.5F);
			}
		}
	}

	//TEST
	//return;
	//ENDTEST

	//---- drawing the data ----
	Canvas->Clear();

	for (ExGroup* group : *Groups)
	{
		for (ExData* data : *group->GetOccupants())
		{
			fPoint center = Vector2D<float>(data->InterpProps.FloatLocation);
			fPoint extend = Vector2D<float>(data->InterpProps.FloatExtend);
			fPoint Loc = fPoint(center.X - 0.5* extend.X, center.Y - 0.5*extend.Y);
			Canvas->DrawRect(Loc, extend);

			std::string *text = data->getText();
			Canvas->CDrawText(Loc, text);
		}
	}
}

void Draw_2D::exe_SetLocation(ExGroup* Group, VectorND<float> &IntLocation)
{
	// so that my location is not recursively changed
	VectorND<float> backupLoc = IntLocation;

	// first a recursive call to all child groups
	std::deque<ExGroup*> childGroups = *Group->GetChildGroups();
	for (ExGroup* childGroup : childGroups)
	{
		exe_SetLocation(childGroup, backupLoc);
	}

	// reset my location
	IntLocation = backupLoc;

	// setting the location of all current data occupants
	std::deque<ExData*> occupants = *Group->GetOccupants();
	for (ExData* occupant : occupants)
	{
		VectorND<float>* loc = Group->GetLocation(occupant);
		//IntLocation += *loc;
		occupant->InterpProps.IntLocation = *loc + IntLocation;
		std::cout << "[MS::Draw_2D]: Info: Set Location of '" + *occupant->getText() + "' to " + (std::string)occupant->InterpProps.IntLocation << std::endl;
		delete loc;
	}
	IntLocation = *Group->GetBaseLocation();
}
