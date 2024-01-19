/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

extern uint32 nsaddr;
extern paint_screen();
extern print_text_on_vga(unsigned int x, unsigned int y, const char * t);


process	main(void)
{



	

	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	nsaddr = 0x800a0c10;

	netstart();


	tcp_init();

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}


	return OK;
    
}
