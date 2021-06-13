function convert(input, base_input, base_convert) {
  console.clear();
  var converted_value = document.getElementById('converted-value');
  base_input = validate_base(base_input);
  base_convert = validate_base(base_convert);
  if (base_input == -1) {
    if (base_convert == -1) {
      //If all three input boxes are empty
      if (input.length == 0) {
        converted_value.innerHTML = "Invalid input, base of input and base to convert to";
        return;
      }
      //If the base_input and base_convert input boxes are empty
      else {
        converted_value.innerHTML = "Invalid base of input and base to convert to";
        return;
      }
    }
    //If the base_input box is empty
    else {
      converted_value.innerHTML = "Invalid base of input";
    }
  }
  if (base_convert == -1) {
    //If the input and base_convert boxes are empty
    if (input.length == 0) {
      converted_value.innerHTML = "Invalid input and base to convert to";
      return;
    }
    //If the base_convert box is empty
    else {
      converted_value.innerHTML = "Invalid base to convert to";
      return;
    }
  }
  
  var decimalForm = 0;
  var addToDecimal;
  if (!validateInput(input, base_input)) {
    converted_value.innerHTML = "Invalid input";
    return;
  }
  decimalForm = convertBaseTen(input, base_input);
  
  var result = '';
  
  if (base_convert != base_input) {
    if (base_convert == 10) {
      result = decimalForm.toString();
    }
    else {
      var temp = '0';
      var mod;
      var times = 0;
      
      addToDecimal = decimalForm;
      while (Math.floor(addToDecimal) != 0) {
        times++;
        addToDecimal /= base_convert;
      }
      times++;
      for (let i = 0; i < times && Math.floor(decimalForm) != 0; i++) {
        mod = decimalForm % base_convert;
        decimalForm /= base_convert;
        
        if (mod >= 10) {
          temp = String.fromCharCode(mod + 55);
        }
        else {
          temp = String.fromCharCode(mod + 48);
        }
        result += temp;
      }
      result = invert_letters(result);
    }
  }
  else {
    result = input;
  }
  if (base_convert == 16) {
    converted_value.innerHTML = `0x${result}`;
  }
  else {
    converted_value.innerHTML = `${result}${base_convert.toString().sub()}`;
  }
}
