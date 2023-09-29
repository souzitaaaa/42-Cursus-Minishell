/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:41:52 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/29 12:45:18 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTROY_H
# define DESTROY_H

# include "minishell.h"

/*
!FREE.C
*/
void	free_env(t_env *stack);

/*
!DESTROY
*/
void	destroy(t_main *main);

#endif
