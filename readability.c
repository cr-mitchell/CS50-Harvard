// readability.c
// by: Charles Mitchell

/* In this homework assignment, we were asked to create a program that calculates the 
Coleman-Liau index readbility score of a given text using the Coleman-Liau formula of 
index = 0.0588 * L - 0.296 * S - 15.8, where is L is average number of letters and S
is average number of sentences */

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
int calculate(int num_letters, int num_words, int num_sentences);

int main(void)
{
    string text = get_string("Text: ");

    //gets return values from all of the functions and then passes them into the calculate function below the three
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    int level = calculate(letters, words, sentences);

    if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }
}

//this function counts the number of letters in the inputted string by looping through it, checking if it is a letter, and tallying it ad returning the total tally
int count_letters(string s)
{
    int counter = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //function in ctype that checks if a character is a letter
        if (isalpha(s[i]))
        {
            counter++;
        }
    }

    return counter;
}


//this function counts the number of words in the inputted string by looping through it, checking if after the word there is a space, and tallying it ad returning the total tally
int count_words(string s)
{
    int counter = 1;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ')
        {
            counter++;
        }
    }

    return counter;
}

//this function counts the number of sentences in the inputted string by looping through it, checking if the sentence ends with a . or ! or ?, and tallying it ad returning the total tally
int count_sentences(string s)
{
    int counter = 0;

    for (int i = 0, n = strlen(s); i < n; i ++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            counter++;
        }
    }

    return counter;
}

//this function calculates the Coleman-Laiu index, readability score, and rounds that number to the nearest integer and returns that integer
int calculate(int num_letters, int num_words, int num_sentences)
{
    //turns the common divider into a floating point number so no decimals are left out during the calculations
    float dec_words = num_words * 1.0;

    float avg_letters = (num_letters / dec_words * 100);
    float avg_sentences = (num_sentences / dec_words * 100);

    //Coleman-Laiu's index readability score formula
    float index = (0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8;

    return round(index);
}
