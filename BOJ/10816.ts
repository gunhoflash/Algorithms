import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
nextLine(); // the size of array
const array: Array<string> = nextLine().split(' ');
nextLine(); // the number of queries
const queries: Array<string> = nextLine().split(' ');

// init map
const map = new Map<string, number>();
for (const n of array) {
  const count = map.get(n);
  map.set(n, (count || 0) + 1);
}

// print the answer
console.log(queries.map(n => map.get(n) || 0).join(' '));
