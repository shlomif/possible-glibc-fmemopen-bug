#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "fcs_cl.h"

/* Copyright (c) 2000 Shlomi Fish
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * output_to_file.h - header file for outputting a solution to a file.
 *
 */


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "inline.h"
#include "bool.h"

#include "fcs_enums.h"

struct fc_solve_display_information_context_struct
{
    fcs_bool_t debug_iter_state_output;
    int freecells_num;
    int stacks_num;
    int decks_num;
    fcs_bool_t parseable_output;
    fcs_bool_t canonized_order_output;
    fcs_bool_t display_10_as_t;
    fcs_bool_t display_parent_iter_num;
    fcs_bool_t debug_iter_output_on;
    fcs_bool_t display_moves;
    fcs_bool_t display_states;
    fcs_bool_t show_exceeded_limits;
    int standard_notation;
    const char * output_filename;
};

typedef struct fc_solve_display_information_context_struct fc_solve_display_information_context_t;

static const fc_solve_display_information_context_t INITIAL_DISPLAY_CONTEXT =
(fc_solve_display_information_context_t) {
    .debug_iter_state_output = FALSE,
    .parseable_output = FALSE,
    .canonized_order_output = FALSE,
    .display_10_as_t = FALSE,
    .display_parent_iter_num = FALSE,
    .display_moves = FALSE,
    .display_states = TRUE,
    .standard_notation = FC_SOLVE__STANDARD_NOTATION_NO,
    .output_filename = NULL,
    .show_exceeded_limits = FALSE
};

static GCC_INLINE void fc_solve_output_result_to_file(
    FILE * const output_fh,
    void * const instance,
    const int ret,
    const fc_solve_display_information_context_t * const dc_ptr
)
{
        {
            fcs_move_t move;

            char * as_string;

            int move_num = 0;
            while (
                    freecell_solver_user_get_next_move(
                        instance,
                        &move
                        ) == 0
                  )
            {
                as_string =
                    freecell_solver_user_current_state_as_string(
                        instance,
                        1,
                        0,
                        1
                    );

                fprintf(output_fh, "%s\n", as_string);

                free(as_string);
                fprintf(output_fh, "%s", "\n====================\n\n");
            }

        }

    return;
}

char shlomif_buffer[2000000];
char shlomif_board_buf[500];

static fc_solve_display_information_context_t my_context;

static void * fcs;

int main(int argc, char * argv[])
{
    my_context = INITIAL_DISPLAY_CONTEXT;

    my_context.parseable_output = my_context.display_10_as_t = my_context.show_exceeded_limits = TRUE;

    fcs = freecell_solver_user_alloc();
    const char * const board_str =
"JD KD 2S 4C 3S 6D 6S\n"
"2D KC KS 5C TD 8S 9C\n"
"9H 9S 9D TS 4S 8D 2H\n"
"JC 5S QD QH TH QS 6H\n"
"5D AD JS 4H 8H 6C\n"
"7H QC AS AC 2C 3D\n"
"7C KH AH 4D JH 8C\n"
"5H 3H 3C 7S 7D TC\n";

    const int ret = freecell_solver_user_solve_board(fcs, board_str);
#if 1
    FILE * output_fh = fmemopen(shlomif_buffer, sizeof(shlomif_buffer), "w");
#else
    FILE * output_fh = fopen("foo.txt", "w");
#endif

    #if 1
    fc_solve_output_result_to_file(output_fh, fcs, ret, &my_context);
    #else
    fc_solve_output_result_to_file(stdout, fcs, ret, &my_context);
    #endif

    fclose(output_fh);

    printf("Buffer=\"%s\"\n", shlomif_buffer);
    freecell_solver_user_recycle(fcs);

    return 0;
}