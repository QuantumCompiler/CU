// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Core.h"

/*  Logical order of implementation of functions
*   blackjack_strategy
*   deal_hand
*   dealer_showing_ace
*   split_hand
*   same_rank_check
*   player_logic
*   dealer_logic
*   hand_comparison_logic
*   game_logic
*   play_game
*/

/*  blackjack_strategy - Provides a strategy for players on what is the best way to play a given hand in blackjack
*   Input:
*       playerHand - Hand object that is passed by reference that represents the hand of a user
*       dealerHand - Hand object that is passed by reference that represents the hand of a dealer
*       showStrategy - Boolean value that is passed by reference that indicates if hints will be shown to a player
*   Algorithm:
*       * Check the parameters of the hand "playerHand"
*       * Check if the player has a an Ace in their hand and if they have duplicate ranks in their hand
*       * Create template `should' statements that are output to terminal for certain conditions
*       * Process the logical steps for the following three scenarios:
*           * Player has duplicate ranks in their hand, is able to split, and has not spoken on whether they want to split ye
*           * Player is dealt and Ace and currently has two cards
*           * Any other scenario that doesn't match the above two
*   Output:
*       This function does not output any values, in modifies specific boolean values of "playerHand" and outputs a message to terminal
*/
void blackjack_strategy(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, bool showStrategy) { 
    // Remove "paramInHand" if present
    if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[2][1])) {
        playerHand->GetBloomFilter()->RemoveElement(playerHand->GetFilterMatrix()[2][1]);
    }
    // Remove "sameParamInHand" if present
    if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[2][2])) {
        playerHand->GetBloomFilter()->RemoveElement(playerHand->GetFilterMatrix()[2][2]);
    }
    // Check the parameters of "playerHand"
    playerHand->ParametersCheck(dealerHand);
    // Check if "playerHand" has the same rank or if they have an Ace in their hand
    playerHand->CheckParamInHand("R", Ranks[0]);
    playerHand->CheckSameParamInHand("R");
    // Player `should' statements
    std::string should_double_down = "Blackjack strategy suggests that " + playerHand->GetDisplayName() + " should " + color_text(31, "double down") + ".";
    std::string should_double_down_or_hit = "Blackjack strategy suggests that " + playerHand->GetDisplayName() + " should " + color_text(31, "hit") + " or " + color_text(31, "double down") + ".";
    std::string should_double_down_or_stand = "Blackjack strategy suggests that " + playerHand->GetDisplayName() + " should " + color_text(31, "stand") + " or " + color_text(31, "double down") + ".";
    std::string should_hit = "Blackjack strategy suggests that " + playerHand->GetDisplayName() + " should " + color_text(31, "hit") + ".";
    std::string should_split = "Blackjack strategy suggests that " + playerHand->GetDisplayName() + " should " + color_text(31, "split") + ".";
    std::string should_split_or_hit = "Blackjack strategy suggests that " + playerHand->GetDisplayName() + " should " + color_text(31, "hit") + " or " + color_text(31, "split") + ".";
    std::string should_stand = "Blackjack strategy suggests that " + playerHand->GetDisplayName() + " should " + color_text(31, "stand") + ".";
    // Logic for if a player is dealt the same rank and only two cards are in the hand with them having not decided if they want to split or not
    if (((playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][3]) && !playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[3][4])) 
        || (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][2]) && !playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[3][3]))) && playerHand->GetPlayerCards()->GetSize() == 2) {
        // Check value of players cards
        switch (playerHand->GetCardsTotal()) {
            // Player card total is 4 (two, two) or 6 (three, three)
            case 4:
            case 6:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a two or three
                    case 2:
                    case 3:
                        // Player should split or hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                        if (showStrategy) {
                            std::cout << std::endl << should_split_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    // Dealer is showing a 4, 5, 6 or 7
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        // Player should split
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                        if (showStrategy) {
                            std::cout << std::endl << should_split << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 8 (four, four)
            case 8:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 5 or 6
                    case 5:
                    case 6:
                        // Player should split or hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                        if (showStrategy) {
                            std::cout << std::endl << should_split_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 10 (five, five)
            case 10:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a Face or an Ace
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    // Otherwise
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        // Player can double down
                        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][1])) {
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][3]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_double_down_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        // Player cannot double down
                        else {
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 12 (six, six || Ace, Ace) 
            case 12:
                // Player has Aces
                if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[2][1])) {
                    // Checking the value of the card that is face up of the dealer
                    switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                        // Dealer is showing any card
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                        case 1:
                        case 11:
                            // Player should split
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                            if (showStrategy) {
                                std::cout << std::endl << should_split << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                            break;
                        default:
                            break;
                    }
                }
                // Player has sixes
                else {
                    // Checking the value of the card that is face up of the dealer
                    switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                        // Dealer is showing a 7
                        case 7:
                            // Player should split or hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                            if (showStrategy) {
                                std::cout << std::endl << should_split_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                            break;
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                            // Player should split
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                            if (showStrategy) {
                                std::cout << std::endl << should_split << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                            break;
                        case 8:
                        case 9:
                        case 10:
                        case 1:
                        case 11:
                            // Player should hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;
            // Player has a 14
            case 14:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing an 8
                    case 8:
                        // Player should split or hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                        if (showStrategy) {
                            std::cout << std::endl << should_split_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    // Dealer is showing a 2 - 7
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        // Player should split
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                        if (showStrategy) {
                            std::cout << std::endl << should_split << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    // Otherwise
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 16 (eight, eight)
            case 16:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should split
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                        if (showStrategy) {
                            std::cout << std::endl << should_split << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }          
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 18 (nine, nine)
            case 18:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 7, Face, or Ace
                    case 7:
                    case 10:
                    case 1:
                    case 11:
                        // Player should stand
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl << should_stand << std::endl; time_sleep(SHORT_TIME_SLEEP); 
                        }
                        break;
                    // Otherwise
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 8:
                    case 9:
                        // Player should split
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][0]);
                        if (showStrategy) {
                            std::cout << std::endl << should_split << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 20 (face, face)
            case 20:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should stand
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl << should_stand << std::endl; time_sleep(SHORT_TIME_SLEEP); 
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    // Logic for if a player is dealt an Ace and only two cards are in the hand
    else if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[2][1]) && !playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[2][2]) && playerHand->GetPlayerCards()->GetSize() == 2) {
        // Check value of players cards
        switch (playerHand->GetCardsTotal()) {
            // Player card total is 13 or 14 (Ace, 2 || Ace, 3)
            case 13:
            case 14:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing 5 or 6
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][3]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_double_down_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        break;
                    // Dealer is showing 2 - 4 or 7 - Face or Ace
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 15 or 16 (Ace, 4 || Ace, 5)
            case 15:
            case 16:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 4, 5, or 6
                    case 4:
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][3]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_double_down_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }              
                        break;
                    // Otherwise
                    case 2:
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 17 (Ace, 6)
            case 17:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 3, 4, 5, or 6
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][3]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_double_down_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        break;
                    // Otherwise
                    case 2:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 18 (Ace, 7)
            case 18:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 2, 7, or 8
                    case 2:
                    case 7:
                    case 8:
                        // Player should stand
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl << should_stand << std::endl; time_sleep(SHORT_TIME_SLEEP); 
                        }
                        break;
                    // Dealer is showing a 3, 4, 5, or 6
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][1])) {
                            // Player should double down or stand
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][3]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl << should_double_down_or_stand << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        else {
                            // Player should stand
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl << should_stand << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        break;
                    // Dealer is showing 9, Face, or Ace
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 19, 20, or 21 (Ace, 8 || Ace, 9 || Ace, Ten)
            case 19:
            case 20:
            case 21:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should stand
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl << should_stand << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        } 
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    // Logic for all other scenarios
    else {
        // Check value of players cards
        switch (playerHand->GetCardsTotal()) {
            // Player card total is 4-8
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 9
            case 9:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing 2-6
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][3]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_double_down_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        break;
                    // Dealer is showing 7-Face or Ace
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 10
            case 10:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing 2-9
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        // Player can double down
                        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][3]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_double_down_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        break;
                    // Dealer is showing a face card or Ace
                    case 10:
                    case 11:
                    case 1:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 11
            case 11:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                        // Player can double down
                        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][3]);
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_double_down_or_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                            if (showStrategy) {
                                std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            }
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 12
            case 12:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 2,3 or 7-Face or Ace
                    case 2:
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    // Dealer is showing a 4-6
                    case 4:
                    case 5:
                    case 6:
                        // Player should stand
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl << should_stand << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 13 through 16
            case 13:
            case 14:
            case 15:
            case 16:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing 2-6
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        // Player should stand
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl << should_stand << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    // Dealer is showing 7-Face or Ace
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[2][4]);
                        if (showStrategy) {
                            std::cout << std::endl << should_hit << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 17 through 21
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
                // Checking the value of the card that is face up of the dealer
                switch (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should stand
                        playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl << should_stand << std::endl; time_sleep(SHORT_TIME_SLEEP); 
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

/*  csv_generator - Generates a CSV file for the game of a player
*   Input:
*       input - Hand object passed by reference that represents the hand that is going to have a csv made of it
*   Algorithm:
*       * Create a file name for the CSV file
*       * Generate a file with the contents of the players hand
*       * Close the file
*   Output:
*       fileName - After creating the csv file, this function returns the name of the file that has been created
*/
std::string csv_generator(std::shared_ptr<Hand>& input) {
    // Create string for filename of csv
    std::string fileName = input->GetName() + " Results.csv";
    // Generate file object
    std::ofstream file(fileName);
    // File has successfully opened
    if (file) {
        // Set headers of csv file
        file << "Hand Number, Hand Wager, Hand Net, Hand Total, Bank Total" << std::endl;
        // Get roots of linked lists for statistics
        std::shared_ptr<node<float>> handBankNode = input->GetHandBankTotals()->GetRoot();
        std::shared_ptr<node<int>> handTotalNode = input->GetHandCardTotals()->GetRoot();
        std::shared_ptr<node<float>> handNetNode = input->GetHandNets()->GetRoot();
        std::shared_ptr<node<int>> handNumNode = input->GetHandPlayed()->GetRoot();
        std::shared_ptr<node<float>> handWagNode = input->GetHandWagers()->GetRoot();
        // Add data to file while the lists are not empty
        while (handNumNode != nullptr && handWagNode != nullptr && handNetNode != nullptr && handTotalNode != nullptr && handBankNode != nullptr) {
            // Generate data in rows of file
            file << handNumNode->data << "," << handWagNode->data << "," << handNetNode->data << "," << handTotalNode->data << "," << handBankNode->data << std::endl;
            handBankNode = handBankNode->nextNode;
            handTotalNode = handTotalNode->nextNode;
            handNetNode = handNetNode->nextNode;
            handNumNode = handNumNode->nextNode;
            handWagNode = handWagNode->nextNode;
        }
        // Close file
        file.close();
        // Output message that file has been successfully created
        progress_bar(LONG_TIME_SLEEP, "Creating CSV ", fileName + " has been successfully created.");
        time_sleep(MEDIUM_TIME_SLEEP); clear_terminal();
    }
    // File failed to open
    else {
        std::cout << "Error creating CSV File: " << fileName << std::endl;
    }
    return fileName;
}

/*  deal_hand - Deals cards to players and shows the hands of each player after the deal
*   Input:
*       playerHand - Hand object passed by reference that represents the users hand
*       dealerHand - Hand object passed by reference that represents the dealers hand
*       inputShoe - Shoe object passed by reference that represents the show of of the game
*   Algorithm:
*       * Request the player place a wager for the hand
*       * Deal cards to a player and dealer
*       * Show the hands of the player and the dealer off of deal
*       * Return the Hand objects and the Shoe object
*   Output:
*       playerHand - Hand object that is modified after having cards added to it
*       dealerHand - Hand object that is modified after having cards added to it
*       inputShoe - Shoe object that is changed after having cards dealt from it
*/
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> deal_hand(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& inputShoe) {
    // Have player place wager
    if (playerHand->GetWager() == 0) {
        playerHand->PlaceWagerPrompt();
    }
    // Deal cards to players
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            playerHand->HitHand(inputShoe);
        }
        else if (i % 2 == 1) {
            dealerHand->HitHand(inputShoe);
        }
    }
    // Show hands of player
    std::cout << std::endl << "Here are the initial hands of each player: " << std::endl << std::endl; time_sleep(SHORT_TIME_SLEEP);
    playerHand->ShowHand("initial");
    dealerHand->ShowHand("initial", "");
    playerHand->ParametersCheck(dealerHand);
    dealerHand->CheckBlackJack();
    return std::make_tuple(playerHand, dealerHand, inputShoe);
}

