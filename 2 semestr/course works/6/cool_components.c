#include <stdio.h>
#include <stdlib.h>

#include "components.h"

void Usage()
{
	printf("Usage: program filename, p\n");
}

/*
Чекаем всех студентиков, имена тех, у кого 2 процессора и внешних устройств <= p - выводим в ст. вывод
параметр p берем из параметров вызова, он должен идти после имени файла с данными студентиков
*/

int main(int argc, char * argv[])
{
	if(argc != 3)
	{
		Usage();
		return 1;
	}
	FILE * in = fopen(argv[1], "rb");
	if(!in)
	{
		perror("Can't open file");
		return 2;
	}

	int p = atoi(argv[2]);
	component comp;
	while(fread(&comp, sizeof(comp), 1, in) == 1)
	{
		if(comp.processorQuant == 2 && comp.outerDevicesQuant <= p)
		{
			printf("%d\t%s\n", comp.id, comp.surname);
		}
	}
	return 0;
}
