#ifndef MYMAP_INCLUDED
#define MYMAP_INCLUDED

#include <map>  // YOU MUST NOT USE THIS HEADER
#include <cassert>

// In accordance with the spec, YOU MUST RE-IMPLEMENT THIS CLASS, since
// you are not allowed to use any STL container other than queue.  The
// implementaions of getFirst and getNext VIOLATE THE SPEC, but at least
// can be used to help you test other classes in the project.

template <class KeyType, class ValueType>
class MyMap
{
public:

    MyMap()
    {
        m_curr = m_map.begin();
    }

    ~MyMap()
    {
    }

    void clear()
    {
        m_map.clear();
	m_curr = m_map.begin();
    }

    int size() const
    {
        return m_map.size();
    }

    void associate(const KeyType& key, const ValueType& value)
    {
        m_map[key] = value;
    }

    const ValueType* find(const KeyType& key) const
    {
        typename HelperMapType::const_iterator it = m_map.find(key);
        if (it == m_map.end())
            return NULL;
        else
            return &it->second;
    }

    ValueType* find(const KeyType& key)
    {
          // Do not change the implementation of this overload of find
        const MyMap<KeyType,ValueType>* constThis = this;
        return const_cast<ValueType*>(constThis->find(key));
    }

      // While this implementation of getFirst and getNext can be used to
      // visit every item in the MyMap object, it VIOLATES THE SPEC because
      // the items are NOT visited in level order. 
    ValueType* getFirst(KeyType& key)
    {
        m_curr = m_map.begin();
        if (m_curr == m_map.end())
            return NULL;

        key = m_curr->first;
        return &m_curr->second;
    }

    ValueType* getNext(KeyType& key)
    {
        assert(m_curr != m_map.end());
        m_curr++;
        if (m_curr == m_map.end())
            return NULL;

        key = m_curr->first;
        return &m_curr->second;
    }

private:
      // YOU ARE NOT ALLOWED TO USE AN STL MAP IN YOUR SOLUTION
    typedef std::map<KeyType,ValueType> HelperMapType;
    HelperMapType                    m_map;
    typename HelperMapType::iterator m_curr;
};

#endif // MYMAP_INCLUDED
