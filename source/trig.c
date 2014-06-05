#include "trig.h"

//Generated with: 
//    for (double i = -1; i <= 1; i+=0.01){ printf("%1.0f, ", acos(i) * (180 / M_PI)); }
// (add a 0 at the end)
static uint8_t lookup_acos[201] = {
	180, 172, 169, 166, 164, 162, 160, 158, 157, 156, 154, 153, 152, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 139, 138, 137, 136, 135, 134, 134, 133, 132, 131, 131, 130, 129, 128, 128, 127, 126, 125, 125, 124, 123, 123, 122, 121, 121, 120, 119, 119, 118, 117, 117, 116, 115, 115, 114, 114, 113, 112, 112, 111, 110, 110, 109, 109, 108, 107, 107, 106, 106, 105, 104, 104, 103, 103, 102, 102, 101, 100, 100, 99, 99, 98, 97, 97, 96, 96, 95, 95, 94, 93, 93, 92, 92, 91, 91, 90, 89, 89, 88, 88, 87, 87, 86, 85, 85, 84, 84, 83, 83, 82, 81, 81, 80, 80, 79, 78, 78, 77, 77, 76, 76, 75, 74, 74, 73, 73, 72, 71, 71, 70, 70, 69, 68, 68, 67, 66, 66, 65, 65, 64, 63, 63, 62, 61, 61, 60, 59, 59, 58, 57, 57, 56, 55, 55, 54, 53, 52, 52, 51, 50, 49, 49, 48, 47, 46, 46, 45, 44, 43, 42, 41, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 28, 27, 26, 24, 23, 22, 20, 18, 16, 14, 11, 8, 0
};

//Generated with:
//    for (uint8_t i = 0; i <= 90; i++){ printf("%1.5f, ", cos(i * M_PI / 180)); }
static double lookup_cos[91] = {
	1.00000, 0.99985, 0.99939, 0.99863, 0.99756, 0.99619, 0.99452, 0.99255, 0.99027, 0.98769, 0.98481, 0.98163, 0.97815, 0.97437, 0.97030, 0.96593, 0.96126, 0.95630, 0.95106, 0.94552, 0.93969, 0.93358, 0.92718, 0.92050, 0.91355, 0.90631, 0.89879, 0.89101, 0.88295, 0.87462, 0.86603, 0.85717, 0.84805, 0.83867, 0.82904, 0.81915, 0.80902, 0.79864, 0.78801, 0.77715, 0.76604, 0.75471, 0.74314, 0.73135, 0.71934, 0.70711, 0.69466, 0.68200, 0.66913, 0.65606, 0.64279, 0.62932, 0.61566, 0.60182, 0.58779, 0.57358, 0.55919, 0.54464, 0.52992, 0.51504, 0.50000, 0.48481, 0.46947, 0.45399, 0.43837, 0.42262, 0.40674, 0.39073, 0.37461, 0.35837, 0.34202, 0.32557, 0.30902, 0.29237, 0.27564, 0.25882, 0.24192, 0.22495, 0.20791, 0.19081, 0.17365, 0.15643, 0.13917, 0.12187, 0.10453, 0.08716, 0.06976, 0.05234, 0.03490, 0.01745, 0.00000
};

//Generated with:
//    for (uint8_t i = 0; i <= 90; i++){ printf("%1.5f, ", sin(i * M_PI / 180)); }
static double lookup_sin[91] = {
	0.00000, 0.01745, 0.03490, 0.05234, 0.06976, 0.08716, 0.10453, 0.12187, 0.13917, 0.15643, 0.17365, 0.19081, 0.20791, 0.22495, 0.24192, 0.25882, 0.27564, 0.29237, 0.30902, 0.32557, 0.34202, 0.35837, 0.37461, 0.39073, 0.40674, 0.42262, 0.43837, 0.45399, 0.46947, 0.48481, 0.50000, 0.51504, 0.52992, 0.54464, 0.55919, 0.57358, 0.58779, 0.60182, 0.61566, 0.62932, 0.64279, 0.65606, 0.66913, 0.68200, 0.69466, 0.70711, 0.71934, 0.73135, 0.74314, 0.75471, 0.76604, 0.77715, 0.78801, 0.79864, 0.80902, 0.81915, 0.82904, 0.83867, 0.84805, 0.85717, 0.86603, 0.87462, 0.88295, 0.89101, 0.89879, 0.90631, 0.91355, 0.92050, 0.92718, 0.93358, 0.93969, 0.94552, 0.95106, 0.95630, 0.96126, 0.96593, 0.97030, 0.97437, 0.97815, 0.98163, 0.98481, 0.98769, 0.99027, 0.99255, 0.99452, 0.99619, 0.99756, 0.99863, 0.99939, 0.99985, 1.00000
};

uint8_t constrain_angle(int16_t angle, uint8_t *quadrant){
	//Get the angle into 0..360 degrees
	while (angle < 0){
		angle += 360;
	}
	while (angle >= 360){
		angle -= 360;
	}
	
	if (angle <= 90) {
		*quadrant = 1;
	}
	else if (angle <= 180){
		*quadrant = 2;
		angle = 180 - angle;
	}
	else if (angle <= 270){
		*quadrant = 3;
		angle = angle - 180;
	}
	else {
		*quadrant = 4;
		angle = 360 - angle;
	}

	return angle;
}

uint8_t acos_d(double value){
	if (value < -1 || value > 1) return 255;	//NaN, out of domain
	return lookup_acos[(uint8_t) ((value * 100) + 100)];
}

double cos_d(int16_t angle){
	uint8_t quadrant = 0;
	angle = constrain_angle(angle, &quadrant);
	return lookup_cos[angle] * (quadrant == 2 || quadrant == 3 ? -1 : 1);
}

double sin_d(int16_t angle){
	uint8_t quadrant = 0;
	angle = constrain_angle(angle, &quadrant);
	return lookup_sin[angle] * (quadrant >= 3 ? -1 : 1);
}
/*
int main() {
	for (double i = -1; i <= 1.001; i+=0.001){
		printf("%1.3f, %d, %3.0f, %d\n", i, (uint8_t) ((i * 100) + 100), acos(i) * (180 / M_PI), acos_d(i));
	}
	printf("%1.3f, %d, %3.0f, %d\n", 1.0, (uint8_t) ((1.0 * 100) + 100), acos(1.0) * (180 / M_PI), acos_d(1.0));
}
*/