// c Maxim Urschumzew 2014

#include "stdafx.h"
#include "SDL.h"

#include "DEGraph.h"

using namespace IA::MeaningStream;
using namespace SO;

SDL_Modules_Init

//////////////////////////////////////////////////////////////////////
// init
DEGraph::DEGraph(IData* DataToDraw, Window_Base* newWindow, const fPoint &newLoc, const fPoint &newSize) : CCanvas(newWindow, newLoc, newSize)
{
	CurrentData = DataToDraw;
	AllDrawnObjects = std::deque<ExData*>();
}

//////////////////////////////////////////////////////////////////////
// draw
void DEGraph::Draw()
{
	Draw(4);
	CCanvas::Draw();
}

void DEGraph::Draw(int Depth)
{
#if cSO_DebugDE > 0
	std::cout << "[DE]: converting data...\n";
#endif

	ExData* Parent;
	AllDrawnObjects.clear();
	Parent = Convert(CurrentData, Depth);

#if cSO_DebugDE > 0
	std::cout << "[DE]: -- found " + std::to_string( AllDrawnObjects.size()) + " objects in depth of " + std::to_string(Depth) + '\n';
	std::cout << "[DE]: setting hierarchic bonds...\n";
#endif

	SetHierarchicBonds(Parent);

#if cSO_DebugDE > 0
	std::cout << "[DE]: -- parent has " + std::to_string(Parent->Children.size()) + " Children\n";
	std::cout << "[DE]: questing for longest horizontal data line\n";
#endif

	int MaxHor = LongestHorizontalDataLine(Parent);

#if cSO_DebugDE > 0
	std::cout << "[DE]: -- longest line is " << std::to_string(MaxHor) << " long\n";
	std::cout << "[DE]: setting object location...\n";
#endif

	SetObjectPosition(Parent, Depth);

#if cSO_DebugDE > 0
	std::cout << "[DE]: drawing points and connections...\n\n";
#endif

	Clear();
	DrawObjects();
	DrawConnections();

}

//////////////////////////////////////////////////////////////////////
// converting
/** creates DE_Objects for every connected data point of the passed data up to the passed depth*/
ExData* DEGraph::Convert(IData* myData, int Depth)
{
	return exe_Convert(myData, Depth, new std::deque<IData*>());
}
ExData* DEGraph::exe_Convert(IData* Current, int Depth, std::deque<IData*>* Ignore)
{
	if (Depth < 0)
		return nullptr;

	if (std::find(Ignore->begin(), Ignore->end(), Current) != Ignore->end())
		return nullptr;

	ExData* currentObj = new ExData(Current, &AllDrawnObjects);
	AllDrawnObjects.push_back(currentObj);
	

#if cSO_DebugDE > 1
	std::cout << "[DE]:  " + (checkM(MText) ? *currentObj->getText() : std::to_string(currentObj->CurrentSource->get())) + " in -depth of " + std::to_string(Depth) + '\n';
#endif

	Ignore->push_back(Current);
	Depth -= 1;

	for (int p_Next = 0; p_Next < Current->getConnectedNum(); p_Next++)
	{
		exe_Convert(Current->getConnected(p_Next), Depth, Ignore);
	}

	return currentObj;
}

/** First sets the distance of every DE_Objects to the master-parent,
then checks every object for the connected data with the lowest distance
and sets it as parent of the current one
*/
void DEGraph::SetHierarchicBonds(ExData* Current)
{
	//set distances
	exe_SetHierarchicDistances(Current, nullptr, 0);

	//set parents & children
	ExData* nearest;
	ExData* current;
	for (int p_Obj = 0; p_Obj < AllDrawnObjects.size(); p_Obj++)
	{
		current = AllDrawnObjects[p_Obj];


		std::deque<ExData*> connected = *current->getConnected();
		if (connected.size() == 0)
			continue;

		if (current->HierarchicDistance == 0)
		{
			current->Parent = NULL;
			continue;
		}

		nearest = connected[0];

		for (int p_Next = 0; p_Next < connected.size(); p_Next++)
		{
			if (connected[p_Next]->HierarchicDistance < nearest->HierarchicDistance)
				nearest = connected[p_Next];
		}

		current->Parent = nearest;
		nearest->Children.push_back(current);
	}
}

void DEGraph::exe_SetHierarchicDistances(ExData* Current, ExData* Caller, int Distance)
{
	std::deque<ExData*> connected = *Current->getConnected();
	if (Caller)
		connected.erase(std::find(connected.begin(), connected.end(), Caller));

	for (int p_Next = 0; p_Next < connected.size(); p_Next++)
	{
		if (connected[p_Next]->HierarchicDistance >= 0 && connected[p_Next]->HierarchicDistance + 1 <= Distance)
			return;
	}

	Current->HierarchicDistance = Distance;
	for (int p_Next = 0; p_Next < connected.size(); p_Next++)
	{
		exe_SetHierarchicDistances(connected[p_Next], Current, Distance + 1);
	}
}

/** returns the maximum amount of data in a horizontal line*/
int DEGraph::LongestHorizontalDataLine(ExData* Parent)
{
	return exe_LongestHorizontalDataLine(Parent);
}

