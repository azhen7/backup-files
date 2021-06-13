function solveEquation(input) {
  console.clear(); //For debugging purposes
  var a = document.getElementById('result');
  a.innerHTML = " ";
  var times = 0, posIndex = 0;
  var total = 0.0;
  var equation = '', arr = '', functions = '';
  var functionPositions = new Array(input.length);
  var numberOfFunctions = 0.0;
  
  if (!isValidInput(input)) {
    a.innerHTML = "Invalid input";
    return;
  }
  equation = copyStrWithoutSpaces(input);
  
  for (let i = 0; i < equation.length; i++) {
    if (equation[i].charCodeAt() > 127) {
      a.innerHTML = "Invalid input";
      return;
    }
    else if (equation[i].toLowerCase() != equation[i].toUpperCase()) {
      arr = equation.substring(i, i + 10);
      if (equation[i] == 'P' || equation[i] == 'p') {
        if (arr.substring(0, 2) == "PI" || arr.substring(0, 2) == "pi") {
          equation = equation.substring(0, i) + '!' + equation.substring(i + 1);
          equation = removeChar(equation, i, 1);
          i++;
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'A') {
        if (arr.substring(0, 10) == "APERY_CNST") {
          equation = removeChar(equation, i, 9);
          i += 9;
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'a') {
        if (arr.substring(0, 7) == "arcsin(") {
          if (!isdigit(equation[i + 7]) && equation[i + 7] != '-' && !validateConstantFirstChar(equation[i + 7])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 7);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 6;
          functions += "d";
        }
        else if (arr.substring(0, 7) == "arccos(") {
          if (!isdigit(equation[i + 7]) && equation[i + 7] != '-' && !validateConstantFirstChar(equation[i + 7])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 7);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 6;
          functions += "e";
        }
        else if (arr.substring(0, 7) == "arctan(") {
          if (!isdigit(equation[i + 7]) && equation[i + 7] != '-' && !validateConstantFirstChar(equation[i + 7])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 7);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 6;
          functions += "f";
        }
        else if (arr.substring(0, 8) == "arcsinh(") {
          if (!isdigit(equation[i + 8]) && equation[i + 8] != '-' && !validateConstantFirstChar(equation[i + 8])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 8);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 7;
          functions += "g";
        }
        else if (arr.substring(0, 8) == "arccosh(") {
          if (!isdigit(equation[i + 8]) && equation[i + 8] != '-' && !validateConstantFirstChar(equation[i + 8])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 8);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 7;
          functions += "h";
        }
        else if (arr.substring(0, 8) == "arctanh(") {
          if (!isdigit(equation[i + 8]) && equation[i + 8] != '-' && !validateConstantFirstChar(equation[i + 8])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 8);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 7;
          functions += "i";
        }
        else if (arr.substring(0, 4) == "abs(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "r";
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'G') {
        if (arr.substring(0, 9) == "GOLDEN_RT") {
          equation = removeChar(equation, i - 1, 9);
          i += 8;
        }
        else if (arr.substring(0, 4) == "GCD(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "2";
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'S') {
        if (arr.substring(0, 6) == "SQRT_2") {
          equation = equation.substring(0, i) + 'T' + equation.substring(i + 1);
          equation = removeChar(equation, i, 5);
          i += 5;
        }
        else if (arr.substring(0, 6) == "SQRT_3") {
          equation = equation.substring(0, i) + 'R' + equation.substring(i + 1);
          equation = removeChar(equation, i, 5);
          i += 5;
        }
        else if (arr.substring(0, 9) == "SILVER_RT") {
          equation = equation.substring(0, i) + 'Y' + equation.substring(i + 1);
          equation = removeChar(equation, i, 8);
          i += 8;
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'r') {
        if (arr.substring(0, 5) == "root(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "0";
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 's') {
        if (arr.substring(0, 4) == "sin(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "4";
        }
        else if (arr.substring(0, 4) == "sec(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "8";
        }
        else if (arr.substring(0, 5) == "sinh(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "a";
        }
        else if (arr.substring(0, 5) == "sinc(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "j";
        }
        else if (arr.substring(0, 5) == "sqrt(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "k";
        }
        else if (arr.substring(0, 7) == "square(") {
          if (!isdigit(equation[i + 7]) && equation[i + 7] != '-' && !validateConstantFirstChar(equation[i + 7])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 7);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 6;
          functions += "m";
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'l') {
        if (arr.substring(0, 4) == "log(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "1";
        }
        else if (arr.substring(0, 5) == "log*(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "A";
        }
        else if (arr.substring(0, 3) == "ln(") {
          if (!isdigit(equation[i + 3]) && equation[i + 3] != '-' && !validateConstantFirstChar(equation[i + 3])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 3);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 2;
          functions += "o";
        }
        else if (arr.substring(0, 6) == "log10(") {
          if (!isdigit(equation[i + 6]) && equation[i + 6] != '-' && !validateConstantFirstChar(equation[i + 6])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 6);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 5;
          functions += "p";
        }
        else if (arr.substring(0, 5) == "log2(")
        {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "q";
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'L') {
        if (arr.substring(0, 4) == "LCM(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "3";
        }
        if (arr.substring(0, 4) == "LOG(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "1";
        }
        else if (arr.substring(0, 5) == "LOG*(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "A";
        }
        else if (arr.substring(0, 3) == "LN(") {
          if (!isdigit(equation[i + 3]) && equation[i + 3] != '-' && !validateConstantFirstChar(equation[i + 3])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 3);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 2;
          functions += "o";
        }
        else if (arr.substring(0, 6) == "LOG10(") {
          if (!isdigit(equation[i + 6]) && equation[i + 6] != '-' && !validateConstantFirstChar(equation[i + 6])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 6);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 5;
          functions += "p";
        }
        else if (arr.substring(0, 5) == "LOG2(")
        {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "q";
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'n') {
        if (arr.substring(0, 3) == "nCr") {
          equation = equation.substring(0, i) + 'C' + equation.substring(i + 1);
          equation = removeChar(equation, i, 2);
          i += 2;
        }
        else if (arr.substring(0, 3) == "nPr") {
          equation = equation.substring(0, i) + 'P' + equation.substring(i + 1);
          equation = removeChar(equation, i, 2);
          i += 2;
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'c') {
        if (arr.substring(0, 4) == "cos(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "5";
        }
        else if (arr.substring(0, 6) == "cosec(") {
          if (!isdigit(equation[i + 6]) && equation[i + 6] != '-' && !validateConstantFirstChar(equation[i + 6])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 6);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 5;
          functions += "7";
        }
        else if (arr.substring(0, 4) == "cot(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "9";
        }
        else if (arr.substring(0, 5) == "cosh(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "b";
        }
        else if (arr.substring(0, 5) == "cbrt(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "l";
        }
        else if (arr.substring(0, 5) == "cube(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "n";
        }
        else if (arr.substring(0, 5) == "ceil(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "s";
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 't') {
        if (arr.substring(0, 4) == "tan(") {
          if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 4);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 3;
          functions += "6";
        }
        else if (arr.substring(0, 5) == "tanh(") {
          if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 5);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 4;
          functions += "c";
        }
        else if (arr.substring(0, 8) == "tetrate(") {
          if (!isdigit(equation[i + 8]) && equation[i + 8] != '-' && !validateConstantFirstChar(equation[i + 8])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 8);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 7;
          functions += "B";
        }
        else {
          a.innerHTML = "Invalid input";
          return;
        }
      }
      else if (equation[i] == 'f') {
        if (equation.substring(0, 6) == "floor(") {
          if (!isdigit(equation[i + 6]) && equation[i + 6] != '-' && !validateConstantFirstChar(equation[i + 6])) {
            a.innerHTML = "Invalid input";
            return;
          }
          equation = removeChar(equation, i - 1, 6);
          functionPositions[numberOfFunctions] = i;
          numberOfFunctions++;
          i += 5;
          functions += "t";
        }
      }
      else if (equation[i] == 'E' || equation[i] == 'e' || equation[i] == 'x');
      else {
        a.innerHTML = "Invalid input";
        return;
      }
    }
  }
  equation = setUp(equation);
  if (equation == "NAN") {
    a.innerHTML = "Invalid input";
    return;
  }
  times = numberOfOperations(equation);
  
  var operations = '';
  var operationPositions = new Array(times);
  var numberOfOperationsLeadingUpToFunction = new Array(times).fill(0);
  var operationPositionIndex = 0, numberOfSeperators = 0;
  var positions = new Array(times + 1).fill(0);
  
  for (let i = 0; i < equation.length; i++) {
    if (validateOperation(equation[i]) == 0) {
      if (equation[i] == '-' && isdigit(equation[i + 1]) && !isdigit(equation[i - 1])) {
        continue;
      }
      operations += equation[i];
      operationPositions[operationPositionIndex] = i;
      operationPositionIndex++;
      if (equation[i] != ',') {
        numberOfOperationsLeadingUpToFunction[functions.length]++;
      }
      else {
        numberOfSeperators++;
        if (functions.length < numberOfSeperators) {
          a.innerHTML = "Invalid Input";
          return;
        }
      }
    }
  }
  var seperatorPositions = new Array(numberOfSeperators);
  numberOfSeperators = 0;
  for (let i = 0; i < equation.length; i++)
  {
    if (isdigit(equation[i]))
    {
      if (i > 0)
      {
        if (!isdigit(equation[i - 1]) && equation[i - 1] != 'm' && equation[i - 1] != '.')
        {
          positions[posIndex] = i;
          posIndex++;
        }
      }
      else
      {
        if (validateConstantChar(equation[i]) && equation[i] != ' ')
        {
          positions[posIndex] = i;
          posIndex++;
        }
      }
    }
    else
    {
      if (equation[i] == '-' && isdigit(equation[i + 1]) && !isdigit(equation[i - 1]))
      {
        equation = equation.substring(0, i) + 'm' + equation.substring(i + 1);
        positions[posIndex] = i;
        posIndex++;
      }
      else if (validateConstantChar(equation[i]))
      {
        positions[posIndex] = i;
        posIndex++;
      }
    }
  }
  positions.sort((a, b) => a - b);
  var nums = new Array(times + 1).fill(0);
  for (let i = 0; i < times + 1; i++) {
    nums[i] = convertFloat(equation, positions[i], equation.length);
    if (operations[i] == ',') {
      seperatorPositions[numberOfSeperators] = i;
      numberOfSeperators++;
    }
  }
  var location = 0;
  functions = functions.toString();
  for (let i = 0, negative = 1; i < numberOfFunctions; i++) {
    for (let j = 0; j < times + 1; j++) {
      if (functionPositions[i] < positions[j]) {
        if (isFunctionWithTwoArgs(functions[i])) {
          if (functionPositions[i] >= operationPositions[j - 1] && numberOfOperationsLeadingUpToFunction[i] >= 0) {
            if (operationPositionIndex >= 1) {
              if (positions[j] <= operationPositions[j] && operations[j] == ',') {
                location = j;
                break;
              }
              else {
                a.innerHTML = "Invalid input";
                return;
              }
            }
            else {
              location = j;
              break;
            }
          }
          else if (operations[j] == ',') {
            break;
          }
          else {
            a.innerHTML = "Invalid input";
            return;
          }
        }
        else {
          if (functionPositions[i] < positions[j]) {
            location = j;
            break;
          }
        }
      }
    }
    //nth root
    if (functions[i] == '0') {
      if (nums[location] < 0 && nums[location + 1] % 2 != 0) {
        nums[location] *= -1;
        if (nums[location + 1] == Math.floor(nums[location + 1])) {
          negative = -1;
        }
      }
      nums[location + 1] = Math.pow(nums[location], 1 / nums[location + 1]);
      nums[location] = setNum(operations, seperatorPositions[i], nums[location]);
      nums[location + 1] *= negative;
    }
    //log
    else if (functions[i] == '1') {
      nums[location + 1] = log_base(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, seperatorPositions[i], nums[location]);
    }
    //GCD
    else if (functions[i] == '2') {
      if (nums[location] != Math.floor(nums[location]) || nums[location + 1] != Math.floor(nums[location + 1])) {
        a.innerHTML = "Invalid input";
        return;
      }
      nums[location + 1] = calculateGCD(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, seperatorPositions[i]);
    }
    //LCM
    else if (functions[i] == '3') {
      if (nums[location] != Math.floor(nums[location]) || nums[location + 1] != Math.floor(nums[location + 1])) {
        a.innerHTML = "Invalid input";
        return;
      }
      nums[location + 1] = Math.abs(nums[location] * nums[location + 1]) / calculateGCD(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, seperatorPositions[i]);
    }
    //sin
    else if (functions[i] == '4') {
      if (nums[location] == 3.141592653) {
        nums[location] = 0;
      }
      else {
        nums[location] = Math.sin(nums[location]);
      }
    }
    //cos
    else if (functions[i] == '5') {
      nums[location] = Math.cos(nums[location]);
    }
    //tan
    else if (functions[i] == '6') {
      nums[location] = Math.tan(nums[location]);
    }
    //cosecant
    else if (functions[i] == '7') {
      nums[location] = cosec(nums[location]);
    }
    //secant
    else if (functions[i] == '8') {
      nums[location] = sec(nums[location]);
    }
    //cotangent
    else if (functions[i] == '9') {
      nums[location] = cot(nums[location]);
    }         
    //sinh
    else if (functions[i] == 'a') {
      nums[location] = Math.sinh(nums[location]);
    }
    //cosh
    else if (functions[i] == 'b') {
      nums[location] = Math.cosh(nums[location]);
    }
    //tanh
    else if (functions[i] == 'c') {
      nums[location] = Math.tanh(nums[location]);
    }
    //arcsin
    else if (functions[i] == 'd') {
      nums[location] = Math.asin(nums[location]);
    }
    //arccos
    else if (functions[i] == 'e') {
      nums[location] = Math.acos(nums[location]);
    }
    //arctan
    else if (functions[i] == 'f') {
      nums[location] = Math.atan(nums[location]);
    }
    //arcsinh
    else if (functions[i] == 'g') {
      nums[location] = Math.asinh(nums[location]);
    }
    //arccosh
    else if (functions[i] == 'h') {
      nums[location] = Math.acosh(nums[location]);
    }
    //arctanh
    else if (functions[i] == 'i') {
      nums[location] = Math.atanh(nums[location]);
    }
    //sinc
    else if (functions[i] == 'j') {
      nums[location] = sinc(nums[location]);
    }
    //sqrt
    else if (functions[i] == 'k') {
      nums[location] = Math.sqrt(nums[location]);
    }
    //cbrt
    else if (functions[i] == 'l') {
      nums[location] = Math.cbrt(nums[location]);
    }
    //square
    else if (functions[i] == 'm') {
      nums[location] *= nums[location];
    }
    //cube
    else if (functions[i] == 'n') {
      nums[location] *= nums[location] * nums[location];
    }
    //natural log
    else if (functions[i] == 'o') {
      nums[location] = Math.log(nums[location]);
    }
    //log base 10
    else if (functions[i] == 'p') {
      nums[location] = Math.log10(nums[location]);
    }
    //binary log
    else if (functions[i] == 'q') {
      nums[location] = Math.log2(nums[location]);
    }
    //abs
    else if (functions[i] == 'r') {
      nums[location] = Math.abs(nums[location]);
    }
    //ceil
    else if (functions[i] == 's') {
      nums[location] = Math.ceil(nums[location]);
    }
    //floor
    else if (functions[i] == 't') {
      nums[location] = Math.floor(nums[location]);
    }
    //iterative log
    else if (functions[i] == 'A') {
      nums[location + 1] = iterative_log(nums[location], nums[location + 1]);
      nums[location] = setNum(operations, seperatorPositions[i]);
    }
    //tetration
    else if (functions[i] == 'B') {
      if (Math.floor(nums[location + 1]) != nums[location + 1]) {
        a.innerHTML = "Invalid input";
        return;
      }
      var exponent = nums[location];
      for (let j = 0; j < nums[location + 1] - 1; j++) {
        exponent = Math.pow(nums[location], exponent);
      }
      nums[location + 1] = exponent;
      nums[location] = setNum(operations, seperatorPositions[i]);
    }
  }
  //E
  for (let i = 0; i < times; i++) {
    if (operations[i] == 'e') {
      if (Math.floor(nums[i + 1]) != nums[i + 1]) {
        a.innerHTML = "Invalid input";
        return;
      }
      nums[i + 1] = Math.floor(nums[i] *  Math.floor(10, nums[i + 1]));
      nums[i] = 0 + 1 * (operations[i + 1] == '*' || operations[i + 1] == '/');
      operations = setOperation(operations, i);
    }
  }
  //Modulo operation
  for (let i = 0; i < times; i++) {
    if (operations[i] == '%') {
      nums[i + 1] = nums[i] % nums[i + 1];
      nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
      operations = setOperation(operations, i);
    }
    else if (operations[i] == ',') {
      operations = setOperation(operations, i);
    }
  }
  //Exponents
  for (let i = 0; i < times; i++)
  {
    if (operations[i] == '^')
    {
      nums[i + 1] = Math.pow(nums[i], nums[i + 1]);
      nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
      operations = setOperation(operations, i);
    }
  }
  //nCr, nPr
  for (let i = 0; i < times; i++) {
    if (operations[i] == 'C')
    {
      if (Math.floor(nums[i]) != nums[i] || Math.floor(nums[i + 1]) != nums[i + 1]) {
        a.innerHTML = "Invalid input";
        return;
      }
      nums[i + 1] = gamma(nums[i] + 1) / (gamma(nums[i + 1] + 1) * gamma(nums[i] - nums[i + 1] + 1));
      total += nums[i + 1];
      nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
      operations = setOperation(operations, i);
    }
    else if (operations[i] == 'P')
    {
      if (Math.floor(nums[i]) != nums[i] || Math.floor(nums[i + 1]) != nums[i + 1]) {
        a.innerHTML = "Invalid input";
        return;
      }
      nums[i + 1] = gamma(nums[i] + 1) / gamma(nums[i] - nums[i + 1] + 1);
      total += nums[i + 1];
      nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
      operations = setOperation(operations, i);
    }
  }
  //Multiplication, Division
  for (let i = 0; i < times; i++) {
    if (operations[i] == '*')
    {
      nums[i + 1] *= nums[i];
      nums[i] = 0;
      operations = setOperation(operations, i);
    }
    else if (operations[i] == '/')
    {
      nums[i] /= nums[i + 1];
      nums[i + 1] = nums[i];
      nums[i] = 0;
      operations = setOperation(operations, i);
    }
  }
  //Assign total first non-zero term of nums
  for (let i = 0; i < times + 1; i++) {
    if (nums[i] != 0) {
      total = nums[i];
      break;
    }
  }
  //Addition, Subtraction
  for (let i = 0; i < times; i++) {
    if (operations[i] == '+') {
      total += nums[i + 1];  
    }
    else if (operations[i] == '-') {
      total -= nums[i + 1];
    }
  }
  a.innerHTML = `Result = ${total}`;
}
