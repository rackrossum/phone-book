#include "phone_book.h"
#include "contact.pb.h"
#include <algorithm>

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
    std::string s(prefix);
    ++s.back();
    
    return m_contacts.lower_bound(std::string_view(s));
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
        auto s_contact = res.add_contact();

        s_contact->set_name(contact.name);

        if (contact.birthday)
        {
            PhoneBookSerialize::Date s_bday;
            s_bday.set_year(contact.birthday->year);
            s_bday.set_month(contact.birthday->month);
            s_bday.set_day(contact.birthday->day);

            *s_contact->mutable_birthday() = s_bday;
        }

        for (const auto& phone : contact.phones)
            s_contact->add_phone_number(phone);
    }

    res.SerializeToOstream(&output);
}

PhoneBook DeserializePhoneBook(std::istream& input)
{

    PhoneBookSerialize::ContactList s_contacts;
    std::vector<Contact> contacts;
    contacts.reserve(s_contacts.contact_size());

    s_contacts.ParseFromIstream(&input);
    for (const auto& s_contact : s_contacts.contact())
    {
        Contact contact;

        contact.name = s_contact.name();

        if (s_contact.has_birthday())
        {
            Date d;
            d.year = s_contact.birthday().year();
            d.month = s_contact.birthday().month();
            d.day = s_contact.birthday().day();

            contact.birthday = d;
        }

        for (const auto& s_phone : s_contact.phone_number())
            contact.phones.push_back(s_phone);

        contacts.push_back(std::move(contact));
    }

    return PhoneBook(std::move(contacts));
}
