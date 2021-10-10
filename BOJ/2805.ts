import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
const [N, M] = nextLine().split(' ').map(n => parseInt(n));
const array: Array<number> = nextLine().split(' ').map(n => parseInt(n));

let minAnswer = 0;
let maxAnswer = 1_000_000_000;

// find the answer 
while (minAnswer <= maxAnswer) {
  const midAnswer = Math.floor((minAnswer + maxAnswer) / 2);
  let sum = 0;
  for (const n of array) {
    sum += Math.max(n - midAnswer, 0);
  }
  if (sum >= M) {
    minAnswer = midAnswer + 1;
  } else {
    maxAnswer = midAnswer - 1;
  }
}

// print the answer
console.log(maxAnswer);
