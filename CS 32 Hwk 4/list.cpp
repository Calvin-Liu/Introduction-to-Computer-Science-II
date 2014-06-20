//
//  File.cpp
//  CS 32 Hwk 4
//
//  Created by Calvin Liu on 3/3/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//
 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MenuItem
{
public:
    MenuItem(string nm) : m_name(nm) {}
    virtual ~MenuItem() {}
    string name() const { return m_name; }
    virtual bool add(MenuItem* m) = 0;
    virtual const vector<MenuItem*>* menuItems() const = 0;
private:
    string m_name;
};

class PlainMenuItem : public MenuItem   // PlainMenuItem allows no submenus
{
public:
    PlainMenuItem(string nm) : MenuItem(nm) {}
    virtual bool add(MenuItem* m) { return false; }
    virtual const vector<MenuItem*>* menuItems() const { return NULL; }
};

class CompoundMenuItem : public MenuItem  // CompoundMenuItem allows submenus
{
public:
    CompoundMenuItem(string nm) : MenuItem(nm) {}
    virtual ~CompoundMenuItem();
    virtual bool add(MenuItem* m) { m_menuItems.push_back(m); return true; }
    virtual const vector<MenuItem*>* menuItems() const { return &m_menuItems; }
private:
    vector<MenuItem*> m_menuItems;
};

CompoundMenuItem::~CompoundMenuItem()
{
    for (int k = 0; k < m_menuItems.size(); k++)
        delete m_menuItems[k];
}

void listAllAuxiliary(string path, const MenuItem* m) 
{
    if(m->menuItems() == NULL)
        return;
    if(m != NULL)
    {
        if(m->menuItems() != NULL)
        {
            for(vector<MenuItem*>::const_iterator it = m->menuItems()->begin(); it != m->menuItems()->end(); it++)
            {
                if(path == "")
                {
                    string s = path + (*it)->name();
                    cout << s << endl;
                    listAllAuxiliary(s, *it);
                }
                else
                {
                    string s = path + '/' + (*it)->name();
                    cout << s << endl;
                    listAllAuxiliary(s, *it);
                }
            }
        }
    }
}

void listAll(const MenuItem* m)
{
    if (m != NULL)
        listAllAuxiliary("", m);
}

int main()
{
    CompoundMenuItem* cm0 = new CompoundMenuItem("New");    //cm0 = new pointer to Compound
    cm0->add(new PlainMenuItem("Window"));  //vector[0] is now PlainMenuItem window
    CompoundMenuItem* cm1 = new CompoundMenuItem("File"); //cm1 = new pointer to Compound
    cm1->add(cm0); //vector[1] is now CompoundMenuItem New
    cm1->add(new PlainMenuItem("Open")); //vector[2] is now PlainMenu open
    cm1->add(new PlainMenuItem("Exit")); //vector[3] is now PlainMenu exit
    CompoundMenuItem* cm2 = new CompoundMenuItem("Help"); //cm2 = new pointer to Compound
    cm2->add(new PlainMenuItem("Index")); //vector[4] is now index
    cm2->add(new PlainMenuItem("About")); //vector[5] is now about
    CompoundMenuItem* cm3 = new CompoundMenuItem("");  // main menu bar //cm3 = new pointer to Compound
    cm3->add(cm1); //vector[6] is now file
    cm3->add(new PlainMenuItem("Refresh"));  // no submenu  //vector[7] is now refresh
    cm3->add(new CompoundMenuItem("Under Development")); // no submenus yet
    cm3->add(cm2);
    listAll(cm3);
    delete cm3;
}

//File
//File/New
//File/New/Window
//File/Open
//File/Exit
//Refresh
//Under Development
//Help
//Help/Index
//Help/About

 