#include "ocv_lookup.h"
#include <stddef.h>

const OCV_Table_t ocv_table[] = {}; // TODO: fill out OCV table

float ocv_lookup(float v) {
	if (v <= ocv_table[0].v) {
		return 0.0;
	}
	if (v >= ocv_table[TABLE_SIZE - 1].v) {
		return 1.0;
	}
	for (size_t i = 0; i < TABLE_SIZE - 1; ++i) {
		if (v < ocv_table[i + 1].v) {
			// linear interpolation
			float soc_1 = ocv_table[i].soc;
			float soc_2 = ocv_table[i + 1].soc;
			float v_1 = ocv_table[i].v;
			float v_2 = ocv_table[i + 1].v;
			float d_v = v - v_1;
			return soc_1 + d_v*((soc_2 - soc_1)/(v_2 - v_1));
		}
	}
	return 1.0;
}
