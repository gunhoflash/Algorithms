import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;
const nextLineStrings = () => nextLine().split(' ');
let output = '';

type Node = {
  value: String;
  left: Node;
  right: Node;
} | null;

const ROOT_ALPHABET = 'A';
const NONE_ALPHABET = '.';

const printPreOrder = (node: Node) => {
  if (node === null) return;
  output += node.value;
  printPreOrder(node.left);
  printPreOrder(node.right);
};

const printInOrder = (node: Node) => {
  if (node === null) return;
  printInOrder(node.left);
  output += node.value;
  printInOrder(node.right);
};

const printPostOrder = (node: Node) => {
  if (node === null) return;
  printPostOrder(node.left);
  printPostOrder(node.right);
  output += node.value;
};

// get the number of nodes
const N = parseInt(nextLine());
const nodes = new Map<string, Node>();
nodes.set(NONE_ALPHABET, null);
for (let i = 0; i < N; i++) {
  const value = String.fromCharCode(65 + i);
  nodes.set(value, { value, left: null, right: null });
}

// construct the tree
for (let i = 0; i < N; i++) {
  const [n, l, r] = nextLineStrings();
  const node = nodes.get(n)!;
  const left = nodes.get(l)!;
  const right = nodes.get(r)!;
  node.left = left;
  node.right = right;
}

const root = nodes.get(ROOT_ALPHABET)!;
printPreOrder(root);
output += '\n';
printInOrder(root);
output += '\n';
printPostOrder(root);
output += '\n';

// print the answer
console.log(output);
