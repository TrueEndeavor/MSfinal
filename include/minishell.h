/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:16:04 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 15:12:21 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h> //For exact error no ENOTDIR or EACCES
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "expand.h"
# include "builtins.h"
# include "utils.h"
# include "signals.h"

# define H_E "warning: here-document at line delimited by end-of-file (wanted "
/* 
 * Flag "g_signum" takes in the signum/exit code
 *       = 2 //SIGNINT
 *       = 3 //SIGQUIT
 */
extern int	g_signum;

int			display_new_prompt(t_core_struct *core);
t_token_T	*minishell_compile(char *src);
int			process_signals_in_child(int status);
void		process_eof(t_core_struct *core);

int			display_error(char *str);
void		panic(char *str);
void		ft_free_tok_list(t_token_T **token_head);
void		ft_free_env(t_env_list *env);
void		ft_free_cmd(t_cmd_P *cmd);
void		ft_free_heredoc(t_cmd_P *cmd);
void		here_ext(char *line, t_herecmd_P *hcmd);
void		free_all(t_cmd_P *root, t_core_struct *core, char *prompt);
void		init_sig(t_core_struct *core, t_cmd_P *fcmd);
void		sig_end(t_herecmd_P *h, t_core_struct *core, t_cmd_P *f, char *l);
void		end(t_herecmd_P *hcmd, t_core_struct *core, t_cmd_P *f, char *l);

#endif
