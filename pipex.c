/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:09:47 by vsoulas           #+#    #+#             */
/*   Updated: 2025/01/24 17:04:18 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex infile "ls -l" "wc -l" outfile
// < infile ls -l | wc -l > outfile
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		perror("Error: Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	initial_struct(argv, &pipex);
	ft_check_args_cmd1(&pipex, envp);
	ft_check_args_cmd2(&pipex, envp);
	ft_create_pipe(&pipex);
	ft_create_fork(&pipex, envp);
	ft_clean_up(&pipex);
	return (EXIT_SUCCESS);
}

// split the arguments into command(s) and argument(s)
// check if the command is found and executable with access()
// find the path of the command

/* write perror messaged and exit failure */
void	ft_check_args_cmd1(t_pipex *pipex, char **envp)
{
	pipex->cmd1 = ft_split(pipex->arg1, ' ');
	if (pipex->cmd1 == NULL)
		ft_free_split(pipex->cmd1);
	if (access(pipex->cmd1[0], F_OK | X_OK) == 0)
	{
		pipex->path_cmd1 = ft_strdup(pipex->cmd1[0]);
		if (pipex->path_cmd1 == NULL)
			ft_free_split(pipex->cmd1);
	}
	else
	{
		pipex->path_cmd1 = get_env_path(pipex->cmd1[0], envp, pipex);
		if (pipex->path_cmd1 == NULL)
			ft_free_split(pipex->cmd1);
	}
}

/* write perror messaged and exit failure */
void	ft_check_args_cmd2(t_pipex *pipex, char **envp)
{
	pipex->cmd2 = ft_split(pipex->arg2, ' ');
	if (pipex->cmd2 == NULL)
		ft_clean_up(pipex);
	if (access(pipex->cmd2[0], F_OK | X_OK) == 0)
	{
		pipex->path_cmd2 = ft_strdup(pipex->cmd2[0]);
		if (pipex->path_cmd2 == NULL)
			ft_clean_up(pipex);
	}
	else
	{
		pipex->path_cmd2 = get_env_path(pipex->cmd2[0], envp, pipex);
		if (pipex->cmd2 == NULL)
			ft_clean_up(pipex);
	}
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
	{
		ft_free_split(paths);
		ft_clean_up(pipex);
		return (perror("Error: Could not split PATH environment variable"), NULL);
	}
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
		{
// add exit
			ft_free_split(paths);
			ft_clean_up(pipex);
		}
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (full_path == NULL)
		{
// add exit
			ft_free_split(paths);
			ft_clean_up(pipex);
		}
		if (access(full_path, F_OK | X_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
		i++;
	}
	perror("Error: command not found in PATH\n");
	return (ft_free_split(paths), NULL);
}

// fork first child process and check for errors
// if first child1 succeded: call ft_child1
// execute commade
// if child2 succeded: call ft_child2;
void	ft_create_fork(t_pipex *pipex, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		ft_clean_up(pipex);
		perror("Couldn't fork pid1\n");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		ft_child1(pipex, envp);
	pid2 = fork();
	if (pid2 == -1)
	{
		ft_clean_up(pipex);
		perror("Couldn't fork pid2\n");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		ft_child2(pipex, envp);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
