//
// Sarvar Khasanov
//

#ifndef SALUTAPP_USER_MATH_H_
#define SALUTAPP_USER_MATH_H_

#include <windows.h>

inline int getRandomInt(int range_min, int range_max) {
	return (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
}

inline float getRandomFloat() {
	return (float) rand() / RAND_MAX;
}

inline float getRandomFloat(float range_min, float range_max) {
	return (float) rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
}

#endif