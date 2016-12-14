// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class THOR_API ThorMath
{
public:
	ThorMath();
	~ThorMath();

	/* Seed the random number generator using nano seconds. Uses chrono library */
	static void SeedRandom();

	/* Generate a random number within a specified range */
	static float RandomRange(float min, float max);
};
