/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:01:49 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/19 11:28:47 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		start = s_len;
	if (len > s_len - start)
		len = s_len - start;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, s + start, len);
	new[len] = 0;
	return (new);
}
