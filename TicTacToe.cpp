typedef
	enum{X=-1,B=0,O=1}
	piece;
class Board{
	piece board[3][3];
	public:
		void clear();
		void show();
		void play(int r, int c, piece p);
		void humanplay();
		void computerplay();
		bool isWinner();
		piece winner();
};
