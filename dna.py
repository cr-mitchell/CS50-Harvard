# dna.py
# by: Charles Mitchell
# In this homework assignment, we were asked to create a program that
# identifies to whom a sequence of DNA belongs using a database csv file
# and a sequence txt file. They are included in the CS50-Harvard respository

import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    data_base = sys.argv[1]
    sequence_file = sys.argv[2]

    # Read database file into a variable
    with open(data_base, "r") as data:
        file_reader = csv.reader(data)
        data_list = list(file_reader)

    # Read DNA sequence file into a variable
    with open(sequence_file, "r") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    counter = []

    for i in range(1, len(data_list[0])):
        counter.append(longest_match(sequence, data_list[0][i]))

    # Check database for matching profiles
    note = "No Match"
    note_count = 0

    for i in range(1, len(data_list)):
        for j in range(len(counter)):
            if counter[j] == int(data_list[i][j + 1]):
                note_count += 1

        if note_count == len(counter):
            note = data_list[i][0]
            break
        else:
            note_count = 0

    print(note)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
