import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
nextLine(); // the number of numbers
const A: Set<string> = new Set(nextLine().split(' '));
nextLine(); // the number of queries
const queries: Array<string> = nextLine().split(' ');

// print the answer
console.log(queries.map(n => A.has(n) ? '1' : '0').join('\n'));
