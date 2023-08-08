/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:14:25 by dinoguei          #+#    #+#             */
/*   Updated: 2022/11/20 16:00:57 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	teste[] = "Tamanna Crusch";
	char	testecpy[] = "Tamanna Crusch";

	printf("Original:\n");
	printf("%s\n", teste);
	printf("By my function:\n");
	ft_memset(teste, 'x', 4);
	printf("%s\n", teste);
	printf("By the original:\n");
	memset(testecpy, 'x', 4);
	printf("%s\n", testecpy);
}
*/
