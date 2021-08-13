'use strict';

let counter = 0;
function solveEquation(input, strUserSees, returnMode = 1) {
  const resultOfEquation = document.getElementById('result');
  superScript = 0;
  console.clear();
  clrscr();
  counter += returnMode;
  let times = 0;
  let total = 0.0;
  let equation = '', arr = '', functions = '';
  let functionPositions = [];
  let numberOfFunctions = 0;
  
  if (resultOfEquation.textContent !== "") {
    const newline = document.createElement("br");
    resultOfEquation.appendChild(newline);
  }
  if (strUserSees.length > 25) {
    resultOfEquation.append("Input is too long. Maximum length of input is 25.");
    return;
  }
  equation = input.replace(/ /g, '');
  if (!isValidInput(input)) {
    resultOfEquation.append(`ERROR: Invalid input`);
    return;
  }
  //Check for functions like sin and GCD. Also check for math constants like PI
  for (let i = 0; i < equation.length; i++) {
    if (invalidChars(equation[i])) {
      resultOfEquation.append(`Syntax ERROR`);
      return;
    }
    if (isalpha(equation[i])) {
      arr = equation.substring(i, i + 10);
      switch(equation[i]) {
        case "P": {
          if (arr.startsWith("PI")) {
            equation = equation.substring(0, i) + 'Z' + equation.substring(i + 1);
            equation = removeChar(equation, i, 1);
            i++;
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "a": {
          if (arr.startsWith("arcsin(")) {
            if (!verifyValidCharAfterFunction(equation, i, 7)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 7);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 6;
            functions += "d";
          }
          else if (arr.startsWith("arccos(")) {
            if (!verifyValidCharAfterFunction(equation, i, 7)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 7);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 6;
            functions += "e";
          }
          else if (arr.startsWith("arctan(")) {
            if (!verifyValidCharAfterFunction(equation, i, 7)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 7);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 6;
            functions += "f";
          }
          else if (arr.startsWith("arcsinh(")) {
            if (!verifyValidCharAfterFunction(equation, i, 8)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 8);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 7;
            functions += "g";
          }
          else if (arr.startsWith("arccosh(")) {
            if (!verifyValidCharAfterFunction(equation, i, 8)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 8);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 7;
            functions += "h";
          }
          else if (arr.startsWith("arctanh(")) {
            if (!verifyValidCharAfterFunction(equation, i, 8)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 8);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 7;
            functions += "i";
          }
          else if (arr.startsWith("abs(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "r";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "G": {
          if (arr.startsWith("GOLDEN_RT")) {
            equation = removeChar(equation, i, 8);
            i += 8;
          }
          else if (arr.startsWith("GCD(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "2";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
        }
        case "S": {
          if (arr.startsWith("SILVER_RT")) {
            equation = equation.substring(0, i) + 'Y' + equation.substring(i + 1);
            equation = removeChar(equation, i, 8);
            i += 8;
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "r": {
          if (arr.startsWith("root(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "0";
          }
          else if (arr.startsWith("round(")) {
            if (!verifyValidCharAfterFunction(equation, i, 6)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 6);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 5;
            functions += "u";
          }
          else if (arr.startsWith("random(")) {
            if (!verifyValidCharAfterFunction(equation, i, 7)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 7);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 6;
            functions += "q";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "s": {
          if (arr.startsWith("sin(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "4";
          }
          else if (arr.startsWith("sec(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "8";
          }
          else if (arr.startsWith("sinh(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "a";
          }
          else if (arr.startsWith("sinc(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "j";
          }
          else if (arr.startsWith("sqrt(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "k";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "l": {
          if (arr.startsWith("log(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "1";
          }
          else if (arr.startsWith("log*(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "A";
          }
          else if (arr.startsWith("ln(")) {
            if (!verifyValidCharAfterFunction(equation, i, 3)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 3);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 2;
            functions += "o";
          }
          else if (arr.startsWith("log10(")) {
            if (!verifyValidCharAfterFunction(equation, i, 6)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 6);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 5;
            functions += "p";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "L": {
          if (arr.startsWith("LCM(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "3";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "n": {
          if (arr.startsWith("nCr")) {
            equation = equation.substring(0, i) + 'C' + equation.substring(i + 1);
            equation = removeChar(equation, i, 2);
            i += 2;
          }
          else if (arr.startsWith("nPr")) {
            equation = equation.substring(0, i) + 'P' + equation.substring(i + 1);
            equation = removeChar(equation, i, 2);
            i += 2;
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "c": {
          if (arr.startsWith("cos(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "5";
          }
          else if (arr.startsWith("csc(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 6);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 5;
            functions += "7";
          }
          else if (arr.startsWith("cot(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "9";
          }
          else if (arr.startsWith("cosh(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "b";
          }
          else if (arr.startsWith("cbrt(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "l";
          }
          else if (arr.startsWith("ceil(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "s";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "t": {
          if (arr.startsWith("tan(")) {
            if (!verifyValidCharAfterFunction(equation, i, 4)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 4);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 3;
            functions += "6";
          }
          else if (arr.startsWith("tanh(")) {
            if (!verifyValidCharAfterFunction(equation, i, 5)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 5);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 4;
            functions += "c";
          }
          else if (arr.startsWith("tetrate(")) {
            if (!verifyValidCharAfterFunction(equation, i, 8)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 8);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 7;
            functions += "B";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "f": {
          if (arr.startsWith("floor(")) {
            if (!verifyValidCharAfterFunction(equation, i, 6)) {
              resultOfEquation.append(`Syntax ERROR`);
              return;
            }
            equation = removeChar(equation, i - 1, 6);
            functionPositions[numberOfFunctions] = i;
            numberOfFunctions++;
            i += 5;
            functions += "t";
          }
          else {
            resultOfEquation.append(`Syntax ERROR`);
            return;
          }
          break;
        }
        case "E":
        case "e":
          break;
        default: {
          resultOfEquation.append(`Syntax ERROR`);
          return;
        }
      }
    }
  }
  equation = setUp(equation);
  if (!equation) {
    resultOfEquation.append(`Syntax ERROR`);
    return;
  }
  equation = getBracketResults(equation);
  if (!equation) {
    resultOfEquation.append(`Syntax ERROR`);
    return;
  }
  
  let positions = [].fill(0);
  positions = getPositionsOfNums(equation);
  times = positions.length - 1;
  
  let operations = ''; //All the operations in the equation
  let operationPositions = []; //All the indexes of the operations
  let numberOfSeperators = equation.split(",").length - 1; //Keeps track of how many commas there are in the equation
  let seperatorPositions = []; //All the positions of the commas in the equation
  let nums = new Array(times + 1).fill(0); //All the numbers in the equation
  //If there are more commas than there are functions which take two inputs
  if (functions.length < numberOfSeperators) {
    resultOfEquation.append(`Syntax ERROR`);
    return;
  }
  //Add operations onto the operations string
  for (let i = 0; i < equation.length; i++) {
    if (validateOperation(equation[i]) === 0) {
      if (equation[i] === '-' && isdigit(equation[i + 1]) && !isdigit(equation[i - 1])) {
        continue;
      }
      operations += equation[i];
      operationPositions.push(i);
      if (equation[i] === ",") {
        seperatorPositions.push(i);
      }
    }
  }
  //Get the numbers
  for (let i = 0; i < times + 1; i++) {
    nums[i] = convertFloat(equation, positions[i], equation.length);
    if (nums[i] === undefined) {
      resultOfEquation.append(`Syntax ERROR`);
      return;
    }
  }
  //Factorial
  for (let i = 0; i < times; i++) {
    if (operations[i] === '!') {
      if (Math.floor(nums[i]) !== nums[i] || nums[i] < 0) {
        resultOfEquation.append(`ERROR: Cannot take factorial of decimal`);
        return;
      }
      nums[i] = factorial(nums[i]);
      operations = operations.substring(0, i) + operations.substring(i + 1);
      if (operations[i] === '!')
        i--;
    }
  }
  let location = 0;
  for (let i = 0; i < times + 1; i++) {
    if (functionPositions.includes(positions[i] + 1)) {
      operations = [operations.slice(0, i), "*", operations.slice(i)].join('');
      operationPositions.splice(i, 0, positions[i] + 1);
      functionPositions[functionPositions.indexOf(positions[i] + 1)]++;
      input = [input.slice(0, positions[i] + 1), "*", input.slice(positions[i] + 1)].join('');
    }
  }
  for (let i = 0, coefficient = 1; i < numberOfFunctions; i++) {
    location = getLocation(i, times, positions, operations, operationPositions, functionPositions, functions);
    if (location === -1) {
      resultOfEquation.append(`Argument ERROR`);
      return;
    }
    nums = getFunctionValue(nums, operations, functions, location, i, counter);
    if (nums.includes(undefined)) {
      resultOfEquation.append(`Argument ERROR`);
      return;
    }
    location = 0;
  }
  //E
  for (let i = 0; i < times; i++) {
    if (operations[i] === 'e') {
      if (Math.floor(nums[i + 1]) !== nums[i + 1]) {
        resultOfEquation.append(`Syntax ERROR`);
        return;
      }
      nums[i + 1] = nums[i] * Math.pow(10, nums[i + 1]);
      nums[i] = setNum(operations, i);
      operations = setOperation(operations, i);
    }
  }
  //Modulo operation
  for (let i = 0; i < times; i++) {
    if (operations[i] === '%') {
      nums[i + 1] = nums[i] % nums[i + 1];
      nums[i] = setNum(operations, i);
      operations = setOperation(operations, i);
    }
    else if (operations[i] === ',' && operations[i - 1] !== '^') {
      operations = setOperation(operations, i);
    }
  }
  //Exponents
  for (let i = 0; i < times; i++) {
    if (operations[i] === '^') {
      nums[i + 1] = Math.pow(nums[i], nums[i + 1]);
      nums[i] = setNum(operations, i);
      operations = setOperation(operations, i);
    }
  }
  //nCr, nPr
  for (let i = 0; i < times; i++) {
    if (operations[i] === 'C') {
      if (Math.floor(nums[i]) !== nums[i] || Math.floor(nums[i + 1]) !== nums[i + 1] || nums[i + 1] > nums[i]) {
        resultOfEquation.append(`Syntax ERROR`);
        return;
      }
      nums[i + 1] = factorial(nums[i]) / (factorial(nums[i + 1]) * factorial(nums[i] - nums[i + 1]));
      total += nums[i + 1];
      nums[i] = setNum(operations, i);
      operations = setOperation(operations, i);
    }
    else if (operations[i] === 'P') {
      if (Math.floor(nums[i]) !== nums[i] || Math.floor(nums[i + 1]) !== nums[i + 1] || nums[i + 1] > nums[i]) {
        resultOfEquation.append(`Syntax ERROR`);
        return;
      }
      nums[i + 1] = factorial(nums[i]) / factorial(nums[i] - nums[i + 1]);
      total += nums[i + 1];
      nums[i] = setNum(operations, i);
      operations = setOperation(operations, i);
    }
  }
  //Multiplication, Division
  for (let i = 0; i < times; i++) {
    if (operations[i] === '*') {
      nums[i + 1] *= nums[i];
      nums[i] = 0;
      operations = setOperation(operations, i);
    }
    else if (operations[i] === '/') {
      nums[i + 1] = nums[i] / nums[i + 1];
      if (!isFinite(nums[i + 1])) {
        resultOfEquation.append(`Division by 0 ERROR`);
        return;
      }
      nums[i] = 0;
      operations = setOperation(operations, i);
    }
  }
  let indexOfNumAssignedToTotal = 0;
  //Assign total first non-zero term of nums
  for (let i = 0; i < times + 1; i++) {
    if (nums[i] !== 0) {
      indexOfNumAssignedToTotal = i;
      total = nums[i];
      break;
    }
  }
  //Addition, Subtraction
  for (let i = indexOfNumAssignedToTotal; i < times; i++) {
    if (operations[i] === '+') {
      total += nums[i + 1];
    }
    else if (operations[i] === '-') {
      total -= nums[i + 1];
    }
  }
  if (returnMode === 1) {
    resultOfEquation.innerHTML += `Equation ${counter}: ${strUserSees} = ${total}`;
  }
  else {
    return total.toString();
  }
}
