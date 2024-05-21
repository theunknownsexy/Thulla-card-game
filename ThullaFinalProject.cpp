#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <algorithm>

using namespace std;
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif
int thisRound = 0;
int specialRound;
string playingDeck[4];
string *playingdeck = playingDeck;
string gamearray[100];
bool thulla = false;
int roundnumber = 0;
int currentroundcounter = 0;
string suit;
string *thullaPtr;
void rearrangeCards(string *ptr)
{
    int index = 0;
    for (int i = 0; i <= 51; i++)
    {
        if ((*(ptr + i)) != "")
        {
            (*(ptr + index)) = (*(ptr + i));
            index++;
        }
    }
    (*(ptr + index)) = "";
}

int thisroundCards(string *ptr, string cardThrown)
{
    *(ptr + thisRound) = cardThrown;
    thisRound++;
    specialRound = thisRound; // for 4 card thulla adjustment so 4 is returned and not 0.
    if (thisRound == 4)
    {
        thisRound = 0;
    }
    return specialRound;
}

int countCards(string *ptr)
{
    int cardcounter = 0;
    for (int i = 0; i <= 51; i++)
    {
        if ((*(ptr + i)) != "")
        {
            cardcounter++;
        }
    }
    return cardcounter;
}

void thullad(string *playingdeckPtr)
{
    int cardcounter = countCards(thullaPtr);
    int cardstoAdd = specialRound;

    // Copy all cards from playingdeck to thullaPtr
    for (int i = 0; i < cardstoAdd; i++)
    {
        *(thullaPtr + cardcounter + i) = *(playingdeckPtr + i);
    }
}

string findSuit(const string &input_str)
{
    string lowercaseInput = input_str;
    transform(lowercaseInput.begin(), lowercaseInput.end(), lowercaseInput.begin(), ::tolower);

    if (lowercaseInput.find("spades") != string::npos)
    {
        return "spades";
    }
    else if (lowercaseInput.find("hearts") != string::npos)
    {
        return "hearts";
    }
    else if (lowercaseInput.find("clubs") != string::npos)
    {
        return "clubs";
    }
    else if (lowercaseInput.find("diamonds") != string::npos)
    {
        return "diamonds";
    }
    else
    {
        return ""; // Return an empty string if none of the suits are found
    }
}

