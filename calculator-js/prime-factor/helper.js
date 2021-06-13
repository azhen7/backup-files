//Check when input is valid
function validateInput(input) {
  for (let i = 0; i < input.length; i++) {
    if (!isdigit(input[i])) {
      return -1;
    }
  }
  return parseInt(input);
}
//Check if number is pfime
function isPrime(num) {
  var i;
  if (num % 2 == 0) {
    return 1;
  }
  if (num % 3 == 0) {
    return 1;
  }
  
  for (i = 1; 6 * i - 1 <= Math.floor(Math.sqrt(num)); i++) {
    if (num % (6 * i - 1) == 0) {
      return 1;
    }
  }
  for (i = 1; 6 * i + 1 <= Math.floor(Math.sqrt(num)); i++) {
    if (num % (6 * i + 1) == 0) {
      return 1;
    }
  }
  return 0;
}
//Get number of prime factors
function getNumberOfPrimeFactors(num) {
  if (isPrime(num) == 0) {
    return 1;
  }
  var i;
  var primeFactorNumber = 0;
  if (num % 2 == 0) {
    primeFactorNumber++;
  }
  if (num % 3 == 0) {
    primeFactorNumber++;
  }
  for (i = 1; 6 * i - 1 <= Math.floor(num / 2); i++) {
    if (num % (6 * i - 1) == 0 && isPrime(6 * i - 1) == 0) {
      primeFactorNumber++;
    }
  }
  for (i = 1; 6 * i + 1 <= Math.floor(num / 2); i++) {
    if (num % (6 * i + 1) == 0 && isPrime(6 * i + 1) == 0) {
      primeFactorNumber++;
    }
  }
  return primeFactorNumber;
}
//Get prime factors
function getPrimeFactors(num) {
  var i;
  var index = 0;
  var numberOfPrimeFactors = getNumberOfPrimeFactors(num);
  var primeFactors = new Array(numberOfPrimeFactors * 4);
  if (num % 2 == 0) {
    primeFactors[index] = 2;
    index++;
  }
  if (num % 3 == 0) {
    primeFactors[index] = 3;
    index++;
  }
  for (i = 1; 6 * i - 1 <= Math.floor(num / 2); i++) {
    if (num % (6 * i - 1) == 0 && isPrime(6 * i - 1) == 0) {
      primeFactors[index] = 6 * i - 1;
      index++;
    }
  }
  for (i = 1; 6 * i + 1 <= Math.floor(num / 2); i++) {
    if (num % (6 * i + 1) == 0 && isPrime(6 * i + 1) == 0) {
      primeFactors[index] = 6 * i + 1;
      index++;
    }
  }
  return primeFactors;
}
//Get the exponents of the prime factors
function getExponentsOfPrimeFactors(num) {
  var numberOfPrimeFactors = getNumberOfPrimeFactors(num);
  var primeFactors = getPrimeFactors(num);
  var primeFactorsAndExponents = new Array(numberOfPrimeFactors * 4).fill(0);
  for (let i = 0; i < numberOfPrimeFactors; i++) {
    while (num % primeFactors[i] == 0) {
      primeFactorsAndExponents[i]++;
      num /= primeFactors[i];
    }
  }
  return primeFactorsAndExponents;
}
