#include "chess.h"
#include "game.h"
#include "minigames.h"
#include "scene.h"
#include <cstdio>
#include <raylib.h>
#include <raymath.h>

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

static Texture2D texture;

static union {
  int value;
  struct {
    bool white_king_moved : 1;
    bool left_white_rook_moved : 1;
    bool right_white_rook_moved : 1;
    bool white_castle : 1;
    bool black_king_moved : 1;
    bool left_black_rook_moved : 1;
    bool right_black_rook_moved : 1;
    bool black_castle : 1;
  };
} flags;

static bool isPathClear(int startPos, int endPos) {
  int startRow = startPos / 8;
  int startCol = startPos % 8;
  int endRow = endPos / 8;
  int endCol = endPos % 8;

  int rowDirection = (endRow > startRow) ? 1 : (endRow < startRow) ? -1 : 0;
  int colDirection = (endCol > startCol) ? 1 : (endCol < startCol) ? -1 : 0;

  int currentRow = startRow + rowDirection;
  int currentCol = startCol + colDirection;

  while (currentRow != endRow || currentCol != endCol) {
    int currentPos = currentRow * 8 + currentCol;
    if (board[currentPos] != CHESS_NONE) {
      return false; // Há uma peça no caminho
    }
    currentRow += rowDirection;
    currentCol += colDirection;
  }
  return true; // Caminho livre
}

static bool isKingInCheck(ChessPieces king) {
  int kingPosition = -1;
  for (int i = 0; i < 64; i++) {
    if (board[i] == king) {
      kingPosition = i;
      break;
    }
  }

  if (kingPosition == -1) {
    return false; // Rei não encontrado (erro de estado do tabuleiro)
  }

  int kingRow = kingPosition / 8;
  int kingCol = kingPosition % 8;

  // Verificar ameaça de peões
  if (king == CHESS_KING_WHITE) {
    if (kingRow > 0 && kingCol > 0 &&
        board[kingPosition - 9] == CHESS_PAWN_BLACK)
      return true;
    if (kingRow > 0 && kingCol < 7 &&
        board[kingPosition - 7] == CHESS_PAWN_BLACK)
      return true;
  } else {
    if (kingRow < 7 && kingCol > 0 &&
        board[kingPosition + 7] == CHESS_PAWN_WHITE)
      return true;
    if (kingRow < 7 && kingCol < 7 &&
        board[kingPosition + 9] == CHESS_PAWN_WHITE)
      return true;
  }

  // Verificar ameaça de cavalos
  int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                           {1, -2},  {1, 2},  {2, -1},  {2, 1}};
  for (auto &move : knightMoves) {
    int newRow = kingRow + move[0];
    int newCol = kingCol + move[1];
    int newPos = newRow * 8 + newCol;
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
      ChessPieces threat =
          (king == CHESS_KING_WHITE) ? CHESS_HORSE_BLACK : CHESS_HORSE_WHITE;
      if (board[newPos] == threat)
        return true;
    }
  }

  // Verificar ameaças de torre, rainha e bispo
  ChessPieces enemyRook =
      (king == CHESS_KING_WHITE) ? CHESS_ROOK_BLACK : CHESS_ROOK_WHITE;
  ChessPieces enemyBishop =
      (king == CHESS_KING_WHITE) ? CHESS_BISHOP_BLACK : CHESS_BISHOP_WHITE;
  ChessPieces enemyQueen =
      (king == CHESS_KING_WHITE) ? CHESS_QUEEN_BLACK : CHESS_QUEEN_WHITE;

  // Verificar ameaças horizontais e verticais (torre e rainha)
  for (int dir = -1; dir <= 1; dir += 2) {
    for (int offset = dir; kingCol + offset >= 0 && kingCol + offset < 8;
         offset += dir) {
      int pos = kingRow * 8 + (kingCol + offset);
      if (board[pos] != CHESS_NONE) {
        if (board[pos] == enemyRook || board[pos] == enemyQueen)
          return true;
        break;
      }
    }
    for (int offset = dir; kingRow + offset >= 0 && kingRow + offset < 8;
         offset += dir) {
      int pos = (kingRow + offset) * 8 + kingCol;
      if (board[pos] != CHESS_NONE) {
        if (board[pos] == enemyRook || board[pos] == enemyQueen)
          return true;
        break;
      }
    }
  }

  // Verificar ameaças diagonais (bispo e rainha)
  for (int dirRow = -1; dirRow <= 1; dirRow += 2) {
    for (int dirCol = -1; dirCol <= 1; dirCol += 2) {
      for (int offset = 1;; ++offset) {
        int newRow = kingRow + dirRow * offset;
        int newCol = kingCol + dirCol * offset;
        if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8)
          break;
        int pos = newRow * 8 + newCol;
        if (board[pos] != CHESS_NONE) {
          if (board[pos] == enemyBishop || board[pos] == enemyQueen)
            return true;
          break;
        }
      }
    }
  }

  return false; // Nenhuma ameaça detectada
}

