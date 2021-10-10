import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
const [K, N] = nextLine().split(' ').map(n => parseInt(n));
const array: Array<number> = [];
for (let i = 0; i < K; i++) {
  array.push(parseInt(nextLine()));
}

let minAnswer = 1;
let maxAnswer = Math.pow(2, 31) - 1;

// find the answer 
while (minAnswer <= maxAnswer) {
  const midAnswer = Math.floor((minAnswer + maxAnswer) / 2);
  let sum = 0;
  for (const n of array) {
    sum += Math.floor(n / midAnswer);
  }
  if (sum >= N) {
    minAnswer = midAnswer + 1;
  } else {
    maxAnswer = midAnswer - 1;
  }
}

// print the answer
console.log(maxAnswer);
