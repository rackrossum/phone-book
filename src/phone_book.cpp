#include "phone_book.h"
#include "contact.pb.h"

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

void PhoneBook::SaveTo(std::ostream& output) const
{
    PhoneBookSerialize::ContactList res;

    for (const auto& contact : m_contacts)
    {
        PhoneBookSerialize::Contact s_contact;

        s_contact.set_name(contact.name);

        if (contact.birthday)
        {
            PhoneBookSerialize::Date s_bday;
            s_bday.set_year(contact.birthday->year);
            s_bday.set_month(contact.birthday->month);
            s_bday.set_day(contact.birthday->day);

            s_contact.set_allocated_date(&s_bday);
        }

        for (const auto& phone : contact.phones)
            s_contact.add_phones(phone);

        auto s_contacts = res.mutable_contacts();
        s_contacts->AddAllocated(&s_contact);
    }

    res.SerializeToOstream(&output);
}
