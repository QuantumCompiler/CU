// // ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef HAND_H
#define HAND_H
#include "../HPP/Shoe.hpp"
#define BLOOMFILTERSIZE 10000
#define BLOOMFILTERITERATIONS 34
/*  Structure Player - Struct to resemble a playing card
*   Data Members:
*     Filter Values:
*       canBuyInsurance - String value that represents if a player is eligible to buy insurance
*       canDoubleDown - String value that represents if a player is eligible to double down
*       canSplitAces - String value that represents if a player is eligible to split Aces
*       canSplitHand - String value that represents if a player is eligible to split their hand (Without Aces present)
*       choseBuyInsurance - String value that represents if a player has chosen to buy insurance
*       choseDoubleDown - String value that represents if a player has chosen to double down
*       choseSplitAces - String value that represents if a player has chosen to split Aces
*       choseSplitHand - String value that represents if a player has chosen to split their hand (Without Aces present)
*       doubleDownResponse - String value that represents if a player has decided if they would like to double down or not
*       hasBlackjack - String value that represents if a player has blackjack in their current hand
*       hasHit - String value that represents if a player has hit on current hand or not
*       paramInHand - String value that represents if a player has a specific parameter in their hand
*       sameParamInHand - String value that represents if a player has the same specific parameter in their hand
*       shouldDoubleDown - String value that represents if a player should double down for a specific hand
*       shouldHit - String value that represents if a player should hit for a specific hand
*       shouldSplit - String value that represents if a player should split for a specific hand
*       shouldStand - String value that represents if a player should stand for a specific hand
*       softSeventeen - String value that represents if a player has a soft seventeen (Hand total of 17 with at least one Ace being counted as 11)
*       splitAcesResponse - String value that represents if a player has decided on if they would like to split Aces or not
*       splitHandResponse - String value that represents if a player has decided on if they would like to split their hand or not
*     Float Values:
*       bankTotal - Float value that represents the total value of a players currency they can play with
*       insuranceWager - Float value that represents the wager of which a player places for insurance
*       net - Float value that represents the net of a hand that has been played
*       wager - Float value that represents the wager that is placed on a hand that is being played
*     Integer Values:
*       cardsTotal - Integer value that represents the total value of a players hand of cards
*       handsBlackjack - Integer value that represents how many blackjack hands a player has had
*       handsCurrentlyHeld - Integer value that represents the number of individual hands that a player has
*       handsLost - Integer value that represents how many hands a player has lost
*       handsPlayed - Integer value that represents the number of total hands played by a player
*       handsPushed - Integer value that represents the number of total hands a player has pushed
*       handsWon - Integer value that represents the number of total hands a player has won
*     String Values:
*       displayBankTotal - String value that represents the modified private data member "bankTotal"
*       displayCardsTotal - String value that represents the modified private data member "cardsTotal"
*       displayInsuranceWager - String value that represents the modified private data member "insuranceWager"
*       displayName - String value that represents the modified private data member "name"
*       displayNet - String value that represents the modified private data member "net"
*       displayWager - String value that represents the modified private data member "wager"
*       name - String value that represents the name of a player
*     List Values:
*       handBankTotals - Linked list of float values that represent a players bank totals after each hand
*       handCardTotals - Linked list of integers that represent a players hand totals
*       handNets - Linked list of float values that represent a players nets after each hand
*       handPlayed - Linked list of integer values that represents the hand played in a game
*       handWagers - Linked list of float values that represent a players wager for each hand
*       playerCards - Linked list of Cards that represent a players cards
*/
struct Player {
    // BloomFilter Filters
    std::shared_ptr<BloomFilter> bloomFilter;
    // Filter Values
    std::string canBuyInsurance = "CanBuyInsurance";
    std::string canDoubleDown = "CanDoubleDown";
    std::string canSplitAces = "CanSplitAces";
    std::string canSplitHand = "CanSplitHand";
    std::string choseBuyInsurance = "ChoseBuyInsurance";
    std::string choseDoubleDown = "ChoseDoubleDown";
    std::string choseSplitAces = "ChoseSplitAces";
    std::string choseSplitHand = "ChoseSplitHand";
    std::string doubleDownResponse = "DoubleDownResponse";
    std::string hasBlackjack = "HasBlackjack";
    std::string hasHit = "HasHit";
    std::string paramInHand = "ParamInHand";
    std::string sameParamInHand = "SameParamInHand";
    std::string shouldDoubleDown = "ShouldDoubleDown";
    std::string shouldHit = "ShouldHit";
    std::string shouldSplit = "ShouldSplit";
    std::string shouldStand = "ShouldStand";
    std::string softSeventeen = "SoftSevenTeen";
    std::string splitAcesResponse = "SplitAcesResponse";
    std::string splitHandResponse = "SplitHandResponse";
    // Filter Matrix
    std::vector<std::vector<std::string>> filterMatrix = {
        {canBuyInsurance, canDoubleDown, canSplitAces, canSplitHand, choseBuyInsurance},
        {choseDoubleDown, choseSplitAces, choseSplitHand, doubleDownResponse, hasBlackjack},
        {hasHit, paramInHand, sameParamInHand, shouldDoubleDown, shouldHit},
        {shouldSplit, shouldStand, softSeventeen, splitAcesResponse, splitHandResponse}
    };
    // Float Values
    float bankTotal;
    float insuranceWager;
    float net;
    float wager;
    // Integer Values
    int cardsTotal;
    int handsBlackjack;
    int handsCurrentlyHeld;
    int handsLost;
    int handsPlayed;
    int handsPushed;
    int handsWon;
    // Strings
    std::string displayBankTotal;
    std::string displayCardsTotal;
    std::string displayInsuranceWager;
    std::string displayName;
    std::string displayNet;
    std::string displayWager;
    std::string name;
    // Lists
    std::shared_ptr<LinkedList<float>> handBankTotals;
    std::shared_ptr<LinkedList<int>> handCardTotals;
    std::shared_ptr<LinkedList<float>> handNets;
    std::shared_ptr<LinkedList<int>> handPlayed;
    std::shared_ptr<LinkedList<float>> handWagers;
    std::shared_ptr<LinkedList<Card>> playerCards;
};
class Hand {
public:
    // Constructors
    Hand(); // Constructor
    ~Hand(); // De-Constructor
    // Class Functions
    Hand AddCardToHand(std::shared_ptr<node<Card>>& input); // Adds card to hand
    Hand AddHandTotal(); // Adds current hand total
    Hand BankDepositPrompt(); // Deposits currency into a players bank
    Hand BankDepositSim(const float& input); // Deposits currency into a players bank for a simulated game
    Hand CheckBlackJack(); // Checks for if a player has blackjack
    Hand CheckParamInHand(const std::string referenceParameter, const std::string checkingParameter); // Checks if a player has a specific parameter in their hand
    Hand CheckSameParamInHand(const std::string referenceParameter, const std::string checkingParameter = ""); // Checks if a player has the same parameter in their hand
    Hand CopyVariables(std::shared_ptr<Hand>& input);
    Hand HitHand(std::shared_ptr<Shoe>& input); // Adds a card to a players hand from a shoe
    Hand InsurancePrompt(); // Prompts a player if they would like to place an insurance wager
    Hand InsuranceSim(const bool& input); // Places an insurance wager for a simulate hand
    Hand NamePrompt(); // Prompts the player for a name that they would like to be called
    Hand NameSim(const std::string& input); // Sets the name of a player of a hand for a simulated game
    Hand ParametersCheck(std::shared_ptr<Hand>& dealerHand); // Checks for certain parameters of how a player can play their hand
    Hand PlaceWagerPrompt(); // Prompts a player for how much currency they would like to place as a wager for a hand
    Hand PlaceWagerSim(const float& input); // Places the wager for a players hand in a simulated game
    Hand ResetHand(); // Resets certain parameters for a players hand
    Hand ShowHand(std::string option = "", const std::string dealerShow = ""); 
    Hand UpdateBank(const int choice, const float& wager); // Updates the bank total of a player
    // Setter Functions
    // Float Values
    void SetBankTotal(const float& input); // Mutates "bankTotal"
    void SetInsuranceWager(const float& input); // Mutates "insuranceWager"
    void SetNet(const float& input); // Mutates "net"
    void SetWager(const float& input); // Mutates "wager"
    // Integer Values
    void SetCardsTotal(const int& input); // Mutates "cardsTotal"
    void SetHandsBlackjack(const int& input); // Mutates "handsBlackjack"
    void SetHandsCurrentlyHeld(const int& input); // Mutates "handsCurrentlyHeld"
    void SetHandsLost(const int& input); // Mutates "handsLost"
    void SetHandsPlayed(const int& input); // Mutates "handsPlayed"
    void SetHandsPushed(const int& input); // Mutates "handsPushed"
    void SetHandsWon(const int& input); // Mutates "handsWon"
    // String Values
    void SetDisplayBankTotal(); // Mutates "displayBankTotal"
    void SetDisplayCardsTotal(); // Mutates "displayCardsTotal"
    void SetDisplayInsuranceWager(); // Mutates "displayInsuranceWager"
    void SetDisplayName(); // Mutates "displayName"
    void SetDisplayNet(); // Mutates "displayNet"
    void SetDisplayWager(); // Mutates "displayWager"
    void SetName(const std::string& input); // Mutates "name"
    // List Values
    void SetHandBankTotals(std::shared_ptr<node<float>>& input); // Mutates "handBankTotals"
    void SetHandCardTotals(std::shared_ptr<node<int>>& input); // Mutates "handCardTotals"
    void SetHandNets(std::shared_ptr<node<float>>& input); // Mutates "handNets"
    void SetHandPlayed(std::shared_ptr<node<int>>& input); // Mutates "handPlayed"
    void SetHandWagers(std::shared_ptr<node<float>>& input); // Mutates "handWagers"
    void SetPlayerCards(std::shared_ptr<node<Card>>& input); // Mutates "playerCards"
    void SetPlayerHands(std::shared_ptr<node<std::shared_ptr<Hand>>>& input); // Mutates "playerHands"
    // Getter Functions
    // Filter Values
    std::shared_ptr<BloomFilter>& GetBloomFilter(); // Retrieves "bloomFilter"
    std::vector<std::vector<std::string>>& GetFilterMatrix(); // Retrieves "filterMatrix"
    // Float Values
    float& GetBankTotal(); // Retrieves "bankTotal"
    float& GetInsuranceWager(); // Retrieves "insuranceWager"
    float& GetNet(); // Retrieves "net"
    float& GetWager(); // Retrieves "wager"
    // Integer Values
    int& GetCardsTotal(); // Retrieves "cardsTotal"
    int& GetHandsBlackjack(); // Retrieves "handsBlackjack"
    int& GetHandsCurrentlyHeld(); // Retrieves "handsCurrentlyHeld"
    int& GetHandsLost(); // Retrieves "handsLost"
    int& GetHandsPlayed(); // Retrieves "handsPlayed"
    int& GetHandsPushed(); // Retrieves "handsPushed"
    int& GetHandsWon(); // Retrieves "handsWon"
    // String Values
    std::string& GetDisplayBankTotal(); // Retrieves "displayBankTotal"
    std::string& GetDisplayCardsTotal(); // Retrieves "displayCardsTotal"
    std::string& GetDisplayInsuranceWager(); // Retrieves "displayInsuranceWager"
    std::string& GetDisplayName(); // Retrieves "displayName"
    std::string& GetDisplayNet(); // Retrieves "displayNet"
    std::string& GetDisplayWager(); // Retrieves "displayWager"
    std::string& GetName(); // Retrieves "name"
    // List Values
    std::shared_ptr<LinkedList<float>>& GetHandBankTotals(); // Retrieves "handBankTotals"
    std::shared_ptr<LinkedList<int>>& GetHandCardTotals(); // Retrieves "handCardTotals"
    std::shared_ptr<LinkedList<float>>& GetHandNets(); // Retrieves "handNets"
    std::shared_ptr<LinkedList<int>>& GetHandPlayed(); // Retrieves "handPlayed"
    std::shared_ptr<LinkedList<float>>& GetHandWagers(); // Retrieves "handWagers"
    std::shared_ptr<LinkedList<Card>>& GetPlayerCards(); // Retrieves "playerCards"
    std::shared_ptr<LinkedList<std::shared_ptr<Hand>>>& GetPlayerHands(); // Retrieves "playerHands"
private:
    std::shared_ptr<Player> player; // Private data member that encapsulates the Player structure
    std::shared_ptr<LinkedList<std::shared_ptr<Hand>>> hands; // Private data member for the hands of a player
};

#endif