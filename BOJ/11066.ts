import * as fs from 'fs';

const inputManager = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

function doAllTests(T: number): void {
  while (T--) {
    doTest();
  }
}

function doTest(): void {
  // get the number of pages and each file size
  const K = parseInt(nextLine());
  const fileSizes = nextLine().split(' ');

  // init {rangeSum} and {minCost}
  const rangeSum: number[][] = Array(K);
  const minCost: number[][] = Array(K);
  for (let i = 0; i < K; i++) {
    rangeSum[i] = Array(K);
    minCost[i] = Array(K);

    rangeSum[i][i] = parseInt(fileSizes[i]);
    minCost[i][i] = 0;
  }

  // start from range 2 to {K}
  for (let rangeLength = 2; rangeLength <= K; rangeLength++) {
    for (let firstIndex = 0; firstIndex <= K - rangeLength; firstIndex++) {
      const lastIndex = firstIndex + rangeLength - 1;

      rangeSum[firstIndex][lastIndex] = rangeSum[firstIndex][lastIndex - 1] + rangeSum[lastIndex][lastIndex];
      minCost[firstIndex][lastIndex] = Infinity;

      // find minimum cost
      for (let i = 0; i < rangeLength - 1; i++) {
        const newCost =
          rangeSum[firstIndex][firstIndex + i] +
          minCost[firstIndex][firstIndex + i] +
          rangeSum[firstIndex + i + 1][lastIndex] +
          minCost[firstIndex + i + 1][lastIndex];

        // update minimum cost
        if (newCost < minCost[firstIndex][lastIndex]) {
          minCost[firstIndex][lastIndex] = newCost;
        }
      }
    }
  }

  // print the answer
  console.log(minCost[0][K - 1]);
}

// get the number of test cases and start all tests
doAllTests(parseInt(nextLine()));

export {
  doAllTests,
  doTest
};
