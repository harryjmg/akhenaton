#include "akh.h"

static void print_welcome(void)
{
	printf("\n");
	printf("=====---                    ---=====\n");
	printf("===--         AKHENATON        --===\n");
	printf("=====---                    ---=====\n\n");
}

# define ONE "6k1/1r2Rpp1/7p/8/8/8/2R2PPP/rB4K1 w 1" // OK
# define ONE2 "8/8/8/5k2/2Q2P2/5P2/3K4/8 w 1" // OK
# define ONE3 "8/8/5R1r/1n2K1k1/7p/8/4BP2/8 w 1" // OK
# define ONE4 "2r4k/1r4pp/8/4N3/2B5/1p5R/1K6/8 w 1" // OK
# define ONE4MIRROR "8/1k6/1P5r/2b5/4n3/8/1R4PP/2R4K b 1" // OK


# define TWO "6k1/P1R2ppp/b7/8/8/7P/2r2PPK/r7 w 2" // OK
# define TWO2 "8/1P6/8/8/8/8/5K2/7k w 2" // OK ! Ven 9 Janvier
# define TWO3 "6k1/5p2/p4K2/8/2N5/8/8/7R w 2" // OK
# define TWO4 "r1b4k/pp4pp/2p4n/8/3b3N/6P1/PP3PK1/4R2R w 2" // OK
# define TWO5 "3n4/6K1/5R1r/6k1/7p/6pP/5P2/8 w 2" // OK

# define THREE "6bk/7p/6pQ/1p1p1pN1/p2P4/P1P5/1P2qPK1/8 w 3" // Ok
# define THREE2 "8/8/8/5K1k/6R1/8/8/8 w 3" // pareil
# define THREE3 "2kb4/4P3/2K5/8/5B2/8/8/8 w 3" // pareil

# define FOUR "8/1Q1K4/1B6/1k6/6p1/2P4p/1P6/8 w 4"


int main(void)
{
	t_board board[1];
	char *str;

	// Bonjour.
	print_welcome();
	// On recupere le problème
	str = NULL;
	if (get_fen(&str) != 0)
		return (1);
	// On lance la machine
	all_init();
	// On parse le problème
	if (parse_fen(board, str) != 0)
		return (1);
	// On affiche le plateau
	print_board(board);
	// On cherche la solution
	search_soluce(board);
	return (0);

}