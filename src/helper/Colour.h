#ifndef COLOR_H
#define COLOR_H

class Colour {
public:
  Colour(double r, double g, double b);

  double getR() const;
  double getG() const;
  double getB() const;

  double abs() const;

  static Colour scalar2norm2rgb(double val, double min, double max);

  Colour &operator+=(const Colour &c);
  Colour &operator-=(const Colour &c);
  Colour &operator*=(double f);
  Colour &operator/=(double f);

protected:
  // Valid values for r_, g_, b_ are in range [0, 1]. However, not being in that range for computing intermediate results
  // is fine. When writing a PLY file back to disk, values above 1 will be set to 1 and values below 0 will be set to 0.
  // Note that color values in the PLY file are [0, 255] and conversion to/from [0, 1] is done automatically when reading/
  // writing PLY files.
  double r_;
  double g_;
  double b_;
};

Colour operator+(const Colour &c0, const Colour &c1);
Colour operator-(const Colour &c0, const Colour &c1);
Colour operator*(const Colour &c0, const Colour &c1);
Colour operator/(const Colour &c0, const Colour &c1);

Colour operator*(double f, const Colour &c);
Colour operator*(const Colour &c, double f);
Colour operator/(const Colour &c, double f);

#endif // COLOR_H
