#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "gamma.h"
#include <stdbool.h>
#include <string.h>


int main() {

/*
scenario: test_random_actions
uuid: 714108935
*/
/*
random actions, total chaos
*/
gamma_t* board = gamma_new(10, 9, 5, 10);
assert( board != NULL );


assert( gamma_move(board, 1, 7, 1) == 1 );
assert( gamma_move(board, 2, 6, 1) == 1 );
assert( gamma_move(board, 3, 6, 5) == 1 );
assert( gamma_move(board, 5, 9, 0) == 1 );
assert( gamma_golden_possible(board, 5) == 1 );
assert( gamma_move(board, 1, 8, 9) == 0 );
assert( gamma_move(board, 2, 6, 7) == 1 );
assert( gamma_golden_possible(board, 2) == 1 );
assert( gamma_move(board, 3, 5, 6) == 1 );
assert( gamma_move(board, 3, 8, 7) == 1 );
assert( gamma_move(board, 4, 4, 3) == 1 );
assert( gamma_free_fields(board, 4) == 82 );
assert( gamma_move(board, 5, 4, 2) == 1 );
assert( gamma_move(board, 5, 0, 6) == 1 );
assert( gamma_move(board, 1, 7, 9) == 0 );
assert( gamma_move(board, 1, 2, 3) == 1 );
assert( gamma_golden_possible(board, 1) == 1 );
assert( gamma_move(board, 3, 8, 1) == 1 );
assert( gamma_move(board, 3, 6, 6) == 1 );
assert( gamma_move(board, 4, 1, 2) == 1 );
assert( gamma_move(board, 4, 7, 5) == 1 );
assert( gamma_move(board, 5, 4, 2) == 0 );
assert( gamma_move(board, 1, 4, 4) == 1 );
assert( gamma_move(board, 1, 9, 5) == 1 );
assert( gamma_move(board, 2, 8, 5) == 1 );
assert( gamma_move(board, 3, 4, 7) == 1 );
assert( gamma_move(board, 3, 8, 5) == 0 );
assert( gamma_move(board, 4, 3, 9) == 0 );


char* board742856733 = gamma_board(board);
assert( board742856733 != NULL );
assert( strcmp(board742856733, 
"..........\n"
"....3.2.3.\n"
"5....33...\n"
"......3421\n"
"....1.....\n"
"..1.4.....\n"
".4..5.....\n"
"......213.\n"
".........5\n") == 0);
free(board742856733);
board742856733 = NULL;
assert( gamma_move(board, 5, 6, 3) == 1 );
assert( gamma_move(board, 1, 3, 2) == 1 );
assert( gamma_move(board, 1, 8, 5) == 0 );
assert( gamma_free_fields(board, 2) == 69 );
assert( gamma_move(board, 3, 2, 3) == 0 );
assert( gamma_move(board, 3, 5, 7) == 1 );
assert( gamma_move(board, 4, 1, 3) == 1 );
assert( gamma_move(board, 4, 9, 1) == 1 );
assert( gamma_move(board, 5, 8, 6) == 1 );
assert( gamma_move(board, 5, 2, 3) == 0 );
assert( gamma_move(board, 1, 2, 3) == 0 );
assert( gamma_golden_move(board, 1, 2, 4) == 0 );
assert( gamma_move(board, 2, 5, 2) == 1 );
assert( gamma_move(board, 2, 7, 8) == 1 );
assert( gamma_move(board, 3, 0, 8) == 1 );
assert( gamma_busy_fields(board, 3) == 8 );
assert( gamma_move(board, 4, 0, 6) == 0 );
assert( gamma_move(board, 4, 1, 7) == 1 );
assert( gamma_move(board, 5, 0, 1) == 1 );
assert( gamma_move(board, 1, 5, 1) == 1 );
assert( gamma_move(board, 1, 0, 8) == 0 );
assert( gamma_move(board, 2, 7, 2) == 1 );
assert( gamma_move(board, 2, 3, 4) == 1 );
assert( gamma_golden_possible(board, 2) == 1 );
assert( gamma_move(board, 3, 8, 6) == 0 );
assert( gamma_move(board, 3, 3, 4) == 0 );
assert( gamma_move(board, 4, 5, 5) == 1 );
assert( gamma_move(board, 4, 4, 7) == 0 );
assert( gamma_golden_possible(board, 4) == 1 );
assert( gamma_move(board, 5, 5, 1) == 0 );
assert( gamma_busy_fields(board, 5) == 6 );
assert( gamma_move(board, 1, 9, 8) == 1 );
assert( gamma_move(board, 1, 0, 0) == 1 );
assert( gamma_move(board, 2, 2, 9) == 0 );
assert( gamma_move(board, 2, 6, 1) == 0 );
assert( gamma_move(board, 3, 2, 9) == 0 );
assert( gamma_move(board, 4, 1, 0) == 1 );
assert( gamma_free_fields(board, 4) == 53 );
assert( gamma_move(board, 5, 5, 0) == 1 );
assert( gamma_move(board, 5, 9, 2) == 1 );
assert( gamma_move(board, 1, 7, 0) == 1 );
assert( gamma_move(board, 2, 7, 6) == 1 );
assert( gamma_move(board, 2, 9, 6) == 1 );
assert( gamma_busy_fields(board, 2) == 9 );
assert( gamma_golden_possible(board, 2) == 1 );
assert( gamma_move(board, 3, 4, 2) == 0 );
assert( gamma_move(board, 3, 3, 7) == 1 );
assert( gamma_move(board, 5, 6, 3) == 0 );
assert( gamma_free_fields(board, 5) == 47 );


char* board829206218 = gamma_board(board);
assert( board829206218 != NULL );
assert( strcmp(board829206218, 
"3......2.1\n"
".4.3332.3.\n"
"5....33252\n"
".....43421\n"
"...21.....\n"
".41.4.5...\n"
".4.152.2.5\n"
"5....12134\n"
"14...5.1.5\n") == 0);
free(board829206218);
board829206218 = NULL;
assert( gamma_move(board, 1, 0, 4) == 1 );
assert( gamma_busy_fields(board, 1) == 10 );
assert( gamma_move(board, 2, 1, 8) == 1 );
assert( gamma_move(board, 3, 7, 9) == 0 );
assert( gamma_move(board, 4, 6, 2) == 1 );
assert( gamma_move(board, 4, 5, 0) == 0 );
assert( gamma_move(board, 5, 4, 5) == 1 );
assert( gamma_busy_fields(board, 5) == 9 );
assert( gamma_golden_possible(board, 5) == 1 );
assert( gamma_move(board, 1, 8, 5) == 0 );
assert( gamma_move(board, 2, 3, 1) == 0 );
assert( gamma_move(board, 2, 8, 1) == 0 );
assert( gamma_move(board, 3, 0, 5) == 1 );
assert( gamma_golden_possible(board, 3) == 1 );
assert( gamma_move(board, 4, 6, 0) == 1 );
assert( gamma_busy_fields(board, 4) == 10 );
assert( gamma_golden_possible(board, 4) == 1 );
assert( gamma_move(board, 5, 6, 3) == 0 );
assert( gamma_free_fields(board, 5) == 41 );
assert( gamma_move(board, 1, 0, 2) == 1 );
assert( gamma_move(board, 1, 8, 3) == 0 );
assert( gamma_move(board, 2, 0, 3) == 0 );
assert( gamma_busy_fields(board, 3) == 10 );
assert( gamma_golden_possible(board, 3) == 1 );
assert( gamma_move(board, 4, 9, 5) == 0 );
assert( gamma_move(board, 4, 3, 8) == 1 );
assert( gamma_move(board, 5, 9, 1) == 0 );
assert( gamma_move(board, 1, 0, 3) == 1 );
assert( gamma_move(board, 2, 7, 7) == 1 );
assert( gamma_move(board, 2, 2, 6) == 1 );
assert( gamma_move(board, 3, 6, 4) == 1 );
assert( gamma_move(board, 3, 4, 7) == 0 );
assert( gamma_move(board, 4, 0, 7) == 1 );
assert( gamma_golden_possible(board, 4) == 1 );
assert( gamma_move(board, 5, 0, 5) == 0 );
assert( gamma_move(board, 5, 6, 1) == 0 );
assert( gamma_move(board, 1, 8, 4) == 1 );
assert( gamma_busy_fields(board, 1) == 13 );
assert( gamma_free_fields(board, 1) == 13 );
assert( gamma_move(board, 2, 4, 5) == 0 );
assert( gamma_move(board, 3, 8, 5) == 0 );
assert( gamma_golden_possible(board, 3) == 1 );
assert( gamma_move(board, 4, 6, 3) == 0 );
assert( gamma_move(board, 5, 6, 3) == 0 );
assert( gamma_move(board, 1, 5, 3) == 0 );
assert( gamma_golden_move(board, 1, 1, 8) == 0 );
assert( gamma_move(board, 2, 8, 2) == 1 );
assert( gamma_move(board, 2, 4, 4) == 0 );
assert( gamma_move(board, 3, 3, 5) == 1 );
assert( gamma_golden_move(board, 3, 7, 6) == 1 );
assert( gamma_move(board, 4, 8, 4) == 0 );
assert( gamma_move(board, 4, 5, 5) == 0 );
assert( gamma_move(board, 5, 1, 2) == 0 );
assert( gamma_move(board, 1, 0, 3) == 0 );
assert( gamma_move(board, 2, 0, 8) == 0 );
assert( gamma_move(board, 2, 5, 1) == 0 );
assert( gamma_free_fields(board, 2) == 31 );
assert( gamma_golden_move(board, 2, 2, 3) == 1 );
assert( gamma_move(board, 3, 7, 8) == 0 );
assert( gamma_move(board, 3, 1, 3) == 0 );
assert( gamma_free_fields(board, 3) == 31 );


char* board994642395 = gamma_board(board);
assert( board994642395 != NULL );
assert( strcmp(board994642395, 
"32.4...2.1\n"
"44.333223.\n"
"5.2..33352\n"
"3..3543421\n"
"1..21.3.1.\n"
"142.4.5...\n"
"14.1524225\n"
"5....12134\n"
"14...541.5\n") == 0);
free(board994642395);
board994642395 = NULL;
assert( gamma_move(board, 4, 2, 2) == 1 );
assert( gamma_free_fields(board, 4) == 12 );
assert( gamma_move(board, 5, 9, 2) == 0 );
assert( gamma_move(board, 5, 0, 2) == 0 );
assert( gamma_busy_fields(board, 1) == 12 );
assert( gamma_move(board, 2, 5, 2) == 0 );
assert( gamma_move(board, 2, 3, 6) == 1 );


char* board515040835 = gamma_board(board);
assert( board515040835 != NULL );
assert( strcmp(board515040835, 
"32.4...2.1\n"
"44.333223.\n"
"5.22.33352\n"
"3..3543421\n"
"1..21.3.1.\n"
"142.4.5...\n"
"1441524225\n"
"5....12134\n"
"14...541.5\n") == 0);
free(board515040835);
board515040835 = NULL;
assert( gamma_move(board, 3, 7, 1) == 0 );
assert( gamma_move(board, 3, 8, 3) == 1 );
assert( gamma_free_fields(board, 3) == 28 );
assert( gamma_move(board, 4, 3, 7) == 0 );
assert( gamma_move(board, 4, 0, 5) == 0 );
assert( gamma_move(board, 5, 3, 5) == 0 );
assert( gamma_move(board, 1, 9, 0) == 0 );
assert( gamma_move(board, 2, 4, 9) == 0 );
assert( gamma_free_fields(board, 2) == 12 );
assert( gamma_golden_possible(board, 2) == 0 );
assert( gamma_busy_fields(board, 3) == 14 );
assert( gamma_golden_possible(board, 3) == 0 );
assert( gamma_move(board, 4, 4, 2) == 0 );
assert( gamma_move(board, 4, 4, 3) == 0 );
assert( gamma_move(board, 5, 8, 1) == 0 );
assert( gamma_move(board, 1, 3, 0) == 1 );
assert( gamma_golden_possible(board, 1) == 1 );
assert( gamma_move(board, 2, 4, 7) == 0 );
assert( gamma_move(board, 3, 8, 8) == 1 );
assert( gamma_move(board, 3, 8, 4) == 0 );
assert( gamma_busy_fields(board, 3) == 15 );
assert( gamma_move(board, 4, 5, 1) == 0 );
assert( gamma_golden_move(board, 4, 0, 5) == 0 );
assert( gamma_move(board, 2, 8, 2) == 0 );
assert( gamma_golden_move(board, 2, 6, 8) == 0 );
assert( gamma_move(board, 3, 0, 8) == 0 );
assert( gamma_golden_possible(board, 3) == 0 );
assert( gamma_move(board, 4, 4, 5) == 0 );
assert( gamma_move(board, 4, 4, 3) == 0 );
assert( gamma_move(board, 1, 3, 7) == 0 );
assert( gamma_move(board, 1, 4, 2) == 0 );
assert( gamma_free_fields(board, 1) == 11 );
assert( gamma_golden_move(board, 1, 1, 8) == 0 );
assert( gamma_move(board, 2, 6, 8) == 1 );
assert( gamma_move(board, 2, 4, 2) == 0 );
assert( gamma_move(board, 4, 1, 2) == 0 );
assert( gamma_move(board, 5, 9, 8) == 0 );
assert( gamma_move(board, 5, 5, 8) == 1 );
assert( gamma_move(board, 1, 1, 0) == 0 );
assert( gamma_move(board, 2, 7, 9) == 0 );
assert( gamma_move(board, 2, 6, 8) == 0 );
assert( gamma_move(board, 3, 5, 1) == 0 );
assert( gamma_move(board, 3, 0, 2) == 0 );
assert( gamma_move(board, 4, 6, 1) == 0 );
assert( gamma_move(board, 4, 9, 0) == 0 );
assert( gamma_move(board, 5, 2, 3) == 0 );
assert( gamma_busy_fields(board, 5) == 10 );
assert( gamma_move(board, 1, 6, 4) == 0 );
assert( gamma_move(board, 2, 6, 1) == 0 );
assert( gamma_move(board, 3, 3, 7) == 0 );
assert( gamma_move(board, 3, 0, 5) == 0 );
assert( gamma_move(board, 4, 6, 4) == 0 );
assert( gamma_move(board, 4, 6, 8) == 0 );
assert( gamma_golden_possible(board, 4) == 1 );
assert( gamma_golden_move(board, 4, 0, 5) == 0 );
assert( gamma_move(board, 5, 7, 2) == 0 );
assert( gamma_move(board, 2, 1, 1) == 0 );
assert( gamma_move(board, 2, 6, 1) == 0 );
assert( gamma_move(board, 3, 6, 1) == 0 );
assert( gamma_busy_fields(board, 3) == 15 );
assert( gamma_move(board, 4, 1, 4) == 1 );
assert( gamma_move(board, 4, 4, 4) == 0 );
assert( gamma_move(board, 5, 0, 2) == 0 );
assert( gamma_golden_move(board, 5, 0, 6) == 0 );
assert( gamma_move(board, 1, 5, 0) == 0 );
assert( gamma_move(board, 1, 5, 5) == 0 );
assert( gamma_golden_move(board, 1, 3, 7) == 0 );
assert( gamma_move(board, 2, 1, 1) == 0 );
assert( gamma_golden_move(board, 2, 4, 0) == 0 );
assert( gamma_move(board, 3, 8, 6) == 0 );
assert( gamma_move(board, 3, 4, 8) == 1 );
assert( gamma_move(board, 4, 4, 9) == 0 );
assert( gamma_move(board, 1, 5, 1) == 0 );
assert( gamma_free_fields(board, 1) == 10 );
assert( gamma_move(board, 2, 6, 0) == 0 );
assert( gamma_move(board, 3, 7, 8) == 0 );
assert( gamma_move(board, 3, 1, 0) == 0 );
assert( gamma_move(board, 4, 6, 2) == 0 );
assert( gamma_busy_fields(board, 5) == 10 );
assert( gamma_free_fields(board, 5) == 9 );
assert( gamma_move(board, 1, 3, 7) == 0 );
assert( gamma_move(board, 1, 6, 3) == 0 );
assert( gamma_move(board, 2, 0, 8) == 0 );
assert( gamma_move(board, 2, 6, 5) == 0 );
assert( gamma_move(board, 3, 9, 3) == 1 );
assert( gamma_move(board, 4, 6, 4) == 0 );
assert( gamma_move(board, 5, 7, 6) == 0 );
assert( gamma_move(board, 1, 4, 2) == 0 );
assert( gamma_move(board, 1, 2, 6) == 0 );
assert( gamma_move(board, 2, 6, 4) == 0 );
assert( gamma_move(board, 2, 2, 8) == 1 );
assert( gamma_move(board, 3, 6, 7) == 0 );
assert( gamma_move(board, 3, 4, 4) == 0 );
assert( gamma_golden_possible(board, 3) == 0 );
assert( gamma_move(board, 4, 5, 1) == 0 );
assert( gamma_move(board, 4, 3, 2) == 0 );
assert( gamma_move(board, 5, 4, 7) == 0 );


char* board160074957 = gamma_board(board);
assert( board160074957 != NULL );
assert( strcmp(board160074957, 
"3224352231\n"
"44.333223.\n"
"5.22.33352\n"
"3..3543421\n"
"14.21.3.1.\n"
"142.4.5.33\n"
"1441524225\n"
"5....12134\n"
"14.1.541.5\n") == 0);
free(board160074957);
board160074957 = NULL;
assert( gamma_move(board, 1, 0, 6) == 0 );
assert( gamma_move(board, 2, 4, 5) == 0 );
assert( gamma_move(board, 2, 0, 6) == 0 );
assert( gamma_free_fields(board, 2) == 9 );
assert( gamma_move(board, 3, 0, 8) == 0 );
assert( gamma_move(board, 4, 7, 8) == 0 );
assert( gamma_move(board, 4, 5, 3) == 1 );
assert( gamma_free_fields(board, 4) == 10 );
assert( gamma_move(board, 5, 4, 2) == 0 );
assert( gamma_move(board, 5, 2, 2) == 0 );
assert( gamma_move(board, 2, 8, 4) == 0 );
assert( gamma_move(board, 2, 7, 1) == 0 );
assert( gamma_move(board, 3, 5, 8) == 0 );
assert( gamma_move(board, 3, 5, 5) == 0 );
assert( gamma_golden_possible(board, 3) == 0 );
assert( gamma_move(board, 4, 0, 1) == 0 );
assert( gamma_move(board, 5, 4, 5) == 0 );
assert( gamma_busy_fields(board, 5) == 10 );
assert( gamma_move(board, 1, 7, 9) == 0 );
assert( gamma_move(board, 1, 3, 6) == 0 );
assert( gamma_move(board, 2, 6, 1) == 0 );
assert( gamma_move(board, 3, 4, 5) == 0 );
assert( gamma_move(board, 4, 6, 4) == 0 );
assert( gamma_move(board, 5, 0, 2) == 0 );
assert( gamma_move(board, 1, 7, 9) == 0 );
assert( gamma_move(board, 1, 6, 4) == 0 );
assert( gamma_free_fields(board, 1) == 10 );
assert( gamma_move(board, 2, 0, 2) == 0 );
assert( gamma_move(board, 2, 2, 0) == 0 );
assert( gamma_move(board, 3, 5, 2) == 0 );
assert( gamma_move(board, 4, 4, 3) == 0 );
assert( gamma_move(board, 4, 3, 2) == 0 );
assert( gamma_move(board, 5, 6, 1) == 0 );
assert( gamma_move(board, 1, 0, 4) == 0 );
assert( gamma_golden_move(board, 1, 2, 8) == 0 );
assert( gamma_move(board, 2, 8, 7) == 0 );
assert( gamma_move(board, 2, 6, 1) == 0 );
assert( gamma_golden_possible(board, 2) == 0 );
assert( gamma_move(board, 3, 7, 2) == 0 );
assert( gamma_move(board, 4, 4, 2) == 0 );
assert( gamma_golden_possible(board, 4) == 1 );
assert( gamma_move(board, 5, 7, 2) == 0 );
assert( gamma_move(board, 5, 9, 3) == 0 );
assert( gamma_move(board, 1, 4, 8) == 0 );
assert( gamma_move(board, 2, 0, 6) == 0 );
assert( gamma_move(board, 2, 3, 7) == 0 );
assert( gamma_move(board, 3, 5, 1) == 0 );
assert( gamma_move(board, 4, 0, 2) == 0 );
assert( gamma_free_fields(board, 4) == 10 );
assert( gamma_move(board, 1, 0, 2) == 0 );
assert( gamma_move(board, 1, 2, 1) == 0 );
assert( gamma_move(board, 2, 5, 1) == 0 );
assert( gamma_move(board, 3, 6, 8) == 0 );
assert( gamma_move(board, 4, 0, 3) == 0 );
assert( gamma_move(board, 4, 6, 7) == 0 );
assert( gamma_move(board, 1, 7, 9) == 0 );
assert( gamma_move(board, 1, 8, 6) == 0 );
assert( gamma_golden_move(board, 1, 3, 8) == 0 );
assert( gamma_move(board, 2, 4, 5) == 0 );
assert( gamma_move(board, 3, 0, 2) == 0 );
assert( gamma_move(board, 4, 7, 1) == 0 );
assert( gamma_move(board, 5, 4, 2) == 0 );


gamma_delete(board);

    return 0;
}
