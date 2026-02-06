#include "./headers/cub3d.h"

void play_sound(t_gen *gen, const char *filename, int loop)
{
    printf("Playing: %s\n", filename);
    t_sound *sounds = &gen->def_values->sounds;

    if (sounds->count >= sounds->capacity)
        return; // too many sounds

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    } 
    else if (pid == 0) {
        char *args[7];
        args[0] = "ffplay";
        args[1] = "-nodisp";
        args[2] = "-autoexit";
        if (loop) {
            args[3] = "-loop";
            args[4] = "0";
            args[5] = (char *)filename;
            args[6] = NULL;
        } else {
            args[3] = (char *)filename;
            args[4] = NULL;
        }
        char *path = "/usr/bin/ffplay";
        execve(path, args, gen->def_values->env);
        perror("execve");
        exit(EXIT_FAILURE);
    } 
    else {
        sounds->pids[sounds->count++] = pid;
    }
}



const char* random_effect() {
    const char *effects[] = {
        "./audio/Come Out and Play With Me.mp3",
        "./audio/Creepy Little Girl Whispering Horror Sounds (HD) (FREE).mp3",
        "./audio/The Last Of Us - Clicker Sound Effect.mp3",
    };
    int n = sizeof(effects) / sizeof(effects[0]);
    return effects[rand() % n];
}

void start_terror_music(t_gen *gen)
{
    t_sound *sounds = &gen->def_values->sounds;

    if (sounds->terror_music_pid > 0)
        return;

    // 1. Play the background theme in the MAIN process
    // This ensures the PID is stored in the gen->sounds structure the game actually uses.
    play_sound(gen, "./audio/Background.mp3", 1);

    // 2. Fork the Scare Manager
    pid_t pid = fork();
    if (pid < 0)
        perror("fork");
    else if (pid == 0)
    {
        // CHILD PROCESS (Scare Manager)
        setpgid(0, 0); 
        srand(time(NULL) ^ getpid()); // Better seed for children
        
        while (1)
        {
            sleep(rand() % 15 + 10); // Give the player some breathing room
            
            // Note: In the child, play_sound will update its LOCAL copy of gen,
            // but that's okay because we kill the whole group later anyway.
            play_sound(gen, random_effect(), 0);
        }
        exit(0);
    }
    else
        sounds->terror_music_pid = pid; 
}


void stop_all_sounds(t_gen *gen)
{
    t_sound *sounds = &gen->def_values->sounds;

    if (sounds->terror_music_pid > 0) {
        kill(-sounds->terror_music_pid, SIGTERM); 
        sounds->terror_music_pid = 0;
    }
    for (int i = 0; i < sounds->count; i++) {
        if (sounds->pids[i] > 0) {
            kill(sounds->pids[i], SIGTERM);
            sounds->pids[i] = 0;
        }
    }
    sounds->count = 0;
}


