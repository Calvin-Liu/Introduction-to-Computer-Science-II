#include <iostream>
#include "provided.h"
#include <string>
#include "MyMap.h"
using namespace std;

void writeWordInfo(Indexer& indexer, string word)
{
    vector<UrlCount> urlCounts = indexer.getUrlCounts(word);
    if (urlCounts.empty()) {
        cout << word << " was not found in the index." << endl;
        return; }
    for (int i = 0; i < urlCounts.size(); i++)
        cout << word << " appears " << urlCounts[i].count << " times at " << urlCounts[i].url << endl;
}


bool testIndexer()
{
    const string INDEX_PREFIX = "index";
    Indexer indexer;
    WordBag wb1("<html>i like gogiberries and I hate spam</html>");
    indexer.incorporate("www.a.com", wb1);
    writeWordInfo(indexer, "I");
    // writes i appears 2 times at www.a.com
    // save the index as file(s) whose names start with prefix
    if ( ! indexer.save(INDEX_PREFIX))
        return false; // error saving the index
    // load the just-saved index into another Indexer
    Indexer indexer2;
    if ( ! indexer2.load(INDEX_PREFIX))
        return false; // error loading the index
    // add more pages to the second index
    WordBag wb2("<html>engineering is FUN</html>");
    indexer2.incorporate("www.b.com", wb2);
    WordBag wb3("<html>Engineering majors like fun</html>");
    indexer2.incorporate("www.c.com", wb3);
    writeWordInfo(indexer2, "like"); // writes in some order:
    // like appears 1 times at www.a.com
    // like appears 1 times at www.c.com
    writeWordInfo(indexer2, "smallberg");
    // writes smallberg was not found in the index
    return true;
}


void reportStatus(string url, bool success)
{
    if (success)
        cout << "Downloaded and indexed the page at " << url << endl;
    else
        cout << "Unable to download the page at " << url << endl;
}

bool testWebCrawler()
{
    const string INDEX_PREFIX = "index"; WebCrawler wc;
    // load a previously-saved index from
    if ( ! wc.load(INDEX_PREFIX)) // error
    return false;
    // specify which URLs we are to crawl
    wc.addUrl("www.youtube.com");
    wc.addUrl("www.nytimes.com");
    wc.addUrl("www.mangahere.com");
    wc.addUrl("www.ucla.edu");
    wc.addUrl("http://www.symantec.com/enterprise");
    // download the specified URLs and add their contents to the
    // index, designating reportStatus as the callback function
    wc.crawl(reportStatus);
    // save the updated index to disk
    if ( ! wc.save(INDEX_PREFIX)) // error saving
        return false;
    return true;// no errors
}

int main()
{
    testWebCrawler();
}