#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;

    for (size_t i = 0; i < length; i++) {
        if (putchar(bytes[i]) == EOF)
	    return false;
    }
		
    return true;
}

static void print_dec(int data) {
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

static void print_hex(int data) {
    char buffer[10];
    buffer[0] = '0';
    buffer[1] = 'x';
    int i = 2;
	
    while(data > 0) {
        int remainder = data % 16;
		
        switch(remainder) {
	case(10):
	    buffer[i] = 'a';
	    break;
        case(11):
            buffer[i] = 'b';
            break;
        case(12):
            buffer[i] = 'c';
            break;
        case(13):
            buffer[i] = 'd';
            break;
        case(14):
            buffer[i] = 'e';
            break;
        case(15):
            buffer[i] = 'f';
            break;
        default:
            buffer[i] = '0' + remainder;
            break;
        }

        ++i;
        data = data / 16;
    }

    for(int j = 0; j < i; ++j)
        putchar(buffer[j]);
}

int printf(const char* restrict format, ...) {
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
                return -1; // TODO: Set errno to EOVERFLOW.

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

                print_dec(num);
                written++;
                break;
        }
        case 'x': {
            format++;
            int num = va_arg(parameters, int);

            if(!maxrem)
                return -1;

            print_hex(num);
            written++;
            break;
        }
        case 's': {
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);

            if (maxrem < len)
                return -1; // TODO: Set errno to EOVERFLOW.

            if (!print(str, len))
                return -1;

            written += len;
            break;
        }
        default: {
            format = format_begun_at;
            size_t len = strlen(format);

            if (maxrem < len)
                return -1; // TODO: Set errno to EOVERFLOW.

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
