#include "smallsh.h"
#include <signal.h>
#include <stdlib.h>

int main()
{
	//signal handler for interrupts
	struct sigaction fgAct;
	fgAct.sa_handler = catchFgSignal;
	fgAct.sa_flags = SA_RESTART;
	sigfillset(&(fgAct.sa_mask));
	sigaction(SIGINT,&fgAct,NULL);

	//signal handler used to catch the completion of background processes
	struct sigaction bgAct;
	bgAct.sa_handler = catchBgSignal;
	bgAct.sa_flags = SA_RESTART;
	sigfillset(&(bgAct.sa_mask));
	sigaction(SIGCHLD,&bgAct,NULL);

	runShell();
	return 0;
}