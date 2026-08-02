#define IDLE_CURRENT_THRESHOLD_C_RATE 0.02
#define THRESHOLD_MS 1000

inline float get_threhsold(float capacity) {
	return IDLE_CURRENT_THRESHOLD_C_RATE*capacity;
}

void vSOCTask(void* pvParameters);
