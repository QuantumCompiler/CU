// // ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Hand.h"

// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  Constructor for Hand Class
*   Input:
*       There is no input required for constructing this class
*   Initialization:
*       Create necessary objects in construction
*       Boolean Values - All boolean values set to false
*       Float Values - All float values set to zero
*       Integer Values - All integer values set to zero
*       String Values - All string values set to empty
*       Vector Values - All vector values set to empty
*/
Hand::Hand() {
    // Object construction
    player = std::make_shared<Player>();
    player->handBankTotals = std::make_shared<LinkedList<float>>();
    player->handCardTotals = std::make_shared<LinkedList<int>>();
    player->handNets = std::make_shared<LinkedList<float>>();
    player->handPlayed = std::make_shared<LinkedList<int>>();
    player->handWagers = std::make_shared<LinkedList<float>>();
    player->playerCards = std::make_shared<LinkedList<Card>>();
    player->bloomFilter = std::make_shared<BloomFilter>(BLOOMFILTERSIZE, BLOOMFILTERITERATIONS);
    hands = std::make_shared<LinkedList<std::shared_ptr<Hand>>>();
    // Float Values Initialization
    this->SetBankTotal(0);
    this->SetInsuranceWager(0);
    this->SetNet(0);
    this->SetWager(0);
    // Integer Values Initialization
    this->SetCardsTotal(0);
    this->SetHandsBlackjack(0);
    this->SetHandsCurrentlyHeld(1);
    this->SetHandsLost(0);
    this->SetHandsPlayed(0);
    this->SetHandsPushed(0);
    this->SetHandsWon(0);
    // String Values Initialization
    this->GetDisplayBankTotal().clear();
    this->GetDisplayCardsTotal().clear();
    this->GetDisplayInsuranceWager().clear();
    this->GetDisplayName().clear();
    this->GetDisplayNet().clear();
    this->GetDisplayWager().clear();
    this->GetName().clear();
    // List Values Initialization
    this->GetHandBankTotals()->ClearList();
    this->GetHandCardTotals()->ClearList();
    this->GetHandNets()->ClearList();
    this->GetHandPlayed()->ClearList();
    this->GetHandWagers()->ClearList();
    this->GetPlayerCards()->ClearList();
    this->GetPlayerHands()->ClearList();
}

// De-Constructor
Hand::~Hand() {}

/*  AddCardToHand - Adds a card to a players hand
*   Input:
*       input - Card node passed by reference that represents the card being inserted into a hand
*   Algorithm:
*       * Calls the "SetCards" function and adds the input parameter "input" to the private data member ""
*       * Call "AddHandTotal" function to add up the total in the hand of the player
*   Output:
*       This function returns a Hand object
*/
Hand Hand::AddCardToHand(std::shared_ptr<node<Card>>& input) {
    // Add card to players hand and update hand total
    this->SetPlayerCards(input);
    this->AddHandTotal();
    return *this;
}

/*  AddHandTotal - Adds the hand total of a current player
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create two integer values; ace_count (Represents the number of aces in a hand), running_hand_value (A running hand value)
*       * Iterate through the cards in a players hand and count how many Aces are present in a players hand
*       * Iterate through the cards in a players hand and do the following:
*           * If the number of Aces in the hand is 1, then set the value of the Ace to 11
*           * If the number of Aces in the hand is greater than 1, then set the current value of the Ace to 1
*           * Update the "running_hand_value" by adding the current cards value to it
*           * Decrease the value of "ace_count" by one, then repeat the loop
*       * Iterate through the cards in a players hand if the "running_hand_value" is greater than 21
*           * If the current card is an Ace, set its value to 1, and add that card value to "running_hand_value"
*           * If the current card is not an Ace, then just add its value to "running_hand_value"
*       * Set the private data member "cardsTotal" to "running_hand_value" using SetCardsTotal
*   Output:
*       This function returns a Hand object after iterating through all the cards in a hand
*/
Hand Hand::AddHandTotal() {
    int ace_count = 0;
    int running_hand_value = 0;
    // Count number of Aces in hand
    std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->GetRoot();
    while (currentCard != nullptr) {
        if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), Ranks[0])) {
            ace_count += 1;
        }
        currentCard = currentCard->nextNode;
    }
    currentCard = this->GetPlayerCards()->GetRoot();
    // Change Ace values
    while (currentCard != nullptr) {
        if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), Ranks[0])) {
            // Change Ace value to 11
            if (ace_count == 1) {
                currentCard->data.SetNewCardValue(11);
            }
            // Change Ace value to 1
            else if (ace_count > 1) {
                currentCard->data.SetNewCardValue(1);
            }
        }
        ace_count -= 1;
        running_hand_value += currentCard->data.GetCardValue();
        currentCard = currentCard->nextNode;
    }
    currentCard = this->GetPlayerCards()->GetRoot();
    if (running_hand_value > 21) {
        running_hand_value = 0;
        while (currentCard != nullptr) {
            // If the card is an Ace, change the value of it to 1
            if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), Ranks[0])) {
                currentCard->data.SetNewCardValue(1);
                running_hand_value += currentCard->data.GetCardValue();
            }
            // If the card is not an Ace, just add value to running_hand_value
            else {
                running_hand_value += currentCard->data.GetCardValue();
            }
            currentCard = currentCard->nextNode;
        }
    }
    currentCard = this->GetPlayerCards()->GetRoot();
    this->SetCardsTotal(running_hand_value);
    return *this;
}