bool correctCard(string *ptr, const string &substring, int cardnumber)
{
    string card = *(ptr + cardnumber);
    size_t found = card.find(substring);

    if (found != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isSuitPresent(string *ptr, const string &subString)
{
    for (int i = 0; i < 13; ++i)
    {
        size_t found = (ptr + i)->find(subString); // Use -> to access elements through the pointer

        if (found != string::npos)
        {
            return true; // If the substring is found in any element, return true
        }
    }

    return false; // If the substring is not found in any element, return false
}

int cardMagnitude(string cardthrown)
{

    char firstchar = cardthrown[0];

    switch (firstchar)
    {
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case '1':
        return 10;
    case 'J':
        if (cardthrown[1] == 'a')
        {
            return 11;
        }
        else
        {
            return 0;
        }
    case 'Q':
        return 12;
    case 'K':
        return 13;
    case 'A':
        return 14;
    default:
        cout << "Debug: Default case, unexpected input." << endl;
        return 0; // Default case to handle unexpected input
    }

    return 0;
}

string playinggame(string *pointer)
{
    string thullastring = "thulla";
    string cardthrown;
    int cardnumber;
    int gamearrayindex = 0;
    string currentcard;

    while (true)
    {
        cout << "Choose The Number of The Card That You Want To Throw (1-" << countCards(pointer) << "): ";
        cin >> cardnumber;

        // Adjusting the cardnumber to be 0-based
        cardnumber--;

        if (roundnumber == 0 || roundnumber == 1 || roundnumber == 2 || roundnumber == 3)
        {
            if (isSuitPresent(pointer, "spades"))
            {
                if (correctCard(pointer, "spades", cardnumber))
                {
                    currentcard = *(pointer + cardnumber);
                    cout << "You Have Played The Following Card: " << currentcard << endl;
                    gamearray[gamearrayindex] = *(pointer + cardnumber);
                    *(pointer + cardnumber) = "";
                    gamearrayindex++;
                    roundnumber++;
                    rearrangeCards(pointer);
                    return currentcard;
                }
                else
                {
                    cout << "Please throw a spades card since you have one, don't try to cheat!!" << endl;
                }
            }
            else
            {
                currentcard = *(pointer + cardnumber);
                cout << "You Have Played The Following Card: " << currentcard << endl;
                gamearray[gamearrayindex] = *(pointer + cardnumber);
                *(pointer + cardnumber) = "";
                gamearrayindex++;
                roundnumber++;
                rearrangeCards(pointer);
                return currentcard;
            }
        }
        else
        {
            if (currentroundcounter == 0)
            {
                currentcard = *(pointer + cardnumber);
                thisroundCards(playingDeck, currentcard);
                cout << "You Have Played The Following Card: " << currentcard << endl;
                suit = findSuit(currentcard);
                gamearray[gamearrayindex] = *(pointer + cardnumber);
                *(pointer + cardnumber) = "";
                gamearrayindex++;
                currentroundcounter++;
                rearrangeCards(pointer);
                return currentcard;
            }
            else
            {
                if (isSuitPresent(pointer, suit))
                {
                    if (correctCard(pointer, suit, cardnumber))
                    {
                        currentcard = *(pointer + cardnumber);
                        thisroundCards(playingDeck, currentcard);
                        cout << "You Have Played The Following Card: " << currentcard << endl;
                        gamearray[gamearrayindex] = *(pointer + cardnumber);
                        *(pointer + cardnumber) = "";
                        gamearrayindex++;
                        currentroundcounter++;
                        if (currentroundcounter == 4)
                        {

                            currentroundcounter = 0;
                        }
                        rearrangeCards(pointer);
                        return currentcard;
                    }
                    else
                    {
                        cout << "Please throw a " << suit << " card since you have one, don't try to cheat!!" << endl;
                    }
                }
                // thulla starts here
                else
                {
                    currentcard = *(pointer + cardnumber);
                    thisroundCards(playingDeck, currentcard);
                    cout << "You Have Played The Following Card: " << currentcard << endl;
                    gamearray[gamearrayindex] = *(pointer + cardnumber);
                    *(pointer + cardnumber) = "";
                    gamearrayindex++;
                    currentroundcounter = 0;
                    rearrangeCards(pointer);
                    return thullastring;
                }
            }
        }
    }
}

int main()
{
    int startingplayer;
    int thisplayer;
    int arraySize = 53;
    string cards[53];
    string playerOne[52];
    string playerTwo[52];
    string playerThree[52];
    string playerFour[52];
    string *pointerplayerone = playerOne;
    string *pointerplayertwo = playerTwo;
    string *pointerplayerthree = playerThree;
    string *pointerplayerfour = playerFour;
    string playerone;
    string playertwo;
    string playerthree;
    string playerfour;
    int playernum;
    int highestcardMag = 0;
    int cardMag;
    string cardThrown;
    string highestCard;
    int highestplayer;
    // rules and initial menu
    cout << "\033[1;34m"; // Set text color to blue
    cout << "                                         _____________________" << endl;
    cout << "                                        |                     |" << endl;
    cout << "                                        | \033[1;37mWELCOME TO THULLA !\033[1;34m |" << endl;
    cout << "                                        |_____________________|" << endl;
    cout << "\033[0m"; // Reset text color
    cout << endl;
    cout << endl;

    cout << "\033[1;31m"; // Set text color to red
    cout << "                                                RULES:" << endl;
    cout << "\033[0m";    // Reset text color
    cout << "\033[1;37m"; // Set text color to white for rules
    cout << "1) Thulla is a 4-player game.\n";
    cout << "2) In the first round, players throw a spades card.\n";
    cout << "3) The one with the highest suit starts the second round.\n";
    cout << "4) From the second round onwards, follow the suit of the winner.\n";
    cout << "5) If someone lacks the suit, they can 'thulla' the player with\n"
            "   the highest card in that round (don't cheat, you will be caught).\n";
    cout << "6) If everyone has the suit, the player with the highest card\n"
            "   starts the next round, and the playing deck is flushed.\033[0m";

    cout << endl;
    cout << endl;

    cout << "\033[1;33m"; // Set text color to yellow
    cout << "                             DON'T CHEAT OR THE THULLA WILL CATCH YOU GOOD LUCK! ";
    cout << "\033[0m"; // Reset text color
    cout << endl;
    cout << "Please enter your name Player 1:" << endl;
    cin >> playerone;
    cout << "Please enter your name Player 2:" << endl;
    cin >> playertwo;
    cout << "Please enter your name Player 3:" << endl;
    cin >> playerthree;
    cout << "Please enter your name Player 4:" << endl;
    cin >> playerfour;
    for (int hearts = 2; hearts <= 10; hearts++) // insert hearts
    {
        cards[hearts] = to_string(hearts) + " of hearts";
    }
    for (int diamonds = 12; diamonds <= 20; diamonds++) // insert diamonds
    {
        cards[diamonds] = to_string(diamonds - 10) + " of diamonds";
    }
    for (int spades = 22; spades <= 30; spades++) // insert spades
    {
        cards[spades] = to_string(spades - 20) + " of spades";
    }
    for (int clubs = 32; clubs <= 40; clubs++) // insert clubs
    {
        cards[clubs] = to_string(clubs - 30) + " of clubs";
    }
    /*for(int i=0;i<52;i++) CHECKING FOR THE CARDS
    {
        cout<<cards[i]<<endl;
    }*/
    cards[0] = "Joker";
    cards[1] = "Jack of hearts";
    cards[11] = "Jack of diamonds";
    cards[21] = "Jack of spades";
    cards[31] = "Jack of clubs";
    cards[41] = "Kings of hearts";
    cards[42] = "Kings of diamonds";
    cards[43] = "Kings of spades";
    cards[44] = "Kings of clubs";
    cards[45] = "Queens of hearts";
    cards[46] = "Queens of diamonds";
    cards[47] = "Queens of spades";
    cards[48] = "Queens of clubs";
    cards[49] = "Ace of hearts";
    cards[50] = "Ace of diamonds";
    cards[51] = "Ace of spades";
    cards[52] = "Ace of clubs";

    /*for(int i =0; i<=52; i++)
    {
        cout<<cards[i]<<endl;
    }*/

    int random_numbers[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
        random_numbers[i] = i;
    }

    srand(static_cast<unsigned int>(time(0)));

    // Printing 52 unique random numbers
    for (int i = 0; i <= 52; i++)
    {
        int randomIndex = rand() % arraySize;
        // cout << random_numbers[randomIndex] << endl;

        // Swap the selected element with the last element and reduce the array size
        arraySize--;
        swap(random_numbers[randomIndex], random_numbers[arraySize]);
    }

    for (int i = 0; i <= 12; i++)
    {
        playerOne[i] = cards[random_numbers[i]];
    }
    for (int i = 0; i <= 12; i++) // Start from 0 instead of 13
    {
        playerTwo[i] = cards[random_numbers[i + 13]]; // Adjust the index
    }
    for (int i = 0; i <= 12; i++) // Start from 0 instead of 26
    {
        playerThree[i] = cards[random_numbers[i + 26]]; // Adjust the index
    }
    for (int i = 0; i <= 12; i++) // Start from 0 instead of 39
    {
        playerFour[i] = cards[random_numbers[i + 39]]; // Adjust the index
    }
    // SHOWING USER HIS CARDS;
    // AND FIRST ROUND
    for (int count = 0; count <= 3; count++)
    {
        cout << "PLEASE ENTER YOUR PLAYER NUMBER (1,2,3 OR 4):" << endl;
        cin >> playernum;
        if (playernum == 1)
        {
            cout << "CARDS FOR " << playerone << " :" << endl;
            for (int i = 0; i < countCards(pointerplayerone); i++)
            {
                cout << i + 1 << ")" << playerOne[i] << endl;
            }

            cardThrown = playinggame(pointerplayerone);
            cardMag = cardMagnitude(cardThrown);
            if (cardMag > highestcardMag)
            {
                highestcardMag = cardMag;
                highestCard = cardThrown;
                highestplayer = 1;
            }
            system(CLEAR_SCREEN);
            cout << "The highest card till now is: " << highestCard;
            cout << endl;
            cout << endl;
            cout << endl;
        }

        else if (playernum == 2)
        {
            cout << "CARDS FOR " << playertwo << " :" << endl;
            for (int i = 0; i < countCards(pointerplayertwo); i++)
            {
                cout << i + 1 << ")" << playerTwo[i] << endl;
            }

            cardThrown = playinggame(pointerplayertwo);
            cardMag = cardMagnitude(cardThrown);
            if (cardMag > highestcardMag)
            {
                highestcardMag = cardMag;
                highestCard = cardThrown;
                highestplayer = 2;
            }
            system(CLEAR_SCREEN);
            cout << "The highest card till now is: " << highestCard;

            cout << endl;
            cout << endl;
            cout << endl;
        }

        else if (playernum == 3)
        {
            cout << "CARDS FOR " << playerthree << " " << endl;
            for (int i = 0; i < countCards(pointerplayerthree); i++)
            {
                cout << i + 1 << ")" << playerThree[i] << endl;
            }

            cardThrown = playinggame(pointerplayerthree);
            cardMag = cardMagnitude(cardThrown);
            if (cardMag > highestcardMag)
            {
                highestcardMag = cardMag;
                highestCard = cardThrown;
                highestplayer = 3;
            }
            system(CLEAR_SCREEN);
            cout << "The highest card till now is: " << highestCard;

            cout << endl;
            cout << endl;
            cout << endl;
        }
        else if (playernum == 4)
        {
            cout << "CARDS FOR " << playerfour << " :" << endl;
            for (int i = 0; i < countCards(pointerplayerfour); i++)
            {
                cout << i + 1 << ")" << playerFour[i] << endl;
            }

            cardThrown = playinggame(pointerplayerfour);
            cardMag = cardMagnitude(cardThrown);
            if (cardMag > highestcardMag)
            {
                highestcardMag = cardMag;
                highestCard = cardThrown;
                highestplayer = 4;
            }
            system(CLEAR_SCREEN);
            cout << "The highest card till now is: " << highestCard;

            cout << endl;
            cout << endl;
            cout << endl;
        }

        /*
        cout<<gamearray[0]<<endl;

        for(int i=0;i<=12;i++)
        {
            cout<<playerOne[i]<<endl;
        }
        */
    }

    int counter;

    while (thulla == false)
    {
        fill(begin(playingDeck), end(playingDeck), "");
        thisRound = 0;
        counter = 0;
        thisplayer = highestplayer;
        startingplayer = thisplayer;

        if (cardThrown != "thulla")
        {
            if (thisplayer == 1)
            {
                cout << "Since " << playerone << " had the highest card in the last round, they will go first" << endl;
            }
            else if (thisplayer == 2)
            {
                cout << "Since " << playertwo << " had the highest card in the last round, they will go first" << endl;
            }
            else if (thisplayer == 3)
            {
                cout << "Since " << playerthree << " had the highest card in the last round, they will go first" << endl;
            }
            else
            {
                cout << "Since " << playerfour << " had the highest card in the last round, they will go first" << endl;
            }
        }

        highestcardMag = 0;

        do
        {
            if (thisplayer == 1)
            {
                cout << "CARDS FOR " << playerone << " :" << endl;
                for (int i = 0; i < countCards(pointerplayerone); i++)
                {
                    cout << i + 1 << ")" << playerOne[i] << endl;
                }

                cardThrown = playinggame(pointerplayerone);
                system(CLEAR_SCREEN);
                if (countCards(pointerplayerone) == 0)
                {
                    cout << "Congragulations " << playerone << " you have won the game !" << endl;
                    return 0;
                }
                if (cardThrown == "thulla")
                {
                    if (highestplayer == 1)
                    {
                        cout << playerone << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else if (highestplayer == 2)
                    {
                        cout << playertwo << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else if (highestplayer == 3)
                    {
                        cout << playerthree << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else
                    {
                        cout << playerfour << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                }
                else
                {
                    cardMag = cardMagnitude(cardThrown);
                    if (cardMag > highestcardMag)
                    {
                        highestcardMag = cardMag;
                        highestCard = cardThrown;
                        highestplayer = 1;
                        thullaPtr = pointerplayerone;
                    }
                    cout << "The highest card till now is: " << highestCard << endl;
                    thisplayer = (thisplayer % 4) + 1;

                    cout << "The cards played till now in this round are: ";

                    for (int i = 0; i <= counter; i++)
                    {
                        cout << playingDeck[i] << endl;
                    }
                    counter++;
                }

                cout << endl;
                cout << endl;
                cout << endl;
            }

            else if (thisplayer == 2)
            {
                cout << "CARDS FOR " << playertwo << " :" << endl;
                for (int i = 0; i < countCards(pointerplayertwo); i++)
                {
                    cout << i + 1 << ")" << playerTwo[i] << endl;
                }

                cardThrown = playinggame(pointerplayertwo);
                system(CLEAR_SCREEN);
                if (countCards(pointerplayertwo) == 0)
                {
                    cout << "Congragulations " << playertwo << " , you have won the game !" << endl;
                    return 0;
                }
                if (cardThrown == "thulla")
                {
                    if (highestplayer == 1)
                    {
                        cout << playerone << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else if (highestplayer == 2)
                    {
                        cout << playertwo << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else if (highestplayer == 3)
                    {
                        cout << playerthree << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else
                    {
                        cout << playerfour << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                }
                else
                {
                    cardMag = cardMagnitude(cardThrown);
                    if (cardMag > highestcardMag)
                    {
                        highestcardMag = cardMag;
                        highestCard = cardThrown;
                        highestplayer = 2;
                        thullaPtr = pointerplayertwo;
                    }
                    cout << "The highest card till now is: " << highestCard << endl;
                    thisplayer = (thisplayer % 4) + 1;

                    cout << "The cards played till now in this round are: ";

                    for (int i = 0; i <= counter; i++)
                    {
                        cout << playingDeck[i] << endl;
                    }
                    counter++;
                }

                cout << endl;
                cout << endl;
                cout << endl;
            }

            else if (thisplayer == 3)
            {
                cout << "CARDS FOR " << playerthree << " :" << endl;
                for (int i = 0; i < countCards(pointerplayerthree); i++)
                {
                    cout << i + 1 << ")" << playerThree[i] << endl;
                }

                cardThrown = playinggame(pointerplayerthree);
                system(CLEAR_SCREEN);
                if (countCards(pointerplayerthree) == 0)
                {
                    cout << "Congragulations " << playerthree << " , you have won the game !" << endl;
                    return 0;
                }
                if (cardThrown == "thulla")
                {
                    if (highestplayer == 1)
                    {
                        cout << playerone << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else if (highestplayer == 2)
                    {
                        cout << playertwo << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else if (highestplayer == 3)
                    {
                        cout << playerthree << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else
                    {
                        cout << playerfour << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                }
                else
                {
                    cardMag = cardMagnitude(cardThrown);
                    if (cardMag > highestcardMag)
                    {
                        highestcardMag = cardMag;
                        highestCard = cardThrown;
                        highestplayer = 3;
                        thullaPtr = pointerplayerthree;
                    }
                    cout << "The highest card till now is: " << highestCard << endl;
                    thisplayer = (thisplayer % 4) + 1;

                    cout << "The cards played till now in this round are: ";

                    for (int i = 0; i <= counter; i++)
                    {
                        cout << playingDeck[i] << endl;
                    }
                    counter++;
                }

                cout << endl;
                cout << endl;
                cout << endl;
            }
            else if (thisplayer == 4)
            {
                cout << "CARDS FOR " << playerfour << " :" << endl;
                for (int i = 0; i < countCards(pointerplayerfour); i++)
                {
                    cout << i + 1 << ")" << playerFour[i] << endl;
                }

                cardThrown = playinggame(pointerplayerfour);
                system(CLEAR_SCREEN);
                if (countCards(pointerplayerfour) == 0)
                {
                    cout << "Congragulations " << playerfour << " you have won the game !" << endl;
                    return 0;
                }
                if (cardThrown == "thulla")
                {
                    if (highestplayer == 1)
                    {
                        cout << playerone << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else if (highestplayer == 2)
                    {
                        cout << playertwo << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else if (highestplayer == 3)
                    {
                        cout << playerthree << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                    else
                    {
                        cout << playerfour << " has been thulla'd!! Since they were thulla'd, they will go first this round" << endl;
                        thullad(playingDeck);
                    }
                }
                else
                {
                    cardMag = cardMagnitude(cardThrown);
                    if (cardMag > highestcardMag)
                    {
                        highestcardMag = cardMag;
                        highestCard = cardThrown;
                        highestplayer = 4;
                        thullaPtr = pointerplayerfour;
                    }
                    cout << "The highest card till now is: " << highestCard << endl;
                    thisplayer = (thisplayer % 4) + 1;

                    cout << "The cards played till now in this round are: ";

                    for (int i = 0; i <= counter; i++)
                    {
                        cout << playingDeck[i] << endl;
                    }
                    counter++;
                }

                cout << endl;
                cout << endl;
                cout << endl;
            }
        } while (thisplayer != startingplayer && cardThrown != "thulla");
    }
}