/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:15:07 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/16 21:58:46 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//COPIADO DO PIPEX

char	*create_pathname(char	*str, char	*str_path, int *flag)
{
	char	*slash_cmd;
	char	**path;
	char	*temp;
	int		i;

	path = ft_split(str_path, ':');
	i = 0;
	while (path[i])
	{
		slash_cmd = ft_strjoin("/", str);
		temp = ft_strjoin(path[i], slash_cmd);
		ft_free_str(&slash_cmd);
		if (access((const char *)temp, F_OK) == 0)
		{
			*flag = 1;
			str = temp;
			break ;
		}
		ft_free_str(&temp);
		i++;
	}
	ft_free_array(&path);
	return (str);
}

char	*find_path(char	*str, char	**envp, int *flag)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			path = envp[i] + 5;
		i++;
	}
	if (path)
		str = create_pathname(str, path, flag);
	return (str);
}

char	*ft_pathname(int *flag, char **envp, int stdout_copy, char **cmd)
{
	int		len;
	char	*str;

	str = "\0";
	len = ft_strlen(cmd[0]);
	if (len > 3)
	{
		if (!ft_strncmp(".sh", cmd[0] + ft_strlen(cmd[0]) - 3, 3))
		{
			if (!ft_strncmp("./", cmd[0], 2))
			{
				str = cmd[0] + 2;
				return (str);
			}
			error_management(cmd[0], stdout_copy, 0);
			free_and_exit(127, cmd, NULL, 0);
		}
	}
	if (access((const char *)cmd[0], F_OK))
		str = find_path(cmd[0], envp, flag);
	else
		str = cmd[0];
	return (str);
}

void	execution(char **cmd, t_main *main)
{
	char	*pathname;
	int		error;
	int		flag;

	pathname = ft_pathname(&flag, main->env_arr, main->stdout_copy, cmd);
	if (!strncmp("./", cmd[0], 2))
	{
		cmd[0] = cmd[0] + 2;
		error = execve((const char *)pathname, (char **const)cmd, main->env_arr);
		cmd[0] = cmd[0] - 2;
	}
	else
		error = execve((const char *)pathname, (char **const)cmd, main->env_arr);
	if (error == -1)
		error_management(cmd[0], main->stdout_copy, 0);
	free_and_exit(127, cmd, pathname, flag);
}

void	exec_other_cmd(char **cmd, t_main *main)
{
	int	pid;

	pid = fork();
	if(pid == 0)
		execution(cmd, main);
	waitpid(pid, NULL, WNOHANG); //PESQUISAR ESTA FLAG
}

