#ifndef __components_h__
#define __components_h__

typedef struct {
	int id;
	char surname[50];
	int processorQuant;
	char processorType[50];
	int memoryWeight;
	char controlerType[50];
	int videoMemoryWeight;
	char winchesterType[50];
	int winchesterQuant;
	int winchesterWeight;
	int integControlerQuant;
	int outerDevicesQuant;
	char OC[50];
} component;

#endif