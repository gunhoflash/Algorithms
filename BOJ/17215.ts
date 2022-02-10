import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

const Strike = 'S';
const Spare = 'P';

// get frames
const frames = nextLine().replace(/S/g, 'S-').match(/.{1,2}/g)!;

// return [firstScore, secondScore, isStrike, isSpare]
const getFrameInfo = (frame: string): [number, number, boolean, boolean] => {
  if (frame[0] === Strike) return [10, 0, true, false];
  const firstScore = parseInt(frame[0]) || 0;
  if (frame[1] === Spare) return [firstScore, 10 - firstScore, false, true];
  return [firstScore, parseInt(frame[1]) || 0, false, false];
};

let score = 0;
let nextBonus = 0;
let nextNextBonus = 0;

for (let i = 0; i < frames.length; i++) {
  const frame = frames[i];
  const [firstScore, secondScore, isStrike, isSpare] = getFrameInfo(frame);
  const frameScore = firstScore + secondScore;

  score += frameScore;

  if (isStrike) {
    score += firstScore * nextBonus;
    nextBonus = nextNextBonus;
    nextNextBonus = 0;
    if (i < 9) {
      nextBonus++;
      nextNextBonus++;
    }
  } else {
    score += firstScore * nextBonus + secondScore * nextNextBonus;
    nextBonus = 0;
    nextNextBonus = 0;
    if (isSpare && i < 9) {
      nextBonus++;
    }
  }
}

// print total score
console.log(score);
