#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static inline void fc_solve_output_result_to_file(
    FILE * const output_fh
)
{
    char * as_string;

#include "calls.c"

    return;
}

char shlomif_buffer[2000000];
char shlomif_board_buf[500];

int main(int argc, char * argv[])
{
#if 1
    FILE * output_fh = fmemopen(shlomif_buffer, sizeof(shlomif_buffer), "w");
#else
    FILE * output_fh = fopen("foo.txt", "w");
#endif

#if 1
    fc_solve_output_result_to_file(output_fh);
#else
    fc_solve_output_result_to_file(stdout);
#endif

    fclose(output_fh);

    printf("Buffer=<<<\n%s\n>>>\n", shlomif_buffer);

    return 0;
}
