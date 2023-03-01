#include <stdio.h>

/*
 * u w x y z
 * p q r s t
 * k l m n o
 * f g h i j
 * a b c d e
 */

int main(int argc, char** argv)
{
	char* a  = argv[1];
	int i = 0;
	int j = 0;
	char output[20];

	while(1)
	{
		int target1 = a[j++];
		int target2 = a[j++];

		if(target1 == '\0' || target2 == '\0')
			break;

		target1 -= '0';
		target2 -= '0';

		int target = (target1 - 1) + 5 * (target2 - 1);
		output[i++] = (char) (target + 'a');

		if(output[i - 1] >= 'v')
			output[i - 1] += 1;
	}
	
	output[i] = '\0';
	printf("%s\n", output);
	return 0;
}