/*  BankDepositPrompt - Updates the private data member "bankTotal" to represent a players bank total
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * First create a float value that represents the bank total of a player prior to depositing
*       * Enter an error catching block that will help us determine if a player has entered a correct value for a bank total
*           * If the value entered is not a float, then we output an error message and clear the inputs
*           * If the value entered is a float or an integer
*               * We check to see if it is less than or equal to zero, if it is, we output an error message and require another input
*               * If it is greater than zero, then we set the private data member "bankTotal" to the "input" with SetBankTotal
*       * We then initialize some values for the statistics tracking of the player
*   Output:
*       This function returns a Hand object after depositing currency into a players bank
*/
Hand Hand::BankDepositPrompt() {
    float input;
    while (true) {
        // Prompt user for deposit
        std::cout << std::endl << "Please enter the amount you'd like to deposit into your bank: "; time_sleep(SHORT_TIME_SLEEP);
        std::cin >> input; time_sleep(SHORT_TIME_SLEEP);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        // Check if value is not a float or integer
        if (checkResult != "f" && checkResult != "i") {
            std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            clear_terminal();
            checkResult.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Check if value is a float or integer
        else if (checkResult == "f" || checkResult == "i") {
            if (input <= 0) {
                std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". Please re-enter a positive value." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                clear_terminal();
                checkResult.clear();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else {
                this->SetBankTotal(input);
                break;
            }
        }
    }
    std::cout << std::endl << this->GetDisplayName() << " has decided to start with: " << this->GetDisplayBankTotal() << std::endl; time_sleep(SHORT_TIME_SLEEP);
    return *this;
}

/*  BankDepositPrompt - Updates the private data member "bankTotal" to represent a players bank total for a simulated game
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * First create a float value that represents the bank total of a player prior to depositing
*   Output:
*       This function returns a Hand object after depositing currency into a players bank
*/
Hand Hand::BankDepositSim(const float& input) {
    this->SetBankTotal(input);
    return *this;
}

/*  CheckBlackJack - Checks to see if a player has blackjack
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Check to see if the player has an Ace in their hand first
*       * Begin by iterating through a hands cards
*       * First, check to see if the current card value in the hand has a value of 10
*           * If it does, proceed to return true if an Ace is also present and the hands size is only two
*           * Otherwise, continue through the hand
*       * Otherwise, proceed to check the next card in hand
*   Output:
*       This function returns a boolean value that determines if a player has a blackjack on deal
*/
Hand Hand::CheckBlackJack() {
    this->CheckParamInHand("R", Ranks[0]);
    // Iterate over cards
    std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->GetRoot();
    while (currentCard != nullptr) {
        // Check if there is a card in hand that has a value of 10
        if (currentCard->data.GetCardValue() == 10) {
            // Check if there is an Ace in the hand and the hand only has 2 cards
            if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[2][1]) && this->GetPlayerCards()->GetSize() == 2) {
                this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[1][4]);
                break;
            }
        }
        currentCard = currentCard->nextNode;
    }
    return *this;
}

/*  CheckParamInHand - Checks to see if there is a specific parameter found in a players hand
*   Input:
*       referenceParameter - Constant string value that represents the type of parameter we are looking for
*           "R" - This parameter represents rank
*           "S" - This parameter represents suit
*       checkingParameter - Constant string value that represents the parameter that we are searching for in a players hand
*   Algorithm:
*       * Start iterating through the cards of the player
*       * If the reference parameter that we are looking for is a rank
*           * We check to see if the current card matches the rank we are looking for by calling "CheckCardParam"
*           * Otherwise, we move on to the next card in the players hand
*       * If the reference parameter that we are looking for is a suit
*           * We check to see if the current card matches the suit we are looking for by calling "CheckCardParam"
*           * Otherwise, we move on to the next card in the players hand
*   Output:
*       This function returns a Hand object after checking if a specific parameter is present in a players hand
*/
Hand Hand::CheckParamInHand(const std::string referenceParameter, const std::string checkingParameter) {
    // Iterate over cards
    std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->GetRoot();
    while (currentCard != nullptr) {
        // If the "referenceParameter" is a rank, check for a rank
        if (referenceParameter == "R") {
            if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), checkingParameter)) {
                this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[2][1]);
                break;
            }
        }
        // If the "referenceParameter" is a suit, check for a suit
        else if (referenceParameter == "S") {
            if (currentCard->data.CheckCardParam(currentCard->data.GetSuit(), checkingParameter)) {
                this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[2][1]);
                break;
            }
        }
        currentCard = currentCard->nextNode;
    }
    return *this;
}

