#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void	new_name_and_not_null_ow_true(void)
{
	char	*getenv_res;

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("before:\t[%s]\n", getenv_res);

	if (setenv("HOGE", "hogehoge", 1) != 0)
	{
		perror("setenv");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("after:\t[%s]\n", getenv_res);
}

void	new_name_and_not_null_ow_false(void)
{
	char	*getenv_res;

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("before:\t[%s]\n", getenv_res);

	if (setenv("HOGE", "hogehoge", 0) != 0)
	{
		perror("setenv");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("after:\t[%s]\n", getenv_res);
}

void	new_name_and_null_ow_true(void)
{
	char	*getenv_res;

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("before:\t[%s]\n", getenv_res);

	if (setenv("HOGE", NULL, 1) != 0)
	{
		perror("setenv");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("after:\t[%s]\n", getenv_res);
}

void	new_name_and_null_ow_false(void)
{
	char	*getenv_res;

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("before:\t[%s]\n", getenv_res);

	if (setenv("HOGE", NULL, 1) != 0)
	{
		perror("setenv");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("after:\t[%s]\n", getenv_res);
}

void	null_name_and_not_null_ow_false(void)
{
	char	*getenv_res;

	errno = 0;
	getenv_res = getenv("HOGE");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("before:\t[%s]\n", getenv_res);

	if (setenv(NULL, NULL, 1) != 0)
	{
		perror("setenv");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	getenv_res = getenv("hoge");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("after:\t[%s]\n", getenv_res);
}

void	existing_name_and_null_ow_false(void)
{
	char	*getenv_res;

	errno = 0;
	getenv_res = getenv("USER");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("before:\t[%s]\n", getenv_res);

	if (setenv("USER", NULL, 0) != 0)
	{
		perror("setenv");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	getenv_res = getenv("USER");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("after:\t[%s]\n", getenv_res);
}

void	existing_name_and_null_ow_true(void)
{
	char	*getenv_res;

	errno = 0;
	getenv_res = getenv("USER");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("before:\t[%s]\n", getenv_res);

	if (setenv("USER", NULL, 1) != 0)
	{
		perror("setenv");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	getenv_res = getenv("USER");
	if (errno != 0)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	printf("after:\t[%s]\n", getenv_res);
}

int	main(void)
{
	// new_name_and_not_null_ow_true(); // normal
	// new_name_and_not_null_ow_false(); // normal
	// new_name_and_null_ow_true(); // SEGV
	// new_name_and_null_ow_false(); // SEGV
	// null_name_and_not_null_ow_false();
	// existing_name_and_null_ow_false();
	existing_name_and_null_ow_true();

	// char	*getenv_res;
	//
	// errno = 0;
	// getenv_res = getenv("USER");
	// if (errno != 0)
	// {
	// 	perror("getenv");
	// 	exit(EXIT_FAILURE);
	// }
	// printf("before:\t[%s]\n", getenv_res);
	//
	// if (setenv("USER", NULL, 0) != 0) // SEGV
	// {
	// 	perror("setenv");
	// 	exit(EXIT_FAILURE);
	// }
	//
	// // if (setenv("USER", NULL, 1) != 0) // SEGV
	// // {
	// // 	perror("setenv");
	// // 	exit(EXIT_FAILURE);
	// // }
	//
	// // if (setenv("USER", "", 1) != 0) // USER=""
	// // {
	// // 	perror("setenv");
	// // 	exit(EXIT_FAILURE);
	// // }
	//
	// getenv_res = getenv("USER");
	// printf("after:\t[%s]\n", getenv_res);
}
