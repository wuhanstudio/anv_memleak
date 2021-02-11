# anv_memleak
RT-Thread 软件包，帮助检查内存泄漏。

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

快速定位到哪个文件，哪一行出现了内存泄漏。

    msh />
     \ | /
    - RT -     Thread Operating System
     / | \     4.0.3 build Feb 11 2021
     2006 - 2021 Copyright by rt-thread team
    msh />an
    anv_memleak_example
    msh />anv_memleak_example
    [packages\anv-memleak\anv_memleak_example.c:14] <0x20007c20> malloc(10)

     /=========================\
     |===    Quick Stats    ===|
     |=========================|
     |total alloc:      0000010|
     |total free:       0000000|
     |-------------------------|
     |total leaks:      0000010|
     |                         |
     |total malloc():   0000001|
     |total calloc():   0000000|
     |-------------------------|
     |total free():     0000000|
     |                         |
     |total realloc():  0000000|
     \=========================/

    [total] 10 allocated, 0 freed
    [count] 1 malloc, 0 free
    [count] 0 calloc, 0 realloc

    [total] 1 leaks
    [packages\anv-memleak\anv_memleak_example.c] line 14, 10 bytes
    msh />
