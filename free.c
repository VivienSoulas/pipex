/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:01:05 by vsoulas           #+#    #+#             */
/*   Updated: 2025/02/06 16:18:55 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_clean_up(t_pipex *pipex)
{
	if (pipex->cmd1 != NULL)
		free(pipex->path_cmd1);
	if (pipex->cmd2 != NULL)
		free(pipex->path_cmd2);
	if (pipex->cmd1 != NULL)
		ft_free_split(pipex->cmd1);
	if (pipex->cmd2 != NULL)
		ft_free_split(pipex->cmd2);
}
