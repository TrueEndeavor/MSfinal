/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:27:03 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/15 12:39:23 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_cmd_P *root, t_core_struct *core, char *prompt)
{
	if (root)
		ft_free_cmd(root);
	ft_free_tok_list(core->token_head);
	free(prompt);
}

void	free_both(t_cmd_P *root, t_token_T *token_head)
{
	if (root)
		ft_free_cmd(root);
	if (token_head)
		ft_free_tok_list(&token_head);
}
