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

char	*expand_more(t_main *main, char *str)
{
	//printf("\033[1;32m\t\t[Expanding More]\033[0m\n");
	int i = 0;
	char **arr;
	char *out;

	arr = ft_split(str, 36);
			//printf("Arr das vars: \n");
			//print_arr(arr);
	while (arr[i])
	{
		if (i != 0 || (i == 0 && *str == '$'))
		{
			arr[i] = ft_strjoinfree2("$", arr[i]);
			arr[i] = expand(main, arr[i]);
		}
		i++;
	}
			//printf("Arr das vars depois de expandir: \n");
			//print_arr(arr);
	out = ft_arr_to_str(arr, str);
	ft_free_str(&str);
	ft_free_array(&arr);
	return (out);
}

int     get_min_len(char *str, int i)
{
	int min =  0;
	min = get_min(ft_strclen(str + i + 1, ' '), ft_strclen(str + i + 1, SQUOTE));
	min = get_min(min, ft_strclen(str + i + 1, '\n'));
	return (min);
}

char	*expand_var(t_main *main, char *str, int i)
{
	int		count;
	char	*expanded;
	char	*out;
	t_var	*aux;

	aux = main->env_list.head;
	count = 0;
	while (count++ < main->env_list.size)
	{
		if (ft_strncmp(str + i + 1, aux->var, get_max(ft_strclen(aux->var, '='), get_min_len(str, i))) == 0)
		{
			//printf("Encontrada variavel de ambiente: %s\n\tNa envp: %s\n", str, aux->var);
			expanded = ft_calloc(ft_strlen(aux->var) - ft_strclen(aux->var, '=') + 1, sizeof(char *));
			ft_strlcpy(expanded, aux->var + ft_strclen(aux->var, '=') + 1, ft_strlen(aux->var) - ft_strclen(aux->var, '=') + 2);
			out = join_expanded(str, expanded, ft_strclen(aux->var, '=') + 1);
			ft_free_str(&expanded);
			return (out);
		}
		aux = aux->next;
	}
	out = join_expanded(str, "\0", ft_strclen(str, ' ') - i);
	return (out);
}


//* Vai tratar de expandir a string para a o seu respetivo valor na variavel de ambiente
	//* ela vai percorrer a lista das env ate achar uma identica ao valor que lhe manda-mos
	//* quando encontrar vai copiar oque esta depois do = para dentro dessa str
char	*expand(t_main *main, char *str)
{
	char	*expanded;
	int     i;
	char	*out;

	//printf("str: .%s.\n", str);
	i = ft_strclen(str, '$');
	if (check_more_var(str, i + 1) == true)
	{
		expanded = expand_more(main, str);
		return (expanded);
	}
	//printf("str: .%s.\n", str);
	//printf("\033[1;32m\t\t[Expanding 1]\033[0m\n");
	//printf("str: %s and str + 1: %s\n", str, str + 1);
	if (str[i + 1] == ' '  || str[i + 1] == '\0')
		return (str);
	if (ft_strncmp(str + i, "$?", 2) == 0)
		out = expand_exitcode(main, str);
	else
		out = expand_var(main, str, i);
			//printf("\033[1;32m\t\t[End expanding 1]\033[0m\n");
	ft_free_str(&str);
	return(out);
}

//* Esta funcao vai verificar se nos comandos foi inserido um $ para poder
	//* prosseguir com a expansao
void	check_expansion_arr(t_main *main, char **arr)
{
	int i = 0;

	if(main->flags.hd)
		return ;
	while (arr[i])
	{
		if (ft_strchr(arr[i], '$'))
			arr[i] = expand(main, arr[i]);
		i++;
	}
	del_emptyline(arr);
}

char	*check_expansion_str(t_main *main, char *str, bool hd)
{
	if(main->flags.hd)
		return(str);
	if (ft_strchr(str, '$'))
	{
		str = expand(main, str);
		if (hd && str[ft_strlen(str) - 1] != '\n')
			str = ft_strjoinfree(str, "\n");
	}
	return(str);
}