/*  dealer_logic - Processes the logic for how the dealer should play their current hands
*   Input:
*       playerHands - Vector of Hand objects that are passed by reference that represent all of the hands of a player
*       dealerHand - Hand object passed by reference that represents the dealers hand
*       Shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
*   Algorithm:
*       * Check the parameters of the dealers hand
*       * Check if all of the hands of the player are over 21
*       * If all the hands of the player are not over 21
*           * Check if the dealer needs to play (i.e. The have 17 or less or they have a soft 17)
*               * If they don't need to play, show the hands of the player and the dealer
*               * If they do need to play, proceed to have the dealer play until they reach a count of 17 or greater (dealer hits on all soft 17)
*           * Show the hands of the player and the dealer after they have finished playing their hand
*       * If all the hands of the player are over 21
*           * Show the hands of the player and the dealer
*       * Return the dealers hand and the game shoe
*   Output:
*       dealerHand - Hand object that represents the modified hand of the dealer after being played with
*       shoe - Shoe object that represents the modified shoe in the game
*/
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Shoe>> dealer_logic(std::vector<std::shared_ptr<Hand>>& playerHands, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe) {
    // Check the parameters of the dealers hand
    dealerHand->ParametersCheck(dealerHand);
    // Check if all hands of the player are over 21
    bool all_over_21 = true;
    for (std::shared_ptr<Hand>& current_hand : playerHands) {
        if (current_hand->GetCardsTotal() <= 21) {
            all_over_21 = false;
            break;
        }
        else {
            all_over_21 = true;
            continue;
        }
    }
    // Not all hands of player are over 21
    if (!all_over_21) {
        // Check if the dealer has an Ace in their hand
        dealerHand->CheckParamInHand("R", Ranks[0]);
        // Dealer has a hand total of seventeen or greater with no Ace in hand
        if (dealerHand->GetCardsTotal() >= 17 && !dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[2][1])) {
            std::cout << std::endl << "The " << dealerHand->GetDisplayName() << " does not need to play their hand with a final total of " << dealerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
        // Dealer has less than 17 or has a soft 17
        else if (dealerHand->GetCardsTotal() < 17 || dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[3][2])) {
            std::cout << std::endl << "The " << dealerHand->GetDisplayName() << " will now play their hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            // Dealer must continue to play and will hit on soft seventeen
            while ((dealerHand->GetCardsTotal() < 17 || dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[3][2]))) {
                // Dealer still has less than seventeen or possesses a soft seventeen
                if (dealerHand->GetCardsTotal() < 17 || dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[3][2])) {
                    dealerHand->HitHand(shoe);
                    std::cout << dealerHand->GetDisplayName() << " hits hand: ";
                    dealerHand->ShowHand("", "cards");
                    dealerHand->ParametersCheck(dealerHand);
                    continue;
                }
                // Dealer has 17 or higher and does not have a soft seventeen
                else if (dealerHand->GetCardsTotal() >= 17 && !dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[3][2])) {
                    break;
                }
            }
        }
        // Show the final hand of the dealer after playing
        std::cout << std::endl << "The " << dealerHand->GetDisplayName() << "'s final hand is:"; time_sleep(SHORT_TIME_SLEEP);
        std::cout << std::endl << dealerHand->GetDisplayName() << " final hand "; dealerHand->ShowHand("", "cards");
    }
    // All hands of player are over 21
    else {
        if (playerHands.size() > 1) {
            std::cout << std::endl << playerHands.at(0)->GetDisplayName() << " has busted on all of their hands. " << dealerHand->GetDisplayName() << " does not need to play their hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
        else {
            std::cout << std::endl << playerHands.at(0)->GetDisplayName() << " has busted on their hand. " << dealerHand->GetDisplayName() << " does not need to play their hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
    }
    // Return the dealer hand and the modified shoe
    return std::make_tuple(dealerHand, shoe);
}

/*  dealer_showing_ace - Checks to see if the dealer is showing an Ace and if a player has blackjack or not
*   Input:
*       playerHand - Hand object passed by reference that represents the user's hand
*       dealerHand - Hand object passed by reference that represents the dealer's hand
*       inputShoe - Shoe object passed by reference that represents the shoe that is being played with
*   Algorithm:
*       * Deal hands to the players with the "deal_hand" function
*       * Create a boolean value "hand_continue" that keeps track if a hand is to be continued
*       * Proceed to check if the player is able to buy insurance (This is done with the "ParametersCheck" function in "deal_hand")
*       * For each instance, we check if the following is true:
*           * If both players have blackjack, if this is true, payout insurance bets if placed, otherwise just push bets
*           * If dealer has blackjack and player does not, payout insurance bets if placed, otherwise just take bets
*           * If dealer does not have blackjack and player does, take insurance bet, and payout blackjack to player
*           * If neither player has blackjack, take insurance bet if placed, continue hand
*       * In each instance above, we output messages that pertain to each instance and update the player bank accordingly
*       * The "hand_continue" boolean value is updated for each case, depending on what the scenario is
*       * Return values at the end of the if else statements
*   Output:
*       playerHand - Modified Hand object after checking for below cases that represents the players hand
*       dealerHand - Hand object that represents the dealers hand after checking cases
*       inputShoe - Shoe object that represents the game shoe that is being played with
*/
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>, bool> dealer_showing_ace(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& inputShoe) {
    // Deal hands to player
    deal_hand(playerHand, dealerHand, inputShoe);
    // Define "hand_continue" boolean value to true
    bool hand_continue = true;
    // Player can buy insurance
    if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][0])) {
        // Tell user that the dealer is showing an Ace and ask them if they would like to buy insurance
        std::cout << std::endl << "The " << dealerHand->GetDisplayName() << " is showing an " << dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetDisplayRank() << ". " << std::endl; time_sleep(SHORT_TIME_SLEEP);
        playerHand->InsurancePrompt();
        // Output a message telling the user they bought insurance
        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][4])) {
            std::cout << std::endl << playerHand->GetDisplayName() << " has chosen to buy insurance. Your insurance wager is " << playerHand->GetDisplayInsuranceWager() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
        // Output a message telling the user they refused to buy insurance
        else {
            std::cout << std::endl << playerHand->GetDisplayName() << " has chosen to not buy insurance." << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
        // Both players have blackjack, hand ends
        if (dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[1][4]) && playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[1][4])) {
            if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][4])) {
                std::cout << std::endl << "Both players have blackjack. " << playerHand->GetDisplayName() << " wins insurance and pushes their original wager. " << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->UpdateBank(3, playerHand->GetWager());
                playerHand->UpdateBank(5, playerHand->GetInsuranceWager());
            }
            else {
                std::cout << std::endl << "Both players have blackjack. " << playerHand->GetDisplayName() << " pushes their original wager." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->UpdateBank(3, playerHand->GetWager());
            }
            std::cout << std::endl << "Here are the final hands of the players:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->ShowHand("final");
            dealerHand->ShowHand("final", "show");
            std::cout << std::endl << playerHand->GetDisplayName() << " pushes the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            hand_continue = false;
            stats_tracker(playerHand);
        }
        // Dealer has blackjack, player does not, hand ends
        else if (dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[1][4]) && !playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[1][4])) {
            if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][4])) {
                std::cout << std::endl << dealerHand->GetDisplayName() << " has blackjack but " << playerHand->GetDisplayName() << " does not. " << playerHand->GetDisplayName()
                << " wins insurance but loses their original wager. "; time_sleep(SHORT_TIME_SLEEP);
                playerHand->UpdateBank(2, playerHand->GetWager());
                playerHand->UpdateBank(5, playerHand->GetInsuranceWager());
            }
            else {
                std::cout << std::endl << dealerHand->GetDisplayName() << " has blackjack but " << playerHand->GetDisplayName() << " does not. " << playerHand->GetDisplayName()
                << " loses their original wager. "; time_sleep(SHORT_TIME_SLEEP);
                playerHand->UpdateBank(2, playerHand->GetWager());
            }
            std::cout << "Here are the final hands of the players:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->ShowHand("final");
            dealerHand->ShowHand("final", "show");
            std::cout << std::endl << playerHand->GetDisplayName() << " loses the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            hand_continue = false;
            stats_tracker(playerHand);
        }
        // Dealer does not have blackjack, player does, hand ends
        else if (!dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[1][4]) && playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[1][4])) {
            if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][4])) {
                std::cout << std::endl << playerHand->GetDisplayName() << " has blackjack and " << dealerHand->GetDisplayName() << " does not. " << playerHand->GetDisplayName()
                << " loses insurance but wins their original wager. "; time_sleep(SHORT_TIME_SLEEP);
                playerHand->UpdateBank(4, playerHand->GetWager());
                playerHand->UpdateBank(2, playerHand->GetInsuranceWager());
            }
            else {
                std::cout << std::endl << playerHand->GetDisplayName() << " has blackjack and " << dealerHand->GetDisplayName() << " does not. " << playerHand->GetDisplayName()
                << " wins their original wager. "; time_sleep(SHORT_TIME_SLEEP);
                playerHand->UpdateBank(4, playerHand->GetWager());
            }
            std::cout << "Here are the final hands of the players:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->ShowHand("final");
            dealerHand->ShowHand("final", "show");
            std::cout << std::endl << playerHand->GetDisplayName() << " wins the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            hand_continue = false;
            stats_tracker(playerHand);
        }
        // Neither player has blackjack, hand continues
        else {
            if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][4])) {
                std::cout << std::endl << "Neither player has blackjack. " << playerHand->GetDisplayName() << " loses their insurance wager. The hand will continue." << std::endl << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->UpdateBank(2, playerHand->GetInsuranceWager());
            }
            else {
                std::cout << std::endl << "Neither player has blackjack. The hand will continue." << std::endl; time_sleep(SHORT_TIME_SLEEP); 
            }
            hand_continue = true;
        }
    }
    // Player is not able to buy insurance
    else {
        // Dealer is showing an Ace but the player does not have enough currency to buy insurance
        if (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.CheckCardParam(dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetRank(), Ranks[0])) {
            if (playerHand->GetBankTotal() < 0.5*playerHand->GetWager()) {
                std::cout << std::endl << "The " << dealerHand->GetDisplayName() << " is showing an " << dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetDisplayRank() << " but " << playerHand->GetDisplayName()
                << " does not have enough currency in their bank to purchase insurance." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
        }
        // Both players have blackjack, hand ends
        if (dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[1][4]) && playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[1][4])) {
            std::cout << std::endl << "Both players have blackjack. " << playerHand->GetDisplayName() << " pushes their original wager." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->UpdateBank(3, playerHand->GetWager());
            std::cout << std::endl << "Here are the final hands of the players:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->ShowHand("final");
            dealerHand->ShowHand("final", "show");
            std::cout << std::endl << playerHand->GetDisplayName() << " pushes the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            hand_continue = false;
            stats_tracker(playerHand);
        }
        // Dealer has blackjack, player does not, hand ends
        else if (dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[1][4]) && !playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[1][4])) {
            std::cout << std::endl << dealerHand->GetDisplayName() << " has blackjack but " << playerHand->GetDisplayName() << " does not. " << playerHand->GetDisplayName()
            << " loses their original wager." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->UpdateBank(2, playerHand->GetWager());
            std::cout << std::endl << "Here are the final hands of the players:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->ShowHand("final");
            dealerHand->ShowHand("final", "show");
            std::cout << std::endl << playerHand->GetDisplayName() << " loses the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            hand_continue = false;
            stats_tracker(playerHand);
        }
        // Dealer does not have blackjack, player does, hand ends
        else if (!dealerHand->GetBloomFilter()->Contains(dealerHand->GetFilterMatrix()[1][4]) && playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[1][4])) {
            std::cout << std::endl << playerHand->GetDisplayName() << " has blackjack and " << dealerHand->GetDisplayName() << " does not. " << playerHand->GetDisplayName()
            << " wins their original wager." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->UpdateBank(4, playerHand->GetWager());
            std::cout << std::endl << "Here are the final hands of the players:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->ShowHand("final");
            dealerHand->ShowHand("final", "show");
            std::cout << std::endl << playerHand->GetDisplayName() << " wins the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            hand_continue = false;
            stats_tracker(playerHand);
        }
        // Neither player has blackjack, hand continues
        else {
            hand_continue = true;
        }
    }
    return std::make_tuple(playerHand, dealerHand, inputShoe, hand_continue);
}

