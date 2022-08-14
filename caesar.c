// caeser.c
// by: Charles Mitchell

/* In this homework assignment, we were asked to create a program that that enables you to encrypt messages using Caesar’s cipher
A simpler terms, the user provides us with a number on the command line and then gives us a string. The letters in that string are
then shifted down the alphabet the number of times what ever number they gave us on the command line. If the shift is at the end
of the alphabet, then the program keeps counting starting at the beginning of the alphabet*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char rotate(char c, int d);

//upper and lowercase alphabet arrays used to index with rotations
char upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, string argv[])
{
    //cancels the program if there aren't 2 arguments on the command line
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //loops through the second argument on the command line to check if it is a numerical value. if not program terminates
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isdigit(argv[1][i]))
        {
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int shift = atoi(argv[1]);

    string message = get_string("plaintext:  ");
    int n = strlen(message);

    printf("ciphertext:  ");

    //loops through the original message and shifts the characters. prints them out as well
    for (int i = 0; i < n; i++)
    {
        char print = rotate(message[i], shift);
        printf("%c", print);
    }

    printf("\n");
}

char rotate(char c, int d)
{
    int value;

    //takes a character and turns it into its place in the alphabet and shifts it according to the users choice. this is for lowercase.
    if (islower(c))
    {
        value = c - 'a';

        //the %26 takes the remainder if value + d is over 26 so that it wraps around and starts from the beginning of the alphabet.
        return lower[(value + d) % 26];
    }

    //takes a character and turns it into its place in the alphabet and shifts it according to the users choice. this is for uppercase.
    else if (isupper(c))
    {
        value = c - 'A';

        //the %26 takes the remainder if value + d is over 26 so that it wraps around and starts from the beginning of the alphabet.
        return upper[(value + d) % 26];
    }

    //returns the character if it is a letter of any kind
    else
    {
        return c;
    }
}
