#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) 
{
	const unsigned char* bytes = (const unsigned char*) data;

	for (size_t i = 0; i < length; i++) {
		if (putchar(bytes[i]) == EOF)
			return false;
	}
		
	return true;
}

static void print_int(int data) 
{
	if(data == 0) {
		putchar('0');
		return;
	}

	char buffer[10];
	int i = 0;
	
	if(data < 0) {
		putchar('-');
		data = -data;
	}

	while(data > 0) {
		buffer[i++] = '0' + (data % 10);
		data = data / 10;
	}

	while(i > 0)
		putchar(buffer[--i]);	
}

int printf(const char* restrict format, ...) 
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;

			size_t amount = 1;

			while (format[amount] && format[amount] != '%')
				amount++;

			if (maxrem < amount)
				// TODO: Set errno to EOVERFLOW.
				return -1;

			if (!print(format, amount))
				return -1;

			format += amount;
			written += amount;

			continue;
		}

		const char* format_begun_at = format++;

		switch(*format) {
		case 'c': {
			format++;
			char c = (char) va_arg(parameters, int);

			if(!maxrem)
				return -1;

			if(!print(&c, sizeof(c)))
				return -1;

			written++;
			break;
		}

		case 'd': {
			format++;
			int num = va_arg(parameters, int);
			
			if(!maxrem)
				return -1;

			print_int(num);

			written++;
			break;
		}
	
		case 's': {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);

			if (maxrem < len)
				// TODO: Set errno to EOVERFLOW.
				return -1;

			if (!print(str, len))
				return -1;

			written += len;
			break;
		}

		default: {
			format = format_begun_at;
			size_t len = strlen(format);

			if (maxrem < len)
				// TODO: Set errno to EOVERFLOW.
				return -1;

			if (!print(format, len))
				return -1;

			written += len;
			format += len;
	
			break;
		}
	}
	}

	va_end(parameters);

	return written;
}
