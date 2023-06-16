#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define F1 "out1"
#define F2 "out2"

char	*command[] = {"echo", "hogehoge", NULL};

typedef struct s_redirect
{
	int		default_in_fd;
	bool	need_backup_in;
	int		default_out_fd;
	bool	need_backup_out;
}	t_redirect;

void	init_redirect(t_redirect *redirect)
{
	redirect->default_in_fd = STDIN_FILENO;
	redirect->default_out_fd = STDOUT_FILENO;
	redirect->need_backup_in = true;
	redirect->need_backup_out = true;
}

void	do_input_redirect(char *filename, t_redirect *redirect)
{
	int	infile_fd;

	infile_fd = open(filename, O_RDONLY);
	if (redirect->need_backup_in)
	{
		redirect->need_backup_in = false;
		redirect->default_in_fd = dup(redirect->default_in_fd);
	}
	dup2(infile_fd, STDOUT_FILENO);
	close(infile_fd);
}

void	do_output_redirect(char *filename, t_redirect *redirect)
{
	int	outfile_fd;

	outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirect->need_backup_out)
	{
		redirect->need_backup_out = false;
		redirect->default_out_fd = dup(redirect->default_out_fd);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	do_output_redirect_append(char *filename, t_redirect *redirect)
{
	int	outfile_fd;

	outfile_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirect->need_backup_out)
	{
		redirect->need_backup_out = false;
		redirect->default_out_fd = dup(redirect->default_out_fd);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	reset_input_redirect(t_redirect *redirect)
{
	dup2(redirect->default_in_fd, STDIN_FILENO);
	close(redirect->default_in_fd);
	redirect->default_in_fd = STDIN_FILENO;
	redirect->need_backup_in = true;
}

void	reset_output_redirect(t_redirect *redirect)
{
	dup2(redirect->default_out_fd, STDOUT_FILENO);
	close(redirect->default_out_fd);
	redirect->default_out_fd = STDOUT_FILENO;
	redirect->need_backup_out = true;
}

void	do_redirect(int redirect_type, t_redirect *redirect)
{
	pid_t		pid;

	if (redirect_type == 1)
	{
		do_output_redirect(F1, redirect);
		do_output_redirect(F2, redirect);
	}
	else
	{
		do_output_redirect_append(F1, redirect);
		do_output_redirect_append(F2, redirect);
	}
	pid = fork();
	if (pid < 0)
	{
		reset_output_redirect(redirect);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execv("/bin/echo", command);
	}
	else
	{
		int	status = 0;
		wait(&status);
		reset_output_redirect(redirect);
		printf("child exited with status: %d\n", status);
	}
}

int	main(int argc, char **argv)
{
	t_redirect	redirect;
	// pid_t		pid;


	if (argc != 2)
		exit(EXIT_FAILURE);
	init_redirect(&redirect);
	// if (atoi(argv[1]) == 1)
	// {
	// 	do_output_redirect(F1, &redirect);
	// 	do_output_redirect(F2, &redirect);
	// }
	// else
	// {
	// 	do_output_redirect_append(F1, &redirect);
	// 	do_output_redirect_append(F2, &redirect);
	// }
	// pid = fork();
	// if (pid < 0)
	// {
	// 	reset_output_redirect(&redirect);
	// 	perror("fork");
	// 	exit(EXIT_FAILURE);
	// }
	// if (pid == 0)
	// {
	// 	execv("/bin/echo", command);
	// }
	// else
	// {
	// 	int	status = 0;
	// 	wait(&status);
	// 	reset_output_redirect(&redirect);
	// 	printf("child exited with status: %d\n", status);
	// }
	for (int i = 0; i < 2; i++)
	{
		do_redirect(atoi(argv[1]), &redirect);
	}
}
