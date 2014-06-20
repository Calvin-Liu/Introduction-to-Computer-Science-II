#include "provided.h"
#include <string>
#include "http.h"
#include <queue>
using namespace std;

class WebCrawlerImpl
{
public:
    void addUrl(string url);
    int getNumberOfUrls() const;
    void crawl(void (*callback)(string url, bool success));
    bool save(string filenameBase);
    bool load(string filenameBase);
private:
    queue<string> m_urlStorage;
    Indexer m_index;
};

void WebCrawlerImpl::addUrl(string url)
{
    m_urlStorage.push(url);
}

int WebCrawlerImpl::getNumberOfUrls() const
{
    return m_urlStorage.size();
}

void WebCrawlerImpl::crawl(void (*callback)(string url, bool success))
{
    while(!m_urlStorage.empty())
    {
        string page;
        string url = m_urlStorage.front();
        bool ifItWorked = HTTP().get(url, page);
        m_urlStorage.pop();
        if(ifItWorked)
        {
            WordBag urlBag(page);
            ifItWorked = m_index.incorporate(url, urlBag);
            callback(url, ifItWorked);
        }
    }
}

bool WebCrawlerImpl::save(string filenameBase)
{
    if(m_index.save(filenameBase))
        return true;  // This compiles, but may not be correct
    else
        return false;
}

bool WebCrawlerImpl::load(string filenameBase)
{
    if(m_index.load(filenameBase))
        return true;  // This compiles, but may not be correct
    else
        return false;
}

//******************** WebCrawler functions *******************************

// These functions simply delegate to WebCrawlerImpl's functions.
// You probably don't want to change any of this code.

WebCrawler::WebCrawler()
{
    m_impl = new WebCrawlerImpl;
}

WebCrawler::~WebCrawler()
{
    delete m_impl;
}

void WebCrawler::addUrl(string url)
{
    m_impl->addUrl(url);
}

int WebCrawler::getNumberOfUrls() const
{
    return m_impl->getNumberOfUrls();
}

void WebCrawler::crawl(void (*callback)(string url, bool success))
{
    m_impl->crawl(callback);
}

bool WebCrawler::save(string filenameBase)
{
    return m_impl->save(filenameBase);
}

bool WebCrawler::load(string filenameBase)
{
    return m_impl->load(filenameBase);
}


