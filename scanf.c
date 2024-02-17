#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#include <stdarg.h>

static char digits[] = "0123456789ABCDEF";

/*
 * Read line
 * While there are args, put correct type into buffer
 */

int 
scanf(const char *restrict format, ...)
{
	// Get user input from STDIN
	char *buf;
	int sz;
	int bytes_read = getline(0, &buf, &sz);

	if (bytes_read < 0)
		return -1;
	
	// Conventional name for va_list object
	va_list ap;
	va_start(ap, format);

	char *s;
	int c, i, state;
	state = 0;

	for (i = 0; format[i]; i++) {
		c = format[i] & 0xff;	// Leaves only the last 8 bits of the original
		if (state == 0) {
			if (c == '%') {
				state = '%';
			} else {
				// TODO: Check for invalid inputs later
				buf++;			// iterate through string since no match
			}
		} else if (state == '%') {
			if (c == 'd') {
				int *d = va_arg(ap, int *);

				// TODO: Figure out how to get int str from buf; stop reading when we stop reading ints
				// TODO: use strcspn and figure out how many characters to read from, then do ptr arithmetic
			} else if (c == 's') {
				s = va_arg(ap, char *);

				// TODO: Figure out better error handling
				// problem 1: buffer no space, problem 2: when to stop reading
				if (s == 0)
					s = "(null)";

				
			}
		}
	}
}
