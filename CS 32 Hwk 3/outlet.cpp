//
//  main.cpp
//  CS 32 Hwk 3
//
//  Created by Calvin Liu on 2/6/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

enum CallType {
    VOICE, TEXT
};


class Outlet //Absract Class
{
public:
    Outlet(string typeofdevice);
    virtual ~Outlet();
    string connect() const;     
    virtual string id() const = 0;
    virtual string transmit(string msg) const = 0;
private:
    string m_typeofdevice;
};

Outlet::Outlet(string typeofdevice)
{
    m_typeofdevice = typeofdevice;
}

Outlet::~Outlet()
{
}

string Outlet::connect() const
{
    return m_typeofdevice;
}



class TwitterAccount : public Outlet
{
public:
    TwitterAccount(string username);
    virtual ~TwitterAccount();
    virtual string id() const;
    virtual string transmit(string msg) const;
private:
    string m_twitter;
};

TwitterAccount::TwitterAccount(string twittername)
:Outlet("Tweet"), m_twitter(twittername)
{}

TwitterAccount::~TwitterAccount()
{
    cout << "Destroying the Twitter account " << m_twitter << '.' << endl;
}

string TwitterAccount::id() const
{
    return m_twitter;
}

string TwitterAccount::transmit(string msg) const
{
    string messagetype = "text: ";
    messagetype += msg;
    return messagetype;
}



class Phone : public Outlet
{
public:
    Phone(string numbers, CallType x);
    virtual ~Phone();
    virtual string id() const;
    virtual string transmit(string msg) const;
private:
    string m_phonenumber;
    CallType m_calltype;
};

Phone::Phone(string numbers, CallType x)
:Outlet("Call"), m_phonenumber(numbers), m_calltype(x)
{}

Phone::~Phone()
{
    cout << "Destroying the phone " << m_phonenumber << '.' << endl;
}

string Phone::id() const
{
    return m_phonenumber;
}

string Phone::transmit(string msg) const
{
    string phonevoice = "voice: ";
    string phonetext = "text: ";
    if(m_calltype == VOICE)
    {
        phonevoice += msg;
        return phonevoice;
    }
    
    else if(m_calltype == TEXT)
    {
        phonetext += msg;
        return phonetext;
    }
    return "ERROR";
}



class EmailAccount : public Outlet
{
public:
    EmailAccount(string email);
    virtual ~EmailAccount();
    virtual string id() const;
    virtual string transmit(string msg) const;
private:
    string m_emailname;
};

EmailAccount::EmailAccount(string email)
:Outlet("Email"), m_emailname(email)
{}

EmailAccount::~EmailAccount()
{
    cout << "Destroying the email account " << m_emailname << '.' << endl;
}

string EmailAccount::id() const
{
    return m_emailname;
}

string EmailAccount::transmit(string msg) const
{
    string emailtype = "text: ";
    emailtype += msg;
    return emailtype;
}


















//void send(const Outlet* out, string msg)
//{
//    cout << out->connect() << " using id " << out->id()
//    << ", sending " << out->transmit(msg) << endl;
//}
//
//int main()
//{
//    Outlet* outlets[4];
//    outlets[0] = new TwitterAccount("UCLAnotice");
//    // Phone users may prefer messages to be left as voice or text.
//    outlets[1] = new Phone("(310) 825 1776", VOICE);
//    outlets[2] = new Phone("(213) 389 9060", TEXT);
//    outlets[3] = new EmailAccount("jbroon@ucla.edu");
//    
//    cout << "Send the message." << endl;
//    for (int k = 0; k < 4; k++)
//        send(outlets[k], "Major power outage in West L.A.");
//    
//    // Clean up the outlets before exiting
//    cout << "Cleaning up." << endl;
//    for (int k = 0; k < 4; k++)
//        delete outlets[k];
//}

//Send the message.
//Tweet using id UCLAnotice, sending text: Major power outage in West L.A.
//Call using id (310) 825 1776, sending voice: Major power outage in West L.A.
//Call using id (213) 389 9060, sending text: Major power outage in West L.A.
//Email using id jbroon@ucla.edu, sending text: Major power outage in West L.A.
//Cleaning up.
//Destroying the Twitter account UCLAnotice.
//Destroying the phone (310) 825 1776.
//Destroying the phone (213) 389 9060.
//Destroying the email account jbroon@ucla.edu.