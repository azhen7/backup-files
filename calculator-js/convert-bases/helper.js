//Convert input to base 10
function convertBaseTen(input, base_input) {
  var decimal = 0;
  var addToDecimal = 0;
  
  if (typeof base_input != 'number') {
    return NaN;
  }
  
  if (base_input === 10) {
    decimal = parseInt(input);
  }
  else {
    for (let i = 0, n = input.length; i < n; i++) {
      if (isdigit(input[i])) {
        addToDecimal = input[i].charCodeAt() - 48;
        addToDecimal *= Math.pow(base_input, n - i - 1);
        decimal += addToDecimal;
      }
      else if (isalpha(input[i])) {
        if (isupper(input[i])) {
          addToDecimal = input[i].charCodeAt() - 55;
          addToDecimal *= Math.pow(base_input, n - i - 1);
          decimal += addToDecimal;
        }
        else if (islower(input[i])) {
          addToDecimal = input[i].charCodeAt() - 87;
          addToDecimal *= Math.pow(base_input, n - i - 1);
          decimal += addToDecimal;
        }
      }
    }
  }
  return decimal;
}
//Reverse input
function invert_letters(input) {
  var invertedStr = "";
  for (let i = input.length - 1; i >= 0; i--) {
    invertedStr += input[i];
  }
  return invertedStr;
}
//Validate input
function validateInput(input, base_input) {
  var addToDecimal;
  for (let i = 0; i < input.length; i++) {
    if (isdigit(input[i])) {
      addToDecimal = input[i].charCodeAt() - 48;
      if (addToDecimal > base_input - 1) {
        return 0;
      }
    }
    else if (isalpha(input[i])) {
      if (base_input <= 10) {
        return 0;
      }
      else {
        if (islower(input[i])) {
          if (input[i].charCodeAt() - 87 > base_input - 1) {
            return 0;
          }
        }
        else if (isupper(input[i])) {
          if (input[i].charCodeAt - 55 > base_input - 1) {
            return 0;
          }
        }
      }
    }
    else {
      return 0;
    }
  }
  return 1;
}
function validate_base(base_input) {
  if (base_input.length == 0) {
    return -1;
  }
  for (let i = 0; i < base_input.length; i++) {
    if (!isdigit(base_input[i])) {
      return -1;
    }
  }
  console.log(parseInt(base_input));
  if (parseInt(base_input) < 2) {
    return -1;
  }
  if (parseInt(base_input) > 36) {
    return -1;
  }
  return parseInt(base_input);
}
