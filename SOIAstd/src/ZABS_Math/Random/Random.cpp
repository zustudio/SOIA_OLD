
#include <random>

#include "Random.h"
#include <iostream>
#include <string>

using namespace ZABS::Math;

//////////////////////////////////////////////////////
// static
//  rand
int Random::InfluencedRand(std::vector<float> &Chances)
{
	//one time:
	auto static const seed = std::random_device()();
	static std::mt19937 random_engine(seed);
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	//always:
	float sum;
	std::vector<float> relativeChances = std::vector<float>();
	std::vector<float> chanceDestribution = std::vector<float>();
	float randomFloat;
	int chosenInt;

	//add elements to arrays
	for (int i = 0; i < Chances.size(); i++)
	{
		relativeChances.push_back(0);
		chanceDestribution.push_back(0);
	}
	////move negative chances up into positive ones
	float smallestChance = 0;
	for (int i = 0; i < Chances.size(); i++)
	{
		smallestChance = smallestChance <= Chances[i] ? smallestChance : Chances[i];
	}
	for (int i = 0; i < Chances.size(); i++)
	{
		Chances[i] -= smallestChance;
	}

	//set minimal chance
	for (int i = 0; i < Chances.size(); i++)
	{
		if (Chances[i] < 1)
			Chances[i] = 1;
	}

	//calculate chance destribution
	//sum up all elements of chances
	for (int i = 0; i < Chances.size(); i++)
	{
		sum += Chances[i];
	}
	//divide by sum
	for (int i = 0; i < Chances.size(); i++)
	{
		relativeChances[i] = Chances[i] / sum;
	}
	//add previous chances to current element
	for (int i = 0; i < Chances.size(); i++)
	{
		chanceDestribution[i] += relativeChances[i] + (i > 0 ? chanceDestribution[i - 1] : 0);
	}

	//get a random float
	randomFloat = distribution(random_engine);

	//calculate which possibility was chosen
	for (int i = Chances.size() - 1; i >= 0; i--)
	{
		if (randomFloat <= chanceDestribution[i])
			chosenInt = i;
	}
	return chosenInt;
}