/*  CheckSameParamInHand - Checks to see if the same parameter is present in a players hand
*   Input:
*       referenceParameter - Constant string value that represents the type of parameter we are looking for
*           "R" - This parameter represents rank
*           "S" - This parameter represents suit
*       checkingParameter - Constant string value that represents the parameter that we are searching for in a players hand
*   Algorithm:
*       * Begin by iterating through the players hand, one card from the beginning of their hand
*       * Set the current card to the index of the vector
*       * If the "referenceParameter" is a Rank
*           * Return false if the current cards rank does not match the first cards rank or if the specific rank that is designated with "checkingParameter"
*             does not match that of the current card
*           * Otherwise, continue to the next card in the players hand
*       * If the "referenceParameter" is a Suit
*           * Return false if the current cards rank does not match the first cards suit or if the specific suit that is designated with "checkingParameter"
*             does not match that of the current card
*           * Otherwise, continue to the next card in the players hand
*       * Otherwise, if all the previous tests pass, then return true
*   Output:
*       This function returns a Hand object after checking if a specific parameter is the same in a players hand
*/
Hand Hand::CheckSameParamInHand(const std::string referenceParameter, const std::string checkingParameter) {
    std::vector<bool> filterCopy = this->GetBloomFilter()->GetFilter();
    this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[2][2]);
    // Iterate over the cards in a players hand
    for (int i = 1; i < this->GetPlayerCards()->GetSize(); i++) {
        std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->RetrieveNode(i);
        // If the "referenceParameter" is a rank, check for the same rank in a hand
        if (referenceParameter == "R") {
            if (!currentCard->data.CheckCardParam(currentCard->data.GetRank(), this->GetPlayerCards()->RetrieveNode(0)->data.GetRank()) || (!checkingParameter.empty() && !currentCard->data.CheckCardParam(currentCard->data.GetRank(), checkingParameter))) {
                this->GetBloomFilter()->GetFilter() = filterCopy;
                break;
            }
        }
        // If the "referenceParameter" is a suit, check for the same suit in a hand
        if (referenceParameter == "S") {
            if (!currentCard->data.CheckCardParam(currentCard->data.GetSuit(), this->GetPlayerCards()->RetrieveNode(0)->data.GetSuit()) || (!checkingParameter.empty() && !currentCard->data.CheckCardParam(currentCard->data.GetSuit(), checkingParameter))) {
                this->GetBloomFilter()->GetFilter() = filterCopy;
                break;
            }
        }
    }
    return *this;
}

/*  CopyVariables - Copies select data members from one hand to the current hand
*   Input:
*       input - Hand object passed by reference that is used to copy data members from
*   Algorithm:
*       * Copy the name of "input" for the current hand with SetName
*       * Copy the bank total of "input" for the current hand with SetBankTotal
*       * Copy the wager of "input" for the current hand with SetWager
*       * Copy the lists of the "input" hand
*   Output:
*       This function returns a Hand object after copying select variables
*/
Hand Hand::CopyVariables(std::shared_ptr<Hand>& input) {
    // Copy name, bank total, and wager to respective hand
    this->SetBankTotal(input->GetBankTotal());
    this->SetHandsCurrentlyHeld(input->GetHandsCurrentlyHeld());
    this->SetHandsPlayed(input->GetHandsPlayed());
    this->SetName(input->GetName());
    this->SetWager(input->GetWager());
    // Copy linked lists of player
    this->GetHandBankTotals() = input->GetHandBankTotals();
    this->GetHandCardTotals() = input->GetHandCardTotals();
    this->GetHandNets() = input->GetHandNets();
    this->GetHandPlayed() = input->GetHandPlayed();
    this->GetHandWagers() = input->GetHandWagers();
    this->GetPlayerHands() = input->GetPlayerHands();
    return *this;
}

/*  HitHand - Removes a hand from a given show and adds it a players hand
*   Input:
*       input - Shoe object that is passed by reference where a Card object is being pulled from
*   Algorithm:
*       * Call AddCardToHand() to add a card to the current players hand
*   Output:
*       This function returns a Hand object after adding a card to it
*/
Hand Hand::HitHand(std::shared_ptr<Shoe>& input) {
    // Add card to current hand
    std::shared_ptr<Card> drawnCard = input->Draw();
    std::shared_ptr<node<Card>> cardNode = this->GetPlayerCards()->InitNode(drawnCard);
    this->AddCardToHand(cardNode);
    return *this;
}

/*  InsurancePrompt - Prompts a player if they would like to buy insurance
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create a string and prompt the user if they would like to buy insurance
*       * Check to see if the input is yes or no
*           * If the input is yes, set the private data member "choseBuyInsurance" to true with "SetChoseBuyInsurance"
*           * If the input is no, set the private data member "choseBuyInsurance" to false with "SetChoseBuyInsurance"
*       * If the answer is not yes or no
*           * Through an output message
*           * Clear the inputs and go back to the beginning of the loop
*   Output:
*       This function returns a Hand object after prompting the user about buying insurance
*/
Hand Hand::InsurancePrompt() {
    std::string input;
    while (true) {
        // Prompt user for insurance
        std::cout << std::endl << "Would you like to buy insurance? Insurance pays (2:1). (y/n): "; time_sleep(SHORT_TIME_SLEEP);
        std::cin >> input; time_sleep(SHORT_TIME_SLEEP);
        // User has chosen to buy insurance, set insurance wager
        if (input == "y") {
            this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[0][4]);
            this->SetInsuranceWager(round_input(0.5*this->GetWager()));
            this->UpdateBank(0,this->GetInsuranceWager());
            return *this;
        }
        // User has chosen to not buy insurance, do not take insurance wager
        else if (input == "n") {
            return *this;
        }
        // Player did not enter a valid input for a response
        else {
            std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your insurance decision." << std::endl;
            input.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
}

/*  InsuranceSim - Determines if a player is to place an insurance wager in a simulated hand
*   Input:
*       input - Constant boolean value that is passed by reference that indicates if a player is going to place an insurance wager or not
*   Algorithm:
*       * Update the players bloom filter to indicate that they have placed an insurance wager
*       * Set the insurance wager for a player
*       * Withdraw the currency from a players bank
*   Output:
*       This function returns a Hand object after prompting the user about buying insurance
*/
Hand Hand::InsuranceSim(const bool& input) {
    if (input) {
        this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[0][4]);
        this->SetInsuranceWager(round_input(0.5*this->GetWager()));
        this->UpdateBank(0,this->GetInsuranceWager());
        return *this;
    }
    else {
        return *this;
    }
}

