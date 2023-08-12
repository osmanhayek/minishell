/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:22:56 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 12:13:25 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_qmark(char **exp, int *j)
{
	char	*save;

	save = ft_itoa(g_global.error_num);
	ft_stradd(exp, save, *j);
	*j += ft_strlen(save);
	free(save);
	return (1);
}
