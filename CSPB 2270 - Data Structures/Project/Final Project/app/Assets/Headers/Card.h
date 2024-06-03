// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef CARD_H
#define CARD_H
#include "../HPP/Utility.hpp"
/*  Structure PlayingCard - Struct to resemble a playing card
*   Data Members:
*       cardValue - Integer value that represents the value of a card
*       displayCardValue - String value that represents a modified version of the "cardValue" data member
*       displayRank - String value that represents a modified version of the "rank" data member
*       displaySuit - String value that represents a modified version of the "suit" data member
*       rank - String value that represents a cards rank
*       suit - String value that represents a cards suit
*/
struct PlayingCard {
    int cardValue;
    std::string displayCardValue;
    std::string displayRank;
    std::string displaySuit;
    std::string rank;
    std::string suit;
};
class Card {
public:
    // Constructors
    Card(const std::string inputRank, const std::string inputSuit); // Constructor
    Card() : card(std::make_shared<PlayingCard>()) {} // Default Constructor
    ~Card(); // De-Constructor
    // Class methods
    bool CheckCardParam(const std::string checking, const std::string feeding);
    friend std::ostream &operator<<(std::ostream &os, Card& currentCard) {
        os << currentCard.GetDisplayRank() << " of " << currentCard.GetDisplaySuit();
        return os;
    }
    // Setter Functions
    void SetCardValue(std::shared_ptr<PlayingCard> inputCard); // Mutates "cardValue"
    void SetDisplayCardValue(std::shared_ptr<PlayingCard> inputCard); // Mutates "displayCardValue"
    void SetDisplayRank(std::shared_ptr<PlayingCard> inputCard); // Mutates "displayRank"
    void SetDisplaySuit(std::shared_ptr<PlayingCard> inputCard); // Mutates "displaySuit"
    void SetNewCardValue(const int input); // Mutates "cardValue"
    // Getter Functions
    int& GetCardValue(); // Retrieves "cardValue"
    std::string& GetDisplayCardValue(); // Retrieves "displayCardValue"
    std::string& GetDisplayRank(); // Retrieves "displayRank"
    std::string& GetDisplaySuit(); // Retrieves "displaySuit"
    std::string& GetRank(); // Retrieves "rank"
    std::string& GetSuit(); // Retrieves "suit"
private:
    std::shared_ptr<PlayingCard> card; // Private data member that encapsulates the PlayingCard structure
};
#endif