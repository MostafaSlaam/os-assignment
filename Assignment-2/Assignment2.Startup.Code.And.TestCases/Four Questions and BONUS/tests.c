#include <kern/tests.h>

//define the white-space symbols
#define WHITESPACE "\t\r\n "

void TestAssignment2()
{
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q1:\n");
	cprintf("========================\n");
	TestAss2Q1();
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q2:\n");
	cprintf("========================\n");
	TestAss2Q2();
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q3:\n");
	cprintf("========================\n");
	TestAss2Q3();
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q4:\n");
	cprintf("========================\n");
	TestAss2Q4();
	cprintf("\n===========================\n");
	cprintf("Automatic Testing of BONUS:\n");
	cprintf("===========================\n");
	TestAss2BONUS();
}

int TestAss2Q1()
{
	int retValue = 1;
	int i = 0;
	//Create first array
	char cr1[100] = "cnia _x1 3";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cr1, WHITESPACE, args, &numOfArgs) ;

	int* ptr1 = CreateIntArray(args) ;
	assert(ptr1 >= (int*)0xF1000000);

	//Check elements of 1st array
	for (i=0 ; i<3; i++)
	{
		if (ptr1[i] != 0)
		{
			cprintf("[EVAL] #1 CreateIntArray: Failed\n");
			return retValue;
		}
	}

	//Create second array
	char cr2[100] = "cnia _y1 4";
	numOfArgs = 0;
	strsplit(cr2, WHITESPACE, args, &numOfArgs) ;

	int* ptr2 = CreateIntArray(args) ;
	assert(ptr2 >= (int*)0xF1000000);

	//Check elements of 2nd array
	for (i=0 ; i<4; i++)
	{
		if (ptr2[i] != 0)
		{
			cprintf("[EVAL] #2 CreateIntArray: Failed\n");
			return retValue;
		}
	}
	//Check elements of 1st array
	for (i=0 ; i<3; i++)
	{
		if (ptr1[i] != 0)
		{
			cprintf("[EVAL] #3 CreateIntArray: Failed\n");
			return retValue;
		}
	}

	//Create third array
	char cr3[100] = "cnia _z1 1";
	numOfArgs = 0;
	strsplit(cr3, WHITESPACE, args, &numOfArgs) ;

	int* ptr3 = CreateIntArray(args) ;
	assert(ptr3 >= (int*)0xF1000000);

	//Check elements of 3rd array
	for (i=0 ; i<1; i++)
	{
		if (ptr3[i] != 0)
		{
			cprintf("[EVAL] #4 CreateIntArray: Failed\n");
			return retValue;
		}
	}
	//Check elements of 2nd array
	for (i=0 ; i<4; i++)
	{
		if (ptr2[i] != 0)
		{
			cprintf("[EVAL] #5 CreateIntArray: Failed\n");
			return retValue;
		}
	}
	//Check elements of 1st array
	for (i=0 ; i<3; i++)
	{
		if (ptr1[i] != 0)
		{
			cprintf("[EVAL] #6 CreateIntArray: Failed\n");
			return retValue;
		}
	}

	cprintf("[EVAL] CreateIntArray: Succeeded\n");

	return retValue;
}

int TestAss2Q2()
{
	int retValue = 1;
	int i = 0;
	//Create first array
	char cr1[100] = "cnia _x 3";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cr1, WHITESPACE, args, &numOfArgs) ;

	int* ptr1 = CreateIntArray(args) ;
	assert(ptr1 >= (int*)0xF1000000);


	//Create second array
	char cr2[100] = "cnia _myArr 14";
	numOfArgs = 0;
	strsplit(cr2, WHITESPACE, args, &numOfArgs) ;

	int* ptr2 = CreateIntArray(args) ;
	assert(ptr2 >= (int*)0xF1000000);

	//Create third array
	char cr3[100] = "cnia _zeros 10";
	numOfArgs = 0;
	strsplit(cr3, WHITESPACE, args, &numOfArgs) ;

	int* ptr3 = CreateIntArray(args) ;
	assert(ptr3 >= (int*)0xF1000000);

	//Get size of 1st array
	int size = 0;
	char cr4[100] = "gas _x";
	numOfArgs = 0;
	strsplit(cr4, WHITESPACE, args, &numOfArgs) ;

	size = GetArraySize(args) ;
	if (size != 3)
	{
		cprintf("[EVAL] #1 GetArraySize: Failed\n");
		return 1;
	}

	//Get size of 2nd array
	char cr5[100] = "gas _myArr";
	numOfArgs = 0;
	strsplit(cr5, WHITESPACE, args, &numOfArgs) ;

	size = GetArraySize(args) ;
	if (size != 14)
	{
		cprintf("[EVAL] #2 GetArraySize: Failed\n");
		return 1;
	}

	//Get size of non-existing array
	char cr6[100] = "gas _zero";
	numOfArgs = 0;
	strsplit(cr6, WHITESPACE, args, &numOfArgs) ;

	size = GetArraySize(args) ;
	if (size != -1)
	{
		cprintf("[EVAL] #3 GetArraySize: Failed\n");
		return 1;
	}

	//Get size of 3rd array
	char cr7[100] = "gas _zeros";
	numOfArgs = 0;
	strsplit(cr7, WHITESPACE, args, &numOfArgs) ;

	size = GetArraySize(args) ;
	if (size != 10)
	{
		cprintf("[EVAL] #4 GetArraySize: Failed\n");
		return 1;
	}

	cprintf("[EVAL] GetArraySize: Succeeded\n");

	return retValue;

}

