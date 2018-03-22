#include <kern/tests.h>
#include <kern/memory_manager.h>

//define the white-space symbols
#define WHITESPACE "\t\r\n "

void TestAssignment4()
{
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q1:\n");
	cprintf("========================\n");
	TestAss4Q1();
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q2:\n");
	cprintf("========================\n");
	TestAss4Q2();
	cprintf("\n========================\n");
	cprintf("Automatic Testing of Q3:\n");
	cprintf("========================\n");
	TestAss4Q3();
}

int TestAss4Q1()
{
	char ap1[100] = "ap 0x3800000";
	execute_command(ap1);
	char ap2[100] = "ap 0x3801000";
	execute_command(ap2);
	char ap3[100] = "ap 0x380A000";
	execute_command(ap3);
	char ap4[100] = "ap 0x380F000";
	execute_command(ap4);
	char ap5[100] = "ap 0x3900000";
	execute_command(ap5);
	char ap6[100] = "ap 0x3A00000";
	execute_command(ap6);
	char ap7[100] = "ap 0x3B00000";
	execute_command(ap7);
	char ap8[100] = "ap 0x3C00000";
	execute_command(ap8);

	//================
	//PART I: 0.5 MARK
	//================
	char cmd1[100] = "cfrc 0x3800000 0x3802000 1";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cmd1, WHITESPACE, args, &numOfArgs) ;
	int cnt = CountFramesWithRefs(args) ;
	if (cnt != 2)
	{
		cprintf("[EVAL] #1 CountFramesWithRefs Failed. Evaluation = 0\n");
		return 0;
	}

	char cmd2[100] = "cfrc 0x3802000 0x3900000 1";
	strsplit(cmd2, WHITESPACE, args, &numOfArgs) ;
	cnt = CountFramesWithRefs(args) ;
	if (cnt != 2)
	{
		cprintf("[EVAL] #2 CountFramesWithRefs Failed. Evaluation = 0\n");
		return 0;
	}

	char cmd3[100] = "cfrc 0x3800000 0x3900000 1";
	strsplit(cmd3, WHITESPACE, args, &numOfArgs) ;
	cnt = CountFramesWithRefs(args) ;
	if (cnt != 4)
	{
		cprintf("[EVAL] #3 CountFramesWithRefs Failed. Evaluation = 0\n");
		return 0;
	}

	char cmd4[100] = "cfrc 0x3800000 0x3D00000 3";
	strsplit(cmd4, WHITESPACE, args, &numOfArgs) ;
	cnt = CountFramesWithRefs(args) ;
	if (cnt != 0)
	{
		cprintf("[EVAL] #4 CountFramesWithRefs Failed. Evaluation = 0\n");
		return 0;
	}

	char cmd5[100] = "cfrc 0x3800000 0x3D00000 1";
	strsplit(cmd5, WHITESPACE, args, &numOfArgs) ;
	cnt = CountFramesWithRefs(args) ;
	if (cnt != 8)
	{
		cprintf("[EVAL] #5 CountFramesWithRefs Failed. Evaluation = 0\n");
		return 0;
	}

	char fp1[100] = "fp 0x3900000";
	execute_command(fp1);
	char fp2[100] = "fp 0x3A00000";
	execute_command(fp2);

	char cmd6[100] = "cfrc 0x3800000 0x3D00000 1";
	strsplit(cmd6, WHITESPACE, args, &numOfArgs) ;
	cnt = CountFramesWithRefs(args) ;
	if (cnt != 6)
	{
		cprintf("[EVAL] #6 CountFramesWithRefs Failed. Evaluation = 0\n");
		return 0;
	}

	//=================
	//PART II: 0.5 MARK
	//=================
	char cmd7[100] = "cfrc 0x3800000 0x3802000 0";
	strsplit(cmd7, WHITESPACE, args, &numOfArgs) ;
	cnt = CountFramesWithRefs(args) ;
	if (cnt != 0)
	{
		cprintf("[EVAL] #7 CountFramesWithRefs Failed. Evaluation = 0.5\n");
		return 0;
	}

	char cmd8[100] = "cfrc 0x3802000 0x3900000 0";
	strsplit(cmd8, WHITESPACE, args, &numOfArgs) ;
	cnt = CountFramesWithRefs(args) ;
	if (cnt != 252)
	{
		cprintf("[EVAL] #8 CountFramesWithRefs Failed. Evaluation = 0.5\n");
		return 0;
	}

	char cmd9[100] = "cfrc 0x3800000 0x3D00000 0";
	strsplit(cmd9, WHITESPACE, args, &numOfArgs) ;
	cnt = CountFramesWithRefs(args) ;
	if (cnt != 1274)
	{
		cprintf("[EVAL] #9 CountFramesWithRefs Failed. Evaluation = 0.5\n");
		return 0;
	}

	char fp3[100] = "fp 0x3800000";
	execute_command(fp3);
	char fp4[100] = "fp 0x3801000";
	execute_command(fp4);
	char fp5[100] = "fp 0x380A000";
	execute_command(fp5);
	char fp6[100] = "fp 0x380F000";
	execute_command(fp6);
	char fp7[100] = "fp 0x3900000";
	execute_command(fp7);
	char fp8[100] = "fp 0x3A00000";
	execute_command(fp8);
	char fp9[100] = "fp 0x3B00000";
	execute_command(fp9);
	char fp10[100] = "fp 0x3C00000";
	execute_command(fp10);


	cprintf("[EVAL] Q1 Automatic Test: Succeeded. Evaluation = 1\n");

	return 0;
}

