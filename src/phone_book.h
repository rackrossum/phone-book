#pragma once

#include "iterator_range.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <iosfwd>
#include <set>

struct Date {
  int year, month, day;
};

struct Contact {
  std::string name;
  std::optional<Date> birthday;
  std::vector<std::string> phones;
};

struct ContactByName
{
    std::string name;
    std::vector<Contact>::const_iterator it;
};

bool operator < (const ContactByName& lhs, const ContactByName& rhs);

class PhoneBook {
public:
  explicit PhoneBook(std::vector<Contact> contacts);

  IteratorRange<???> FindByNamePrefix(std::string_view name_prefix) const;

  void SaveTo(std::ostream& output) const;

private:

private:
    std::vector<Contact> m_contacts;
    std::set<ContactByName> m_sortedContacts;
};

PhoneBook DeserializePhoneBook(std::istream& input);