static bool isMoveValid(int src, int dest) {
  if (src >= 64 || src < 0 || dest >= 64 || dest < 0 ||
      board[src] == CHESS_NONE || board[src] % 2 == turn % 2 ||
      (board[dest] != CHESS_NONE && (board[src] % 2 == board[dest] % 2))) {
    return false;
  }
  int startRow = src / 8;
  int startCol = src % 8;
  int endRow = dest / 8;
  int endCol = dest % 8;

  ChessPieces piece = board[src];
  ChessPieces kingturn = (ChessPieces)(CHESS_KING_BLACK + turn % 2);

  ChessPieces newboard[64];
  for (int i = 0; i < 64; i++) {
    newboard[i] = board[i];
  }
  for (int i = 0; i < 64; i++) {
    board[i] = newboard[i];
  }

  bool simulate = false;

  switch (piece) {
  case CHESS_PAWN_BLACK:
    if ((board[dest] != CHESS_NONE && board[dest] % 2 == 0 &&
         (endRow - startRow == 1 && abs(endCol - startCol) == 1)) ||
        (((endRow == startRow + 1 && startCol == endCol) ||
          (startCol == endCol && startRow == 1 && endRow == 3)) &&
         isPathClear(src, dest) && board[dest] == CHESS_NONE)) {
      simulate = true; // Movimento simples de Peão Preto
    }
    break;
  case CHESS_PAWN_WHITE:
    if ((board[dest] != CHESS_NONE && board[dest] % 2 == 1 &&
         (endRow - startRow == -1 && abs(endCol - startCol) == 1)) ||
        ((endRow == startRow - 1 && startCol == endCol ||
          (startCol == endCol && startRow == 6 && endRow == 4)) &&
         isPathClear(src, dest) && (board[dest] == CHESS_NONE))) {
      simulate = true; // Movimento simples de Peão Branco
    }
    break;

  case CHESS_HORSE_BLACK:
  case CHESS_HORSE_WHITE:
    // Exemplo para Cavalo: movimentos em "L"
    if ((abs(startRow - endRow) == 2 && abs(startCol - endCol) == 1) ||
        (abs(startRow - endRow) == 1 && abs(startCol - endCol) == 2)) {
      simulate = true;
    }
    break;

  case CHESS_ROOK_BLACK:
  case CHESS_ROOK_WHITE:
    // Exemplo para Torre: pode mover em linha reta
    if ((startRow == endRow || startCol == endCol) && isPathClear(src, dest)) {
      simulate = true;
    }
    break;

  case CHESS_BISHOP_BLACK:
  case CHESS_BISHOP_WHITE:
    // Exemplo para Bispo: pode mover na diagonal
    if (abs(startRow - endRow) == abs(startCol - endCol) &&
        isPathClear(src, dest)) {
      simulate = true;
    }
    break;

  case CHESS_QUEEN_BLACK:
  case CHESS_QUEEN_WHITE:
    // Exemplo para Rainha: pode mover como Torre ou Bispo
    if (((startRow == endRow || startCol == endCol) ||
         (abs(startRow - endRow) == abs(startCol - endCol))) &&
        isPathClear(src, dest)) {
      simulate = true;
    }
    break;

  case CHESS_KING_BLACK:
    if (src == 4 && dest == 6 && board[5] == CHESS_NONE &&
        board[6] == CHESS_NONE && !flags.black_king_moved &&
        !flags.right_black_rook_moved && !isKingInCheck(CHESS_KING_BLACK) &&
        !flags.black_castle) {
      simulate = true;
    } else if (abs(startRow - endRow) <= 1 && abs(startCol - endCol) <= 1 &&
               isPathClear(src, dest)) {
      simulate = true;
    }
    break;
  case CHESS_KING_WHITE:
    if (src == 60 && dest == 62 && board[61] == CHESS_NONE &&
        board[62] == CHESS_NONE && !flags.white_king_moved &&
        !flags.right_white_rook_moved && !isKingInCheck(CHESS_KING_WHITE) &&
        !flags.white_castle) {
      simulate = true;
    }
    // Exemplo para Rei: pode mover uma casa em qualquer direção
    else if (abs(startRow - endRow) <= 1 && abs(startCol - endCol) <= 1 &&
             isPathClear(src, dest)) {
      simulate = true;
    }
    break;

  default:
    simulate = false; // Caso a posição de início esteja vazia ou peça inválida
  }

  if (!simulate) {
    return false;
  }

  board[dest] = board[src];
  board[src] = CHESS_NONE;

  bool status;
  if (isKingInCheck(kingturn)) {
    status = false;
  } else {
    status = true;
  }

  board[src] = newboard[src];
  board[dest] = newboard[dest];

  return status;
}

