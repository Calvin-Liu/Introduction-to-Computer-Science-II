#ifndef PROVIDED_INCLUDED
#define PROVIDED_INCLUDED

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

class WordBagImpl;

class WordBag
{
public:
    WordBag(const std::string& text);
    ~WordBag();
    bool getFirstWord(std::string& word, int& count);
    bool getNextWord(std::string& word, int& count);
private:
    WordBagImpl* m_impl;
      // We prevent a WordBag object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    WordBag(const WordBag&);
    WordBag& operator=(const WordBag&);
};

struct UrlCount
{
    std::string url;
    int count;
};

class IndexerImpl;

class Indexer
{
public:
    Indexer();
    ~Indexer();
    bool incorporate(std::string url, WordBag& wb);
    std::vector<UrlCount> getUrlCounts(std::string word);
    bool save(std::string filenameBase);
    bool load(std::string filenameBase);
private:
    IndexerImpl* m_impl;
      // We prevent an Indexer object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    Indexer(const Indexer&);
    Indexer& operator=(const Indexer&);
};

class WebCrawlerImpl;

class WebCrawler
{
public:
    WebCrawler();
    ~WebCrawler();
    void addUrl(std::string url);
    int getNumberOfUrls() const;
    void crawl(void (*callback)(std::string url, bool success));
    bool save(std::string filenameBase);
    bool load(std::string filenameBase);
private:
    WebCrawlerImpl* m_impl;
      // We prevent a WebCrawler object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    WebCrawler(const WebCrawler&);
    WebCrawler& operator=(const WebCrawler&);
};

class SearcherImpl;

class Searcher
{
public:
    Searcher();
    ~Searcher();
    std::vector<std::string> search(std::string terms);
    bool load(std::string filenameBase);
private:
    SearcherImpl* m_impl;
      // We prevent a Searcher object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    Searcher(const Searcher&);
    Searcher& operator=(const Searcher&);
};

  // Helper functions for strToLower and Tokenizer

inline char toLower(char c)  // needed to work around overload issue
{
    return std::tolower(c);
}

inline bool isAlnum(char c)
{
    return std::isalnum(static_cast<unsigned char>(c));
}

inline bool isNotAlnum(char c)
{
    return !isAlnum(c);
}

  // strToLower - Change all upper case letters in s to lower case

inline void strToLower(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(), toLower);
}

  // Tokenizer

class Tokenizer
{
public:
    Tokenizer(const std::string& text)
     : m_text(text)
    {
        m_nextChar = m_text.begin();
    }

    bool getNextToken(std::string& token)
    {
          // find start of next token
	std::string::const_iterator start = std::find_if(m_nextChar, m_text.end(), isAlnum);
	if (start == m_text.end())
	{
	    m_nextChar = m_text.end();
	    token.clear();
	    return false;
	}

          // find end of next token
	m_nextChar = std::find_if(start+1, m_text.end(), isNotAlnum);
	token.assign(start, m_nextChar);
	return true;
    }

private:
    const std::string           m_text;
    std::string::const_iterator m_nextChar;
};

#endif // PROVIDED_INCLUDED
