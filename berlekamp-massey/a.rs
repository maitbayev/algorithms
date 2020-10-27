use std::cmp::max;
use std::io;

make_field! {Field, 998244353}

/// Finds the shortest linear recurrence using the [Berlekamp–Massey
/// algorithm](https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm).
/// Returns list of coefficients `c[0], c[1], ..., c[l-1]` corresponding to the recurrence relation
/// `a[n] = c[0]*a[n - 1] + c[1]*a[n-2] + ... + c[l-1]*a[n-l]`.
///
/// # Examples
///
/// ```
/// use eulerlib::linear_recurrence;
///
/// assert_eq!(linear_recurrence(&[1, 1, 2, 3, 5, 8]), vec![1, 1]);
/// assert_eq!(linear_recurrence(&[0, 1, 4, 9, 16, 25]), vec![3, -3, 1]);
/// ```
pub fn linear_recurrence(a: &[Field]) -> Vec<Field> {
    let mut c = vec![Field::one()];
    let mut b = vec![Field::one()];
    let mut db = Field::one();
    let mut shift = 0;
    for i in 0..a.len() {
        shift += 1;
        let mut d = Field::zero();
        for j in 0..c.len() {
            d += a[i - j] * c[j];
        }
        if d == Field::zero() {
            continue;
        }
        let c_prev = c.clone();
        let coef = d / db;
        c.resize(max(c.len(), b.len() + shift), Field::zero());
        for j in 0..b.len() {
            c[j + shift] -= coef * b[j];
        }
        if c_prev.len() < c.len() {
            b = c_prev;
            db = d;
            shift = 0;
        }
    }

    c[1..].iter().map(|&x| -x).collect()
}

fn readline() -> String {
    let stdin = io::stdin();
    let mut buf = String::new();
    stdin.read_line(&mut buf).expect("reading won't fail");
    buf.trim().to_string()
}

fn main() {
    readline();
    let v: Vec<Field> = readline()
        .split_whitespace()
        .map(|x| Field::from(x.parse::<i32>().unwrap()))
        .collect();
    let r = linear_recurrence(&v);
    println!("{}", r.len());
    for v in r.iter() {
        print!("{} ", v.0);
    }
}

#[macro_export]
macro_rules! make_field {
    ($name:ident, $mod:expr) => {
        #[derive(Clone, Copy, Eq, PartialEq, Debug, Hash)]
        pub struct $name(pub i32);

        impl $name {
            pub const MOD: i32 = $mod;

            fn canon(val: i32) -> Self {
                $name(if val < 0 { val + Self::MOD } else { val })
            }

            fn one() -> Self {
                $name(1)
            }

            fn zero() -> Self {
                $name(0)
            }

            pub fn pow(self, n: u64) -> Self {
                let mut n = n;
                let mut res = $name::one();
                let mut a = self;
                while n > 0 {
                    if n & 1 == 1 {
                        res = res * a;
                    }
                    a = a * a;
                    n >>= 1;
                }

                res
            }

            pub fn recip(self) -> Self {
                self.pow(Self::MOD as u64 - 2)
            }
        }

        impl From<i32> for $name {
            fn from(val: i32) -> Self {
                Self::canon(val % $name::MOD)
            }
        }

        impl From<u32> for $name {
            fn from(val: u32) -> Self {
                $name((val % ($name::MOD as u32)) as i32)
            }
        }

        impl From<i64> for $name {
            fn from(val: i64) -> Self {
                Self::canon((val % ($name::MOD as i64)) as i32)
            }
        }

        impl From<u64> for $name {
            fn from(val: u64) -> Self {
                $name((val % ($name::MOD as u64)) as i32)
            }
        }

        impl std::ops::Neg for $name {
            type Output = Self;

            fn neg(self) -> Self {
                Self::canon(-self.0)
            }
        }

        impl std::ops::Add for $name {
            type Output = Self;
            fn add(self, other: Self) -> Self {
                let s = self.0 + other.0;
                $name(if s >= Self::MOD { s - Self::MOD } else { s })
            }
        }

        impl std::ops::Sub for $name {
            type Output = Self;
            fn sub(self, other: Self) -> Self {
                Self::canon(self.0 - other.0)
            }
        }

        impl std::ops::Mul for $name {
            type Output = Self;
            fn mul(self, other: Self) -> Self {
                let mul: i64 = (self.0 as i64 * other.0 as i64) % $name::MOD as i64;
                $name(mul as i32)
            }
        }

        impl std::ops::Div for $name {
            type Output = Self;
            fn div(self, other: Self) -> Self {
                self * other.recip()
            }
        }

        impl std::ops::AddAssign for $name {
            fn add_assign(&mut self, other: Self) {
                *self = *self + other;
            }
        }

        impl std::ops::SubAssign for $name {
            fn sub_assign(&mut self, other: Self) {
                *self = *self - other;
            }
        }

        impl std::ops::MulAssign for $name {
            fn mul_assign(&mut self, other: Self) {
                *self = *self * other;
            }
        }

        impl std::ops::DivAssign for $name {
            fn div_assign(&mut self, other: Self) {
                *self = *self / other;
            }
        }

        impl std::iter::Sum for $name {
            fn sum<I: Iterator<Item = Self>>(iter: I) -> Self {
                iter.fold(Self::zero(), std::ops::Add::add)
            }
        }

        impl std::iter::Product for $name {
            fn product<I: Iterator<Item = Self>>(iter: I) -> Self {
                iter.fold(Self::one(), std::ops::Mul::mul)
            }
        }
    };
}
