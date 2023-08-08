/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:00:03 by dinoguei          #+#    #+#             */
/*   Updated: 2023/01/02 10:42:54 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *str, const char *str2)
{
	char	*temp;
	int		i;
	int		len1;
	int		len2;

	if (!str || !str2)
		return (NULL);
	len1 = ft_strlen((char *)str);
	len2 = ft_strlen ((char *)str2);
	temp = malloc((len1 + len2 + 1) * sizeof(const char));
	if (!temp)
		return (NULL);
	i = 0;
	while (len1 > i)
		temp[i++] = *str++;
	i = 0;
	while (len2 > i)
		temp[len1 + i++] = *str2++;
	temp[len1 + i] = '\0';
	return (temp);
}
/*
int	main(void)
{
	char	*teste = "Nanakusa ";
	char	*teste2 = "Nazuna";

	printf("Originals:\n");
	printf("%s\n", teste);
	printf("%s\n", teste2);
	printf("By my function:\n");
	printf("%s\n", ft_strjoin(teste, teste2));
}
*/
