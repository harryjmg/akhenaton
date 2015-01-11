/*

9 Jan 2014
J'ai fait quelques modifications qui rendent mon programme correct, la rapidité
1) J'ai ajouté deux variables, moves_possible et king_attacked. moves_possible
permet de savoir si au moins un mouvement a été possible sans se mettre en
echecs. king_attacked garde en variable le résultat de ma fonction
is_sq_attacked() pour ne pas le recalculer plein de fois.

2) J'ai ajouté une condition dans chaque boucle for du minimax, elle invalide
directement les mouvements mettant en échecs. Lorsqu'un mouvement est possible,
moves_possible est incrémenté.

3) Fusion du if WHITE et if BLACK dans le minimax. De nombreuses compressions
dans cette même fonction pour la rendre moins volumineuse et peut être plus 
simple à lire.

*/

#include "akh.h"

int BEST_MOVE;
int MOVE;

static int find_engine(t_board *board, int start_depth, int depth)
{
	t_movelist movelist[1];
	int best_value;
	int i;
	int val;
	int side;
	int moves_possible;
	int king_attacked;

	// SI PROFONDEUR MAX, RECHERCHE INFRUCTUEUSE
	if (depth == 0)
		return (0);

	// RECHERCHE DU MEILLEUR MOUVEMENT
	side = board->side;
	moves_possible = 0;
	best_value = side ? 50000 : -50000;
	movegen(board, movelist);
	if (movelist->count == 0) return (0);
	for (i = 0; i < movelist->count; i++)
	{

		makemove(board, movelist->moves[i].move);
		king_attacked = is_sq_attacked(board->KingSq[side], side ^ 1, board);
		if (king_attacked == FALSE)
		{
			moves_possible++;
			val = find_engine(board, start_depth, depth - 1);
			if ((!side && val > best_value) || (side && val < best_value))
			{
				BEST_MOVE = depth == start_depth ? movelist->moves[i].move : BEST_MOVE;
				best_value = val;
			}
		}
		unmakemove(board);
	}
	
	// SI AUCUNS MOUVEMENTS VALIDES TROUVÉS POUR CETTE POSITION, MAT OU PAT
	king_attacked = is_sq_attacked(board->KingSq[side], side ^ 1, board);
	if (king_attacked && moves_possible == 0 && side == BLACK)
		return (10000);
	else if (!king_attacked && moves_possible == 0 && side == BLACK)
		return (0);

	if (king_attacked && moves_possible == 0 && side == WHITE)
		return (-10000);
	else if (!king_attacked && moves_possible == 0 && side == WHITE)
		return (0);

	// SI IL Y A EU DES MOUVEMENTS VALIDES, ON A UNE VALEUR A RETURN
	return (best_value);
}

static void auto_search_soluce(t_board *board)
{
	int max_depth;
	int best_score;
	int i;
	int j;
	int flag;

	for (j = 1; j < 5; j++)
	{
		max_depth = j * 2;
		if (max_depth == 6) printf("You can go take a coffee\n");
		if (max_depth == 7) printf("You should press ^c to quit this...\n");
		flag = 1;
		i = 0;
		while (max_depth - 1 > 0)
		{
			best_score = find_engine(board, max_depth, max_depth);
			if (best_score == 0)
			{
				flag = 0;
				break ;
			}
			if (board->side == board->pb_side) printf("%d. %s ", ++i, PrMove(BEST_MOVE));
			else printf("%s\n", PrMove(BEST_MOVE));
			makemove(board, BEST_MOVE);
			max_depth--;
		}
		if (flag == 1)
		{
			printf("MATE\n");
			printf("\n\n");
			return ;
		}
	}
	printf("Solution not found in less than 5 moves :(\n");
}

void search_soluce(t_board *board)
{
	int max_depth;
	int best_score;
	int i;

	printf("===--     Search started       --===\n");

	if (board->pb_nmate == -1)
		return (auto_search_soluce(board));
	max_depth = board->pb_nmate * 2;

	printf("Please wait...\n");
	if (max_depth >= 7) printf("Please wait as far you can wait (^c : quit)\n");
	else printf("\n");

	i = 0;
	while (max_depth - 1 > 0)
	{
		best_score = find_engine(board, max_depth, max_depth);
		if (best_score == 0)
		{
			printf("Solution not found :(\n\n\n");
			return ;
		}
		if (board->side == board->pb_side)
			printf("%d. %s ", ++i, PrMove(BEST_MOVE));
		else
			printf("%s\n", PrMove(BEST_MOVE));
		makemove(board, BEST_MOVE);
		max_depth--;
	}
	printf("MATE\n");
	printf("\n\n");
}

