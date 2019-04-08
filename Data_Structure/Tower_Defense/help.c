#include "towerDefence.h"
void drawTower2(int y, int x){
	attron(COLOR_PAIR(4));
	mvprintw(y, x, "   ");
	mvprintw(y+1, x, "   ");
	mvprintw(y+2, x, "   ");
	attroff(COLOR_PAIR(4));
}

void help(){
	int command;
	clear();
	
	drawBox(0, 0, 47, 85);

	drawCursor(3, 2);
	drawCursor(3, 12);
	drawTower2(4, 13);
	
	mvprintw(3, 24, "First, you have to select a position to build a tower.");
	mvprintw(4, 24, "You can use a direction key to move a cursor.");
	mvprintw(5, 24, "After moving a cursor, press 't' to build a tower!");
	mvprintw(6, 24, "But remember! You need 100 money to build a tower.");


	mvprintw(14, 7, "@");
	mvprintw(14, 5, "@");
	
	mvprintw(12, 9, "@");
	mvprintw(10, 9, "@");
	
	mvprintw(16, 9, "@");
	mvprintw(18, 9, "@");
	
	mvprintw(14, 11, "@");
	mvprintw(14, 13, "@");
	drawTower2(13, 8);
	
	mvprintw(13, 24, "Secondly, you have to choose a direction of tower.");
	mvprintw(14, 24, "After pressing 't', press one of direction keys");
	mvprintw(15, 24, "Bullets will goes on that direction.");


	attron(A_REVERSE);
	mvprintw(21, 5, "         ");
	mvprintw(23, 5, "         ");
	mvprintw(25, 5, "         ");
	
	mvprintw(29, 3, "   ");
	mvprintw(29, 9, "   ");
	mvprintw(29, 15, "   ");
	attroff(A_REVERSE);

	attron(COLOR_PAIR(6));
	mvprintw(23, 5, "!!!");
	mvprintw(25, 11, "!!!");
	mvprintw(29, 3, "!");
	mvprintw(29, 10, "!");
//	mvprintw(31, 17, "!");
	attroff(COLOR_PAIR(6));
	
	mvprintw(27, 4, "@");
	mvprintw(28, 10, "@");

	mvprintw(21, 24, "After building your first tower,");
	mvprintw(22, 24, "enemies will begin to appear at the start point.");
	mvprintw(23, 24, "Enemies follow the path. If enemy arrive at the end of path,");
	mvprintw(24, 24, "your life point will decrease by 1 point.");
	mvprintw(25, 24, "If your life point goes down to 0,then GAME OVER!");
	
	mvprintw(28, 24, "When a bullet hits an enemy, an enemy's hp will decrease.");
	mvprintw(29, 24, "An enemy dies if its hp equal to 0."); 
	mvprintw(30, 24, "And you'll get some money.");


	drawTower2(33, 3);
	mvprintw(36, 4, "@");
	mvprintw(40, 4, "@");
	drawCursor(32, 8);
	drawTower2(33, 9);
	drawTower2(33, 15);
	mvprintw(36, 16, "@");
	mvprintw(38, 16, "@");
	mvprintw(40, 16, "@");
	

	mvprintw(34, 24, "You can also upgrade your towers!");
	mvprintw(35, 24, "Move cursor to select the tower which you wish to upgrade.");
	mvprintw(36, 24, "After selecting the tower, press 'u' to upgrade the tower.");
	mvprintw(37, 24, "Upgrade makes bullets more powerfully and rapidly!");
	mvprintw(38, 24, "Warning! Upgrade costs a lot of money.");
	
	attron(A_REVERSE);
	mvprintw(41,1,"                                      BASIC KEYS                                     ");
	attroff(A_REVERSE);
	mvprintw(43, 24, " Direction keys : Move cursor ");
	mvprintw(44, 24, " Alphabet 't'   : Build a tower ");
	mvprintw(45, 24, " Alphabet 'u'   : Upgrade a tower ");
	mvprintw(46, 24, " Alphabet 'q'   : Quit the game ");

	attron(COLOR_PAIR(1));
	mvprintw(0, 1,"              ------------------------HOW To PLAY-------------------------");
	mvprintw(48,1,"              -------------------Press Any key to quit--------------------");
	refresh();
	attroff(COLOR_PAIR(1));
	wgetch(stdscr);	
	wgetch(stdscr);
}
