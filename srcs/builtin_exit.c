#include "builtin.h"
#include <limits.h>
#include "ft_err.h"
#include "minishell.h"

static int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

static bool	is_valid_argument(char *s)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	if (!ft_isdigit(*s))
		return (false);
	while (ft_isdigit(*s))
		s++;
	while (ft_isspace(*s))
		s++;
	if (*s)
		return (false);
	return (true);
}

static int	is_overflow(long current, long sign, char next)
{
	if (0 < sign)
	{
		if (LONG_MAX / 10 < current)
			return (1);
		current = current * 10;
		if ((LONG_MAX - current) < (next - '0'))
			return (1);
	}
	else
	{
		current = current * (-1);
		if (current < (LONG_MIN / 10))
			return (1);
		current = current * 10;
		if (-(next - '0') < (LONG_MIN - current))
			return (1);
	}
	return (0);
}

static void	atol_exit(char *str)
{
	char	*istr;
	long	num;
	int		sign;

	istr = str;
	sign = 1;
	num = 0;
	while (ft_isspace(*istr))
		istr++;
	if (*istr == '-' || *istr == '+')
		if (*istr++ == '-')
			sign = -1;
	while (ft_isdigit(*istr) && !is_overflow(num, sign, *istr))
		num = num * 10 + (*istr++ - '0');
	while (ft_isspace(*istr))
		istr++;
	if (*istr)
	{
		err_builtin_exit("numeric argument required", str);
		exit(255);
	}
	exit((sign * num) & 255);
}

int	builtin_exit(char **argv)
{
	if (isatty(STDOUT_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (argv[1] == NULL)
		exit(g_env->status);
	if (is_valid_argument(argv[1]))
	{
		if (argv[2])
		{
			err_builtin_exit("too many arguments", NULL);
			return (EXIT_FAILURE);
		}
		atol_exit(argv[1]);
	}
	err_builtin_exit("numeric argument required", argv[1]);
	exit(255);
	return (EXIT_FAILURE);
}
