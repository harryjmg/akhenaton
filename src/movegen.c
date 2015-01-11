#include "akh.h"

#define MOVE(f, t, ca, pro, fl) ( (f) | ((t) << 7) | ( (ca) << 14 ) | ( (pro) << 20 ) | (fl))
#define SQOFFBOARD(sq) (FilesBrd[(sq)]==OFFBOARD)

const int LoopSlidePce[8] = { wB, wR, wQ, 0, bB, bR, bQ, 0 };
const int LoopNonSlidePce[6] = { wN, wK, 0, bN, bK, 0 };
const int LoopSlideIndex[2] = { 0, 4 };
const int LoopNonSlideIndex[2] = { 0, 3 };
const int NumDir[13] = { 0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8 };

const int PceDir[13][8] = {
	{ 0, 0, 0, 0, 0, 0, 0 }, // EMPTY
	{ 0, 0, 0, 0, 0, 0, 0 }, // wP
	{ -8, -19,	-21, -12, 8, 19, 21, 12 }, // wN
	{ -9, -11, 11, 9, 0, 0, 0, 0 }, // wB
	{ -1, -10,	1, 10, 0, 0, 0, 0 }, // wR
	{ -1, -10,	1, 10, -9, -11, 11, 9 }, // wQ
	{ -1, -10,	1, 10, -9, -11, 11, 9 }, // wK
	{ 0, 0, 0, 0, 0, 0, 0 }, // bP
	{ -8, -19,	-21, -12, 8, 19, 21, 12 }, // bN
	{ -9, -11, 11, 9, 0, 0, 0, 0 }, // bB
	{ -1, -10,	1, 10, 0, 0, 0, 0 }, // bR
	{ -1, -10,	1, 10, -9, -11, 11, 9 }, // bQ
	{ -1, -10,	1, 10, -9, -11, 11, 9 } // bK
};

static void AddQuietMove(const t_board *pos, int move, t_movelist *list)
{
	if (pos) // Esquive de warning
	{
		list->moves[list->count].move = move;
		list->moves[list->count].score = 0;
		list->count++;
	}
}

static void AddCaptureMove(const t_board *pos, int move, t_movelist *list)
{
	if (pos) // Esquive de warning
	{
		list->moves[list->count].move = move;
		if (CAPTURED(move) == bK || CAPTURED(move) == wK)
			list->moves[list->count].score = 200;
		list->moves[list->count].score = 50;
		list->count++;
	}
}

static void AddWhitePawnCapMove(const t_board *pos, const int from, const int to, const int cap, t_movelist *list) 
{
	if (RanksBrd[from] == RANK_7)
	{
		AddCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
	}
	else
		AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
}

static void AddWhitePawnMove(const t_board *pos, const int from, const int to, t_movelist *list)
{
	if (RanksBrd[from] == RANK_7)
	{
		AddQuietMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
	}
	else
		AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
}

static void AddBlackPawnCapMove(const t_board *pos, const int from, const int to, const int cap, t_movelist *list)
{
	if (RanksBrd[from] == RANK_2)
	{
		AddCaptureMove(pos, MOVE(from, to, cap, bQ ,0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, bR, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, bB, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, bN, 0), list);
	}
	else
		AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
}

static void AddBlackPawnMove(const t_board *pos, const int from, const int to, t_movelist *list )
{
	if (RanksBrd[from] == RANK_2)
	{
		AddQuietMove(pos, MOVE(from, to, EMPTY, bQ, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bR, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bB, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bN, 0), list);
	} 
	else
		AddQuietMove(pos, MOVE(from,to,EMPTY,EMPTY,0), list);
}

void movegen(const t_board *pos, t_movelist *list)
{
	list->count = 0;

	int pce = EMPTY;
	int side = pos->side;
	int sq = 0; int t_sq = 0;
	int pceNum = 0;
	int dir = 0;
	int index = 0;
	int pceIndex = 0;

	// PAWNS
	if (side == WHITE)
	{
		for (pceNum = 0; pceNum < pos->pceNum[wP]; ++pceNum)
		{
			sq = pos->pList[wP][pceNum];
			if (pos->pieces[sq + 10] == EMPTY)
			{
				AddWhitePawnMove(pos, sq, sq + 10, list);
				if (RanksBrd[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY)
					AddQuietMove(pos, MOVE(sq,(sq + 20), EMPTY , EMPTY, MFLAGPS), list);
			}
			if (!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK)
				AddWhitePawnCapMove(pos, sq, sq + 9, pos->pieces[sq + 9], list);
			if (!SQOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]] == BLACK)
				AddWhitePawnCapMove(pos, sq, sq + 11, pos->pieces[sq + 11], list);
		}
	}
	else
	{
		for (pceNum = 0; pceNum < pos->pceNum[bP]; ++pceNum)
		{
			sq = pos->pList[bP][pceNum];
			if (pos->pieces[sq - 10] == EMPTY)
			{
				AddBlackPawnMove(pos, sq, sq - 10, list);
				if (RanksBrd[sq] == RANK_7 && pos->pieces[sq - 20] == EMPTY)
					AddQuietMove(pos, MOVE(sq, (sq - 20), EMPTY, EMPTY, MFLAGPS), list);
			}
			if (!SQOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]] == WHITE)
				AddBlackPawnCapMove(pos, sq, sq - 9, pos->pieces[sq - 9], list);
			if (!SQOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]] == WHITE)
				AddBlackPawnCapMove(pos, sq, sq - 11, pos->pieces[sq - 11], list);

		}	
	}

	// SLIDING PIECES
	pceIndex = LoopSlideIndex[side];
	pce = LoopSlidePce[pceIndex++];
	while (pce != 0)
	{
		for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
		{
			sq = pos->pList[pce][pceNum];
			for (index = 0; index < NumDir[pce]; ++index)
			{
				dir = PceDir[pce][index];
				t_sq = sq + dir;
				while (!SQOFFBOARD(t_sq))
				{
					// BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
					if (pos->pieces[t_sq] != EMPTY)
					{
						if (PieceCol[pos->pieces[t_sq]] == (side ^ 1))
							AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
						break;
					}
					AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), list);
					t_sq += dir;
				}
			}
		}
		pce = LoopSlidePce[pceIndex++];
	}

	// NON SLIDING PIECES
	pceIndex = LoopNonSlideIndex[side];
	pce = LoopNonSlidePce[pceIndex++];
	while (pce != 0)
	{
		for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
		{
			sq = pos->pList[pce][pceNum];
			for (index = 0; index < NumDir[pce]; ++index)
			{
				dir = PceDir[pce][index];
				t_sq = sq + dir;
				if (SQOFFBOARD(t_sq))
					continue;
				// BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
				if (pos->pieces[t_sq] != EMPTY)
				{
					if (PieceCol[pos->pieces[t_sq]] == (side ^ 1))
						AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
					continue;
				}
				AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), list);
			}
		}
		pce = LoopNonSlidePce[pceIndex++];
	}
}