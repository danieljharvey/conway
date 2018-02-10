/* changed.re - has the board actually changed? (we stop if not) */
let pairIsSame = pair => pair[0] === pair[1];

open List;

let hasChanged = (oldGrid: Life.grid, newGrid: Life.grid) =>
  List.fold_left2(
    (total, oldOne, newOne) => oldOne !== newOne ? true : total,
    false,
    flatten(oldGrid),
    flatten(newGrid)
  );