import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

const N = parseInt(nextLine());

const pattern = nextLine();
const [preToken, postToken] = pattern.split('*');
const regex = new RegExp(`^${preToken}.*${postToken}$`);

for (let i = 0; i < N; i++) {
  const str = nextLine();
  console.log(str.match(regex) ? 'DA' : 'NE');
}
