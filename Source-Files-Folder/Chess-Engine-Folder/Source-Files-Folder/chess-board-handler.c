
#include "../Header-Files-Folder/engine-include-file.h"

// ##############################################################################

bool piece_team_exists(Piece pieceTeam)
{
	unsigned short team = PIECE_TEAM_MACRO(pieceTeam);

	return (team == TEAM_WHITE || team == TEAM_BLACK);
}

bool piece_type_exists(Piece pieceType)
{
	unsigned short type = PIECE_TYPE_MACRO(pieceType);

	return NUMBER_IN_BOUNDS(type, 1, 6);
}

bool board_piece_exists(Piece piece)
{
	bool teamExists = piece_team_exists(piece);
	bool typeExists = piece_type_exists(piece);

	return (teamExists && typeExists);
}

bool board_pieces_team(Piece firstPiece, Piece secondPiece)
{
	Piece firstTeam = firstPiece & PIECE_TEAM_MASK;
	Piece secondTeam = secondPiece & PIECE_TEAM_MASK;

	return board_teams_team(firstTeam, secondTeam);
}

bool board_teams_team(Piece firstTeam, Piece secondTeam)
{
	bool bothBlack = (firstTeam == PIECE_TEAM_BLACK && secondTeam == PIECE_TEAM_BLACK);
	bool bothWhite = (firstTeam == PIECE_TEAM_WHITE && secondTeam == PIECE_TEAM_WHITE);

	return (bothBlack || bothWhite);
}

bool board_teams_enemy(Piece firstTeam, Piece secondTeam)
{
	bool enemyWhite = (firstTeam == PIECE_TEAM_BLACK && secondTeam == PIECE_TEAM_WHITE);
	bool enemyBlack = (firstTeam == PIECE_TEAM_WHITE && secondTeam == PIECE_TEAM_BLACK);

	return (enemyWhite || enemyBlack);
}

bool chess_piece_empty(Piece piece)
{
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	return (pieceTeam == PIECE_TEAM_NONE && pieceType == PIECE_TYPE_NONE);
}

// ##############################################################################

bool point_inside_board(Point point)
{
	if(point == POINT_NONE || point < 0) return false;

	return NUMBER_IN_BOUNDS(point, 0, BOARD_LENGTH);
}

bool board_points_team(const Piece board[], Point first, Point second)
{
	Piece firstPiece = board[first];
	Piece secondPiece = board[second];

	return board_pieces_team(firstPiece, secondPiece);
}

// ##############################################################################

Info info_team_enemy(Info infoTeam)
{
	if(infoTeam == INFO_TEAM_WHITE) return INFO_TEAM_BLACK;

	else if(infoTeam == INFO_TEAM_BLACK) return INFO_TEAM_WHITE;

	return INFO_TEAM_NONE;
}

bool info_team_exists(Info infoTeam)
{
	unsigned short team = INFO_TEAM_MACRO(infoTeam);

	return (team == TEAM_WHITE || team == TEAM_BLACK);
}

// ##############################################################################

unsigned short move_array_amount(const Move moves[])
{
	unsigned short movesAmount = 0;

	while(moves[movesAmount] != MOVE_NONE && moves[movesAmount] >= 0)
	{
		movesAmount += 1;
	}

	return movesAmount;
}

bool move_inside_board(Move move)
{
	if(move == MOVE_NONE || move < 0) return false;

	Point start = MOVE_START_MACRO(move);
	Point stop = MOVE_STOP_MACRO(move);

	bool startInside = point_inside_board(start);
	bool stopInside = point_inside_board(stop);

	return (startInside && stopInside);
}

// ##############################################################################

short move_file_offset(Move move, unsigned short team)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short startFile = POINT_FILE_MACRO(startPoint);
	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);

	short fileOffset = (stopFile - startFile);

	if(team == TEAM_WHITE) return fileOffset;// * WHITE_MOVE_VALUE;

	if(team == TEAM_BLACK) return fileOffset;// * BLACK_MOVE_VALUE;

	return SHORT_NONE;
}

short move_rank_offset(Move move, unsigned short team)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short startRank = POINT_RANK_MACRO(startPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	short rankOffset = (stopRank - startRank);

	if(team == TEAM_WHITE) return rankOffset * WHITE_MOVE_VALUE;

	if(team == TEAM_BLACK) return rankOffset * BLACK_MOVE_VALUE;

	return SHORT_NONE;
}

// ##############################################################################

// Kings

// ##############################################################################

bool normal_team_exists(unsigned short team)
{
	return (team == TEAM_WHITE || team == TEAM_BLACK);
}

unsigned short normal_team_enemy(unsigned short team)
{
	if(team == TEAM_WHITE) return TEAM_BLACK;

	else if(team == TEAM_BLACK) return TEAM_WHITE;

	return TEAM_NONE;
}
