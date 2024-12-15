import random
import sys

# Check if N is provided as a command line argument
if len(sys.argv) < 2:
    print("Please provide the value of N as a command line argument.")
    sys.exit(1)

# Get the value of N from the command line argument
N = int(sys.argv[1])

# Generate a list of 100 random values between 0 and N
random_values = [random.randint(0, N) for _ in range(100)]

# Print the list of random values
print("List of 100 random values between 0 and", N, ":")
print(random_values)