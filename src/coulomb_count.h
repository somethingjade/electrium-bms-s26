#define TIME_STEP 1 // TODO: figure out the actual delta t

inline float CoulombCount_SOC(float prev, float current, float capacity, float time_step) {
	return prev + (current/capacity)*time_step;
}
