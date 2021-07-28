//log with variable base
let log_base = (a, b) => {
  return Math.log(a) / Math.log(b);
};
//secant
let sec = (x) => {
  return 1 / Math.cos(x);
};
//cotangent
let cot = (x) => {
  return 1 / Math.tan(x);
};
//cosecant
let cosec = (x) => {
  return 1 / Math.sin(x);
};
//round
let round = (a) => {
  let negative = 1;
  if (a < 0) {
    a *= -1;
    negative = -1;
  }
  a = Math.trunc(a) + 1 * (a - Math.floor(a) >= 0.5);
  a *= negative;
  return a;
};
//sin cardinal (e.g. sinc)
let sinc = (x) => {
  if (x == 0) {
    return 1;
  }
  return Math.sin(x) / x;
};
//iterative log
let iterative_log = (a, b) => {
  if (b < 1.444667 || a <= 1) {
    return -1;
  }
  let iterative_count = 0;
  while (a > 1) {
    iterative_count++;
    a = log_base(a, b);
  }
  return iterative_count;
};
//tetration
let tetrate = (a, b) => {
  let exponent = a
  for (let j = 0; j < b - 1; j++) {
    exponent = Math.pow(a, exponent);
  }
  return exponent;
};
//factorial
let factorial = (num) => {
  let result = 1;
  for (let i = 2; i <= num; i++) {
    result *= i;
  }
  return result;
}
// Calculates GCD of a and b
let calculateGCD = (a, b) => {
  let temp = 0;
  if (a < b) {
    temp = a;
    a = b;
    b = temp;
  }
  while (b !== 0) {
    temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}
