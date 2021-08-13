//Contains additional constants and functions
const PI = 3.141592653;
const E = 2.718281828;
const GOLDEN_RT = 1.618033988;
const SILVER_RT = 2.414213562;
const mathConsts = [
  "PI",
  "E",
  "GOLDEN_RT",
  "SILVER_RT"
];

//Return numbers present in equation
function convertFloat(input, startIndex, endIndex) {
  let lastNum = 0;
  let total = 0.0;
  let multNeg = 1;
  let numNum = 1;
  let returnValueOfMathConstant = (input, i) => {
    const repMathConstsChar = ["Z", "E", "G", "Y"];
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
    if (operations[index + offset] === "*" || operations[index + offset] === "/" || 
        ((operations[index] === "*" || operations[index] === "/") && offset >= 0)) {
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
  switch(functions[i]) {
    //nth root
    case "0": {
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
      break;
    }
    //log
    case "1": {
      if (operations[location - 1] === '^') {
        nums[location] = log_base(nums[location], nums[location + 1], 1);
        nums[location + 1] = setNum(operations, location, 0);
      }
      else {
        nums[location + 1] = log_base(nums[location], nums[location + 1]);
        nums[location] = setNum(operations, location);
      }
      break;
    }
    //GCD
    case "2": {
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
      break;
    }
    //LCM
    case "3": {
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
      break;
    }
    //sin
    case "4": {
      if (nums[location] === 3.141592653) {
        nums[location] = 0;
      } 
      else {
        nums[location] = Math.sin(nums[location]);
      }
      break;
    }
    //cos
    case "5":
      nums[location] = Math.cos(nums[location]);
      break;
    //tan
    case "6":
      nums[location] = Math.tan(nums[location]);
      break;
    //cosecant
    case "7":
      nums[location] = cosec(nums[location]);
      break;
    //secant
    case "8":
      nums[location] = sec(nums[location]);
      break;
    //cotangent
    case "9":
      nums[location] = cot(nums[location]);
      break;
    //sinh
    case "a":
      nums[location] = Math.sinh(nums[location]);
      break;
    //cosh
    case "b":
      nums[location] = Math.cosh(nums[location]);
      break;
    //tanh
    case "c":
      nums[location] = Math.tanh(nums[location]);
      break;
    //arcsin
    case "d":
      nums[location] = Math.asin(nums[location]);
      break;
    //arccos
    case "e":
      nums[location] = Math.acos(nums[location]);
      break;
    //arctan
    case "f":
      nums[location] = Math.atan(nums[location]);
      break;
    //arcsinh
    case "g":
      nums[location] = Math.asinh(nums[location]);
      break;
    //arccosh
    case "h":
      nums[location] = Math.acosh(nums[location]);
      break;
    //atanh
    case "i":
      nums[location] = Math.atanh(nums[location]);
      break;
    //sinc
    case "j":
      nums[location] = sinc(nums[location]);
      break;
    //sqrt
    case "k":
      nums[location] = Math.sqrt(nums[location]);
      break;
    //cbrt
    case "l":
      nums[location] = Math.cbrt(nums[location]);
      break;
    //ln
    case "o":
      nums[location] = Math.log(nums[location]);
      break;
    //log
    case "p":
      nums[location] = Math.log10(nums[location]);
      break;
    //random number
    case "q":
      nums[location] = Math.random().toFixed(3);
      break;
    //abs
    case "r":
      nums[location] = Math.abs(nums[location]);
      break;
    //ceil
    case "s":
      nums[location] = Math.ceil(nums[location]);
      break;
    //floor
    case "t":
      nums[location] = Math.floor(nums[location]);
      break;
    //round
    case "u":
      nums[location] = round(nums[location]);
      break;
    //iterative log
    case "A": {
      if (operations[location] === '^') {
        nums[location] = iterative_log(nums[location], nums[location + 1], 1);
        nums[location + 1] = setNum(operations, location);
      }
      else {
        nums[location + 1] = iterative_log(nums[location], nums[location + 1]);
        nums[location] = setNum(operations, location);
      }
      break;
    }
    //tetration
    case "B": {
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
      break;
    }
  }
  return nums;
}

function getBracketResults(equation) {
  let numOfLeft = 0;
  let numOfRight = 0;
  let startingPos = 0;
  let endingPos = 0;
  for (let indexOfEquation = 0; indexOfEquation < equation.length; indexOfEquation++) {
    if (equation[indexOfEquation] === '(') {
      if (numOfLeft === 0) {
        startingPos = indexOfEquation;
      }
      numOfLeft++;
    }
    else if (equation[indexOfEquation] === ')') {
      if (numOfLeft === 0) {
        return null;
      }
      numOfRight++;
    }
    
    if (numOfRight === numOfLeft && (numOfRight > 0 && numOfLeft > 0)) {
      endingPos = indexOfEquation;
      let str = equation.substring(startingPos + 1, endingPos);
      str = solveEquation(str, '', 0);
      equation = equation.substring(0, startingPos) + str + equation.substring(endingPos + 1);
      
      numOfLeft = 0;
      numOfRight = 0;
      startingPos = 0;
      endingPos = 0;
    }
  }
  return equation;
}
function getLocation(i, times, positions, operations, operationPositions, functionPositions, functions) {
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
              return -1;
            }
          }
          else {
            return -1;
          }
        }
        else if (operationPositions[j - 1] === undefined) {
          if (operations[j] === ',') {
            return j;
          }
          else {
            return -1;
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
            return -1;
          }
        }
        else if (operationPositions[j - 1] === undefined) {
          return j;
        }
        else {
          return -1;
        }
      }
    }
  }
  return -1;
}
function getSubtractVal(arr, secondArr, lastChar, str) {
  let funcOrConstStr = lastChar;
  let lookback = 2;
  while (lookback <= str.length && (isalpha(str[str.length - lookback]))) {
    funcOrConstStr += str[str.length - lookback];
    lookback++;
  }
  funcOrConstStr = invert_letters(funcOrConstStr);
  if (arr.includes(funcOrConstStr) || secondArr.includes(funcOrConstStr)) {
    return funcOrConstStr.length;
  }
  return 1;
};
