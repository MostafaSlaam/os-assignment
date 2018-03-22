/*	Simple command-line kernel prompt useful for
	controlling the kernel and exploring the system interactively.


KEY WORDS
==========
CONSTANTS:	WHITESPACE, NUM_OF_COMMANDS
VARIABLES:	Command, commands, name, description, function_to_execute, number_of_arguments, arguments, command_string, command_line, command_found
FUNCTIONS:	readline, cprintf, execute_command, run_command_prompt, command_kernel_info, command_help, strcmp, strsplit, start_of_kernel, start_of_uninitialized_data_section, end_of_kernel_code_section, end_of_kernel
=====================================================================================================================================================================================================
 */

#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/memlayout.h>
#include <inc/assert.h>
#include <inc/x86.h>


#include <kern/console.h>
#include <kern/command_prompt.h>
#include <kern/memory_manager.h>
#include <kern/trap.h>
#include <kern/kdebug.h>
#include <kern/user_environment.h>
#include <kern/tests.h>


//TODO:LAB3.Hands-on: declare start address variable of "My int array"

//=============================================================

//Structure for each command
struct Command
{
	char *name;
	char *description;
	// return -1 to force command prompt to exit
	int (*function_to_execute)(int number_of_arguments, char** arguments);
};

//Functions Declaration
int command_writemem(int number_of_arguments, char **arguments);
int command_readmem(int number_of_arguments, char **arguments);
int command_meminfo(int , char **);

//Lab2.Hands.On
//=============
//TODO: LAB2 Hands-on: declare the command function here


//Lab4.Hands.On
//=============
int command_show_mapping(int number_of_arguments, char **arguments);
int command_set_permission(int number_of_arguments, char **arguments);
int command_share_range(int number_of_arguments, char **arguments);

//Lab5.Examples
//=============
int command_nr(int number_of_arguments, char **arguments);
int command_ap(int , char **);
int command_fp(int , char **);

//Lab5.Hands-on
//=============
int command_asp(int, char **);
int command_cfp(int, char **);

//Lab6.Examples
//=============
int command_run(int , char **);
int command_kill(int , char **);
int command_ft(int , char **);


//Array of commands. (initialized)
struct Command commands[] =
{
		{ "help", "Display this list of commands", command_help },	//don't need arguments
		{ "kernel_info", "Display information about the kernel", command_kernel_info },	//don't need arguments
		{ "wum", "writes one byte to specific location" ,command_writemem},	//need arguments
		{ "rum", "reads one byte from specific location" ,command_readmem},	//need arguments
		{ "ver", "Print the FOS version" ,command_ver},//don't need arguments
		{ "add", "Add two integers" ,command_add},//need arguments
		{ "meminfo", "Display number of free frames in the memory" ,command_meminfo},//need arguments

		//helper commands
		//===============
		{ "cvp", "Connect virtual address to physical address", command_cvp},
		{ "dvp", "DisConnect virtual address from its physical one", command_dvp},

		//Assignment4 commands
		//====================
		{ "cfrc", "Count Page Frames with Specific Reference Count ", command_cfrc},
		{ "srp", "Share 2 virtual ranges with the given permissions", command_srp},
		{ "mum", "Move user memory", command_mum},

		//TODO: LAB2 Hands-on: add the commands here


		//LAB4: Hands-on
		{ "sm", "Lab4.HandsOn: display the mapping info for the given virtual address", command_show_mapping},
		{ "sp", "Lab4.HandsOn: set the desired permission to a given virtual address page", command_set_permission},
		{ "sr", "Lab4.HandsOn: shares the physical frames of the first virtual range with the 2nd virtual range", command_share_range},

		//LAB5: Examples
		{ "nr", "Lab5.Example: show the number of references of the physical frame" ,command_nr},
		{ "ap", "Lab5.Example: allocate one page [if not exists] in the user space at the given virtual address", command_ap},
		{ "fp", "Lab5.Example: free one page in the user space at the given virtual address", command_fp},

