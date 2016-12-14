// Fill out your copyright notice in the Description page of Project Settings.

#include "Thor.h"
#include "ThorMath.h"
#include <stdlib.h>  /* srand, rand */
#include <time.h>    /* time */
#include <chrono>

ThorMath::ThorMath()
{
}

ThorMath::~ThorMath()
{
}

/* Seed the random number generator using nano seconds. Uses chrono library */
void ThorMath::SeedRandom()
{
	using namespace std::chrono;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	unsigned long time =
		std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
	srand(time);
}

/* Generate a random number within a specified range */
float ThorMath::RandomRange(float min, float max)
{
	SeedRandom();
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

