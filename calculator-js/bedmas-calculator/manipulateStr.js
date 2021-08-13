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
        return null;
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
        return null;
      }
    }
    else if (copy[i] == '*') {
      //copy = copy.substring(0, i) + '*' + copy.substring(i + 1);
      if (i == 0) {
        return null;
      }
      if (i > 0) {
        if (copy[i - 1] == '/') {
          return null;
        }
      }
      if (copy[i + 1] == '*') {
        copy = copy.substring(0, i) + '^' + copy.substring(i + 2);
      }
      else if (isCharExceptions(copy[i + 1]) || copy[i + 1] == '-');
      else {
        return null;
      }
    }
    else if (copy[i] == '/') {
      if (i == 0) {
        return null;
      }
      if (isCharExceptions(copy[i + 1]) || copy[i + 1] == '-');
      else {
        return null;
      }
    }
    else if (copy[i] == '!') {
      if (i == 0) {
        return null;
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