		//LAB5: Hands-on
		{ "asp", "Lab5.HandsOn: allocate 2 shared pages with the given virtual addresses" ,command_asp},
		{ "cfp", "Lab5.HandsOn: count the number of free pages in the given range", command_cfp},

		//LAB6: Examples
		{ "ft", "Lab6.Example: Free table", command_ft},
		{ "run", "Lab6.Example: Load and Run User Program", command_run},
		{ "kill", "Lab6.Example: Kill User Program", command_kill},

};

//Number of commands = size of the array / size of command structure
#define NUM_OF_COMMANDS (sizeof(commands)/sizeof(commands[0]))

int firstTime = 1;

//invoke the command prompt
void run_command_prompt()
{
	//CAUTION: DON'T CHANGE OR COMMENT THESE LINE======
	if (firstTime)
	{
		firstTime = 0;
		TestAssignment4();
	}
	else
	{
		cprintf("Test failed.\n");
	}
	//================================================

	char command_line[1024];

	while (1==1)
	{
		//get command line
		readline("FOS> ", command_line);

		//parse and execute the command
		if (command_line != NULL)
			if (execute_command(command_line) < 0)
				break;
	}
}

/***** Kernel command prompt command interpreter *****/

//define the white-space symbols
#define WHITESPACE "\t\r\n "

//Function to parse any command and execute it
//(simply by calling its corresponding function)
int execute_command(char *command_string)
{
	// Split the command string into whitespace-separated arguments
	int number_of_arguments;
	//allocate array of char * of size MAX_ARGUMENTS = 16 found in string.h
	char *arguments[MAX_ARGUMENTS];


	strsplit(command_string, WHITESPACE, arguments, &number_of_arguments) ;
	if (number_of_arguments == 0)
		return 0;

	// Lookup in the commands array and execute the command
	int command_found = 0;
	int i ;
	for (i = 0; i < NUM_OF_COMMANDS; i++)
	{
		if (strcmp(arguments[0], commands[i].name) == 0)
		{
			command_found = 1;
			break;
		}
	}

	if(command_found)
	{
		int return_value;
		return_value = commands[i].function_to_execute(number_of_arguments, arguments);
		return return_value;
	}
	else
	{
		//if not found, then it's unknown command
		cprintf("Unknown command '%s'\n", arguments[0]);
		return 0;
	}
}

/***** Implementations of basic kernel command prompt commands *****/
/***************************************/
/*DON'T change the following functions*/
/***************************************/
//print name and description of each command
int command_help(int number_of_arguments, char **arguments)
{
	int i;
	for (i = 0; i < NUM_OF_COMMANDS; i++)
		cprintf("%s - %s\n", commands[i].name, commands[i].description);

	cprintf("-------------------\n");

	return 0;
}

/*DON'T change this function*/
//print information about kernel addresses and kernel size
int command_kernel_info(int number_of_arguments, char **arguments )
{
	extern char start_of_kernel[], end_of_kernel_code_section[], start_of_uninitialized_data_section[], end_of_kernel[];

	cprintf("Special kernel symbols:\n");
	cprintf("  Start Address of the kernel 			%08x (virt)  %08x (phys)\n", start_of_kernel, start_of_kernel - KERNEL_BASE);
	cprintf("  End address of kernel code  			%08x (virt)  %08x (phys)\n", end_of_kernel_code_section, end_of_kernel_code_section - KERNEL_BASE);
	cprintf("  Start addr. of uninitialized data section 	%08x (virt)  %08x (phys)\n", start_of_uninitialized_data_section, start_of_uninitialized_data_section - KERNEL_BASE);
	cprintf("  End address of the kernel   			%08x (virt)  %08x (phys)\n", end_of_kernel, end_of_kernel - KERNEL_BASE);
	cprintf("Kernel executable memory footprint: %d KB\n",
			(end_of_kernel-start_of_kernel+1023)/1024);
	return 0;
}


