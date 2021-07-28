//Contains all the string-related functions
function isCharExceptions(c) {
  if (isdigit(c) || validateConstantChar(c) || c == ')' || c == ' ')
    return 1;
  return 0;
}
//Check whether c is indicative of function which requires two arguments (e.g. GCD, LCM, log, root, etc.)
function isFunctionWithTwoArgs(c) {
  if ((c.charCodeAt() >= '0'.charCodeAt() && c.charCodeAt() <= '3'.charCodeAt()) || (c >= 'A'.charCodeAt() && c <= 'B'.charCodeAt)) {
    return 1;
  }
  return 0;
}
// Check whether c is an operation 
function validateOperation(c) {
  if (c == '+' || c == '*' || c == '-' || c == '/' || c == '^' || c == '%' || c == 'e' || c == 'C' || c == 'P' || c == ',' || c == 'x' ||
      c == '!') {
    return 0;
  }
  return 1;
}
// Check whether char is representative of a math constant (e.g. PI) 
function validateConstantChar(c) {
  if (c == 'Z' || c == 'T' || c == 'R' || c == 'G' || c == 'E' || c == 'Y')
      return 1;
  return 0;
}
// Check whether char is first character of a math constant (e.g. PI) 
function validateConstantFirstChar(c) {
  if (c == 'P' || c == 'G' || c == 'S' || c == 'R' || c == 'C' || c == 'p' || c == 's')
      return 1;
  return 0;
}
// Validate char
function validNext(c) {
  if (isdigit(c) || c == 'm' || c == ' ' || c == '-' || validateConstantChar(c) || validateOperation(c))
      return 0;
  return 1;
}
// Check if char is not valid
function invalidChars(c) {
  if (c == '<' || c == '>' || c == '?' || c == '@' || c == '#' || c == '$' || c == '&' || c == '{' || c == '}' || c == '[' || c == ']'
     || c == '"' || c == ';' || c == ':' || c == '`' || c == '_' || c.charCodeAt() > 127)
    return 1;
  return 0;
}
// Replaces characters with spaces 
function removeChar(input, index, c) {
  let changedStr = input.substring(0, index + 1);
  for (let i = 0; i < c; i++) {
    changedStr += " ";
  }
  changedStr += input.substring(index + c + 1);
  return changedStr;
}
// Validate string 
function isValidInput(input) {
  if (input.length == 0) {
    return 0;
  }
  return 1;
}
// Set up string 
function setUp(input) {
  let copy = input;
  for (let i = 0; i < copy.length; i++) {
    if (copy[i] == '+') {
      if (copy[i + 1] == '-' || copy[i + 1] == '+') {
        copy = copy.substring(0, i) + copy[i + 1] + copy.substring(i + 2);
      }
      else if (isCharExceptions(copy[i + 1]));
      else {
        return "NAN";
      }
    }
    else if (copy[i] == '-') {
      if (copy[i + 1] == '-') {
        copy = copy.substring(0, i) + '+' + copy.substring(i + 2);
      }
      else if (copy[i + 1] == '+') {
        copy = copy.substring(0, i) + copy.substring(i + 1);
      }
      else if (isCharExceptions(copy[i + 1]));
      else {
        return "NAN";
      }
    }
    else if (copy[i] == '*' || copy[i] == 'x') {
      copy = copy.substring(0, i) + '*' + copy.substring(i + 1);
      if (i == 0) {
        return "NAN";
      }
      if (i > 0) {
        if (copy[i - 1] == '/') {
          return "NAN";
        }
      }
      if (copy[i + 1] == '*') {
        copy = copy.substring(0, i) + '^' + copy.substring(i + 2);
      }
      else if (isCharExceptions(copy[i + 1]) || copy[i + 1] == '-');
      else {
        return "NAN";
      }
    }
    else if (copy[i] == '/') {
      if (i == 0) {
        return "NAN";
      }
      if (isCharExceptions(copy[i + 1]) || copy[i + 1] == '-');
      else {
        return "NAN";
      }
    }
    else if (copy[i] == '!') {
      if (i == 0) {
        return "NAN";
      }
    }
  }
  return copy;
}

function verifyValidCharAfterFunction(equation, i, addIndex) {
  if (equation[i + addIndex] == undefined)
    return 0;
  if (isdigit(equation[i + addIndex]) || equation[i + addIndex] == '-' || validateConstantFirstChar(equation[i + addIndex]))
    return 1;
  return 0;
}
