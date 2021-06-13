//Checks whether c is a letter (a - z or A - Z)
function isalpha(c) {
  if (c == ' ') {
    return 0;
  }
  if (c.toLowerCase() != c.toUpperCase()) {
    return 1;
  }
  return 0;
}
//Checks whether c is a digit (0 - 9)
function isdigit(c) {
  if (c == ' ')
    return 0;
  if (c >= '0'.charCodeAt() || c <= '9'.charCodeAt())
    return 1;
  return 0;
}
//Checks whether c is a lowercase letter
function islower(c) {
  if (c == ' ') {
    return 0;
  }
  if (c >= 'a'.charCodeAt() && c <= 'z'.charCodeAt()) {
    return 1;
  }
  return 0;
}
//Checks whether c is a uppercase letter
function isupper(c) {
  if (c == ' ') {
    return 0;
  }
  if (c >= 'A'.charCodeAt() && c <= 'Z'.charCodeAt()) {
    return 1;
  }
  return 0;
}
