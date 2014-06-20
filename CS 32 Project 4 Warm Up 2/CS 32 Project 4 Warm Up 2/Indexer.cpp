#include "provided.h"
#include <string>
#include <vector>
#include "MyMap.h"
#include <iostream>
#include <fstream>
using namespace std;

 
bool readItem(istream& stream, string& s)
{
    if(!stream)
    {
        return false;
    }
    getline(stream,s);
    return true; 
}

bool readItem(istream& stream, int& i)
{
    if(!stream)
    {
        return false;
    }
    stream >> i; 
    stream.ignore(10000, '\n'); //don't need
    return true;
    
}

bool readItem(istream& stream, vector<UrlCount>& v)
{
    if(!stream)
    {
        return false;
    }
    
    UrlCount temp;
    vector<UrlCount>::const_iterator iter;
    for(iter = v.begin(); iter != v.end(); iter++)
    {
        stream >> temp.url;
        stream >> temp.count;
        v.push_back(temp);
    } //cerr to check
    return true;
}

 
template<typename KeyType, typename ValueType>
bool loadMyMap(string filename, MyMap<KeyType,ValueType>& m)
{
    m.clear();
    ifstream infile(filename);    // infile is a name of our choosing
    if (!infile )		        // Did opening the file fail?
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    
    int i;
    readItem(infile, i);
    for(int j = 0; j < i; j++)
    {
        KeyType key;
        ValueType k;
        readItem(infile, key);
        readItem(infile, k);
        m.associate(key, k);
    }
    return true;
}



void writeItem(ostream& stream, string s)
{
    stream << s << endl;
}

void writeItem(ostream& stream, int i) // for Chicken eggsLaidPerMonth
{
    stream << i << endl;
}

void writeItem(ostream& stream, const UrlCount& c) // for list elements
{
    writeItem(stream, c.url);
    writeItem(stream, c.count);
}

void writeItem(ostream& stream, const vector<UrlCount>& vec) // for map value
{
    for(vector<UrlCount>::const_iterator iter = vec.begin(); iter != vec.end(); iter++)
    {
        writeItem(stream, *iter);
    }
}


template<typename KeyType, typename ValueType>
bool saveMyMap(string filename, MyMap<KeyType,ValueType>& m)
{
    ofstream outfile(filename);
    if(!outfile)
    {
	    cerr << "Error: Cannot create results.txt!" << endl;
	    return false;
	}
    
    writeItem(outfile, m.size());
    KeyType key;
    
    for(ValueType* temp = m.getFirst(key); temp != NULL; temp = m.getNext(key))
    {
            writeItem(outfile, key);
            writeItem(outfile, *temp);
    }
    return true;
}




class IndexerImpl
{
public:
    bool incorporate(string url, WordBag& wb);
    vector<UrlCount> getUrlCounts(string word);
    bool save(string filenameBase);
    bool load(string filenameBase);
private:
    vector<UrlCount> m_urlCount;
    MyMap<string, int> m_urlToId;
    MyMap<int, string> m_idToUrl;
    MyMap<string, vector<UrlCount>> m_wordToIdCounts;
};

bool IndexerImpl::incorporate(string url, WordBag& wb)
{
    int randomID = rand();
    string word;
    
    if(m_urlToId.find(url) == NULL)
    {
        while(m_idToUrl.find(randomID) != NULL)
            randomID = rand();
        
        m_urlToId.associate(url, randomID);
        m_idToUrl.associate(randomID, url);
        
        int count;
        bool gotAWord = wb.getFirstWord(word, count);
        while(gotAWord)
        {
            vector<UrlCount> temp;
            UrlCount URL;
            URL.count = count;
            URL.url = url;
            temp.push_back(URL);
            vector<UrlCount>* urlcounts;
            if (!(urlcounts = m_wordToIdCounts.find(word)))
                m_wordToIdCounts.associate(word, temp);
            else
                urlcounts->push_back(URL);
            
            
            gotAWord = wb.getNextWord(word, count);
        }
        return true;
    }
    else
        return false;
}

vector<UrlCount> IndexerImpl::getUrlCounts(string word)
{
    strToLower(word);
    if(vector<UrlCount>* v = m_wordToIdCounts.find(word))
    {
        return *v;
    }
    else
        return vector<UrlCount>();
}

bool IndexerImpl::save(string filenameBase)
{
     return saveMyMap(filenameBase + ".u2i", m_urlToId) &&
     saveMyMap(filenameBase + ".i2u", m_idToUrl) &&
     saveMyMap(filenameBase + ".w2ic", m_wordToIdCounts);
}

bool IndexerImpl::load(string filenameBase)
{
    return loadMyMap(filenameBase + ".u2i", m_urlToId) && loadMyMap(filenameBase + ".i2u", m_idToUrl) && loadMyMap(filenameBase + ".w2ic", m_wordToIdCounts);
}












//******************** Indexer functions *******************************

// These functions simply delegate to IndexerImpl's functions.
// You probably don't want to change any of this code.

Indexer::Indexer()
{
    m_impl = new IndexerImpl;
}

Indexer::~Indexer()
{
    delete m_impl;
}

bool Indexer::incorporate(string url, WordBag& wb)
{
    return m_impl->incorporate(url, wb);
}

vector<UrlCount> Indexer::getUrlCounts(string word)
{
    return m_impl->getUrlCounts(word);
}

bool Indexer::save(string filenameBase)
{
    return m_impl->save(filenameBase);
}

bool Indexer::load(string filenameBase)
{
    return m_impl->load(filenameBase);
}






