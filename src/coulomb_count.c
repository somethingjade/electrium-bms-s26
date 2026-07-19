#include "coulomb_count.h"
#include "sensors/current/current.h"

float CoulombCount_SOC(float prev, float capacity) {
	float current = ReadCurrent();
	return prev + (current/capacity)*TIME_STEP;
}
