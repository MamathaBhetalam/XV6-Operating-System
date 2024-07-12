Part A: Pointer Dereference:
In xv6, the VM system uses a simple two-level page table. As it currently is structured, user code is loaded into the very first part of the address space. Thus, if you dereference a null pointer, you will not see an exception (as you might expect) (In the latest version you will still get an exception trap error); instead, you will see whatever code is the first bit of code in the program that is running. Try it and see! Report what you find in your Readme file.
Thus, the first fundamental thing you might do in this case is to create a program that dereferences a null pointer. It is simple! See if you can do it. Then run it on Linux as well as xv6 to see the difference.
Your job here will be to figure out how xv6 sets up a page table and then change it to leave the first three pages (0x0 - 0x3000) unmapped. The code segment should be starting at 0x3000. Thus, once again, this project is mainly about understanding the code and not writing very much. Look at how exec() works to understand better how address spaces get filled with code and, in general, initialized. That will get you most of the way.
You should also look at fork(), in particular the part where the address space of the child is created by copying the address space of the parent. What needs to change in there?
Remember that the first process is a little unique and is constructed by the kernel directly? Take a look at userinit() and do not forget to update it too.
The rest of your task will be completed by looking through the code to figure out where there are checks or assumptions made about the address space. Consider what happens when you pass a parameter into the kernel; for example, if passing a pointer, the kernel needs to be very careful to ensure you haven't passed it a bad pointer. How does it do this now? Does this code need to change in order to work in your new version of xv6?
One last hint: you'll have to look at the xv6 makefile as well. In there, user programs are compiled so as to set their entry point (where the first instruction is) to 0. If you change xv6 to make the first two pages invalid, clearly, the entry point must be the new beginning of the code segment. Thus, something in the makefile will need to change to reflect this as well.
You should be able to demonstrate what happens when the user code tries to access a null pointer. If you do this part correctly, xv6 should trap and kill the process without too much trouble on your part.
This is the exciting part, check how your older uniq, head, and ps program works in this scenario. Report your findings.
Part B: Stack Rearrangement:
The xv6 address space (after modifications from Part A) is set up like this:
USERTOP = 640KB
(free)
heap (grows towards the high-end of the address space)
stack (fixed-sized, one page)
code
(3 unmapped pages)
ADDR = 0x0
In this part of the xv6 project, you'll rearrange the address in the following manner:
USERTOP = 640KB
stack (at end of address space; grows backwards)
... (gap >= 5 pages)
heap (grows towards the high-end of the address space)
code
(3 unmapped pages)
ADDR = 0x0
This will take a little work on your part. First, you'll have to figure out where xv6 allocates and initializes the code, heap, and user stack; then, you'll have to figure out how to change the allocation to be in new places. You'll need to place the stack at the high end of the xv6 user address space instead of between the code and heap.
Some tricky parts: one thing you'll have to be very careful with is how xv6 currently tracks the size of a process's address space (currently with the sz field in the proc struct). There are a number of places in the code where this is used (e.g., to check whether an argument passed into the kernel is valid; to copy the address space). We recommend keeping this field to track the size of the code and heap, but doing some other accounting to track the stack, and changing all relevant code (i.e., that used to deal with sz ) to now work with your new accounting.
You should also be wary of growing your heap and overwriting your stack. In this assignment, you should always leave 5 unallocated (invalid) pages between the stack and heap. These are reserved for supporting memory mapping segments.
The high end of the xv6 user address space is 640KB (see the USERTOP value defined in the xv6 code). Thus your first stack page should live at 636KB-640KB.
