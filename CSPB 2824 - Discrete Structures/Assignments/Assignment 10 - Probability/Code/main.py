# BirthdayProblem - Calculates the number of days required for 2 people to having the same birthday at a desired probability
# Input:
#   numPeople - Number of people in data set
#   desiredProbability - Desired probability of two people sharing the same birthday
# Algorithm:
#   * Set the break condition to 1
#   * Set the number of days to be the number of people on the planet
#   * Perform the following calculation until the probability is less than or equal to the desired
#       * Increment the number of days
#       * Calculate the probability of everyone having a different birthday for a set number of days
#       * Calculate the probability of two people having the same birthday
#   * Return the number of days
# Output:
#   days - Number of days required for two people amongst numPeople to have a desiredProbability chance of sharing the same birthday
def BirthdayProblem(numPeople, desiredProbability):
    # Break condition probability
    sameProb = 1
    # Number of days
    days = numPeople
    # Repeat until sameProb <= desiredProbability
    while (sameProb > desiredProbability):
        # Increment the number of days
        days += 1
        # Set the different birthday prob to one
        diffProb = 1
        # Calculate the different birthday probability
        for i in range(1, numPeople + 1):
            iPeopleProb = ((days + 1) - i) / days
            diffProb *= iPeopleProb
        # Calculate the same birthday probability
        sameProb = round(1 - diffProb, 3)
    # Return number of days
    return days

print(f"The number of days on this planet is: {BirthdayProblem(33, 0.50)} days.")