/*  game_logic - Processes the logic required for a single hand of blackjack amongst players and dealer
*   Input:
*       playerHand - Hand object that is passed by reference that represents the users hand that is being played with
*       dealerHand - Hand object that is passed by reference that represents the dealers hand that is being played with
*       shoe - Shoe object that is passed by reference that represents the game shoe that is being played with
*   Algorithm:
*       * Process the dealer_showing_ace function and return its values
*       * Determine if the hand must continue after dealer_showing_ace
*           * If it continues, process the following functions: same_rank_check, player_logic, dealer_logic, hand_comparison_logic
*           * If it does not continue, proceed to return the objects that have been modified
*       * Return the playerHand, dealerHand, and shoe objects
*   Output:
*       playerHand - Hand object that represents the modified hand object that represents the player after a hand has been played
*       dealerHand - Hand object that represents the modified hand object that represents the dealer after a hand has been played
*       shoe - Shoe object that represents the game shoe that represents the shoe after a hand has been played
*/
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> game_logic(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe) {
    // Process the dealer_showing_ace function
    auto dealerAce = dealer_showing_ace(playerHand, dealerHand, shoe);
    // If neither player has blackjack, continue
    if (std::get<3>(dealerAce)) {
        // Process the same_rank_check function
        auto sameRank = same_rank_check(std::get<0>(dealerAce), std::get<1>(dealerAce), std::get<2>(dealerAce));
        int hand_counter = 0;
        std::vector<std::shared_ptr<Hand>> playerHandsPL;
        // Iterate over all hands of the user and process the player_logic function
        for (std::shared_ptr<Hand>& current_hand : std::get<0>(sameRank)) {
            hand_counter++;
            auto playerHandLogic = player_logic(current_hand, std::get<2>(sameRank), std::get<1>(sameRank), std::get<3>(sameRank), hand_counter);
            playerHandsPL.insert(playerHandsPL.begin(), std::get<0>(playerHandLogic));
            playerHand = std::get<0>(playerHandLogic);
            dealerHand = std::get<1>(playerHandLogic);
            shoe = std::get<2>(playerHandLogic);
        }
        std::reverse(playerHandsPL.begin(), playerHandsPL.end());
        // Process the dealer_logic function
        auto dealerHandLogic = dealer_logic(playerHandsPL, dealerHand, shoe);
        dealerHand = std::get<0>(dealerHandLogic);
        shoe = std::get<1>(dealerHandLogic);
        int current_hand_counter = 1;
        int totalHands = playerHandsPL.size();
        std::vector<std::shared_ptr<Hand>> playerHandsHCL;
        // Iterate over all hands of the user and process the hand_comparison_logic function
        for (std::shared_ptr<Hand>& current_hand : playerHandsPL) {
            current_hand->CopyVariables(playerHand);
            auto handComparisonLogic = hand_comparison_logic(current_hand, dealerHand, totalHands, current_hand_counter);
            playerHand = std::get<0>(handComparisonLogic);
            dealerHand = std::get<1>(handComparisonLogic);
            playerHandsHCL.insert(playerHandsHCL.begin(), std::get<0>(handComparisonLogic));
            current_hand_counter++;
        }
        // Reset all individual hands 
        for (std::shared_ptr<Hand>& current_hand : playerHandsHCL) {
            current_hand->ResetHand();
        }
    }
    // If a player has blackjack return the player and dealer hand along with the game shoe
    playerHand->ResetHand();
    dealerHand->ResetHand();
    // Return the player and dealer hand and the game shoe
    return std::make_tuple(playerHand, dealerHand, shoe);
}