/*  NamePrompt - Prompts a user to input a name for their player
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create a string value "input" and prompt the user for what they want their name to be
*       * Call the "SetName" function to set the private data member "name" to "input"
*   Output:
*       This function returns a Hand object after prompting the user about what their name will be
*/
Hand Hand::NamePrompt() {
    std::string input;
    // Prompt user for their name
    std::cout << std::endl << "Please enter a name for your player: "; time_sleep(SHORT_TIME_SLEEP);
    std::getline(std::cin, input); time_sleep(SHORT_TIME_SLEEP);
    // Set the players name to "input"
    this->SetName(input);
    return *this;
}

/*  NameSim - Sets the name of a player of a hand for a simulated game
*   Input:
*       input - Constant string object that is passed by reference to be set to the players name
*   Algorithm:
*       * Call the "SetName" function to set the private data member "name" to "input"
*   Output:
*       This function returns a Hand object after prompting the user about what their name will be
*/
Hand Hand::NameSim(const std::string& input) {
    this->SetName(input);
    return *this;
}

/*  ParametersCheck - Checks to see if certain parameters in regards to wagering are met
*   Input:
*       dealerHand - Hand object passed by reference that represents the dealer's hand
*   Algorithm:
*       * This algorithm checks for specific parameters that pertain to how the player can play their hand
*       * The parameters that are checked are the following:
*           * Blackjack Check - Checks to see if the players have blackjack or not
*           * Insurance Check - Checks to see if the player is able to buy insurance for their hand
*           * Double Down Check - Checks to see if the player is able to double down for their hand
*           * Soft Seventeen Check - Checks to see if the player possesses a soft seventeen in their hand
*   Output:
*       This function returns a Hand object after checking the parameters in the current hand
*/
Hand Hand::ParametersCheck(std::shared_ptr<Hand>& dealerHand) {
    // Reset Parameters
    // Clear same parameter check
    if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[2][2])) {
        this->GetBloomFilter()->RemoveElement(this->GetFilterMatrix()[2][2]);
    }
    // Clear blackjack check
    if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[1][4])) {
        this->GetBloomFilter()->RemoveElement(this->GetFilterMatrix()[1][4]);
    }
    // Clear dealer blackjack
    if (dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[1][4])) {
        dealerHand->GetBloomFilter()->RemoveElement(dealerHand->GetFilterMatrix()[1][4]);
    }
    // Clear can split aces
    if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[0][2])) {
        this->GetBloomFilter()->RemoveElement(this->GetFilterMatrix()[0][2]);
    }
    // Clear can split hand
    if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[0][3])) {
        this->GetBloomFilter()->RemoveElement(this->GetFilterMatrix()[0][3]);
    }
    // Clear can buy insurance
    if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[0][0])) {
        this->GetBloomFilter()->RemoveElement(this->GetFilterMatrix()[0][0]);
    }
    // Clear can double down
    if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[0][1])) {
        this->GetBloomFilter()->RemoveElement(this->GetFilterMatrix()[0][1]);
    }
    // Clear soft seventeen
    if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[3][2])) {
        this->GetBloomFilter()->RemoveElement(this->GetFilterMatrix()[3][2]);
    }
    this->CheckSameParamInHand("R");
    this->CheckBlackJack();
    // Dealer Checks
    dealerHand->CheckBlackJack();
    // Can Split Hand Check
    if (this->GetBloomFilter()->Contains(this->GetFilterMatrix()[2][2]) && this->GetPlayerCards()->GetSize() == 2) {
        // Player has enough money to split
        if (this->GetBankTotal() >= this->GetWager()) {
            // Checking if player has aces
            bool aces = this->GetPlayerCards()->RetrieveNode(0)->data.CheckCardParam(this->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[0]);
            // Player doesn't have Aces, can still split hand
            if (!aces) {
                this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[0][3]);
            }
            // Player has Aces, can split Aces, can't split regular hand
            else {
                this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[0][2]);
            }
        }
    }
    // Insurance Check
    if (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetRank() == Ranks[0] && !this->GetBloomFilter()->Contains(this->GetFilterMatrix()[2][0])) {
        // Player has enough money to buy insurance
        if (this->GetBankTotal() >= 0.5*this->GetWager()) {
            this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[0][0]);
        }
    }
    // Can Double Down Check
    if (!this->GetBloomFilter()->Contains(this->GetFilterMatrix()[2][0]) && !this->GetBloomFilter()->Contains(this->GetFilterMatrix()[1][3])) {
        if (this->GetBankTotal() >= this->GetWager()) {
            this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[0][1]);
        }
    }
    // Soft Seventeen Check
    if (this->GetCardsTotal() == 17) {
        std::shared_ptr<node<Card>> current = this->GetPlayerCards()->GetRoot();
        while (current != nullptr) {
            if (current->data.GetRank() == Ranks[0] && current->data.GetCardValue() == 11) {
                this->GetBloomFilter()->AddToFilter(this->GetFilterMatrix()[3][2]);
                break;
            }
            current = current->nextNode;
        }
    }
    return *this;
}

