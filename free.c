/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:01:05 by vsoulas           #+#    #+#             */
/*   Updated: 2025/02/07 16:36:09 by vsoulas          ###   ########.fr       */
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
	if (pipex->path_cmd1 != NULL)
		free(pipex->path_cmd1);
	if (pipex->path_cmd2 != NULL)
		free(pipex->path_cmd2);
	if (pipex->cmd1 != NULL)
		ft_free_split(pipex->cmd1);
	if (pipex->cmd2 != NULL)
		ft_free_split(pipex->cmd2);
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
}

// getenv() gives string with all possible directories separated with :
// example = /usr/bin:/bin:/usr/bin/local
// paths get all the directories paths by spltiting path_env in a 2D array
// run through each paths joining the path given to the cmd given
// checks if files/cmd is valid
// if nothing checks in, free variables and return NULL
char	*get_env_path(char *cmd, char **envp, t_pipex *pipex)
{
	char	*temp;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	paths = ft_split(ft_find_path(envp), ':');
	if (paths == NULL)
		return (ft_clean_up(pipex), NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
			return (ft_free_split(paths), ft_clean_up(pipex), NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (full_path == NULL)
			return (ft_free_split(paths), ft_clean_up(pipex), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
		i++;
	}
	ft_printf("%s: command not found\n", cmd);
	return (ft_free_split(paths), NULL);
}
