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

		//Assignment2 commands
		//====================
		{ "cnia", "Create named integer array with the given size", command_cnia},
		{ "gas", "Get the size of the given array", command_gas},
		{ "sea", "Set item at the given zero-based index in the given array", command_sea},
		{ "cav", "Calculate the variance of the given array ", command_cav},

		//Assignment2.BONUS command
		//=========================
		{ "enia", "Expand a named integer array and shift up all above arrays (if any)", command_enia},


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
		TestAssignment2();
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
	panic("Function is not implemented yet!");

	return 0;
}

//[2] Allocate Page: If the given user virtual address is mapped, do nothing. Else, allocate a single frame and map it to a given virtual address in the user space
int command_ap(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Example: fill this function. corresponding command name is "ap"
	//Comment the following line
	panic("Function is not implemented yet!");

	return 0 ;
}

//[3] Free Page: Un-map a single page at the given virtual address in the user space
int command_fp(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Example: fill this function. corresponding command name is "fp"
	//Comment the following line
	panic("Function is not implemented yet!");

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
/****************************************************************/

//========================================================
/*ASSIGNMENT-2 [MAIN QUESTIONS] */
//========================================================

//Q1:Create Named Int Array (0.75 MARK)
//=====================================
/*DON'T change this function*/
int command_cnia(int number_of_arguments, char **arguments )
{
	//DON'T WRITE YOUR LOGIC HERE, WRITE INSIDE THE CreateIntArray() FUNCTION
	CreateIntArray(arguments);
	return 0;
}
/*---------------------------------------------------------*/

/*FILL this function
 * arguments[1]: array name
 * arguments[2]: array size
 * Return:
 * 		Start address of the FIRST ELEMENT in the created array
 *
 * Example:
 * 	FOS> cnia	x	3
 * 				^
 * 				|
 * arguments	[1]	[2]
 * Create integer array named "x", with 3 elements and intialize them by zeros
 * It should return the start address of the FIRST ELEMENT in the created array
 */

char array_name[30][1000];
unsigned int addres[30];
int size[30];
int count=0;
unsigned int addresse=0xF1000000;
int* CreateIntArray(char** arguments)
{
	//TODO: Assignment2.Q1
	//put your logic here
	//...
if(count==30)
{
	cprintf("sorry the max number is 30");
	return 0;
}
int *ptr=(int*)addresse;
strcpy(array_name[count], arguments[1]);
int n=strtol(arguments[2],NULL,10);
size[count]=n;
int i;
for(i=0;i<n;i++)
{
	*ptr=0;
	ptr++;
}
    addres[count]=addresse;
    int* x=(int*)addresse;
	addresse=(unsigned int)ptr;
	count++;


	return x;
}
//========================================================

//Q2:Get the Array Size (0.75 MARK)
//=================================

/*DON'T change this function*/
int command_gas(int number_of_arguments, char **arguments )
{
	//DON'T WRITE YOUR LOGIC HERE, WRITE INSIDE THE GetArraySize() FUNCTION
	int ret = GetArraySize(arguments) ;
	if (ret != -1)
	{
		cprintf("size of %s = %d\n", arguments[1], ret);
	}
	else
	{
		cprintf("Array not exists!!\n");
	}
	return 0;
}
/*---------------------------------------------------------*/

/*FILL this function
 * arguments[1]: array name
 * Return:
 * 		If array exists: return its size
 * 		Else: return -1
 */
int GetArraySize(char** arguments)
{
	//TODO: Assignment2.Q2
	//put your logic here
	//...

	int i;
	for(i=0;i<30;i++)
	{
		if(strcmp(array_name[i],arguments[1])==0)
		{
			return size[i];
		}
	}

	return -1 ;
}
//========================================================

//Q3:Set Element in the Array (0.75 MARK)
//=======================================

/*DON'T change this function*/
int command_sea(int number_of_arguments, char **arguments )
{
	//DON'T WRITE YOUR LOGIC HERE, WRITE INSIDE THE SetElementInArray() FUNCTION
	int ret = SetElementInArray(arguments) ;
	if (ret == -1)
	{
		cprintf("Index outside the boundary of the array\n");
	}
	return 0;
}
/*---------------------------------------------------------*/

/*FILL this function
 * arguments[1]: array name
 * arguments[2]: item index (zero-based)
 * arguments[3]: item value
 * Return:
 * 		If index is correct: return 0
 * 		Else: return -1
 */
int SetElementInArray(char** arguments)
{
	//TODO: Assignment2.Q3
	//put your logic here
	//...
	int i;
		for(i=0;i<30;i++)
		{
			if(strcmp(array_name[i],arguments[1])==0)
			{
				int index=strtol(arguments[2],NULL,10);
				if(index==0)
				{
					int *ptr=(int*)(addres[i]);
									*ptr=strtol(arguments[3],NULL,10);
									return 0;
				}
				else if(index<size[i])
				{
				int *ptr=(int*)(addres[i]+(sizeof (int)*index));
				*ptr=strtol(arguments[3],NULL,10);
				return 0;
				}
				return -1;
			}
		}
	return -1 ;
}
//========================================================

//Q4:Calculate Array Variance (0.75 MARK)
//=======================================

/*DON'T change this function*/
int command_cav(int number_of_arguments, char **arguments )
{
	//DON'T WRITE YOUR LOGIC HERE, WRITE INSIDE THE CalcArrVar() FUNCTION
	int var = CalcArrVar(arguments);
	cprintf("variance of %s = %d\n", arguments[1], var);
	return 0;
}
/*---------------------------------------------------------*/

/*FILL this function
 * arguments[1]: array name
 */
int CalcArrVar(char** arguments)
{
	//TODO: Assignment2.Q4
	//put your logic here
//...
	int i;
	int mean=0;
	int var=0;

     for(i=0;i<30;i++)
     {
      if(strcmp(array_name[i],arguments[1])==0)
       {
    	  int *ptr1=(int*)addres[i];
    	  int *ptr2=(int*)addres[i];
    	  int j;
    	  for(j=0;j<size[i];j++)
    	  {
    		  mean=mean+*ptr1;
    		  ptr1++;
cprintf("%d\n",*ptr1);
    	  }
    	  mean=mean/size[i];
    	  cprintf("%d\n",mean);
    	  int f;
    	      	  for(f=0;f<size[i];f++)
    	      	  {
    	      		  var=var+((*ptr2-mean)*(*ptr2-mean));
    	      		  ptr2++;
    	      	  }
    	      	  int x=var/size[i];
    	      	cprintf("%d\n",x);
    	return  x;
       }
     }
	return -1;
}


//========================================================

//========================================================
/*ASSIGNMENT-2 [BONUS QUESTION] */
//========================================================

//BONUS: Expand Named Int Array (2 MARKS)
//========================================

/*DON'T change this function*/
int command_enia(int number_of_arguments, char **arguments )
{
	//DON'T WRITE YOUR LOGIC HERE, WRITE INSIDE THE ExpandIntArray() FUNCTION
	ExpandIntArray(arguments);
	return 0;
}
/*---------------------------------------------------------*/

/*FILL this function
 * arguments[1]: array name
 * It should delete the previously created <array name> from the memory.
 * This is done by moving down all allocated arrays that are located after the deleted one.
 */
void ExpandIntArray(char** arguments)
{
	//TODO: Assignment2.BONUS
	//put your logic here
	//...

	for(int i=0;i<30;i++)
	{
		if(strcmp(array_name[i],arguments[1])==0)
				{
			        int extra=strtol(arguments[2],NULL,10);
			        int counter=count;
			        int temp=count;

			        for(int j=0;i<temp-i;j++)
			        {
			        	for(int k=0;k<size[counter];k++)
			        	{
			        int*old_ptr=(int*)addres[counter];
			        old_ptr+=size[counter]+k;

			        int*temp=(int*)(addres[counter]+extra);

			        int*new_ptr=(int*)addres[counter];
			        new_ptr+=size[counter]+extra+k;
			        *new_ptr=*old_ptr;
			        addres[counter]=(int)temp;
			        	}
			        counter--;
			        }
			        int*ptr=(int*)addres[i];
			        ptr+=size[i]+extra;
			        for(int f=0;f<extra;f++)
			        {
			        	*ptr=0;
			        	ptr++;
			        }
			        size[i]+=extra;


				}
	}

}


