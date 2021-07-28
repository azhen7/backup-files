//Contains additional constants and functions
const PI = 3.141592653;
const E = 2.718281828;
const GOLDEN_RT = 1.618033988;
const SILVER_RT = 2.414213562;
const SQRT_2 = 1.414213562;
const SQRT_3 = 1.732050807;
const mathConsts = [
  "PI",
  "E",
  "GOLDEN_RT",
  "SILVER_RT",
  "SQRT_2",
  "SQRT_3"
];

//Return numbers present in equation
function convertFloat(input, startIndex, endIndex) {
  let lastNum = 0;
  let total = 0.0;
  let multNeg = 1;
  let numNum = 1;
  let returnValueOfMathConstant = (input, i) => {
    const repMathConstsChar = ["Z", "E", "G", "Y", "T", "R"];
    let index = repMathConstsChar.indexOf(input[i]);
    return eval(mathConsts[index]);
  }
  for (let i = startIndex; i < endIndex; i++) {
    if (!isdigit(input[i])) {
      //If input[i] is a decimal point, start adding decimals
      if (input[i] === ".") {
        if (!isdigit(input[i + 1])) {
          return undefined;
        }
        else {
          lastNum = 1;
        }
      }
      //If input[i] is a valid operation, this implies that the first number has terminated
      else if (validateOperation(input[i]) === 0 || input[i] == ' ') {
        break;
      }
      else if (validateConstantChar(input[i])) {
        if (total === 0)
            total = 1;
        total *= returnValueOfMathConstant(input, i);
        break;
      }
      else if (input[i] === "m")
        multNeg = -1;
      else {
        return undefined;
      }
    } 
    else {
      if (lastNum === 0) {
        total += input[i].charCodeAt() - 48;
        if (i !== endIndex - 1) {
          if (isdigit(input[i + 1])) 
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

function setNum(operations, index, offset = -1) {
  if (operations[index + offset] === undefined) {
    return 0;
  }
  else {
    if (operations[index + offset] === "*" || operations[index + offset] === "/" || (operations[index] === "^" && offset >= 0)) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

//Get the positions of the numbers
function getPositionsOfNums(equation, arrSize) {
  let positions = [];
  //Get the positions of the numbers
  for (let i = 0; i < equation.length; i++) {
    if (isdigit(equation[i])) {
      if (i > 0) {
        if (!isdigit(equation[i - 1]) && equation[i - 1] !== 'm' && equation[i - 1] !== '.') {
          positions.push(i);
        }
      }
      else {
        positions.push(i);
      }
    }
    else {
      if (equation[i] === '-' && isdigit(equation[i + 1])) {
        if (i > 0) {
          if (validateOperation(equation[i - 1])) {
            equation = equation.substring(0, i) + 'm' + equation.substring(i + 1);
            positions.push(i);
          }
          else {
            positions.push(i);
          }
        }
      }
      else if (validateConstantChar(equation[i])) {
        if (i > 0) {
          if (!isdigit(equation[i - 1]) && equation[i - 1] !== '-') {
            positions.push(i);
          }
        }
        else {
          positions.push(i);
        }
      }
    }
  }
  positions.sort((a, b) => a - b); //Sort the positions in case there is some stupid positions confusion
  return positions;
}

function getFunctionValue(nums, operations, functions, location, i, counter) {
  //nth root
  if (functions[i] === "0") {
    let negative = 1;
    if (nums[location] < 0 && nums[location + 1] % 2 !== 0) {
      nums[location] *= -1;
      if (nums[location + 1] === Math.floor(nums[location + 1])) {
        negative = -1;
      }
    }
    if (operations[location - 1] === '^') {
      nums[location] = Math.pow(nums[location], 1 / nums[location + 1]);
      nums[location + 1] = setNum(operations, location, 0);
    }
    else {
      nums[location + 1] = Math.pow(nums[location], 1 / nums[location + 1]);
      nums[location] = setNum(operations, location);
    }
    nums[location + 1] *= negative;
  }
  //log
  else if (functions[i] === "1") {
    if (operations[location - 1] === '^') {
      nums[location] = log_base(nums[location], nums[location + 1], 1);
      nums[location + 1] = setNum(operations, location, 0);
    }
    else {
      nums[location + 1] = log_base(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, location);
    }
  }
  //GCD
  else if (functions[i] === "2") {
    if (nums[location] !== Math.floor(nums[location]) || nums[location + 1] !== Math.floor(nums[location + 1])) {
      nums[location + 1] = undefined;
      return nums;
    }
    if (operations[location - 1] === '^') {
      nums[location] = calculateGCD(nums[location], nums[location + 1], 1);
      nums[location + 1] = setNum(operations, location, 0);
    }
    else {
      nums[location + 1] = Math.abs(nums[location] * nums[location + 1]) / calculateGCD(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, location);
    }
  }
  //LCM
  else if (functions[i] === "3") {
    if (nums[location] !== Math.floor(nums[location]) || nums[location + 1] !== Math.floor(nums[location + 1])) {
      nums[location + 1] = undefined;
      return nums;
    }
    if (operations[location - 1] === '^') {
      nums[location] = Math.abs(nums[location] * nums[location + 1]) / calculateGCD(nums[location], nums[location + 1]);
      nums[location + 1] = setNum(operations, location, 0);
    }
    else {
      nums[location + 1] = Math.abs(nums[location] * nums[location + 1]) / calculateGCD(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, location);
    }
  }
  //sin
  else if (functions[i] === "4") {
    if (nums[location] === 3.141592653) {
      nums[location] = 0;
    } 
    else {
      nums[location] = Math.sin(nums[location]);
    }
  }
  //cos
  else if (functions[i] === "5") {
    nums[location] = Math.cos(nums[location]);
  }
  //tan
  else if (functions[i] === "6") {
    nums[location] = Math.tan(nums[location]);
  }
  //cosecant
  else if (functions[i] === "7") {
    nums[location] = cosec(nums[location]);
  }
  //secant
  else if (functions[i] === "8") {
    nums[location] = sec(nums[location]);
  }
  //cotangent
  else if (functions[i] === "9") {
    nums[location] = cot(nums[location]);
  }
  //sinh
  else if (functions[i] === "a") {
    nums[location] = Math.sinh(nums[location]);
  }
  //cosh
  else if (functions[i] === "b") {
    nums[location] = Math.cosh(nums[location]);
  }
  //tanh
  else if (functions[i] === "c") {
    nums[location] = Math.tanh(nums[location]);
  }
  //arcsin
  else if (functions[i] === "d") {
    nums[location] = Math.asin(nums[location]);
  }
  //arccos
  else if (functions[i] === "e") {
    nums[location] = Math.acos(nums[location]);
  }
  //arctan
  else if (functions[i] === "f") {
    nums[location] = Math.atan(nums[location]);
  }
  //arcsinh
  else if (functions[i] === "g") {
    nums[location] = Math.asinh(nums[location]);
  }
  //arccosh
  else if (functions[i] === "h") {
    nums[location] = Math.acosh(nums[location]);
  }
  //arctanh
  else if (functions[i] === "i") {
    nums[location] = Math.atanh(nums[location]);
  }
  //sinc
  else if (functions[i] === "j") {
    nums[location] = sinc(nums[location]);
  }
  //sqrt
  else if (functions[i] === "k") {
    nums[location] = Math.sqrt(nums[location]);
  }
  //cbrt
  else if (functions[i] === "l") {
    nums[location] = Math.cbrt(nums[location]);
  }
  //natural log
  else if (functions[i] === "o") {
    nums[location] = Math.log(nums[location]);
  }
  //log base 10
  else if (functions[i] === "p") {
    nums[location] = Math.log10(nums[location]);
  }
  //random number
  else if (functions[i] === "q") {
    
  }
  //abs
  else if (functions[i] === "r") {
    nums[location] = Math.abs(nums[location]);
  }
  //ceil
  else if (functions[i] === "s") {
    nums[location] = Math.ceil(nums[location]);
  }
  //floor
  else if (functions[i] === "t") {
    nums[location] = Math.floor(nums[location]);
  }
  //round
  else if (functions[i] === "u") {
    nums[location] = round(nums[location]);
  }
  //iterative log
  else if (functions[i] === "A") {
    if (operations[location] === '^') {
      nums[location] = iterative_log(nums[location], nums[location + 1], 1);
      nums[location + 1] = setNum(operations, location);
    }
    else {
      nums[location + 1] = iterative_log(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, location);
    }
  }
  //tetration
  else if (functions[i] === "B") {
    if (Math.floor(nums[location + 1]) !== nums[location + 1]) {
      return undefined;
    }
    if (operations[location] === '^') {
      nums[location] = tetrate(nums[location], nums[location + 1], 1);
      nums[location + 1] = setNum(operations, location);
    }
    else {
      nums[location + 1] = tetrate(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, location);
    }
  }
  return nums;
}

function getLocation(i, times, positions, operations, operationPositions, functionPositions) {
  for (let j = 0; j < times + 1; j++) {
    if (functionPositions[i] < positions[j]) {
      //Check if function takes two inputs (e.g. GCD)
      if (isFunctionWithTwoArgs(functions[i])) {
        if (functionPositions[i] > operationPositions[j - 1]) {
          if (operations[j] === ',') {
            if ((positions[j] < operationPositions[j] && positions[j + 1] < operationPositions[j + 1]) 
                || operationPositions[j + 1] === undefined) {
              return j;
            }
            else {
              return NaN;
            }
          }
          else {
            return NaN;
          }
        }
        else if (operationPositions[j - 1] === undefined) {
          if (operations[j] === ',') {
            return j;
          }
          else {
            return NaN;
          }
        }
      }
      //If the function takes only one input (e.g. trig functions)
      else {
        if (functionPositions[i] > operationPositions[j - 1]) {
          if (positions[j] < operationPositions[j]) {
            return j;
          }
          else if (operationPositions[j] === undefined || operationPositions[j - 1] === undefined) {
            return j;
          }
          else {
            return NaN;
          }
        }
        else if (operationPositions[j - 1] === undefined) {
          return j;
        }
        else {
          return NaN;
        }
      }
    }
  }
  return 0;
}
let getSubtractVal = (arr, lastChar, str) => {
  let funcOrConstStr = lastChar;
  let lookback = 2;
  while (isalpha(str[str.length - lookback])) {
    funcOrConstStr += str[str.length - lookback];
    if (str.length === lookback) {
      break;
    }
    lookback++;
  }
  funcOrConstStr = invert_letters(funcOrConstStr);
  if (arr.includes(funcOrConstStr)) {
    return funcOrConstStr.length;
  }
  else if (["nPr", "nCr"].includes(funcOrConstStr)) {
    return 3;
  }
  return 1;
};
//Invert letters in a string
let invert_letters = (input) => {
  let invertedStr = "";
  for (let i = input.length - 1; i >= 0; i--) {
    invertedStr += input[i];
  }
  return invertedStr;
};
