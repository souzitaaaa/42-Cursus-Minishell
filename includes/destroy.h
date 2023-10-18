/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:41:52 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/17 19:16:54 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTROY_H
# define DESTROY_H

# include "minishell.h"

/*
!FREE_STRUCTS.C
*/
void	free_quotes(t_quotes *stack);
void	free_lexer(t_lexer *stack);
void	free_env(t_env *stack);

/*
!DESTROY
*/
void    destroy_input(t_main *main);
void    destroy_main(t_main *main, bool input);

#endif
