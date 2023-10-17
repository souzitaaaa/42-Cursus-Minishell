/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:09:13 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/16 21:35:06 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*Flag = 1: juntar a str in quotes e o arr after na string seguinte
//Juntar a str in quotes e a 1a str do array after na mesma string
char	**ft_arrnl_strarrjoin(char	**arr1, char	*str, char	**arr2)
{
	size_t	arr1_len;
	size_t	arr2_len;
	char	**new_arr;

	arr1_len = 0;
	if(arr1)
		arr1_len = ft_arrlen(arr1);
	arr2_len = ft_arrlen(arr2);
	new_arr = ft_calloc((arr1_len + arr2_len + 2), sizeof(char *));
	if (!new_arr)
		return (0);
	if(arr1)
		ft_arrlcpy(new_arr, arr1, (arr1_len + 1));
	str = ft_strjoinfree(str, arr2[0]);
	new_arr[arr1_len] = str;
	ft_arrlcpy(new_arr + arr1_len + 1, arr2 + 1, (arr2_len));
	return (new_arr);
}

//*Flag = 2: juntar a str in quotes na mesma string que a ultima do arr before e juntar o arr after na string seguinte
//Juntar a ultma do arr1 e str in quotes  after na mesma string
char	**ft_arrstrnl_arrjoin(char	**arr1, char	*str, char	**arr2)
{
	size_t	arr1_len;
	size_t	arr2_len;
	char	**new_arr;

	arr2_len = 0;
	arr1_len = ft_arrlen(arr1);
	if(arr2)
		arr2_len = ft_arrlen(arr2);
	new_arr = ft_calloc((arr1_len + arr2_len + 1), sizeof(char *));
	if (!new_arr)
		return (0);
	arr1[arr1_len - 1] = ft_strjoinfree(arr1[arr1_len -1], str);
	if(!arr2)
		return(arr1);
	ft_arrlcpy(new_arr, arr1, (arr1_len + 1));
	ft_arrlcpy(new_arr + arr1_len, arr2, (arr2_len + 1));
	return (new_arr);
}

//*Flag = 3: juntar a str in quotes e o arr after na ultima str do array before
char	**ft_arrstrarrjoin(char	**arr1, char	*str, char	**arr2)
{
	size_t	arr1_len;
	size_t	arr2_len;
	char	**new_arr;

	if (!arr1 || !str || !arr2)
		return (NULL);
	arr1_len = ft_arrlen(arr1);
	arr2_len = ft_arrlen(arr2);
	new_arr = malloc((arr1_len + arr2_len + 2) * sizeof(char *));
	if (!new_arr)
		return (0);
	str = ft_strjoinfree(str, arr2[0]);
	arr1[arr1_len -1] = ft_strjoinfree(arr1[arr1_len -1], str);
	ft_arrlcpy(new_arr, arr1, (arr1_len + 1));
	ft_arrlcpy(new_arr + arr1_len, arr2 + 1, (arr2_len));
	return (new_arr);
}

char *join_expanded(char *str, char *expanded, int len)
{
	char *result;
	char *before;

	before = ft_substr(str, 0, ft_strclen(str, '$'));
	result = ft_strjoinfree(before, expanded);
	result = ft_strjoinfree(result, str + ft_strclen(str, '$') + len);
	printf("result: %s\n", result);
	return(result);
}
