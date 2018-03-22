#include <kern/tests.h>

//define the white-space symbols
#define WHITESPACE "\t\r\n "

void TestAssignment1()
{
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q1:\n");
	cprintf("========================\n");
	TestAss1Q1();
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q2:\n");
	cprintf("========================\n");
	TestAss1Q2();
}
int TestAss1Q1()
{
	//cprintf("Q1 Automatic Test: under preparation. will be available later isA\n");
	int retValue = 0;
	int i = 0;
	//CASE1: pow
	char cr1[100] = "calc ^ 2 10";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cr1, WHITESPACE, args, &numOfArgs) ;

	uint32 ret = Calc(numOfArgs, args) ;
	if (ret != 1024)
	{
		cprintf("[EVAL] Calc.Pow: Failed\n");
		return retValue;
	}

	//CASE2: add
	char cr2[100] = "calc + 1 2 3 4";
	numOfArgs = 0;
	strsplit(cr2, WHITESPACE, args, &numOfArgs) ;

	ret = Calc(numOfArgs, args) ;
	if (ret != 10)
	{
		cprintf("[EVAL] Calc.Add: Failed\n");
		return retValue;
	}
	char cr3[100] = "calc + 1 2 3 4 10 100";
	numOfArgs = 0;
	strsplit(cr3, WHITESPACE, args, &numOfArgs) ;

	ret = Calc(numOfArgs, args) ;
	if (ret != 120)
	{
		cprintf("[EVAL] Calc.Add: Failed\n");
		return retValue;
	}

	//CASE3: factorial
	char cr4[100] = "calc ! 5";
	numOfArgs = 0;
	strsplit(cr4, WHITESPACE, args, &numOfArgs) ;

	ret = Calc(numOfArgs, args) ;
	if (ret != 120)
	{
		cprintf("[EVAL] Calc.Factorial: Failed\n");
		return retValue;
	}

	//CASE4: bitwise and
	char cr5[100] = "calc & 1101 1001";
	numOfArgs = 0;
	strsplit(cr5, WHITESPACE, args, &numOfArgs) ;

	ret = Calc(numOfArgs, args) ;
	if (ret != 9)
	{
		cprintf("[EVAL] Calc.And: Failed\n");
		return retValue;
	}
	char cr6[100] = "calc & 11110000 10101010";
	numOfArgs = 0;
	strsplit(cr6, WHITESPACE, args, &numOfArgs) ;

	ret = Calc(numOfArgs, args) ;
	if (ret != 160)
	{
		cprintf("[EVAL] Calc.And: Failed\n");
		return retValue;
	}
	cprintf("[EVAL] Calc: Succeeded\n");

	return 0;
}
int TestAss1Q2()
{
	cprintf("Q3 Test: manually try the test cases in the doc. \n..."
			"OR, you can do it automatically by un-commenting the code in tests.c (TestAss1Q2()), it should output the same results in the Examples of the Assignment Document\n");
/*
	int retValue = 0;
	int i = 0;

	//CASE1:
	//should execute the help command
	char cr0[100] = "help";
	execute_command(cr0) ;

	//should execute the add command
	char cr1[100] = "add 2 3";
	execute_command(cr1) ;

	//CASE2: should print the description of the "add"
	char cr2[100] = "add";
	execute_command(cr2) ;

	//CASE3: should print the commands that start with kernel
	char cr3[100] = "kernel";
	execute_command(cr3) ;

	//CASE4: should print the commands that start with ru
	char cr4[100] = "ru";
	execute_command(cr4) ;

	//CASE5: should print unknown command
	char cr5[100] = "smm";
	execute_command(cr5) ;

*/
	return 0;
}
