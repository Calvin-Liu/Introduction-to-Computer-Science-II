#include "provided.h"
#include <string>
using namespace std;

class WordBagImpl
{
public:
    WordBagImpl(const string& text);
    bool getFirstWord(string& word, int& count);
    bool getNextWord(string& word, int& count);
};

WordBagImpl::WordBagImpl(const string& text)
{
}

bool WordBagImpl::getFirstWord(string& word, int& count)
{
    return false;  // This compiles, but may not be correct
}

bool WordBagImpl::getNextWord(string& word, int& count)
{
    return false;  // This compiles, but may not be correct
}

//******************** WordBag functions *******************************

// These functions simply delegate to WordBagImpl's functions.
// You probably don't want to change any of this code.

WordBag::WordBag(const std::string& text)
{
    m_impl = new WordBagImpl(text);
}

WordBag::~WordBag()
{
    delete m_impl;
}

bool WordBag::getFirstWord(string& word, int& count)
{
    return m_impl->getFirstWord(word, count);
}

bool WordBag::getNextWord(string& word, int& count)
{
    return m_impl->getNextWord(word, count);
}
