#include "Colour.h"
#include <cmath>

#define LOGMIN 0.1

Colour::Colour(double r, double g, double b) : r_(r), g_(g), b_(b) {}

double Colour::getR() const { return r_; }

double Colour::getG() const { return g_; }

double Colour::getB() const { return b_; }

double Colour::abs() const { return sqrt(r_ * r_ + g_ * g_ + b_ * b_); };

Colour Colour::scalar2norm2rgb(double val, double min, double max) {
  val = val < LOGMIN ? LOGMIN : val;
  min = min < LOGMIN ? LOGMIN : min;
  max = max < LOGMIN ? LOGMIN : max;
  double norm = (log(val) - log(min)) / (log(max) - log(min));
  return {norm, norm, norm};
}

Colour &Colour::operator+=(const Colour &c) {
  this->r_ += c.r_;
  this->g_ += c.g_;
  this->b_ += c.b_;
  return *this;
}

Colour &Colour::operator-=(const Colour &c) {
  this->r_ -= c.r_;
  this->g_ -= c.g_;
  this->b_ -= c.b_;
  return *this;
}

Colour &Colour::operator*=(double f) {
  this->r_ = this->r_ * f;
  this->g_ = this->g_ * f;
  this->b_ = this->b_ * f;
  return *this;
}

Colour &Colour::operator/=(double f) {
  this->r_ = this->r_ / f;
  this->g_ = this->g_ / f;
  this->b_ = this->b_ / f;
  return *this;
}

Colour operator+(const Colour &c0, const Colour &c1) {
  return {c0.getR() + c1.getR(), c0.getG() + c1.getG(), c0.getB() + c1.getB()};
}

Colour operator-(const Colour &c0, const Colour &c1) {
  return {c0.getR() - c1.getR(), c0.getG() - c1.getG(), c0.getB() - c1.getB()};
}

Colour operator*(const Colour &c0, const Colour &c1) {
  return {c0.getR() * c1.getR(), c0.getG() * c1.getG(), c0.getB() * c1.getB()};
}

Colour operator/(const Colour &c0, const Colour &c1) {
  return {c0.getR() / c1.getR(), c0.getG() / c1.getG(), c0.getB() / c1.getB()};
}

Colour operator*(double f, const Colour &c) {
  return {c.getR() * f, c.getG() * f, c.getB() * f};
}

Colour operator*(const Colour &c, double f) { return f * c; }

Colour operator/(const Colour &c, double f) {
  return {c.getR() / f, c.getG() / f, c.getB() / f};
}