/*DON'T change this function*/
int command_readmem(int number_of_arguments, char **arguments)
{
	unsigned int address = strtol(arguments[1], NULL, 16);
	unsigned char *ptr = (unsigned char *)(address ) ;

	cprintf("value at address %x = %c\n", ptr, *ptr);

	return 0;
}

/*DON'T change this function*/
int command_writemem(int number_of_arguments, char **arguments)
{
	unsigned int address = strtol(arguments[1], NULL, 16);
	unsigned char *ptr = (unsigned char *)(address) ;

	*ptr = arguments[2][0];

	return 0;
}

/*DON'T change this function*/
int command_meminfo(int number_of_arguments, char **arguments)
{
	cprintf("Free frames = %d\n", calculate_free_frames());
	return 0;
}

//===========================================================================
//Lab1 Examples
//=============
/*DON'T change this function*/
int command_ver(int number_of_arguments, char **arguments)
{
	cprintf("FOS version 0.1\n") ;
	return 0;
}

/*DON'T change this function*/
int command_add(int number_of_arguments, char **arguments)
{
	int n1 = strtol(arguments[1], NULL, 10);
	int n2 = strtol(arguments[2], NULL, 10);

	int res = n1 + n2 ;
	cprintf("res=%d\n", res);

	return 0;
}

//===========================================================================
//Lab2.Hands.On
//=============
//TODO: LAB2 Hands-on: write the command function here


//===========================================================================
//Lab4.Hands.On
//=============
int command_show_mapping(int number_of_arguments, char **arguments)
{
	//TODO: LAB4 Hands-on: fill this function. corresponding command name is "sm"
	//Comment the following line
	panic("Function is not implemented yet!");

	return 0 ;
}

int command_set_permission(int number_of_arguments, char **arguments)
{
	//TODO: LAB4 Hands-on: fill this function. corresponding command name is "sp"
	//Comment the following line
	panic("Function is not implemented yet!");

	return 0 ;
}

int command_share_range(int number_of_arguments, char **arguments)
{
	//TODO: LAB4 Hands-on: fill this function. corresponding command name is "sr"
	//Comment the following line
	panic("Function is not implemented yet!");

	return 0;
}

//===========================================================================
//Lab5.Examples
//==============
//[1] Number of references on the given physical address
int command_nr(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Example: fill this function. corresponding command name is "nr"
	//Comment the following line
	//panic("Function is not implemented yet!");



	uint32 pa = strtol(arguments[1], NULL, 16);

		//[1]  Get the frame info of the given pa
		struct Frame_Info * ptr_frame_info ;
		ptr_frame_info = to_frame_info(pa);

		// [2] Display number of references
		cprintf("num of refs at pa %x = %d\n", pa, ptr_frame_info->references);
		return 0;
}

//[2] Allocate Page: If the given user virtual address is mapped, do nothing. Else, allocate a single frame and map it to a given virtual address in the user space
int command_ap(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Example: fill this function. corresponding command name is "ap"
	//Comment the following line
	//panic("Function is not implemented yet!");
	//If already mapped, do nothing
		//Else, allocate & map

		uint32 va = strtol(arguments[1], NULL, 16);

		//[1] Check if the page exists or not?
		uint32 *ptr_table = NULL;
		struct Frame_Info* ptr_frame_info = get_frame_info(ptr_page_directory, (void*)va, &ptr_table);
		if (ptr_frame_info != NULL)
			return 0;

		//[2] Allocate new frame
		int ret = allocate_frame(&ptr_frame_info) ;
		if (ret == E_NO_MEM)
		{
			cprintf("No enough memory!\n");
			return -1;
		}

		//[3] Map the given va to the allocated frame
		ret = map_frame(ptr_page_directory, ptr_frame_info, (void*)va, PERM_USER|PERM_WRITEABLE);
		if (ret == E_NO_MEM)
		{
			cprintf("No enough memory!\n");
			return -1;
		}

		return 0 ;
}

