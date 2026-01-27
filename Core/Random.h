//Random.h
//Random stores the Random number generator that will be called in multiple programs
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <random>

class FRandom
{
public:
	std::mt19937 RandomGenerator;
	std::random_device rd;
};


