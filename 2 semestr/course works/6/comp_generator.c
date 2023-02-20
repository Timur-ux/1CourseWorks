#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "components.h"

void Usage()
{
	printf("Usage: program filename, components quantity\n");  
}
const char names[10][50] = {"Timur", "Valera", "Masha", "Misha", "Anna", "Tanya", "Greror", "Max", "Vitaliy", "Vika"};
const char procType[3][50] = {"Intel", "AMD", "Pentium"};
const char contrType[3][50] = {"Keyboard", "Touchpad", "VoiceControler"};
const char winchType[2][10] = {"SSD", "HDD"};
const char OC[4][15] = {"Windows", "MacOC", "Linux/Ubuntu", "MS/DOS"};

void generateComponent(component *comp, int id)
{
	comp->id = id;
	strcpy(comp->surname, names[rand()%10]);
	comp->processorQuant = 1+rand()%3;
	strcpy(comp->processorType, procType[rand()%3]);
	comp->memoryWeight = 1+rand()%1024;
	strcpy(comp->controlerType, contrType[rand()%3]);
	comp->videoMemoryWeight = 1+rand()%512;
	strcpy(comp->winchesterType, winchType[rand()%2]);
	comp->winchesterQuant = 1+rand()%4;
	comp->winchesterWeight = 1+rand()%1024;
	comp->integControlerQuant = 1+rand()%3;
	comp->outerDevicesQuant = 1+rand()%3;
	strcpy(comp->OC, OC[rand()%4]);
}

int main(int argc, char * argv[])
{
	if(argc != 3)
	{
		Usage();
		return 1;
	}
	component comp;
	FILE *out = fopen(argv[1], "wb");
	int n = atoi(argv[2]);
	if(!out)
	{
		perror("Can't open the file");
		return 2;
	}
	srand(n);
	for(int i = 0; i < n; i++)
	{
		generateComponent(&comp, i+1);
		fwrite(&comp, sizeof(comp), 1, out);
	}
	return 0;
}

