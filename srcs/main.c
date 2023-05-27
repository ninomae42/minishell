#include "tokenizer.h"
#include "parser.h"
#include "exec.h"
#include "environ.h"

extern char **environ;

// bool	is_argc_valid(int argc)
// {
// 	return (argc == 2);
// }
//
// int	main(int argc, char **argv)
// {
// 	t_token	*token;
// 	bool	is_error;
//
// 	if (!is_argc_valid(argc))
// 		exit(EXIT_FAILURE);
// 	is_error = false;
// 	token = tokenize(argv[1], &is_error);
// 	print_token(token);
// 	puts("=====");
// 	t_node	*ast = parse(token);
// 	dealloc_token(token);
// 	print_ast_pre_order(ast);
// 	int status = exec_command(ast);
// 	exit(status);
// }

int	main(void)
{
	t_env	*env;

	env = env_new();
	if (load_env(env, environ) != 0)
	{
		env_dealloc(env);
		exit(EXIT_FAILURE);
	}
	// ft_printenv(env);
	// env_entry_print(env);
	// printf("entry_size: %zu\n", env_entry_size(env));
	// puts("");
	//
	// ft_setenv(env, "PWD", "/code/dir/dir2", 1);
	// // ft_printenv(env);
	// env_entry_print(env);
	// printf("entry_size: %zu\n", env_entry_size(env));
	// puts("");
	//
	// ft_setenv(env, "HOGE", "hogehoge=mogemoge", 1);
	// // ft_printenv(env);
	// env_entry_print(env);
	// printf("entry_size: %zu\n", env_entry_size(env));
	// puts("");
	//
	// ft_unsetenv(env, "PWD");
	// // ft_printenv(env);
	// env_entry_print(env);
	// printf("entry_size: %zu\n", env_entry_size(env));
	// puts("");
	//
	// ft_unsetenv(env, "HOSTNAME");
	// // ft_printenv(env);
	// env_entry_print(env);
	// printf("entry_size: %zu\n", env_entry_size(env));
	// puts("");

	char	**environ = env_entry_alloc_environ(env);
	char	**tmp = environ;
	while (*environ != NULL)
	{
		printf("%s\n", *environ);
		environ++;
	}
	free(tmp);

	env_dealloc(env);
}
