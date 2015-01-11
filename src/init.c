#include "akh.h"

int Sq120ToSq64[120];
int Sq64ToSq120[64];
int FilesBrd[120];
int RanksBrd[120];

void init_sq120To64()
{
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;
	for (index = 0; index < 120; ++index)
		Sq120ToSq64[index] = 65;
	for (index = 0; index < 64; ++index)
		Sq64ToSq120[index] = 120;
	for (rank = RANK_1; rank <= RANK_8; ++rank)
	{
		for (file = FILE_A; file <= FILE_H; ++file)
		{
			sq = FRTOSQ(file,rank);
			Sq64ToSq120[sq64] = sq;
			Sq120ToSq64[sq] = sq64;
			sq64++;
		}
	}
}

void init_filerankbrd()
{
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;

	for(index = 0; index < 120; ++index) {
		FilesBrd[index] = OFFBOARD;
		RanksBrd[index] = OFFBOARD;
	}

	for(rank = RANK_1; rank <= RANK_8; ++rank) {
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = FRTOSQ(file,rank);
			FilesBrd[sq] = file;
			RanksBrd[sq] = rank;
		}
	}
}

void all_init(void)
{
	init_filerankbrd();
	init_sq120To64();
}