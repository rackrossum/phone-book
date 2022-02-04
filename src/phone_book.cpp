#include "phone_book.h"

PhoneBook::PhoneBook(std::vector<Contact> contacts)
    : m_contacts(contacts.begin(), contacts.end())
{
}

bool operator < (const Contact& lhs, const Contact& rhs)
{
   return lhs.name < rhs.name; 
}

bool operator < (const std::string_view& lhs, const Contact& rhs)
{
    return lhs < rhs.name;
}

bool operator < (const Contact& lhs, const std::string_view& rhs)
{
    return lhs.name < rhs;
}

PhoneBook::Contacts::iterator PhoneBook::FindUpperBound(std::string_view prefix) const
{
    Contacts::iterator res = m_contacts.lower_bound(prefix);
    for (;res != m_contacts.end(); ++res)
    {
        if (std::string_view(res->name).compare(0, std::min(prefix.size(), res->name.size()), prefix) != 0)
            break;
    }

    return res;
}

IteratorRange<PhoneBook::Contacts::iterator> PhoneBook::FindByNamePrefix(std::string_view name_prefix) const
{
    if (name_prefix.empty())
        return {m_contacts.begin(), m_contacts.end()};

    return {m_contacts.lower_bound(name_prefix), FindUpperBound(name_prefix)};
}