int TestAss4Q2()
{
	char *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;
	int kilo = 1024 ;
	int mega = 1024*1024 ;


	//================
	//PART I: 0.5 MARK
	//================
	char cmd1[100] = "srp F0000000 40000000 32 M w s";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cmd1, WHITESPACE, args, &numOfArgs) ;

	ShareRangeWithPermissions(args) ;

	if(CSR(0xF0000000, 0x40000000, 32*mega, -1, 1, 0) < 0)
	{
		cprintf("[EVAL] Test Failed #1. Evaluation = 0\n");
		return 0;
	}
	if(CSR(0xF0000000, 0x40000000, 4*kilo, 2, 1, 0) < 0)
	{
		cprintf("[EVAL] Test Failed #2. Evaluation = 0\n");
		return 0;
	}
	extern char end_of_kernel[];
	uint32 endRange = ((uint32)end_of_kernel - KERNEL_BASE);
	if(CSR(0xF0000000+PHYS_IO_MEM, 0x40000000+PHYS_IO_MEM, endRange - PHYS_IO_MEM, 2, 1, 0) < 0)
	{
		cprintf("[EVAL] Test Failed #3. Evaluation = 0\n");
		return 0;
	}
	ptr1 = (char*)0xF0000000; *ptr1 = 'A' ;
	ptr2 = (char*)0x40000000;


	if ((*ptr1) != 'A' || (*ptr2) != 'A')
	{
		cprintf("[EVAL] #1 ShareRangeWithPermissions: Failed. Evaluation = 0\n");
		return 0;
	}

	ptr1 = (char*)0x41000000; *ptr1 = 'C' ;
	ptr2 = (char*)0xF1000000;

	if ((*ptr1) != 'C' || (*ptr2) != 'C')
	{
		cprintf("[EVAL] #2 ShareRangeWithPermissions: Failed. Evaluation = 0\n");
		return 0;
	}

	//=================
	//PART II: 0.5 MARK
	//=================
	char cmd2[100] = "srp 40000000 0 648 K w u";
	strsplit(cmd2, WHITESPACE, args, &numOfArgs) ;

	ShareRangeWithPermissions(args) ;

	if(CSR(0x40000000, 0, 648*kilo, -1, 1, 1) < 0)
	{
		cprintf("[EVAL] Test Failed #4. Evaluation = 0.5\n");
		return 0;
	}
	if(CSR(0x40000000, 0, 4*kilo, 3, 1, 1) < 0)
	{
		cprintf("[EVAL] Test Failed #5. Evaluation = 0.5\n");
		return 0;
	}
	if(CSR(0x40001000, 0x1000, 636*kilo, 2, 1, 1) < 0)
	{
		cprintf("[EVAL] Test Failed #6. Evaluation = 0.5\n");
		return 0;
	}
	ptr1 = (char*)0x0;
	ptr2 = (char*)0x9FFFF; *ptr2 = 'D';
	ptr3 = (char*)0xF009FFFF;
	ptr4 = (char*)0x4009FFFF;

	if ((*ptr1) != 'A' || (*ptr3) != 'D' || (*ptr4) != 'D')
	{
		cprintf("[EVAL] #3 ShareRangeWithPermissions: Failed. Evaluation = 0.5\n");
		return 0;
	}

	//==================
	//PART III: 0.5 MARK
	//==================
	char cmd3[100] = "srp 9FC00 3FFC00 7 K r u";
	strsplit(cmd3, WHITESPACE, args, &numOfArgs) ;

	ShareRangeWithPermissions(args) ;

	if(CSR(0x9F000, 0x3FF000, 12*kilo, -1, 0, 1) < 0)
	{
		cprintf("[EVAL] Test Failed #7. Evaluation = 1\n");
		return 0;
	}
	if(CSR(0x9F000, 0x3FF000, 4*kilo, 3, 0, 1) < 0)
	{
		cprintf("[EVAL] Test Failed #8. Evaluation = 1\n");
		return 0;
	}
	if(CSR(0xA0000, 0x400000, 8*kilo, 4, 0, 1) < 0)
	{
		cprintf("[EVAL] Test Failed #9. Evaluation = 1\n");
		return 0;
	}
	ptr1 = (char*)0x3FFFFF;
	ptr2 = (char*)0x400A1001;
	ptr3 = (char*)0x401001;

	if ((*ptr1) != 'D' || (*ptr2) != (*ptr3) )
	{
		cprintf("[EVAL] #4 ShareRangeWithPermissions: Failed. Evaluation = 1\n");
		return 0;
	}


	cprintf("[EVAL] Q2 Automatic Test: Succeeded. Evaluation = 1.5\n");
	return 0;
}

