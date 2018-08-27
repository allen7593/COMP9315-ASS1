#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int belong(int i, int* iset, int iset_len){  // belong(int, int_set, int_set_length)
	int x;
	for(x=0; x<iset_len; x++){
		if(i==iset[x]){
			return 1;  // int in int_set
		}
	}
	return 0;  // int not in int_set
}


int contain(int* isetA, int isetA_len, int* isetB, int isetB_len){ //isetB contains isetA = A @> B
	if(isetA_len > isetB_len){
		return 0;  //int_setB cannot contain int_setA
	}
	int ia,ib,count=0;
	for(ia=0; ia<isetA_len; ia++){
		for(ib=0; ib<isetB_len; ib++){
			if(isetA[ia]==isetB[ib]){
				count++;
				break;
			}
		}		
	}
	if(count==isetA_len){
		return 1;  //isetB contains isetA = A @> B
	}
	else{
		return 0;  //isetB cannot contain isetA
	}
}


int equal(int* isetA, int isetA_len, int* isetB, int isetB_len){  //int_setA = int_setB
	int ab, ba;
	ab =contain(isetA, isetA_len, isetB, isetB_len);
	ba =contain(isetB, isetB_len, isetA, isetA_len);
	if(ab == 1 && ba == 1){ 
		return 1;  //int_setA = int_setB
	}
	else{
		return 0;  //int_setA != int_setB
	}
}


int *intset_intersection(int* intarray_inj, int* isetA, int isetA_len, int* isetB, int isetB_len){  //A&&B
	int i,count=0;
	if(isetA_len < isetB_len){
		for(i=0; i< isetA_len; i++){
			if(belong(isetA[i], isetB, isetB_len)==1){
				intarray_inj[count]=isetA[i];
				count++;
			}
		}
		intarray_inj[isetA_len]=count;
	}
	else{
		for(i=0; i< isetB_len; i++){
			if(belong(isetB[i], isetA, isetA_len)==1){
				intarray_inj[count]=isetB[i];
				count++;
			}
		}
		intarray_inj[isetB_len]=count;
	}
	if(count == 0){
		return NULL;  // no itersection
	}
	else{
		return intarray_inj;
	}
	
}


int *intset_union(int* intarray_uni, int* isetA, int isetA_len, int* isetB, int isetB_len){  //A||B
	int i,count=0;
	if(isetA_len > isetB_len){
		memcpy(intarray_uni,isetA,sizeof(int)*isetA_len);
		for(i=0; i< isetB_len; i++){
			if(belong(isetB[i], intarray_uni, isetA_len+count)==0){
				intarray_uni[isetA_len+count]=isetB[i];
				count++;
			}
		}
		intarray_uni[isetA_len+isetB_len]=isetA_len+count;
	}
	else{
		memcpy(intarray_uni,isetB,sizeof(int)*isetB_len);
		for(i=0; i< isetA_len; i++){
			if(belong(isetA[i], intarray_uni, isetB_len+count)==0){
				intarray_uni[isetB_len+count]=isetA[i];
				count++;
			}
		}
		intarray_uni[isetA_len+isetB_len]=isetB_len+count;
	}
	return intarray_uni;

}


int *intset_disjunction(int* intarray_dis, int* isetA, int isetA_len, int* isetB, int isetB_len){  //A!!B
	int *intarray_inj, maxlen_inj;
	if(isetA_len<isetB_len){
		maxlen_inj = isetA_len+1;
	}
	else{
		maxlen_inj = isetB_len+1;
	}
	intarray_inj = malloc(maxlen_inj*sizeof(int));
	intset_intersection(intarray_inj, isetA, isetA_len, isetB, isetB_len);
	int len_inj=intarray_inj[maxlen_inj-1];

	int *intarray_uni, maxlen_uni =0;
	maxlen_uni = isetA_len + isetB_len+1;
	// printf("%d\n", maxlen_uni);
	intarray_uni = malloc(maxlen_uni*sizeof(int));
	intset_union(intarray_uni, isetA, isetA_len, isetB, isetB_len);
	int len_uni=intarray_uni[maxlen_uni-1];

	int i,j=0;
	for(i=0; i<len_uni; i++){
		if(belong(intarray_uni[i],intarray_inj,len_inj)==0){
			intarray_dis[j]=intarray_uni[i];
			j++;
		}
	}
	intarray_dis[isetA_len+isetB_len] = j;
	return intarray_dis;

}


