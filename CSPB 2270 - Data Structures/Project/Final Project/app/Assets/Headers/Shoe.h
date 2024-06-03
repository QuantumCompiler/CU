// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef SHOE_H
#define SHOE_H
#include "../HPP/Card.hpp"
/*  Structure Deck - Struct that resembles a deck of cards
*   Data Members:
*       numOfDecks - Integer value that represents the number of decks in a shoe
*       cardsInShoe - Vector of Card objects that represents the number of cards in a shoe / deck
*       riggedCards - Vector of Card objects that represents the number of cards in a rigged shoe / deck
*/
struct Deck {
    int numOfDecks;
    std::shared_ptr<LinkedList<Card>> cards;
};
class Shoe {
public:
    // Constructors
    Shoe(); // Constructor
    ~Shoe(); // De-Constructor
    // Class Functions
    Shoe CopyShoe(const std::shared_ptr<Shoe> input);
    Shoe CreateShoePrompt(); // Creates shoe of cards
    Shoe CreateShoeSim(); // Creates a shoe for a simulate game
    std::shared_ptr<Card> Draw(); // Removes last card from shoe
    void EmptyShoe(); // Empties a shoe of cards
    void Shuffle(); // Shuffles shoe of cards
    // Setter Functions
    void SetCardsInShoe(std::shared_ptr<node<Card>>& input); // Mutates "cards"
    void SetNumOfDecks(const int input); // Mutates "numOfDecks"
    // Getter Functions
    int& GetNumOfDecks(); // Retrieves "numOfDecks"
    std::shared_ptr<LinkedList<Card>>& GetCardsInShoe(); // Retrieves "cards"
private:
    std::shared_ptr<Deck> deck; // Private data member that encapsulates the Deck structure
};

#endif