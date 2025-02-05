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
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
}