int *intset_difference(int* intarray_dif, int* isetA, int isetA_len, int* isetB, int isetB_len){  //A-B
	int *intarray_inj, maxlen_inj;
	if(isetA_len<isetB_len){
		maxlen_inj = isetA_len+1;
	}
	else{
		maxlen_inj = isetB_len+1;
	}
	intarray_inj = malloc(maxlen_inj*sizeof(int));
	intset_intersection(intarray_inj, isetA, isetA_len, isetB, isetB_len);
	int len_inj=intarray_inj[maxlen_inj-1];

	int i,j=0;
	for(i=0; i<isetA_len; i++){
		if(belong(isetA[i],intarray_inj,len_inj)==0){
			intarray_dif[j]=isetA[i];
			j++;
		}
	}
	intarray_dif[isetA_len] = j;
	return intarray_dif;
}


int main(int argc, char** argv) // ./operation1-belong int int_set
{
	int test1[] = {12,22};
	int test2[] = {1,22,34};
	int i1=4;
	int i2=22;
	
	int iset_len1, iset_len2;
	iset_len1 = sizeof(test1)/sizeof(test1[0]);
	iset_len2 = sizeof(test2)/sizeof(test2[0]);
	// printf("len12: %d %d\n", iset_len1, iset_len2);

	//test belong function
	int result1, result2;
	result1 =belong(i1, test1, iset_len1);
	result2 =belong(i2, test2, iset_len2);
	// printf("%d %d\n", result1, result2);


	//test contain function
	int result3, result4;
	result3 =contain(test1, iset_len1, test2, iset_len2);
	result4 =contain(test2, iset_len2, test1, iset_len1);
	// printf("%d %d\n", result3, result4);


	//test equal function
	int result5;
	result5 = equal(test1, iset_len1, test2, iset_len2);
	// printf("%d\n", result5);


	//test intset_injection function
	int *intarray_inj, maxlen_inj;
	if(iset_len1<iset_len2){
		maxlen_inj = iset_len1+1; //intarray_inj[iset_len1] = intarray_inj[maxlen_inj-1] = intarray_length
	}
	else{
		maxlen_inj = iset_len2+1; //intarray_inj[iset_len2] = intarray_inj[maxlen_inj-1] = intarray_length
	}
	intarray_inj = malloc(maxlen_inj*sizeof(int));
	intset_intersection(intarray_inj,test1, iset_len1, test2, iset_len2); 
	printf("intarray_length: %d\n", intarray_inj[maxlen_inj-1]);
	int i;
	for (i = 0; i < intarray_inj[maxlen_inj-1]; i++)
	{
		printf("%d ", intarray_inj[i]);
	}
	printf("\n");


	//test intset_union function
	int *intarray_uni, maxlen_uni =0;
	maxlen_uni = iset_len1 + iset_len2+1; //intarray_inj[iset_len1+iset_len2] = intarray_inj[maxlen_inj-1] = intarray_length
	// printf("%d\n", maxlen_uni);
	intarray_uni = malloc(maxlen_uni*sizeof(int));
	intset_union(intarray_uni, test1, iset_len1, test2, iset_len2);
	printf("intarray_length: %d\n", intarray_uni[maxlen_uni-1]);
	for (i = 0; i < intarray_uni[maxlen_uni-1]; i++)
	{
		printf("%d ", intarray_uni[i]);
	}
	printf("\n");


	//test intset_disjunction function
	int *intarray_dis, maxlen_dis;
	maxlen_dis = iset_len1 + iset_len2+1;
	intarray_dis = malloc(maxlen_dis*sizeof(int));
	intset_disjunction(intarray_dis, test1, iset_len1, test2, iset_len2);
	printf("intarray_length: %d\n", intarray_dis[maxlen_dis-1]);
	for (i = 0; i < intarray_dis[maxlen_dis-1]; i++)
	{
		printf("%d ", intarray_dis[i]);
	}
	printf("\n");


	//test intset_difference function
	int *intarray_dif, maxlen_dif;
	maxlen_dif = iset_len1+1;
	intarray_dif = malloc(maxlen_dif*sizeof(int));
	intset_difference(intarray_dif, test1, iset_len1, test2, iset_len2);
	printf("intarray_length: %d\n", intarray_dif[maxlen_dif-1]);
	for (i = 0; i < intarray_dif[maxlen_dif-1]; i++)
	{
		printf("%d ", intarray_dif[i]);
	}
	printf("\n");


	free(intarray_inj);
	free(intarray_uni);
	free(intarray_dis);
	return 0;
}