#include <unistd.h>
#include <stdio.h>

/**
 * main - prints the parent pid of process
 *
 * Return: 0 (Success)
 */
int main()
{
	pid_t ppid, pid;
	pid = getpid();
	ppid = getppid();
	printf("pid =%d\nppid =%d\n", pid, ppid);
	return (0);
}
