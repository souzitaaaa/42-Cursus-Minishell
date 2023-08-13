/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:45:24 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/13 15:14:09 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
	{
		write(1, "error: NULL string", 20);
		return (1);
	}
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strclen(char const *s, char c)
{
	size_t	len;

	if (!s)
	{
		write(1, "error: NULL string", 20);
		return (1);
	}
	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		i++;
	}
	return (i);
}

//#include <stdio.h>
/*int main()
{
    const char *str;

    str = "rita";
    printf("%s is: %u\n", str, ft_strlen(str));
    str = "outlander; ";
    printf("%s is: %u\n", str, ft_strlen(str));
    str = "";
    printf("%s is: %u\n", str, ft_strlen(str));
    return (0);
}*/