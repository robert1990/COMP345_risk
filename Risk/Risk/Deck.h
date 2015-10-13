#ifndef DECK_H
#define DECK_H

#include <vector>

class Deck {
public:
	struct Card {
		int card_id;
	};
	
	Deck();
	~Deck();
	
	Deck::Card draw_card();
	void return_card(Card card);
private:
	/*Member variables*/
	static const int max_deck_size = 30;
	std::vector<Card> current_deck;
	
	/*Member functions*/
	void initialize_deck();
	void shuffle_deck();
};

#endif