function solution(n, s, a, b, fares) {
  // init distances: a square matrix of size (n + 1)
  const distances = Array(n + 1).fill().map(() => Array(n + 1).fill(Infinity));
  for (const [c, d, f] of fares) {
    distances[c][d] = distances[d][c] = f;
  }

  // use Floyd-Warshall Algorithm
  for (let k = 1; k <= n; k++) {
    distances[k][k] = 0;
    for (let i = 1; i <= n; i++) {
      for (let j = 1; j <= n; j++) {
        distances[i][j] = Math.min(distances[i][j], distances[i][k] + distances[k][j]);
      }
    }
  }

  // find the minimum cost
  return Math.min(...distances[s].map((d, i) => d + distances[i][a] + distances[i][b]));
}