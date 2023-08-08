/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:48:24 by dinoguei          #+#    #+#             */
/*   Updated: 2022/11/29 19:57:54 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(unsigned int n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != '\0')
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_utoa(unsigned int n)
{
	char				*out;
	unsigned int		len;

	len = get_len(n);
	out = malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	out[len] = '\0';
	len--;
	if (n == 0)
		out[0] = '0';
	while (n != '\0')
	{
		out[len] = (n % 10) + '0';
		len--;
		n = n / 10;
	}
	return (out);
}
/*
int		main(void)
{
	int number1 = 123456789;
	int number2 = 1;
	int number3 = 0;
	int number4 = -123456789;
	int number5 = -1;
	int number6 = -0;

	printf("%s\n", ft_itoa(number1));
	printf("%s\n", ft_itoa(number2));
	printf("%s\n", ft_itoa(number3));
	printf("%s\n", ft_itoa(number4));
	printf("%s\n", ft_itoa(number5));
	printf("%s\n", ft_itoa(number6));
}
*/
