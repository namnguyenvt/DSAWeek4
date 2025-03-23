/*
 * HexGame.h
 *
 *  Created on: 1/03/2025
 *      Author: dongmo
 */

#ifndef NASHGAME_H_
#define NASHGAME_H_

class NashGame {
private:
	Board *board;
	Player *player[2];
public:
	NashGame(Board *b, Player *p1, Player *p2) {
		board = b;
		player[0] = p1;
		player[1] = p2;
	}

	void play();
};

void NashGame::play() {
	int won = 0;
	bool isFull = false;
	board->printBoard();

	while (!won && !isFull) {

		int playerType = board->getTurn();
		int playerIndex = (playerType == player[0]->getType()) ? 0 : 1;
		int x = -1;
		int y = -1;

		if (!player[playerIndex]->getMove(board, x, y)) {
			cout << "No available move" << endl;
			return;
		}

		cout << player[playerIndex]->getPlayerName() << " plays " << " ("
				<< x + 1 << ", " << y + 1 << "):" << endl;

		if (!board->addMove(playerType, x, y))
			return;

		board->printBoard();
		if (board->isBoardFull() == false) {
			isFull = true;
		}
		won = board->checkWinningStatus(playerType);
        if(won == playerType)
        	cout << player[playerIndex]->getPlayerName() << " player wins!" << endl;

	}
}

#endif /* NASHGAME_H_ */
