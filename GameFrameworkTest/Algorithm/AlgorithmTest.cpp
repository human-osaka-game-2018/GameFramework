#include "pch.h"

#include "Algorithm.h"

using namespace gameframework;

TEST(AlgorithmTest, SwitchMinBetweenMax) {
	// Arrange
	int cycleVal = 5;
	float switchingMin = 0.5f;
	float switchingMax = 2.0f;
	std::vector<float> retVals;

	// Act
	for (int val = 0; val <= cycleVal; ++val) {
		float ret = algorithm::SwitchMinBetweenMax(val, cycleVal, switchingMin, switchingMax);
		retVals.push_back(ret);
	}

	// Assert
	EXPECT_FLOAT_EQ(switchingMin, retVals[0]);
	EXPECT_FLOAT_EQ(switchingMax, retVals[5]);
}
