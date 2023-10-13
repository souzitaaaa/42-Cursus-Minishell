/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:02:18 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/24 16:53:25 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_number_len(int n)
{
	int	len;

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

bool    check_more_var(char *str)
{
	int i = 1;
	
	if(*str == ' ')
		i = ft_strclen(str, '$') + 1;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char    *ft_arr_to_str(char **arr)
{
	int     arr_len = 0;
	int     i = 0;
	char    *out;
	
	while (arr[i])
	{
		arr_len += ft_strlen(arr[i]);
		i++;
	}
	printf("total arr_len: %i\n", arr_len);
	out = ft_calloc(arr_len + 1, sizeof(char *));
	i = 0;
	while (arr[i])
	{
		out = ft_strjoin(out, arr[i]);
		i++;
	}
	printf("Str pós juntar: %s\n", out);
	return (out);
}

char	*expand_more(t_main *main, char *str)
{
	printf("\033[1;32m\t\t[Expanding More]\033[0m\n");
	int     count = 0;
	t_var	*aux;
	char    *expanded = NULL;
	char    **arr;
	int i = 0;
	int dif;
	
	arr = ft_split(str, 36);
			printf("Arr das vars: \n");
			print_arr(arr);
	if (*str == ' ')
		i = 1;
	while (arr[i])
	{
		printf("Var a analisar: %s\n", arr[i]);
		if (ft_strncmp(arr[i], "$?", 2) == 0)
		{
			printf("Encontrada variavel de ambiente: %s\n\tExit code: %i\n", arr[i], main->exit_code);
			expanded = malloc(sizeof(char) * get_number_len(main->exit_code));
			expanded = ft_itoa(main->exit_code);
			printf("Expanded excode: %s\n", expanded);
			ft_free_str(&arr[i]);
			arr[i] = ft_strdup(expanded);
			ft_free_str(&expanded);
		}
		aux = main->env_list.head;
		count = 0;
		while (count++ < main->env_list.size)
		{
			if (ft_strncmp(arr[i], aux->var, ft_strclen(aux->var, '=')) == 0)
			{
				printf("Encontrada variavel de ambiente: %s\n\tNa envp: %s\n", arr[i], aux->var);
				expanded = ft_calloc(ft_strlen(aux->var) - ft_strclen(arr[i], ' ')  + 1, sizeof(char));
				dif = ft_strlen(arr[i]) - ft_strclen(arr[i], ' ');
				if (dif > 0)
				{
					printf("Dif function\n");
					ft_strlcpy(expanded, aux->var + ft_strclen(arr[i], ' '), ft_strlen(aux->var) - ft_strclen(arr[i], ' ') + 1);
					char *space = ft_calloc(dif + 1, sizeof(char));
					ft_memset(space, ' ', dif);
					printf("space after: %s.\n", space);
					printf("Expanded in dif function: %s\n", expanded);	
					expanded = ft_strjoinfree(expanded, space);
				}
				else
					ft_strlcpy(expanded, aux->var + ft_strclen(arr[i], ' '), ft_strlen(aux->var) - ft_strclen(arr[i], ' ') + 1);
				printf("Expanded: %s\n", expanded);
				ft_free_str(&arr[i]);
				arr[i] = ft_strdup(expanded + 1);
				ft_free_str(&expanded);
				break;
			}
			aux = aux->next;
		}
		if (count > main->env_list.size)
		{
			ft_free_str(&arr[i]);
			arr[i] = ft_strdup("");
		}	
		i++;
	}
			printf("Arr das vars depois de expandir: \n");
			print_arr(arr);
	return (ft_arr_to_str(arr));
}

//* Vai tratar de expandir a string para a o seu respetivo valor na variavel de ambiente
	//* ela vai percorrer a lista das env ate achar uma identica ao valor que lhe manda-mos
	//* quando encontrar vai copiar oque esta depois do = para dentro dessa str
char	*expand(t_main *main, char *cmp, bool ignore)
{
	int		count = 0;
	t_var	*aux = main->env_list.head;
	char *expanded = NULL;
	char    *str;
	int     i = 0;

	if (ignore == false)
	{
		while (is_space(cmp[i]) == true && cmp[i])
			i++;
	}
	str = ft_substr(cmp, i, ft_strlen(cmp) - i);
	printf("str: .%s.\n", str);
	if (check_more_var(str) == true)
	{
		expanded = expand_more(main, str);
		return (expanded);
	}
	printf("\033[1;32m\t\t[Expanding 1]\033[0m\n");
	printf("str: %s and str + 1: %s\n", str, str + 1);
	if (ft_strncmp(str, "$?", 2) == 0)
	{
		printf("Encontrada variavel de ambiente: %s\n\tExit code: %i\n", str, main->exit_code);
		expanded = malloc(sizeof(char) * get_number_len(main->exit_code));
		expanded = ft_itoa(main->exit_code);
		if (str + 2)
			expanded = ft_strjoinfree(expanded, str + 2);
		return (expanded);
	}
	while (count++ < main->env_list.size)
	{
		if (ft_strncmp(str + ft_strclen(str, '$') + 1, aux->var, ft_strclen(aux->var, '=')) == 0)
		{
			printf("Encontrada variavel de ambiente: %s\n\tNa envp: %s\n", str, aux->var);
			expanded = ft_calloc(ft_strclen(str, '$') + ft_strlen(aux->var) - ft_strclen(aux->var, '=') + 2, sizeof(char *));
			if (ft_strclen(str, '$') > 0)
			{
				printf("Dif function\n");
				ft_strlcpy(expanded, aux->var + ft_strclen(aux->var, '=') + 1, ft_strlen(aux->var) - ft_strclen(str, '$') + 1);
				char *space = ft_calloc(ft_strclen(str, '$') + 1, sizeof(char));
				ft_memset(space, ' ', ft_strclen(str, '$'));
				printf("space after: %s.\n", space);
				printf("Expanded in dif function: %s\n", expanded);	
				//! tratar do free da expanded
				expanded = ft_strjoin(space, expanded);
				free(space);
			}
			else
				ft_strlcpy(expanded, aux->var + ft_strclen(aux->var, '=') + 1, ft_strlen(aux->var) - ft_strclen(aux->var, '=') + 2);
			printf("\033[1;32m\t\t[End expanding 2]\033[0m\n");
			return (expanded);
		}
		aux = aux->next;
	}
			printf("\033[1;32m\t\t[End expanding 1]\033[0m\n");
	return("\0");
}


//* Esta funcao vai verificar se nos comandos foi inserido um $ para poder
	//* prosseguir com a expansao
void	check_expansion_arr(t_main *main, char **arr)
{
	int i = 0;
	int j;

	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (ft_strchr("$", arr[i][j]))
				arr[i] = expand(main, arr[i], false);
			j++;
		}
		i++;
	}
}
