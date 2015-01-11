#include "akh.h"

void print_board(t_board *pos) {

	int sq, file, rank, piece;

	printf("\n");
	for(rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d  ", rank + 1);
		for(file = FILE_A; file <= FILE_H; file++) {
			sq = FRTOSQ(file,rank);
			piece = pos->pieces[sq];
			printf("%3c", PceChar[piece]);
		}
		printf("\n");
	}

	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; file++) {
		printf("%3c", 'a' + file);
	}
	printf("\n\n");
}

void board_init(t_board *pos)
{
	int index = 0;

	for(index = 0; index < 120; ++index) {
		pos->pieces[index] = OFFBOARD;
	}

	for(index = 0; index < 64; ++index) {
		pos->pieces[SQ120(index)] = EMPTY;
	}

	for(index = 0; index < 13; ++index) {
		pos->pceNum[index] = 0;
	}

	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

	pos->side = BOTH;

	pos->history_count = 0;
}

