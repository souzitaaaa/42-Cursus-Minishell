/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:00:03 by dinoguei          #+#    #+#             */
/*   Updated: 2023/10/09 18:04:16 by jede-ara         ###   ########.fr       */
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

char	*ft_strjoinfree(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_s;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!new_s)
		return (0);
	ft_strlcpy(new_s, s1, (s1_len + 1));

	ft_strlcpy((new_s + s1_len), s2, (s2_len + 1));
	if (*s1)
		ft_free_str((char **)&s1);
	return (new_s);
}

char	**ft_arrjoin(char **s1, char **s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	**new_s;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_arrlen(s1);
	s2_len = ft_arrlen(s2);
	new_s = malloc((s1_len + s2_len + 1) * sizeof(char *));
	if (!new_s)
		return (0);
	ft_arrlcpy(new_s, s1, (s1_len + 1));
	ft_arrlcpy((new_s + s1_len), s2, (s2_len + 1));
	return (new_s);
}

char	**ft_arrstrarrjoin(char	**arr1, char	*str, char	**arr2)
{
	size_t	arr1_len;
	size_t	arr2_len;
	char	**new_arr;

	if (!arr1 || !str || !arr2)
		return (0);
	arr1_len = ft_arrlen(arr1);
	arr2_len = ft_arrlen(arr2);
	new_arr = malloc((arr1_len + arr2_len + 2) * sizeof(char *));
	if (!new_arr)
		return (0);
	ft_arrlcpy(new_arr, arr1, (arr1_len + 1));
	new_arr[arr1_len] = str;
	ft_arrlcpy(new_arr + arr1_len + 1, arr2, (arr2_len + 1));
	return (new_arr);
}

char	**ft_arrstrjoin(char	**arr, char	*str)
{
	size_t	arr_len;
	char	**new_arr;

	if (!arr || !str)
		return (0);
	arr_len = ft_arrlen(arr);
	new_arr = malloc((arr_len + 2) * sizeof(char *));
	if (!new_arr)
		return (0);
	ft_arrlcpy(new_arr, arr, (arr_len + 1));
	new_arr[arr_len] = str;
	return (new_arr);
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
