import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;
const nextLineNumbers = () => nextLine().split(' ').map(Number);
let output = '';

type Node = {
  isVisited: boolean;
  adjacents: Node[];
}

const getNumberOfTree = (n: number, m: number): number => {
  let nTree = 0;
  const nodes: Array<Node> = Array(n + 1).fill(null).map(() => ({
    isVisited: false,
    adjacents: [],
  }));

  // config adjacents
  for (let i = 0; i < m; i++) {
    const [a, b] = nextLineNumbers();
    nodes[a].adjacents.push(nodes[b]);
    nodes[b].adjacents.push(nodes[a]);
  }

  // check all nodes
  for (let i = n; i; i--) {
    const node = nodes[i];
    if (node.isVisited) continue;

    let isTree = true;

    // bfs from the node
    const q = [node];
    while (q.length) {
      // pop one
      const cur = q.shift()!;

      if (cur.isVisited) {
        // graph has a cycle
        isTree = false;
        continue;
      }
      cur.isVisited = true;

      // visit adjacents
      q.push(...cur.adjacents.filter(adj => !adj.isVisited));
    }

    // a new tree found
    if (isTree) nTree++;
  }

  return nTree;
};

let testNumber = 0;

while (true) {
  let [n, m] = nextLineNumbers();
  if (n == 0 && m == 0) break;

  testNumber++;
  output += `Case ${testNumber}: `;

  const nTree = getNumberOfTree(n, m);
  switch (nTree) {
    case 0:
      output += 'No trees.\n';
      break;
    case 1:
      output += 'There is one tree.\n';
      break;
    default:
      output += `A forest of ${nTree} trees.\n`;
      break;
  }
}

console.log(output);
