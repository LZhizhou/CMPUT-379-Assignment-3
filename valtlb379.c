#include <stdio.h>
#include <string.h>

int flag_i = 0;
int flushperiod = 0;
static int FIFO = 1;
static int LRU = 2;
int policy;
int pgsize = 0;
int tlbsize = 0;
void read_argv(int *argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        char temp[20];
        strcpy(temp, argv[i]);
        if (strcmp("-i", temp))
        {
            flag_i = 1;
            continue;
        }
        else if (strcmp("-f", argv[i]) == 0)
        {
            flushperiod = atoi(argv[++i]);
            continue;
        }
        else if (strcmp("-p", argv[i]) == 0)
        {
            if (strcmp("FIFO", argv[i + 1]) == 0)
            {
                policy = FIFO;
                i++;
                continue;
            }
            else if (strcmp("LRU", argv[i + 1]))
            {
                policy = LRU;
                i++;
                continue;
            }
        }
        else if (pgsize == 0)
        {
            pgsize = atoi(argv[i]);
        }
        else
        {
            tlbsize = atoi(argv[i]);
        }
    }
}
void next_line()
{
    int c = getchar();
    while (c != '\n' && c != EOF)
        c = getchar();
}

int main(int *argc, char **argv)
{

    read_argv(argc, argv);
    char instruction;
    char content[20];

    while (1)
    {
        scanf(" %c", instruction);
        if (!flag_i && instruction == 'I' || instruction == 'S' || instruction == 'L' || instruction == 'M')
        {
            
        }
        else
        {
            next_line();
        }
    }
}