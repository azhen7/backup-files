let mode = 1;
let cursorPos = 0;
let multiplySign = [
  "×",
  "nPr",
  "GCD("
];
let divideSign = [
  "/",
  "nCr",
  "LCM("
];
let inbuilt_logs = [
  "log(",
  "log10(",
  "ln("
];
let inbuilt_powers = [
  "x²",
  "x³",
  ""
];
let sin = [
  "sin(",
  "csc(",
  "arcsin("
];
let cos = [
  "cos(",
  "sec(",
  "arccos("
];
let tan = [
  "tan(",
  "cot(",
  "arctan("
];

let functions = [
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
  "sin(", "cos(", "tan(",
  "sinh(", "cosh(", "tanh(",
  "arcsin(",
  "arccos(",
  "arctan(",
  "arcsinh(",
  "arccosh(",
  "arctanh(",
  "log(", "LOG(",
  "ln(", "LN(",
  "log10(", "LOG10(",
  "log2(", "LOG2(",
  "cot(", "csc(", "sec(",
  "sinc(", "log*(", "LOG*(",
  "LCM(", "GCD(", 
  "root(", "tetrate(",
  "square(", "cube(",
  "sqrt(", "cbrt(",
  "floor(", "ceil(", "round(",
  "abs(", ","
];
let superscriptReplacementText = [
  "⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹",
  "ˢᶦⁿ⁽", "ᶜᵒˢ⁽", "ᵗᵃⁿ⁽",
  "ˢᶦⁿʰ⁽", "ᶜᵒˢʰ⁽", "ᵗᵃⁿʰ⁽",
  "ᵃʳᶜˢᶦⁿ⁽",
  "ᵃʳᶜᶜᵒˢ⁽",
  "ᵃʳᶜᵗᵃⁿ⁽",
  "ᵃʳᶜˢᶦⁿʰ⁽",
  "ᵃʳᶜᶜᵒˢʰ⁽",
  "ᵃʳᶜᵗᵃⁿʰ⁽",
  "ˡᵒᵍ⁽", "ᴸᴼᴳ⁽",
  "ˡⁿ⁽", "ᴸᴺ⁽",
  "ˡᵒᵍ¹⁰⁽", "ᴸᴼᴳ¹⁰⁽",
  "ˡᵒᵍ²⁽", "ᴸᴼᴳ²⁽",
  "ᶜᵒᵗ⁽", "ᶜᵒˢᵉᶜ⁽", "ˢᵉᶜ⁽",
  "ˢᶦⁿᶜ⁽", "ˡᵒᵍ*⁽", "ᴸᴼᴳ*⁽",
  "ᴸᶜᴹ⁽", "ᴳᶜᴰ⁽", 
  "ʳᵒᵒᵗ⁽", "ᵗᵉᵗʳᵃᵗᵉ⁽",
  "ˢᵠᵘᵃʳᵉ⁽", "ᶜᵘᵇᵉ⁽",
  "ˢᵠʳᵗ⁽", "ᶜᵇʳᵗ⁽",
  "ᶠˡᵒᵒʳ⁽", "ᶜᵉᶦˡ⁽", "ʳᵒᵘⁿᵈ⁽",
  "ᵃᵇˢ⁽", "𝄒"
];
let actualEquation = '';
let superScript = 0;

