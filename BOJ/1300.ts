import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
const N = parseInt(nextLine());
const K = parseInt(nextLine());

let minAnswer = 1;
let maxAnswer = K;

// find the answer 
while (minAnswer <= maxAnswer) {
  const midAnswer = Math.floor((minAnswer + maxAnswer) / 2);

  let integral = 0;
  for (let i = Math.min(midAnswer, N); i > 0; i--) {
    integral += Math.min(N, Math.floor(midAnswer / i));
  }

  if (integral < K) {
    minAnswer = midAnswer + 1;
  } else {
    maxAnswer = midAnswer - 1;
  }
}

// print the answer
console.log(minAnswer);
