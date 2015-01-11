#include "akh.h"

void makemove(t_board *pos, int move)
{
	int from;
	int to;
	int prom;
	int pce;

	pos->history_count++;
	pos->history_moves[pos->history_count] = move;

	from = FROMSQ(move);
	to = TOSQ(move);
	prom = PROMOTED(move);

	pce = pos->pieces[from];

	pos->pieces[from] = EMPTY;
	if (prom != EMPTY) pos->pieces[to] = prom;
	else pos->pieces[to] = pce;

	pos->side ^= 1;
	update_pieceslist(pos);
}

void unmakemove(t_board *pos)
{
	int move;
	int pce;
	int from;
	int to;
	int cap;
	int prom;

	move = pos->history_moves[pos->history_count];
	pos->history_count--;

	from = FROMSQ(move);
	to = TOSQ(move);
	cap = CAPTURED(move);
	prom = PROMOTED(move);

	pce = pos->pieces[to];

	if (cap != EMPTY) pos->pieces[to] = cap;
	else pos->pieces[to] = EMPTY;

	if (prom != EMPTY) pos->pieces[from] = (PieceCol[pce] == WHITE) ? wP : bP;
	else pos->pieces[from] = pce;

	pos->side ^= 1;
	
	update_pieceslist(pos);
}