/*  hand_comparison_logic - Compares the hand of a player to that of the dealer and determines if they push, win, or lose
*   Input:
*       playerHand - Hand object that is passed by reference that represents the current hand that is being examined
*       dealerHand - Hand object that is passed by reference that represents the dealers hand that is being examined against for the players hand
*       playerHandCount - Integer value that is passed by reference that represents the number of hands that player has
*       currentHandCounter - Integer value that represents the current hand of the total hands of a player that is being examined
*   Algorithm:
*       * Create a "hand_tracker" string value that keeps track of the current hand that is being examined
*       * Check to first see if players current hand is less than or equal to 21
*           * If it is less than or equal to 21, check to see if the players hand is equal to that of the dealers
*               * If it is, then update the players bank so that it is a push for the player
*               * Show the final hand of the player (or current hand if multiple) and output a message showing the result of the hand
*           * Check to see if the dealers hand is greater than the players and less than or equal to 21
*               * If it is, then update the players bank so that it is a loss for the player
*               * Show the final hand of the player (or current hand if multiple) and output a message showing the result of the hand
*           * Check to see if the players hand is greater than that of the dealers
*               * If it is, then update the players bank so that it is a win for the player
*               * Show the final hand of the player (or current hand if multiple) and output a message showing the result of the hand
*       * Check to see if the players current hand is greater than 21
*           * If it is, then update the players bank so that it is a loss for the player
*           * Show the final hand of the player (or current hand if multiple) and output a message showing the result of the hand
*       * Update the stat tracking for the current hand of the player
*       * Return the player hand and dealer hand
*   Output:
*       playerHand - Hand object that represents the updated player hand after the function is done executing
*       dealerHand - Hand object that represents the dealers hand after the function is done executing
*/
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>> hand_comparison_logic(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, int& playerHandCount, int& currentHandCounter) {
    // Keep track of the number of hands of a player
    std::string hand_tracker;
    bool multiple_hands = false;
    if (playerHandCount > 1) {
        multiple_hands = true;
        if (currentHandCounter == 1) {
            hand_tracker = "first";
        }
        else if (currentHandCounter == 2) {
            hand_tracker = "second";
        }
        else if (currentHandCounter == 3) {
            hand_tracker = "third";
        }
        else if (currentHandCounter == 4) {
            hand_tracker = "fourth";
        }
        else if (currentHandCounter == 5) {
            hand_tracker = "fifth";
        }
        else {
            hand_tracker.clear();
        }
    }
    // Player has a hand total of less than or equal to 21
    if (playerHand->GetCardsTotal() <= 21) {
        // Player and dealer have the same hand total
        if (playerHand->GetCardsTotal() == dealerHand->GetCardsTotal()) {
            // Player pushes their current hand
            playerHand->UpdateBank(3, playerHand->GetWager());
            // Player has a singular hand, show their hand
            if (!multiple_hands) { 
                std::cout << std::endl << "Both players have the same final value of " << playerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "The final hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->ShowHand("final");
            }
            // Player has multiple hands, show the current hand
            else {
                std::cout << std::endl << "Both players have the same final value of " << playerHand->GetDisplayCardsTotal() << " for hand " << std::to_string(currentHandCounter) << ". " << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->ShowHand("final " + hand_tracker);
            }
            // Show the dealers final hand
            dealerHand->ShowHand("final", "show");
            // Tell the user the result of their singular hand
            if (!multiple_hands) {
                std::cout << std::endl << "This hand is a push. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
            // Tell the user the result of their current hand
            else {
                std::cout << std::endl << "Hand " << std::to_string(currentHandCounter) << " is a push. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet()
                << " for hand " << std::to_string(currentHandCounter) << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
        }
        // Dealer wins
        else if (dealerHand->GetCardsTotal() > playerHand->GetCardsTotal() && dealerHand->GetCardsTotal() <= 21) {
            // Player loses their current hand
            playerHand->UpdateBank(2, playerHand->GetWager());
            // Player has a singular hand, show their hand
            if (!multiple_hands) {
                std::cout << std::endl << dealerHand->GetDisplayName() << " has a greater final value of " << dealerHand->GetDisplayCardsTotal() << " compared to " << playerHand->GetDisplayName() << "'s final value of " 
                << playerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "The final hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->ShowHand("final");
            }
            // Player has multiple hands, show their current hand
            else {
                std::cout << std::endl << dealerHand->GetDisplayName() << " has a greater final value of " << dealerHand->GetDisplayCardsTotal() << " for hand " << std::to_string(currentHandCounter) << " compared to " 
                << playerHand->GetDisplayName() << "'s final value of " << playerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->ShowHand("final " + hand_tracker);
            }
            // Show the dealers hand
            dealerHand->ShowHand("final", "show");
            // Tell the user the result of their singular hand
            if (!multiple_hands) {
                std::cout << std::endl << playerHand->GetDisplayName() << " loses the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
            // Tell the user the result of their current hand
            else {
                std::cout << std::endl << playerHand->GetDisplayName() << " loses hand " << std::to_string(currentHandCounter) << ". " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet()
                << " for hand " << std::to_string(currentHandCounter) << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
        }
        // Player wins
        else if (dealerHand->GetCardsTotal() < playerHand->GetCardsTotal()) {
            // Player wins their current hand
            playerHand->UpdateBank(1, playerHand->GetWager());
            // Player has a singular hand, show their hand
            if (!multiple_hands) {
                std::cout << std::endl << playerHand->GetDisplayName() << " has a greater final value of " << playerHand->GetDisplayCardsTotal() << " compared to " << dealerHand->GetDisplayName() << "'s final value of " 
                << dealerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "The final hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->ShowHand("final");
            }
            // Player has multiple hands, show their current hand
            else {
                std::cout << std::endl << playerHand->GetDisplayName() << " has a greater final value of " << playerHand->GetDisplayCardsTotal() << " for hand " << std::to_string(currentHandCounter) << " compared to " 
                << dealerHand->GetDisplayName() << "'s final value of " << dealerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->ShowHand("final " + hand_tracker);
            }
            // Show the dealers hand
            dealerHand->ShowHand("final", "show");
            // Tell the user the result of their singular hand
            if (!multiple_hands) {
                std::cout << std::endl << playerHand->GetDisplayName() << " wins the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
            // Tell the user the result of their current hand
            else {
                std::cout << std::endl << playerHand->GetDisplayName() << " wins hand " << std::to_string(currentHandCounter) << ". " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet()
                << " for hand " << std::to_string(currentHandCounter) << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
        }
        // Dealer has busted on their current hand
        else if (dealerHand->GetCardsTotal() > 21) {
            // Player wins their current hand
            playerHand->UpdateBank(1, playerHand->GetWager());
            // Player has a singular hand, show their hand
            if (!multiple_hands) {
                std::cout << std::endl << dealerHand->GetDisplayName() << " has busted with a final value of " << dealerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "The final hands of each player for the current hand are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->ShowHand("final");
            }
            // Player has multiple hands, show their current hand
            else {
                std::cout << std::endl << dealerHand->GetDisplayName() << " has busted with a final value of " << dealerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                playerHand->ShowHand("final " + hand_tracker);
            }
            // Show the dealers hand
            dealerHand->ShowHand("final", "show");
            // Tell the user the result of their singular hand
            if (!multiple_hands) {
                std::cout << std::endl << playerHand->GetDisplayName() << " wins the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
            // Tell the user the result of their current hand
            else {
                std::cout << std::endl << playerHand->GetDisplayName() << " wins hand " << std::to_string(currentHandCounter) << ". " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet()
                << " for hand " << std::to_string(currentHandCounter) << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
        }
    }
    // Player has busted on their current hand
    else if (playerHand->GetCardsTotal() > 21) {
        // Player loses on their current hand
        playerHand->UpdateBank(2, playerHand->GetWager());
        // Player has a singular hand, show their hand
        if (!multiple_hands) {
            std::cout << std::endl << "The final hands of each player for the current hand are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->ShowHand("final");
        }
        // Player has multiple hands, show their current hand
        else {
            std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            playerHand->ShowHand("final" + hand_tracker);
        }
        // Show the dealers hand
        dealerHand->ShowHand("final", "show");
        // Tell the user the result of their singular hand
        if (!multiple_hands) {
            std::cout << std::endl << playerHand->GetDisplayName() << " loses the current hand. " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet() << " this hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
        // Tell the user the result of their current hand
        else {
            std::cout << std::endl << playerHand->GetDisplayName() << " loses hand " << std::to_string(currentHandCounter) << ". " << playerHand->GetDisplayName() << " nets " << playerHand->GetDisplayNet()
            << " for hand " << std::to_string(currentHandCounter) << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
    }
    // Update the stats of the current hand for the player
    stats_tracker(playerHand);
    // Return the player hand, dealer hand, and the shoe
    return std::make_tuple(playerHand, dealerHand);
}

/*  play_game - Processes all the logic that is required for a game of blackjack to be played
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create hand objects for the players
*       * Set the names of the players in the game
*       * Deposit currency into the players bank
*       * Create a shoe object for the game
*       * Set the minimum cards that need to be left in the shoe to continue playing
*       * Proceed to play a new hand while the cards left in the shoe is greater than "min_card_count" and the player has a positive bank total left
*       * Process the "game_logic" function
*       * Prompt the player if they would like to continue playing if their bank total is greater than zero
*           * If they choose to continue playing, check to see if the number of cards is greater than "min_card_count"
*               * If it is, continue on to the next hand
*               * If it isn't, shuffle a new shoe
*           * If they choose to stop playing, break the while loop and end the game
*       * If the players bank total is zero, prompt the player if they would like re-deposit currency into their bank
*           * If they choose to re-deposit, check to see if the number of cards is greater than "min_card_count"
*               * If it is, continue on to the next hand
*               * If it isn't, shuffle a new shoe
*           * If they choose to not re-deposit, break the while loop and end the game
*       * After the player has chosen to stop playing, create a csv of the stats for the player
*   Output:
*       This function does not return a value
*/
void play_game() {
    clear_terminal();
    progress_bar(LONG_TIME_SLEEP, "Loading Game", "Ready To Play :)");
    clear_terminal();
    // Create Hand objects
    std::shared_ptr<Hand> humanHand(new Hand);
    std::shared_ptr<Hand> dealerHand(new Hand);
    // Set the names of the players
    dealerHand->SetName("Dealer");
    humanHand->NamePrompt();
    // Deposit currency for users
    humanHand->BankDepositPrompt();
    // Create Shoe object
    std::shared_ptr<Shoe> gameShoe(new Shoe);
    gameShoe->CreateShoePrompt();
    // Card count minimum
    int min_card_count = 13;
    // Play game while the cards in the shoe is greater than 13 and the users bank total is greater than 0
    while (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count && humanHand->GetBankTotal() > 0) {
        // Process the game_logic function
        auto gameLogic = game_logic(humanHand, dealerHand, gameShoe);
        humanHand->CopyVariables(std::get<0>(gameLogic));
        dealerHand->CopyVariables(std::get<1>(gameLogic));
        gameShoe = std::get<2>(gameLogic);
        bool continue_playing = false;
        // Continue playing if the player has a bank total of greater than zero
        if (humanHand->GetBankTotal() > 0) {
            std::string cont_play;
            // Prompt the player if they want to continue playing, force them to enter either y or n
            while (true) {
                std::cout << std::endl << "Would you like to continue playing? (y/n): "; time_sleep(SHORT_TIME_SLEEP);
                std::cin >> cont_play; time_sleep(SHORT_TIME_SLEEP);
                // Player has chosen to continue playing
                if (cont_play == "y") {
                    // Ample enough cards left in shoe to continue playing
                    if (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count) {
                        std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Dealing new hands.");
                        clear_terminal();
                        break;
                    }
                    // Shoe must be reshuffled
                    else {
                        std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Shuffling a new shoe.");
                        gameShoe->EmptyShoe();
                        gameShoe->SetNumOfDecks(gameShoe->GetNumOfDecks());
                        gameShoe->CreateShoePrompt();
                        clear_terminal();
                        break;
                    }
                }
                // Player has chosen to stop playing
                else if (cont_play == "n") {
                    std::cout << std::endl << humanHand->GetDisplayName() << " has chosen to quit playing. Final bank total: " << humanHand->GetDisplayBankTotal() << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    std::cout << std::endl << "Thank you for playing " << humanHand->GetDisplayName() << "!" << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                    clear_terminal();
                    break;
                }
                // Player has entered an incorrect response to the prompt
                else {
                    clear_terminal();
                    cont_play.clear();
                    continue;
                }
            }
            // Set "continue_playing" to true if the player has chosen to continue playing
            if (cont_play == "y") {
                continue_playing = true;
            }
            // Set "continue_playing" to false if the player has chosen to stop playing
            else {
                cont_play = false;
            }
        }
        // Player has run out of currency in their bank
        else {
            std::string redeposit;
            std::cout << std::endl << humanHand->GetDisplayName() << " has run out of currency in their bank." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            // Prompt the player if they want to re-deposit currency into their bank, require them to enter y or n
            while (true) {
                std::cout << std::endl << "Would you like to deposit more currency into your bank? (y/n): "; time_sleep(SHORT_TIME_SLEEP);
                std::cin >> redeposit; time_sleep(SHORT_TIME_SLEEP);
                // Player has chosen to re-deposit currency into their bank
                if (redeposit == "y") {
                    humanHand->BankDepositPrompt(); time_sleep(MEDIUM_TIME_SLEEP);
                    // Proceed with same shoe if greater than minimum card count
                    if (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count) {
                        std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Dealing new hands.");
                    }
                    // Create new shoe if the current card count in the shoe is less than "min_card_count"
                    else {
                        std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Shuffling a new shoe.");
                        gameShoe->EmptyShoe();
                        gameShoe->SetNumOfDecks(gameShoe->GetNumOfDecks());
                        gameShoe->CreateShoePrompt();
                    }
                    clear_terminal();
                    break;
                }
                // Player has chosen not to re-deposit currency into their bank
                else if (redeposit == "n") {
                    std::cout << std::endl << humanHand->GetDisplayName() << " has chosen to not redeposit more currency into their bank. Game over." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    std::cout << std::endl << "Thank you for playing " << humanHand->GetDisplayName() << "!" << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                    clear_terminal();
                    break;
                }
                // Player has entered an incorrect response to the prompt
                else {
                    clear_terminal();
                    redeposit.clear();
                    continue;;
                }
            }
            // Set "continue_playing" to true if the player has chosen to re-deposit currency
            if (redeposit == "y") {
                continue_playing = true;
            }
            // Set "continue_playing" to false if the player has chosen not to re-deposit currency
            else {
                continue_playing = false;
            }
        }
        // End the while loop if "continue_playing" has been set to false
        if (!continue_playing) {
            break;
        }
        // Continue the while loop if "continue_playing" has been set to true
        else {
            continue;
        }
    }
    std::string csvFile = csv_generator(humanHand);
    std::string txtFile = txt_generator(humanHand, csvFile, 0, 4);
    plotBarChart(txtFile);
}

/*  player_logic - Processes the possible options of what a player can do on their current hand
*   Input:
*       currentPlayerHand - Hand object that is passed by reference to be the current hand that is being played with
*       dealerHand - Hand object that is passed by reference that resembles the dealers hand
*       masterPlayerHand - Hand object that is passed by reference that resembles the players original hand
*       shoe - Shoe object that is passed by reference that resembles the current game shoe that is being played with
*       hand_counter - Integer value that represents the current hand of a player out of their total hands
*   Algorithm:
*       * Check the parameters of the current hand
*       * If the player has not split aces
*           * Create a label indicating what hand is being played with
*           * Process the logic of what a player can do with their hand
*           * Prompt the player if they would like to hit, stand, or double down, given that they can double down
*           * Proceed to process the logic of how the player has played and if they can continue to play their current hand
*           * See individual line comments for more detail
*       * If the player has split aces, simply bypass all options of hitting, standing, and doubling down
*       * Return all hand objects and shoe
*   Output:
*       currentPlayerHand - Returns the current player hand that is being played with
*       dealerHand - Returns the dealers hand
*       shoe - Returns the modified shoe object that is being used for the players to play with
*/
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> player_logic(std::shared_ptr<Hand>& currentPlayerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Hand>& masterPlayerHand, std::shared_ptr<Shoe>& shoe, int& hand_counter) {
    // Check the parameters of the given hand
    currentPlayerHand->ParametersCheck(dealerHand);
    // Player did not split Aces
    if (!masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][1])) {
        // Correctly label the current hand of the player
        std::string response;
        std::string hand_tracker;
        if (hand_counter == 1) {
            hand_tracker = "first";
        }
        else if (hand_counter == 2) {
            hand_tracker = "second";
        }
        else if (hand_counter == 3) {
            hand_tracker = "third";
        }
        else if (hand_counter == 4) {
            hand_tracker = "fourth";
        }
        else if (hand_counter == 5) {
            hand_tracker = "fifth";
        }
        else {
            hand_tracker = "current";
        }
        if (hand_counter > 1) {
            currentPlayerHand->HitHand(shoe);
        }
        // Process the logic of if a player needs to be prompted for what they should do in a hand
        while ((response != "h" && response != "s" && response != "d") && currentPlayerHand->GetCardsTotal() < 21) {
            // Prompts for if the player has not hit their current hand yet
            if (!currentPlayerHand->GetBloomFilter()->Contains(currentPlayerHand->GetFilterMatrix()[2][0])) {
                // Player is playing a split hand
                if (masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                    // Show current hand of player and dealer hand
                    std::cout << std::endl << "Here are the initial hands of each player for hand " << std::to_string(hand_counter) << ":" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    currentPlayerHand->ShowHand("initial " + hand_tracker);
                    dealerHand->ShowHand("initial");
                    // Player can double down their current split hand
                    if (currentPlayerHand->GetBloomFilter()->Contains(currentPlayerHand->GetFilterMatrix()[0][1])) {
                        // Prompt player what they would like to do
                        std::cout << std::endl << "Would you like to hit, stand, or double down for hand " << std::to_string(hand_counter) << "?" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        blackjack_strategy(currentPlayerHand, dealerHand, true);
                        std::cout << std::endl << "Enter (h) to hit, (s) to stand, and (d) to double down for " << std::to_string(hand_counter) << ": "; time_sleep(SHORT_TIME_SLEEP);
                    }
                    // Player can't double down their current split hand
                    else {
                        // Prompt player what they would like to do
                        std::cout << std::endl << "Would you like to hit or stand for hand " << std::to_string(hand_counter) << "?" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        blackjack_strategy(currentPlayerHand, dealerHand, true);
                        std::cout << std::endl << "Enter (h) to hit and (s) to stand for " << std::to_string(hand_counter) << ": "; time_sleep(SHORT_TIME_SLEEP);
                    }
                    std::cin >> response;
                    std::cout << std::endl; time_sleep(SHORT_TIME_SLEEP);
                }
                // Player is not playing a split hand
                else {
                    // Player can double down their current hand
                    if (currentPlayerHand->GetBloomFilter()->Contains(currentPlayerHand->GetFilterMatrix()[0][1])) {
                        // Prompt player what they would like to do
                        std::cout << std::endl << "Would you like to hit, stand, or double down?" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        blackjack_strategy(currentPlayerHand, dealerHand, true);
                        std::cout << std::endl << "Enter (h) to hit, (s) to stand, and (d) to double down: "; time_sleep(SHORT_TIME_SLEEP);
                    }
                    // Player can't double down their current hand
                    else {
                        // Prompt player what they would like to do
                        std::cout << std::endl << "Would you like to hit or stand?" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        blackjack_strategy(currentPlayerHand, dealerHand, true);
                        std::cout << std::endl << "Enter (h) to hit and (s) to stand: "; time_sleep(SHORT_TIME_SLEEP);
                    }
                    std::cin >> response;
                    std::cout << std::endl; time_sleep(SHORT_TIME_SLEEP);
                }          
            }
            // Player has hit their current hand
            else {
                // Show hand of current player in their split hands
                if (masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                    currentPlayerHand->ShowHand("current " + hand_tracker);
                }
                // Show hand of current player
                else {
                    currentPlayerHand->ShowHand("current");
                }
                // Show dealer hand
                dealerHand->ShowHand("initial");
                // Prompt player what they would like to do
                std::cout << std::endl << "Would you like to hit (h) or stand (s)?" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                blackjack_strategy(currentPlayerHand, dealerHand, true);
                std::cout << std::endl << "Enter (h) to hit and (s) to stand: "; time_sleep(SHORT_TIME_SLEEP);
                std::cin >> response;
                std::cout << std::endl; time_sleep(SHORT_TIME_SLEEP);
            }
            // Player has chosen to hit their hand
            if (response == "h") {
                // Set has hit to be true and hit the current hand
                currentPlayerHand->GetBloomFilter()->AddToFilter(currentPlayerHand->GetFilterMatrix()[2][0]);
                currentPlayerHand->HitHand(shoe);
                // Player has busted their current hand
                if (currentPlayerHand->GetCardsTotal() > 21) {
                    // Tell player they have busted on their current hand
                    std::cout << currentPlayerHand->GetDisplayName() << " has chosen to hit and busted. Final hand total: " << currentPlayerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    // Show hand of current split hand and hide dealers hand
                    if (masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                        std::cout << std::endl << "Here is " << currentPlayerHand->GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter)
                        << " and the " << dealerHand->GetDisplayName() << "'s current hand:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        currentPlayerHand->ShowHand("final " + hand_tracker);
                        dealerHand->ShowHand("current");
                    }
                    // Show hand of current hand and show dealer hand
                    else {
                        std::cout << std::endl << "Here is the final hand for " << currentPlayerHand->GetDisplayName() << " and the final hand of the " << dealerHand->GetDisplayName() << ":" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        currentPlayerHand->ShowHand("initial");
                        dealerHand->ShowHand("final", "show");
                    }
                    break;
                }
                // Player has a hand total of less than 21
                else if (currentPlayerHand->GetCardsTotal() < 21) {
                    // Tell player they have hit their current hand
                    std::cout << currentPlayerHand->GetDisplayName() << " has chosen to hit. Current hand total: " << currentPlayerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    // Prompt for if this is a split hand
                    if (masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                        std::cout << std::endl << "Here are the current hands of each player for hand " << std::to_string(hand_counter) << ":" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    }
                    // Prompt for if this is a singular hand
                    else {
                        std::cout << std::endl << "Here are the current hands of each player:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    }
                }
                // Players current hand is 21
                else if (currentPlayerHand->GetCardsTotal() == 21) {
                    // Tell player they have achieved 21
                    std::cout << currentPlayerHand->GetDisplayName() << " has chosen to hit. Final hand total: " << currentPlayerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    // Show hand of current split hand
                    if (masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                        std::cout << std::endl << "Here is " << masterPlayerHand->GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter) << " and the " 
                        << dealerHand->GetDisplayName() << "'s current hand:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        currentPlayerHand->ShowHand("final " + hand_tracker);
                        dealerHand->ShowHand("current", "");
                    }
                    // Show hand of singular hand
                    else {
                        std::cout << std::endl << "Here is the final hand for " << currentPlayerHand->GetDisplayName() << " and the initial hand of the " 
                        << dealerHand->GetDisplayName() << ":" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        currentPlayerHand->ShowHand("final");
                        dealerHand->ShowHand("initial", "show");
                    }
                }
                response.clear();
            }
            // Player has chosen to stay on their current hand
            else if (response == "s") {
                // Tell player they have chosen to stay
                std::cout << currentPlayerHand->GetDisplayName() << " has chosen to stand. Final hand total: " << currentPlayerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                // Show hands of current hand in split hands
                if (masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                    std::cout << std::endl << "Here is " << currentPlayerHand->GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter)
                    << " and the " << dealerHand->GetDisplayName() << "'s current hand:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    currentPlayerHand->ShowHand("final " + hand_tracker);
                    dealerHand->ShowHand("current" , "");
                }
                // Show hand of singular hand
                else {
                    std::cout << std::endl << "Here is the final hand for " << currentPlayerHand->GetDisplayName() << " and the initial hand of the " 
                    << dealerHand->GetDisplayName() << ":" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    currentPlayerHand->ShowHand("final");
                    dealerHand->ShowHand("initial" , "show");
                }
                break;
            }
            // Player has chosen to double down
            else if (response == "d") {
                // Player can double down
                if (currentPlayerHand->GetBloomFilter()->Contains(currentPlayerHand->GetFilterMatrix()[0][1])) {
                    // Update bank totals of player and hit hand
                    currentPlayerHand->GetBloomFilter()->AddToFilter(currentPlayerHand->GetFilterMatrix()[1][0]);
                    currentPlayerHand->UpdateBank(0, currentPlayerHand->GetWager());
                    currentPlayerHand->SetWager(2 * currentPlayerHand->GetWager());
                    currentPlayerHand->HitHand(shoe);
                    // Player has busted
                    if (currentPlayerHand->GetCardsTotal() > 21) {
                        // Tell player they have busted on their current hand
                        std::cout << currentPlayerHand->GetDisplayName() << " has doubled down and busted. Final hand total: " << currentPlayerHand->GetDisplayCardsTotal() << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                        // Show current hand of split hand
                        if (masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                            std::cout << std::endl << "Here is " << currentPlayerHand->GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter)
                            << " and the " << dealerHand->GetDisplayName() << "'s current hand:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            currentPlayerHand->ShowHand("final " + hand_tracker);
                            dealerHand->ShowHand("current");
                        }
                        // Show singular hand
                        else if (!masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                            std::cout << std::endl << "Here is the final hand for " << currentPlayerHand->GetDisplayName() << " and the final hand of the " 
                            << dealerHand->GetDisplayName() << ":" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            currentPlayerHand->ShowHand("final");
                            dealerHand->ShowHand("final", "show");
                        }
                        else
                        break;
                    }
                    // Player has reached 21
                    else if (currentPlayerHand->GetCardsTotal() <= 21) {
                        // Tell player they have reached 21
                        std::cout << currentPlayerHand->GetDisplayName() << " has doubled down. Final hand total: " << currentPlayerHand->GetDisplayCardsTotal() << "." << std::endl; 
                        // Show current hand of split hand
                        if (masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                            std::cout << std::endl << "Here is " << currentPlayerHand->GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter) << " and the " 
                            << dealerHand->GetDisplayName() << "'s current hand:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            currentPlayerHand->ShowHand("final " + hand_tracker);
                            dealerHand->ShowHand("current");
                        }
                        // Show singular hand
                        else {
                            std::cout << std::endl << "Here is the final hand for " << currentPlayerHand->GetDisplayName() << " and the initial hand of the " 
                            << dealerHand->GetDisplayName() << ":" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            currentPlayerHand->ShowHand("final");
                            dealerHand->ShowHand("initial", "show");
                        }
                        break;
                    }
                }
                // Player cannot double down
                else {
                    // Tell player they cannot double down, return to choices for player
                    std::cout << "Your current bank total of " << currentPlayerHand->GetDisplayBankTotal() << " is not greater than your wager of "
                    << currentPlayerHand->GetDisplayWager() << ". You cannot double down." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    response.clear();
                    continue;
                }
            }
            // Player has entered and incorrect value for a choice
            else if (response != "h" && response != "s" && response != "d") {
                if (!masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
                    std::cout << color_text(31, "Invalid choice") << "." << std::endl; 
                }
                else {
                    std::cout << color_text(31, "Invalid choice") << "." << std::endl << std::endl; 
                }        
                response.clear();
                continue;
            }
        }
        if (currentPlayerHand->GetCardsTotal() == 21 && masterPlayerHand->GetBloomFilter()->Contains(masterPlayerHand->GetFilterMatrix()[1][2])) {
            std::cout << std::endl << currentPlayerHand->GetDisplayName() << " has gotten " << currentPlayerHand->GetDisplayCardsTotal() << "! You no longer need to play this hand: Your final hand is:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
            currentPlayerHand->ShowHand("final " + hand_tracker);
        }
        // Copy variables of current hand to master hand
        masterPlayerHand->CopyVariables(currentPlayerHand);
    }
    // Player has chosen to split aces
    else {
        masterPlayerHand->CopyVariables(currentPlayerHand);
    }
    // Return hands of player
    return std::make_tuple(currentPlayerHand, dealerHand, shoe);
}

/*  plotBarChart - Creates a bar chart of the results from a text file of a players hand
*   Input:
*       input - Constant string that is passed by reference that represents the name of the file
*   Algorithm:
*       * Create a gnuplot object
*       * Check if the file opened successfully
*       * Set plot properties
*       * Set axis ranges
*       * Plot the data of the text file
*       * Close gnuplot
*   Output
*       This function does not return a value
*/
void plotBarChart(const std::string& input) {
    const char* fileName = input.c_str();
    // Create gnuplot object
    FILE *plt = popen("gnuplot -persist", "w");
    // File failed to open
    if (plt == NULL) {
        return;
    }
    // Set plot properties
    fprintf(plt, "set boxwidth 0.25 relative\n"); // Set box width
    fprintf(plt, "set style fill solid\n"); // Set style of the bars
    fprintf(plt, "set grid\n"); // Show a grid
    // Set axis ranges
    fprintf(plt, "set xrange [0:]\n"); // Set x range
    fprintf(plt, "set yrange [0:]\n"); // Set y range
    // Plot the data
    fprintf(plt, "plot '%s' every ::1 using 1:2 with boxes lc rgb 'blue'\n", fileName);
    // Close gnuplot
    pclose(plt);
}

/*  same_rank_check - Checks to see if the player has the same rank in their hand and if they want to split their hand
*   Input:
*       playerHand - Hand object passed by reference that represents the players hand that is being checked for the below conditions
*       dealerHand - Hand object passed by reference that represents the dealers hand that is being checked against the players
*       shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
*   Algorithm:
*       * First check if the player is able to split their hand or not
*           * Proceed to check if they can split aces, if they can, prompt them if they would like to and process the logic after that (See inline comments)
*           * Check if they can split other cards than aces, prompt them if they would like to and process the logic after that (See inline comments)
*       * Otherwise, return the values and continue with the logic of the game
*   Output:
*       new_hand - Vector of Hand objects, this can either be singular or multiple depending on the checks and choices of the players hand
*       playerHand - Hand object that represents the players hand and variables that originally were fed into the function that are now modified
*       dealerHand - Hand object that represents the dealers hand with all of their variables
*       shoe - Shoe object that represents the shoe that is being played with by the player and dealer
*       hand_count - Integer value that represents that number of individual hands that the player has after this function has completed
*/
std::tuple<std::vector<std::shared_ptr<Hand>>, std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>, int> same_rank_check(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe) {
    int hand_count = 1;
    std::vector<std::shared_ptr<Hand>> new_hand;
    // Check if player can split their hand
    if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][2]) || playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][3])) {
        // Player can split aces
        if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][2])) {
            std::string aces_response;
            while (aces_response.empty()) {
                // Prompt player to enter response to split aces
                std::cout << std::endl << "You have the same rank of " << playerHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << " in your hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "Would you like to split your hand? You may only split your hand once." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                blackjack_strategy(playerHand, dealerHand, true);
                std::cout << std::endl << "Enter (y) for yes and (n) for no: "; time_sleep(SHORT_TIME_SLEEP);
                std::cin >> aces_response; std::cout << std::endl;
                // Player has chosen to split aces
                if (aces_response == "y") {
                    playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[1][1]);
                    playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][3]);
                    std::cout << playerHand->GetDisplayName() << " has chosen to split their " << playerHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << "'s." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    std::vector<std::shared_ptr<Hand>> split_aces = split_hand(playerHand);
                    std::shared_ptr<Hand> player_hand_1 = split_aces.at(0);
                    std::shared_ptr<Hand> player_hand_2 = split_aces.at(1);
                    player_hand_1->HitHand(shoe);
                    player_hand_2->HitHand(shoe);
                    new_hand.push_back(player_hand_1);
                    new_hand.push_back(player_hand_2);
                    hand_count = 2;
                    int loop_counter = 1;
                    std::string hand_tracker;
                    for (std::shared_ptr<Hand>& current_hand : new_hand) {
                        if (loop_counter == 1) {
                            hand_tracker = "first";
                        }
                        else if (loop_counter == 2) {
                            hand_tracker = "second";
                        }
                        current_hand->ShowHand(hand_tracker);
                        loop_counter++;
                    }
                    dealerHand->ShowHand();
                    playerHand->CopyVariables(new_hand.back());
                }
                // Player has chosen to not split aces
                else if (aces_response == "n") {
                    playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][3]);
                    std::cout << playerHand->GetDisplayName() << " has chosen not to split their " << playerHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << "'s." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    playerHand->ShowHand();
                    dealerHand->ShowHand();
                    new_hand.push_back(playerHand);
                    playerHand->CopyVariables(new_hand.back());
                }
                // Player has entered an invalid response
                else {
                    std::cout << std::endl << color_text(31, "Invalid choice") + " of " + color_text(31, aces_response) + ". Please re-enter your decision." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    aces_response.clear();
                }
            }
        }
        // Player can split normal hand
        else if (playerHand->GetBloomFilter()->Contains(playerHand->GetFilterMatrix()[0][3])) {
            std::string same_rank_response;
            while (same_rank_response.empty()) {
                // Prompt player to enter response to split hand
                std::cout << std::endl << "You have the same rank of " << playerHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << " in your hand." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                std::cout << std::endl << "Would you like to split your hand? You can split up to four times." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                blackjack_strategy(playerHand, dealerHand, true);
                std::cout << std::endl << "Enter (y) for yes and (n) for no: "; time_sleep(SHORT_TIME_SLEEP);
                std::cin >> same_rank_response; std::cout << std::endl; 
                // Player has chosen to split their hand
                if (same_rank_response == "y") {
                    playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[1][2]);
                    playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][4]);
                    std::cout << playerHand->GetDisplayName() << " has chosen to split their " << playerHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << "'s." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    std::vector<std::shared_ptr<Hand>> splitHand = split_hand(playerHand);
                    std::vector<std::shared_ptr<Hand>> splitHands;
                    std::vector<std::shared_ptr<Hand>> tempHands;
                    std::shared_ptr<Hand> playerHand1 = splitHand.at(0);
                    std::shared_ptr<Hand> playerHand2 = splitHand.at(1);
                    std::shared_ptr<Hand> checkingHand(new Hand);
                    playerHand2->HitHand(shoe);
                    tempHands.push_back(playerHand2);
                    tempHands.push_back(playerHand1);
                    checkingHand = playerHand2;
                    checkingHand->CopyVariables(playerHand2);
                    checkingHand->ParametersCheck(dealerHand);
                    int split_counter = 1;
                    hand_count++;
                    int loop_counter = 1;
                    std::string hand_tracker;
                    for (std::shared_ptr<Hand>& current_hand : tempHands) {
                        if (loop_counter == 1) {
                            hand_tracker = "first";
                        }
                        else if (loop_counter == 2) {
                            hand_tracker = "second";
                        }
                        current_hand->ShowHand(hand_tracker);
                        loop_counter++;
                    }
                    dealerHand->ShowHand();
                    // Player can split hand again
                    if (checkingHand->GetBloomFilter()->Contains(checkingHand->GetFilterMatrix()[0][3])) {
                        while (split_counter < 4 && checkingHand->GetBloomFilter()->Contains(checkingHand->GetFilterMatrix()[0][3])) {
                            std::string split_again;
                            // Prompt player if they want to split again
                            while (split_again != "y" || split_again != "n") {
                                std::cout << std::endl << "You have pulled the same rank of " << checkingHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << " again." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                std::cout << std::endl << "Would you like to split your current hand again?" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                blackjack_strategy(checkingHand, dealerHand, true);
                                std::cout << std::endl << "Enter (y) for yes and (n) for no: "; time_sleep(SHORT_TIME_SLEEP);
                                std::cin >> split_again; std::cout << std::endl;
                                if (split_again == "y") {
                                    split_counter++;
                                    hand_count++;
                                    std::vector<std::shared_ptr<Hand>> new_split = split_hand(checkingHand);
                                    std::shared_ptr<Hand> newPlayerHand1 = new_split.at(0);
                                    std::shared_ptr<Hand> newPlayerHand2 = new_split.at(1);
                                    newPlayerHand2->HitHand(shoe);
                                    splitHands.insert(splitHands.begin(), newPlayerHand1);
                                    checkingHand = newPlayerHand2;
                                    checkingHand->CopyVariables(newPlayerHand2);
                                    checkingHand->ParametersCheck(dealerHand);
                                    break;
                                }
                                else if (split_again == "n") {
                                    break;
                                }
                                else {
                                    std::cout << color_text(31, "Invalid Entry") << ". Please enter a valid choice." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    split_again.clear();
                                }
                            }
                            splitHands.insert(splitHands.begin(), checkingHand);
                            splitHands.insert(splitHands.end(), playerHand1);
                            for (int i = 0; i < splitHands.size(); i++) {
                                splitHands.at(i)->CopyVariables(checkingHand);
                            }
                            // Player has chosen to split their hand again
                            if (checkingHand->GetBloomFilter()->Contains(checkingHand->GetFilterMatrix()[0][3]) && split_again == "y") {
                                // Player is eligible to split their hand again
                                if (split_counter < 4) {
                                    std::cout << playerHand->GetDisplayName() << " has chosen to split their hand again." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    int loop_counter = 1;
                                    std::string hand_tracker;
                                    for (std::shared_ptr<Hand>& current_hand : splitHands) {
                                        if (loop_counter == 1) {
                                            hand_tracker = "first";
                                        }
                                        else if (loop_counter == 2) {
                                            hand_tracker = "second";
                                        }
                                        else if (loop_counter == 3) {
                                            hand_tracker = "third";
                                        }
                                        else if (loop_counter == 4) {
                                            hand_tracker = "fourth";
                                        }
                                        else {
                                            hand_tracker = "current";
                                        }
                                        current_hand->ShowHand(hand_tracker);
                                        loop_counter++;
                                    }
                                    splitHands.erase(splitHands.begin());
                                    splitHands.pop_back();
                                    continue;
                                }
                                // Player cannot split their hand again due to max splits
                                else if (split_counter == 4) {
                                    std::cout << playerHand->GetDisplayName() << " has reached the max amount of times to split. You can no longer split your hands." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    int loop_counter = 1;
                                    std::string hand_tracker;
                                    for (std::shared_ptr<Hand>& current_hand : splitHands) {
                                        if (loop_counter == 1) {
                                            hand_tracker = "first";
                                        }
                                        else if (loop_counter == 2) {
                                            hand_tracker = "second";
                                        }
                                        else if (loop_counter == 3) {
                                            hand_tracker = "third";
                                        }
                                        else if (loop_counter == 4) {
                                            hand_tracker = "fourth";
                                        }
                                        else {
                                            hand_tracker = "current";
                                        }
                                        current_hand->ShowHand(hand_tracker);
                                        loop_counter++;
                                    }
                                    dealerHand->ShowHand();
                                    break;
                                }
                            }
                            // Player has chosen to not split their hand again or can't
                            else if (!checkingHand->GetBloomFilter()->Contains(checkingHand->GetFilterMatrix()[0][3]) || split_again == "n") {
                                checkingHand->CheckSameParamInHand("R");
                                // Player cannot split their hand again
                                if (!checkingHand->GetBloomFilter()->Contains(checkingHand->GetFilterMatrix()[0][3])) {
                                    // Player doesn't have the currency to split their hand again
                                    if (checkingHand->GetBankTotal() < checkingHand->GetWager()) {
                                        std::cout << "You pulled the same rank of " << checkingHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << " again but you do not have enough currency to continue splitting. You can no longer split your hands." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                        std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    }
                                    // Player did not pull the same rank again
                                    else if (!checkingHand->GetBloomFilter()->Contains(checkingHand->GetFilterMatrix()[2][2])) {
                                        std::cout << "You did not pull the same rank of " << checkingHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << " again. You can no longer split your hands." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                        std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    }
                                    int loop_counter = 1;
                                    std::string hand_tracker;
                                    for (std::shared_ptr<Hand>& current_hand : splitHands) {
                                        if (loop_counter == 1) {
                                            hand_tracker = "first";
                                        }
                                        else if (loop_counter == 2) {
                                            hand_tracker = "second";
                                        }
                                        else if (loop_counter == 3) {
                                            hand_tracker = "third";
                                        }
                                        else if (loop_counter == 4) {
                                            hand_tracker = "fourth";
                                        }
                                        else {
                                            hand_tracker = "current";
                                        }
                                        current_hand->ShowHand(hand_tracker);
                                        loop_counter++;
                                    }
                                    dealerHand->ShowHand();
                                }
                                // Player has chosen to not split their hand
                                else if (split_again == "n") {
                                    std::cout << playerHand->GetDisplayName() << " has chosen not to split their hand again." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                                    int loop_counter = 1;
                                    std::string hand_tracker;
                                    for (std::shared_ptr<Hand>& current_hand : splitHands) {
                                        if (loop_counter == 1) {
                                            hand_tracker = "first";
                                        }
                                        else if (loop_counter == 2) {
                                            hand_tracker = "second";
                                        }
                                        else if (loop_counter == 3) {
                                            hand_tracker = "third";
                                        }
                                        else if (loop_counter == 4) {
                                            hand_tracker = "fourth";
                                        }
                                        else {
                                            hand_tracker = "current";
                                        }
                                        current_hand->ShowHand(hand_tracker);
                                        loop_counter++;
                                    }
                                    dealerHand->ShowHand();
                                }
                                break;
                            }
                        }
                        // Assign new_hand to splitHands
                        new_hand = splitHands;
                    }
                    // Player can't split hand again
                    else if (!checkingHand->GetBloomFilter()->Contains(checkingHand->GetFilterMatrix()[0][3])) {
                        checkingHand->CheckSameParamInHand("R");
                        // Player doesn't have the currency to split again
                        if (checkingHand->GetBloomFilter()->Contains(checkingHand->GetFilterMatrix()[2][2])) {
                            std::cout << std::endl << "You pulled the same rank of " << checkingHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << " again but you do not have enough currency to continue splitting. You can no longer split your hands." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            int loop_counter = 1;
                            std::string hand_tracker;
                            for (std::shared_ptr<Hand>& current_hand : tempHands) {
                                if (loop_counter == 1) {
                                    hand_tracker = "first";
                                }
                                else if (loop_counter == 2) {
                                    hand_tracker = "second";
                                }
                                else {
                                    hand_tracker = "current";
                                }
                                current_hand->ShowHand(hand_tracker);
                                loop_counter++;  
                            }
                            dealerHand->ShowHand();
                        }
                        // Player did not pull the same card again
                        else {
                            std::cout << std::endl << "You did not pull the same rank of " << checkingHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << " again. You can no longer split your hands." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(SHORT_TIME_SLEEP);
                            int loop_counter = 1;
                            std::string hand_tracker;
                            for (std::shared_ptr<Hand>& current_hand : tempHands) {
                                if (loop_counter == 1) {
                                    hand_tracker = "first";
                                }
                                else if (loop_counter == 2) {
                                    hand_tracker = "second";
                                }
                                else {
                                    hand_tracker = "current";
                                }
                                current_hand->ShowHand(hand_tracker);
                                loop_counter++;  
                            }
                            dealerHand->ShowHand();
                        }
                        // Assign new_hand to tempHands
                        new_hand = tempHands;
                    }
                    playerHand->CopyVariables(new_hand.back());
                }
                // Player has chosen to not split their hand
                else if (same_rank_response == "n") {
                    playerHand->GetBloomFilter()->AddToFilter(playerHand->GetFilterMatrix()[3][4]);
                    std::cout << playerHand->GetDisplayName() << " has chosen not to split their " << playerHand->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() << "'s." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    playerHand->ShowHand();
                    dealerHand->ShowHand();
                    new_hand.push_back(playerHand);
                    playerHand->CopyVariables(new_hand.back());
                }
                // Player has entered an invalid response
                else {
                    std::cout << color_text(31, "Invalid choice") + " of " + color_text(31, same_rank_response) + ". Please re-enter your decision." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    same_rank_response.clear();
                }
            }
        }
    }
    else {
        new_hand.push_back(playerHand);
        playerHand->CopyVariables(new_hand.back());
    }
    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
}

