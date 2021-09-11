function getOrderSet(order) {
  let orderSet = new Set([order]);

  // register sub-order
  const n = order.length;
  if (n > 2) {
    for (let i = 0; i < n; i++) {
      getOrderSet(order.substring(0, i) + order.substring(i + 1))
        .forEach(o => orderSet.add(o));
    }
  }

  return orderSet;
}

function solution(orders, course) {
  const orderMap = {};
  const maxFrequency = Array(11).fill(Infinity);

  // register all orders
  orders.forEach(order => {
    getOrderSet(order.split('').sort().join(''))
      .forEach(o => {
        orderMap[o] = (orderMap[o] || 0) + 1;
      });
  });

  // init maxFrequency
  course.forEach(size => {
    maxFrequency[size] = 2;
  });

  // filter mostFrequentOrders
  const mostFrequentOrders = Array(11);
  for (let i = 0; i < 11; i++) {
    mostFrequentOrders[i] = [];
  }

  Object.entries(orderMap)
  .forEach(([order, frequency]) => {
    const size = order.length;
    if (frequency < maxFrequency[size]) return;
    if (frequency > maxFrequency[size]) {
      maxFrequency[size] = frequency;
      mostFrequentOrders[size] = [];
    }
    mostFrequentOrders[size].push(order);
  });

  return mostFrequentOrders.flat().sort();
}
