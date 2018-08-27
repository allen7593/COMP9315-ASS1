#include <stdio.h>


int belong(int i, int* iset, int iset_len){  // belong(int, int_set, int_set_length)
	int x;
	for(x=0; x<iset_len; x++){
		if(i==iset[x]){
			return 1;  // int in int_set
		}
	}
	return 0;  // int not in int_set
}



int main(int argc, char** argv) // ./operation1-belong int int_set
{
	int test1[] = {1,2,34};
	int test2[] = {22};
	int i1=4;
	int i2=22;
	
	int iset_len1, iset_len2;
	iset_len1 = sizeof(test1)/sizeof(test1[0]);
	iset_len2 = sizeof(test2)/sizeof(test2[0]);

	int result1, result2;
	result1 =belong(i1, test1, iset_len1);
	result2 =belong(i2, test2, iset_len2);
	printf("%d %d\n", result1, result2);
	
	return 0;
}