/*  split_hand - Splits the hand of a current player and produces two new hands for the player
*   Input:
*       input - Hand object passed by reference that represents the original hand of the user
*   Algorithm:
*       * Create a vector of hands that will represent the new hands of the player
*       * Update the bank of the player by withdrawing money from the bank of the player
*       * Append one of the cards from the players original hand, copy the variables, and append the hand
*   Output:
*       split_hands - This is a vector of hands that represents the new hands of the player
*/
std::vector<std::shared_ptr<Hand>> split_hand(std::shared_ptr<Hand>& input) {
    // Create a vector of hands for the player
    std::vector<std::shared_ptr<Hand>> split_hands;
    int handsTotal = input->GetHandsCurrentlyHeld();
    handsTotal++;
    input->SetHandsCurrentlyHeld(handsTotal);
    // Update the bank of the player
    input->UpdateBank(0, input->GetWager());
    // Append card from players original hand, copy the variables of the input hand, and then add the hand to the vector of new hands
    std::shared_ptr<node<Card>> current = input->GetPlayerCards()->GetRoot();
    while (current != nullptr) {
        std::shared_ptr<Hand> newHand(new Hand);
        std::shared_ptr<Card> tempCard(new Card(current->data.GetRank(), current->data.GetSuit()));
        std::shared_ptr<node<Card>> tempNode = newHand->GetPlayerCards()->InitNode(tempCard);
        newHand->AddCardToHand(tempNode);
        newHand->CopyVariables(input);
        split_hands.push_back(newHand);
        current = current->nextNode;
    }
    return split_hands;
}

