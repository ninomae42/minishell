/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:04:09 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:04:10 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "parser.h"
# include "minishell.h"

// expander.c
char	*concat_str(char *s1, char *s2);
char	*expand_word(char *word);
void	expand(t_ast *ast);

// expander_utils.c
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
char	*get_escaped_str(char *s);

// expander_utils2.c
char	*get_without_escape_str(char *escaped_str);

// expander_quotes1.c
char	*expand_no_quote(char **word);
char	*expand_single_quote(char **word);

// expander_parameter.c
char	*expand_parameter(char **word);

// expander_double_quotes.c
char	*expand_double_quote(char **word);

#endif
