#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int belong(int i, int* iset, int iset_len){  // belong(int, int_set, int_set_length)
	int x;
	if(iset_len==0){
		return 0;  // iset is void set
	}
	for(x=0; x<iset_len; x++){
		if(i==iset[x]){
			return 1;  // int in int_set
		}
	}
	return 0;  // int not in int_set
}


int contain(int* isetA, int isetA_len, int* isetB, int isetB_len){ //isetB contains isetA = A @> B
	if(isetA_len==0){
		if (isetB_len==0){
			return 0;  //void set cannot contain void set
		}
		return 1;  //any set contains void set
	}
	if(isetA_len > isetB_len){
		return 0;  //int_setB cannot contain int_setA
	}
	int ia;
	for(ia=0; ia<isetA_len; ia++){
		if(belong(isetA[ia],isetB,isetB_len)!=1){
			return 0;  //isetB cannot contain int_setA
		}		
	}
	return 1; //isetB contains isetA = A @> B
}


int equal(int* isetA, int isetA_len, int* isetB, int isetB_len){  //int_setA = int_setB
	int ab, ba;
	ab =contain(isetA, isetA_len, isetB, isetB_len);
	ba =contain(isetB, isetB_len, isetA, isetA_len);
	if(ab == 1 && ba == 1){ 
		return 1;  //int_setA = int_setB
	}
	return 0;  //int_setA != int_setB
}


int *intset_intersection(int* isetA, int isetA_len, int* isetB, int isetB_len, int *inj_len){  //A&&B
	if(isetA_len==0||isetB_len==0){
		*inj_len =0;
		return NULL;  //void set intersection with any set
	}
	int *intarray_inj=NULL, *tmp_inj=NULL, *maxarr=NULL, *minarr=NULL;
	int maxlen, minlen, i, count=0;
	if(isetA_len < isetB_len){
		minarr=isetA;
		maxarr=isetB;
		minlen=isetA_len;
		maxlen=isetB_len;
	}
	else{
		minarr=isetB;
		maxarr=isetA;
		minlen=isetB_len;
		maxlen=isetA_len;
	}
	for(i=0; i< minlen; i++){
		if(belong(minarr[i], maxarr, maxlen)==1){
			count++;
			if(count==1){
				tmp_inj=malloc(sizeof(int));
			}
			else{
				tmp_inj=realloc(tmp_inj, count*sizeof(int));
			}
			intarray_inj = tmp_inj;
			intarray_inj[count-1]=minarr[i];
		}
	}

	*inj_len = count;
	return intarray_inj;
	
}


int *intset_union(int* isetA, int isetA_len, int* isetB, int isetB_len, int *uni_len){  //A||B
	if(isetA_len==0){
		if (isetB_len==0){
			*uni_len=0;
			return NULL;  //void set union void set
		}
		*uni_len = isetB_len;
		return isetB;  //void set union isetB
	}
	if(isetB_len==0){
		*uni_len = isetA_len;
		return isetA;  //isetA union void set
	}

	int *intarray_uni=NULL, *tmp_uni=NULL, *maxarr=NULL, *minarr=NULL;
	int maxlen, minlen, i, count=0;
	if(isetA_len < isetB_len){
		if (contain(isetA, isetA_len, isetB, isetB_len)==1){
			*uni_len = isetB_len;
			return isetB;   // isetB contains isetA
		}
		minarr=isetA;
		maxarr=isetB;
		minlen=isetA_len;
		maxlen=isetB_len;
	}
	else{
		if (contain(isetB, isetB_len, isetA, isetA_len)==1){
			*uni_len = isetA_len;
			return isetA;   // isetA contains isetB
		}
		minarr=isetB;
		maxarr=isetA;
		minlen=isetB_len;
		maxlen=isetA_len;
	}

	tmp_uni=malloc(sizeof(int)*maxlen);
	intarray_uni = tmp_uni;
	memcpy(intarray_uni,maxarr,sizeof(int)*maxlen);
	
	for(i=0; i< minlen; i++){
		if(belong(minarr[i], intarray_uni, maxlen+count)==0){
			count++;
			tmp_uni=realloc(tmp_uni, (maxlen+count)*sizeof(int));
			intarray_uni = tmp_uni;
			intarray_uni[maxlen+count-1]=minarr[i];
		}
	}
	*uni_len=maxlen+count;	
	return intarray_uni;

}


