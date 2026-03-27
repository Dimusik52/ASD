// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#include "monom.h"

Monom::Monom(double _coefficent, int x, int y, int z) {
  factor.coefficient = _coefficent;
  factor.powers[0] = x;
  factor.powers[1] = y;
  factor.powers[2] = z;
}
Monom::Monom(double _coefficent, int fr_power, int sc_power, char val1,
             char val2)
    : factor{_coefficent, {0, 0, 0}} {
  factor.coefficient = _coefficent;
  if (val1 == val2) throw std::invalid_argument("Identical variables");

  if (val1 == 'x')
    factor.powers[0] = fr_power;
  else if (val1 == 'y')
    factor.powers[1] = fr_power;
  else if (val1 == 'z')
    factor.powers[2] = fr_power;
  else
    throw std::invalid_argument("Invalid variable");

  if (val2 == 'x')
    factor.powers[0] = sc_power;
  else if (val2 == 'y')
    factor.powers[1] = sc_power;
  else if (val2 == 'z')
    factor.powers[2] = sc_power;
  else
    throw std::invalid_argument("Invalid variable");
}
Monom::Monom(double _coefficent, int power, char val)
    : factor{_coefficent, {0, 0, 0}} {
  factor.coefficient = _coefficent;
  if (val == 'x')
    factor.powers[0] = power;
  else if (val == 'y')
    factor.powers[1] = power;
  else if (val == 'z')
    factor.powers[2] = power;
  else
    throw std::invalid_argument("Invalid variable");
}
Monom::Monom(double _coefficent) : factor{_coefficent, {0, 0, 0}} {}
Monom::Monom() {
  factor.coefficient = 0.0;
  for (int i = 0; i < MONOM; i++) {
    factor.powers[i] = 0;
  }
}
Monom::Monom(const Monom& other) : factor(other.factor) {}

bool Monom::operator==(const Monom& other) const { return powerCompare(other); }
bool Monom::operator!=(const Monom& other) const { return !(*this == other); }
Monom Monom::operator*(const Monom& other) const {
  Monom m = *this;
  m *= other;
  return m;
}

Monom Monom::operator/(const Monom& other) const {
  double denom = other.getCoefficient();
  if (std::abs(denom) < 1e-11) {
    throw std::invalid_argument("Division by zero");
  }
  Monom m = *this;
  m /= other;
  return m;
}

Monom Monom::operator+(const Monom& other) const {
  if (!powerCompare(other)) {
    throw std::invalid_argument("You cannot add dissimilar monomials");
  }
  Monom m = *this;
  m += other;
  return m;
}

Monom Monom::operator-(const Monom& other) const {
  if (!powerCompare(other)) {
    throw std::invalid_argument("You cannot add dissimilar monomials");
  }
  Monom m = *this;
  m -= other;
  return m;
}

Monom Monom::operator-() const {
  return Monom(-factor.coefficient, factor.powers[0], factor.powers[1],
               factor.powers[2]);
}
Monom& Monom::operator=(const Monom& other) {
  if (this != &other) {
    factor = other.factor;
  }
  return *this;
}

Monom& Monom::operator*=(const Monom& other) {
  setCoefficient(getCoefficient() * other.getCoefficient());
  setXPower(getXPower() + other.getXPower());
  setYPower(getYPower() + other.getYPower());
  setZPower(getZPower() + other.getZPower());
  return *this;
}
Monom& Monom::operator-=(const Monom& other) {
  setCoefficient(getCoefficient() - other.getCoefficient());
  return *this;
}
Monom& Monom::operator+=(const Monom& other) {
  setCoefficient(getCoefficient() + other.getCoefficient());
  return *this;
}
Monom& Monom::operator/=(const Monom& other) {
  setCoefficient(getCoefficient() / other.getCoefficient());
  setXPower(getXPower() - other.getXPower());
  setYPower(getYPower() - other.getYPower());
  setZPower(getZPower() - other.getZPower());
  return *this;
}

double Monom::solve(double _x, double _y, double _z) {
  return factor.coefficient * pow(_x, getXPower()) * pow(_y, getYPower()) *
         pow(_z, getZPower());
}
bool Monom::powerCompare(const Monom& other) const {
  return factor.powers[0] == other.factor.powers[0] &&
         factor.powers[1] == other.factor.powers[1] &&
         factor.powers[2] == other.factor.powers[2];
}

double pow(double x, int power) {
  if (power < 0) {
    if (std::abs(x) < 1e-11) {
      throw std::invalid_argument("Division by zero");
    }
    return 1.0 / pow(x, -power);
  }

  double result = 1.0;
  double base = x;
  int p = power;

  while (p > 0) {
    if (p % 2 == 1) {
      result *= base;
    }
    base *= base;
    p /= 2;
  }
  return result;
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
  if (m.getCoefficient() == 0) return os;

  os << m.getCoefficient();
  if (m.getXPower() != 0) {
    os << "x";
    if (m.getXPower() != 1) os << "^" << m.getXPower();
  }
  if (m.getYPower() != 0) {
    os << "y";
    if (m.getYPower() != 1) os << "^" << m.getYPower();
  }
  if (m.getZPower() != 0) {
    os << "z";
    if (m.getZPower() != 1) os << "^" << m.getZPower();
  }
  return os;
}
std::istream& operator>>(std::istream& is, Monom& m) {
  double c;
  int ix, iy, iz;
  is >> c >> ix >> iy >> iz;
  if (is) {
    m = Monom(c, ix, iy, iz);
  }
  return is;
}