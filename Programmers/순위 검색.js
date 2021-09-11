function infoToBit(language, tech, career, food) {
  let b = 0b000000000;

  switch (language) {
    case 'cpp':    b |= 0b100000000; break;
    case 'java':   b |= 0b010000000; break;
    case 'python': b |= 0b001000000; break;
    case '-':      b |= 0b111000000; break;
  }

  switch (tech) {
    case 'backend':  b |= 0b000100000; break;
    case 'frontend': b |= 0b000010000; break;
    case '-':        b |= 0b000110000; break;
  }

  switch (career) {
    case 'junior': b |= 0b000001000; break;
    case 'senior': b |= 0b000000100; break;
    case '-':      b |= 0b000001100; break;
  }

  switch (food) {
    case 'chicken': b |= 0b000000010; break;
    case 'pizza':   b |= 0b000000001; break;
    case '-':       b |= 0b000000011; break;
  } 

  return b;
}

function initBitMap(bitMap) {
  const languages = ['cpp', 'java', 'python', '-'];
  const techs = ['backend', 'frontend', '-'];
  const careers = ['junior', 'senior', '-'];
  const foods = ['chicken', 'pizza', '-'];

  languages.forEach(language => {
    techs.forEach(tech => {
      careers.forEach(career => {
        foods.forEach(food => {
          const bit = infoToBit(language, tech, career, food);
          bitMap[bit] = [];
        });
      });
    });
  });
}

function sortBitMapScore(bitMap) {
  Object.values(bitMap).forEach(arr => arr.sort((a, b) => a - b));
}

function solution(info, queries) {
  const bitMap = {}

  initBitMap(bitMap);
  info.forEach(str => {
    const [language, tech, career, food, score] = str.split(' ');
    bitMap[infoToBit(language, tech, career, food)].push(parseInt(score));
  });
  sortBitMapScore(bitMap);

  return queries.map(query => {
    const [language, tech, career, food, score] = query.replace(/\sand/g, '').split(' ');
    const queryBit = infoToBit(language, tech, career, food);
    const minScore = parseInt(score);

    return Object.entries(bitMap).reduce((n, [bit, arr]) => {
      const b = bit & queryBit;
      if ((b & 0b111000000) && (b & 0b000110000) && (b & 0b000001100) && (b & 0b000000011)) {
        // use binary search that match minScore
        let left = 0;
        let right = arr.length - 1;
        while (left <= right) {
          const mid = Math.floor((left + right) / 2);
          if (arr[mid] >= minScore) {
            right = mid - 1;
          } else {
            left = mid + 1;
          }
        }
        n += arr.length - left;
      }

      return n;
    }, 0);
  });
}
