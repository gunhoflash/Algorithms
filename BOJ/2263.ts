import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;
const nextLineNumbers = () => nextLine().split(' ').map(Number);

// 구간 타입
type Range = {
  inOrderStart: number;
  inOrderEnd: number;
  postOrderStart: number;
  postOrderEnd: number;
};

// init
const [N] = nextLineNumbers();
const inOrder = nextLineNumbers();
const postOrder = nextLineNumbers();
const preOrder: Array<number> = [];

const inOrderIndex: Array<number> = [];
inOrder.forEach((value, index) => inOrderIndex[value] = index);

const printingStack: Array<Range> = [{
  inOrderStart: 0,
  inOrderEnd: N - 1,
  postOrderStart: 0,
  postOrderEnd: N - 1,
}];
while (printingStack.length) {
  // pop one
  const {
    inOrderStart,
    inOrderEnd,
    postOrderStart,
    postOrderEnd,
  } = printingStack.pop()!;
  const root = postOrder[postOrderEnd];
  const inOrderIndexOfRoot = inOrderIndex[root];
  const nLeft = inOrderIndexOfRoot - inOrderStart;
  const nRight = inOrderEnd - inOrderIndexOfRoot;

  // print the local root
  preOrder.push(root);

  // push all rights
  if (nRight > 0) {
    printingStack.push({
      inOrderStart: inOrderIndexOfRoot + 1,
      inOrderEnd: inOrderEnd,
      postOrderStart: postOrderStart + nLeft,
      postOrderEnd: postOrderEnd - 1,
    });
  }
  // push all lefts
  if (nLeft > 0) {
    printingStack.push({
      inOrderStart: inOrderStart,
      inOrderEnd: inOrderIndexOfRoot - 1,
      postOrderStart: postOrderStart,
      postOrderEnd: postOrderStart + nLeft - 1,
    });
  }
}

// print the pre-order result
console.log(preOrder.join(' '));
