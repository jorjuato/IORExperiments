
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

main()
{
	float number;
	int num;
	char answ;
	srand(time(0));

	while(1)
	{
		if (!scanf("",&answ))
		{
			number = 100 * (float)( ( (float)rand())/(float) (RAND_MAX+1.0))  ;
			num = number;
			
			//number = rand();
			printf("el número flotante es : %f  \n", number);
			printf("el número entero es : %d  \n", (int)number);
		}

	}
}
