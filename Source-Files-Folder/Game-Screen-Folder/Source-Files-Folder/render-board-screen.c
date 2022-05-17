
#include "../Header-Files-Folder/game-screen-includer.h"

bool display_chess_board(Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], Point point)
{
	SDL_RenderClear(screen.render);

	if(!render_chess_board(screen, board, info, kings, moveArray, point)) return false;

	SDL_RenderPresent(screen.render);

	return true;
}

bool display_result_board(Screen screen, const Piece board[], Info info, Kings kings)
{
	SDL_RenderClear(screen.render);

	if(!render_result_board(screen, board, info, kings)) return false;

	SDL_RenderPresent(screen.render);

	return true;
}

bool render_chess_board(Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], Point point)
{
	if(!render_board_squares(screen)) return false;

  if(!render_latest_move(screen, moveArray)) return false;

  if(!render_check_squares(screen, board, info, kings)) return false;

	if(!render_move_squares(screen, board, info, kings, point)) return false;

	if(!render_board_pieces(screen, board)) return false;

	return true;
}

bool render_result_board(Screen screen, const Piece board[], Info info, Kings kings)
{
	unsigned short team = INFO_TEAM_MACRO(info);

	unsigned short winningTeam = normal_team_enemy(team);

	if(check_mate_ending(board, info, kings, team))
	{
		if(!render_team_squares(screen, winningTeam)) return false;
	}
	else if(check_draw_ending(board, info, kings, team))
	{
		if(!render_board_squares(screen)) return false;
	}
	else
	{
		// This is if there is no check mate or draw (game not ended)
	}


	if(!render_check_squares(screen, board, info, kings)) return false;

	if(!render_board_pieces(screen, board)) return false;

	return true;
}

bool extract_team_square(Surface** squareImage, unsigned short team)
{
	if(team == TEAM_WHITE)
	{
		if(!load_filename_image(squareImage, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/white-square.png")) return false;
	}
	else if(team == TEAM_BLACK)
	{
		if(!load_filename_image(squareImage, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/black-square.png")) return false;
	}
	else return false;

	return true;
}

bool render_team_squares(Screen screen, unsigned short team)
{
	Surface* squareImage;

	if(!extract_team_square(&squareImage, team)) return false;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(!render_point_image(screen, squareImage, point, 255)) return false;
	}

  return true;
}

bool render_board_pieces(Screen screen, const Piece board[])
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(!chess_piece_exists(board[point])) continue;

		if(!render_board_piece(screen, board[point], point)) return false;
	}
	return true;
}

bool render_board_piece(Screen screen, Piece piece, Point point)
{
	if(!chess_piece_exists(piece)) return false;

	Surface* pieceImage;

	if(!extract_piece_image(&pieceImage, piece)) return false;

	if(!render_point_image(screen, pieceImage, point, 255)) return false;

	return true;
}

bool render_check_square(Screen screen, const Piece board[], Info info, Point kingPoint)
{
	if(!king_inside_check(board, info, kingPoint)) return true;

	Surface* checkSquare;

	if(!load_filename_image(&checkSquare, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/check-square.png")) return false;

	if(!render_point_image(screen, checkSquare, kingPoint, 255)) return false;

	return true;
}

bool render_check_squares(Screen screen, const Piece board[], Info info, Kings kings)
{
	Point whiteKing = KINGS_WHITE_MACRO(kings);
	Point blackKing = KINGS_BLACK_MACRO(kings);

	if(!render_check_square(screen, board, info, whiteKing)) return false;

	if(!render_check_square(screen, board, info, blackKing)) return false;

	return true;
}

bool render_move_squares(Screen screen, const Piece board[], Info info, Kings kings, Point point)
{
	if(!point_inside_board(point)) return true;

	unsigned short team = PIECE_TEAM_MACRO(board[point]);

	if(!current_team_move(info, team)) return false;


	Move* moveArray;

	if(!piece_legal_moves(&moveArray, board, info, kings, point)) return true;

  unsigned short moveAmount = move_array_amount(moveArray);


	if(moveAmount <= 0)
	{
		free(moveArray);

		return false;
	}


  Surface* moveSquare;

	if(!load_filename_image(&moveSquare, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/move-square.png"))
	{
		free(moveArray);

		return false;
	}


	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Point stopPoint = MOVE_STOP_MACRO(moveArray[index]);


		if(!render_point_image(screen, moveSquare, stopPoint, 255))
		{
      free(moveArray);

			return false;
		}
	}

	free(moveArray);

	return true;
}

bool render_latest_move(Screen screen, const Move moveArray[])
{
	unsigned short moveAmount = move_array_amount(moveArray);

	if(moveAmount <= 0) return true;


	Surface* movedSquare;

	if(!load_filename_image(&movedSquare, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/moved-square.png")) return false;


  if(!render_board_move(screen, movedSquare, moveArray[moveAmount - 1], 255)) return false;

  return true;
}

bool render_board_squares(Screen screen)
{
	Surface* whiteSquare, *blackSquare;

	if(!load_filename_image(&whiteSquare, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/white-square.png")) return false;

  if(!load_filename_image(&blackSquare, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/black-square.png")) return false;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short rank = POINT_RANK_MACRO(point);
		unsigned short file = POINT_FILE_MACRO(point);

		Surface* image = (rank + file) % 2 == 0 ? whiteSquare : blackSquare;

		if(!render_point_image(screen, image, point, 255)) return false;
	}

  return true;
}
