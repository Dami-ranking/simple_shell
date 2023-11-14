#include"main.h"
/**
 * _printf - Function to print a message
 * @mess: The message to be printed
 */
void _printf(const char *mess)
{
	write(1, mess, strlen(mess));
}
