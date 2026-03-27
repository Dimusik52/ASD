// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#include <string>
#include "polynom.h"

size_t Polynom::size() const { // Возвращать поле _size;
  size_t count = 0;
  auto it = polynom.begin();
  while (it != polynom.end()) {
    ++count;
    ++it;
  }
  return count;
}

Polynom::Polynom() {}

Polynom::Polynom(const Polynom& other) { polynom = other.polynom; }
Polynom::Polynom(std::string expression) { *this = parse(expression); }

Polynom& Polynom::operator=(const Polynom& other) {
  if (this != &other) {
    polynom = other.polynom;
  }
  return *this;
}

Polynom Polynom::operator+(const Monom& other) {
  Polynom res = *this;
  res.addMonomSorted(other);
  return res;
}

Polynom Polynom::operator-(const Monom& other) {
  Polynom res = *this;
  Monom neg = -other;
  //neg.setCoefficient(-neg.getCoefficient());
  res = res + neg;
  return res;
}

Polynom Polynom::operator*(const Monom& other) {
  Polynom res;
  for (auto it = begin(); it != end(); ++it) {
    Monom prod = *it * other;
    res.addMonomSorted(prod);
  }
  return res;
}

Polynom Polynom::operator+(const Polynom& other) {
  Polynom result = *this;

  for (auto it = other.begin(); it != other.end(); ++it) {
    result.addMonomSorted(*it);
  }

  return result;
}

Polynom Polynom::operator-(const Polynom& other) {
  Polynom result = *this;

  for (auto it = other.begin(); it != other.end(); ++it) {
    Monom negated = *it;
    negated.setCoefficient(-negated.getCoefficient());
    result.addMonomSorted(negated);
  }
  return result;
}
Polynom Polynom::operator*(const Polynom& other) {
  if (isEmpty() || other.isEmpty()) return Polynom();

  Polynom res;
  for (auto it1 = begin(); it1 != end(); ++it1) {
    for (auto it2 = other.begin(); it2 != other.end(); ++it2) {
      res.addMonomSorted((*it1) * (*it2));
    }
  }
  return res;
}

void Polynom::addMonomSorted(const Monom& m) {
  if (std::abs(m.getCoefficient()) < 1e-11) return;

  auto it = begin();
  size_t pos = 0;

  while (it != end() && !lexGreater(m, *it)) {
    if (it->powerCompare(m)) {
      Monom sum = *it + m;
      if (std::abs(sum.getCoefficient()) < 1e-11) {
        polynom.erase(pos);
      } else {
        *it = sum;
      }
      return;
    }
    ++it;
    pos++;
  }
  polynom.insert(pos, m);
}

bool Polynom::lexGreater(const Monom& a, const Monom& b) {
  if (a.getXPower() != b.getXPower()) return a.getXPower() > b.getXPower();
  if (a.getYPower() != b.getYPower()) return a.getYPower() > b.getYPower();
  return a.getZPower() > b.getZPower();
}

Polynom Polynom::parse(const std::string& s) {
  enum class State { Start, Coefficient, Variable, PowerStart, Power };

  Polynom result;
  State state = State::Start;

  double coef = 1.0;
  int powers[3] = {0, 0, 0};  // [0]=x, [1]=y, [2]=z
  int sign = 1;
  std::string buffer;
  char currentVar;

  auto getVarIndex = [](char c) {
    if (c == 'x') return 0;
    if (c == 'y') return 1;
    return 2;  // 'z'
  };

  auto flushTerm = [&]() {
    if (coef != 0.0) {
      result.addMonomSorted(Monom(sign * coef, powers[0], powers[1], powers[2]));
    }
    coef = 1.0;
    powers[0] = powers[1] = powers[2] = 0;
    sign = 1;
  };

  for (size_t i = 0; i <= s.size(); ++i) {
    char c = (i < s.size()) ? s[i] : '\0';
    if (c == ' ') continue;

    switch (state) {
      case State::Start:
        if (c == '+' || c == '-') {
          if (i != 0) flushTerm();
          sign = (c == '+') ? 1 : -1;
        } else if (isdigit(c) || c == '.') {
          buffer = c;
          state = State::Coefficient;
        } else if (c == 'x' || c == 'y' || c == 'z') {
          currentVar = c;
          state = State::Variable;
        } else if (c == '\0') {
          flushTerm();
        } else
          throw std::invalid_argument("Unexpected character");
        break;

      case State::Coefficient:
        if (isdigit(c) || c == '.') {
          if (c == '.') {
            if (std::count(buffer.begin(), buffer.end(), '.') >= 1) {
              throw std::invalid_argument("Multiple dots in number");
            }
          }
          buffer += c;
        }
        else {
          coef = std::stod(buffer);
          buffer.clear();
          state = State::Start;
          --i;
        }
        break;

      case State::Variable:
        if (c == '^')
          state = State::PowerStart;
        else {
          powers[getVarIndex(currentVar)] = 1;
          state = State::Start;
          --i;
        }
        break;

      case State::PowerStart:
        if (!isdigit(c)) throw std::invalid_argument("Expected digit after ^");
        buffer = c;
        state = State::Power;
        break;

      case State::Power:
        if (isdigit(c))
          buffer += c;
        else {
          powers[getVarIndex(currentVar)] = std::stoi(buffer);
          buffer.clear();
          state = State::Start;
          --i;
        }
        break;
    }
  }
  return result;
}

std::ostream& operator<<(std::ostream& ostr, const Polynom& p) {
  if (p.isEmpty()) {
    ostr << "0";
    return ostr;
  }

  auto it = p.begin();

  if (it->getCoefficient() < 0) {
    ostr << "-";
  }
  ostr << Monom(std::abs(it->getCoefficient()), it->getXPower(),
                it->getYPower(), it->getZPower());

  ++it;
  for (; it != p.end(); ++it) {
    double coef = it->getCoefficient();
    if (coef > 0) {
      ostr << " + ";
    } else {
      ostr << " - ";
    }
    ostr << Monom(std::abs(coef), it->getXPower(), it->getYPower(),
                  it->getZPower());
  }
  return ostr;
}