#include "akh.h"

int get_fen(char **str_fen)
{
	size_t linecap;
	ssize_t linelen;

	*str_fen = malloc(sizeof(char) * 100);
	linecap = 0;
	printf("Please enter a chess problem :\n");
	linelen = getline(&(*str_fen), &linecap, stdin);
	if (linelen < 10)
		return (1);
	return (0);
}

void update_pieceslist(t_board *pos)
{
	int piece,sq,index,colour;

	for (index = 0; index < 13; ++index)
		pos->pceNum[index] = 0;

	pos->KingSq[WHITE] = NO_SQ;
	pos->KingSq[BLACK] = NO_SQ;

	for (index = 0; index < 120; ++index) {
		sq = index;
		piece = pos->pieces[index];

		ASSERT(PceValidEmptyOffbrd(piece));

		if (piece != OFFBOARD && piece!= EMPTY) {
			colour = PieceCol[piece];

			ASSERT(SideValid(colour));
			ASSERT(pos->pceNum[piece] < 10);
			ASSERT(pos->pceNum[piece] >= 0);

			pos->pList[piece][pos->pceNum[piece]] = sq;
			pos->pceNum[piece]++;

			if (piece == wK) pos->KingSq[WHITE] = sq;
			if (piece == bK) pos->KingSq[BLACK] = sq;
		}
	}
}

int parse_fen(t_board *pos, char *str_fen)
{
	int 	i;
	int 	rank;
	int 	file;
	int 	piece;
	int 	n;
	int 	sq120;

	ASSERT(str_fen != NULL);
	board_init(pos);
	file = FILE_A;
	rank = RANK_8;
	while (*str_fen && rank >= RANK_1)
	{
		n = 1;
		switch (*str_fen)
		{
			case 'p': piece = bP; break;
			case 'r': piece = bR; break;
			case 'n': piece = bN; break;
			case 'b': piece = bB; break;
			case 'k': piece = bK; break;
			case 'q': piece = bQ; break;
			case 'P': piece = wP; break;
			case 'R': piece = wR; break;
			case 'N': piece = wN; break;
			case 'B': piece = wB; break;
			case 'K': piece = wK; break;
			case 'Q': piece = wQ; break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
                piece = EMPTY;
                n = *str_fen - '0';
                break;
            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                str_fen++;
                continue;
            default :
                return (1);
		}
		i = 0;
		while (i < n)
		{
			sq120 = SQ120(rank * 8 + file);
			if (piece != EMPTY)
				pos->pieces[sq120] = piece;	
			i++;
			file++;
		}
		str_fen++;
	}
	ASSERT(rank == -1 && file == FILE_A);
	ASSERT(*str_fen == 'w' || *str_fen == 'b');
	pos->pb_side = (*str_fen == 'w') ? WHITE : BLACK;
	pos->side = pos->pb_side;
	
	str_fen += 2;
	ASSERT((*str_fen >= '0' && *str_fen <= '9') || *str_fen == '-');
	pos->pb_nmate = (*str_fen) - '0';
	if (*str_fen == '-')
		pos->pb_nmate = -1;
	
	update_pieceslist(pos);
	return (0);
}