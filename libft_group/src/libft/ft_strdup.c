/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:05:20 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/05 22:37:19 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*ptr;

	len = ft_strlen((char *)str);
	ptr = malloc((len + 1) * sizeof(const char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = *str;
		i++;
		str++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_arrdup(char **arr)
{
	int		i;
	int		len;
	char	**ptr;

	len = ft_arrlen((char **)arr);
	ptr = malloc((len + 1) * sizeof(const char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = ft_strdup(arr[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

/*int	main(void)
{
	char	**teste;
	char	**testecpy;

	teste = ft_calloc(sizeof(char *), 4);
	teste[0] = ft_calloc(sizeof(char), 4);
	teste[0] = "ola";
	teste[1] = ft_calloc(sizeof(char), 5);
	teste[1] = "tudo";
	teste[2] = ft_calloc(sizeof(char), 4);
	teste[2] = "bem";
	teste[3] = NULL;

	printf("Original:\n");
	print_arr(teste);
	printf("Cpy:\n");
	testecpy = ft_arrdup(teste);
	print_arr(testecpy);
}*/

