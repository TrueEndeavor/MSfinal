/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:25 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/15 12:29:10 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *s)
{
	char	*result;
	char	*substring;

	result = ft_strchr(s, '=');
	if (result)
	{
		substring = ft_substr(s, 0, (ft_strlen(s) - ft_strlen(result)));
		if (!substring)
			return (NULL);
		return (substring);
	}
	else
		return (ft_strdup(s));
}

char	*get_value(char *s)
{
	char	*found_key_at;
	char	*result;
	int		start_index;

	found_key_at = ft_strchr(s, '=');
	result = NULL;
	if (found_key_at && ft_strlen(found_key_at) != 1)
	{
		start_index = (ft_strlen(s) - ft_strlen(found_key_at)) + 1;
		result = ft_substr(s, start_index, ft_strlen(s));
	}
	else
	{
		result = ft_calloc(1, sizeof(char));
		if (!result)
			return (NULL);
		*result = '\0';
	}
	return (result);
}

t_env_list	*init_env(char **envp)
{
	t_env_list	*minishell_envp_head;
	t_env_list	*new;
	int			i;

	minishell_envp_head = NULL;
	i = 0;
	while (envp[i])
	{
		if ((ft_strchr(envp[i], '=')) != NULL)
		{
			new = ft_lstnew_env(get_key(envp[i]), get_value(envp[i]));
			if (!new)
				return ((ft_lstclear_env(&minishell_envp_head, free), NULL));
			ft_lstadd_back_env(&minishell_envp_head, new);
		}
		i++;
	}
	return (minishell_envp_head);
}

int	validate_key(t_core_struct *core, char *key_to_set, char *key_value_pair)
{
	int	ret;

	ret = 0;
	if (!key_to_set)
		panic ("key to set not found");
	if (!is_valid_variable_name(key_to_set) || \
		(ft_strchr(key_to_set, '=') != NULL))
	{
		ft_printf("export: `%s': not a valid identifier\n", key_value_pair);
		core->exit_code = EXIT_FAILURE;
		ret = 1;
	}
	return (ret);
}

void	get_key_val(t_core_struct *core, char *kvp, char **key1, char **val)
{
	*key1 = get_key(kvp);
	if (validate_key(core, *key1, kvp) == 1)
	{
		if (*key1 != NULL && *key1[0] != '\0')
			free(*key1);
		return ;
	}
	get_trimmed_val(val, kvp);
}
