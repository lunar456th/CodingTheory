#include "utility.h"

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		perror("argument error");
		goto exit;
	}

	if(!strcmp(argv[1], "e"))
	{
		e(atoi(argv[2]), argv[3], argv[4]);
	}
	else if(!strcmp(argv[1], "d"))
	{
		d(atoi(argv[2]), argv[3], argv[4]);
	}
	else
	{
		perror("invalid parameter");
		goto exit;
	}

exit:
	return 0;
}
