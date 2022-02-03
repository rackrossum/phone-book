#include "phone_book.h"

PhoneBook::PhoneBook(std::vector<Contact> contacts)
    : m_contacts(contacts.begin(), contacts.end())
{
}

bool operator < (const Contact& lhs, const Contact& rhs)
{
   return lhs.name < rhs.name; 
}
