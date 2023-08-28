/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:17:24 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/16 21:07:31 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//getcwd  obtém o diretório de trabalho atual
int	pwd(void)
{
	char	pwd[4096];

	getcwd(pwd, 4096);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (0);
}
