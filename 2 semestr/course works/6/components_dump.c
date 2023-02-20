#include <stdio.h>
#include <string.h>

#include "components.h"

void Usage()
{
	printf("Usage: program filename\n");  
}

int readComponent(component *comp)
{
	return scanf("%s %d %s %d %s %d %s %d %d %d %d %s\n", &comp->surname, \
	&comp->processorQuant, &comp->processorType, &comp->memoryWeight, &comp->controlerType, \
	&comp->videoMemoryWeight, &comp->winchesterType, &comp->winchesterQuant,\
	&comp->winchesterWeight, &comp->integControlerQuant, &comp->outerDevicesQuant, &comp->OC) == 12;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		Usage();
		return 1;
	}
	component comp;
	FILE *out = fopen(argv[1], "w");
	if(!out)
	{
		perror("Can't open the file");
		return 2;
	}
	int id = 1;
	while(readComponent(&comp))
	{
		comp.id = id;
		fwrite(&comp, sizeof(comp), 1, out);
		id++;
	}
	return 0;
}