//[3] Free Page: Un-map a single page at the given virtual address in the user space
int command_fp(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Example: fill this function. corresponding command name is "fp"
	//Comment the following line
	//panic("Function is not implemented yet!");
	uint32 address = strtol(arguments[1], NULL, 16);
		unsigned char *va = (unsigned char *)(address) ;
		// Un-map the page at this address
		unmap_frame(ptr_page_directory, va);

		return 0;
}

//===========================================================================
//Lab5.Hands-on
//==============
//[1] Allocate Shared Pages
int command_asp(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Hands-on: fill this function. corresponding command name is "asp"
	//Comment the following line
	panic("Function is not implemented yet!");

	return 0;
}


//[2] Count Free Pages in Range
int command_cfp(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Hands-on: fill this function. corresponding command name is "cfp"
	//Comment the following line
	panic("Function is not implemented yet!");

	return 0;
}

//===========================================================================
//Lab6.Examples
//=============
/*DON'T change this function*/
int command_run(int number_of_arguments, char **arguments)
{
	//[1] Create and initialize a new environment for the program to be run
	struct UserProgramInfo* ptr_program_info = env_create(arguments[1]);
	if(ptr_program_info == 0) return 0;

	//[2] Run the created environment using "env_run" function
	env_run(ptr_program_info->environment);
	return 0;
}

/*DON'T change this function*/
int command_kill(int number_of_arguments, char **arguments)
{
	//[1] Get the user program info of the program (by searching in the "userPrograms" array
	struct UserProgramInfo* ptr_program_info = get_user_program_info(arguments[1]) ;
	if(ptr_program_info == 0) return 0;

	//[2] Kill its environment using "env_free" function
	env_free(ptr_program_info->environment);
	ptr_program_info->environment = NULL;
	return 0;
}

int command_ft(int number_of_arguments, char **arguments)
{
	//TODO: LAB6 Example: fill this function. corresponding command name is "ft"
	//Comment the following line

	return 0;
}

//===========================================================================
//Helper Commands
//===============
/*DON'T change this function*/
int command_cvp(int number_of_arguments, char **arguments)
{
	uint32 va = strtol(arguments[1], NULL, 16);
	uint32 pa = strtol(arguments[2], NULL, 16);
	map_frame(ptr_page_directory, to_frame_info(pa), (void*)va, 3);
	return 0;
}

/*DON'T change this function*/
int command_dvp(int number_of_arguments, char **arguments)
{
	uint32 va = strtol(arguments[1], NULL, 16);
	uint32 *ptr_table;
	get_page_table(ptr_page_directory, (void*) va, 0, &ptr_table);
	if (ptr_table!=NULL)
		ptr_table[PTX(va)] &= ~PERM_PRESENT;

	return 0;
}

/****************************************************************/

//========================================================
/*ASSIGNMENT-4 [MAIN QUESTIONS] */
//========================================================

//Q1:1)	Count Page Frames with Specific Reference Count (1 MARK)
//==============================================================
/*DON'T change this function*/
int command_cfrc(int number_of_arguments, char **arguments )
{
	//DON'T WRITE YOUR LOGIC HERE, WRITE INSIDE THE CountFramesWithRefs() FUNCTION
	int ret = CountFramesWithRefs(arguments);
	cprintf("cnt = %d\n", ret);
	return 0;
}
/*---------------------------------------------------------*/

/*FILL this function
 * arguments[1]: source virtual address in HEX
 * arguments[2]: destination virtual address in HEX
 * arguments[3]: number of references to be checked
 * Return:
 * 	If <num of ref> greater than 0: return number of page frames in the given range that have these <num of ref>.
 * 	If <num of ref> equal 0: return number of empty pages in the given range.
 */
