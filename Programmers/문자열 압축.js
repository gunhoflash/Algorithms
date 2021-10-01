const splitWithSize = (str, size) => [...str.matchAll(new RegExp(`(.{${size}})|.+$`, 'g'))].map(([str]) => str);

const tokenize = str => ({ value: str, repeat: 1 });

const mergeTokens = tokens => {
  if (tokens.length < 2) return tokens;

  const arr = [];
  let prevToken = tokens[0];

  tokens.slice(1).forEach(token => {
    if (prevToken.value === token.value) {
      prevToken.repeat++;
    } else {
      arr.push(prevToken);
      prevToken = token;
    }
  });
  arr.push(prevToken);

  return arr;
}

const getStringifiedTokenLength = ({value, repeat}) => value.length + (repeat > 1 ? repeat.toString().length : 0);

const sum = arr => arr.reduce((acc, v) => acc + v, 0);

const map = f => arr => arr.map(f);

const pipe = (f, ...restF) => (...args) => (f ? pipe(...restF)(f(...args)) : args);

function solution(str) {
  let answer = str.length;

  for (let size = Math.floor(str.length / 2); size; size--) {
    const length = pipe(
      splitWithSize, // 문자열을 사이즈만큼 나눠서 배열로 만든다.
      map(tokenize), // 각 문자열을 토큰화한다.
      mergeTokens, // 인접한 같은 토큰을 합친다.
      map(getStringifiedTokenLength), // 각 토큰을 문자열로 변환한 길이를 구한다
      sum, // 각 문자열의 길이를 합친다.
    )(str, size);
    answer = Math.min(answer, length);
  }

  return answer;
}