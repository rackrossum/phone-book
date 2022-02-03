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

bool operator < (const Contact& lhs, const Contact& rhs);

class PhoneBook {
public:
    using Contacts = std::set<Contact>;

public:
    explicit PhoneBook(std::vector<Contact> contacts);

    IteratorRange<Contacts> FindByNamePrefix(std::string_view name_prefix) const;

    void SaveTo(std::ostream& output) const;

private:
    Contacts m_contacts;
};

PhoneBook DeserializePhoneBook(std::istream& input);

