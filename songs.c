/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   songs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:32:50 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 20:05:21 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

static void exec_sound(t_gen *gen, const char *filename)
{
    char *args[3];
    char *path = "/usr/bin/paplay";

    args[0] = "paplay";
    args[1] = (char *)filename;
    args[2] = NULL;

    execve(path, args, gen->def_values->env);
    perror("execve");
    exit(EXIT_FAILURE);
}

void play_sound(t_gen *gen, const char *filename)
{
    t_sound *sounds = &gen->def_values->sounds;
    if (sounds->count >= sounds->capacity)
        return;

    pid_t pid = fork();
    if (pid == 0)
    {
        // Join terror group if active (for clean group kill later)
        if (sounds->terror_music_pid > 0)
            setpgid(0, sounds->terror_music_pid);

        exec_sound(gen, filename);
        // unreachable
    }
    else if (pid > 0)
        sounds->pids[sounds->count++] = pid;
}

void play_looped_background(t_gen *gen, const char *filename, int is_terror)
{
    t_sound *sounds = &gen->def_values->sounds;

    // Stop any existing background first
    if (sounds->background_music_pid > 0)
    {
        kill(sounds->background_music_pid, SIGKILL);
        // waitpid(sounds->background_music_pid, NULL, 0); // optional, but safer
        sounds->background_music_pid = 0;
    }

    pid_t supervisor_pid = fork();
    if (supervisor_pid < 0)
    {
        perror("fork background");
        return;
    }

    if (supervisor_pid == 0)  // supervisor child
    {
        // For terror: put everything in same group
        if (is_terror)
        {
            setpgid(0, 0);  // new group, or join existing if you prefer
        }

        while (1)
        {
            pid_t play_pid = fork();
            if (play_pid == 0)  // player grandchild
            {
                if (is_terror)
                    setpgid(0, getpgid(getpid()));  // ensure in group

                exec_sound(gen, filename);
                perror("execve background");
                exit(1);
            }
            else if (play_pid > 0)
            {
                waitpid(play_pid, NULL, 0);  // wait → when ends → loop restarts
            }
            else
            {
                perror("fork play");
                break;
            }
        }
        exit(0);
    }
    else  // parent
    {
        sounds->background_music_pid = supervisor_pid;

        if (is_terror)
        {
            sounds->terror_music_pid = supervisor_pid;  // reuse or keep separate
            setpgid(supervisor_pid, supervisor_pid);   // parent sets group leader
        }
    }
}

const char	*random_effect(void)
{
	int			n;
	const char	*effects[] = {
		"./audio/Come Out and Play With Me.ogg",
		"./audio/Creepy Little Girl Whispering Horror Sounds (HD) (FREE).ogg",
		"./audio/The Last Of Us - Clicker Sound Effect.ogg",
	};

	n = sizeof(effects) / sizeof(effects[0]);
	return (effects[rand() % n]);
}

void start_terror_music(t_gen *gen)
{
    t_sound *sounds = &gen->def_values->sounds;
    if (sounds->background_music_pid > 0)  // or check terror flag
        return;

    // Optional: stop default first
    stop_all_sounds(gen);

    play_looped_background(gen, "./audio/Background.ogg", 1);  // is_terror = true

    // Now the random effects loop in the same supervisor or separate
    // Simplest: fork another child for randoms
    pid_t effects_pid = fork();
    if (effects_pid == 0)
    {
        if (sounds->background_music_pid > 0)
            setpgid(0, sounds->background_music_pid);  // join group

        srand(time(NULL) ^ getpid());
        while (1)
        {
            sleep(rand() % 15 + 10);
            play_sound(gen, random_effect());  // non-looped
        }
        exit(0);
    }
    // Optional: track effects_pid too if needed
}

void stop_all_sounds(t_gen *gen)
{
    t_sound *sounds = &gen->def_values->sounds;

    // Kill background supervisor (default or terror)
    if (sounds->background_music_pid > 0)
    {
        kill(sounds->background_music_pid, SIGTERM);  // kinder
        usleep(100000);
        kill(sounds->background_music_pid, SIGKILL);
        // waitpid(sounds->background_music_pid, NULL, 0); // optional
        sounds->background_music_pid = 0;
    }

    // Kill terror group if separate
    if (sounds->terror_music_pid > 0 && sounds->terror_music_pid != sounds->background_music_pid)
    {
        kill(-sounds->terror_music_pid, SIGKILL);
        sounds->terror_music_pid = 0;
    }

    // Kill any stray one-shots
    for (int i = 0; i < sounds->count; i++)
    {
        if (sounds->pids[i] > 0)
        {
            kill(sounds->pids[i], SIGKILL);
        }
    }
    sounds->count = 0;

    // Safety net (your current pkill)
    pid_t pk = fork();
    if (pk == 0)
    {
        char *args[] = {"pkill", "-u", getenv("USER"), "-x", "paplay", NULL};
        execvp("pkill", args);
        exit(1);
    }
    if (pk > 0) waitpid(pk, NULL, 0);
}
