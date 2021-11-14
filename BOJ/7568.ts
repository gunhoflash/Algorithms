import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
const N: number = parseInt(nextLine()); // the number of people
const people: number[][] = Array(N).fill(null).map(
  () => nextLine().split(' ').map(n => parseInt(n))
);

const answer = people.map(
  ([x, y]) => people.filter(([p, q]) => p > x && q > y).length + 1
).join(' ');

// print the answer
console.log(answer);