/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:00:15 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/21 16:00:15 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_token(t_main *main, t_type token, char *str)
{
	t_node	*new;

	new = create_n(main, token, str);
	if (!new)
		return (1);
	insert_last(&main->tokens, new);
	return (0);
}
