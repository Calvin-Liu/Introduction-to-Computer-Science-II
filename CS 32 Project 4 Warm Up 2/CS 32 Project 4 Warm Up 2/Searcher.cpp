#include "provided.h"
#include <string>
#include "MyMap.h"
using namespace std;

bool comparingFunction(UrlCount current, UrlCount adjacent)
{
    if(current.url > adjacent.url)
    {
        return true; 
    }
    else
        return false;
}

bool comparingintFunction(UrlCount current, UrlCount adjacent)
{
    if(current.count > current.count)
    {
        return true;
    }
    else
        return false;
}





class SearcherImpl
{
public:
    vector<string> search(string terms);
    bool load(string filenameBase);
private:
    Indexer index;
};

vector<string> SearcherImpl::search(string terms)
{
    Tokenizer termsParsed(terms);
    string word;
    int numberOfWords = 0;
    vector<string> orderedVector;
    vector<UrlCount> bigVector;
    MyMap<string,bool> seenWords;
    vector<UrlCount> orderbyscore;
    
    while(termsParsed.getNextToken(word))
    {
        strToLower(word);
        if(!seenWords.find(word))
        {
            seenWords.associate(word, true);
            numberOfWords++;
            int k = 0;
            vector<UrlCount> temp = index.getUrlCounts(word);
            for(temp[k]; k < temp.size(); k++)
            {
                bigVector.push_back(temp[k]);
            }
        }
    }
        
    sort(bigVector.begin(), bigVector.end(), comparingFunction); //now sorted and next to each other
    UrlCount current_url = bigVector[0];
    int start = 0;
    int T = int(0.7 * numberOfWords);
    if(T < 1)
    {
        T = 1;
    }
    
    int length;
    for(int j = 1; j < bigVector.size(); j++)
    {
        if(bigVector[j].url != current_url.url)
        {
            orderbyscore.push_back(current_url);
        }
    }
    
    sort(orderbyscore.begin(), orderbyscore.end(), comparingintFunction);
    
    int anotherstart = 0;
    for(int i = 1; i < bigVector.size(); i++)
    {
        length = i-anotherstart;
        if(length >= T)
        {
            orderedVector.push_back(current_url.url);
        }
        start = i;
        current_url = bigVector[i];
    }
    
    
    
    //combine all the vectors for each word
    //sort that by score
    //get rid of the repeats
    //push that into your string vector, each one
    //return the string vector
    
    return orderedVector;
    
    
    return vector<string>(); //This compiles, but may not be correct
}

bool SearcherImpl::load(string filenameBase)
{
    if(index.load(filenameBase))
    {
        return true;
    }
    else
        return false;  // This compiles, but may not be correct
}

//******************** Searcher functions *******************************

// These functions simply delegate to SearcherImpl's functions.
// You probably don't want to change any of this code.

Searcher::Searcher()
{
    m_impl = new SearcherImpl;
}

Searcher::~Searcher()
{
    delete m_impl;
}

vector<string> Searcher::search(string terms)
{
    return m_impl->search(terms);
}

bool Searcher::load(string filenameBase)
{
    return m_impl->load(filenameBase);
}