int *intset_difference(int* isetA, int isetA_len, int* isetB, int isetB_len, int *dif_len){  //A-B
	if(isetA_len==0){  //void set
		*dif_len=0;
		return NULL;
	}

	int *intarray_inj, inj_len;
	intarray_inj=intset_intersection(isetA, isetA_len, isetB, isetB_len, &inj_len); 
	if (inj_len==0)
	{
		*dif_len=isetA_len;
		return isetA;  //no intersection
	}

	int i, count=0, *intarray_dif=NULL, *tmp_dif=NULL;
	for(i=0; i< isetA_len; i++){
		if(belong(isetA[i], intarray_inj, inj_len)==0){
			count++;
			if(count==1){
				tmp_dif=malloc(sizeof(int));
			}
			else{
				tmp_dif=realloc(tmp_dif, count*sizeof(int));
			}
			intarray_dif = tmp_dif;
			intarray_dif[count-1]=isetA[i];
		}
	}

	*dif_len = count;
	return intarray_dif;
}


int *intset_disjunction(int* isetA, int isetA_len, int* isetB, int isetB_len, int *dis_len){  //A!!B
	int *intarray_dis=NULL, count, *ab, ablen, *ba, balen;
	ab=intset_difference(isetA, isetA_len, isetB, isetB_len, &ablen);
	ba=intset_difference(isetB, isetB_len, isetA, isetA_len, &balen);
	intarray_dis=intset_union(ab,ablen,ba,balen,&count);
	*dis_len=count;
	return intarray_dis;

}


int main(int argc, char** argv) // ./operation1-belong int int_set
{
	int test1[] = {1,22};    //{1,22,34}; //{11,5}; //{11,5,1};
	int test2[] = {1,22,34};
	int i1=4;
	int i2=22;
	
	int iset_len1, iset_len2;
	iset_len1 = sizeof(test1)/sizeof(test1[0]);//0
	iset_len2 = sizeof(test2)/sizeof(test2[0]);//0
	// printf("len12: %d %d\n", iset_len1, iset_len2);

	//test belong function
	int result1, result2;
	result1 =belong(i1, test1, iset_len1);
	result2 =belong(i2, test2, iset_len2);
	printf("%d %d\n", result1, result2);


	//test contain function
	int result3, result4;
	result3 =contain(test1, iset_len1, test2, iset_len2);
	result4 =contain(test2, iset_len2, test1, iset_len1);
	printf("%d %d\n", result3, result4);


	//test equal function
	int result5;
	result5 = equal(test1, iset_len1, test2, iset_len2);
	printf("%d\n", result5);


	//test intset_injection function
	int *intarray_inj, inj_len;
	intarray_inj=intset_intersection(test1, iset_len1, test2, iset_len2, &inj_len); 
	printf("intarray_length: %d\n", inj_len);
	int i;
	for (i = 0; i < inj_len; i++)
	{
		printf("%d ", *(intarray_inj+i));
	}
	printf("\n");


	//test intset_union function
	int *intarray_uni, uni_len =0;
	intarray_uni=intset_union(test1, iset_len1, test2, iset_len2, &uni_len);
	printf("intarray_length: %d\n", uni_len);
	for (i = 0; i < uni_len; i++)
	{
		printf("%d ", *(intarray_uni+i));
	}
	printf("\n");


	//test intset_disjunction function
	int *intarray_dis, dis_len;
	intarray_dis = intset_disjunction(test1, iset_len1, test2, iset_len2, &dis_len);
	printf("intarray_length: %d\n", dis_len);
	for (i = 0; i < dis_len; i++)
	{
		printf("%d ", *(intarray_dis+i));
	}
	printf("\n");


	//test intset_difference function
	int *intarray_dif, dif_len;
	intarray_dif = intset_difference(test1, iset_len1, test2, iset_len2, &dif_len);
	printf("intarray_length: %d\n", dif_len);
	for (i = 0; i < dif_len; i++)
	{
		printf("%d ", *(intarray_dif+i));
	}
	printf("\n");


	return 0;
}