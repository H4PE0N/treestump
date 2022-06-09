
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

bool chess_piece_exists(Piece piece)
{
	bool pieceTeamExists = piece_team_exists(piece);
	bool pieceTypeExists = piece_type_exists(piece);

	return (pieceTeamExists && pieceTypeExists);
}



bool piece_teams_team(Piece firstPieceTeam, Piece secondPieceTeam)
{
	bool bothBlack = (firstPieceTeam == PIECE_TEAM_BLACK && secondPieceTeam == PIECE_TEAM_BLACK);
	bool bothWhite = (firstPieceTeam == PIECE_TEAM_WHITE && secondPieceTeam == PIECE_TEAM_WHITE);

	return (bothBlack || bothWhite);
}

bool piece_teams_enemy(Piece firstPieceTeam, Piece secondPieceTeam)
{
	bool enemyWhite = (firstPieceTeam == PIECE_TEAM_BLACK && secondPieceTeam == PIECE_TEAM_WHITE);
	bool enemyBlack = (firstPieceTeam == PIECE_TEAM_WHITE && secondPieceTeam == PIECE_TEAM_BLACK);

	return (enemyWhite || enemyBlack);
}



bool chess_pieces_team(Piece firstPiece, Piece secondPiece)
{
	Piece firstPieceTeam = (firstPiece & PIECE_TEAM_MASK);
	Piece secondPieceTeam = (secondPiece & PIECE_TEAM_MASK);

	return piece_teams_team(firstPieceTeam, secondPieceTeam);
}

bool chess_pieces_enemy(Piece firstPiece, Piece secondPiece)
{
	Piece firstPieceTeam = (firstPiece & PIECE_TEAM_MASK);
	Piece secondPieceTeam = (secondPiece & PIECE_TEAM_MASK);

	return piece_teams_enemy(firstPieceTeam, secondPieceTeam);
}


Piece piece_team_enemy(Piece pieceTeam)
{
	if(pieceTeam == PIECE_TEAM_WHITE) return PIECE_TEAM_BLACK;

	else if(pieceTeam == PIECE_TEAM_BLACK) return PIECE_TEAM_WHITE;

	return PIECE_TEAM_NONE;
}

Point board_piece_point(const Piece board[], Piece piece)
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(board[point] == piece) return point;
	}
	return POINT_NONE;
}

Point rank_file_point(unsigned short rank, unsigned short file)
{
	return (RANK_POINT_MACRO(rank) | FILE_POINT_MACRO(file));
}

// ##############################################################################

bool point_inside_board(Point point)
{
	return NUMBER_IN_BOUNDS(point, 0, BOARD_LENGTH);
}

bool board_points_team(const Piece board[], Point firstPoint, Point secondPoint)
{
	Piece firstPiece = board[firstPoint];
	Piece secondPiece = board[secondPoint];

	return chess_pieces_team(firstPiece, secondPiece);
}

bool board_points_enemy(const Piece board[], Point firstPoint, Point secondPoint)
{
	Piece firstPiece = board[firstPoint];
	Piece secondPiece = board[secondPoint];

	return chess_pieces_enemy(firstPiece, secondPiece);
}

bool board_point_exists(const Piece board[], Point point)
{
	Piece piece = board[point];

	return chess_piece_exists(piece);
}

signed short array_point_index(const Point pointArray[], unsigned short amount, Point point)
{
	signed short pointIndex = -1;

	for(unsigned short index = 0; index < amount; index += 1)
	{
		if(pointArray[index] == point) { pointIndex = index; break; }
	}
	return pointIndex;
}

bool delete_array_point(Point* pointArray, unsigned short amount, short delIndex)
{
	if(!(delIndex >= 0 && delIndex < amount)) return false;

	for(int index = delIndex; index < (amount - 1); index += 1)
	{
		pointArray[index] = pointArray[index + 1];
	}
	pointArray[amount - 1] = POINT_NONE; return true;
}

Point* create_point_array(unsigned short amount)
{
	Point* pointArray = malloc(sizeof(Point) * (amount + 1));

	for(short index = 0; index < (amount + 1); index += 1)
	{
		pointArray[index] = POINT_NONE;
	}
	return pointArray;
}

