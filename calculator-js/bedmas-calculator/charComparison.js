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
  if (c === "×") return 0;
  if (c == '<' || c == '>' || c == '?' || c == '@' || c == '#' || c == '$' || c == '&' || c == '{' || c == '}' || c == '[' || c == ']'
     || c == '"' || c == ';' || c == ':' || c == '`' || c == '_' || c.charCodeAt() > 127)
    return 1;
  return 0;
}