int DEGraph::exe_LongestHorizontalDataLine(ExData* Current)
{
	std::deque<ExData*>* children;
	children = &Current->Children;

	if (children->size() == 0)
	{
		return 1;
	}
	else
	{
		int sum = 0;
		for (int p_Next = 0; p_Next < children->size(); p_Next++)
		{
			ExData* next = (*children)[p_Next];
			sum += exe_LongestHorizontalDataLine(next);
		}
		return sum;
	}
}

/** gets the amount of data in a passed line*/
int DEGraph::HorizontalDataLine(ExData* Parent, int Distance)
{
	return GetObjectsWithDistance(Distance)->size();
}

/** sets the location variables of objects to their wanted location*/
void DEGraph::SetObjectPosition(ExData* Parent, int Depth)
{
	fPoint Start(0,0);
	exe_SetObjectPosition(Parent, Parent, Depth, Start);

	for (int p_Obj = 0; p_Obj < AllDrawnObjects.size(); p_Obj++)
	{
		ExData* obj = AllDrawnObjects[p_Obj];
		if (obj->Extend.X == 0 && obj->Extend.Y == 0)
		{
			std::cout << "[DE]: WARNING: found " + std::to_string(int(*obj->CurrentSource))/*->Text*/ + " without extend\n";
			obj->Extend = fPoint(0.1, 0.1);
		}

	}
}

void DEGraph::exe_SetObjectPosition(ExData* Parent, ExData* Current, int TotalDepth, fPoint &CurrentLoc)
{
	float DeltaX, DeltaY;
	fPoint oldCurrentLoc = fPoint(CurrentLoc);
	fPoint myCurrentLoc = fPoint();

	//setting x
	if (Current->Children.size() == 0)
	{
		DeltaX = 1 / (1 + (float)HorizontalDataLine(Parent, Current->HierarchicDistance));
		CurrentLoc.X += DeltaX;
		myCurrentLoc = CurrentLoc;
	}
	else
	{
		//DE_Point^ myCurrentLoc = new fPoint(CurrentLoc);
		for (int p_Child = 0; p_Child < Current->Children.size(); p_Child++)
		{
			ExData* child = Current->Children[p_Child];
			exe_SetObjectPosition(Parent, child, TotalDepth, CurrentLoc);
		}

		float XOfChildren = CurrentLoc.X - oldCurrentLoc.X;
		DeltaX = Current->Children.size() > 1 ? (float)XOfChildren * 0.5 : (float)XOfChildren;
		myCurrentLoc.X = DeltaX + oldCurrentLoc.X;
	}
	//setting y
	DeltaY = 1 / (2 + (float)TotalDepth);
	myCurrentLoc.Y = DeltaY * (1 + Current->HierarchicDistance);

	//applying
	Current->Location = fPoint(myCurrentLoc);
	Current->Extend = fPoint(DeltaX * 0.8, DeltaY * 0.2);
}

/** gets all objects with a passed distance*/
std::deque<ExData*>* DEGraph::GetObjectsWithDistance(int Distance)
{
	std::deque<ExData*>* applying = new std::deque<ExData*>();
	for (int p_Obj = 0; p_Obj < AllDrawnObjects.size(); p_Obj++)
	{
		if (AllDrawnObjects[p_Obj]->HierarchicDistance == Distance)
			applying->push_back(AllDrawnObjects[p_Obj]);
	}
	return applying;
}

/** draws all objects*/
void DEGraph::DrawObjects()
{
	for (int p_Obj = 0; p_Obj < AllDrawnObjects.size(); p_Obj++)
	{
		ExData* current = AllDrawnObjects[p_Obj];
		fPoint Loc = fPoint(current->Location.X - 0.5* current->Extend.X, current->Location.Y);
		DrawRect(Loc, current->Extend);
		
		std::string *text = current->getText();
		CDrawText(current->Location, text);
	}
}
/** draws the connections between the objects*/
void DEGraph::DrawConnections()
{
	for (int p_Obj = 0; p_Obj < AllDrawnObjects.size(); p_Obj++)
	{
		ExData* current = AllDrawnObjects[p_Obj];
		/*for (int p_Child = 0; p_Child < current->Children.size(); p_Child++)
		{
		ExData* child = current->Children[p_Child];

		CurrentCanvas->DrawFloatArrow(new fPoint(current->Location->X, current->Location->Y + current->Extend->Y * 0.5), new fPoint(child->Location->X, child->Location->Y - child->Extend->Y * 0.5));
		}*/
		std::deque<ExData*>* Connected = current->getConnected(LinkType::Downlink);
		for (int p_Next = 0; p_Next < Connected->size(); p_Next++)
		{
			ExData* child = (*Connected)[p_Next];

			DrawLine(fPoint(current->Location.X/* + current->Extend.X * 0.5*/, current->Location.Y + current->Extend.Y), fPoint(child->Location.X/* + child->Extend.X * 0.5*/, child->Location.Y), fColor(0.7,0.7,0.7));
		}
	}
}
