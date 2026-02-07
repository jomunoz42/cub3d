#include "./headers/cub3d.h"

void	play_sound(t_gen *gen, const char *filename, int loop)
{
	t_sound	*sounds;
	pid_t	pid;
		char *args[7];
	char	*path;

	printf("Playing: %s\n", filename);
	sounds = &gen->def_values->sounds;
	if (sounds->count >= sounds->capacity)
		return ; // too many sounds
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		args[0] = "ffplay";
		args[1] = "-nodisp";
		args[2] = "-autoexit";
		if (loop)
		{
			args[3] = "-loop";
			args[4] = "0";
			args[5] = (char *)filename;
			args[6] = NULL;
		}
		else
		{
			args[3] = (char *)filename;
			args[4] = NULL;
		}
		path = "/usr/bin/ffplay";
		execve(path, args, gen->def_values->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		sounds->pids[sounds->count++] = pid;
	}
}

const char	*random_effect(void)
{
	int	n;

	const char *effects[] = {
		"./audio/Come Out and Play With Me.mp3",
		"./audio/Creepy Little Girl Whispering Horror Sounds (HD) (FREE).mp3",
		"./audio/The Last Of Us - Clicker Sound Effect.mp3",
	};
	n = sizeof(effects) / sizeof(effects[0]);
	return (effects[rand() % n]);
}

void	start_terror_music(t_gen *gen)
{
	t_sound	*sounds;
	pid_t	pid;

	sounds = &gen->def_values->sounds;
	if (sounds->terror_music_pid > 0)
		return ;
	play_sound(gen, "./audio/Background.mp3", 1);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		setpgid(0, 0);
		srand(time(NULL) ^ getpid());
		while (1)
		{
			sleep(rand() % 15 + 10);
			play_sound(gen, random_effect(), 0);
		}
		exit(0);
	}
	else
		sounds->terror_music_pid = pid;
}

void	stop_all_sounds(t_gen *gen)
{
	t_sound	*sounds;

	sounds = &gen->def_values->sounds;
	if (sounds->terror_music_pid > 0)
	{
		kill(-sounds->terror_music_pid, SIGTERM);
		sounds->terror_music_pid = 0;
	}
	for (int i = 0; i < sounds->count; i++)
	{
		if (sounds->pids[i] > 0)
		{
			kill(sounds->pids[i], SIGTERM);
			sounds->pids[i] = 0;
		}
	}
	sounds->count = 0;
}
