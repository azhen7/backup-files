function primeFactor(num) {
  var a = document.getElementById('result');
  a.innerHTML = "";
  num = validateInput(num);
  if (num == -1) {
    a.innerHTML = "Invalid input";
    return;
  }
  var primeFactors = getPrimeFactors(num);
  var exponentsOfPrimeFactors = getExponentsOfPrimeFactors(num);
  var n = getNumberOfPrimeFactors(num);
  a.innerHTML += `${num.toString()} = `;
  for (let i = 0; i < n - 1; i++) {
    if (exponentsOfPrimeFactors[i] == 1) {
      a.innerHTML += `${primeFactors[i].toString()} x `;
    }
    else {
      a.innerHTML += `${primeFactors[i].toString()}${exponentsOfPrimeFactors[i].toString().sup()} x `;
    }
  }
  if (exponentsOfPrimeFactors[n - 1] == 1) {
      a.innerHTML += `${primeFactors[n - 1].toString()}`;
  }
  else {
    a.innerHTML += `${primeFactors[n - 1].toString()}${exponentsOfPrimeFactors[n - 1].toString().sup()}`;
  }
}
