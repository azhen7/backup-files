//Contains additional constants and functions
const PI = 3.141592653;
const E = 2.718281828;
const GOLDEN_RT = 1.618033988;
const SILVER_RT = 2.414213562;
const APERY_CONST = 1.202056903;
const SQRT_2 = 1.414213562;
const SQRT_3 = 1.732050807;

/* Check if char is a number */
function isdigit(c) {
  if (c == ' ')
    return 0;
  if (c >= 48 || c <= 57)
    return 1;
  return 0;
}
//Returns number of operations
function numberOfOperations(input) {
  var times = 0;
  for (let i = 0; i < input.length; i++) {
    if (isdigit(input[i])) {
      continue;
    }
    if (validateOperation(input[i]) == 0) {
      if (validNext(input[i + 1]) == 0) {
        if (!(input[i] == '-' && isdigit(input[i + 1]) && !isdigit(input[i - 1]))) {
          times++;
        }
      }
    }
  }
  return times;
}
//Return numbers present in equation
function convertFloat(input, startIndex, endIndex) {
  var lastNum = 0;
  var total = 0.0;
  var multNeg = 1;
  var numNum = 1;
  for (let i = startIndex; i < endIndex; i++) {
    if (!isdigit(input[i])) {
      //If input[i] is a decimal point, start adding decimals
      if (input[i] == '.')
      {
        if (!isdigit(input[i + 1]))
        {
          if (input[i + 1] == '.' || isalpha(input[i + 1]) || input[i + 1] == ' ') {
            document.getElementById('result').innerHTML = "Invalid input";
            return;
          }
          else {
            break;
          }
        }
        else {
          lastNum = 1;
        }
      }
      //If input[i] is a valid operation, this implies that the first number has terminated
      else if (validateOperation(input[i]) == 0 || input[i] == ' ') {
        break;
      }
      else if (validateConstantChar(input[i])) {
        total = returnValueOfMathConstant(input, i);
        break;
      }
      else if (input[i] == 'm') {
        multNeg = -1;
      }
      else {
        document.getElementById('result').innerHTML = "Invalid input";
        return;
      }
    }
    else {
      if (lastNum == 0) {
        total += input[i].charCodeAt() - 48;
        if (isdigit(input[i + 1])) {
          total *= 10;
        }
      }
      else {
        total += (input[i].charCodeAt() - 48) / Math.pow(10, numNum);
        numNum++;
      }
    }
  }
  total *= multNeg;
  return total;
}

function returnValueOfMathConstant(input, i) {
  //Pi
  if (input[i] == '!') {
    return getMathConstant(input, i, PI);
  }
  //Golden Ratio
  else if (input[i] == 'G') {
    return getMathConstant(input, i, GOLDEN_RT);
  }
  //Square root of 2
  else if (input[i] == 'T') {
    return getMathConstant(input, i, SQRT_2);
  }
  //Square root of 3
  else if (input[i] == 'R') {
    return getMathConstant(input, i, SQRT_3);
  }
  //Euler's number
  else if (input[i] == 'E') {
    return getMathConstant(input, i, E);
  }
  //Silver Ratio
  else if (input[i] == 'Y') {
    return getMathConstant(input, i, SILVER_RT);
  }
  //Apery's Constant
  else if (input[i] == 'A') {
    return getMathConstant(input, i, APERY_CONST);
  }
  return 0;
}

function getMathConstant(input, index, mathConstant) {
  var value = 0;
  var coefForConsts;
  var lookback = 1;
  var startIndexCoefficient;
  if (index > 0 && isdigit(input[index - 1]))
  {
      coefForConsts = 0;
      while ((isdigit(input[index - lookback]) || input[index - lookback] == '.') && index - lookback >= 0)
      {
          startIndexCoefficient++;
          lookback++;
      }
      coefForConsts = convertFloat(input, index - startIndexCoefficient, index);
      value = coefForConsts * mathConstant;
  }
  else {
    value = mathConstant;
  }
  return value;
}

function log_base(a, b) {
  return Math.log(a) / Math.log(b);
}

function setNum(operations, index) {
  if (index == 0) {
    return 0;
  }
  else if (index > 0) {
    if (operations[index - 1] == '*' || operations[index - 1] == '/') {
      return 1;
    }
    else {
      return 0;
    }
  }
}
// Calculates GCD of a and b
function calculateGCD(a, b) {
  var temp = 0;
  if (a < b) {
    temp = a;
    a = b;
    b = temp;
  }
  while (b != 0) {
    temp = b;
    b = a % b;
    a = temp;
  }
    return a;
}
//sinc
function sinc(x) {
  if (x == 0) {
    return 1;
  }
  return Math.sin(x) / x;
}
//secant
function sec(x) {
  return 1 / Math.cos(x);
}
//cotangent
function cot(x) {
  return 1 / Math.tan(x);
}
//cosecant
function cosec(x) {
  return 1 / Math.sin(x);
}
//iterative log
function iterative_log(a, b) {
  if (b < 1.444667 || a <= 1) {
    return -1;
  }
  var iterative_count = 0;
  while (a > 1) {
    iterative_count++;
    a = log_base(a, b);
  }
  return iterative_count;
}
