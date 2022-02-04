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
bool operator < (const std::string_view& lhs, const Contact& rhs);
bool operator < (const Contact& lhs, const std::string_view& rhs);

class PhoneBook {
public:
    using Contacts = std::multiset<Contact, std::less<>>;

public:
    explicit PhoneBook(std::vector<Contact> contacts);

    IteratorRange<Contacts::iterator> FindByNamePrefix(std::string_view name_prefix) const;

    void SaveTo(std::ostream& output) const;

private:
    Contacts::iterator FindUpperBound(std::string_view prefix) const;

private:
    Contacts m_contacts;
};

PhoneBook DeserializePhoneBook(std::istream& input);

