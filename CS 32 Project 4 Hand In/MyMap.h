#ifndef MYMAP_INCLUDED
#define MYMAP_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <queue>

template <class KeyType, class ValueType>
class MyMap
{
public:
    MyMap()
    {
        m_root = NULL;
        m_mapItems = 0;
    }
    
    
    
    ~MyMap()
    {
        clear();
    }
    
    
    
    void clear()
    {
        clearNodes(m_root);
    }
    
    
    
    int size() const
    {
        return m_mapItems;
    }
    
    
    
    void associate(const KeyType& key, const ValueType& value)
    {
        if(m_root == NULL)
        {
            m_root = new Node;
            m_root->m_value = value;
            m_root->m_key = key;
            m_root->m_right = NULL;
            m_root->m_left = NULL;
            m_mapItems++;
        }
        else
        {
            addNode(m_root, key, value);
        }
    }
    
    
    
    const ValueType* find(const KeyType& key) const
    {
        Node* temp = findThatNode(m_root, key);
        if(temp != NULL)
            return &(temp->m_value);
        else
            return NULL;
    }
    
    
    
    ValueType* find(const KeyType& key)
    {
        // Do not change the implementation of this overload of find
        const MyMap<KeyType,ValueType>* constThis = this;
        return const_cast<ValueType*>(constThis->find(key));
    }
    
    
    
    ValueType* getFirst(KeyType& key)
    {
        if(m_root == NULL)
            return NULL;
        if(m_root != NULL)
        {
            mapQueue.push(m_root->m_left);
            mapQueue.push(m_root->m_right);
        }
        key = m_root->m_key;
        return &m_root->m_value;
    }
    
    
    
    ValueType* getNext(KeyType& key)
    {
        //must return items in level order, and run in constant time
        Node* temp = mapQueue.front();
        mapQueue.pop();
        if(temp != NULL)
        {
            mapQueue.push(temp->m_left);
            mapQueue.push(temp->m_right);
        }
        else if(temp == NULL)
        {
            while(!mapQueue.empty())
            {
                mapQueue.pop();
                temp = mapQueue.front();
                if(temp != NULL)
                    break;
            }
        }
        if(mapQueue.empty())
            return NULL;
        
        key = temp->m_key;
        return &(temp->m_value);
    }
private:
    struct Node
    {
        KeyType m_key;
        ValueType m_value;
        Node* m_left = NULL;
        Node* m_right = NULL;
    };
    
    
    
    
    void addNode(Node* p, const KeyType& key, const ValueType& value)
    {
        if(p != NULL)
        {
            if(p->m_key == key)
            {
                p->m_value = value;
                return;
            }
            
            Node* next;
            if(key < p->m_key)
            {
                next = p->m_left;
                if(p->m_left == NULL)
                {
                    p->m_left = new Node;
                    m_mapItems++;
                    p->m_left->m_value = value;
                    p->m_left->m_key = key;
                    p->m_left->m_left = NULL;
                    p->m_left->m_right = NULL;
                    return;
                }
            }
            else
            {
                next = p->m_right;
                if(p->m_right == NULL)
                {
                    p->m_right = new Node;
                    m_mapItems++;
                    p->m_right->m_value = value;
                    p->m_right->m_key = key;
                    p->m_right->m_left = NULL;
                    p->m_right->m_right = NULL;
                    return;
                }
            }
            addNode(next, key, value);
        }
    }
    
    
    
    
    void clearNodes(Node* p)
    {
        if(p == NULL)
            return;
        
        clearNodes(p->m_right);
        clearNodes(p->m_left);
        
        delete p;
    }
    
    
    
    Node* findThatNode(Node* p, const KeyType& key) const
    {
        if(p == NULL)
            return NULL;
        else if(p->m_key == key)
        {
            return p;
        }
        else if(key > p->m_key)
        {
            return findThatNode(p->m_right, key);
        }
        else if(key < p->m_key)
        {
            return findThatNode(p->m_left, key);
        }
        return NULL;
    }
    
    
    
    
    
    
    MyMap(const MyMap &other);
    MyMap &operator=(const MyMap &other);
    int m_mapItems;
    Node* m_root;
    // Add needed members
    
    std::queue<Node*> mapQueue;
};

#endif // MYMAP_INCLUDED