//Clear input textbox
function clrscr() {
  equation.value = "";
  actualEquation = "";
  cursorPos = 0;
  setMode(1);
}
//Add character(s) to equation
function addToEquation(val) {
  let visualStr = equation.value.substring(0, cursorPos);
  let restOfVisualStr = equation.value.substring(cursorPos);
  let str = actualEquation.substring(0, cursorPos + superScript);
  let restOfStr = actualEquation.substring(cursorPos + superScript);
  if (isOgOperation(val) && val !== "^") {
    superScript = 0;
  }
  if (val === "")
    return;
  if (val === "^") {
    str += val;
    superScript = 1;
  }
  else if (val === '×') {
    visualStr += '×';
    str += '*';
  }
  else if (inbuilt_powers.includes(val)) {
    addToEquation("^");
    let num = inbuilt_powers.indexOf(val) + 2;
    addToEquation(num.toString());
    superScript = 0;
  }
  else {
    if (superScript === 1 && functions.includes(val)) {
      let i = functions.indexOf(val)
      visualStr += superscriptReplacementText[i];
      str += val;
    }
    else {
      visualStr += val;
      str += val;
    }
  }
  visualStr += restOfVisualStr;
  str += restOfStr;
  equation.value = visualStr;
  actualEquation = str;
  if (val !== "^") {
    cursorPos += val.length;
  }
}
//Remove last char
function removeLastChar() {
  if (equation.value === "")
      return;
  if (cursorPos === 0) {
    increase();
  }
  let str = actualEquation.substring(0, cursorPos + 1);
  let restOfStr = actualEquation.substring(cursorPos + 1);
  let lastChar = str[str.length - 1];
  let less = 1;
  let lessForVisual = 1;
  if (lastChar === "^") {
    superScript = 0;
    lessForVisual = -1;
  }
  else if (lastChar === '(') {
    less = getSubtractVal(functions, [], lastChar, str);
    lessForVisual = less;
  }
  else if (isalpha(lastChar)) {
    less = getSubtractVal(mathConsts, ["nPr", "nCr"], lastChar, str);
    lessForVisual = less;
  }
  let visibleStr = equation.value;
  let restOfVisibleStr = visibleStr.substring(cursorPos)
  visibleStr = visibleStr.substring(0, cursorPos);
  equation.value = visibleStr.substring(0, visibleStr.length - lessForVisual) + restOfVisibleStr;
  actualEquation = actualEquation.substring(0, str.length - less) + restOfStr;
  if (actualEquation[actualEquation.length - 1] === "^") {
    superScript = 0;
    actualEquation = actualEquation.substring(0, actualEquation.length - 1);
  }
  setMode(1);
  cursorPos -= lessForVisual;
}
//Set the mode to val. Update dynamic value buttons accordingly
function setMode(val) {
  mode = val;
  setOperation(mode - 1);
}
//Set the value of buttons depending on the "mode"
function setAddValue(str) {
  let index = mode - 1;
  let s = eval(str);
  addToEquation(s[index]);
}
//Set value of dynamic button to index of array
function setOperation(index) {
  let indicesForArrays = 0;
  let valOfArray = '';
  let arrays = [
    multiplySign, 
    divideSign, 
    inbuilt_logs, 
    inbuilt_powers,
    sin, cos, tan
  ];
  let names = [
    "multiplySign",
    "divideSign",
    "inbuilt_logs",
    "inbuilt_powers",
    "sin", "cos", "tan"
  ];
  for (let i = 0; i < arrays.length; i++) {
    indicesForArrays = index;
    if (indicesForArrays >= arrays[i].length) {
      indicesForArrays = arrays[i].length - 1;
    }
    document.getElementById(names[i]).value = arrays[i][indicesForArrays];
  }
}
//Decrease cursor position
function decrease() {
  if (cursorPos === 0)
      return;
  let str = equation.value;
  str = str.substring(0, cursorPos);
  let lastChar = str[str.length - 1];
  let less = 1;
  if (lastChar === '(') {
    less = getSubtractVal(functions, [], lastChar, str);
    console.log(less)
  }
  else if (isalpha(lastChar)) {
    less = getSubtractVal(mathConsts, ["nPr", "nCr"], lastChar, str);
  }
  cursorPos -= less;
}
//Increase cursor position
function increase() {
  if (cursorPos === equation.value.length)
    return;
  let firstChar = equation.value.charAt(cursorPos);
  if (isalpha(firstChar)) {
    let s = firstChar;
    let lookback = 1;
    while (equation.value.charAt(cursorPos + lookback) !== '(' && !mathConsts.includes(s)) {
      s += equation.value.charAt(cursorPos + lookback);
      lookback++;
    }
    if (!mathConsts.includes(s)) s += "(";
    cursorPos += s.length;
  }
  else if (firstChar === "^") {
    increase();
  }
  else
    cursorPos++;
}
let isOgOperation = (c) => {
  if (c === '+' || c === '-' || c === 'x' || c === '/'
      || c === '^' || c === '^' || c === '!' || c === 'nPr' || c === 'nCr'
      || c == '%' || c == 'e')
    return 1;
  return 0;
};