unsigned short point_array_amount(const Point pointArray[])
{
	unsigned short amount = 0;

	while(pointArray[amount] != POINT_NONE) amount += 1;

	return amount;
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

unsigned short move_array_amount(const Move moveArray[])
{
	unsigned short movesAmount = 0;

	while(moveArray[movesAmount] != MOVE_NONE && moveArray[movesAmount] >= 0)
	{
		movesAmount += 1;
	}

	return movesAmount;
}

Move* create_move_array(unsigned short arrayLength)
{
	Move* moveArray = malloc(sizeof(Move) * arrayLength);

	for(unsigned short index = 0; index < arrayLength; index += 1)
	{
		moveArray[index] = MOVE_NONE;
	}

	return moveArray;
}

bool move_inside_board(Move move)
{
	if(move == MOVE_NONE || move < 0) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	bool startPointInside = point_inside_board(startPoint);
	bool stopPointInside = point_inside_board(stopPoint);

	return (startPointInside && stopPointInside);
}

bool move_points_team(const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return board_points_team(board, startPoint, stopPoint);
}

bool move_points_enemy(const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return board_points_enemy(board, startPoint, stopPoint);
}

short move_file_offset(Move move, unsigned short team)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short startFile = POINT_FILE_MACRO(startPoint);
	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);

	signed short fileOffset = (stopFile - startFile);

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

	signed short rankOffset = (stopRank - startRank);

	if(team == TEAM_WHITE) return rankOffset * WHITE_MOVE_VALUE;

	if(team == TEAM_BLACK) return rankOffset * BLACK_MOVE_VALUE;

	return SHORT_NONE;
}

short normal_rank_offset(Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return (POINT_RANK_MACRO(stopPoint) - POINT_RANK_MACRO(startPoint));
}

short normal_file_offset(Move move)
{
		Point startPoint = MOVE_START_MACRO(move);
		Point stopPoint = MOVE_STOP_MACRO(move);

		return (POINT_FILE_MACRO(stopPoint) - POINT_FILE_MACRO(startPoint));
}

signed short board_move_pattern(Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return (stopPoint - startPoint);
}

bool create_move_string(char* moveString, const Piece board[], Info info, Kings kings, Move move)
{
	if(move == MOVE_NONE || move < 0)
	{
		*moveString = '\0';

		return true;
	}

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short type = PIECE_TYPE_MACRO(board[startPoint]);

	Piece pieceTeam = (board[startPoint] & PIECE_TEAM_MASK);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);


	char pieceSymbol = '\0';
	char stopPointString[10];
	char checkSymbol = '\0';
	char mateSymbol = '\0';
	char captureSymbol = '\0';


	if(pieceTeam == PIECE_TEAM_WHITE) pieceSymbol = WHITE_MOVE_SYMBOLS[type];
	else if(pieceTeam == PIECE_TEAM_BLACK) pieceSymbol = BLACK_MOVE_SYMBOLS[type];

	if(!create_point_string(stopPointString, stopPoint))
	{
		printf("if(!create_point_string(stopPointString, stopPoint))\n");
	}

	if(move_deliver_mate(board, info, kings, move))
	{
		mateSymbol = '#';
	}
	else if(move_deliver_check(board, info, kings, move))
	{
		checkSymbol = '+';
	}

	if(board_points_enemy(board, startPoint, stopPoint) || (INFO_PASSANT_MACRO(info) == (stopFile + 1) ))
	{
		captureSymbol = 'x';
	}



	sprintf(moveString, "%s%s%s%s%s",
		(char[]) {pieceSymbol, '\0'},
		(char[]) {captureSymbol, '\0'},
		stopPointString,
		(char[]) {checkSymbol, '\0'},
		(char[]) {mateSymbol, '\0'}
	);

	//sprintf(moveString, "%c%c%s%c", pieceSymbol, speciallChar1, stopPointString, speciallChar2);

	return true;
}

bool create_point_string(char* pointString, Point point)
{
	unsigned short file = POINT_FILE_MACRO(point);
	unsigned short rank = POINT_RANK_MACRO(point);

	sprintf(pointString, "%c%c", FILE_SYMBOLS[file], RANK_SYMBOLS[rank]);

	return true;
}

// ##############################################################################

Point team_king_point(Kings kings, unsigned short team)
{
	if(team == TEAM_WHITE) return KINGS_WHITE_MACRO(kings);

	else if(team == TEAM_BLACK) return KINGS_BLACK_MACRO(kings);

	return POINT_NONE;
}

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

bool normal_teams_team(unsigned short firstTeam, unsigned short secondTeam)
{
	bool bothWhite = (firstTeam == TEAM_WHITE && secondTeam == TEAM_WHITE);
	bool bothBlack = (firstTeam == TEAM_BLACK && secondTeam == TEAM_BLACK);

	return (bothWhite || bothBlack);
}

bool normal_teams_enemy(unsigned short firstTeam, unsigned short secondTeam)
{
	bool enemyWhite = (firstTeam == TEAM_BLACK && secondTeam == TEAM_WHITE);
	bool enemyBlack = (firstTeam == TEAM_WHITE && secondTeam == TEAM_BLACK);

	return (enemyWhite || enemyBlack);
}