/*  stats_tracker - Updates the stat trackers of a current hand
*   Input:
*       input - Hand object passed by reference who's stats are being updated
*   Algorithm:
*       * Update hands bank total
*       * Update hands cards total
*       * Update hands nets total
*       * Update hands played total
*       * Update hands wagers total
*   Output:
*       This function does not return a value
*/
void stats_tracker(std::shared_ptr<Hand>& input) {
    // Update hands bank total
    std::shared_ptr<node<float>> bankNode = input->GetHandBankTotals()->InitNode(input->GetBankTotal());
    input->SetHandBankTotals(bankNode);
    // Update hands cards total
    std::shared_ptr<node<int>> cardsTotalNode = input->GetHandCardTotals()->InitNode(input->GetCardsTotal());
    input->SetHandCardTotals(cardsTotalNode);
    // Update hands nets total
    std::shared_ptr<node<float>> netsTotalNode = input->GetHandNets()->InitNode(input->GetNet());
    input->SetHandNets(netsTotalNode);
    // Update hands played total
    std::shared_ptr<node<int>> handsPlayedNode = input->GetHandPlayed()->InitNode(input->GetHandsPlayed());
    input->SetHandPlayed(handsPlayedNode);
    // Update hands wagers total
    std::shared_ptr<node<float>> handWagerNode = input->GetHandWagers()->InitNode(input->GetWager());
    input->SetHandWagers(handWagerNode);
}

