import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;
const nextLineNumbers = () => nextLine().split(' ').map(Number);

type Node = {
  id: number;
  parent: number | null;
  adjacents: Node[];
};

// init all nodes (index 0 is dummy)
const [N] = nextLineNumbers();
const nodes: Array<Node> = new Array(N + 1).fill(null).map((_, i) => ({
  id: i,
  parent: null,
  adjacents: [],
}));

// get all edges
for (let i = 0; i < N - 1; i++) {
  const [p, q] = nextLineNumbers();
  nodes[p].adjacents.push(nodes[q]);
  nodes[q].adjacents.push(nodes[p]);
}

// start from the root: node 1
nodes[1].parent = 1;
const visitingQueue = [nodes[1]];
while (visitingQueue.length) {
  // pop one
  const node = visitingQueue.shift()!;

  // visit all adjacent nodes
  // set parent and push to queue
  visitingQueue.push(
    ...node.adjacents.filter(node => node.parent === null).map(adj => {
      adj.parent = node.id;
      return adj;
    })
  );
}

// print parents
console.log(
  nodes.slice(2).map(node => node.parent).join('\n')
);
