// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Utility.h"
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- Suit and Rank Arrays ---- ---- ---- ---- ---- ---- ---- ---- ---- ----  //
std::string Suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
std::string Ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
// ---- ---- ---- ---- ---- ---- ---- ---- ---- Class Independent Methods ---- ---- ---- ---- ---- ---- ---- ---- //
/*  clear_terminal - Clears the terminal of a machine
*   Input:
*       * This function does not have any input parameters
*   Algorithm:
*       If the machine is a Windows machine, then "cls" is passed as a system command
*       If the machine is a Unix machine, then "clear" is passed as a system command
*   Output:
*       This function does not return a value
*/
void clear_terminal() {
// Windows machines
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
// Unix machines
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#endif
}

/*  color_text - Styles the console text of an entry
*   Input:
*       codeInput - Constant integer value that corresponds to the desired color to be outputted to console
*           codeInput = 31 - Red Text
*           codeInput = 32 - Green Text
*           codeInput = 33 - Yellow Text
*           codeInput = 34 - Blue Text
*           codeInput = 35 - Purple Text
*           codeInput = 36 - Cyan Text
*           codeInput = 37 - White Text
*       textInput - Constant string value that is passed to be changed to a different color
*   Algorithm:
*       * codeInput is ran through a switch statement to check if it matches one of codes to style one of text
*       * If codeInput matches one of the above input codes, then the parameter "textInput" is changed to the color
*         of the parameter "codeInput"
*   Output:
*       The function returns the string combination of "code + textInput + "\033[0m""
*           code is what is changed to according to codeInput
*           textInput is the string parameter that is fed into the function to be colored
*           \033[0m" is the ending of the unicode phrase to change the output in console
*/
std::string color_text(const int codeInput, const std::string textInput) {
    std::string code;
    switch (codeInput)
    {
    case 31:
        code = "\033[31m"; // Red Text
        break;
    case 32:
        code = "\033[32m"; // Green Text
        break;
    case 33:
        code = "\033[33m"; // Yellow Text
        break;
    case 34:
        code = "\033[34m"; // Blue Text
        break;
    case 35:
        code = "\033[35m"; // Purple Text
        break;
    case 36:
        code = "\033[36m"; // Cyan Text
        break;
    case 37:
        code = "\033[37m"; // White Text
        break;
    default:
        code = "\033[37m"; // Default Text
        break;
    }
    return code + textInput + "\033[0m";
}

/*  progress_bar - This function provides a loading bar animation for a given amount of time
*   Input:
*       input - Constant long value that is used to calculate the time that is required for the animation to run
*       loadingMessage - Constant string value that is used to indicate the desired message for when the bar is loading
*       finishedMessage - Constant string value that is used to display a message when the animation ends
*   Algorithm:
*       * Calculate the total progress based on the input value
*       * Display the progress bar with a loading animation
*       * Update the progress bar with the percentage completion and loading message
*       * Sleep for a short duration to simulate the loading process
*       * Display the completed progress bar with 100% and finished message
*       * Sleep for a short duration after the progress is complete
*   Output:
*       This function does not return a value
*/
void progress_bar(const long input, const std::string loadingMessage, const std::string finishedMessage) {
    // Length of progress bar
    int progressLength = 30;
    // Generate random color for loading bar
    int randomLoad = random_int(33, 36);
    for (int progress = 0; progress <= progressLength; progress++) {
        float percentage = static_cast<float>(progress) / progressLength * 100;
        std::cout << color_text(randomLoad, "[");
        for (int i = 0; i < progress; i++) {
            std::cout << color_text(randomLoad, "=");
        }
        std::cout << color_text(randomLoad, ">") << std::string(progressLength - progress, ' ') << color_text(randomLoad, "]");
        std::cout << " " << color_text(randomLoad, std::to_string(static_cast<int>(percentage))) << color_text(randomLoad, "%") + " " + color_text(randomLoad, loadingMessage) + "\033[K\r";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(input / 100));
    }
    std::cout << color_text(32, "[");
    for (int i = 0; i < progressLength; i++) {
        std::cout << color_text(32, "=");
    }
    std::cout << "\033[K" << color_text(32, "] 100% ") + color_text(32, finishedMessage) << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(input / 2));
}

/*  random_int - This function generates a random integer value for a given range
*   Input:
*       lowerBound - Constant integer value that represents the lower bound of the random integer
*       upperBound - Constant integer value that represents the upper bound fo the random integer
*   Algorithm:
*       * Generate a random number generator
*       * Create a uniform integer distribution with the desired range
*       * Generate a random integer in that desired range
*   Output:
*       ret - Integer value that represents a random integer value in a specified range
*/
int random_int(const int lowerBound, const int upperBound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(lowerBound, upperBound);
    int ret = dist(gen);
    return ret;
}

/*  round_input - This function rounds a float value to two digits to resemble a currency value
*   Input:
*       input - Float value that is to be rounded to a currency value
*   Algorithm:
*       * This function utilizes the built in "round" function to round a value to two digits
*   Output:
*       input - Float value that is returned after being rounded to a currency value
*/
float round_input(float input) {
    input = round(input * 100) / 100;
    return input;
}

/*  round_to_string - This function rounds a float value to two digits and returns it as a string
*   Input:
*       input - Constant float value that is fed into the function that is to be rounded
*   Algorithm:
*       * This function uses ostringstream to cast a float to a string and round it two decimal values
*   Output:
*       return_string - Rounded string value to resemble a currency value
*/
std::string round_to_string(const float input) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << input;
    std::string return_string = oss.str();
    return return_string;
}

/*  time_sleep - This function causes the console to sleep for a given amount of time
*   Input:
*       input - Constant long value that resembles the time in milliseconds to have the console sleep
*   Algorithm:
*       * This function utilizes the "sleep_for" built in function to cause the console to sleep
*   Output:
*       This function does not return a value
*/
void time_sleep(const long input) {
    std::this_thread::sleep_for(std::chrono::milliseconds(input));
}