#include "phone_book.h"

PhoneBook::PhoneBook(std::vector<Contact> contacts)
    : m_contacts(std::move(contacts))
{
    for (auto it = m_contacts.begin(); it != m_contacts.end(); ++it)
        m_sortedContacts.insert({it->name, it});
}

bool operator < (const ContactByName& lhs, const ContactByName& rhs)
{
   return lhs.name < rhs.name; 
}
