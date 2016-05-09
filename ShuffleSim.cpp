// ShuffleSim.cpp
// Matt Grant 9 May 2016
// Simulates
#include <vector>
using std::vector;
#include <iostream>
#include <cstdlib>
using std::abs;
#include <algorithm>
using std::reverse;

#include "Node.h"

vector<Node*> genDeck(size_t size);
vector<Node*> riffle(vector<Node*> deck);
vector<Node*> pile(size_t piles, vector<Node*> deck);
size_t disorder(vector<Node*> deck);
double localDisorder(vector<Node*> deck);
int find(int target, vector<Node*> deck);
void printDeck(vector<Node*>& deck);

const int PILE = 10;
const int RIFFLE = 13;

int main() {
    vector<Node*> deck = genDeck(60);
    vector<Node*> deckReverse = deck;
    vector<Node*> deckRiffle = deck;
    vector<Node*> deckPile = deck;
    vector<Node*> sevenDeckPile = deck;
    ////This is used for quick demonstrations. It only calculates disorder after the entire shuffling 
    ////process is finished
    ////Control
    //std::cout << "Control" << std::endl;
    //printDeck(deck);
    //std::cout << "Disorder: " << disorder(deck) << std::endl;
    //std::cout << "Average local Disorder" << localDisorder(deck) << std::endl << std::endl;

    ////Reverse
    //std::cout << "Control" << std::endl;
    //reverse(deckReverse.begin(), deckReverse.end());
    //printDeck(deckReverse);
    //std::cout << "Disorder: " << disorder(deckReverse) << std::endl;
    //std::cout << "Average local Disorder" << localDisorder(deckReverse) << std::endl << std::endl;

    ////7 Pile Shuffle
    //std::cout << "7 Pile Shuffle" << std::endl;
    //deckPile = pile(7,deckPile);
    //printDeck(deckPile);
    //std::cout << "Disorder: " << disorder(deckPile) << std::endl;
    //std::cout << "Average local Disorder" << localDisorder(deckPile) << std::endl << std::endl;

    //
    ////x 7 Pile Shuffle
    //std::cout << "x 7 Pile Shuffle" << std::endl;
    //for (int i = 0; i < PILE; ++i) {
    //    sevenDeckPile = pile(7, sevenDeckPile);
    //}
    //printDeck(sevenDeckPile);
    //std::cout << "Disorder: " << disorder(sevenDeckPile) << std::endl;
    //std::cout << "Average local Disorder" << localDisorder(sevenDeckPile) << std::endl << std::endl;
    //
    ////Riffle once
    //std::cout << "Single Riffle Shuffle" << std::endl;
    //deck = riffle(deck);
    //printDeck(deck);
    //std::cout << "Disorder: " << disorder(deck) << std::endl;
    //std::cout << "Average local Disorder" << localDisorder(deck) << std::endl << std::endl;

    ////X Riffle Shuffle
    //std::cout << "7 Riffle Shuffle" << std::endl;
    //for (int i = 0; i < RIFFLE; ++i) {
    //    deckRiffle = riffle(deckRiffle);
    //}
    //printDeck(deckRiffle);
    //std::cout << "Disorder: " << disorder(deckRiffle) << std::endl;
    //std::cout << "Average local Disorder" << localDisorder(deckRiffle) << std::endl << std::endl;
   

    ////This is used to lots of data at once. Records disorder after every shuffle
    ////x 7 Pile Shuffle
    //std::cout << "x 7 Pile Shuffle" << std::endl;
    //for (int i = 0; i < 30; ++i) {
    //    sevenDeckPile = pile(7, sevenDeckPile);
    //    std::cout << "(" << i + 1 << ")" << "Disorder: " << disorder(sevenDeckPile);
    //    std::cout << " Average local Disorder" << localDisorder(sevenDeckPile) << std::endl;
    //}
    //printDeck(sevenDeckPile);


    //X Riffle Shuffle
    std::cout << "7 Riffle Shuffle" << std::endl;
    for (int i = 0; i < 15; ++i) {
        deckRiffle = riffle(deckRiffle);
        std::cout << "(" << i + 1 << ")" << "Disorder: " << disorder(deckRiffle);
        std::cout << " Average local Disorder" << localDisorder(deckRiffle) << std::endl;
    }
    printDeck(deckRiffle);

}

vector<Node*> genDeck(size_t size) {
    vector<Node*> toReturn;
    for (size_t i = 0; i < size; ++i) {
        toReturn.push_back(new Node(i));
    }
    return toReturn;
}

vector<Node*> riffle(vector<Node*> lhs) {
    vector<Node*> toReturn;
    vector<Node*> rhs;
    for (size_t i = (lhs.size()/2); i < lhs.size(); ++i) {
        rhs.push_back(lhs[i]);
    }
    lhs.resize(lhs.size() / 2);
    size_t bound = lhs.size() + rhs.size();
    for (size_t i = 0; i < bound; ++i) {
        if(i % 2 == 0){
            toReturn.push_back(lhs.front());
            lhs.erase(lhs.begin());
        }
        else {
            toReturn.push_back(rhs.front());
            rhs.erase(rhs.begin());
        }
    }
    return toReturn;
}

vector<Node*> pile(size_t numPiles, vector<Node*> deck) {
    vector<Node*> toReturn;
    vector< vector<Node*> > piles;
    for (size_t i = 0; i < numPiles; ++i) {
        vector<Node*> temp;
        piles.push_back(temp);
    }
    for (size_t i = 0; i < deck.size(); ++i) {
        piles[i % numPiles].push_back(deck[i]);
    }
    for (auto &i : piles) {
        for (auto &j : i) {
            toReturn.push_back(j);
        }
    }
    return toReturn;
}

size_t disorder(vector<Node*> deck) {
    size_t toReturn = 0;
    for (int i = 0; i < deck.size(); ++i) {
        toReturn += abs(i - deck[i]->id());
    }
    return toReturn;
}

double localDisorder(vector<Node*> deck) {
    double toReturn = 0;
    for (int i = 0; i < deck.size(); ++i) {
        int upper = find(deck[i]->id() + 1, deck);
        int lower = find(deck[i]->id() - 1, deck);
        if (upper != -1) {
            toReturn += abs(upper - i) - 1;
        }
        if( lower != -1){
            toReturn += abs(lower - i) - 1;
        }
    }
    toReturn /= deck.size();
    return toReturn;
}

//Returns -1 if not found
int find(int target, vector<Node*> deck) {
    for (size_t i = 0; i < deck.size(); ++i) {
        if(deck[i]->id() == target){
            return i;
        }
    }
    return -1;
}

void printDeck(vector<Node*>& deck) {
    std::cout << "{ ";
    for(auto &i: deck){
        std::cout << i->id() << " ";
    }
    std::cout << " }" << std::endl;
}