#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"

int flag_i = 0;
int flushperiod = -1;
int policy;
int pgsize = 0;
int tlbsize = 0;
address_node tlb;
int ref_count = 0;
int tlb_count = 0;
int total_ref = 0;
int total_hit = 0;
int total_miss = 0;

void read_argv(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        char temp[20];
        strcpy(temp, argv[i]);
        if (strcmp("-i", temp) == 0)
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
    if (c == EOF)
    {
            printf("%d memory references handled\n%d TLB misses\n%d TLB hits\n",total_ref, total_miss, total_hit);
    destroy(tlb);
        exit(0);
    }
}
void tlb_hit(int page_number)
{
    total_hit++;
}
void tlb_miss(address_node tlb, int page_number)
{
    total_miss++;
    if (tlb_count >= tlbsize)
    {
        remove_first(tlb);
    }
    else
    {
        tlb_count++;
    }
    
    append_node(tlb, page_number);
}

void handle(char ins, char *content)
{
    //printf("ins: %c, address: %s\n",ins,content);
    unsigned int page_number = (int)strtol(content, NULL, 16) / pgsize;

    if (search_node(tlb, page_number, policy))
    {
        tlb_hit(page_number);
    }
    else
    {
        tlb_miss(tlb, page_number);
    }
    ref_count++;
    total_ref++;
    if (ref_count == flushperiod) {
        clear(tlb);
        ref_count = 0;
        tlb_count = 0;
    }
    
//print_all(tlb);
//sleep(3);
    //printf("%d\n", page_number);
}

int main(int argc, char **argv)
{

    read_argv(argc, argv);
    char instruction;
    tlb = create_node();
    while (1)
    {
        scanf(" %s", &instruction);
        if ((!flag_i && instruction == 'I') || instruction == 'S' || instruction == 'L' || instruction == 'M')
        {
            char content[20];
            scanf("%s,", content);
            handle(instruction, content);
            next_line();
        }
        else
        {
            next_line();
        }
    }

}