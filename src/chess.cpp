#include "game.h"
#include "minigames.h"
#include "scene.h"
#include <raylib.h>
#include <raymath.h>

enum ChessPieces {
  CHESS_NONE = 0,
  CHESS_PAWN_BLACK,
  CHESS_PAWN_WHITE,
  CHESS_HORSE_BLACK,
  CHESS_HORSE_WHITE,
  CHESS_ROOK_BLACK,
  CHESS_ROOK_WHITE,
  CHESS_BISHOP_BLACK,
  CHESS_BISHOP_WHITE,
  CHESS_QUEEN_BLACK,
  CHESS_QUEEN_WHITE,
  CHESS_KING_BLACK,
  CHESS_KING_WHITE
};

char letters[] = {0, 'P', 'H', 'R', 'B', 'Q', 'K'};

ChessPieces board[64] = {
    CHESS_ROOK_BLACK, CHESS_HORSE_BLACK,  CHESS_BISHOP_BLACK, CHESS_QUEEN_BLACK,
    CHESS_KING_BLACK, CHESS_BISHOP_BLACK, CHESS_HORSE_BLACK,  CHESS_ROOK_BLACK,
    CHESS_PAWN_BLACK, CHESS_PAWN_BLACK,   CHESS_PAWN_BLACK,   CHESS_PAWN_BLACK,
    CHESS_PAWN_BLACK, CHESS_PAWN_BLACK,   CHESS_PAWN_BLACK,   CHESS_PAWN_BLACK,
    CHESS_NONE,       CHESS_NONE,         CHESS_NONE,         CHESS_NONE,
    CHESS_NONE,       CHESS_NONE,         CHESS_NONE,         CHESS_NONE,
    CHESS_NONE,       CHESS_NONE,         CHESS_NONE,         CHESS_NONE,
    CHESS_NONE,       CHESS_NONE,         CHESS_NONE,         CHESS_NONE,
    CHESS_NONE,       CHESS_NONE,         CHESS_NONE,         CHESS_NONE,
    CHESS_NONE,       CHESS_NONE,         CHESS_NONE,         CHESS_NONE,
    CHESS_NONE,       CHESS_NONE,         CHESS_NONE,         CHESS_NONE,
    CHESS_NONE,       CHESS_NONE,         CHESS_NONE,         CHESS_NONE,
    CHESS_PAWN_WHITE, CHESS_PAWN_WHITE,   CHESS_PAWN_WHITE,   CHESS_PAWN_WHITE,
    CHESS_PAWN_WHITE, CHESS_PAWN_WHITE,   CHESS_PAWN_WHITE,   CHESS_PAWN_WHITE,
    CHESS_ROOK_WHITE, CHESS_HORSE_WHITE,  CHESS_BISHOP_WHITE, CHESS_QUEEN_WHITE,
    CHESS_KING_WHITE, CHESS_BISHOP_WHITE, CHESS_HORSE_WHITE,  CHESS_ROOK_WHITE,
};

static bool change_pos = false;
static int index = -1;
static int turn = 1;

static bool isMoveValid(int src, int dest) {
  if (src >= 64 || src < 0 || dest >= 64 || dest < 0 ||
      board[src] == CHESS_NONE ||
      (board[dest] != CHESS_NONE && (board[src] % 2 == board[dest] % 2))) {
    return false;
  }
  int startRow = src / 8;
  int startCol = src % 8;
  int endRow = dest / 8;
  int endCol = dest % 8;

  ChessPieces piece = board[src];

  switch (piece) {
  case CHESS_PAWN_BLACK:
  case CHESS_PAWN_WHITE:
    // Exemplo para Peão: pode mover 1 casa para frente
    if (piece == CHESS_PAWN_BLACK) {
      if ((endRow == startRow + 1 && startCol == endCol) ||
          (startCol == endCol && startRow == 1 && endRow == 3)) {
        return true; // Movimento simples de Peão Preto
      }
    } else {
      if (endRow == startRow - 1 && startCol == endCol ||
          (startCol == endCol && startRow == 6 && endRow == 4)) {
        return true; // Movimento simples de Peão Branco
      }
    }
    break;

  case CHESS_HORSE_BLACK:
  case CHESS_HORSE_WHITE:
    // Exemplo para Cavalo: movimentos em "L"
    if ((abs(startRow - endRow) == 2 && abs(startCol - endCol) == 1) ||
        (abs(startRow - endRow) == 1 && abs(startCol - endCol) == 2)) {
      return true;
    }
    break;

  case CHESS_ROOK_BLACK:
  case CHESS_ROOK_WHITE:
    // Exemplo para Torre: pode mover em linha reta
    if (startRow == endRow || startCol == endCol) {
      return true;
    }
    break;

  case CHESS_BISHOP_BLACK:
  case CHESS_BISHOP_WHITE:
    // Exemplo para Bispo: pode mover na diagonal
    if (abs(startRow - endRow) == abs(startCol - endCol)) {
      return true;
    }
    break;

  case CHESS_QUEEN_BLACK:
  case CHESS_QUEEN_WHITE:
    // Exemplo para Rainha: pode mover como Torre ou Bispo
    if ((startRow == endRow || startCol == endCol) ||
        (abs(startRow - endRow) == abs(startCol - endCol))) {
      return true;
    }
    break;

  case CHESS_KING_BLACK:
  case CHESS_KING_WHITE:
    // Exemplo para Rei: pode mover uma casa em qualquer direção
    if (abs(startRow - endRow) <= 1 && abs(startCol - endCol) <= 1) {
      return true;
    }
    break;

  default:
    return false; // Caso a posição de início esteja vazia ou peça inválida
  }
  return false;
}

static void ChessRender(void) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Color col, textcol;
      if (i + 8 * j == index || isMoveValid(index, i + 8 * j)) {
        col = GRAY;
      } else if (i % 2 == 0) {
        col = j % 2 == 0 ? DARKGRAY : LIGHTGRAY;
      } else {
        col = j % 2 == 0 ? LIGHTGRAY : DARKGRAY;
      }
      DrawRectangle(64 + 64 * i, 64 + 64 * j, 64, 64, col);
      DrawRectangleLines(64 + 64 * i, 64 + 64 * j, 64, 64, BLACK);
      ChessPieces piece = board[i + 8 * j];
      if (piece != CHESS_NONE) {
        textcol = piece % 2 == 1 ? BLACK : WHITE;
        char letter =
            piece % 2 == 1 ? letters[(piece + 1) / 2] : letters[piece / 2];
        DrawText(TextFormat("%c", letter), 64 + 64 * i + 8, 64 + 64 * j + 4, 64,
                 textcol);
      }
    }
  }
}

static void ChessHandleEvents(void) {
  if (change_pos && IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
    change_pos = false;
    index = -1;
    return;
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Rectangle pos = {static_cast<float>(64 + 64 * i),
                       static_cast<float>(64 + 64 * j), 64, 64};
      if (CheckCollisionPointRec(GetMousePosition(), pos) &&
          IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if (!change_pos && board[i + 8 * j] != CHESS_NONE &&
            turn % 2 != board[i + 8 * j] % 2) {
          change_pos = true;
          index = i + 8 * j;
        } else if (change_pos && index != i + 8 * j &&
                   isMoveValid(index, i + 8 * j)) {
          board[i + 8 * j] = board[index];
          board[index] = CHESS_NONE;
          change_pos = false;
          index = -1;
          turn++;
        }
      }
    }
  }
}

static const Scene ChessScene(ChessHandleEvents, nullptr, ChessRender);

void SetupChessMinigame() { game->scene = &ChessScene; }
