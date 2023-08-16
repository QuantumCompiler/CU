 <h1 align="center">Blackjack Logic With Bloom Filters</h1>

## Data Structure of Project

This project incorporates the use of a bloom filter in the context of a blackjack program where the filter is used to process specific logical conditions that arise during a hand for a player while they are playing blackjack. During a blackjack hand, players must have certain specific conditions checked for each stage of the hand. For example, when a player is dealt cards the first condition that is usually checked for is whether or not the player has blackjack in their current hand. Several checks occur after this initial check, like if a player is eligible to split their hand, if they can double down, buy insurance, amongst other conditions. This project uses a bloom filter to keep track of each of these conditions for a given players hand in a game. The total list of conditions that are checked during the logic processing of the hand can be seen below:

- Conditions To Be Checked:
    - CanBuyInsurance - This is a condition that is turned on or off depending on if a player is eligible to purchase insurance for a given hand.
    - CanDoubleDown - This is a condition that is turned on or off depending on whether or not a player is eligible to double down on their hand.
    - CanSplitAces - This is a condition that is turned on or off depending on if a player is eligible to split a hand where duplicate Aces are present off of the deal.
    - CanSplitHand - This is a condition that is turned on or off depending on if a player is eligible to split a hand
    where duplicate ranks occur in a hand that happen to not be Aces.
    - ChoseBuyInsurance - This is a condition that is turned on or off depending on whether a player has chosen to purchase insurance for a given hand of a player.
    - ChoseDoubleDown - This is a condition that is turned on or off depending on whether a player has chosen to double down on their current hand.
    - ChoseSplitAces - This is a condition that is turned on or off depending on whether a player has chosen to split a hand where duplicate Aces were present off of the initial deal to a player.
    - ChoseSplitHand - This is a condition that is turned on or off depending on whether a player has chosen to split a hand where duplicate ranks occur were the rank of the cards are not Aces.
    - DoubleDownResponse - This is a condition that is turned on or off depending on whether a player has answered the prompt for if they would like to double down on their current hand off of the initial deal.
    - HasBlackjack - This is a condition that is turned on or off depending on if a player was dealt a blackjack off of the initial deal of a hand.
    - HasHit - This is a condition that is turned on or off depending on whether a player has hit a current hand in blackjack.
    - ParamInHand - This is a condition that is turned on or off depending on whether a specific parameter (either rank or suit of a card) is present in a players hand.
    - SameParamInHand - This is a condition that is turned on or off depending on whether a specific parameter (either rank or suit of a card) is present for all cards in a players hand.
    - ShouldDoubleDown - This is a condition that is turned on or off depending on if blackjack strategy dictates if a player should double down for a given hand.
    - ShouldHit - This is a condition that is turned on or off depending on if blackjack strategy dictates if a player should hit for a given hand.
    - ShouldSplit - This is a condition that is turned on or off depending on if blackjack strategy dictates if a player should split for a given hand.
    - ShouldStand - This is a condition that is turned on or off depending on if blackjack strategy dictates if a player should stand for a given hand.
    - SoftSevenTeen - This is a condition that is turned on or off depending on whether or not a player currently possesses a hand where a soft 17 (a hand in blackjack where the players high card total is equal to 17 and there is an Ace present where it can either be counted as an 11 or a 1) is present.
    - SplitAcesResponse - This is a condition that is turned on or off depending on if a player has responded to the prompt of whether or not they would like to split their hand where duplicate Aces occur in a players hand off of the initial deal.
    - SplitHandResponse - This is a condition that is turned on or off depending on if a player has responded to the prompt of whether or not they would like to split their hand where duplicate ranks occur in a players hand off of the initial deal.

In the list of aforementioned conditions, "turning on or of" refers to if a condition is added to the bloom filter or if it is not present in the bloom filter. In the context of the bloom filters application in this program, a condition is only "turned on" if it has been inserted into the filter. A condition is "turned off" if it is not present in the filter.

## Bloom Filters

A bloom filter is a data structure in object oriented programming that utilizes hashing of values that are to be inserted into a bloom filter. In bloom filters, there is typically a container that is used to hold boolean values that indicate whether or not a value is "probably present" or not present. Because of their design, bloom filters can produce false positives (a return of true when the condition being checked is actually not true) but they do not return false negatives (assuming that the declaration and definition of the structure is done properly). Typical bloom filters incorporate functions that will add values to the filter as well as a function that will search the filter if the value is present in the filter. Bloom filters must also incorporate functions that hash values as well as a function that will calculate the index of said value with the hashed value. Bloom filters are optimal due to their space efficiency and runtime efficiency. The bloom filter for this project has the following structure / member functions:

- Bloom Filter Data Structure:
    - Filter Struct - This is a custom structure that contains the following data members:
        - bucketIndex - An index value for where the value would / will be found inside the bloom filter.
        - filter - A container that holds boolean values indicating if an element is probably present or not present within the filter.
        - hashCode - A value that is calculated with the use of hash functions for a given value.
        - hashFunctionIterations - A value that is used to determine how many times over a hash value will be recalculated in the context of an algorithm found inside the bloom filter class itself.
    - BloomFilter Class - This is class that incorporates the aforementioned Filter structure along with defined member functions that are used for the implementation of a bloom filter.
        - Private Members:
            - bloomFilter - Filter struct that is to be used inside the bloom filter class
        - Public Members:
            - BloomFilter - This is a constructor for the bloom filter class.
            - ~BloomFilter - This is a de-constructor for the bloom filter class.
            - AddToFilter - Adds a value to a bloom filter.
            - CalculateBucketIndex - Calculates the bucket index of given value.
            - CalculateHashCode - Calculates the hash code for a given value.
            - ClearFilter - Clears the container of the bloom filter.
            - Contains - Searches a bloom filter to determine if a value is present in it.
            - RemoveElement - Manually removes an element from a bloom filter.
            - GetBucket - Retrieves the bucket index of "bloomFilter"
            - GetFilter - Retrieves the container of "bloomFilter"
            - GetHashCode - Retrieves the hash code of "bloomFilter"
            - GetHashFuncIterations - Retrieves the number of hash function iterations of "bloomFilter"
            - SetBucket - Mutates the bucket index of "bloomFilter"
            - SetFilter - Mutates the container of "bloomFilter"
            - SetHashCode - Mutates the hash code "bloomFilter"
            - SetNumHashFunctions - Mutates the number of hash function iterations of "bloomFilter"

The declarations of definitions of these member functions are very involved and cannot be easily summarized in the context of this README. Visit the Assets directory found in the app director of this project to further examine the definition and declaration of these members.

## Steps For Compiling

To compile and run this project, navigate to the **build** directory and type the following commands into the terminal / command prompt:

- Steps For Compilation:
    - cmake ..
    - make
    - ./gTest - To run the test suite for this project
    - ./main - To run the main program for this projects