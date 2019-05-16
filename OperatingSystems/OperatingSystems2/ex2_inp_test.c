int main() {
    int board[4][4] = {{0, 4, 2, 2},//0044
                       {2, 2, 2, 4},//0244
                       {2, 2, 4, 0},//0044
                       {2, 2, 4, 8}};//0448
    int temp;
    for (int k = 0; k < 4; ++k) {
        for (int i = 4 - 1; i > 0; --i) {
            if (board[k][i] != 0) {
                for (int j = i - 1; j >= 0; --j) {
                    if (board[k][j] != 0) {
                        if (board[k][i] == board[k][j]) {
                            board[k][j] += board[k][i];
                            board[k][i] = 0;
                            i = j - 1;
                        }
                        break;
                    }
                }
            }
        }
    }
    for (int l = 0; l < 4; ++l) {
        temp = 4 - 1;
        for (int i = 4 - 1; i >= 0; --i) {
            if (board[l][i] != 0) {
                if (i != temp) {
                    board[l][temp] = board[l][i];
                    board[l][i] = 0;
                }
                temp--;
            }
        }
    }
}