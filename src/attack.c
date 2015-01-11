#include "akh.h"

const int KnDir[8] = { -8, -19,	-21, -12, 8, 19, 21, 12 };
const int RkDir[4] = { -1, -10,	1, 10 };
const int BiDir[4] = { -9, -11, 11, 9 };
const int KiDir[8] = { -1, -10,	1, 10, -9, -11, 11, 9 };

int is_sq_attacked(int sq, int side, t_board *pos)
{
	int index;
	int pce;
	int t_sq;
	int dir;

	// pawns
	if (side == WHITE)
	{
		if (pos->pieces[sq - 11] == wP || pos->pieces[sq - 9] == wP)
			return (TRUE);
	}
	else
	{
		if (pos->pieces[sq + 11] == bP || pos->pieces[sq + 9] == bP)
			return (TRUE);
	}

	// knights
	index = 0;
	while (index < 8)
	{		
		pce = pos->pieces[sq + KnDir[index]];
		if (pce != OFFBOARD && IsKn(pce) && PieceCol[pce] == side)
			return (TRUE);
		index++;
	}

	// rooks & queens
	index = 0;
	while (index < 4)
	{		
		dir = RkDir[index];
		t_sq = sq + dir;
		pce = pos->pieces[t_sq];
		while (pce != OFFBOARD)
		{
			if (pce != EMPTY)
			{
				if (IsRQ(pce) && PieceCol[pce] == side)
					return (TRUE);
				break;
			}
			t_sq += dir;
			pce = pos->pieces[t_sq];
		}
		index++;
	}

	// bishops, queens
	index = 0;
	while (index < 4)
	{
		dir = BiDir[index];
		t_sq = sq + dir;
		pce = pos->pieces[t_sq];
		while (pce != OFFBOARD)
		{
			if (pce != EMPTY)
			{
				if (IsBQ(pce) && PieceCol[pce] == side)
					return (TRUE);
				break;
			}
			t_sq += dir;
			pce = pos->pieces[t_sq];
		}
		index++;
	}
	
	// kings
	index = 0;
	while (index < 8)
	{		
		pce = pos->pieces[sq + KiDir[index]];
		if (pce != OFFBOARD && IsKi(pce) && PieceCol[pce]==side)
			return (TRUE);
		index++;
	}

	return (FALSE);
}