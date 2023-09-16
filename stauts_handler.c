#include "main.h"

int status_handler(Shell *sh,int status)
{
	switch (status)
	{
		case 1 : 
			if (errno == EACCES)
			{
				sh->status = 127;
				return (sh->status);
			}
			break;
		case 2 :
			if (errno = ENOENT)
			{
				sh->status = 126;
				return (sh->status);
			}
			break;
	}
	return (status);
}
