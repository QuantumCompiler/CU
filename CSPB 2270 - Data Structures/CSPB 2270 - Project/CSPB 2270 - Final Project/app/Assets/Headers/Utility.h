// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef UTILITY_H
#define UTILITY_H
#include "../HPP/LinkedList.hpp"

void clear_terminal(); // Clears a terminal
std::string color_text(const int codeInput, const std::string textInput); // Colors input text
void progress_bar(const long input, const std::string loadingMessage, const std::string finishedMessage); // Progress bar animation
int random_int(const int lowerBound, const int upperBound); // Generates random integer in a range
float round_input(float input); // Founds a float input
std::string round_to_string(const float input); // Rounds a float and generates a string
void time_sleep(const long input); // Sleeps the console for a specified time

#endif