static int countValidMoves() {
  int count = 0;
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      if (isMoveValid(i, j)) {
        count++;
      }
    }
  }
  return count;
}

static void ChessRender(void) {
  if (countValidMoves() == 0) {
    DrawText("MATE", 600, 50, 64, RED);
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Color col;
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
        DrawTexturePro(
            texture,
            {static_cast<float>(
                 798 - 133 * (piece % 2 == 0 ? (piece) / 2 : (piece + 1) / 2)),
             static_cast<float>(133 * (piece % 2)), 133, 133},
            {static_cast<float>(64 + 64 * i), static_cast<float>(64 + 64 * j),
             64, 64},
            {0, 0}, 0, WHITE);
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
          if (!flags.white_castle && !flags.white_king_moved &&
              !flags.right_white_rook_moved && index == 60 && i + 8 * j == 62 &&
              board[i + 8 * j] == CHESS_KING_WHITE) {
            board[61] = board[63];
            board[63] = CHESS_NONE;
            flags.white_castle = true;
          } else if (!flags.black_castle && !flags.black_king_moved &&
                     !flags.right_black_rook_moved && index == 4 &&
                     i + 8 * j == 6 && board[i + 8 * j] == CHESS_KING_BLACK) {
            board[5] = board[7];
            board[7] = CHESS_NONE;
            flags.black_castle = true;
          }
          if (!flags.right_white_rook_moved && index == 63 &&
              board[i + 8 * j] == CHESS_ROOK_WHITE) {
            flags.right_white_rook_moved = true;
          } else if (!flags.white_king_moved && index == 60 &&
                     board[i + 8 * j] == CHESS_KING_WHITE) {
            flags.white_king_moved = true;
          } else if (!flags.right_black_rook_moved && index == 7 &&
                     board[i + 8 * j] == CHESS_ROOK_BLACK) {
            flags.right_black_rook_moved = true;
          } else if (!flags.black_king_moved && index == 60 &&
                     board[i + 8 * j] == CHESS_KING_BLACK) {
            flags.black_king_moved = true;
          }
          change_pos = false;
          index = -1;
          turn++;
        }
      }
    }
  }
}

static const Scene ChessScene(ChessHandleEvents, nullptr, ChessRender);

void SetupChessMinigame() {
  game->scene = &ChessScene;
  flags.value = 0;
  texture = LoadTexture("assets/chess.png");
}
