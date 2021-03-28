import * as fs from 'fs';

const inputManager: Generator<string, any, unknown> = (function *() {
  const stdin = '/dev/stdin';
  const lines = fs.readFileSync(stdin).toString().split('\n');
  for (const line of lines) yield line;
  return null;
})();
const nextLine = (): string => inputManager.next().value;

class MinMax {
  public max: number;
  public min: number;

  constructor(max: number = -Infinity, min: number = Infinity) {
    this.max = max;
    this.min = min;
  }

  updateMax(...max: number[]) {
    this.max = Math.max(this.max, ...max);
  }

  updateMin(...min: number[]) {
    this.min = Math.min(this.min, ...min);
  }
};

// get all inputs
const N: number = parseInt(nextLine()); // the length of expression
const expression: string = nextLine();

function getMinMax(expression: string): MinMax {
  const length = expression.length;

  if (length == 1) {
    const firstNumber = parseInt(expression[0]);
    return new MinMax(firstNumber, firstNumber);
  }

  // divide by every operator
  const result = new MinMax();
  for (let i = 1; i < length - 1; i += 2) {
    const left_result = getMinMax(expression.slice(0, i));
    const right_result = getMinMax(expression.slice(i + 1));

    switch (expression[i]) {
      case '+':
      result.updateMax(left_result.max + right_result.max);
      result.updateMin(left_result.min + right_result.min);
      break;

      case '-':
      result.updateMax(left_result.max - right_result.min);
      result.updateMin(left_result.min - right_result.max);
      break;

      case '*':
      result.updateMax(left_result.max * right_result.max, left_result.max * right_result.min, left_result.min * right_result.max, left_result.min * right_result.min);
      result.updateMin(left_result.max * right_result.max, left_result.max * right_result.min, left_result.min * right_result.max, left_result.min * right_result.min);
      break;
    }
  }

  return result;
}

console.log(getMinMax(expression).max);
