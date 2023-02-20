#include <stdio.h>
#include <string.h>

#include "components.h"

void Usage()
{
	printf("Usage: program filename\n");  
}

void writeComponent(component *comp)
{
	printf("%d\t%s\t%d\t%s\t%d\t%s\t%d\t%s\t%d\t%d\t%d\t%d\t%s\n", comp->id, comp->surname, \
	comp->processorQuant, comp->processorType, comp->memoryWeight, comp->controlerType, \
	comp->videoMemoryWeight, comp->winchesterType, comp->winchesterQuant,\
	comp->winchesterWeight, comp->integControlerQuant, comp->outerDevicesQuant, comp->OC);
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		Usage();
		return 1;
	}
	component comp;
	FILE *in = fopen(argv[1], "rb");
	if(!in)
	{
		perror("Can't open the file");
		return 2;
	}
	while(fread(&comp, sizeof(comp), 1, in)==1)
	{
		writeComponent(&comp);
	}
	return 0;
}

