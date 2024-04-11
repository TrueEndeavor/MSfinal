/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:01:06 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 15:16:23 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sig(t_core_struct *core, t_cmd_P *fcmd)
{
	t_data	*data;

	setup_heredoc_signals();
	data = simpleton();
	data->core = core;
	data->fcmd = fcmd;
}

void	sig_end(t_herecmd_P *h, t_core_struct *core, t_cmd_P *f, char *l)
{
	ft_printf("%s,`%s')\n", H_E, h->delimiter);
	frhere(h, core, l, f);
	exit(EXIT_SUCCESS);
}

void	end(t_herecmd_P *hcmd, t_core_struct *core, t_cmd_P *f, char *l)
{
	frhere(hcmd, core, l, f);
	exit(EXIT_SUCCESS);
}
