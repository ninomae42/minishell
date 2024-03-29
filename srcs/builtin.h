/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 09:59:46 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 09:59:47 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"
# include "libft.h"

bool	is_builtin(char *command_name);
int		execute_builtin(char **argv);;
int		builtin_echo(char **argv);
int		builtin_cd(char **argv);
int		builtin_pwd(char **argv);
int		builtin_export(char **argv);
int		builtin_unset(char **argv);
int		builtin_env(char **argv);
int		builtin_exit(char **argv);

// helpers
int		export_print(void);
void	init_pwd(void);
void	set_pwd_value(void);

#endif
