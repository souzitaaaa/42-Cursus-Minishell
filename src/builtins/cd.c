/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:34 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/09 12:06:04 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*only_cd(t_main *main, bool  child)
{
	char *home;
	char *aux;

	home = getenv("HOME");
	if (home == NULL)
	{
		if (main->flags.not_print == false)
			error_cd(STDERR_FILENO, "HOME");
		exit_child(main, 1, child);
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
			exit_child(main, 1, child);
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
		exit_child(main, 1, child);
		return (1);
	}
	return (0);
}

char    *get_envvar(char *str, t_env *env_list)
{
	int count = 0;
	t_var *aux = env_list->head;
	char *out;

	while(count++ < env_list->size)
	{
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			out = malloc(sizeof(char) * ft_strlen(aux->var) - ft_strlen(str));
			ft_strlcpy(out, aux->var + ft_strlen(str) + 1, ft_strlen(aux->var) - ft_strlen(str));
			return(out);
		}
		aux = aux->next;
	}
	return(NULL);
}

void cd(char *path, t_main *main, bool child)
{
	char	*new_path;
	int		dir;
	char	*current;
	char	*path_pwd;
	char	*prev;

	current = ft_calloc(sizeof(char), 4096);
	getcwd(current, 4096);
	if (path == NULL)
	{
		new_path = get_envvar("HOME", &main->env_list);
		if (new_path)
		{
			dir = change_dir(new_path, main, child);
			if (dir == 0)
			{
				path_pwd = ft_calloc(sizeof(char), 4096);
				getcwd(path_pwd, 4096);
				refresh_pwd(main, path_pwd);
				refresh_oldpwd(main, current);
			}
		}
		else
		{
			if (main->flags.not_print == false)
				error_cd(STDERR_FILENO, "HOME");
			exit_child(main, 1, child);
			return ;
		}
	}
	else
	{
		if (ft_strcmp(path, "-") == 0)
		{
			prev = get_envvar("OLDPWD", &main->env_list);
			if(prev)
			{
				dir = change_dir(prev, main, child);
				if (dir == 0)
				{
					if (main->flags.not_print == false)
						ft_printf("%s\n", prev);
					path_pwd = ft_calloc(sizeof(char), 4096);
					getcwd(path_pwd, 4096);
					refresh_pwd(main, path_pwd);
					refresh_oldpwd(main, current);
				}
			}
			else
			{
				if (main->flags.not_print == false)
					error_cd(STDERR_FILENO, "OLDPWD");
				exit_child(main, 1, child);
				return ;
			}
		}
		else
		{
			new_path = find_home(path, main, child);
			dir = change_dir(new_path, main, child);
			if (dir == 0)
			{
				path_pwd = ft_calloc(sizeof(char), 4096);
				getcwd(path_pwd, 4096);
				refresh_pwd(main, path_pwd);
				refresh_oldpwd(main, current);
			}
		}
		exit_child(main, 0, child);
	}
}
