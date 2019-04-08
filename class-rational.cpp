#include <cmath>
#include <iostream>
#include <numeric>

class Rational {
private:
    int nu, de;
public:
    Rational(int x = 0, int y = 1) {
        if (x <= 0 && y < 0) {
            nu = abs(x) / std::gcd(x, y);
            de = abs(y) / std::gcd(x, y);
        } else if (x > 0 && y < 0) {
            nu = -x / std::gcd(x, y);
            de = abs(y) / std::gcd(x, y);
        } else {
            nu = x / std::gcd(x, y);
            de = y / std::gcd(x, y);
        }
    }

    int numerator() const {
        return nu;
    }

    int denominator() const {
        return de;
    }

    bool operator == (const Rational& z2) const {
        return nu == z2.nu && de == z2.de;
    }

    bool operator != (const Rational& z2) const {
        return nu != z2.nu || de != z2.de;
    }

    Rational& operator += (const Rational& z2) {
        int tmp_nu = nu * z2.denominator() + de * z2.numerator();
        int tmp_de = de * z2.denominator();
        int tmp_gcd = std::gcd(tmp_nu, tmp_de);
        nu = tmp_nu / tmp_gcd;
        de = tmp_de / tmp_gcd;
        return *this;
    }

    Rational& operator -= (const Rational& z2) {
        int tmp_nu = nu * z2.denominator() - de * z2.numerator();
        int tmp_de = de * z2.denominator();
        int tmp_gcd = std::gcd(tmp_nu, tmp_de);
        nu = tmp_nu / tmp_gcd;
        de = tmp_de / tmp_gcd;
        return *this;
    }

    Rational& operator *= (const Rational& z2) {
        int tmp_nu = nu * z2.numerator();
        int tmp_de = de * z2.denominator();
        int tmp_gcd = std::gcd(tmp_nu, tmp_de);
        nu = tmp_nu / tmp_gcd;
        de = tmp_de / tmp_gcd;
        return *this;
    }

    Rational& operator /= (const Rational& z2) {
        if (z2.numerator() != 0) {
            int tmp_nu = nu * z2.denominator();
            int tmp_de = de * z2.numerator();
            int tmp_gcd = std::gcd(tmp_nu, tmp_de);
            if (tmp_de < 0) {
                tmp_nu *= -1;
                tmp_de = abs(tmp_de);
            }
            nu = tmp_nu / tmp_gcd;
            de = tmp_de / tmp_gcd;
        }
        return *this;
    }

    Rational operator + () {
        return {nu, de};
    }

    Rational operator - () {
        return {-nu, de};
    }

    Rational& operator++ () {
        int tmp_nu = nu + de;
        int tmp_de = de;
        int tmp_gcd = std::gcd(tmp_nu, tmp_de);
        nu = tmp_nu / tmp_gcd;
        de = tmp_de / tmp_gcd;
        return *this;
    }

    Rational& operator-- () {
        int tmp_nu = nu - de;
        int tmp_de = de;
        int tmp_gcd = std::gcd(tmp_nu, tmp_de);
        nu = tmp_nu / tmp_gcd;
        de = tmp_de / tmp_gcd;
        return *this;
    }

    Rational operator++ (int) {
        Rational result(*this);
        ++(*this);
        return result;
    }

    Rational operator-- (int) {
        Rational result(*this);
        --(*this);
        return result;
    }
};

Rational operator + (const Rational& z1, const Rational& z2) {
    int tmp_nu = z1.numerator() * z2.denominator() + z1.denominator() * z2.numerator();
    int tmp_de = z1.denominator() * z2.denominator();
    int tmp_gcd = std::gcd(tmp_nu, tmp_de);
    return {tmp_nu / tmp_gcd, tmp_de / tmp_gcd};
}

Rational operator - (const Rational& z1, const Rational& z2) {
    int tmp_nu = z1.numerator() * z2.denominator() - z1.denominator() * z2.numerator();
    int tmp_de = z1.denominator() * z2.denominator();
    int tmp_gcd = std::gcd(tmp_nu, tmp_de);
    return {tmp_nu / tmp_gcd, tmp_de / tmp_gcd};
}

Rational operator * (const Rational& z1, const Rational& z2) {
    int tmp_nu = z1.numerator() * z2.numerator();
    int tmp_de = z1.denominator() * z2.denominator();
    int tmp_gcd = std::gcd(tmp_nu, tmp_de);
    return {tmp_nu / tmp_gcd, tmp_de / tmp_gcd};
}

Rational operator / (const Rational& z1, const Rational& z2) {
    if (z2.numerator() != 0) {
        int tmp_nu = z1.numerator() * z2.denominator();
        int tmp_de = z1.denominator() * z2.numerator();
        int tmp_gcd = std::gcd(tmp_nu, tmp_de);
        if (tmp_de < 0) {
            tmp_nu *= -1;
            tmp_de = abs(tmp_de);
        }
        return {tmp_nu / tmp_gcd, tmp_de / tmp_gcd};
    } else {
        return {0, 1};
    }
}
