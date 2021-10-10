import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  // const stdin = '/dev/stdin';
  const stdin = './input';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

// get all inputs
const [N, C] = nextLine().split(' ').map(n => parseInt(n));
const houses: Array<number> = [];
for (let i = 0; i < N; i++) {
  houses.push(parseInt(nextLine()));
}

// return whether the distance is enough to place all routers
function isValidDistance(distance: Number): boolean {
  let nRouter = 1;
  let prev = houses[0];
  for (let i = 1; i < N; i++) {
    if (houses[i] - prev >= distance) {
      prev = houses[i];
      nRouter++;
    }
  }

  return nRouter >= C;
}

// sort houses in ascending order
houses.sort((a, b) => a - b);

// get the maximum of minimum distance between routers
let minDistance = 1;
let maxDistance = Math.floor((houses[N - 1] - houses[0]) / (C - 1));
while (minDistance <= maxDistance) {
  const distance = Math.floor((minDistance + maxDistance) / 2);
  if (isValidDistance(distance)) {
    minDistance = distance + 1;
  } else {
    maxDistance = distance - 1;
  }
}

const answer = minDistance - 1;

// print the answer
console.log(answer);