int CountFramesWithRefs(char** arguments)
{
	//TODO: Assignment4.Q1
	//put your logic here
	//...
uint32 src=strtol(arguments[1],NULL,16);
uint32 dst=strtol(arguments[2],NULL,16);
int num=strtol(arguments[3],NULL,10);
int count1=0;
int count2=0;
uint32 frams[10000];
int counter=0;
int x=0;

while(1==1)
{
	if (src>dst||src==dst)
		break;

	uint32 *ptr=NULL;
	get_page_table(ptr_page_directory,(void*) src, 0, &ptr) ;
	if(ptr!=NULL)
		{
			uint32 TableEntry=ptr[PTX(src)];
			int p = ptr[PTX(src)] & PERM_PRESENT;
	        if(p!=0)
	         {

			int frameNum=TableEntry>>12;
			uint32 address=frameNum*PAGE_SIZE;
			uint32 offset=PGOFF(src);
			uint32 pa=address+offset;
			for(int i=0;i<counter;i++)
			{
				if(pa==frams[i])
				{
					x=1;
					break;
				}
			}
			if(x==0)
			{

			frams[counter]=pa;
			counter++;
			count1++;

			}
			else
			{
				x=0;
			}
	        }
	        else
	        {
	        	count2++;
	        }
	        }
	src+=PAGE_SIZE;
}


if(num==0)
{
	//cprintf("cnt12 = %d\n", count2);
	return count2;
	}
else if(num==1)
{
//	cprintf("cnt1 = %d\n", count1);
	return count1;
	}


	return 0;
}
//========================================================

//Q2:Share Range with Permissions (1.5 MARK)
//==========================================

/*DON'T change this function*/
int command_srp(int number_of_arguments, char **arguments )
{
	//DON'T WRITE YOUR LOGIC HERE, WRITE INSIDE THE ShareRangeWithPermissions() FUNCTION
	ShareRangeWithPermissions(arguments) ;
	return 0;
}
/*---------------------------------------------------------*/

/*FILL this function
 * arguments[1]: start virtual address of the range to be shared (in HEX)
 * arguments[2]: start virtual address of the second range (in HEX)
 * arguments[3]: size of the sharing range
 * arguments[4]: size unit: 'K' for Kilobyte, 'M' for Megabyte
 * arguments[5]: <r/w>: 'r' for read-only permission, 'w' for read/write permission
 * arguments[6]: <s/u>:  's' for supervisor permission, 'u' for user permission
 */
void ShareRangeWithPermissions(char** arguments)
{
	//TODO: Assignment4.Q2
	//put your logic here
	//...
	int32  va1 = strtol(arguments[1], NULL, 16) ;
	int32 va2 = strtol(arguments[2], NULL, 16) ;
	uint32 size = (uint32)strtol(arguments[3], NULL, 10) ;
	char sizeUnit=arguments[4][0];
	char p=arguments[5][0];
	char u=arguments[6][0];




	if(sizeUnit=='K')
	{
		size *= 1024 ;
	    size = ROUNDUP(size, PAGE_SIZE); //round it to the nearest page
	    size+=PAGE_SIZE;
	}
	else if (sizeUnit=='M')
	{
		size *= 1048576 ;
	   size = ROUNDUP(size, PAGE_SIZE); //round it to the nearest page

	}

	 int r;
	 uint32 *ptr1=NULL;
	 struct Frame_Info * ptr;
	 //
	 {
		 if(va1%PAGE_SIZE)
		 		size+=PAGE_SIZE;
		va1=ROUNDDOWN(va1,PAGE_SIZE);

	 }


for (int i = 0 ; i < size ; i += PAGE_SIZE)
{


 get_page_table(ptr_page_directory, (void*)va1, 0, &ptr1) ;
	if(ptr1!=NULL)
	  {
	   int p1 = ptr1[PTX(va1)] & PERM_PRESENT;
		       if(p1!=0)
		          {
		           uint32 fnPage = ptr1[PTX(va1)] >> 12;
		           ptr=to_frame_info(fnPage*PAGE_SIZE);
		            }
		            else
		            {
		            	r=allocate_frame(&ptr);
		            	if(r==E_NO_MEM)
		            	{
		            		cprintf("no free fram");
		            	}
		                r=map_frame(ptr_page_directory,ptr,(void*)va1,PERM_USER|PERM_WRITEABLE|PERM_PRESENT);
		                if(r==E_NO_MEM)
		                {
		                  cprintf("no free table");
		                }
		            }
		    	}


	//ptr=get_frame_info(ptr_page_directory,(void*)va1,&ptr1);


	if(p=='r'&&u=='s')
	 {
		r=map_frame(ptr_page_directory,ptr,(void*)va2,((~PERM_WRITEABLE)&(~PERM_USER)));
		cprintf("rs ");

	 }

	 else if(p=='w'&&u=='s')
			{
			 r=map_frame(ptr_page_directory,ptr,(void*)va2,(PERM_WRITEABLE)&(~PERM_USER));

		    }

	 else if(p=='w'&&u=='u')
			{
			 r=map_frame(ptr_page_directory,ptr,(void*)va2,PERM_USER|PERM_WRITEABLE);

			}

	else if(p=='r'&&u=='u')
			{
			 r=map_frame(ptr_page_directory,ptr,(void*)va2,(~PERM_WRITEABLE)&(PERM_USER));

			}
        va1 += PAGE_SIZE;
        va2 += PAGE_SIZE;

	}

}