/*  txt_generator - Generates a text file off of a given csv file that is fed into the function
*   Input:
*       input - Hand object that is passed by reference that represents the player who's statistics are being generated
*       csvFilename - Constant string value that is passed by reference that represents the csv file that is going to be converted to a txt file
*       firstInt - Constant integer value that represents the first row of a csv file that will be converted into a txt file
*       secondInt - Constant integer value that represents the second row of a csv file that will be converted into a txt file
*   Algorithm:
*       * Generate name for the text file
*       * Generate objects for files
*       * Test if the files open, return name of string if file fails to open
*       * Create header names of file
*       * Grab the first row of the csv file
*       * Write the header of the file
*       * Write to text file while contents are present in the csv file
*       * Close file and return name of file
*   Output:
*       fileName - After creating the txt file, this function returns the name of the file that has been created
*/
std::string txt_generator(std::shared_ptr<Hand>& input, const std::string& csvFilename, const int firstInt, const int secondInt) {
    // Generate a name for the txt file
    std::string txtFilename = input->GetName() + " Results.txt";
    // Generate an ifstream object of the csv file
    std::ifstream csvFile(csvFilename);
    // Generate an ofstream object of the txt file
    std::ofstream txtFile(txtFilename);
    // csv or txt file failed to open, return the string
    if (!csvFile.is_open() || !txtFile.is_open()) {
        return txtFilename;
    }
    // Create headers for the columns of the txt file
    std::string firstColumn;
    std::string secondColumn;
    // Generate the name of the first column
    switch (firstInt) {
        case 0:
            firstColumn = "Hand Number";
            break;
        case 1:
            firstColumn = "Hand Wager";
            break;
        case 2:
            firstColumn = "Hand Net";
            break;
        case 3:
            firstColumn = "Hand Total";
            break;
        case 4:
            firstColumn = "Bank Total";
            break;
        default:
            break;
    }
    // Generate the name of the second column
    switch (secondInt) {
        case 0:
            secondColumn = "Hand Number";
            break;
        case 1:
            secondColumn = "Hand Wager";
            break;
        case 2:
            secondColumn = "Hand Net";
            break;
        case 3:
            secondColumn = "Hand Total";
            break;
        case 4:
            secondColumn = "Bank Total";
            break;
        default:
            break;
    }
    // Grab the row of csv file
    std::string line;
    std::getline(csvFile, line);
    // Write the header of the csv file
    txtFile << firstColumn << " " << secondColumn << std::endl;
    // Keep writing to txt file while there is still data in the csv file
    while(std::getline(csvFile, line)) {
        std::istringstream ss(line);
        std::string value;
        std::vector<std::string> values;
        while (std::getline(ss, value, ',')) {
            values.push_back(value);
        }
        txtFile << values[firstInt] << " " << values[secondInt] << std::endl;
    }
    // Close files
    csvFile.close();
    txtFile.close();
    // Return name of txt file
    return txtFilename;
}