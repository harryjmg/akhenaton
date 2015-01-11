#ifndef AKH_H_
#define AKH_H_

#include <stdio.h>
#include <stdlib.h>

// Un assert sympathique
# define DEBUG
# ifndef DEBUG
#  define ASSERT(n)
# else
# 	define ASSERT(n) \
	if(!(n)) { \
		printf("ASSERT (%s) failed ",#n); \
		printf("In File %s ",__FILE__); \
		printf("At Line %d\n",__LINE__); \
		exit(1);}
#endif

/* GAME MOVE */

/*
0000 0000 0000 0000 0000 0111 1111 -> From 0x7F
0000 0000 0000 0011 1111 1000 0000 -> To >> 7, 0x7F
0000 0000 0011 1100 0000 0000 0000 -> Captured >> 14, 0xF
0000 0000 0100 0000 0000 0000 0000 -> EP 0x40000
0000 0000 1000 0000 0000 0000 0000 -> Pawn Start 0x80000
0000 1111 0000 0000 0000 0000 0000 -> Promoted Piece >> 20, 0xF
0001 0000 0000 0000 0000 0000 0000 -> Castle 0x1000000
*/

#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m)>>20) & 0xF)
#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7C000
#define MFLAGPROM 0xF00000

#define NOMOVE 0

#define MAXPOSITIONMOVES 100
#define MAXDEPTH 64


# define FRTOSQ(f,r) ( (21 + (f) ) + ( (r) * 10 ) )
# define SQ64(sq120) (Sq120ToSq64[(sq120)])
# define SQ120(sq64) (Sq64ToSq120[(sq64)])	
# define IsBQ(p) (PieceBishopQueen[(p)])
# define IsRQ(p) (PieceRookQueen[(p)])
# define IsKn(p) (PieceKnight[(p)])
# define IsKi(p) (PieceKing[(p)])

enum { FALSE, TRUE };
enum { WHITE, BLACK, BOTH };
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK  };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum {
  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
  A2 = 31, B2, C2, D2, E2, F2, G2, H2,
  A3 = 41, B3, C3, D3, E3, F3, G3, H3,
  A4 = 51, B4, C4, D4, E4, F4, G4, H4,
  A5 = 61, B5, C5, D5, E5, F5, G5, H5,
  A6 = 71, B6, C6, D6, E6, F6, G6, H6,
  A7 = 81, B7, C7, D7, E7, F7, G7, H7,
  A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};


// Structures
typedef struct
{
	int move;
	int score;
} t_move;

typedef struct
{
	t_move moves[MAXPOSITIONMOVES];
	int count;
} t_movelist;

typedef struct s_board
{
	int pb_side;
	int pb_nmate;

	int side;
	int KingSq[2];
	int pieces[120];

	int pceNum[13];
	int pList[13][10];

	int history_moves[50];
	int history_count;
} t_board;

// Rangées et colonnes de chaque cases
extern int FilesBrd[120];
extern int RanksBrd[120];

// 
extern int Sq120ToSq64[120];
extern int Sq64ToSq120[64];

extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceCol[13];

extern int PieceKnight[13];
extern int PieceKing[13];
extern int PieceRookQueen[13];
extern int PieceBishopQueen[13];
extern int PieceSlides[13];

extern int Mirror64[64];

extern int PieceCol[13];
extern int PiecePawn[13];


// parse.c
int get_fen(char **str_fen);
int parse_fen(t_board *board, char *str_fen);

// init.c
void all_init(void);

// board.c
void print_board(t_board *board);
void update_pieceslist(t_board *pos);
void board_init(t_board *board);

// validate.c
int SqOnBoard(const int sq);
int SideValid(const int side);
int FileRankValid(const int fr);
int PieceValidEmpty(const int pce);
int PieceValid(const int pce);
int SqIs120(const int sq);
int PceValidEmptyOffbrd(const int pce);

// attack.c
int is_sq_attacked(int sq, int side, t_board *pos);

// io.c
char *PrMove(int move);
char *PrSq(int sq);
void PrintMoveList(t_movelist *list);

// movegen.c
void movegen(const t_board *pos, t_movelist *list);

// makemove.c
void makemove(t_board *pos, int move);
void unmakemove(t_board *pos);

// search.c
void search_soluce(t_board *board);

#endif