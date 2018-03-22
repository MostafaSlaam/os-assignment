/* See COPYRIGHT for copyright information. */
#ifndef FOS_KERN_TESTS_H
#define FOS_KERN_TESTS_H
#ifndef FOS_KERNEL
# error "This is a FOS kernel header; user programs should not #include it"
#endif

#include <kern/command_prompt.h>
#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/memlayout.h>
#include <inc/assert.h>
#include <inc/x86.h>

void TestAssignment4();
int TestAss4Q1();
int TestAss4Q2();
int TestAss4Q3();
int CB(uint32 va, int bitIndex);
void ClearUserSpace();
int CSR(uint32 ptr1, uint32 ptr2, uint32 size, int ref, uint8 rw, uint8 su);
#endif /* !FOS_KERN_TESTS_H */
