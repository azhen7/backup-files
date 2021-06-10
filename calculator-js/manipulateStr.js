//Contains all the string-related functions
//Check whether c is indicative of function which requires two arguments (e.g. GCD, LCM, log, root, etc.)
function isFunctionWithTwoArgs(c) {
  if ((c >= '0'.charCodeAt() && c <= '3'.charCodeAt()) || (c >= 'A'.charCodeAt() && c <= 'B'.charCodeAt)) {
    return 1;
  }
  return 0;
}
/* Check whether c is an operation */
function validateOperation(c) {
  if (c == '+' || c == '*' || c == '-' || c == '/' || c == '^' || c == '%' || c == 'e' || c == 'C' || c == 'P' || c == ',' || c == 'x') {
    return 0;
  }
  return 1;
}
/* Check whether char is representative of a math constant (e.g. PI) */
function validateConstantChar(c) {
  if (c == '!' || c == 'T' || c == 'R' || c == 'G' || c == 'E' || c == 'Y' || c == 'A')
      return 1;
  return 0;
}
/* Check whether char is first character of a math constant (e.g. PI) */
function validateConstantFirstChar(c) {
  if (c == 'P' || c == 'G' || c == 'S' || c == 'R' || c == 'A' || c == 'C' || c == 'p' || c == 's')
      return 1;
  return 0;
}
/* Validate char */
function validNext(c) {
  if (isdigit(c) || c == 'm' || c == ' ' || c == '-' || validateConstantChar(c))
      return 0;
  return 1;
}
/* Copy string without spaces */
function copyStrWithoutSpaces(input) {
  var strWithoutSpaces = '';
  for (let x = 0; x < input.length; x++) {
    if (input[x] != ' ') {
      strWithoutSpaces += input[x];
    }
  }
  return strWithoutSpaces;
}
/* Replaces characters with spaces */
function removeChar(input, index, c) {
  var changedStr = input.substring(0, index + 1);
  for (let i = 0; i < c; i++) {
    changedStr[index + 1 + i] += ' ';
  }
  changedStr += input.substring(index + c + 1);
  return changedStr;
}
/* Validate string */
function isValidInput(input) {
  if (input.length == 0) {
    return 1;
  }
  for (let x = 0; x < input.length; x++) {
    if (input[x] != ' ') {
      return 1;
    }
  }
  return 0;
}
/* Set up string */
function setUp(input) {
  var copy = input;
  for (let i = 0; i < copy.length; i++) {
    if (copy[i] == '+') {
      if (copy[i + 1] == '-') {
        copy = copy.substring(0, i) + '-' + copy.substring(i + 2);
      }
      else if (isdigit(copy[i + 1]) || copy[i + 1] == ' ');
      else {
        copy = "NAN";
        break;
      }
    }
    else if (copy[i] == '-') {
      if (copy[i + 1] == '-') {
        copy = copy.substring(0, i) + '+' + copy.substring(i + 2);
      }
      else if (copy[i + 1] == '+') {
        copy = copy.substring(0, i) + copy.substring(i + 1);
      }
      else if (isdigit(copy[i + 1]) || copy[i + 1] == ' ');
      else {
        copy = "NAN";
        break;
      }
    }
    else if (copy[i] == '*' || copy[i] == 'x') {
      copy = copy.substring(0, i) + '*' + copy.substring(i + 1);
      if (i > 0)
      {
        if (copy[i + 1] == '/')
        {
            copy = "NAN";
            break;
        }
      }
      else {
        document.getElementById('result').innerHTML = "Invalid input";
        return;
      }
      if (copy[i + 1] == '*') {
        copy = copy.substring(0, i) + '^' + copy.substring(i + 2);
      }
      else if (copy[i + 1] == '+') {
        copy = copy.substring(0, i) + '-' + copy.substring(i + 1);
      }
      else if (isdigit(copy[i + 1]) || copy[i + 1] == '-' || copy[i + 1] == ' ');
      else
      {
        copy = "NAN";
        break;
      }
    }
    else if (copy[i] == '/') {
      if (i == 0) {
        document.getElementById('result').innerHTML = "Invalid input";
        return;
      }
      if (copy[i + 1] == '*')
      {
        copy = "NAN";
        break;
      }
    }
  }
  return copy;
}
//Set current operation to be the previous one
function setOperation(operations, index) {
  var changedStrOperations = '';
  if (index > 0) {
    if (operations[index - 1] != 'C' && operations[index - 1] != 'P') {
      changedStrOperations = operations.substring(0, index) + operations[index - 1] + operations.substring(index + 1);
    }
  }
  return changedStrOperations;
}