//========================================================

//Q3: Move User Memory (1.5 MARK)
//===============================

/*DON'T change this function*/
int command_mum(int number_of_arguments, char **arguments )
{
	//DON'T WRITE YOUR LOGIC HERE, WRITE INSIDE THE MoveUserMem() FUNCTION
	int ret = MoveUserMem(arguments) ;
	if (ret == -1)
	{
		cprintf("destination exists! nothing is done\n");
	}
	return 0;
}
/*---------------------------------------------------------*/

/*FILL this function
 * arguments[1]: source virtual address in HEX
 * arguments[2]: destination virtual address in HEX
 * arguments[3]: number of pages to be moved
 * Return:
 * 	If ANY of the destination pages exists, do nothing and return -1.
 * 	Otherwise, move and return 0.
 */
int MoveUserMem(char** arguments)
{
	//TODO: Assignment4.Q3
	//put your logic here
	//...

	char *va1 = (char *)strtol(arguments[1], NULL, 16) ;
	char *va2 = (char *)strtol(arguments[2], NULL, 16) ;
	uint32 temp=(uint32)va2;
	int pages = strtol(arguments[3], NULL, 10) ;
	for(int j=0;j<pages;j++)
	{
		uint32* page_table=NULL;
	get_page_table(ptr_page_directory,(void*)temp,0,&page_table);
		if (page_table != NULL && (page_table[PTX(temp)] & PERM_PRESENT))
				{
				return -1;
				}
		temp += PAGE_SIZE;
	}

	for(int i=0 ;i<pages;i++)
	{

		struct Frame_Info *ptrva1;
		uint32 *ptr_page_table1 = NULL;
		get_page_table(ptr_page_directory, va1, 0, &ptr_page_table1) ;
			if (ptr_page_table1 != NULL)
			{
				int p1 = ptr_page_table1[PTX(va1)] & PERM_PRESENT;
			   if(p1!=0)
				 {
				uint32 fnPage = ptr_page_table1[PTX(va1)] >> 12;
			    ptrva1=to_frame_info(fnPage*PAGE_SIZE);
			     }

			}

		int r=map_frame(ptr_page_directory,ptrva1,(void*)va2, PERM_USER|PERM_WRITEABLE);
		unmap_frame(ptr_page_directory,va1);
		va1 += PAGE_SIZE;
		va2 += PAGE_SIZE;
	}

	return 0 ;
}
//========================================================
