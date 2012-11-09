#include <stdio.h>

int main(int argc, char **argv)
{
	// Se nessun file, usa stdin, stdout
	if(argc == 1)
	{
		char buf[1024];
		while(1)
		{
			//scanf("%s", buf);
			printf("%s", buf);
		}
		return 0;		
	}
	
	
	// Altrimenti leggiamo il file
	FILE *f;
	
	f = fopen(argv[1], "r");
	
	if(f == NULL)
	{
		printf("%s: %s: no such file or directory\n", argv[0], argv[1]);
		return 1;
	}
	

	return 0;
}
