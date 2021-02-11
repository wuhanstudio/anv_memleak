#include <rtthread.h>
#include <stdio.h>

#define ANV_LEAKS_IMPLEMENTATION
#include <anv_leaks.h>

int anv_memleak_example(int argc, char const *argv[])
{
    anv_leak_info **leaks;
    size_t leaks_count;

    anv_leaks_init(stdout);

    void *mem = malloc(10);
    anv_leaks_quickpeek();

    // free(mem);
    // anv_leaks_quickpeek();

    anv_leaks_stats stats;
    anv_leaks_get_stats(&stats);

    rt_kprintf("[total] %d allocated, %d freed\n", stats.total_allocated, stats.total_freed);
    rt_kprintf("[count] %d malloc, %d free\n", stats.malloc_count, stats.free_count);
    rt_kprintf("[count] %d calloc, %d realloc\n", stats.calloc_count, stats.realloc_count);

    anv_leaks_get_leaks(&leaks, &leaks_count);

    rt_kprintf("\n");
    rt_kprintf("[total] %d leaks\n", leaks_count);

    for (int i = 0; i < leaks_count; ++i)
    {
        rt_kprintf("[%s] line %d, %d bytes\n", leaks[i]->filename,  leaks[i]->line, leaks[i]->bytes);
    }
    anv_leaks_free_info(leaks, leaks_count);

	return 0;
}
MSH_CMD_EXPORT(anv_memleak_example, anv memleak example);
