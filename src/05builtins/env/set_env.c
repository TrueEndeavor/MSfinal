/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/15 13:17:25 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_val(char **val, char *value_to_set)
{
	if (*val != NULL)
		free(*val);
	*val = NULL;
	*val = ft_strdup(value_to_set);
	if (*val == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	if (value_to_set != NULL && value_to_set[0] != '\0')
		free(value_to_set);
}

void	add_enventry(char *key, char *value, int mod_flag, t_env_list *head)
{
	t_env_list	*new;

	new = NULL;
	if (value != NULL && mod_flag == 0)
	{
		new = ft_lstnew_env(key, value);
		if (!new)
			ft_lstclear_env(&head, free);
		ft_lstadd_back_env(&head, new);
	}
	else if (mod_flag == 0)
	{
		new = ft_lstnew_env(key, NULL);
		if (!new)
			ft_lstclear_env(&head, free);
		ft_lstadd_back_env(&head, new);
	}
}

void	replace_enventry(t_env_list **node, char *key, char *val, int *mod_flag)
{
	if ((ft_strlen((*node)->name) == ft_strlen(key)) && \
		(ft_strcmp((*node)->name, key) == 0))
	{
		if (val == NULL && *mod_flag == 2)
			replace_val(&(*node)->value, "");
		if (val && *val != '\0')
			replace_val(&(*node)->value, val);
		*mod_flag = 1;
	}
}

void	try_replace(t_env_list **node, char *key, char *value, int *mod_flag)
{
	replace_enventry(node, key, value, mod_flag);
}

void	set_env(t_core_struct *core, char *key_value_pair)
{
	t_env_list	*head;
	char		*key2set;
	char		*value2set;
	int			modified_flag;

	head = core->env_list;
	modified_flag = 0;
	key2set = NULL;
	value2set = NULL;
	get_key_val(core, key_value_pair, &key2set, &value2set);
	if (core->exit_code != EXIT_FAILURE)
	{
		while (core->env_list)
		{
			if (ft_strchr(key_value_pair, '=') && !value2set)
				modified_flag = 2;
			try_replace(&(core->env_list), key2set, value2set, &modified_flag);
			if (check_flag(modified_flag, &key2set) == 1)
				break ;
			core->env_list = (core->env_list)->next;
		}
		if (!modified_flag)
			add_enventry(key2set, value2set, modified_flag, head);
		core->env_list = head;
	}
}
