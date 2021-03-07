import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
const N: number = parseInt(nextLine()); // the size of array
const A: Array<number> = nextLine().split(' ').map(n => parseInt(n));
const leftMaxGaps: Array<number> = Array(N);
const rightMaxGaps: Array<number> = Array(N);

// calculate left part
let min_before = A[0];
leftMaxGaps[0] = -Infinity;
for (let i = 1; i < N - 2; i++) {
  leftMaxGaps[i] = Math.max(leftMaxGaps[i - 1], A[i] - min_before);

  // update minimum
  min_before = Math.min(min_before, A[i]);
}

// calculate right part
let max_after = A[N - 1];
rightMaxGaps[N - 1] = -Infinity;
for (let i = N - 2; i > 1; i--) {
  rightMaxGaps[i] = Math.max(rightMaxGaps[i + 1], max_after - A[i]);

  // update maximum
  max_after = Math.max(max_after, A[i]);
}

// get the answer
let answer = -Infinity;
for (let i = 1; i < N - 2; i++) {
  answer = Math.max(answer, leftMaxGaps[i] + rightMaxGaps[i + 1]);
}

// print the answer
console.log(answer);