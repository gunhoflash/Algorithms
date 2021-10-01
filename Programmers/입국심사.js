function solution(n, times) {
  let answerMin = 1;
  let answerMax = Math.min(...times) * n;

  while (answerMin < answerMax) {
    // presume answer and check whether it is right
    const answer = Math.floor((answerMin + answerMax) / 2);
    const maxN = times.reduce((acc, time) => acc + Math.floor(answer / time), 0);
    if (maxN < n) {
      answerMin = answer + 1;
    } else {
      answerMax = answer;
    }
  }

  return answerMin;
}