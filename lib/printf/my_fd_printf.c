#include "../inc/libft.h"
#include <stdarg.h>


#define BUFFER_SIZE (42 * 4046)


#define FLAGS_ZEROPAD   (1U <<  0U)
#define FLAGS_LEFT      (1U <<  1U)
// #define FLAGS_PLUS      (1U <<  2U)
#define FLAGS_SPACE     (1U <<  3U)
// #define FLAGS_HASH      (1U <<  4U)
// #define FLAGS_UPPERCASE (1U <<  5U)
#define FLAGS_PRECISION (1U <<  6U)
// #define FLAGS_SHORT     (1U <<  7U)
#define FLAGS_LONG      (1U <<  8U)
// #define FLAGS_LONG_LONG (1U <<  9U)
// #define FLAGS_PRECISION (1U << 10U)
// #define FLAGS_ADAPT_EXP (1U << 11U)

char buffer[BUFFER_SIZE];



int my_printf(int fd, va_list ap, char *format)
{
	static int ret = 0;
	char *tmp = NULL;

  unsigned int flags, width, precision, n;
  size_t idx = 0U;
  char *arg;

	ft_bzero(buffer, BUFFER_SIZE);
	while (*format && idx < BUFFER_SIZE) {

		if (*format == '%') { // %[flags][width][.precision][length]
			format++;

      flags = 0U;
      do {
        switch (*format) {
          case '0': flags |= FLAGS_ZEROPAD; format++; n = 1U; break;
          case '-': flags |= FLAGS_LEFT;    format++; n = 1U; break;
          default :                                   n = 0U; break;
        }
      } while (n);

      width = 0U;
      if (ft_isdigit(*format)) {
        width = skip_atoi((const char**)&format);
      } else if (*format == '*') {
        const int w = va_arg(ap, int);
        if (w < 0) {
          flags |= FLAGS_LEFT;    // reverse padding
          width = (unsigned int)-w;
        } else {
          width = (unsigned int)w;
        }
        format++;
      }

      precision = 0U;
      if (*format == '.') {
        flags |= FLAGS_PRECISION;
        format++;
        if (ft_isdigit(*format)) {
          precision = skip_atoi((const char**)&format);
        } else if (*format == '*') {
          const int prec = (int)va_arg(ap, int);
          precision = prec > 0 ? (unsigned int)prec : 0U;
          format++;
        }
      }
      if (*format == 'l') {
        flags |= FLAGS_LONG;
        format++;
      }

      switch (*format) {
        case 'd' :
        case 'i' :
        case 'u' :
        case 'x' :
        case 'X' : {
          

          // ignore '0' flag when precision is given
          if (flags & FLAGS_PRECISION) {
            flags &= ~FLAGS_ZEROPAD;
          }

          if (*format == 'i' || *format == 'd') {
            arg = ft_itoa(va_arg(ap, int));
          } else {
            if (*format == 'x' || *format == 'X') {
              char base[] = (*format == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";
            } else {
              char base[] = "0123456789";
            }
            arg = ft_unitoa_base(va_arg(ap, unsigned int), base);
          }
        }
      }

			// tmp = get_variable(*format++, tab, opt, ap);
			// ft_strlcpy(buffer + idx, tmp, ft_strlen(tmp) + 1);
			// idx += ft_strlen(tmp);
			// free(tmp);
		}
		else
			buffer[idx++] = *format++;
	}
	ft_putstr_fd(fd, buffer);
	ret += idx;
	return (*format) ? my_printf(fd, ap, format) : ret;
}

int my_fd_printf(int fd, const char *format, ...)
{
  va_list ap;
  va_start(ap, format);
  ft_bzero(buffer, BUFFER_SIZE);
  int ret = my_printf(fd, ap, (char*)format);
  va_end(ap);
  return ret;
}

#include <stdio.h>

int main(void)
{
  printf("%10.s salut\n", "-100");
  return 0;
}