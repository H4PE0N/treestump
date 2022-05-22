
#ifndef RENDER_BOARD_SCREEN_H
#define RENDER_BOARD_SCREEN_H

bool render_chess_board(Screen, const Piece[], Info, Kings, const Move[]);

bool render_mark_board(Screen, const Piece[], Info, Kings, const Move[], const Point[]);

bool render_move_board(Screen, const Piece[], Info, Kings, const Move[], Point);

bool render_promote_board(Screen, unsigned short);

bool render_result_board(Screen, const Piece[], Info, Kings);

// ####################################################################################

bool render_move_squares(Screen, const Piece[], Info, Kings, Point);

bool render_latest_move(Screen, const Move[]);

bool render_check_squares(Screen, const Piece[], Info, Kings);

bool render_board_pieces(Screen, const Piece[]);

bool render_board_piece(Screen, Piece, Point);

bool render_check_square(Screen, const Piece[], Info, Point);

bool render_board_squares(Screen);

bool render_team_squares(Screen, unsigned short);

bool render_point_image(Screen, Surface*, Point, Uint8);

bool render_board_move(Screen, Surface*, Move, Uint8);

bool render_board_image(Render*, Surface*, Rect, Uint8);

bool render_input_marks(Screen, const Point[]);

#endif
