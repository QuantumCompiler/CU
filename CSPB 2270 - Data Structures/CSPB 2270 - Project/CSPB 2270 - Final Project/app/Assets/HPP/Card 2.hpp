// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Card.h"
// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  Constructor for Card class
*   Input:
*       inputRank - Constant string value that represents a cards rank
*       inputSuit - Constant string value that represents a cards suit
*   Initialization:
*       Create a card object on the heap
*       card->rank is set to inputRank
*       card->suit is set to inputSuit
*       SetCardValue, SetDisplayRank, SetDisplaySuit, SetDisplayCardValue functions are called to mutate private
*       data members
*/
Card::Card(const std::string inputRank, const std::string inputSuit) {
    card = std::make_shared<PlayingCard>();
    card->rank = inputRank;
    card->suit = inputSuit;
    SetCardValue(card);
    SetDisplayRank(card);
    SetDisplaySuit(card);
    SetDisplayCardValue(card);
}

// De-Constructor
Card::~Card() {}

/*  CheckCardParam - Checks to see if a specific parameter is present for a card
*   Input:
*       checkingParam - Constant string value that is being fed into function to check if it matches another
*       feedingParam - Constant string value that is being checked against the feeding parameter
*   Algorithm:
*       * Check to see if the "checkingParam" matches with the "checkingParam"
*   Output:
*       This function returns a boolean value indicating if the two parameters match
*/
bool Card::CheckCardParam(const std::string checkingParam, const std::string feedingParam) {
    return checkingParam == feedingParam;
}

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// SetCardValue - Mutates the private data member "cardValue" by assigning it to a cards correct value
void Card::SetCardValue(std::shared_ptr<PlayingCard> inputCard) {
    // Iterate through all possible ranks of cards
    for (int i = 0; i < 13; i++) {
        if (CheckCardParam(inputCard->rank, Ranks[i])) {
            switch (i) {
            // Set the default value of an Ace to 11
            case 0:
                card->cardValue = 11;
                break;
            // Set the value of 2 through 9 to their respective rank
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                card->cardValue = std::stoi(Ranks[i]);
                break;
            // Set the value of Jack, Queen, and King to 10
            case 10:
            case 11:
            case 12:
                card->cardValue = 10;
            default:
                break;
            }
        }
    }
}

// SetDisplayCardValue - Mutates the private data member "displayCardValue"
void Card::SetDisplayCardValue(std::shared_ptr<PlayingCard> inputCard) {
    card->displayCardValue = color_text(31, std::to_string(inputCard->cardValue));
}

// SetDisplayRank - Mutates the private data member "displayRank"
void Card::SetDisplayRank(std::shared_ptr<PlayingCard> inputCard) {
    card->displayRank = color_text(32, inputCard->rank);
}

// SetDisplaySuit - Mutates the private data member "displaySuit"
void Card::SetDisplaySuit(std::shared_ptr<PlayingCard> inputCard) {
    // Iterate through all possible suits of cards
    for (int i = 0; i < 4; i++) {
        if (CheckCardParam(inputCard->suit, Suits[i])) {
            switch (i) {
            // Set the color to purple for Clubs and Spades
            case 0:
            case 3:
                card->displaySuit = color_text(35, inputCard->suit);
                break;
            // Set the color to red for Diamonds and Hearts
            case 1:
            case 2:
                card->displaySuit = color_text(31, inputCard->suit);
                break;
            // Default to white for all other suits
            default:
                card->displaySuit = color_text(37, inputCard->suit);
                break;
            }
        }
    }
}

// SetNewCardValue - Mutates the private data member "cardValue" by assigning it to a new value
void Card::SetNewCardValue(const int input) {
    card->cardValue = input;
    SetDisplayCardValue(card);
}

// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetCardValue - Retrieves the private data member "cardValue"
int& Card::GetCardValue() {
    return card->cardValue;
}

// GetDisplayCardValue - Retrieves the private data member "displayCardValue"
std::string& Card::GetDisplayCardValue() {
    return card->displayCardValue;
}

// GetDisplayRank - Retrieves the private data member "displayRank"
std::string& Card::GetDisplayRank() {
    return card->displayRank;
}

// GetDisplaySuit - Retrieves the private data member "displaySuit"
std::string& Card::GetDisplaySuit() {
    return card->displaySuit;
}

// GetRank - Retrieves the private data member "rank"
std::string& Card::GetRank() {
    return card->rank;
}

// GetSuit - Retrieves the private data member "suit"
std::string& Card::GetSuit() {
    return card->suit;
}