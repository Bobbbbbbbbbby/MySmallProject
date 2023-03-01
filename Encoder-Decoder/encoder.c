#include <stdio.h>
/*
 * u w x y z
 * p q r s t
 * k l m n o
 * f g h i j
 * a b c d e
 */

int main (int argc, char* argv[])
{
	char* arg = argv[1];
	char output[20];
	int j = 0;
	int i = 0;
	while(arg[i] != '\0')
	{
		char a = arg[i++];
		if(a >= 'v')
			a--;
		int target = a - 'a' + 1;
		int target1 = target % 5;
		int target2 = target / 5 + 1;

		output[j++] = target1 + '0';
		output[j++] = target2 + '0';
	}
    
	output[j] = '\0';
	printf("%s\n", output);
	return 0;
}