/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:34 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/26 19:44:19 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
Export:
•	export 2=mario nao pode funcionar - FAZER MENSAGENS DE ERRO 
• TEM UM SEG FAULT QUANDO FAÇO >a cd .. e cd . (nao sei em qual ordem e situação)
*/

char	*only_cd(t_main *main, bool  child)
{
	char *home;
	char *aux;
	
	home = getenv("HOME");
	if (home == NULL)
	{
		if (main->flags.not_print == false)
			error_cd(STDERR_FILENO);
		if (child)
			exit(1);
		set_exit_code(main, 1);
		return (NULL);
	}
	aux = ft_substr(home, 1, ft_strlen(home) - 1);
	free(aux);
	return (home);
}

char *find_home(char *path, t_main *main, bool child)
{
	char *home;
	char *aux;

	if (path[0] == '~')
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			if (main->flags.not_print == false)
				error_msg_file(path, STDERR_FILENO);
			if (child)
				exit(1);
			set_exit_code(main, 1);
			return (NULL);
		}
		aux = ft_substr(path, 1, ft_strlen(path) - 1);
		free(aux);
		return (home);
	}
	return (ft_strdup(path));
}

int change_dir(char *path, t_main *main, bool child)
{
	if (chdir(path) == 0)
		set_exit_code(main, 0);
	else
	{
		if (main->flags.not_print == false)
			error_msg_file(path, STDERR_FILENO);
		if (child)
			exit(1);
		set_exit_code(main, 1);
	}
	return (0);
}

void cd(char *path, t_main *main, bool child)
{
	char	*new_path;
	int		dir;
	char	*current;
	char	*path_pwd;

	current = ft_calloc(sizeof(char), 4096);
	getcwd(current, 4096);
	if (path == NULL)
	{
		new_path = only_cd(main, child);
		change_dir(new_path, main, child);
		dir = change_dir(new_path, main, child);
		if (dir == 0)
			{
				main->prev = ft_calloc(sizeof(char), ft_strlen(current) + 1);
				ft_strlcpy(main->prev, current, ft_strlen(current) + 1);
			}
	}
	else
	{
		if (ft_strcmp(path, "-") == 0)
		{
			if (main->prev)
			{
				dir = change_dir(main->prev, main, child);
				if (dir == 0)
				{
					if (main->flags.not_print == false)
						ft_printf("%s\n", main->prev);
					main->prev = ft_calloc(sizeof(char), ft_strlen(current) + 1);
					ft_strlcpy(main->prev, current, ft_strlen(current) + 1);
					path_pwd = ft_calloc(sizeof(char), 4096);
					getcwd(path_pwd, 4096);
					refresh_pwd(main, path_pwd);
					refresh_oldpwd(main, main->prev);
				}
			}
			else
			{
				if (main->flags.not_print == false)
					error_cd(STDERR_FILENO);
				if (child)
					exit(1);
				set_exit_code(main, 1);
			}
		}
		else
		{
			new_path = find_home(path, main, child);
			dir = change_dir(new_path, main, child);
			if (dir == 0)
			{
				main->prev = ft_calloc(sizeof(char), ft_strlen(current) + 1);
				ft_strlcpy(main->prev, current, ft_strlen(current) + 1);
				path_pwd = ft_calloc(sizeof(char), 4096);
				getcwd(path_pwd, 4096);
				refresh_pwd(main, path_pwd);
				refresh_oldpwd(main, main->prev);
			}
		}
		if (child)
			exit(0);
		set_exit_code(main, 0);
	}
}

