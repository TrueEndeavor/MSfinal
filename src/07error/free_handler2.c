/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:27:03 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/11 15:03:55 by lannur-s         ###   ########.fr       */
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
