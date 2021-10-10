import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
nextLine();
const A: Array<number> = nextLine().split(' ').map(n => parseInt(n));

const endNumbers: Array<number> = [0];

for (const n of A) {
  const maxEndNumber = endNumbers[endNumbers.length - 1];
  if (n >= maxEndNumber) {
    // n is end-number
    if (n > maxEndNumber) {
      endNumbers.push(n);
    }
    continue;
  }

  // find the minimum end-number bigger than n
  // by using binary search
  let left = 0;
  let right = endNumbers.length - 1;
  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    if (endNumbers[mid] < n) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  // update end-number
  const index = left;
  endNumbers[index] = n;
}

// print the answer
console.log(endNumbers.length - 1);