int TestAss4Q3()
{
	char *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6;
	int kilo = 1024 ;
	int mega = 1024*1024 ;

	//ClearUserSpace();

	char ap1[100] = "ap 0x2800000";
	execute_command(ap1);
	char ap2[100] = "ap 0x2801000";
	execute_command(ap2);
	char ap3[100] = "ap 0x2802000";
	execute_command(ap3);
	ptr1 = (char*)0x2800000; *ptr1 = 'a';
	ptr1 = (char*)0x28017FF; *ptr1 = 'b';
	ptr1 = (char*)0x2802FFF; *ptr1 = 'c';

	int ff1 = calculate_free_frames();

	//=================
	//PART I: 0.75 MARK
	//=================
	char cmd1[100] = "mum 0x2800000 0x2900000 3";
	int numOfArgs = 0;
	char *args[MAX_ARGUMENTS] ;
	strsplit(cmd1, WHITESPACE, args, &numOfArgs) ;

	int ret = MoveUserMem(args) ;

	int ff2 = calculate_free_frames();

	if (ret != 0 || ff1 != ff2)
	{
		cprintf("[EVAL] #0 MoveUserMem: Failed. Evaluation = 0\n");
		return 0;
	}

	if (CB(0x2900000, 0) != 1 || CB(0x2901000, 0) != 1 || CB(0x2902000, 0) != 1)
	{
		cprintf("[EVAL] #1 MoveUserMem: Failed. Evaluation = 0\n");
		return 0;
	}

	ptr1 = (char*)0x2900000;
	ptr2 = (char*)0x29017FF;
	ptr3 = (char*)0x2902FFF;
	if ((*ptr1) != 'a' || (*ptr2) != 'b' || (*ptr3) != 'c')
	{
		cprintf("[EVAL] #2 MoveUserMem: Failed. Evaluation = 0\n");
		return 0;
	}

	*ptr2 = 'y';
	if ((*ptr2) != 'y')
	{
		cprintf("[EVAL] #3 MoveUserMem: Failed. Evaluation = 0\n");
		return 0;
	}

	ff1 = ff2 ;

	char cmd2[100] = "mum 0x2901000 0x2BFF000 2";
	strsplit(cmd2, WHITESPACE, args, &numOfArgs) ;

	ret = MoveUserMem(args) ;

	ff2 = calculate_free_frames();

	if (ret != 0 || ff1 - ff2 != 1)
	{
		cprintf("[EVAL] #4 MoveUserMem: Failed. Evaluation = 0\n");
		return 0;
	}
	if (CB(0x2BFF000, 0) != 1 || CB(0x2C00000, 0) != 1)
	{
		cprintf("[EVAL] #5 MoveUserMem: Failed. Evaluation = 0\n");
		return 0;
	}
	ptr1 = (char*)0x2BFF7FF;
	ptr2 = (char*)0x2C00FFF;
	if ((*ptr1) != 'y' || (*ptr2) != 'c')
	{
		cprintf("[EVAL] #6 MoveUserMem: Failed. Evaluation = 0\n");
		return 0;
	}

	if (CB(0x2800000, 0) != 0 || CB(0x2801000, 0) != 0 || CB(0x2802000, 0) != 0
			|| CB(0x2901000, 0) != 0 || CB(0x2902000, 0) != 0)
	{
		cprintf("[EVAL] #7 MoveUserMem: Failed. Evaluation = 0\n");
		return 0;
	}

	//==================
	//PART II: 0.75 MARK
	//==================
	char ap4[100] = "ap 0x1400000"; execute_command(ap4);
	char ap5[100] = "ap 0x1401000"; execute_command(ap5);
	char ap6[100] = "ap 0x1402000"; execute_command(ap6);
	char ap7[100] = "ap 0x1C00000"; execute_command(ap7);

	ptr1 = (char*)0x1400000; *ptr1 = 'a';
	ptr1 = (char*)0x14007FF; *ptr1 = 'b';
	ptr1 = (char*)0x1400FFF; *ptr1 = 'c';
	ptr1 = (char*)0x1C00000; *ptr1 = 'x';
	ptr1 = (char*)0x1C007FF; *ptr1 = 'y';
	ptr1 = (char*)0x1C00FFF; *ptr1 = 'z';

	ff1 = calculate_free_frames();

	char cmd4[100] = "mum 0x1C00000 0x1400000 1";
	strsplit(cmd4, WHITESPACE, args, &numOfArgs) ;

	ret = MoveUserMem(args) ;

	ff2 = calculate_free_frames();

	if (ret != -1 || ff1 - ff2 != 0)
	{
		cprintf("[EVAL] #8 MoveUserMem: Failed. Evaluation = 0.75\n");
		return 0;
	}
	if (CB(0x1400000, 0) != 1 || CB(0x1C00000, 0) != 1)
	{
		cprintf("[EVAL] #9 MoveUserMem: Failed. Evaluation = 0.75\n");
		return 0;
	}

	ptr1 = (char*)0x1400000;
	ptr2 = (char*)0x1C00000;
	ptr3 = (char*)0x14007FF;
	ptr4 = (char*)0x1C007FF;
	ptr5 = (char*)0x1400FFF;
	ptr6 = (char*)0x1C00FFF;
	if ((*ptr1) != 'a' || (*ptr2) != 'x' || (*ptr3) != 'b' ||
			(*ptr4) != 'y'|| (*ptr5) != 'c'|| (*ptr6) != 'z')
	{
		cprintf("[EVAL] #10 MoveUserMem: Failed. Evaluation = 0.75\n");
		return 0;
	}


	char cmd3[100] = "mum 0x1400000 0x1BFF000 3";
	strsplit(cmd3, WHITESPACE, args, &numOfArgs) ;

	ret = MoveUserMem(args) ;

	ff2 = calculate_free_frames();

	if (ret != -1 || ff1 - ff2 != 0)
	{
		cprintf("[EVAL] #11 MoveUserMem: Failed. Evaluation = 0.75\n");
		return 0;
	}
	if (CB(0x1400000, 0) != 1 || CB(0x1401000, 0) != 1 || CB(0x1402000, 0) != 1 ||
			CB(0x1BFF000, 0) != -1 || CB(0x1C00000, 0) != 1 || CB(0x1C01000, 0) != 0)
	{
		cprintf("[EVAL] #12 MoveUserMem: Failed. Evaluation = 0.75\n");
		return 0;
	}

	ptr1 = (char*)0x1400000;
	ptr2 = (char*)0x1C00000;
	ptr3 = (char*)0x14007FF;
	ptr4 = (char*)0x1C007FF;
	ptr5 = (char*)0x1400FFF;
	ptr6 = (char*)0x1C00FFF;
	if ((*ptr1) != 'a' || (*ptr2) != 'x' || (*ptr3) != 'b' ||
			(*ptr4) != 'y'|| (*ptr5) != 'c'|| (*ptr6) != 'z')
	{
		cprintf("[EVAL] #13 MoveUserMem: Failed. Evaluation = 0.75\n");
		return 0;
	}



	cprintf("[EVAL] Q3 Automatic Test: Succeeded. Evaluation = 1.5\n");

	return 0;
}
//===========================================================================
//===========================================================================
//===========================================================================

