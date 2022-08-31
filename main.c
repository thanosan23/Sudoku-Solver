#include "util/std.h"
#include "util/util.h"

// Fill board in 'board.txt'
u8 grid[9][9];

typedef struct {
  u8 row;
  u8 col;
} Pos;

bool isEnd(Pos pos) {
  return pos.row == 9 && pos.col == 0;
}

void setValue(Pos pos, u8 val) {
  assert(pos.row <= 8 && pos.col <= 8, "Not a valid position.");
  grid[pos.row][pos.col] = val;
}

bool getValue(Pos pos) {
  assert(pos.row <= 8 && pos.col <= 8, "Not a valid position.");
  return grid[pos.row][pos.col];
}

bool valid(u8 grid[9][9], u8 row, u8 col, u8 value) {
  bool ret = true;
  // check inner grids
  u8 boxRow = (row/3) * 3;
  u8 boxCol = (col/3) * 3;

  for(u8 i = boxRow; i < boxRow+3; i++) {
    for(u8 j = boxCol; j < boxCol+3; j++) {
      if(grid[i][j] == value) ret = false;
    }
  }

  // check rows and cols
  for(u8 i = 0; i < 9; i++) {
    if(grid[row][i] == value) ret = false;
  }
  for(u8 i = 0; i < 9; i++) {
    if(grid[i][col] == value) ret = false;
  }

  return ret;
}

Pos nextCell(u8 grid[9][9], Pos pos) {
  pos.col += 1;
  if(pos.col > 8) {
    pos.row++;
    pos.col = 0;
  }
  Pos ret;
  ret.row = pos.row;
  ret.col = pos.col;
  return ret;
}

bool dfs(u8 grid[9][9], Pos pos) {
  if(isEnd(pos)) return true;
  if(getValue(pos) == 0) {
    // try all possible values
    bool found = false;
    for(u8 i = 1; i <= 9; i++) {
      if(valid(grid, pos.row, pos.col, i)) {
        setValue(pos, i);
        if(dfs(grid, nextCell(grid, pos))) {
          found = true;
        }
      }
      if(found) {
        return true;
      } else {
        setValue(pos, 0);
      }
    }
  } else {
    // go the next cell
    return dfs(grid, nextCell(grid, pos));
  }

  return false;
}

int main(UNUSED int argc, UNUSED char *argv[]) {

  f32 startTime = NOW();

  // Parse file into a 2D array
  FILE *file = fopen("board.txt", "r");
  if(file == NULL) {
    printf("File does not exist\n");
    exit(1);
  }
  u8 *buffer = read_file(file);
  u8 gridIdx = -1;
  for(u32 i = 0; buffer[i] != 0; i++) {
    // only consider numerical elements
    if(buffer[i] >= '0' && buffer[i] <= '9') {
      // put number on the grid
      gridIdx++;
      assert(gridIdx<81, "Grid is too big!");
      grid[gridIdx/9][gridIdx%9] = buffer[i] - '0';
    }
  }
  assert(gridIdx==80, "Grid is not the right size!");

  fclose(file);
  free(buffer);

  // Run the main algorithm
  Pos start = { 0, 0 };
  u8 result = dfs(grid, start);

  if(result == 1) {
    // Show the grid
    for(u8 i = 0; i < 9; i++) {
      for(u8 j = 0; j < 9; j++) {
        printf("%d ", grid[i][j]);
      }
      printf("\n");
    }
  } else {
    printf("No Solution.");
  }

  // Log elapsed time
  f32 endTime = NOW();
  LOG("Finished in %fs.", (endTime-startTime)/NS);

  return 0;
}
