#include <iostream>

using namespace std;

#define N_PIECE 5
#define MAX_BOARD_SIZE 10
#define is_1_at(d, i) (d >> (31 - i)) & 1
#define add_1_at(d, i) d |= 1 << (31 - i)

typedef unsigned int t_row;

struct piece {
	t_row rows[MAX_BOARD_SIZE] = { 0 };
	int dr;
	int dc;
	int width;
	int height;
	int first_top_part_position;
	bool is_placed;
};

inline int get_first_part_position(t_row row) {
	for (int c = 0; c < 32; c++) {
		if (is_1_at(row, c)) {
			return c;
		}
	}

	// never reach here
	return 0;
}

inline void print_board(piece pieces[N_PIECE], int board_size) {
	int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

	// configure board
	for (int i = 0; i < N_PIECE; i++) {
		int dr = pieces[i].dr;
		int dc = pieces[i].dc;
		int width = pieces[i].width;
		int height = pieces[i].height;

		for (int r = 0; r < height; r++) {
			t_row row = pieces[i].rows[r];
			for (int c = 0; c < width; c++) {
				if (is_1_at(row, c)) {
					board[r + dr][c + dc] = i + 1;
				}
			}
		}
	}

	// print board
	for (int r = 0; r < board_size; r++) {
		for (int c = 0; c < board_size; c++) {
			cout << board[r][c];
		}
		cout << '\n';
	}
}

inline void remove_piece(piece &p, t_row board[MAX_BOARD_SIZE], int board_size) {
	int dr = p.dr;
	int dc = p.dc;
	int height = p.height;

	for (int r = 0; r < height; r++) {
		board[r + dr] -= (p.rows[r] >> dc);
	}
}

inline bool place_piece(piece &p, t_row board[MAX_BOARD_SIZE]) {
	int dr = p.dr;
	int dc = p.dc;
	int height = p.height;

	// check if piece can be placed
	for (int r = 0; r < height; r++) {
		if ((p.rows[r] >> dc) & board[r + dr]) {
			return false;
		}
	}

	// place the piece
	for (int r = 0; r < height; r++) {
		// place a part of the piece
		board[r + dr] |= (p.rows[r] >> dc);
	}

	// the piece is placed sucessfully
	return true;
}

inline bool is_all_pieces_placed(piece pieces[N_PIECE]) {
	for (int i = 0; i < N_PIECE; i++) {
		if (!pieces[i].is_placed) {
			return false;
		}
	}
	return true;
}

bool is_all_pieces_placable(piece pieces[N_PIECE], t_row board[MAX_BOARD_SIZE], int board_size) {
	for (int r = 0; r < board_size; r++) {
		for (int c = 0; c < board_size; c++) {
			if (is_1_at(board[r], c)) continue;

			// need to place some piece here

			// find a piece not placed yet
			for (int i = 0; i < N_PIECE; i++) {
				if (pieces[i].is_placed) continue;

				// try to place the piece

				int dr = r;
				int dc = c - pieces[i].first_top_part_position;

				// check if the piece out of the board
				if (dr + pieces[i].height > board_size || dc < 0 || dc + pieces[i].width > board_size) {
					continue;
				}

				pieces[i].dr = dr;
				pieces[i].dc = dc;

				// check if the piece can be placed
				if (place_piece(pieces[i], board)) {
					pieces[i].is_placed = true;

					// check if all pieces are placed
					if (is_all_pieces_placed(pieces)) {
						return true;
					}

					// try to place other pieces
					if (is_all_pieces_placable(pieces, board, board_size)) {
						return true;
					}

					// some pieces are not placed
					// revert the piece
					remove_piece(pieces[i], board, board_size);
					pieces[i].is_placed = false;
				}
			}

			// if no piece can be placed, then go back to the previous cell
			return false;
		}
	}

	// NOTE: never reach here
	return true;
}

int main(void) {
	t_row board[MAX_BOARD_SIZE] = { 0 };
	piece pieces[N_PIECE];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the size of the board
	int board_size;
	cin >> board_size;

	// get the pieces
	int n_part = 0;
	for (int i = 0; i < N_PIECE; i++) {
		int width, height;
		cin >> height >> width;
		for (int r = 0; r < height; r++) {
			t_row row = 0;
			for (int c = 0; c < width; c++) {
				char ch;
				cin >> ch;
				if (ch == '#') {
					n_part++;
					add_1_at(row, c);
				}
			}
			pieces[i].rows[r] = row;
		}
		pieces[i].width = width;
		pieces[i].height = height;
		pieces[i].is_placed = false;
		pieces[i].first_top_part_position = get_first_part_position(pieces[i].rows[0]);
	}

	if (n_part == board_size * board_size && is_all_pieces_placable(pieces, board, board_size)) {
		// all pieces are placed
		print_board(pieces, board_size);
	} else {
		// no way to place the pieces
		cout << "gg";
	}

	return 0;
}