int CB(uint32 va, int bn)
{
	uint32 *ptr_table = NULL;
	uint32 mask = 1<<bn;
	get_page_table(ptr_page_directory, (void*)va, 0, &ptr_table);
	if (ptr_table == NULL) return -1;
	return (ptr_table[PTX(va)] & mask) == mask ? 1 : 0 ;
}

void ClearUserSpace()
{
	for (int i = 0; i < PDX(USER_TOP); ++i) {
		ptr_page_directory[i] = 0;
	}
}

int CSR(uint32 ptr1, uint32 ptr2, uint32 size, int ref, uint8 rw, uint8 su)
{
	uint32 totalNumberOfPages = (size)/PAGE_SIZE;
	void* ptrTemp1 = (void*)ptr1;
	void* ptrTemp2 = (void*)ptr2;

	for(int i = 0;i<totalNumberOfPages;i++)
	{
		uint32* ptr_table1;
		uint32* ptr_table2;

		struct Frame_Info * pfi1 = get_frame_info(ptr_page_directory, ptrTemp1, &ptr_table1);
		struct Frame_Info * pfi2 = get_frame_info(ptr_page_directory, ptrTemp2, &ptr_table2);
		if (ptr_table1 == NULL)
		{
			cprintf("[EVAL] #1 ShareRangeWithPermissions: Failed. Table of address 1 = NULL\n");
			return -1;
		}
		if (ptr_table2 == NULL)
		{
			cprintf("[EVAL] #1 ShareRangeWithPermissions: Failed. Table of address 2 = NULL\n");
			return -1;
		}
		if(ptr_table1[PTX(ptrTemp1)] >> 12 != ptr_table2[PTX(ptrTemp2)] >> 12)
		{
			cprintf("[EVAL] #1 ShareRangeWithPermissions: Failed. Frame numbers not equal in the whole range\n");
			return -1;
		}
		if (ref != -1)
		{
			if ((*pfi2).references != ref)
			{
				cprintf("[EVAL] #1 ShareRangeWithPermissions: Failed. Num of frame references is not correct. MAKE SURE to use the 6 functions of LAB5 when solving this assignment\n");
				return -1;
			}
		}
		if (CB((uint32)ptrTemp2,0) <= 0)
		{
			cprintf("[EVAL] #1 ShareRangeWithPermissions: Failed. Present not set in the entire range\n");
			return -1;
		}
		if (CB((uint32)ptrTemp2,1) != rw)
		{
			cprintf("[EVAL] #1 ShareRangeWithPermissions: Failed. R/W not correct in the entire range\n");
			return -1;
		}
		if (CB((uint32)ptrTemp2,2) != su)
		{
			cprintf("[EVAL] #1 ShareRangeWithPermissions: Failed. S/U not correct in the entire range\n");
			return -1;
		}

		ptrTemp1 += PAGE_SIZE;
		ptrTemp2 += PAGE_SIZE;
	}

	return 0;
}
