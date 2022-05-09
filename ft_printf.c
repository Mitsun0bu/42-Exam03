#include <unistd.h>
#include <stdarg.h>

int	ft_printf(char *format, ...);
int	ft_putchar(char c);
int	ft_convert_arg(char c, va_list arg_lst);
int	ft_print_s(char *s);
int	ft_print_nb(long long nb, char *base, long long base_size);

int	ft_printf(char *format, ...)
{
	int		len = 0;
	va_list	arg_lst;

	va_start(arg_lst, format);
	while (*format)
	{
		if (*format != '%')
			len += ft_putchar(*format);
		else
		{
			len += ft_convert_arg(*(format + 1), arg_lst);
			format ++;
		}
		format ++;
	}
	va_end(arg_lst);
	return (len);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_convert_arg(char c, va_list arg_lst)
{
	if (c == 's')
		return (ft_print_s(va_arg(arg_lst, char *)));
	else if (c == 'd')
		return (ft_print_nb(va_arg(arg_lst, int), "0123456789", 10));
	else if (c == 'x')
		return (ft_print_nb(va_arg(arg_lst, unsigned int), "0123456789abcdef", 16));
	else
		return (0);
}

int	ft_print_s(char *s)
{
	int	len = -1;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[++len])
		ft_putchar(s[len]);
	return (len);
}

int	ft_print_nb(long long nb, char *base, long long base_size)
{
	int			len = 0;
	long long	nbr = nb;

	if (nbr < 0)
	{
		len += ft_putchar('-');
		nbr = -nbr;
		nb = -nb;
	}
	if (nbr == 0)
		len = 1;
	while (nbr > 0)
	{
		len ++;
		nbr = nbr / base_size;
	}
	if (nb >= base_size)
		ft_print_nb((nb / base_size), base, base_size);
	ft_putchar(base[nb % base_size]);
	return (len);
}
