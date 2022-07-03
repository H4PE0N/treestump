
#include "../Header-Files-Folder/engine-include-file.h"

// The value of the board is positive for whites favour and negative for blacks favour
signed short board_state_value(const Piece board[], Info info, Kings kings)
{
	signed short boardValue = 0;

	boardValue += board_pieces_value(board);

	boardValue += check_draw_value(board, info, kings);

	boardValue += check_mate_value(board, info, kings);

	return boardValue;
}

signed short board_pieces_value(const Piece board[])
{
	signed short piecesValue = 0;
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Piece piece = board[point];

		if(!chess_piece_exists(piece)) continue;

		piecesValue += chess_piece_value(piece);

		piecesValue += piece_matrix_value(piece, point);
	}
	return piecesValue;
}

signed short check_mate_value(const Piece board[], Info info, Kings kings)
{
	signed short mateValue = 0;

	if(check_mate_ending(board, info, kings, TEAM_WHITE)) mateValue += MATE_VALUE;

	if(check_mate_ending(board, info, kings, TEAM_BLACK)) mateValue -= MATE_VALUE;

	return mateValue;
}

signed short check_draw_value(const Piece board[], Info info, Kings kings)
{
	signed short drawValue = 0;

	if(check_draw_ending(board, info, kings, TEAM_WHITE)) drawValue += DRAW_VALUE;

	if(check_draw_ending(board, info, kings, TEAM_BLACK)) drawValue -= DRAW_VALUE;

	return drawValue;
}


signed short chess_piece_value(Piece piece)
{
	if(!chess_piece_exists(piece)) return 0;

	unsigned short team = PIECE_TEAM_MACRO(piece);
	unsigned short type = PIECE_TYPE_MACRO(piece);

	signed short pieceValue = PIECE_TYPE_VALUES[type];

	return team_weight_value(pieceValue, team);
}

signed short team_weight_value(signed short value, unsigned short team)
{
	if(team == TEAM_BLACK) return -value;
	if(team == TEAM_WHITE) return +value;

	else return 0;
}

signed short piece_matrix_value(Piece piece, Point point)
{
	if(!point_inside_board(point) || !chess_piece_exists(piece)) return 0;

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
  Piece pieceType = (piece & PIECE_TYPE_MASK);

  unsigned short rank = POINT_RANK_MACRO(point);

	unsigned short teamRank = team_matrix_rank(rank, pieceTeam);
	unsigned short teamFile = POINT_FILE_MACRO(point);

	signed short matrixValue = type_matrix_value(pieceType, teamRank, teamFile);

	unsigned short team = PIECE_TEAM_MACRO(piece);

	return team_weight_value(matrixValue, team);
}

unsigned short team_matrix_rank(unsigned short rank, Piece pieceTeam)
{
	return (pieceTeam == PIECE_TEAM_BLACK) ? (BOARD_RANKS-rank-1) : rank;
}

signed short type_matrix_value(Piece pieceType, unsigned short rank, unsigned short file)
{
	if(pieceType == PIECE_TYPE_PAWN) return PAWN_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_KNIGHT) return KNIGHT_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_BISHOP) return BISHOP_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_ROOK) return ROOK_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_QUEEN) return QUEEN_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_KING) return KING_MATRIX[rank][file];

	return 0;
}
