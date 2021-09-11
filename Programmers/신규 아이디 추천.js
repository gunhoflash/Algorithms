function solution(new_id) {
  let answer = new_id
    .toLowerCase()
    .replace(/[^a-z0-9._-]/g, '')
    .replace(/\.+/g, '.')
    .replace(/^\./, '')
    .replace(/\.$/, '')
    .replace(/^$/g, 'a')
    .slice(0, 15)
    .replace(/\.$/, '');

  while (answer.length <= 2) {
    answer += answer.slice(-1);
  }
  return answer;
}
