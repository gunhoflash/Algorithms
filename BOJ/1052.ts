import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = `${__dirname}/input.txt`;
  // const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// set N and K
let [N, K] = nextLine().split(' ').map(n => Number.parseInt(n));
let nBoughtBottles = 0;

while (true) {
  // convert N to binary string
  const binaryString = N.toString(2);

  // count the number of bottles
  const nBottles = Array.from(binaryString).filter(bit => bit === '1').length;

  // break the loop when the number of bottles is equals to or lower than {K}
  if (nBottles <= K) break;

  // get the size of the smallest bottle
  const sizeOfSmallestBottle = Number.parseInt(binaryString.substring(binaryString.lastIndexOf('1')), 2);

  // buy bottles
  nBoughtBottles += sizeOfSmallestBottle;
  N += sizeOfSmallestBottle;
}

// print the answer
console.log(nBoughtBottles);
