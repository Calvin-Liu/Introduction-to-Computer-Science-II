#include "provided.h"
#include <string>
#include "MyMap.h"
using namespace std;

class WordBagImpl
{
public:
    WordBagImpl(const string& text);
    bool getFirstWord(string& word, int& count);
    bool getNextWord(string& word, int& count);
private:
    MyMap<string, int> m_Map;
};

WordBagImpl::WordBagImpl(const string& text)
{
    Tokenizer t(text);
    string word;
    
    while(t.getNextToken(word))
    {
        strToLower(word);
        int* ptr = m_Map.find(word);
        if(ptr != NULL)
            m_Map.associate(word, ++(*ptr));
        else
            m_Map.associate(word, 1);
    }
}

bool WordBagImpl::getFirstWord(string& word, int& count)
{
    int* ptr = m_Map.getFirst(word);
    if(ptr != NULL)
    {
        count = *ptr;
        return true;
    }
    else
        return false;
}

bool WordBagImpl::getNextWord(string& word, int& count)
{
    int* ptr = m_Map.getNext(word);
    if(ptr != NULL)
    {
        count = *ptr;
        return true;
    }
    return false;
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
