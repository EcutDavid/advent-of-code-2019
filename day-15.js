const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin
  // output: process.stdout
});

function parseComponent(component) {
  const parts = component.split(' ');
  return [Number(parts[0]), parts[1]];
}

function checkIsDone(state) {
  for (const [k, v] of state) {
    if (k === 'ORE') continue;
    if (v > 0) return false;
  }
  return true;
}

(async function() {
  const needs = {};
  const kSet = new Set();
  const weightMap = new Map();

  for await (const line of rl) {
    // Each line in input.txt will be successively available here as `line`.
    let [left, right] = line.split(' => ');
    left = line.split(', ').map(parseComponent);
    const [v, k] = parseComponent(right);
    kSet.add(k);
    if (!needs[k]) needs[k] = new Map();
    weightMap.set(k, v);

    for (const d of left) {
      kSet.add(d[1]);
      needs[k].set(d[1], d[0]);
    }
  }


  // Q1
  const state = new Map([["FUEL", 1]]);

  while (!checkIsDone(state)) {
    for (const [k1, v1] of state) {
      if (k1 === "ORE" || v1 <= 0) continue;
      const times = Math.ceil(v1 / weightMap.get(k1));
      state.set(k1, v1 - times * weightMap.get(k1))
      for (const [k2, v2] of needs[k1]) {
        if (!state.get(k2)) state.set(k2, 0);
        state.set(k2, state.get(k2) + v2 * times);
      }
    }
  }

  console.log("Q1 answer", state.get('ORE'));

  // Q2, use binary search to solve the problem
  let l = 1, r = 1e8, q2Answer = -1;
  while (l <= r) {
    const mid = Math.floor((l + r) / 2);
    const state = new Map([["FUEL", mid]]);

    while (!checkIsDone(state)) {
      for (const [k1, v1] of state) {
        if (k1 === "ORE" || v1 <= 0) continue;
        const times = Math.ceil(v1 / weightMap.get(k1));
        state.set(k1, v1 - times * weightMap.get(k1));
        for (const [k2, v2] of needs[k1]) {
          if (!state.get(k2)) state.set(k2, 0);
          state.set(k2, state.get(k2) + v2 * times);
        }
      }
    }

    const cost = state.get("ORE");
    if (cost > 1e12) {
      r = mid - 1;
    } else {
      l = mid + 1;
      q2Answer = mid;
    }
  }

  console.log("Q2 answer", q2Answer);
})();
