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
  allChildrenVisited: boolean;
  maxDistanceToLeaf: number;
  edges: Edge[];
};

type Edge = {
  to: Node;
  distance: number;
};

// init all nodes (index 0 is dummy)
let [N] = nextLineNumbers();
const nodes: Array<Node> = new Array(N + 1).fill(null).map((_, i) => ({
  allChildrenVisited: false,
  maxDistanceToLeaf: 0,
  edges: [],
}));

let maxDiameter = 0;

const findMaximumDistanceToLeaf = (node: Node) => {
  let firstMaxDistanceToLeaf = 0;
  let secondMaxDistanceToLeaf = 0;

  for (const edge of node.edges) {
    // update maxDistanceToLeaf
    const distanceToLeaf = edge.distance + edge.to.maxDistanceToLeaf;
    if (distanceToLeaf >= firstMaxDistanceToLeaf) {
      secondMaxDistanceToLeaf = firstMaxDistanceToLeaf;
      firstMaxDistanceToLeaf = distanceToLeaf;
    } else if (distanceToLeaf > secondMaxDistanceToLeaf) {
      secondMaxDistanceToLeaf = distanceToLeaf;
    }
  }

  // update maximum diameter
  const diameter = firstMaxDistanceToLeaf + secondMaxDistanceToLeaf;
  if (diameter > maxDiameter) {
    maxDiameter = diameter;
  }

  return firstMaxDistanceToLeaf;
}

// construct tree
while (--N) {
  const [p, c, d] = nextLineNumbers();

  const parent = nodes[p];
  const child = nodes[c];
  parent.edges.push({ to: child, distance: d });
}

// start from the root node
const visitingStack = [nodes[1]];
while (visitingStack.length) {
  const node = visitingStack[visitingStack.length - 1];

  // check if children are visited
  if (!node.allChildrenVisited) {
    node.allChildrenVisited = true;
    // visit children first
    visitingStack.push(...node.edges.map(({to}) => to));
    continue;
  }

  // if all children are visited,
  // then visit this node
  visitingStack.pop();
  node.maxDistanceToLeaf = findMaximumDistanceToLeaf(node);
}

// print the maximum diameter
console.log(maxDiameter);