int TestAss2Q3()
{
	int retValue = 1;
	int i = 0;
	//Create first array
	char cr1[100] = "cnia _x3 3";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cr1, WHITESPACE, args, &numOfArgs) ;

	int* ptr1 = CreateIntArray(args) ;
	assert(ptr1 >= (int*)0xF1000000);


	//Create second array
	char cr2[100] = "cnia _myArr3 4";
	numOfArgs = 0;
	strsplit(cr2, WHITESPACE, args, &numOfArgs) ;

	int* ptr2 = CreateIntArray(args) ;
	assert(ptr2 >= (int*)0xF1000000);

	//Set (Exist)
	char f1[100] = "sea _x3 2 300";
	strsplit(f1, WHITESPACE, args, &numOfArgs) ;
	int ret = SetElementInArray(args) ;
	if (ret != 0)
	{
		cprintf("[EVAL] #1 SetElementInArray: Failed\n");
		return 1;
	}
	if (ptr1[2] != 300)
	{
		cprintf("[EVAL] #2 SetElementInArray: Failed\n");
		return 1;
	}

	//Set (Exist)
	char f2[100] = "sea _myArr3 0 100000";
	strsplit(f2, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;
	if (ret != 0)
	{
		cprintf("[EVAL] #3 SetElementInArray: Failed\n");
		return 1;
	}
	if (ptr2[0] != 100000)
	{
		cprintf("[EVAL] #4 SetElementInArray: Failed\n");
		return 1;
	}

	//Set (Not Exist)
	char f3[100] = "sea _x3 3 11";
	strsplit(f3, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;
	if (ret != -1)
	{
		cprintf("[EVAL] #5 SetElementInArray: Failed\n");
		return 1;
	}
	if (ptr2[0] != 100000 || ptr2[1] != 0 || ptr2[2] != 0 || ptr2[3] != 0)
	{
		cprintf("[EVAL] #6 SetElementInArray: Failed\n");
		return 1;
	}
	cprintf("[EVAL] SetElementInArray: Succeeded\n");

	return 1;
}


int TestAss2Q4()
{
	int retValue = 1;
	int i = 0;
	//Create first array
	char cr1[100] = "cnia _x4 3";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cr1, WHITESPACE, args, &numOfArgs) ;

	int* ptr1 = CreateIntArray(args) ;
	assert(ptr1 >= (int*)0xF1000000);


	//Create second array
	char cr2[100] = "cnia _y4 4";
	numOfArgs = 0;
	strsplit(cr2, WHITESPACE, args, &numOfArgs) ;

	int* ptr2 = CreateIntArray(args) ;
	assert(ptr2 >= (int*)0xF1000000);

	int ret =0 ;

	//Set elements of 1st array
	char f1[100] = "sea _x4 0 10";
	strsplit(f1, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	char f2[100] = "sea _x4 1 20";
	strsplit(f2, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	char f3[100] = "sea _x4 2 30";
	strsplit(f3, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	//Calculate var of 1st array
	char v1[100] = "cav _x4";
	strsplit(v1, WHITESPACE, args, &numOfArgs) ;
	ret = CalcArrVar(args) ;

	if (ret != 66)
	{
		cprintf("[EVAL] #1 CalcArrVar: Failed\n");
		return 1;
	}

	//Set elements of 2nd array
	char f4[100] = "sea _y4 0 400";
	strsplit(f4, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	char f5[100] = "sea _y4 1 400";
	strsplit(f5, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	//Calculate var of 2nd array
	char v2[100] = "cav _y4";
	strsplit(v2, WHITESPACE, args, &numOfArgs) ;
	ret = CalcArrVar(args) ;

	if (ret != 40000)
	{
		cprintf("[EVAL] #2 CalcArrVar: Failed\n");
		return 1;
	}

	cprintf("[EVAL] CalcArrVar: Succeeded\n");

	return 1;
}

int TestAss2BONUS()
{
	int retValue = 1;
	int i = 0;
	int ret =0 ;

	//Create first array
	char cr1[100] = "cnia _x+ 2";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cr1, WHITESPACE, args, &numOfArgs) ;

	int* ptr1 = CreateIntArray(args) ;
	assert(ptr1 >= (int*)0xF1000000);

	//Create second array
	char cr2[100] = "cnia _y+ 3";
	numOfArgs = 0;
	strsplit(cr2, WHITESPACE, args, &numOfArgs) ;

	int* ptr2 = CreateIntArray(args) ;
	assert(ptr2 >= (int*)0xF1000000);

	//Create third array
	char cr3[100] = "cnia _z+ 1";
	numOfArgs = 0;
	strsplit(cr3, WHITESPACE, args, &numOfArgs) ;

	int* ptr3 = CreateIntArray(args) ;
	assert(ptr3 >= (int*)0xF1000000);

	//Set elements
	char f1[100] = "sea _y+ 0 400";
	strsplit(f1, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	char f2[100] = "sea _y+ 2 400";
	strsplit(f2, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	char f3[100] = "sea _z+ 0 400";
	strsplit(f3, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	//Expand 1st array
	char e1[100] = "enia _x+ 2";
	strsplit(e1, WHITESPACE, args, &numOfArgs) ;
	ExpandIntArray(args) ;

	//Expand 3rd array
	char e2[100] = "enia _z+ 3";
	strsplit(e2, WHITESPACE, args, &numOfArgs) ;
	ExpandIntArray(args) ;

	//Expand 2nd array
	char e3[100] = "enia _y+ 1";
	strsplit(e3, WHITESPACE, args, &numOfArgs) ;
	ExpandIntArray(args) ;

	//Set elements
	char f4[100] = "sea _x+ 2 400";
	strsplit(f4, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	char f5[100] = "sea _x+ 3 400";
	strsplit(f5, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	char f6[100] = "sea _z+ 3 400";
	strsplit(f6, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	//Create fourth array
	char cr4[100] = "cnia _w+ 4";
	numOfArgs = 0;
	strsplit(cr4, WHITESPACE, args, &numOfArgs) ;

	int* ptr4 = CreateIntArray(args) ;
	assert(ptr4 >= (int*)0xF1000000);

	//Set elements
	char f7[100] = "sea _w+ 0 200";
	strsplit(f7, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	char f8[100] = "sea _w+ 3 200";
	strsplit(f8, WHITESPACE, args, &numOfArgs) ;
	ret = SetElementInArray(args) ;

	//Get size of 1st array
	char g1[100] = "gas _x+";
	numOfArgs = 0;
	strsplit(g1, WHITESPACE, args, &numOfArgs) ;
	ret = GetArraySize(args) ;
	if (ret != 4)
	{
		cprintf("[EVAL] #1 ExpandIntArray: Failed\n");
		return 1;
	}

	//Get size of 2nd  array
	char g2[100] = "gas _y+";
	numOfArgs = 0;
	strsplit(g2, WHITESPACE, args, &numOfArgs) ;
	ret = GetArraySize(args) ;
	if (ret != 4)
	{
		cprintf("[EVAL] #2 ExpandIntArray: Failed\n");
		return 1;
	}

	//Get size of 3rd array
	char g3[100] = "gas _z+";
	numOfArgs = 0;
	strsplit(g3, WHITESPACE, args, &numOfArgs) ;
	ret = GetArraySize(args) ;
	if (ret != 4)
	{
		cprintf("[EVAL] #3 ExpandIntArray: Failed\n");
		return 1;
	}

	//Get size of 4th array
	char g4[100] = "gas _w+";
	numOfArgs = 0;
	strsplit(g4, WHITESPACE, args, &numOfArgs) ;
	ret = GetArraySize(args) ;
	if (ret != 4)
	{
		cprintf("[EVAL] #4 ExpandIntArray: Failed\n");
		return 1;
	}

	//Calculate var of 1st array
	char v1[100] = "cav _x+";
	strsplit(v1, WHITESPACE, args, &numOfArgs) ;
	ret = CalcArrVar(args) ;
	if (ret != 40000)
	{
		cprintf("[EVAL] #5 ExpandIntArray: Failed\n");
		return 1;
	}

	//Calculate var of 2nd array
	char v2[100] = "cav _y+";
	strsplit(v2, WHITESPACE, args, &numOfArgs) ;
	ret = CalcArrVar(args) ;
	if (ret != 40000)
	{
		cprintf("[EVAL] #6 ExpandIntArray: Failed\n");
		return 1;
	}

	//Calculate var of 3rd array
	char v3[100] = "cav _z+";
	strsplit(v3, WHITESPACE, args, &numOfArgs) ;
	ret = CalcArrVar(args) ;
	if (ret != 40000)
	{
		cprintf("[EVAL] #7 ExpandIntArray: Failed\n");
		return 1;
	}

	//Calculate var of 4th array
	char v4[100] = "cav _w+";
	strsplit(v4, WHITESPACE, args, &numOfArgs) ;
	ret = CalcArrVar(args) ;
	if (ret != 10000)
	{
		cprintf("[EVAL] #8 ExpandIntArray: Failed\n");
		return 1;
	}
	cprintf("[EVAL] [BONUS] ExpandIntArray: Succeeded\n");

	return retValue;
}