/*  PlaceWager - Prompts the user to input a wager for their hand
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create a float value "input" and prompt the user for their wager they would like to place
*       * Check to see if the input is valid
*       * If the input is not a float or an integer
*           * Throw an error, return to the beginning of the while loop while clearing inputs
*       * If the input is a float or an integer
*           * Check to see if the value entered is greater than zero
*               * If it is not, throw an error, return to the beginning of the while loop clearing inputs
*               * If it is, check to see if the input is greater than the bank total
*                   * If it is, then throw an error, return to the beginning of the while loop clearing inputs
*                   * If it is not, set the private data member "wager" to "input" with "SetWager"
*   Output:
*       This function returns a Hand object after setting the wager of a players hand
*/
Hand Hand::PlaceWagerPrompt() {
    float input;
    while (true) {
        // Prompt user for the wager that they would like place for their hand
        std::cout << std::endl << "Please enter a wager for this hand. Current bank total: " << this->GetDisplayBankTotal() << ": "; time_sleep(SHORT_TIME_SLEEP);
        std::cin >> input; time_sleep(SHORT_TIME_SLEEP);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        // Check if the input is not a float or integer
        if (checkResult != "f" && checkResult != "i") {
            std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            clear_terminal();
            checkResult.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Check if a the input is a float or an integer
        else if (checkResult == "f" || checkResult == "i") {
            // User has entered a value that is less than zero, return to beginning of while loop
            if (input <= 0) {
                std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". Please re-enter a positive value." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                clear_terminal();
                checkResult.clear();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // User has entered a value that is greater than zero
            else {
                // User has entered a wager that is greater than their bank, return to beginning of while loop
                if (input > this->GetBankTotal()) {
                    std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". You must enter a wager that is less than or equal to your bank total "
                    << this->GetDisplayBankTotal() << ". Please re-enter your submission." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    clear_terminal();
                    checkResult.clear();
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                // User has entered a valid input for a wager, set the private data member "wager" to "input"
                else {
                    this->SetWager(input);
                    this->UpdateBank(0, this->GetWager());
                    std::cout << std::endl << GetDisplayName() << " has wagered: " << this->GetDisplayWager() << " with a current bank total " << this->GetDisplayBankTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    return *this;
                }
            }
        }
    }
}

/*  PlaceWagerSim - Places a wager for a the hand of a simulated game
*   Input:
*       input - Constant float passed by reference to represent the wager for a given hand
*   Algorithm:
*       * Set the wager for the current hand
*       * Update the bank total for the player
*       * Return the hand object
*   Output:
*       This function returns a Hand object after setting the wager of a players hand
*/
Hand Hand::PlaceWagerSim(const float& input) {
    this->SetWager(input);
    this->UpdateBank(0, this->GetWager());
    return *this;
}

/*  ResetHand - Resets some private data members of a player
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Resets bloom filter of player
*       * Resets all float values to 0.00
*       * Resets all integer values to 0
*       * Clears all string values
*       * Clears all list values
*   Output:
*       This function returns a Hand object after resetting select private data members
*/
Hand Hand::ResetHand() {
    // Filter values
    this->GetBloomFilter()->ClearFilter();
    // Float Values
    this->SetInsuranceWager(0.00);
    this->SetNet(0.00);
    this->SetWager(0.00);
    // Integer Values
    this->SetCardsTotal(0);
    this->SetHandsCurrentlyHeld(1);
    // String Values
    this->GetDisplayBankTotal().clear();
    this->GetDisplayCardsTotal().clear();
    this->GetDisplayInsuranceWager().clear();
    this->GetDisplayNet().clear();
    this->GetDisplayWager().clear();
    // List Values
    this->GetPlayerCards()->ClearList();
    this->GetPlayerHands()->ClearList();
    return *this;
}

/*  ShowHand - This function displays the cards that are present in a players hand
*   Input:
*       option - String value that represents a custom hand tracker (e.g. First, Second, etc.)
*       dealerShow - Constant string value that determines if the dealer is to show both hands
*   Algorithm:
*       * Begin by checking to see if the "option" string is empty
*           * If it is, set it to current
*       * Create string objects that represent certain trackers for the output
*       * Check to see if the player is not the dealer
*           * If it is, create some more string objects to represent parameters
*           * Iterate through the cards in the players hand
*           * Add the hand total and display the other hand parameters
*       * If the player is the dealer
*           * If the dealer is hiding a card, output a special message to console
*           * If the dealer is showing both cards, do the same as a non dealer player
*   Output:
*       This function returns a Hand object after displaying what cards they have
*/
Hand Hand::ShowHand(std::string option, const std::string dealerShow) {
    // Test to see if the option value is empty
    if (option.empty()) {
        option = "current";
    }
    // Modify the string values
    std::string optionMod = color_text(34, option);
    std::string handTotalMod = color_text(36, "Hand Total");
    // The player is not the dealer
    if (this->GetName() != "Dealer") {
        // Modify more string values
        std::string handWager = color_text(32, "Hand Wager");
        std::string bankTotal = color_text(33, "Bank Total");
        std::cout << this->GetDisplayName() << "'s " << optionMod << " hand: [";
        // Iterate through the cards in players hand
        for (int i = 0; i < this->GetPlayerCards()->GetSize(); i++) {
            if (i == this->GetPlayerCards()->GetSize() - 1) {
                std::cout << this->GetPlayerCards()->RetrieveNode(i)->data << "] ";
            }
            else {
                std::cout << this->GetPlayerCards()->RetrieveNode(i)->data << " , ";
            }
        }
        // Add hand total and display players hand parameters
        this->AddHandTotal();
        std::cout << handTotalMod << ": " << this->GetDisplayCardsTotal() << " , " << handWager << ": " << this->GetDisplayWager() << " , " << bankTotal << ": " << this->GetDisplayBankTotal() << std::endl; time_sleep(SHORT_TIME_SLEEP);
    }
    // The player is the dealer
    else if (this->GetName() == "Dealer") {
        // Dealer is hiding a card
        if (dealerShow.empty()) {
            std::string backCardMod = color_text(36, std::to_string(this->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()));
            std::cout << this->GetDisplayName() << "'s " << optionMod << " hand : [Hidden, " << this->GetPlayerCards()->RetrieveNode(-1)->data << "] " << handTotalMod << ": " << backCardMod << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
        // Dealer is showing both cards
        else {
            if (dealerShow != "cards") {
                std::cout << this->GetDisplayName() << "'s " << optionMod << " hand: [";
            }
            // Specialized display of cards
            else {
                std::cout << "[";
            }
            // Iterate through the cards in dealers hand
            for (int i = 0; i < this->GetPlayerCards()->GetSize(); i++) {
                if (i == this->GetPlayerCards()->GetSize() - 1) {
                    std::cout << this->GetPlayerCards()->RetrieveNode(i)->data << "] ";
                }
                else {
                    std::cout << this->GetPlayerCards()->RetrieveNode(i)->data << " , ";
                }
            }
            // Add hand total and display players hand parameters
            this->AddHandTotal();
            std::cout << handTotalMod << ": " << this->GetDisplayCardsTotal() << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
    }
    return *this;
}

/*  UpdateBank - Updates the bank of a player
*   Input:
*       choice - Constant integer that is supposed to represent the outcome of a hand
*       wager - Constant float passed by reference that is the wager being used to update the bank
*   Algorithm:
*       * Grab the prior bank value with "prior_bank"
*       * The following codes represent what the choices mean
*           * 0 - Player withdraws money from bank (placing wager)
*           * 1 - Player wins hand
*           * 2 - Player loses hand
*           * 3 - Player pushes hand
*           * 4 - Player wins blackjack
*           * 5 - Player wins insurance
*   Output:
*       This function returns a Hand object after updating the players bank
*/
Hand Hand::UpdateBank(const int choice, const float& wager) {
    float prior_bank = this->GetBankTotal();
    int handsWon = this->GetHandsWon();
    int handsLost = this->GetHandsLost();
    int handsPushed = this->GetHandsPushed();
    int handsBJ = this->GetHandsBlackjack();
    int handsPlayed = this->GetHandsPlayed();
    switch (choice) {
    // 0 - Player withdraws money from bank (places wager)
    case 0:
        this->SetBankTotal(prior_bank - wager);
        return *this;
    // 1 - Player wins hand
    case 1:
        handsWon++;
        handsPlayed++;
        this->SetHandsPlayed(handsPlayed);
        this->SetHandsWon(handsWon);
        this->SetBankTotal(this->GetBankTotal() + (2.0 * wager));
        this->SetNet(this->GetNet() + (this->GetBankTotal() - (prior_bank + wager)));
        return *this;
    // 2 - Player loses hand
    case 2:
        handsLost++;
        handsPlayed++;
        this->SetHandsPlayed(handsPlayed);
        this->SetHandsLost(handsLost);
        this->SetBankTotal(prior_bank);
        this->SetNet(this->GetNet() + (this->GetBankTotal() - (prior_bank + wager)));
        return *this;
    // 3 - Player pushes hand
    case 3:
        handsPushed++;
        handsPlayed++;
        this->SetHandsPlayed(handsPlayed);
        this->SetHandsPushed(handsPushed);
        this->SetBankTotal(this->GetBankTotal() + wager);
        this->SetNet(this->GetNet() + (this->GetBankTotal() - (prior_bank + wager)));
        return *this;
    // 4 - Player wins blackjack
    case 4:
        handsBJ++;
        handsPlayed++;
        this->SetHandsPlayed(handsPlayed);
        this->SetHandsBlackjack(handsBJ);
        this->SetBankTotal(this->GetBankTotal() + wager + (1.5 * wager));
        this->SetNet(this->GetNet() + (this->GetBankTotal() - (prior_bank + wager)));
        return *this;
    // 5 - Player wins insurance
    case 5:
        this->SetBankTotal(this->GetBankTotal() + (3 * wager));
        this->SetNet(this->GetNet() + (this->GetBankTotal() - (prior_bank + wager)));
        return *this;
    default:
        return *this;
        break;
    }
}

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// SetBankTotal - Mutates the private data member "bankTotal" by assigning it to "input"
void Hand::SetBankTotal(const float& input) {
    float rounded_input = round_input(input);
    player->bankTotal = rounded_input;
    this->SetDisplayBankTotal();
}

// SetInsuranceWager - Mutates the private data member "insuranceWager" by assigning it to "input"
void Hand::SetInsuranceWager(const float& input) {
    float rounded_input = round_input(input);
    player->insuranceWager = rounded_input;
    this->SetDisplayInsuranceWager();
}

// SetNet - Mutates the private data member "net" by assigning it to "input"
void Hand::SetNet(const float& input) {
    float rounded_input = round_input(input);
    player->net = rounded_input;
    this->SetDisplayNet();
}

// SetWager - Mutates the private data member "wager" by assigning it to "input"
void Hand::SetWager(const float& input) {
    float rounded_input = round_input(input);
    player->wager = rounded_input;
    this->SetDisplayWager();
}

// SetCardsTotal - Mutates the private data member "cardsTotal" by assigning it to "input"
void Hand::SetCardsTotal(const int& input) {
    player->cardsTotal = input;
    this->SetDisplayCardsTotal();
}

// SetHandsBlackjack - Mutates the private data member "handsBlackjack" by assigning it to "input"
void Hand::SetHandsBlackjack(const int& input) {
    player->handsBlackjack = input;
}

// SethandsCurrentlyHeld - Mutates the private data member "handsCurrentlyHeld" by assigning it to "input"
void Hand::SetHandsCurrentlyHeld(const int& input) {
    player->handsCurrentlyHeld = input;
}

// SetHandsLost - Mutates the private data member "handsLost" by assigning it to "input"
void Hand::SetHandsLost(const int& input) {
    player->handsLost = input;
}

// SetHandsPlayed - Mutates the private data member "handsPlayed" by assigning it to "input"
void Hand::SetHandsPlayed(const int& input) {
    player->handsPlayed = input;
}

// SetHandsPushed - Mutates the private data member "handsPushed" by assigning it to "input"
void Hand::SetHandsPushed(const int& input) {
    player->handsPushed = input;
}

// SetHandsWon - Mutates the private data member "handsWon" by assigning it to "input"
void Hand::SetHandsWon(const int& input) {
    player->handsWon = input;
}

// SetDisplayBankTotal - Mutates the private data member "displayBankTotal" by assigning it to "input"
void Hand::SetDisplayBankTotal() {
    std::string modified_input = color_text(33, round_to_string(GetBankTotal()));
    player->displayBankTotal = modified_input;
}

// SetDisplayCardsTotal - Mutates the private data member "displayCardsTotal" by assigning it to "input"
void Hand::SetDisplayCardsTotal() {
    std::string modified_input = color_text(35, std::to_string(GetCardsTotal()));
    player->displayCardsTotal = modified_input;
}

// SetDisplayInsuranceWager - Mutates the private data member "displayInsuranceWager" by assigning it to "input"
void Hand::SetDisplayInsuranceWager() {
    std::string modified_input = color_text(31, round_to_string(GetInsuranceWager()));
    player->displayInsuranceWager = modified_input;
}

// SetDisplayName - Mutates the private data member "displayName" by assigning it to "input"
void Hand::SetDisplayName() {
    std::string modified_input;
    if (GetName() != "Dealer") {
        modified_input = color_text(34, GetName());
    }
    else {
        modified_input = color_text(31, GetName());
    }
    player->displayName = modified_input;
}

// SetDisplayNet - Mutates the private data member "displayNet" by assigning it to "input"
void Hand::SetDisplayNet() {
    std::string modified_input = color_text(33, round_to_string(GetNet()));
    player->displayNet = modified_input;
}

// SetDisplayWager - Mutates the private data member "displayWager" bt assigning it to "input"
void Hand::SetDisplayWager() {
    std::string modified_input = color_text(31, round_to_string(GetWager()));
    player->displayWager = modified_input;
}

// SetName - Mutates the private data member "name" bt assigning it to "input"
void Hand::SetName(const std::string& input) {
    player->name = input;
    this->SetDisplayName();
}

// SetHandBankTotals - Mutates the private data member "handBankTotals" bt assigning it to "input"
void Hand::SetHandBankTotals(std::shared_ptr<node<float>>& input) {
    player->handBankTotals->AppendNode(input);
}

// SetHandCardTotals - Mutates the private data member "handCardTotals" bt assigning it to "input"
void Hand::SetHandCardTotals(std::shared_ptr<node<int>>& input) {
    player->handCardTotals->AppendNode(input);
}

// SetHandNets - Mutates the private data member "handNets" bt assigning it to "input"
void Hand::SetHandNets(std::shared_ptr<node<float>>& input) {
    player->handNets->AppendNode(input);
}

// SetHandPlayed - Mutates the private data member "handPlayed" bt assigning it to "input"
void Hand::SetHandPlayed(std::shared_ptr<node<int>>& input) {
    player->handPlayed->AppendNode(input);
}

// SetHandWagers - Mutates the private data member "handWagers" bt assigning it to "input"
void Hand::SetHandWagers(std::shared_ptr<node<float>>& input) {
    player->handWagers->AppendNode(input);
}

// SetPlayerCards - Mutates the private data member "playerCards" bt assigning it to "input"
void Hand::SetPlayerCards(std::shared_ptr<node<Card>>& input) {
    player->playerCards->AppendNode(input);
}

// SetPlayerHands - Mutates the private data member "hands" bt assigning it to "input"
void Hand::SetPlayerHands(std::shared_ptr<node<std::shared_ptr<Hand>>>& input) {
    hands->AppendNode(input);
}

// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetBloomFilter - Retrieves the private data member "bloomFilter"
std::shared_ptr<BloomFilter>& Hand::GetBloomFilter() {
    return player->bloomFilter;
}

// GetFilterMatrix - Retrieves the private data member "filterMatrix"
std::vector<std::vector<std::string>>& Hand::GetFilterMatrix() {
    return player->filterMatrix;
}

// GetBankTotal - Retrieves the private data member "bankTotal"
float& Hand::GetBankTotal() {
    return player->bankTotal;
}

// GetInsuranceWager - Retrieves the private data member "insuranceWager"
float& Hand::GetInsuranceWager() {
    return player->insuranceWager;
}

// GetNet - Retrieves the private data member "net"
float& Hand::GetNet() {
    return player->net;
}

// GetWager - Retrieves the private data member "wager"
float& Hand::GetWager() {
    return player->wager;
}

// GetCardsTotal - Retrieves the private data member "cardsTotal"
int& Hand::GetCardsTotal() {
    return player->cardsTotal;
}

// GetHandsBlackjack - Retrieves the private data member "handsBlackjack"
int& Hand::GetHandsBlackjack() {
    return player->handsBlackjack;
}

// GetHandsCurrentlyHeld - Retrieves the private data member "handsCurrentlyHeld"
int& Hand::GetHandsCurrentlyHeld() {
    return player->handsCurrentlyHeld;
}

// GetHandsLost - Retrieves the private data member "handsLost"
int& Hand::GetHandsLost() {
    return player->handsLost;
}

// GetHandsPlayed - Retrieves the private data member "handsPlayed"
int& Hand::GetHandsPlayed() {
    return player->handsPlayed;
}

// GetHandsPushed - Retrieves the private data member "handsPushed"
int& Hand::GetHandsPushed() {
    return player->handsPushed;
}

// GetHandsWon - Retrieves the private data member "handsWon"
int& Hand::GetHandsWon() {
    return player->handsWon;
}

// GetDisplayBankTotal - Retrieves the private data member "displayBankTotal"
std::string& Hand::GetDisplayBankTotal() {
    return player->displayBankTotal;
}

// GetDisplayCardsTotal - Retrieves the private data member "displayCardsTotal"
std::string& Hand::GetDisplayCardsTotal() {
    return player->displayCardsTotal;
}

// GetDisplayInsuranceWager - Retrieves the private data member "displayInsuranceWager"
std::string& Hand::GetDisplayInsuranceWager() {
    return player->displayInsuranceWager;
}

// GetDisplayName - Retrieves the private data member "displayName"
std::string& Hand::GetDisplayName() {
    return player->displayName;
}

// GetDisplayNet - Retrieves the private data member "displayNet"
std::string& Hand::GetDisplayNet() {
    return player->displayNet;
}

// GetDisplayWager - Retrieves the private data member "displayWager"
std::string& Hand::GetDisplayWager() {
    return player->displayWager;
}

// GetName - Retrieves the private data member "name"
std::string& Hand::GetName() {
    return player->name;
}

// GetHandBankTotals - Retrieves the private data member "handBankTotals"
std::shared_ptr<LinkedList<float>>& Hand::GetHandBankTotals() {
    return player->handBankTotals;
}

// GetHandCardTotals - Retrieves the private data member "handCardTotals"
std::shared_ptr<LinkedList<int>>& Hand::GetHandCardTotals() {
    return player->handCardTotals;
}

// GetHandNets - Retrieves the private data member "handNets"
std::shared_ptr<LinkedList<float>>& Hand::GetHandNets() {
    return player->handNets;
}

// GetHandPlayed - Retrieves the private data member "handPlayed"
std::shared_ptr<LinkedList<int>>& Hand::GetHandPlayed() {
    return player->handPlayed;
}

// GetHandWagers - Retrieves the private data member "handWagers"
std::shared_ptr<LinkedList<float>>& Hand::GetHandWagers() {
    return player->handWagers;
}

// GetPlayerCards - Retrieves the private data member "playerCards"
std::shared_ptr<LinkedList<Card>>& Hand::GetPlayerCards() {
    return player->playerCards;
}

// GetPlayerHands - Retrieves the private data member "hands"
std::shared_ptr<LinkedList<std::shared_ptr<Hand>>>& Hand::GetPlayerHands() {
    return hands;
}